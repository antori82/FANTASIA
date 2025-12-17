// Fill out your copyright notice in the Description page of Project Settings.

#include "ElevenLabsTTSComponent.h"

using namespace std;

// Sets default values for this component's properties
UElevenLabsTTSComponent::UElevenLabsTTSComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UElevenLabsTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	isPlaying = true;

	FTTSResultAvailableDelegate TTSResultSubscriber;
	FTTSPartialResultAvailableDelegate TTSPartialResultSubscriber;

	TTSResultSubscriber.BindUObject(this, &UElevenLabsTTSComponent::getResult);
	TTSPartialResultSubscriber.BindUObject(this, &UElevenLabsTTSComponent::getPartialResult);
	handle = ElevenLabsTTSThread::setup(Key, VoiceID, ModelID, stability, similarity_boost, style, use_speaker_boost, true);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
	TTSPartialResultAvailableHandle = handle->TTSPartialResultAvailableSubscribeUser(TTSPartialResultSubscriber);

	AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this]() {
		TArray<float> outData;
		float item;

		while (isPlaying) {
			if (!sendData.IsEmpty())
				bufferOpen = true;
			if (usingStreamingBuffer and sendData.Dequeue(item)) {
				outData.Add(item);

				if (outData.Num() >= 100) {
					FACERuntimeModule::Get().AnimateFromAudioSamples(A2Fpointer, outData, 1, 16000, false, EmotionParameters, A2FParameters, A2FProvider);
					outData.Empty();
				}
			}
			else if (!usingStreamingBuffer and bufferOpen) {
				while (sendData.Dequeue(item))
					outData.Add(item);
				FACERuntimeModule::Get().AnimateFromAudioSamples(A2Fpointer, outData, 1, 16000, true, EmotionParameters, A2FParameters, A2FProvider);
				outData.Empty();
				bufferOpen = false;
				UE_LOG(LogTemp, Warning, TEXT("Closed audio buffer"));
			}
		}
		});
}

void UElevenLabsTTSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	isPlaying = false;
}

// Called every frame
void UElevenLabsTTSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";

	}
	else if (idPartialSynthesisReady != "") {
		
		PartialSynthesisReady.Broadcast(idPartialSynthesisReady);
		idPartialSynthesisReady = "";
		//StreamingBuffer.Remove(idPartialSynthesisReady);
	}
}

void UElevenLabsTTSComponent::getResult(FTTSData response, FString id)
{

	//handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);

	if (IsValid(A2Fpointer) and usingStreamingBuffer) {
		UE_LOG(LogTemp, Warning, TEXT("Streaming finished"));
		usingStreamingBuffer = false;
	}

	Buffer.Remove(id);
	Buffer.Add(id, response);
	idSynthesisReady = id;


}

void UElevenLabsTTSComponent::getPartialResult(TArray<uint8> response, FString id)
{
	if (!StreamingBuffer.Contains(id)) {
		//TArray<float> newArray;

		//StreamingBuffer.Add(id, newArray);
	}

	for (int i = 0; i < response.Num() - 1; i += 2) {
		//StreamingBuffer[id].Add(*reinterpret_cast<int16*>(&response.GetData()[i]) / 32768.0f);
		sendData.Enqueue(*reinterpret_cast<int16*>(&response.GetData()[i]) / 32768.0f);
	}
		
	if (IsValid(A2Fpointer) and !usingStreamingBuffer and !bufferOpen) {
		UE_LOG(LogTemp, Warning, TEXT("Starting streaming"));
		usingStreamingBuffer = true;
		bufferOpen = true;
	}
	
	idPartialSynthesisReady = id;
}

void UElevenLabsTTSComponent::TTSSynthesize(FString text, FString id)
{
	handle->Synthesize(text, id);
}

USoundWaveProcedural* UElevenLabsTTSComponent::TTSGetSound(FString id) {
	USoundWaveProcedural* SyntheticVoice = NewObject<USoundWaveProcedural>();
	USoundWave* SyntheticVoiceOut = NewObject<USoundWave>();
	float SamplingRate = 16000;

	SyntheticVoice->SetSampleRate(SamplingRate);
	SyntheticVoice->NumChannels = 1;
	const int32 BytesDataPerSecond = SamplingRate;
	SyntheticVoice->RawPCMDataSize = Buffer[id].AudioData.Num() * sizeof(uint8);
	SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SamplingRate);
	SyntheticVoice->QueueAudio((const uint8*) Buffer[id].AudioData.GetData(), SyntheticVoice->RawPCMDataSize);

	return SyntheticVoice;
}

TArray<uint8> UElevenLabsTTSComponent::TTSGetRawSound(FString id) {
	SyntheticVoicePCMData.Empty();

	for (int i = 0; i < Buffer[id].AudioData.Num(); i++)
		SyntheticVoicePCMData.Add(Buffer[id].AudioData.GetData()[i]);

	return SyntheticVoicePCMData;
}