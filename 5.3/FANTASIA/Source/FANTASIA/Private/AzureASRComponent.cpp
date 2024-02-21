// Fill out your copyright notice in the Description page of Project Settings.


#include "AzureASRComponent.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

// Sets default values for this component's properties
UAzureASRComponent::UAzureASRComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	VoiceCapture = FVoiceModule::Get().CreateVoiceCapture("");
}


// Called when the game starts
void UAzureASRComponent::BeginPlay()
{
	Super::BeginPlay();

	config = SpeechConfig::FromSubscription(std::string(TCHAR_TO_UTF8(*Key)), std::string(TCHAR_TO_UTF8(*Region)));
	config->SetEndpointId(std::string(TCHAR_TO_UTF8(*Endpoint)));
	config->SetSpeechRecognitionLanguage(std::string(TCHAR_TO_UTF8(*Language)));
}

void UAzureASRComponent::getPartialRecognition(FString text)
{
	IncomingMessage.Broadcast(text);
	handle->Shutdown();
	//AzureASRThread::Shutdown();
}

// Called every frame
void UAzureASRComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAzureASRComponent::AzureASRStart()
{
	FPartialRecognitionAvailableDelegate PartialRecognitionSubscriber;
	PartialRecognitionSubscriber.BindUObject(this, &UAzureASRComponent::getPartialRecognition);
	handle = AzureASRThread::setup(config, audioInput, EAzureASREnum::ASR_ONESHOT);
	PartialRecognitionAvailableHandle = handle->PartialRecognitionAvailableSubscribeUser(PartialRecognitionSubscriber);
}

void UAzureASRComponent::AzureASRStop() {
	handle->Shutdown();
	pushStream->Close();
	VoiceCapture->Stop();
}

