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
	handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);

	Buffer.Remove(id);
	Buffer.Add(id, response);
	idSynthesisReady = id;
}

void UElevenLabsTTSComponent::getPartialResult(TArray<uint8> response, FString id)
{
	if (!StreamingBuffer.Contains(id)) {
		TArray<float> newArray;

		StreamingBuffer.Add(id, newArray);
	}

	for (int i = 0; i < response.Num() - 1; i += 2)
		StreamingBuffer[id].Add(*reinterpret_cast<int16*>(&response.GetData()[i]) / 32768.0f);

	if (IsValid(A2Fpointer)) {
		A2Fpointer->QueueAudio(StreamingBuffer[id]);

		StreamingBuffer[id].Empty();
	}
	
	idPartialSynthesisReady = id;
}

void UElevenLabsTTSComponent::TTSSynthesize(FString text, FString id, bool stream)
{
	FTTSResultAvailableDelegate TTSResultSubscriber;
	FTTSPartialResultAvailableDelegate TTSPartialResultSubscriber;

	TTSResultSubscriber.BindUObject(this, &UElevenLabsTTSComponent::getResult);
	TTSPartialResultSubscriber.BindUObject(this, &UElevenLabsTTSComponent::getPartialResult);
	handle = ElevenLabsTTSThread::setup(Key, text, id, VoiceID, ModelID, stability, similarity_boost, style, use_speaker_boost, stream);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
	TTSPartialResultAvailableHandle = handle->TTSPartialResultAvailableSubscribeUser(TTSPartialResultSubscriber);
}

USoundWaveProcedural* UElevenLabsTTSComponent::TTSGetSound(FString id) {
	USoundWaveProcedural* SyntheticVoice = NewObject<USoundWaveProcedural>();
	float SamplingRate = 16000;

	SyntheticVoice->SetSampleRate(SamplingRate);
	SyntheticVoice->NumChannels = 1;
	const int32 BytesDataPerSecond = SamplingRate;
	SyntheticVoice->RawPCMDataSize = Buffer[id].AudioData.Num() * sizeof(uint8);
	SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SamplingRate);
	SyntheticVoice->QueueAudio((const uint8*) Buffer[id].AudioData.GetData(), SyntheticVoice->RawPCMDataSize);
	
	return SyntheticVoice;
}

TArray<float> UElevenLabsTTSComponent::TTSGetRawSound(FString id) {
	TArray<float> AudioData;

	for (int i = 0; i < Buffer[id].AudioData.Num() * sizeof(uint8); i += 2) {
		float NormalizedSample = 0.0f;
		int16 Sample = *reinterpret_cast<int16*>(&Buffer[id].AudioData.GetData()[i]);
		NormalizedSample = Sample / 32768.0f;

		AudioData.Add(NormalizedSample);
	}
	return AudioData;
}

TArray<float> UElevenLabsTTSComponent::TTSGetPartialRawSound(FString id) {
	TArray<float> AudioData;

	StreamingBuffer.RemoveAndCopyValue(id, AudioData);

	return AudioData;
}