#pragma once
//#include "Core.h"
#include "Serialization/JsonSerializer.h"
#include "FANTASIATypes.h"
#include <speechapi_cxx.h>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Intent;

DECLARE_DELEGATE_OneParam(FNLUResultAvailableDelegate, FNLUResponse);
DECLARE_EVENT_OneParam(AzureNLUThread, FNLUResultAvailableEvent, FNLUResponse);

//~~~~~ Multi Threading ~~~
class AzureNLUThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AzureNLUThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	shared_ptr<IntentRecognizer> recognizer;
	std::vector<std::shared_ptr<LanguageUnderstandingModel>> NLUModels;
	shared_ptr<SpeechConfig> NLUConfig;

	TArray<UNLUEntity*> BuildEntities(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUEntity*> entities);
	TArray<UNLUIntent*> BuildIntents(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUIntent*> intents);

	FNLUResultAvailableEvent NLUResultAvailable;

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	AzureNLUThread(shared_ptr<SpeechConfig> config, std::vector<std::shared_ptr<LanguageUnderstandingModel>> models);

	virtual ~AzureNLUThread();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	void StartOneShotRecognition();

	static AzureNLUThread* setup(shared_ptr<SpeechConfig> config, std::vector<std::shared_ptr<LanguageUnderstandingModel>> models);

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	FDelegateHandle NLUResultAvailableSubscribeUser(FNLUResultAvailableDelegate& UseDelegate);
	void NLUResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);

};