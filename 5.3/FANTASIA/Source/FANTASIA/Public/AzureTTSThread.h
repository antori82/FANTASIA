#pragma once
//#include "Core.h"
#include "FANTASIATypes.h"
#include <speechapi_cxx.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

DECLARE_EVENT_TwoParams(AzureTTSThread, FAzureResultAvailableEvent, FTTSData, FString);

//~~~~~ Multi Threading ~~~
class AzureTTSThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AzureTTSThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	FAzureResultAvailableEvent TTSResultAvailable;

	shared_ptr<SpeechConfig> TTSConfig;
	shared_ptr<SpeechSynthesizer> synthesizer;

	FString Language;
	FString Voice;
	FString Key;
	FString Region;
	FString ssml;
	FString id;

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	AzureTTSThread(shared_ptr<SpeechConfig> config, FString inLanguage, FString inVoice, FString inKey, FString inRegion, FString inSsml, FString inID);

	virtual ~AzureTTSThread();

	static AzureTTSThread* setup(shared_ptr<SpeechConfig> config, FString Language, FString Voice, FString Key, FString Region, FString ssml, FString id);

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	void Synthesize();

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate);
	void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};