// Fill out your copyright notice in the Description page of Project Settings.

/**
 * @file AzureNLUComponent.h
 * @brief Unreal Engine actor component for Azure Conversational Language Understanding (CLU).
 * @deprecated This component is deprecated and will be removed after switching to UE 5.7.
 */

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

/** Delegate broadcast when an NLU response (intents + entities) is available. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingNLUEvent, FNLUResponse, NLUResponse);

/**
 * @brief Actor component that wraps Azure Conversational Language Understanding (CLU).
 *
 * Captures microphone input, performs speech recognition via Azure, and forwards
 * the transcript to CLU for intent/entity extraction. Results are broadcast as a
 * Blueprint-assignable delegate on the game thread.
 *
 * @deprecated This component is deprecated and will be removed after switching
 *             to UE 5.7.
 * @see AzureNLUThread
 */
UCLASS(ClassGroup = (Azure), meta = (BlueprintSpawnableComponent, Deprecated, DeprecationMessage = "AzureNLUComponent is deprecated and will be removed after switching to UE 5.7."), config = Game)
class UAzureNLUComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sets default values for this component's properties. */
	UAzureNLUComponent();

protected:
	virtual void BeginPlay() override;

private:

	// ── Private State ──────────────────────────────────────────────────

	/** Unreal voice capture interface for microphone input. */
	TSharedPtr<IVoiceCapture> VoiceCapture;

	/** Audio configuration for the Azure recognizer. */
	shared_ptr<AudioConfig> audioInput;

	/** Worker thread performing the NLU operation. */
	AzureNLUThread* handle;

	/** Azure Speech SDK configuration handle. */
	shared_ptr<SpeechConfig> config;

	/** CLU language understanding models registered during BeginPlay. */
	std::vector<std::shared_ptr<LanguageUnderstandingModel>> models;

	FDelegateHandle NLUResultAvailableHandle;

	bool responseReady = false;  /**< Flag set when a result is ready for broadcast. */
	FNLUResponse outResponse;    /**< Buffered NLU response for game-thread broadcast. */

	/**
	 * @brief Callback invoked by the worker thread when NLU completes.
	 * @param response  The parsed NLU response with intents and entities.
	 */
	void getResult(FNLUResponse response);

	/**
	 * @brief Validate that all required configuration fields are non-empty.
	 * @return True if the configuration is valid.
	 */
	bool checkConfigIsValid();

public:

	// ── Public Properties ──────────────────────────────────────────────

	/** Azure Cognitive Services Speech subscription key. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString SpeechKey;

	/** Azure service region (e.g. "westeurope"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Region;

	/** Recognition language code (e.g. "en-US"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Language;

	/** Azure Language resource key for CLU. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString LanguageKey;

	/** Azure Language resource endpoint URL. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Endpoint;

	/** CLU project name. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString ProjectName;

	/** CLU deployment name. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString DeploymentName;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Broadcast when an NLU result (intents + entities) is available. */
	UPROPERTY(BlueprintAssignable, Category = "Speech Understanding")
	FIncomingNLUEvent IncomingMessage;

	// ── Public Methods ─────────────────────────────────────────────────

	/**
	 * @brief Start a one-shot NLU recognition from the default microphone.
	 * @note Validates configuration before starting. Logs errors if fields are empty.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NLU Start", Keywords = "Azure Plugin NLU", DeprecatedFunction, DeprecationMessage = "AzureNLUComponent is deprecated and will be removed after switching to UE 5.7."), Category = "NLU")
	void AzureNLUStart();
};