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
	/** Playback speed: 0.7 (slower) .. 1.2 (faster); 1.0 = normal. */
	float Speed = 1.f;
};

/**
 * @brief Stateless helpers for the ElevenLabs text-to-speech protocol.
 */
class FANTASIA_API FElevenLabsProtocol
{
public:
	/**
	 * @brief Build a with-timestamps synthesis request.
	 * @param bStreaming    true -> /stream/with-timestamps (NDJSON), false -> /with-timestamps (single JSON).
	 * @param LanguageCode  ISO 639-1 code (e.g. "it") to force the language on models
	 *                      that support it (Flash/Turbo v2.5); empty = auto-detect.
	 * Always requests pcm_16000 so no audio decoding beyond base64 is needed.
	 */
	static FTTSSynthesisRequest BuildRequest(const FString& VoiceID, const FString& ModelID,
		const FString& Key, const FElevenLabsVoiceSettings& Settings,
		const FString& Text, const FString& ID, bool bStreaming,
		const FString& LanguageCode = FString());

	/**
	 * @brief Apply alias-style pronunciation rules to @p Text before synthesis.
	 *
	 * This is the Flash v2.5 "alias" mechanism done client-side: each rule is a
	 * whole-word respelling (e.g. "epilessia" -> "epilessìa") that pins a
	 * pronunciation the model otherwise samples inconsistently. Flash v2.5 ignores
	 * IPA/phoneme tags, so a respelling is the only reliable lever; doing it here
	 * keeps it in the engine, applied to every synthesis automatically.
	 *
	 * Matching is whole-word and case-insensitive; a match that begins with an
	 * uppercase letter keeps its leading capital (sentence-start "Epilessia" ->
	 * "Epilessìa"). Keys are matched on ASCII word runs, so the un-accented
	 * base form is the one to use as a key (which is the form that mispronounces
	 * anyway). Returns @p Text unchanged when @p Pronunciations is empty.
	 *
	 * Pure and deterministic -- unit-testable without network/ACE.
	 */
	static FString ApplyPronunciations(const TMap<FString, FString>& Pronunciations, const FString& Text);

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
