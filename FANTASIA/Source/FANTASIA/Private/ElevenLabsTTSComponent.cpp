// Fill out your copyright notice in the Description page of Project Settings.

#include "ElevenLabsTTSComponent.h"

// Sets default values for this component's properties
UElevenLabsTTSComponent::UElevenLabsTTSComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UElevenLabsTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	isPlaying.store(true);

	FTTSResultAvailableDelegate TTSResultSubscriber;
	FTTSPartialResultAvailableDelegate TTSPartialResultSubscriber;

	TTSResultSubscriber.BindUObject(this, &UElevenLabsTTSComponent::getResult);
	TTSPartialResultSubscriber.BindUObject(this, &UElevenLabsTTSComponent::getPartialResult);
	handle = ElevenLabsTTSThread::setup(Key, VoiceID, ModelID, stability, similarity_boost, style, use_speaker_boost, true);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
	TTSPartialResultAvailableHandle = handle->TTSPartialResultAvailableSubscribeUser(TTSPartialResultSubscriber);

	AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this]() {
		TArray<float> outData;
		// [OPT] Pre-allocate to avoid repeated reallocation during streaming.
		outData.Reserve(A2F_STREAMING_BATCH_SIZE);
		float item;

		while (isPlaying.load(std::memory_order_relaxed)) {

			// ---- Wait for work instead of spin-looping ----
			// [OPT-CRITICAL] The original code was a bare while(isPlaying) with no sleep/yield.
			// That burns an entire CPU core (~100% utilisation on one logical processor) doing nothing
			// whenever the TTS is idle — which is most of the time. FEvent::Wait blocks the OS thread
			// at zero CPU cost until signalled by getPartialResult/getResult/EndPlay.
			// Timeout of 50ms is a safety net so the thread re-checks isPlaying even if a signal is missed.
			ConsumerWakeEvent->Wait(50);
			ConsumerWakeEvent->Reset();

			// ---- Flush stale data from a previous synthesis ----
			// [FIX] Prevents the buffer-bleed bug: orphaned samples from sentence A leaking into sentence B.
			if (needsFlush.load(std::memory_order_acquire)) {
				while (sendData.Dequeue(item)) {}  // drain queue (SPSC-safe: we are the sole consumer)
				outData.Empty();
				bufferOpen.store(false);
				needsFlush.store(false, std::memory_order_release);
				continue;  // re-check; more data may have arrived during flush
			}

			// ---- Streaming: batch samples for A2F ----
			if (!sendData.IsEmpty())
				bufferOpen.store(true);

			if (usingStreamingBuffer.load(std::memory_order_acquire) && sendData.Dequeue(item)) {
				outData.Add(item);

				// [OPT] Drain up to a full batch in one iteration instead of dequeuing one sample per loop pass.
				// The original code dequeued exactly 1 sample per outer-loop iteration, meaning it had to
				// spin through the while(isPlaying) overhead, the IsEmpty() check, and the atomic loads
				// 100 times just to fill one batch. This inner drain pulls everything available in one go.
				while (outData.Num() < A2F_STREAMING_BATCH_SIZE && sendData.Dequeue(item)) {
					outData.Add(item);
				}

				if (outData.Num() >= A2F_STREAMING_BATCH_SIZE) {
					FACERuntimeModule::Get().AnimateFromAudioSamples(A2Fpointer, outData, 1, 16000, false, EmotionParameters, A2FParameters, A2FProvider);
					outData.Empty();
				}
			}
			// ---- Drain: streaming ended, flush remaining samples with final=true ----
			else if (!usingStreamingBuffer.load(std::memory_order_acquire) && bufferOpen.load()) {
				while (sendData.Dequeue(item))
					outData.Add(item);
				FACERuntimeModule::Get().AnimateFromAudioSamples(A2Fpointer, outData, 1, 16000, true, EmotionParameters, A2FParameters, A2FProvider);
				outData.Empty();
				bufferOpen.store(false);
				UE_LOG(LogTemp, Warning, TEXT("Closed audio buffer"));
			}
		}
	});
}

void UElevenLabsTTSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	isPlaying.store(false);
	ConsumerWakeEvent->Trigger();  // [OPT] Wake the consumer so it sees isPlaying==false and exits promptly
}

// Called every frame
void UElevenLabsTTSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// [FIX] Original used else-if, which starved PartialSynthesisReady whenever a full result was
	// also pending in the same frame. Now both can fire independently per tick.
	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}

	if (idPartialSynthesisReady != "") {
		PartialSynthesisReady.Broadcast(idPartialSynthesisReady);
		idPartialSynthesisReady = "";
	}
}

void UElevenLabsTTSComponent::getResult(FTTSData response, FString id)
{
	if (IsValid(A2Fpointer) && usingStreamingBuffer.load()) {
		UE_LOG(LogTemp, Warning, TEXT("Streaming finished"));
		usingStreamingBuffer.store(false);
		needsFlush.store(true, std::memory_order_release);  // [FIX] Signal consumer to discard any stale tail
		ConsumerWakeEvent->Trigger();                        // [OPT] Wake consumer for the drain
	}

	Buffer.Remove(id);
	Buffer.Add(id, response);
	idSynthesisReady = id;
}

void UElevenLabsTTSComponent::getPartialResult(TArray<uint8> response, FString id)
{
	// [FIX] Guard against empty or single-byte responses.
	// Original: `i < response.Num() - 1` with int — if Num()==0, this wraps to MAX_INT on unsigned comparison.
	const int32 NumBytes = response.Num();
	if (NumBytes < 2) return;

	// [OPT] Bulk-convert and enqueue. Access raw pointer once instead of calling GetData() per iteration.
	const uint8* RawData = response.GetData();
	for (int32 i = 0; i <= NumBytes - 2; i += 2) {
		sendData.Enqueue(static_cast<float>(*reinterpret_cast<const int16*>(RawData + i)) / 32768.0f);
	}

	if (IsValid(A2Fpointer) && !usingStreamingBuffer.load() && !bufferOpen.load()) {
		UE_LOG(LogTemp, Warning, TEXT("Starting streaming"));
		usingStreamingBuffer.store(true);
		bufferOpen.store(true);
	}

	// [OPT] Wake consumer — data is now available
	ConsumerWakeEvent->Trigger();

	idPartialSynthesisReady = id;
}

void UElevenLabsTTSComponent::TTSSynthesize(FString text, FString id)
{
	handle->Synthesize(text, id);
}

USoundWaveProcedural* UElevenLabsTTSComponent::TTSGetSound(FString id) {
	USoundWaveProcedural* SyntheticVoice = NewObject<USoundWaveProcedural>();
	// [FIX] Removed: USoundWave* SyntheticVoiceOut = NewObject<USoundWave>()
	// That object was allocated every call but never used — a GC-tracked memory leak.

	constexpr float SamplingRate = 16000.f;

	SyntheticVoice->SetSampleRate(SamplingRate);
	SyntheticVoice->NumChannels = 1;
	SyntheticVoice->RawPCMDataSize = Buffer[id].AudioData.Num() * sizeof(uint8);
	SyntheticVoice->Duration = static_cast<float>(Buffer[id].AudioData.Num()) / (2.f * SamplingRate);
	SyntheticVoice->QueueAudio(Buffer[id].AudioData.GetData(), SyntheticVoice->RawPCMDataSize);

	return SyntheticVoice;
}

TArray<uint8> UElevenLabsTTSComponent::TTSGetRawSound(FString id) {
	// [OPT] Return a direct copy via bulk operation instead of element-by-element Add().
	// Original allocated into a *member* array (not thread-safe if called from multiple contexts)
	// then copied it again on return. This returns a clean local with a single memcpy.
	return Buffer[id].AudioData;
}
