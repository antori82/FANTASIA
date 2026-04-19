// Fill out your copyright notice in the Description page of Project Settings.

/**
 * @file AzureASRComponent.h
 * @brief Unreal Engine actor component for Azure Cognitive Services automatic speech recognition.
 * @deprecated This component is deprecated and will be removed after switching to UE 5.7.
 *             Use WhisperCaptureComponent for local ASR instead.
 * @see UWhisperCaptureComponent
 */

#pragma once

//#include "CoreMinimal.h"
#include "FANTASIA.h"
#include "Components/ActorComponent.h"
#include "Runtime/Online/Voice/Public/VoiceModule.h"
#include "AzureASRThread.h"
#include "FANTASIATypes.h"
#include <iostream>
#include "Voice.h"
#include <string>
#include <speechapi_cxx.h>
#include "AzureASRComponent.generated.h"


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

/** Delegate broadcast with intermediate (partial) recognition text. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingPartialASREvent, FString, message);

/** Delegate broadcast with the final recognition result text. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingFinalASREvent, FString, message);

/**
 * @brief Actor component that wraps Azure Cognitive Services for automatic speech recognition.
 *
 * Captures microphone input via Unreal's IVoiceCapture and streams it to Azure
 * for one-shot or continuous speech recognition. Partial and final results are
 * broadcast as Blueprint-assignable delegates on the game thread.
 *
 * @deprecated This component is deprecated and will be removed after switching
 *             to UE 5.7. Use WhisperCaptureComponent for local ASR instead.
 * @see UWhisperCaptureComponent, AzureASRThread
 */
UCLASS( ClassGroup=(Azure), meta=(BlueprintSpawnableComponent, Deprecated, DeprecationMessage = "AzureASRComponent is deprecated and will be removed after switching to UE 5.7."), config= Game)
class UAzureASRComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Sets default values for this component's properties. */
	UAzureASRComponent();

protected:
	virtual void BeginPlay() override;

private:

	// ── Private State ──────────────────────────────────────────────────

	/** Unreal voice capture interface for microphone input. */
	TSharedPtr<IVoiceCapture> VoiceCapture ;

	/** Push-based audio stream fed into the Azure recognizer. */
	shared_ptr<PushAudioInputStream> pushStream ;

	/** Audio configuration wrapping the push stream. */
	shared_ptr<AudioConfig> audioInput ;

	/** Worker thread performing the recognition operation. */
	AzureASRThread* handle;

	/** Azure Speech SDK configuration handle. */
	shared_ptr<SpeechConfig> config;

	FDelegateHandle PartialRecognitionAvailableHandle;
	FDelegateHandle FinalRecognitionAvailableHandle;

	bool dataSent = false;             /**< Whether audio data has been sent to the stream. */
	bool responseReady = false;        /**< Flag set when a final result is ready for broadcast. */
	bool partialResponseReady = false; /**< Flag set when a partial result is ready for broadcast. */
	FString outResponse;               /**< Buffered final recognition text. */
	FString outPartialResponse;        /**< Buffered partial recognition text. */

	/**
	 * @brief Callback for partial (intermediate) recognition results.
	 * @param text  Partial transcript text.
	 */
	void getPartialRecognition(FString text);

	/**
	 * @brief Callback for final recognition results.
	 * @param text  Final transcript text.
	 */
	void getFinalRecognition(FString text);

public:

	// ── Public Properties ──────────────────────────────────────────────

	/** Raw incoming voice data from the microphone capture. */
	TArray<uint8> IncomingRawVoiceData;

	/** Intermediate buffer for voice data being sent to Azure. */
	TArray<uint8> BufferedData;

	/** Azure Cognitive Services subscription key. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
		FString Key;

	/** Azure service region (e.g. "westeurope"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
		FString Region;

	/** Recognition language code (e.g. "en-US"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
		FString Language;

	/** Custom endpoint ID for the Azure Speech resource. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
		FString Endpoint;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Broadcast when a final recognition result is available. */
	UPROPERTY(BlueprintAssignable, Category = "Speech Recognition")
		FIncomingFinalASREvent IncomingFinalMessage;

	/** Broadcast when a partial (intermediate) recognition result is available. */
	UPROPERTY(BlueprintAssignable, Category = "Speech Recognition")
		FIncomingPartialASREvent IncomingPartialMessage;

	// ── Public Methods ─────────────────────────────────────────────────

	/**
	 * @brief Start speech recognition in the specified mode.
	 * @param mode  One-shot or continuous recognition mode.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ASR Start", Keywords = "AzureASRPlugin ASR", DeprecatedFunction, DeprecationMessage = "AzureASRComponent is deprecated and will be removed after switching to UE 5.7."), Category = "ASR")
	void AzureASRStart(EAzureASREnum mode = EAzureASREnum::ASR_ONESHOT);

	/**
	 * @brief Stop an ongoing continuous recognition session.
	 * @note Closes the push stream and stops microphone capture.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "ASR Stop", Keywords = "AzureASRPlugin ASR", DeprecatedFunction, DeprecationMessage = "AzureASRComponent is deprecated and will be removed after switching to UE 5.7."), Category = "ASR")
	void AzureASRStop();
};