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
	config->SetEndpointId(std::string(TCHAR_TO_UTF8(*Endpoint)));
	if (Streaming)
		config->SetSpeechSynthesisOutputFormat(SpeechSynthesisOutputFormat::Raw16Khz16BitMonoPcm);
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

	Buffer.Remove(id);
	Buffer.Add(id, response);
	idSynthesisReady = id;
}

void UAzureTTSComponent::TTSSynthesize(FString ssml, FString id)
{
	FTTSResultAvailableDelegate TTSResultSubscriber;
	TTSResultSubscriber.BindUObject(this, &UAzureTTSComponent::getResult);
	handle = AzureTTSThread::setup(config, Language, Voice, Key, Region, ssml, id);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
}

USoundWave* UAzureTTSComponent::TTSGetSound(FString id) {
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

TArray<float> UAzureTTSComponent::TTSGetRawSound(FString id) {
	TArray<float> AudioData;

	for (int i = 0; i < Buffer[id].AudioData.Num() * sizeof(uint8); i += 2) {
	    float NormalizedSample = 0.0f;
	    int16 Sample = *reinterpret_cast<int16*>(&Buffer[id].AudioData.GetData()[i]);
	    NormalizedSample = Sample / 32768.0f;

	    AudioData.Add(NormalizedSample);
	}
	return AudioData;
}
