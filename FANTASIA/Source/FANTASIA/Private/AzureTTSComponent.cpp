// Fill out your copyright notice in the Description page of Project Settings.

/**
 * @file AzureTTSComponent.cpp
 * @brief Implementation of UAzureTTSComponent -- Azure Cognitive Services TTS actor component.
 * @deprecated This component is deprecated and will be removed after switching to UE 5.7.
 */

#include "AzureTTSComponent.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

UAzureTTSComponent::UAzureTTSComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


/** Configures Azure SpeechConfig from subscription key, region, and endpoint. */
void UAzureTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("[AzureTTSComponent] This component is deprecated and will be removed after switching to UE 5.7."));

	config = SpeechConfig::FromSubscription(std::string(TCHAR_TO_UTF8(*Key)), std::string(TCHAR_TO_UTF8(*Region)));
	config->SetEndpointId(std::string(TCHAR_TO_UTF8(*Endpoint)));
	if (Streaming)
		config->SetSpeechSynthesisOutputFormat(SpeechSynthesisOutputFormat::Raw16Khz16BitMonoPcm);
	//config-> SpeechSynthesisLanguage = std::string(TCHAR_TO_UTF8(*Language));
}

/** Broadcasts the synthesis-ready event on the game thread when a result is pending. */
void UAzureTTSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}
}

/** Worker-thread callback: stores the result and flags it for game-thread broadcast. */
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

/** Creates a procedural SoundWave from buffered 16 kHz mono PCM data. */
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

/** Converts buffered 16-bit PCM bytes to normalized float samples in [-1.0, 1.0]. */
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
