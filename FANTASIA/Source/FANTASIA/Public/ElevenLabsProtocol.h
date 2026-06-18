/**
 * @file ElevenLabsProtocol.h
 * @brief Shared ElevenLabs request building + with-timestamps alignment decoding.
 *
 * Lives in core FANTASIA so both the core UElevenLabsTTSComponent and the
 * optional FANTASIAACE UACEElevenLabsTTSComponent reuse one implementation
 * (they inherit from different bases, so the protocol can't be shared via a
 * common component base).
 */

#pragma once

#include "CoreMinimal.h"
#include "RESTTTSComponent.h" // FTTSSynthesisRequest, FTTSStreamDecoder
#include "FANTASIATypes.h"    // FTTSSegmentTiming, FTTSData

/** ElevenLabs voice_settings payload fields. */
struct FElevenLabsVoiceSettings
{
	float Stability = 0.f;
	float SimilarityBoost = 0.f;
	float Style = 0.f;
	bool bUseSpeakerBoost = false;
};

/**
 * @brief Stateless helpers for the ElevenLabs text-to-speech protocol.
 */
class FANTASIA_API FElevenLabsProtocol
{
public:
	/**
	 * @brief Build a with-timestamps synthesis request.
	 * @param bStreaming  true -> /stream/with-timestamps (NDJSON), false -> /with-timestamps (single JSON).
	 * Always requests pcm_16000 so no audio decoding beyond base64 is needed.
	 */
	static FTTSSynthesisRequest BuildRequest(const FString& VoiceID, const FString& ModelID,
		const FString& Key, const FElevenLabsVoiceSettings& Settings,
		const FString& Text, const FString& ID, bool bStreaming);

	/** Per-request decoder for the streaming NDJSON envelope (base64 audio + alignment). */
	static TSharedPtr<FTTSStreamDecoder> MakeStreamDecoder();

	/**
	 * @brief Parse the one-shot /with-timestamps JSON envelope.
	 * @param Json       Raw JSON bytes (may alias OutResult.AudioData).
	 * @param OutResult  Receives decoded PCM in AudioData and Words/Characters timing.
	 */
	static void ParseOffline(const TArray<uint8>& Json, FTTSData& OutResult);

	/**
	 * @brief Group per-character timing into whole-word segments (split on whitespace).
	 *        Pure and deterministic -- unit-tested without network/ACE.
	 */
	static TArray<FTTSSegmentTiming> WordsFromCharacters(const TArray<FTTSSegmentTiming>& Characters);
};
