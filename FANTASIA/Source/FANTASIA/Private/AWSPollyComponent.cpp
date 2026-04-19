// Fill out your copyright notice in the Description page of Project Settings.

/**
 * @file AWSPollyComponent.cpp
 * @brief Implementation of UAWSPollyComponent -- Amazon Polly TTS actor component.
 * @deprecated This component is deprecated and will be removed after switching to UE 5.7.
 */

#include "AWSPollyComponent.h"

using namespace std;

UAWSPollyComponent::UAWSPollyComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UAWSPollyComponent::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("[AWSPollyComponent] This component is deprecated and will be removed after switching to UE 5.7."));
}

/** Broadcasts the synthesis-ready event on the game thread when a result is pending. */
void UAWSPollyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}
		
}

/** Worker-thread callback: stores the result and flags it for game-thread broadcast. */
void UAWSPollyComponent::getResult(FTTSData response, FString id) {
	handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);
	handle->Shutdown();

	Buffer.Add(id, response);
	idSynthesisReady = id;
}

/** Wraps SSML in <speak> tags, spawns AWSPollyThread, and subscribes to its result event. */
void UAWSPollyComponent::AWSPollySynthesize(FString ssml, FString id, bool getLipSync) {
	ssml = "<speak>" + ssml + "</speak>";
	FTTSResultAvailableDelegate TTSResultSubscriber;
	TTSResultSubscriber.BindUObject(this, &UAWSPollyComponent::getResult);
	handle = AWSPollyThread::setup(voiceType, Voice, AccessKey, SecretAccessKey, ssml, id, getLipSync);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
}

TArray<FTTSTimedStruct> UAWSPollyComponent::AWSPollyGetLipSync(FString id) {
	TArray<FTTSTimedStruct> outStruct = Buffer[id].lipsync;

	return outStruct;
}

TArray<FTTSTimedStruct> UAWSPollyComponent::AWSPollyGetNotifies(FString id) {
	TArray<FTTSTimedStruct> outStruct = Buffer[id].notifies;

	return outStruct;
}

/** Creates a procedural SoundWave from buffered 16 kHz mono PCM data. */
USoundWave* UAWSPollyComponent::AWSPollyGetSound(FString id) {
	uint32 SAMPLING_RATE = 16000;

	USoundWaveProcedural* SyntheticVoice = NewObject<USoundWaveProcedural>();
	SyntheticVoice->SetSampleRate(SAMPLING_RATE);
	SyntheticVoice->NumChannels = 1;
	const int32 BytesDataPerSecond = SAMPLING_RATE;
	SyntheticVoice->RawPCMDataSize = Buffer[id].AudioData.Num() * sizeof(uint8);
	SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SAMPLING_RATE);
	SyntheticVoice->QueueAudio((const uint8*)Buffer[id].AudioData.GetData(), SyntheticVoice->RawPCMDataSize);
	return SyntheticVoice;
}

/** Converts buffered 16-bit PCM bytes to normalized float samples in [-1.0, 1.0]. */
TArray<float> UAWSPollyComponent::TTSGetRawSound(FString id) {
	TArray<float> AudioData;

	for (int i = 0; i < Buffer[id].AudioData.Num() * sizeof(uint8); i += 2) {
		float NormalizedSample = 0.0f;
		int16 Sample = *reinterpret_cast<int16*>(&Buffer[id].AudioData.GetData()[i]);
		NormalizedSample = Sample / 32768.0f;

		AudioData.Add(NormalizedSample);
	}
	return AudioData;
}