// Fill out your copyright notice in the Description page of Project Settings.

/**
 * @file AzureASRComponent.cpp
 * @brief Implementation of UAzureASRComponent -- Azure Cognitive Services ASR actor component.
 * @deprecated This component is deprecated and will be removed after switching to UE 5.7.
 *             Use WhisperCaptureComponent for local ASR instead.
 */

#include "AzureASRComponent.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

UAzureASRComponent::UAzureASRComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	VoiceCapture = FVoiceModule::Get().CreateVoiceCapture("");
}


/** Configures Azure SpeechConfig from subscription key, region, endpoint, and language. */
void UAzureASRComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("[AzureASRComponent] This component is deprecated and will be removed after switching to UE 5.7."));

	config = SpeechConfig::FromSubscription(std::string(TCHAR_TO_UTF8(*Key)), std::string(TCHAR_TO_UTF8(*Region)));
	config->SetEndpointId(std::string(TCHAR_TO_UTF8(*Endpoint)));
	config->SetSpeechRecognitionLanguage(std::string(TCHAR_TO_UTF8(*Language)));
}

void UAzureASRComponent::getPartialRecognition(FString text)
{
	outPartialResponse = text;
	partialResponseReady = true;
}

void UAzureASRComponent::getFinalRecognition(FString text){
	handle->Shutdown();

	outResponse = text;
	responseReady = true;
}

/** Broadcasts partial and final recognition results on the game thread. */
void UAzureASRComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (partialResponseReady) {
		IncomingPartialMessage.Broadcast(outPartialResponse);
		partialResponseReady = false;
	}
	
	if (responseReady) {
		IncomingFinalMessage.Broadcast(outResponse);
		responseReady = false;
	}
}

/** Spawns an AzureASRThread in the requested mode and subscribes to its recognition events. */
void UAzureASRComponent::AzureASRStart(EAzureASREnum mode)
{
	FPartialRecognitionAvailableDelegate PartialRecognitionSubscriber;
	FFinalRecognitionAvailableDelegate FinalRecognitionSubscriber;

	PartialRecognitionSubscriber.BindUObject(this, &UAzureASRComponent::getPartialRecognition);
	FinalRecognitionSubscriber.BindUObject(this, &UAzureASRComponent::getFinalRecognition);
	handle = AzureASRThread::setup(config, audioInput, mode);
	PartialRecognitionAvailableHandle = handle->PartialRecognitionAvailableSubscribeUser(PartialRecognitionSubscriber);
	FinalRecognitionAvailableHandle = handle->FinalRecognitionAvailableSubscribeUser(FinalRecognitionSubscriber);
}

/** Shuts down the recognition thread, closes the push stream, and stops microphone capture. */
void UAzureASRComponent::AzureASRStop() {
	handle->Shutdown();
	pushStream->Close();
	VoiceCapture->Stop();
}

