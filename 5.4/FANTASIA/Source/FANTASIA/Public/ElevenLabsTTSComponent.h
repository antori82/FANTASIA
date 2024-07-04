#pragma once

#include "FANTASIA.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "ElevenLabsTTSThread.h"
#include <iostream>
#include <string>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include "ElevenLabsTTSComponent.generated.h"

using namespace std;

UCLASS(meta = (BlueprintSpawnableComponent))
class UElevenLabsTTSComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UElevenLabsTTSComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TMap<FString, FTTSData> Buffer;
	TMap<FString, FString> PendingSSML;
	ElevenLabsTTSThread* handle;

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
	FString VoiceID;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString ModelID;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString Key;

	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float stability;

	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float similarity_boost;

	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float style;

	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	bool use_speaker_boost;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "ElevenLabs TTS"), Category = "TTS")
	void TTSSynthesize(FString ssml, FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "ElevenLabs TTS"), Category = "TTS")
	USoundWave* TTSGetSound(FString id);
};