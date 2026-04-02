#include "ElevenLabsTTSThread.h"

ElevenLabsTTSThread* ElevenLabsTTSThread::Runnable = NULL;

ElevenLabsTTSThread::ElevenLabsTTSThread(FString inKey, FString inVoiceID, FString inModelID, float inStability, float inSimilarity_boost, float inStyle, bool inUse_speaker_boost, bool stream)
	: StopTaskCounter(0)
{
	key = inKey;
	voiceID = inVoiceID;
	modelID = inModelID;
	stability = inStability;
	similarity_boost = inSimilarity_boost;
	style = inStyle;
	use_speaker_boost = inUse_speaker_boost;
	isStreaming = stream;
	Thread = FRunnableThread::Create(this, TEXT("ElevenLabsTTSThread"), 0, TPri_Normal);
}

ElevenLabsTTSThread::~ElevenLabsTTSThread() {
	delete Thread;
	Thread = NULL;
}

ElevenLabsTTSThread* ElevenLabsTTSThread::setup(FString key, FString voiceID, FString modelID, float stability, float similarity_boost, float style, bool use_speaker_boost, bool stream) {
	if (!Runnable && FPlatformProcess::SupportsMultithreading()) {
		Runnable = new ElevenLabsTTSThread(key, voiceID, modelID, stability, similarity_boost, style, use_speaker_boost, stream);
	}
	return Runnable;
}

bool ElevenLabsTTSThread::Init() {
	return true;
}

uint32 ElevenLabsTTSThread::Run() {
	SynthesizeLoop();
	return 0;
}

void ElevenLabsTTSThread::Stop() {
	StopTaskCounter.Increment();
	SynthesizeWakeEvent->Trigger();  // [OPT] Wake the loop so it can check StopTaskCounter and exit
}

void ElevenLabsTTSThread::EnsureCompletion() {
	Stop();
	Thread->WaitForCompletion();
}

void ElevenLabsTTSThread::Shutdown() {
	if (Runnable) {
		Runnable->EnsureCompletion();  // [FIX] Actually stop the thread before nulling the pointer.
		                               // Original just set Runnable=NULL, leaving a zombie thread running forever.
		delete Runnable;
		Runnable = NULL;
	}
}

void ElevenLabsTTSThread::Synthesize(FString inText, FString inID) {
	id = inID;
	text = inText;
	synthesize.store(true, std::memory_order_release);
	SynthesizeWakeEvent->Trigger();  // [OPT] Wake the loop immediately instead of waiting for it to poll
}

void ElevenLabsTTSThread::SynthesizeLoop()
{
	// [FIX] Original: `while (true)` with no exit condition.
	// StopTaskCounter was never checked, so Stop()/EnsureCompletion() could not terminate the thread.
	while (StopTaskCounter.GetValue() == 0) {

		// [OPT-CRITICAL] The original loop was: while(true) { if(synthesize) { ... } }
		// When no synthesis is pending (which is the vast majority of the time), this spins at 100% CPU
		// on one core doing nothing but re-reading `synthesize` millions of times per second.
		// FEvent::Wait puts the OS thread to sleep at zero CPU cost until Synthesize() or Stop() signals it.
		SynthesizeWakeEvent->Wait();
		SynthesizeWakeEvent->Reset();

		if (StopTaskCounter.GetValue() != 0)
			break;

		if (!synthesize.load(std::memory_order_acquire))
			continue;

		FString payload;
		TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonObject> settings = MakeShareable(new FJsonObject());

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

		if (isStreaming) {
			Request->SetURL("https://api.elevenlabs.io/v1/text-to-speech/" + voiceID + "/stream?output_format=pcm_16000");
			Request->OnRequestProgress64().BindLambda([this](FHttpRequestPtr Req, int64 BytesSent, int64 BytesReceived)
				{
					if (BytesReceived > 0 && PreviousBytes < BytesReceived && Req->GetResponse().IsValid()) {

						// [FIX] Was: uint16 len = Req->GetResponse()->GetContent().Num();
						// GetContent().Num() returns int32. uint16 silently truncates anything above 65535,
						// which is only ~2 seconds of 16kHz 16-bit mono PCM. Any longer sentence would
						// wrap around and corrupt the streaming offsets, producing garbled audio.
						const int64 len = Req->GetResponse()->GetContent().Num();

						if (StreamingNum < len) {
							TArray<uint8> SynthResult;
							const int64 Available = len - StreamingNum;

							if (Available % 2 == 0) {
								SynthResult = TArray<uint8>(&Req->GetResponse()->GetContent()[StreamingNum], Available);
								StreamingNum = len;
							}
							else {
								SynthResult = TArray<uint8>(&Req->GetResponse()->GetContent()[StreamingNum], Available - 1);
								StreamingNum = len - 1;
							}

							PreviousBytes = BytesReceived;
							TTSPartialResultAvailable.Broadcast(SynthResult, id);
						}
					}
				});
		}
		else {
			Request->SetURL("https://api.elevenlabs.io/v1/text-to-speech/" + voiceID + "?output_format=pcm_16000");
		}

		Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
			if (bWasSuccessful && Response.IsValid()) {
				TArray<uint8> ResponseData = Response->GetContent();

				FTTSData SynthResult;
				SynthResult.AudioData = ResponseData;
				SynthResult.ssml = text;

				if (isStreaming && ResponseData.Num() > StreamingNum) {
					TArray<uint8> Remaining(&Response->GetContent()[StreamingNum], ResponseData.Num() - StreamingNum);
					PreviousBytes = 0;
					StreamingNum = 0;
					TTSPartialResultAvailable.Broadcast(Remaining, id);
				}

				TTSResultAvailable.Broadcast(SynthResult, id);
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("Connection to the TTS endpoint failed."));
			}
		});

		PreviousBytes = 0;
		StreamingNum = 0;

		Request->SetVerb("POST");
		Request->SetHeader("Content-Type", "application/json");
		Request->SetHeader("xi-api-key", key);

		settings->SetNumberField("stability", stability);
		settings->SetNumberField("similarity_boost", similarity_boost);
		settings->SetNumberField("style", style);
		settings->SetNumberField("use_speaker_boost", use_speaker_boost);

		payloadObject->SetStringField("text", text);
		payloadObject->SetStringField("model_id", modelID);
		payloadObject->SetObjectField("voice_settings", settings);

		FJsonSerializer::Serialize(payloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&payload));
		Request->SetContentAsString(payload);

		Request->ProcessRequest();
		synthesize.store(false, std::memory_order_release);
	}
}

FDelegateHandle ElevenLabsTTSThread::TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate) {
	return TTSResultAvailable.Add(UseDelegate);
}

void ElevenLabsTTSThread::TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) {
	TTSResultAvailable.Remove(DelegateHandle);
}

FDelegateHandle ElevenLabsTTSThread::TTSPartialResultAvailableSubscribeUser(FTTSPartialResultAvailableDelegate& UseDelegate) {
	return TTSPartialResultAvailable.Add(UseDelegate);
}

void ElevenLabsTTSThread::TTSPartialResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) {
	TTSPartialResultAvailable.Remove(DelegateHandle);
}
