#pragma once

#include "FANTASIATypes.h"
#include "Http.h"
#include <atomic>

DECLARE_EVENT_TwoParams(RESTTTSThread, FRESTTTSResultAvailableEvent, FTTSData, FString);
DECLARE_EVENT_TwoParams(RESTTTSThread, FRESTTTSPartialResultAvailableEvent, TArray<uint8>, FString);

struct FTTSSynthesisRequest
{
	FString URL;
	TMap<FString, FString> Headers;
	FString Body;           // empty = GET request, non-empty = POST with this body
	FString ID;
	FString OriginalText;
	bool bStreaming = false;
};

class RESTTTSThread : public FRunnable
{
private:
	FThreadSafeCounter StopTaskCounter;
	FRunnableThread* Thread;

	FRESTTTSResultAvailableEvent TTSResultAvailable;
	FRESTTTSPartialResultAvailableEvent TTSPartialResultAvailable;

	FTTSSynthesisRequest PendingRequest;
	int64 StreamingNum = 0;
	int64 PreviousBytes = 0;

	std::atomic<bool> synthesize{false};
	FEventRef SynthesizeWakeEvent{EEventMode::ManualReset};

public:
	RESTTTSThread();
	virtual ~RESTTTSThread();

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	void SynthesizeLoop();
	void Synthesize(FTTSSynthesisRequest Request);
	void EnsureCompletion();

	FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate);
	void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
	FDelegateHandle TTSPartialResultAvailableSubscribeUser(FTTSPartialResultAvailableDelegate& UseDelegate);
	void TTSPartialResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};
