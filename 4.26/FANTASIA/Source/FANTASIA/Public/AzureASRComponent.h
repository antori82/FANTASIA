// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "FANTASIA.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/Voice/Public/VoiceModule.h"
#include "AzureASRThread.h"
#include <iostream>
#include "Voice.h"
#include <string>
#include <speechapi_cxx.h>
#include "AzureASRComponent.generated.h"


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingASREvent, FString, message);

UCLASS( ClassGroup=(Azure), meta=(BlueprintSpawnableComponent) )
class UAzureASRComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAzureASRComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TSharedPtr<IVoiceCapture> VoiceCapture ;
	shared_ptr<PushAudioInputStream> pushStream ;
	shared_ptr<AudioConfig> audioInput ;
	AzureASRThread* handle;
	shared_ptr<SpeechConfig> config;
	FDelegateHandle PartialRecognitionAvailableHandle;
	bool dataSent = false;

	void getPartialRecognition(FString text);

public:	

	TArray<uint8> IncomingRawVoiceData;
	TArray<uint8> BufferedData;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Key;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Region;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Language;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, Category = "Speech Recognition")
		FIncomingASREvent IncomingMessage;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ASR Start", Keywords = "AzureASRPlugin ASR"), Category = "ASR")
		void AzureASRStart();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ASR Stop", Keywords = "AzureASRPlugin ASR"), Category = "ASR")
		void AzureASRStop();
};