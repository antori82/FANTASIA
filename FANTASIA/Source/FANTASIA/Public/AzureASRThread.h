/**
 * @file AzureASRThread.h
 * @brief Worker thread that performs Azure Cognitive Services speech recognition off the game thread.
 * @deprecated Part of the deprecated AzureASR pipeline. Will be removed after UE 5.7.
 *             Use WhisperCaptureComponent for local ASR instead.
 * @see UWhisperCaptureComponent
 */

#pragma once
#include "Core.h"
#include "FANTASIATypes.h"
#include <speechapi_cxx.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

/** Delegate type for partial recognition results (single FString parameter). */
DECLARE_DELEGATE_OneParam(FPartialRecognitionAvailableDelegate, FString);

/** Event broadcast when a partial (intermediate) recognition result is available. */
DECLARE_EVENT_OneParam(AzureASRThread, FPartialRecognitionAvailableEvent, FString);

/** Delegate type for final recognition results (single FString parameter). */
DECLARE_DELEGATE_OneParam(FFinalRecognitionAvailableDelegate, FString);

/** Event broadcast when a final recognition result is available. */
DECLARE_EVENT_OneParam(AzureASRThread, FFinalRecognitionAvailableEvent, FString);


/**
 * @brief Background worker thread for Azure speech-to-text recognition.
 *
 * Supports one-shot and continuous recognition modes using the Microsoft
 * Speech SDK. Broadcasts partial and final recognition results through events.
 *
 * @deprecated Part of the deprecated AzureASR pipeline. Will be removed after UE 5.7.
 *             Use WhisperCaptureComponent for local ASR instead.
 * @see UAzureASRComponent, UWhisperCaptureComponent
 */
class AzureASRThread : public FRunnable
{

private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AzureASRThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Azure Speech SDK recognizer instance. */
	shared_ptr<SpeechRecognizer> recognizer;

	/** Current recognition mode (one-shot or continuous). */
	EAzureASREnum ASRMode;

	/** Azure Speech SDK configuration handle. */
	shared_ptr<SpeechConfig> ASRConfig;

	/** Start continuous recognition with event-based callbacks. */
	void StartContinuousRecognition();

	/** Request the recognizer to stop continuous recognition. */
	void StopContinuousRecognition();

	/** Perform a single one-shot recognition call. */
	void StartOneShotRecognition();

	/** Event fired for intermediate (partial) recognition results. */
	FPartialRecognitionAvailableEvent PartialRecognitionAvailable;

	/** Event fired for final recognition results. */
	FPartialRecognitionAvailableEvent FinalRecognitionAvailable;

public:

	// ── Thread Core Functions ──────────────────────────────────────────

	/**
	 * @brief Construct with explicit audio input and launch the worker thread.
	 * @param config      Pre-configured Azure SpeechConfig.
	 * @param audioInput  Audio configuration (e.g. push stream from microphone).
	 * @param Mode        One-shot or continuous recognition mode.
	 */
	AzureASRThread(shared_ptr<SpeechConfig> config, shared_ptr<AudioConfig> audioInput, EAzureASREnum Mode);

	/**
	 * @brief Construct using default microphone input and launch the worker thread.
	 * @param config  Pre-configured Azure SpeechConfig.
	 * @param Mode    One-shot or continuous recognition mode.
	 */
	AzureASRThread(shared_ptr<SpeechConfig> config, EAzureASREnum Mode);

	virtual ~AzureASRThread();

	// ── FRunnable interface ────────────────────────────────────────────
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	/**
	 * @brief Factory method with explicit audio input.
	 * @return Pointer to the running thread instance.
	 */
	static AzureASRThread* setup(shared_ptr<SpeechConfig> config, shared_ptr<AudioConfig> audioInput, EAzureASREnum Mode);

	/**
	 * @brief Factory method using default microphone input.
	 * @return Pointer to the running thread instance.
	 */
	static AzureASRThread* setup(shared_ptr<SpeechConfig> config, EAzureASREnum Mode);

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	// ── Delegate Management ────────────────────────────────────────────

	/**
	 * @brief Subscribe a delegate to receive partial recognition results.
	 * @param UseDelegate  Delegate to bind.
	 * @return Handle for later unsubscription.
	 */
	FDelegateHandle PartialRecognitionAvailableSubscribeUser(FPartialRecognitionAvailableDelegate& UseDelegate);

	/** @brief Unsubscribe a partial recognition delegate. */
	void PartialRecognitionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);

	/**
	 * @brief Subscribe a delegate to receive final recognition results.
	 * @param UseDelegate  Delegate to bind.
	 * @return Handle for later unsubscription.
	 */
	FDelegateHandle FinalRecognitionAvailableSubscribeUser(FFinalRecognitionAvailableDelegate& UseDelegate);

	/** @brief Unsubscribe a final recognition delegate. */
	void FinalRecognitionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);

};