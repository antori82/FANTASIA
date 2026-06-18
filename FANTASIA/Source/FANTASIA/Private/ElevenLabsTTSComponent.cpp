/**
 * @file ElevenLabsTTSComponent.cpp
 * @brief Implementation of UElevenLabsTTSComponent -- ElevenLabs TTS specialization.
 *
 * Request building and with-timestamps alignment decoding live in the shared
 * FElevenLabsProtocol so the core and FANTASIAACE ElevenLabs components stay in
 * lockstep.
 */

#include "ElevenLabsTTSComponent.h"
#include "ElevenLabsProtocol.h"

/** Sets default streaming mode and 16 kHz sample rate for ElevenLabs output. */
UElevenLabsTTSComponent::UElevenLabsTTSComponent()
{
	bStreaming = true;
	SampleRate = 16000;
}

FTTSSynthesisRequest UElevenLabsTTSComponent::BuildSynthesisRequest(const FString& Text, const FString& ID)
{
	FElevenLabsVoiceSettings Settings;
	Settings.Stability = stability;
	Settings.SimilarityBoost = similarity_boost;
	Settings.Style = style;
	Settings.bUseSpeakerBoost = use_speaker_boost;
	return FElevenLabsProtocol::BuildRequest(VoiceID, ModelID, Key, Settings, Text, ID, bStreaming);
}

TSharedPtr<FTTSStreamDecoder> UElevenLabsTTSComponent::CreateStreamDecoder()
{
	return FElevenLabsProtocol::MakeStreamDecoder();
}

void UElevenLabsTTSComponent::ProcessResponse(const TArray<uint8>& RawResponse, FTTSData& OutResult)
{
	FElevenLabsProtocol::ParseOffline(RawResponse, OutResult);
}
