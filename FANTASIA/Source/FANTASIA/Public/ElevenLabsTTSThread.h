#pragma once
#include "FANTASIATypes.h"
#include "Http.h"
#include "Runtime/Json/Public/Json.h"
#include "TTSThreadInterface.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include <atomic>

DECLARE_EVENT_TwoParams(ElevenLabsTTSThread, FElevenLabsTTSResultAvailableEvent, FTTSData, FString);
DECLARE_EVENT_TwoParams(ElevenLabsTTSThread, FElevenLabsTTSPartialResultAvailableEvent, TArray<uint8>, FString);

//~~~~~ Multi Threading ~~~
class ElevenLabsTTSThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static ElevenLabsTTSThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	FElevenLabsTTSResultAvailableEvent TTSResultAvailable;
	FElevenLabsTTSPartialResultAvailableEvent TTSPartialResultAvailable;

	FString text;
	FString id;
	FString voiceID;
	FString modelID;
	FString key;

	// [FIX] Changed from int32 to int64 to handle responses > 2 GB correctly,
	// and to match the int64 BytesReceived parameter in OnRequestProgress64.
	int64 StreamingNum = 0;

	float stability;
	float similarity_boost;
	float style;
	float use_speaker_boost;

	// [FIX] Changed from int to int64 to match the OnRequestProgress64 signature.
	int64 PreviousBytes = 0;

	bool isStreaming;

	// [FIX] Was a plain bool read by the SynthesizeLoop thread and written by the game thread
	// calling Synthesize() — a data race. Now atomic.
	std::atomic<bool> synthesize{false};

	// [OPT] Event-driven wake replaces the CPU-burning spin loop in SynthesizeLoop.
	FEventRef SynthesizeWakeEvent{EEventMode::ManualReset};

public:

	//~~~ Thread Core Functions ~~~

	ElevenLabsTTSThread(FString inKey, FString inVoiceID, FString inModelID, float inStability, float inSimilarity_boost, float inStyle, bool inUse_speaker_boost, bool stream);

	virtual ~ElevenLabsTTSThread();

	static ElevenLabsTTSThread* setup(FString key, FString voiceID, FString modelID, float stability, float similarity_boost, float style, bool use_speaker_boost, bool stream);

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	void SynthesizeLoop();
	void Synthesize(FString text, FString inID);

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate);
	void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
	FDelegateHandle TTSPartialResultAvailableSubscribeUser(FTTSPartialResultAvailableDelegate& UseDelegate);
	void TTSPartialResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};
