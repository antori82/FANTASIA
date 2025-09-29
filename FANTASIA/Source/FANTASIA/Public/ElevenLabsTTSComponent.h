#pragma once

#include "FANTASIA.h"
#include "Engine.h"
#include "CoreMinimal.h"

#include "EnableGrpcIncludes.h"
#include "Audio2FaceComponent.h"
#include "DisableGrpcIncludes.h"

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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TMap<FString, FTTSData> Buffer;
	TMap<FString, TArray<float>> StreamingBuffer;
	TMap<FString, FString> PendingSSML;
	ElevenLabsTTSThread* handle;
	FDelegateHandle TTSResultAvailableHandle;
	FDelegateHandle TTSPartialResultAvailableHandle;
	FSynthesizedInternalEvent synthesisReadyInternal;
	FString idSynthesisReady = "";
	FString idPartialSynthesisReady = "";

	void getResult(FTTSData response, FString id);
	void getPartialResult(TArray<uint8> response, FString id);


	bool usingStreamingBuffer = false;
public:

	// Sets default values for this component's properties
	UElevenLabsTTSComponent();

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	UAudio2FaceComponent* A2Fpointer;

	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
	FSynthesizedEvent SynthesisReady;

	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
	FPartialSynthesizedEvent PartialSynthesisReady;

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
	void TTSSynthesize(FString ssml, FString id, bool stream);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "ElevenLabs TTS"), Category = "TTS")
	USoundWaveProcedural* TTSGetSound(FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Raw Sound", Keywords = "ElevenLabs TTS"), Category = "TTS")
	TArray<float> TTSGetRawSound(FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Streaming Raw Sound", Keywords = "ElevenLabs TTS"), Category = "TTS")
	TArray<float> TTSGetPartialRawSound(FString id);
};