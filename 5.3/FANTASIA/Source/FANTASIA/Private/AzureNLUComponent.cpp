// Fill out your copyright notice in the Description page of Project Settings.


#include "AzureNLUComponent.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

// Sets default values for this component's properties
UAzureNLUComponent::UAzureNLUComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bRunOnAnyThread = false;

	VoiceCapture = FVoiceModule::Get().CreateVoiceCapture("");
}


// Called when the game starts
void UAzureNLUComponent::BeginPlay()
{
	Super::BeginPlay();

	config = SpeechConfig::FromSubscription(std::string(TCHAR_TO_UTF8(*Key)), std::string(TCHAR_TO_UTF8(*Region)));
	config->SetSpeechRecognitionLanguage(std::string(TCHAR_TO_UTF8(*Language)));
	model = LanguageUnderstandingModel::FromAppId(TCHAR_TO_UTF8(*AppID));
}

void UAzureNLUComponent::getResult(FNLUResponse response)
{
	//IncomingMessage.Broadcast(response);
	handle->NLUResultAvailableUnsubscribeUser(NLUResultAvailableHandle);
	handle->Shutdown();

	outResponse = response;
	responseReady = true;
}

// Called every frame
void UAzureNLUComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (responseReady) {
		IncomingMessage.Broadcast(outResponse);
		responseReady = false;
	}
}

void UAzureNLUComponent::AzureNLUStart()
{
	FNLUResultAvailableDelegate NLUResultSubscriber;
	NLUResultSubscriber.BindUObject(this, &UAzureNLUComponent::getResult);
	handle = AzureNLUThread::setup(config, model);
	NLUResultAvailableHandle = handle->NLUResultAvailableSubscribeUser(NLUResultSubscriber);
}
