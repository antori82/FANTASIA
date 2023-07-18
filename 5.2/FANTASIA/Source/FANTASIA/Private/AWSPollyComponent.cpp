// Fill out your copyright notice in the Description page of Project Settings.

#include "AWSPollyComponent.h"

using namespace std;

// Sets default values for this component's properties
UAWSPollyComponent::UAWSPollyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAWSPollyComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UAWSPollyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}
		
}

void UAWSPollyComponent::getResult(FTTSData response, FString id)
{
	handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);
	handle->Shutdown();

	Buffer.Add(id, response);
	idSynthesisReady = id;
}

void UAWSPollyComponent::AWSPollySynthesize(FString ssml, FString id, bool getLipSync)
{
	ssml = "<speak>" + ssml + "</speak>";
	FTTSResultAvailableDelegate TTSResultSubscriber;
	TTSResultSubscriber.BindUObject(this, &UAWSPollyComponent::getResult);
	handle = AWSPollyThread::setup(voiceType, Voice, AccessKey, SecretAccessKey, ssml, id, getLipSync);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
}

/*
USoundWaveProcedural* UAWSPollyComponent::AWSPollyGetSound(FString id) {
	uint32 SAMPLING_RATE = 16000;

	SyntheticVoice = NewObject<USoundWaveProcedural>();
	SyntheticVoice->SetSampleRate(SAMPLING_RATE);
	SyntheticVoice->NumChannels = 1;
	SyntheticVoice->SoundGroup = SOUNDGROUP_Voice;
	SyntheticVoice->bLooping = false;
	SyntheticVoice->bProcedural = true;

	SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SAMPLING_RATE);
	SyntheticVoice->QueueAudio(Buffer[id].AudioData.GetData(), Buffer[id].AudioData.Num() * sizeof(int8));

	return SyntheticVoice;
}
*/

TArray<FTTSTimedStruct> UAWSPollyComponent::AWSPollyGetLipSync(FString id) {
	TArray<FTTSTimedStruct> outStruct = Buffer[id].lipsync;

	return outStruct;
}

TArray<FTTSTimedStruct> UAWSPollyComponent::AWSPollyGetNotifies(FString id) {
	TArray<FTTSTimedStruct> outStruct = Buffer[id].notifies;

	return outStruct;
}

USoundWave* UAWSPollyComponent::AWSPollyGetSound(FString id) {
	uint32 SAMPLING_RATE = 16000;

	USoundWave* SyntheticVoice = NewObject<USoundWave>();
	SyntheticVoice->SetSampleRate(SAMPLING_RATE);
	SyntheticVoice->NumChannels = 1;
	const int32 BytesDataPerSecond = SAMPLING_RATE;
	SyntheticVoice->RawPCMDataSize = Buffer[id].AudioData.Num() * sizeof(uint8);
	SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SAMPLING_RATE);
	SyntheticVoice->RawPCMData = static_cast<uint8*>(FMemory::Malloc(SyntheticVoice->RawPCMDataSize));
	FMemory::Memcpy(SyntheticVoice->RawPCMData, Buffer[id].AudioData.GetData(), SyntheticVoice->RawPCMDataSize);
	return SyntheticVoice;
}