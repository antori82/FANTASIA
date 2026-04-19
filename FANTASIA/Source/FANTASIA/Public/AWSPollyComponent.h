// Fill out your copyright notice in the Description page of Project Settings.

/**
 * @file AWSPollyComponent.h
 * @brief Unreal Engine actor component for Amazon Polly text-to-speech synthesis.
 * @deprecated This component is deprecated and will be removed after switching to UE 5.7.
 *             Use URESTTTSComponent instead.
 */

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

/**
 * @brief Actor component that wraps Amazon Polly for text-to-speech synthesis.
 *
 * Provides Blueprint-callable functions for SSML-based speech synthesis,
 * sound retrieval, lip-sync viseme extraction, and SSML mark notifies.
 *
 * @deprecated This component is deprecated and will be removed after switching
 *             to UE 5.7. Use URESTTTSComponent instead.
 * @see URESTTTSComponent
 */
UCLASS(ClassGroup = (AmazonWebServices), meta = (BlueprintSpawnableComponent, Deprecated, DeprecationMessage = "AWSPollyComponent is deprecated and will be removed after switching to UE 5.7."), config = Game)
class UAWSPollyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sets default values for this component's properties. */
	UAWSPollyComponent();

	// ── Public Properties ──────────────────────────────────────────────

	/** Audio component used to play back synthesized speech. */
	UPROPERTY(BlueprintReadWrite, Category = "Speech to Text")
	UAudioComponent* Speaker;

	/** Broadcast when a synthesis request completes, carrying the request ID. */
	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
	FSynthesizedEvent SynthesisReady;

	/** Name of the Amazon Polly voice to use (e.g. "Joanna", "Matthew"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Voice;

	/** Whether to use a Standard or Neural voice type. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	TTSVoiceType voiceType;

	/** AWS access key ID for authenticating with the Polly service. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString AccessKey;

	/** AWS secret access key for authenticating with the Polly service. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString SecretAccessKey;

	// ── Public Methods ─────────────────────────────────────────────────

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Start an SSML-based speech synthesis request.
	 * @param ssml  SSML text to synthesize (automatically wrapped in <speak> tags).
	 * @param id    Unique identifier used to retrieve the result later.
	 * @param getLipSync  If true, also requests viseme and SSML mark data.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "AWS Plugin TTS", DeprecatedFunction, DeprecationMessage = "AWSPollyComponent is deprecated and will be removed after switching to UE 5.7."), Category = "TTS")
	void AWSPollySynthesize(FString ssml, FString id, bool getLipSync);

	/**
	 * @brief Retrieve the synthesized audio as a USoundWave.
	 * @param id  Identifier of a completed synthesis request.
	 * @return A procedural SoundWave containing 16 kHz mono PCM audio.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "AWS Plugin TTS", DeprecatedFunction, DeprecationMessage = "AWSPollyComponent is deprecated and will be removed after switching to UE 5.7."), Category = "TTS")
	USoundWave* AWSPollyGetSound(FString id);

	/**
	 * @brief Retrieve viseme lip-sync data for a completed synthesis.
	 * @param id  Identifier of a completed synthesis request.
	 * @return Array of timed viseme entries.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get LipSync", Keywords = "AWS Plugin TTS", DeprecatedFunction, DeprecationMessage = "AWSPollyComponent is deprecated and will be removed after switching to UE 5.7."), Category = "TTS")
	TArray<FTTSTimedStruct> AWSPollyGetLipSync(FString id);

	/**
	 * @brief Retrieve SSML mark notifies for a completed synthesis.
	 * @param id  Identifier of a completed synthesis request.
	 * @return Array of timed SSML mark entries.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Notifies", Keywords = "AWS Plugin TTS", DeprecatedFunction, DeprecationMessage = "AWSPollyComponent is deprecated and will be removed after switching to UE 5.7."), Category = "TTS")
	TArray<FTTSTimedStruct> AWSPollyGetNotifies(FString id);

	/**
	 * @brief Retrieve synthesized audio as normalized float samples.
	 * @param id  Identifier of a completed synthesis request.
	 * @return Array of float samples in [-1.0, 1.0] range.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Raw Sound", Keywords = "Azure Plugin TTS", DeprecatedFunction, DeprecationMessage = "AWSPollyComponent is deprecated and will be removed after switching to UE 5.7."), Category = "TTS")
	TArray<float> TTSGetRawSound(FString id);

protected:
	virtual void BeginPlay() override;

private:

	// ── Private State ──────────────────────────────────────────────────

	/** Maps request IDs to their completed TTS data (audio + metadata). */
	TMap<FString, FTTSData> Buffer;

	/** Maps request IDs to pending SSML text awaiting synthesis. */
	TMap<FString, FString> PendingSSML;

	/** Worker thread handle for the current synthesis operation. */
	AWSPollyThread* handle;

	FTimerHandle TimerHandle;
	FDelegateHandle TTSResultAvailableHandle;
	FSynthesizedInternalEvent synthesisReadyInternal;

	/** ID of the most recently completed synthesis, broadcast on next tick. */
	FString idSynthesisReady = "";

	/**
	 * @brief Callback invoked by the worker thread when synthesis completes.
	 * @param response  The synthesized TTS data.
	 * @param id        The request identifier.
	 */
	void getResult(FTTSData response, FString id);
};