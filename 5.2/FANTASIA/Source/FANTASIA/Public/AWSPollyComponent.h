// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FANTASIA.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "AWSPollyThread.h"
#include <iostream>
#include <string>
#include "AWSPollyComponent.generated.h"

//using namespace std;

UCLASS(ClassGroup = (AmazonWebServices), meta = (BlueprintSpawnableComponent))
class UAWSPollyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAWSPollyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TMap<FString, FTTSData> Buffer;
	TMap<FString, FString> PendingSSML;
	AWSPollyThread* handle;
	FTimerHandle TimerHandle;
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
		FString Voice;
		
	UPROPERTY(EditAnywhere, Category = "Configuration")
		TTSVoiceType voiceType;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString AccessKey;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString SecretAccessKey;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "AWS Plugin TTS"), Category = "TTS")
		void AWSPollySynthesize(FString ssml, FString id, bool getLipSync);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "AWS Plugin TTS"), Category = "TTS")
		USoundWave* AWSPollyGetSound(FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get LipSync", Keywords = "AWS Plugin TTS"), Category = "TTS")
		TArray<FTTSTimedStruct> AWSPollyGetLipSync(FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Notifies", Keywords = "AWS Plugin TTS"), Category = "TTS")
		TArray<FTTSTimedStruct> AWSPollyGetNotifies(FString id);
};