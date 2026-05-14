/**
 * @file AzureNLUThread.h
 * @brief Worker thread that performs Azure CLU intent/entity recognition off the game thread.
 * @deprecated Part of the deprecated AzureNLU pipeline. Will be removed after UE 5.7.
 */

#pragma once
//#include "Core.h"
#include "Serialization/JsonSerializer.h"
#include "FANTASIATypes.h"
#include <speechapi_cxx.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Intent;

/** Delegate type for NLU results (single FNLUResponse parameter). */
DECLARE_DELEGATE_OneParam(FNLUResultAvailableDelegate, FNLUResponse);

/** Event broadcast when an NLU result becomes available. */
DECLARE_EVENT_OneParam(AzureNLUThread, FNLUResultAvailableEvent, FNLUResponse);

/**
 * @brief Background worker thread for Azure Conversational Language Understanding.
 *
 * Runs as a singleton FRunnable. Captures microphone input via the default device,
 * performs intent recognition using the Azure Speech SDK + CLU models, parses the
 * JSON response into UNLUIntent / UNLUEntity objects, and broadcasts the result.
 *
 * @deprecated Part of the deprecated AzureNLU pipeline. Will be removed after UE 5.7.
 * @see UAzureNLUComponent
 */
class AzureNLUThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AzureNLUThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Azure Speech SDK intent recognizer instance. */
	shared_ptr<IntentRecognizer> recognizer;

	/** CLU language understanding models applied to the recognizer. */
	std::vector<std::shared_ptr<LanguageUnderstandingModel>> NLUModels;

	/** Azure Speech SDK configuration handle. */
	shared_ptr<SpeechConfig> NLUConfig;

	/**
	 * @brief Parse entity JSON array into UNLUEntity objects.
	 * @param items     JSON array of entity objects from the CLU response.
	 * @param entities  Accumulator array to append parsed entities to.
	 * @return The updated entities array.
	 */
	TArray<UNLUEntity*> BuildEntities(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUEntity*> entities);

	/**
	 * @brief Parse intent JSON array into UNLUIntent objects.
	 * @param items    JSON array of intent objects from the CLU response.
	 * @param intents  Accumulator array to append parsed intents to.
	 * @return The updated intents array.
	 */
	TArray<UNLUIntent*> BuildIntents(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUIntent*> intents);

	/** Event fired when NLU results are available. */
	FNLUResultAvailableEvent NLUResultAvailable;

public:

	// ── Thread Core Functions ──────────────────────────────────────────

	/**
	 * @brief Construct and immediately launch the worker thread.
	 * @param config  Pre-configured Azure SpeechConfig.
	 * @param models  CLU language understanding models to apply.
	 */
	AzureNLUThread(shared_ptr<SpeechConfig> config, std::vector<std::shared_ptr<LanguageUnderstandingModel>> models);

	virtual ~AzureNLUThread();

	// ── FRunnable interface ────────────────────────────────────────────
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	/** Perform a single one-shot intent recognition and broadcast the result. */
	void StartOneShotRecognition();

	/**
	 * @brief Factory method. Creates the singleton thread if multithreading is supported.
	 * @return Pointer to the running thread instance.
	 */
	static AzureNLUThread* setup(shared_ptr<SpeechConfig> config, std::vector<std::shared_ptr<LanguageUnderstandingModel>> models);

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	// ── Delegate Management ────────────────────────────────────────────

	/**
	 * @brief Subscribe a delegate to receive NLU results.
	 * @param UseDelegate  Delegate to bind.
	 * @return Handle for later unsubscription.
	 */
	FDelegateHandle NLUResultAvailableSubscribeUser(FNLUResultAvailableDelegate& UseDelegate);

	/** @brief Unsubscribe a previously registered NLU delegate. */
	void NLUResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);

};