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

DECLARE_EVENT_TwoParams(AWSPollyThread, FAWSPollyResultAvailableEvent, FTTSData, FString);

//~~~~~ Multi Threading ~~~
class AWSPollyThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AWSPollyThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	FAWSPollyResultAvailableEvent TTSResultAvailable;

	TTSVoiceType voiceType;
	FString Voice;
	FString AccessKey;
	FString SecretAccessKey;
	FString Region;
	FString ssml;
	FString id;
	bool lipSync;

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	AWSPollyThread(TTSVoiceType inVoiceType, FString inVoice, FString accessKey, FString secretAccessKey, FString inSsml, FString inID, bool getLipSync);

	virtual ~AWSPollyThread();

	static AWSPollyThread* setup(TTSVoiceType inVoiceType, FString Voice, FString accessKey, FString secretAccessKey, FString ssml, FString id, bool getLipSync);

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