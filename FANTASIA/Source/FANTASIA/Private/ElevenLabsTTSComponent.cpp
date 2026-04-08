/**
 * @file ElevenLabsTTSComponent.cpp
 * @brief Implementation of UElevenLabsTTSComponent -- ElevenLabs TTS specialization.
 */

#include "ElevenLabsTTSComponent.h"
#include "Runtime/Json/Public/Json.h"

/** Sets default streaming mode and 16 kHz sample rate for ElevenLabs output. */
UElevenLabsTTSComponent::UElevenLabsTTSComponent()
{
	bStreaming = true;
	SampleRate = 16000;
}

/**
 * Constructs an ElevenLabs streaming TTS request with voice settings JSON payload.
 * Targets the /v1/text-to-speech/{VoiceID}/stream endpoint with pcm_16000 output.
 */
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
