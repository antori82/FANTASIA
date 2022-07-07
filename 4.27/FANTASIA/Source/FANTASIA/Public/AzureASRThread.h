#pragma once
#include "Core.h"
#include <speechapi_cxx.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

DECLARE_DELEGATE_OneParam(FPartialRecognitionAvailableDelegate, FString);
DECLARE_EVENT_OneParam(AzureASRThread, FPartialRecognitionAvailableEvent, FString);

enum class EAzureASREnum : uint8
{
	ASR_CONTINUOUS,
	ASR_ONESHOT
};

//~~~~~ Multi Threading ~~~
class AzureASRThread : public FRunnable
{

private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AzureASRThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	shared_ptr<SpeechRecognizer> recognizer;
	EAzureASREnum ASRMode;
	shared_ptr<SpeechConfig> ASRConfig;

	void StartContinuousRecognition();
	void StopContinuousRecognition();

	void StartOneShotRecognition();

	FPartialRecognitionAvailableEvent PartialRecognitionAvailable;

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	AzureASRThread(shared_ptr<SpeechConfig> config, shared_ptr<AudioConfig> audioInput, EAzureASREnum Mode);
	AzureASRThread(shared_ptr<SpeechConfig> config, EAzureASREnum Mode);

	virtual ~AzureASRThread();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	static AzureASRThread* setup(shared_ptr<SpeechConfig> config, shared_ptr<AudioConfig> audioInput, EAzureASREnum Mode);
	static AzureASRThread* setup(shared_ptr<SpeechConfig> config, EAzureASREnum Mode);

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	FDelegateHandle PartialRecognitionAvailableSubscribeUser(FPartialRecognitionAvailableDelegate& UseDelegate);
	void PartialRecognitionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);

};