#include "ElevenLabsTTSThread.h"

using namespace std;

ElevenLabsTTSThread* ElevenLabsTTSThread::Runnable = NULL;

ElevenLabsTTSThread::ElevenLabsTTSThread(FString inKey, FString inText, FString inID, FString inVoiceID, FString inModelID, float inStability, float inSimilarity_boost, float inStyle, bool inUse_speaker_boost) : StopTaskCounter(0) {
	key = inKey;
	text = inText;
	id = inID;
	voiceID = inVoiceID;
	modelID = inModelID;
	stability = inStability;
	similarity_boost = inSimilarity_boost;
	style = inStyle;
	use_speaker_boost = inUse_speaker_boost;

	Thread = FRunnableThread::Create(this, TEXT("ElevenLabsTTSThread"), 0, TPri_Normal);
	Endpoint = "https://api.elevenlabs.io/v1/text-to-speech/" + voiceID;
}

ElevenLabsTTSThread::~ElevenLabsTTSThread() {
	delete Thread;
	Thread = NULL;
}


ElevenLabsTTSThread* ElevenLabsTTSThread::setup(FString key, FString text, FString inID, FString voiceID, FString modelID, float stability, float similarity_boost, float style, bool use_speaker_boost) {
	if (!Runnable && FPlatformProcess::SupportsMultithreading()) {
		Runnable = new ElevenLabsTTSThread(key, text, inID, voiceID, modelID, stability, similarity_boost, style, use_speaker_boost);
	}
	return Runnable;
}

bool ElevenLabsTTSThread::Init() {
	return true;
}

uint32 ElevenLabsTTSThread::Run() {
	Synthesize();
	return 0;
}

void ElevenLabsTTSThread::Stop() {
	StopTaskCounter.Increment();
}

void ElevenLabsTTSThread::EnsureCompletion() {
	Stop();
	Thread->WaitForCompletion();
}

void ElevenLabsTTSThread::Shutdown() {
	if (Runnable) {
		Runnable = NULL;
	}
}

void ElevenLabsTTSThread::Synthesize()
{
	FString payload;
	TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());
	TSharedPtr<FJsonObject> settings = MakeShareable(new FJsonObject());

	//Http request to API
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
			if (bWasSuccessful && Response.IsValid()) {
				TArray<uint8> ResponseData = Response->GetContent();

				FTTSData SynthResult;
				SynthResult.AudioData = ResponseData;
				SynthResult.ssml = text;

				TTSResultAvailable.Broadcast(SynthResult, id);

			}
			else {
				UE_LOG(LogTemp, Error, TEXT("Connection to the TTS endpoint failed."));
			}
		});
	Request->SetURL(Endpoint + "?output_format=pcm_16000");
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
}

FDelegateHandle ElevenLabsTTSThread::TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate) {
	return TTSResultAvailable.Add(UseDelegate);
}

void ElevenLabsTTSThread::TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) {
	TTSResultAvailable.Remove(DelegateHandle);
}