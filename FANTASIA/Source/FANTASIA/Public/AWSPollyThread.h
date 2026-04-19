/**
 * @file AWSPollyThread.h
 * @brief Worker thread that performs Amazon Polly speech synthesis off the game thread.
 * @deprecated Part of the deprecated AWSPolly pipeline. Will be removed after UE 5.7.
 */

#pragma once
//#include "Core.h"
#define USE_IMPORT_EXPORT
#define USE_WINDOWS_DLL_SEMANTICS

#include "FANTASIATypes.h"
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/polly/PollyClient.h>
#include <aws/core/utils/Outcome.h>
#include <aws/polly/model/SynthesizeSpeechRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"

//using namespace std;

/** Event broadcast when an AWS Polly TTS result becomes available. */
DECLARE_EVENT_TwoParams(AWSPollyThread, FAWSPollyResultAvailableEvent, FTTSData, FString);

/**
 * @brief Background worker thread that calls the Amazon Polly API for speech synthesis.
 *
 * Runs as a singleton FRunnable. On completion it broadcasts the synthesized audio
 * (and optional viseme/mark data) through FAWSPollyResultAvailableEvent.
 *
 * @deprecated Part of the deprecated AWSPolly pipeline. Will be removed after UE 5.7.
 * @see UAWSPollyComponent
 */
class AWSPollyThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AWSPollyThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Event fired when synthesis completes with audio data and request ID. */
	FAWSPollyResultAvailableEvent TTSResultAvailable;

	// ── Synthesis Parameters ───────────────────────────────────────────

	TTSVoiceType voiceType;   /**< Standard or Neural voice selection. */
	FString Voice;            /**< Polly voice name (e.g. "Joanna"). */
	FString AccessKey;        /**< AWS access key ID. */
	FString SecretAccessKey;  /**< AWS secret access key. */
	FString Region;           /**< AWS region. */
	FString ssml;             /**< SSML text to synthesize. */
	FString id;               /**< Caller-assigned request identifier. */
	bool lipSync;             /**< Whether to request viseme data. */

public:

	// ── Thread Core Functions ──────────────────────────────────────────

	/**
	 * @brief Construct and immediately launch the worker thread.
	 * @param inVoiceType    Standard or Neural voice type.
	 * @param inVoice        Polly voice name.
	 * @param accessKey      AWS access key ID.
	 * @param secretAccessKey AWS secret access key.
	 * @param inSsml         SSML content to synthesize.
	 * @param inID           Caller-assigned request identifier.
	 * @param getLipSync     Whether to also request viseme speech marks.
	 */
	AWSPollyThread(TTSVoiceType inVoiceType, FString inVoice, FString accessKey, FString secretAccessKey, FString inSsml, FString inID, bool getLipSync);

	virtual ~AWSPollyThread();

	/**
	 * @brief Factory method. Creates the singleton thread if multithreading is supported.
	 * @return Pointer to the running thread instance, or nullptr.
	 */
	static AWSPollyThread* setup(TTSVoiceType inVoiceType, FString Voice, FString accessKey, FString secretAccessKey, FString ssml, FString id, bool getLipSync);

	// ── FRunnable interface ────────────────────────────────────────────
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	/** Perform the Polly synthesis call and broadcast results. */
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