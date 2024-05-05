// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralTTSComponent.h"

using namespace std;

// Sets default values for this component's properties
UGeneralTTSComponent::UGeneralTTSComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGeneralTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!Speaker) {
		Speaker = NewObject<UAudioComponent>(this);
		Speaker->RegisterComponent();
	}
}

// Called every frame
void UGeneralTTSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}
}

void UGeneralTTSComponent::getResult(FTTSData response, FString id)
{
	handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);
	handle->Shutdown();

	Buffer.Remove(id);
	Buffer.Add(id, response);
	idSynthesisReady = id;
}

void UGeneralTTSComponent::TTSSynthesize(FString ssml, FString id)
{
	FTTSResultAvailableDelegate TTSResultSubscriber;
	TTSResultSubscriber.BindUObject(this, &UGeneralTTSComponent::getResult);
	handle = GeneralTTSThread::setup(ssml, id, Endpoint);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
}

USoundWave* UGeneralTTSComponent::TTSGetSound(FString id) {
	USoundWave* SyntheticVoice = NewObject<USoundWave>();
	SyntheticVoice->SetSampleRate(SamplingRate);
	SyntheticVoice->NumChannels = 1;
	const int32 BytesDataPerSecond = SamplingRate;
	SyntheticVoice->RawPCMDataSize = Buffer[id].AudioData.Num() * sizeof(uint8);
	SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SamplingRate);
	SyntheticVoice->RawPCMData = static_cast<uint8*>(FMemory::Malloc(SyntheticVoice->RawPCMDataSize));
	FMemory::Memcpy(SyntheticVoice->RawPCMData, Buffer[id].AudioData.GetData(), SyntheticVoice->RawPCMDataSize);
	return SyntheticVoice;
}