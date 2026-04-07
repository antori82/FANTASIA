// Fill out your copyright notice in the Description page of Project Settings.

#include "AWSPollyComponent.h"

using namespace std;

// Sets default values for this component's properties
UDEPRECATED_AWSPollyComponent::UDEPRECATED_AWSPollyComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDEPRECATED_AWSPollyComponent::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("[AWSPollyComponent] This component is deprecated and will be removed after switching to UE 5.7."));
}

// Called every frame
void UDEPRECATED_AWSPollyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}
		
}

void UDEPRECATED_AWSPollyComponent::getResult(FTTSData response, FString id) {
	handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);
	handle->Shutdown();

	Buffer.Add(id, response);
	idSynthesisReady = id;
}

void UDEPRECATED_AWSPollyComponent::AWSPollySynthesize(FString ssml, FString id, bool getLipSync) {
	ssml = "<speak>" + ssml + "</speak>";
	FTTSResultAvailableDelegate TTSResultSubscriber;
	TTSResultSubscriber.BindUObject(this, &UDEPRECATED_AWSPollyComponent::getResult);
	handle = AWSPollyThread::setup(voiceType, Voice, AccessKey, SecretAccessKey, ssml, id, getLipSync);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
}

TArray<FTTSTimedStruct> UDEPRECATED_AWSPollyComponent::AWSPollyGetLipSync(FString id) {
	TArray<FTTSTimedStruct> outStruct = Buffer[id].lipsync;

	return outStruct;
}

TArray<FTTSTimedStruct> UDEPRECATED_AWSPollyComponent::AWSPollyGetNotifies(FString id) {
	TArray<FTTSTimedStruct> outStruct = Buffer[id].notifies;

	return outStruct;
}

USoundWave* UDEPRECATED_AWSPollyComponent::AWSPollyGetSound(FString id) {
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

TArray<float> UDEPRECATED_AWSPollyComponent::TTSGetRawSound(FString id) {
	TArray<float> AudioData;

	for (int i = 0; i < Buffer[id].AudioData.Num() * sizeof(uint8); i += 2) {
		float NormalizedSample = 0.0f;
		int16 Sample = *reinterpret_cast<int16*>(&Buffer[id].AudioData.GetData()[i]);
		NormalizedSample = Sample / 32768.0f;

		AudioData.Add(NormalizedSample);
	}
	return AudioData;
}