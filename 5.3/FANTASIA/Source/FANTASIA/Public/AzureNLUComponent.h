// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "FANTASIA.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/Voice/Public/VoiceModule.h"
#include "AzureNLUThread.h"
#include "FANTASIATypes.h"
#include <iostream>
#include "Voice.h"
#include <string>
#include <speechapi_cxx.h>
#include "AzureNLUComponent.generated.h"


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;
using namespace Microsoft::CognitiveServices::Speech::Intent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingNLUEvent, FNLUResponse, NLUResponse);

UCLASS(ClassGroup = (Azure), meta = (BlueprintSpawnableComponent))
class UAzureNLUComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAzureNLUComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TSharedPtr<IVoiceCapture> VoiceCapture;
	shared_ptr<AudioConfig> audioInput;
	AzureNLUThread* handle;
	shared_ptr<SpeechConfig> config;
	std::vector<std::shared_ptr<LanguageUnderstandingModel>> models;

	FDelegateHandle NLUResultAvailableHandle;
	//bool dataSent = false;

	void getResult(FNLUResponse response);

public:

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString SpeechKey;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Region;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Language;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString LanguageKey;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Endpoint;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString projectName;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString deploymentName;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Speech Understanding")
		FIncomingNLUEvent IncomingMessage;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NLU Start", Keywords = "Azure Plugin NLU"), Category = "NLU")
		void AzureNLUStart();
};