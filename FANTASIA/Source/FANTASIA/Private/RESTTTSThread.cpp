#include "RESTTTSThread.h"

RESTTTSThread::RESTTTSThread()
	: StopTaskCounter(0)
{
	Thread = FRunnableThread::Create(this, TEXT("RESTTTSThread"), 0, TPri_Normal);
}

RESTTTSThread::~RESTTTSThread()
{
	delete Thread;
	Thread = nullptr;
}

bool RESTTTSThread::Init()
{
	return true;
}

uint32 RESTTTSThread::Run()
{
	SynthesizeLoop();
	return 0;
}

void RESTTTSThread::Stop()
{
	StopTaskCounter.Increment();
	SynthesizeWakeEvent->Trigger();
}

void RESTTTSThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void RESTTTSThread::Synthesize(FTTSSynthesisRequest Request)
{
	PendingRequest = MoveTemp(Request);
	synthesize.store(true, std::memory_order_release);
	SynthesizeWakeEvent->Trigger();
}

void RESTTTSThread::SynthesizeLoop()
{
	while (StopTaskCounter.GetValue() == 0)
	{
		SynthesizeWakeEvent->Wait();
		SynthesizeWakeEvent->Reset();

		if (StopTaskCounter.GetValue() != 0)
			break;

		if (!synthesize.load(std::memory_order_acquire))
			continue;

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

		HttpRequest->SetURL(PendingRequest.URL);

		if (PendingRequest.Body.IsEmpty())
		{
			HttpRequest->SetVerb("GET");
		}
		else
		{
			HttpRequest->SetVerb("POST");
			HttpRequest->SetContentAsString(PendingRequest.Body);
		}

		for (const auto& Header : PendingRequest.Headers)
		{
			HttpRequest->SetHeader(Header.Key, Header.Value);
		}

		const FString RequestID = PendingRequest.ID;
		const FString RequestText = PendingRequest.OriginalText;

		if (PendingRequest.bStreaming)
		{
			HttpRequest->OnRequestProgress64().BindLambda([this, RequestID](FHttpRequestPtr Req, int64 BytesSent, int64 BytesReceived)
			{
				if (BytesReceived > 0 && PreviousBytes < BytesReceived && Req->GetResponse().IsValid())
				{
					const TArray<uint8>& Content = Req->GetResponse()->GetContent();
					const int64 len = Content.Num();

					if (StreamingNum < len)
					{
						const int64 Available = len - StreamingNum;
						const int64 Aligned = Available - (Available & 1); // round down to even

						TArray<uint8> SynthResult(&Content[StreamingNum], Aligned);
						StreamingNum += Aligned;
						PreviousBytes = BytesReceived;
						TTSPartialResultAvailable.Broadcast(SynthResult, RequestID);
					}
				}
			});
		}

		HttpRequest->OnProcessRequestComplete().BindLambda([this, RequestID, RequestText](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (bWasSuccessful && Response.IsValid())
			{
				const TArray<uint8>& Content = Response->GetContent();

				if (PendingRequest.bStreaming && Content.Num() > StreamingNum)
				{
					TArray<uint8> Remaining(&Content[StreamingNum], Content.Num() - StreamingNum);
					PreviousBytes = 0;
					StreamingNum = 0;
					TTSPartialResultAvailable.Broadcast(Remaining, RequestID);
				}

				FTTSData SynthResult;
				SynthResult.AudioData = Content;
				SynthResult.ssml = RequestText;
				TTSResultAvailable.Broadcast(SynthResult, RequestID);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Connection to the TTS endpoint failed."));
			}
		});

		PreviousBytes = 0;
		StreamingNum = 0;

		HttpRequest->ProcessRequest();
		synthesize.store(false, std::memory_order_release);
	}
}

FDelegateHandle RESTTTSThread::TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate)
{
	return TTSResultAvailable.Add(UseDelegate);
}

void RESTTTSThread::TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	TTSResultAvailable.Remove(DelegateHandle);
}

FDelegateHandle RESTTTSThread::TTSPartialResultAvailableSubscribeUser(FTTSPartialResultAvailableDelegate& UseDelegate)
{
	return TTSPartialResultAvailable.Add(UseDelegate);
}

void RESTTTSThread::TTSPartialResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	TTSPartialResultAvailable.Remove(DelegateHandle);
}
