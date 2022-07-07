// Fill out your copyright notice in the Description page of Project Settings.

#include "AzureTTSComponent.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

// Sets default values for this component's properties
UAzureTTSComponent::UAzureTTSComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAzureTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	config = SpeechConfig::FromSubscription(std::string(TCHAR_TO_UTF8(*Key)), std::string(TCHAR_TO_UTF8(*Region)));
	//config-> SpeechSynthesisLanguage = std::string(TCHAR_TO_UTF8(*Language));
}

// Called every frame
void UAzureTTSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}
}

void UAzureTTSComponent::getResult(FTTSData response, FString id)
{
	handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);
	handle->Shutdown();

	Buffer.Add(id, response);
	idSynthesisReady = id;
}

void UAzureTTSComponent::AzureTTSSynthesize(FString ssml, FString id)
{
	FTTSResultAvailableDelegate TTSResultSubscriber;
	TTSResultSubscriber.BindUObject(this, &UAzureTTSComponent::getResult);
	handle = AzureTTSThread::setup(config, Language, Voice, Key, Region, ssml, id);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
}

USoundBase* UAzureTTSComponent::AzureTTSGetSound(FString id) {
	uint32 SAMPLING_RATE = 16000;

	SyntheticVoice = NewObject<USoundWaveProcedural>();
	SyntheticVoice->SetSampleRate(SAMPLING_RATE);
	SyntheticVoice->NumChannels = 1;
	SyntheticVoice->SoundGroup = SOUNDGROUP_Voice;
	SyntheticVoice->bLooping = true;
	SyntheticVoice->bProcedural = true;

	SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SAMPLING_RATE);
	SyntheticVoice->QueueAudio(Buffer[id].AudioData.GetData(), Buffer[id].AudioData.Num() * sizeof(int8));

	return SyntheticVoice;
}