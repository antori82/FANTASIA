/**
 * @file AzureTTSThread.h
 * @brief Worker thread that performs Azure Cognitive Services speech synthesis off the game thread.
 * @deprecated Part of the deprecated AzureTTS pipeline. Will be removed after UE 5.7.
 */

#pragma once
//#include "Core.h"
#include "FANTASIATypes.h"
#include <speechapi_cxx.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

/** Event broadcast when an Azure TTS result becomes available. */
DECLARE_EVENT_TwoParams(AzureTTSThread, FAzureResultAvailableEvent, FTTSData, FString);

/**
 * @brief Background worker thread that calls the Azure Speech SDK for TTS synthesis.
 *
 * Runs as a singleton FRunnable. Wraps the input text in an SSML envelope with the
 * configured voice/language, calls SpeakSsmlAsync, and broadcasts the resulting
 * PCM audio through FAzureResultAvailableEvent.
 *
 * @deprecated Part of the deprecated AzureTTS pipeline. Will be removed after UE 5.7.
 * @see UAzureTTSComponent
 */
class AzureTTSThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AzureTTSThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Event fired when synthesis completes with audio data and request ID. */
	FAzureResultAvailableEvent TTSResultAvailable;

	// ── Azure SDK Handles ──────────────────────────────────────────────

	/** Shared Speech SDK configuration (subscription key, region, endpoint). */
	shared_ptr<SpeechConfig> TTSConfig;

	/** Speech synthesizer created from TTSConfig for the current request. */
	shared_ptr<SpeechSynthesizer> synthesizer;

	// ── Synthesis Parameters ───────────────────────────────────────────

	FString Language;  /**< Language code (e.g. "en-US"). */
	FString Voice;     /**< Voice name (e.g. "AriaNeural"). */
	FString Key;       /**< Azure subscription key. */
	FString Region;    /**< Azure service region. */
	FString ssml;      /**< SSML text to synthesize. */
	FString id;        /**< Caller-assigned request identifier. */

public:

	// ── Thread Core Functions ──────────────────────────────────────────

	/**
	 * @brief Construct and immediately launch the worker thread.
	 * @param config      Pre-configured Azure SpeechConfig.
	 * @param inLanguage  Language code.
	 * @param inVoice     Voice name.
	 * @param inKey       Azure subscription key.
	 * @param inRegion    Azure region.
	 * @param inSsml      SSML content to synthesize.
	 * @param inID        Caller-assigned request identifier.
	 */
	AzureTTSThread(shared_ptr<SpeechConfig> config, FString inLanguage, FString inVoice, FString inKey, FString inRegion, FString inSsml, FString inID);

	virtual ~AzureTTSThread();

	/**
	 * @brief Factory method. Creates the singleton thread if multithreading is supported.
	 * @return Pointer to the running thread instance, or nullptr.
	 */
	static AzureTTSThread* setup(shared_ptr<SpeechConfig> config, FString Language, FString Voice, FString Key, FString Region, FString ssml, FString id);

	// ── FRunnable interface ────────────────────────────────────────────
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	/** Perform the Azure SSML synthesis call and broadcast results. */
	void Synthesize();

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	// ── Delegate Management ────────────────────────────────────────────

	/**
	 * @brief Subscribe a delegate to receive synthesis results.
	 * @param UseDelegate  Delegate to bind.
	 * @return Handle that can be used to unsubscribe later.
	 */
	FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate);

	/**
	 * @brief Unsubscribe a previously registered delegate.
	 * @param DelegateHandle  Handle returned by TTSResultAvailableSubscribeUser.
	 */
	void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};