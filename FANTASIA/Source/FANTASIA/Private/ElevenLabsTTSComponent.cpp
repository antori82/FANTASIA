#include "ElevenLabsTTSComponent.h"
#include "Runtime/Json/Public/Json.h"

UElevenLabsTTSComponent::UElevenLabsTTSComponent()
{
	bStreaming = true;
	SampleRate = 16000;
}

FTTSSynthesisRequest UElevenLabsTTSComponent::BuildSynthesisRequest(const FString& Text, const FString& ID)
{
	FTTSSynthesisRequest Request;
	Request.ID = ID;
	Request.OriginalText = Text;
	Request.bStreaming = true;

	Request.URL = FString::Printf(TEXT("https://api.elevenlabs.io/v1/text-to-speech/%s/stream?output_format=pcm_16000"), *VoiceID);

	Request.Headers.Add(TEXT("Content-Type"), TEXT("application/json"));
	Request.Headers.Add(TEXT("xi-api-key"), Key);

	TSharedPtr<FJsonObject> PayloadObject = MakeShareable(new FJsonObject());
	TSharedPtr<FJsonObject> Settings = MakeShareable(new FJsonObject());

	Settings->SetNumberField("stability", stability);
	Settings->SetNumberField("similarity_boost", similarity_boost);
	Settings->SetNumberField("style", style);
	Settings->SetNumberField("use_speaker_boost", use_speaker_boost ? 1.0 : 0.0);

	PayloadObject->SetStringField("text", Text);
	PayloadObject->SetStringField("model_id", ModelID);
	PayloadObject->SetObjectField("voice_settings", Settings);

	FString Payload;
	FJsonSerializer::Serialize(PayloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&Payload));
	Request.Body = Payload;

	return Request;
}
