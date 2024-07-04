#pragma once
#include "FANTASIATypes.h"
#include "Http.h"
#include "Runtime/Json/Public/Json.h"
#include "TTSThreadInterface.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"


using namespace std;

DECLARE_EVENT_TwoParams(ElevenLabsTTSThread, FElevenLabsTTSResultAvailableEvent, FTTSData, FString);

//~~~~~ Multi Threading ~~~
class ElevenLabsTTSThread : public FRunnable, public ITTSThreadInterface
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static ElevenLabsTTSThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	FElevenLabsTTSResultAvailableEvent TTSResultAvailable;

	FString text;
	FString id;
	FString voiceID;
	FString modelID;
	FString key;
	FString Endpoint;

	float stability;
	float similarity_boost;
	float style;
	float use_speaker_boost;


public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	ElevenLabsTTSThread(FString inKey, FString inText, FString inID, FString inVoiceID, FString inModelID, float inStability, float inSimilarity_boost, float inStyle, bool inUse_speaker_boost);

	virtual ~ElevenLabsTTSThread();

	static ElevenLabsTTSThread* setup(FString key, FString text, FString inID, FString voiceID, FString modelID, float stability, float similarity_boost, float style, bool use_speaker_boost);

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	void Synthesize() override;

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate) override;
	void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) override;
};