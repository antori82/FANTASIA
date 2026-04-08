// Fill out your copyright notice in the Description page of Project Settings.

/**
 * @file AzureTTSComponent.h
 * @brief Unreal Engine actor component for Azure Cognitive Services text-to-speech synthesis.
 * @deprecated This component is deprecated and will be removed after switching to UE 5.7.
 *             Use URESTTTSComponent instead.
 */

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

/**
 * @brief Actor component that wraps Azure Cognitive Services for text-to-speech synthesis.
 *
 * Uses the Microsoft Speech SDK to perform SSML-based synthesis, with optional
 * streaming output mode. Results are buffered and broadcast on the game thread.
 *
 * @deprecated This component is deprecated and will be removed after switching
 *             to UE 5.7. Use URESTTTSComponent instead.
 * @see URESTTTSComponent, AzureTTSThread
 */
UCLASS(ClassGroup = (Azure), meta = (BlueprintSpawnableComponent, Deprecated, DeprecationMessage = "AzureTTSComponent is deprecated and will be removed after switching to UE 5.7."))
class UAzureTTSComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sets default values for this component's properties. */
	UAzureTTSComponent();

protected:
	virtual void BeginPlay() override;

private:

	// ── Private State ──────────────────────────────────────────────────

	/** Maps request IDs to their completed TTS data. */
	TMap<FString, FTTSData> Buffer;

	/** Maps request IDs to pending SSML text. */
	TMap<FString, FString> PendingSSML;

	/** Azure Speech SDK configuration handle. */
	shared_ptr<SpeechConfig> config;

	/** Worker thread performing the current synthesis operation. */
	AzureTTSThread* handle;

	FDelegateHandle TTSResultAvailableHandle;

	/**
	 * @brief Callback invoked by the worker thread when synthesis completes.
	 * @param response  The synthesized TTS data.
	 * @param id        The request identifier.
	 */
	void getResult(FTTSData response, FString id);

	FSynthesizedInternalEvent synthesisReadyInternal;

	/** ID of the most recently completed synthesis, broadcast on next tick. */
	FString idSynthesisReady = "";

public:

	// ── Public Properties ──────────────────────────────────────────────

	/** Audio component used to play back synthesized speech. */
	UPROPERTY(BlueprintReadWrite, Category = "Speech to Text")
	UAudioComponent* Speaker;

	/** Broadcast when a synthesis request completes, carrying the request ID. */
	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
	FSynthesizedEvent SynthesisReady;

	/** Language code for the Azure voice (e.g. "en-US"). */
	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString Language;

	/** Azure voice name (e.g. "AriaNeural"). */
	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString Voice;

	/** Azure Cognitive Services subscription key. */
	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString Key;

	/** Azure service region (e.g. "westeurope"). */
	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString Region;

	/** Custom endpoint ID for Azure Speech resource. */
	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString Endpoint;

	/** If true, use raw 16 kHz 16-bit mono PCM streaming output. */
	UPROPERTY(EditAnywhere, Category = "Configuration")
	bool Streaming;

	// ── Public Methods ─────────────────────────────────────────────────

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Start SSML-based speech synthesis via Azure.
	 * @param ssml  SSML text to synthesize.
	 * @param id    Unique identifier to retrieve results later.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "Azure Plugin TTS", DeprecatedFunction, DeprecationMessage = "AzureTTSComponent is deprecated and will be removed after switching to UE 5.7."), Category = "TTS")
	void TTSSynthesize(FString ssml, FString id);

	/**
	 * @brief Retrieve the synthesized audio as a USoundWave.
	 * @param id  Identifier of a completed synthesis request.
	 * @return Procedural SoundWave containing 16 kHz mono PCM audio.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "Azure Plugin TTS", DeprecatedFunction, DeprecationMessage = "AzureTTSComponent is deprecated and will be removed after switching to UE 5.7."), Category = "TTS")
	USoundWave* TTSGetSound(FString id);

	/**
	 * @brief Retrieve synthesized audio as normalized float samples.
	 * @param id  Identifier of a completed synthesis request.
	 * @return Array of float samples in [-1.0, 1.0] range.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Raw Sound", Keywords = "Azure Plugin TTS", DeprecatedFunction, DeprecationMessage = "AzureTTSComponent is deprecated and will be removed after switching to UE 5.7."), Category = "TTS")
	TArray<float> TTSGetRawSound(FString id);
};