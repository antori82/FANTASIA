// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FANTASIA.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "AzureTTSThread.h"
#include <speechapi_cxx.h>
#include <iostream>
#include <string>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include "AzureTTSComponent.generated.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

UCLASS(ClassGroup = (Azure), meta = (BlueprintSpawnableComponent))
class UAzureTTSComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAzureTTSComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TMap<FString, FTTSData> Buffer;
	TMap<FString, FString> PendingSSML;
	shared_ptr<SpeechConfig> config;
	AzureTTSThread* handle;
	
	FDelegateHandle TTSResultAvailableHandle;

	void getResult(FTTSData response, FString id);

	FSynthesizedInternalEvent synthesisReadyInternal;

	FString idSynthesisReady = "";

public:

	UPROPERTY(BlueprintReadWrite, Category = "Speech to Text")
		UAudioComponent* Speaker;

	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
		FSynthesizedEvent SynthesisReady;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Language;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Voice;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Key;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Region;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "Azure Plugin TTS"), Category = "TTS")
		void AzureTTSSynthesize(FString ssml, FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "Azure Plugin TTS"), Category = "TTS")
		USoundBase* AzureTTSGetSound(FString id);
};