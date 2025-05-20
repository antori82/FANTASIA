#pragma once
#include "FANTASIATypes.h"
//#include "GeneralTTSComponent.h" // fa casino


#include "EnableGrpcIncludes.h"
#include "Audio2FaceComponent.h"
#include "DisableGrpcIncludes.h"

#include "Http.h"
#include "Runtime/Json/Public/Json.h"
#include "TTSThreadInterface.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"



using namespace std;

DECLARE_EVENT_TwoParams(GeneralTTSThread, ResultAvailableEvent, FTTSData, FString);


//~~~~~ Multi Threading ~~~
class GeneralTTSThread : public FRunnable, public ITTSThreadInterface
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static GeneralTTSThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	ResultAvailableEvent TTSResultAvailable;

	FString ssml;
	FString id;
	FString Endpoint;
	UAudio2FaceComponent* A2FPointer = nullptr;

	void OnTTSPartialDataReceived(FHttpRequestPtr Request, int64 BytesSent, int64 BytesReceived);

	void HandleNonStreamingResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	int64 PreviousBytes = 0;



public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	GeneralTTSThread(FString inSsml, FString inID, FString Endpoint, UAudio2FaceComponent* A2FPointer);

	virtual ~GeneralTTSThread();

	static GeneralTTSThread* setup(FString ssml, FString id, FString Endpoint, UAudio2FaceComponent* A2F);

	

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	void Synthesize() override;

	void SynthesizeStream();

	//void SynthImplem(bool stream);



	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate) override;
	void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) override;
};