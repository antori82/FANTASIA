/**
 * @file ACEElevenLabsTTSComponent.cpp
 * @brief Implementation of UACEElevenLabsTTSComponent -- ElevenLabs TTS with A2F.
 *
 * Request building and with-timestamps alignment decoding are shared with the
 * core ElevenLabs component via FElevenLabsProtocol (lives in core FANTASIA).
 */

#include "ACEElevenLabsTTSComponent.h"
#include "ElevenLabsProtocol.h"

UACEElevenLabsTTSComponent::UACEElevenLabsTTSComponent()
{
	bStreaming = true;
	SampleRate = 16000;
}

FTTSSynthesisRequest UACEElevenLabsTTSComponent::BuildSynthesisRequest(const FString& Text, const FString& ID)
{
	FElevenLabsVoiceSettings Settings;
	Settings.Stability = stability;
	Settings.SimilarityBoost = similarity_boost;
	Settings.Style = style;
	Settings.bUseSpeakerBoost = use_speaker_boost;
	Settings.Speed = speed;
	const FString Pronounced = FElevenLabsProtocol::ApplyPronunciations(PronunciationMap, Text);
	return FElevenLabsProtocol::BuildRequest(VoiceID, ModelID, Key, Settings, Pronounced, ID, bStreaming, language_code);
}

TSharedPtr<FTTSStreamDecoder> UACEElevenLabsTTSComponent::CreateStreamDecoder()
{
	return FElevenLabsProtocol::MakeStreamDecoder();
}

void UACEElevenLabsTTSComponent::ProcessResponse(const TArray<uint8>& RawResponse, FTTSData& OutResult)
{
	FElevenLabsProtocol::ParseOffline(RawResponse, OutResult);
}
