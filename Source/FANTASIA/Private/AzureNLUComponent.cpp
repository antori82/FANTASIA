// Fill out your copyright notice in the Description page of Project Settings.


#include "AzureNLUComponent.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

// Sets default values for this component's properties
UAzureNLUComponent::UAzureNLUComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	VoiceCapture = FVoiceModule::Get().CreateVoiceCapture("");
}


// Called when the game starts
void UAzureNLUComponent::BeginPlay()
{
	Super::BeginPlay();

	config = SpeechConfig::FromSubscription(std::string(TCHAR_TO_UTF8(*SpeechKey)), std::string(TCHAR_TO_UTF8(*Region)));
	config->SetSpeechRecognitionLanguage(std::string(TCHAR_TO_UTF8(*Language)));


	auto cluModel = ConversationalLanguageUnderstandingModel::FromResource(
		std::string(TCHAR_TO_UTF8(*LanguageKey)),
		std::string(TCHAR_TO_UTF8(*Endpoint)),
		std::string(TCHAR_TO_UTF8(*projectName)),
		std::string(TCHAR_TO_UTF8(*deploymentName)));

	models.push_back(cluModel);
	
}

void UAzureNLUComponent::getResult(FNLUResponse response)
{
	handle->NLUResultAvailableUnsubscribeUser(NLUResultAvailableHandle);
	handle->Shutdown();
	//IncomingMessage.Broadcast(response);

	outResponse = response;
	responseReady = true;
}

// Called every frame
void UAzureNLUComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (responseReady) {
		responseReady = false;
		IncomingMessage.Broadcast(outResponse);
	}
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAzureNLUComponent::AzureNLUStart()
{
	FNLUResultAvailableDelegate NLUResultSubscriber;
	NLUResultSubscriber.BindUObject(this, &UAzureNLUComponent::getResult);
	handle = AzureNLUThread::setup(config, models);
	NLUResultAvailableHandle = handle->NLUResultAvailableSubscribeUser(NLUResultSubscriber);
}
