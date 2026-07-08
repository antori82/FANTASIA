/**
 * @file ElevenLabsTTSComponent.h
 * @brief Specialization of URESTTTSComponent for the ElevenLabs text-to-speech API.
 */

#pragma once

#include "CoreMinimal.h"
#include "RESTTTSComponent.h"
#include "ElevenLabsTTSComponent.generated.h"

/**
 * @brief Actor component for ElevenLabs text-to-speech synthesis.
 *
 * Inherits from URESTTTSComponent and overrides BuildSynthesisRequest to
 * construct ElevenLabs-specific HTTP requests with voice settings. Streams
 * 16 kHz 16-bit mono PCM audio by default.
 *
 * @see URESTTTSComponent
 */
UCLASS(meta = (BlueprintSpawnableComponent), Config = Game)
class UElevenLabsTTSComponent : public URESTTTSComponent
{
	GENERATED_BODY()

public:
	UElevenLabsTTSComponent();

protected:
	/**
	 * @brief Build an ElevenLabs with-timestamps synthesis request.
	 * @param Text  Plain text to synthesize.
	 * @param ID    Caller-assigned request identifier.
	 * @return Fully populated FTTSSynthesisRequest (streaming or one-shot per bStreaming).
	 */
	virtual FTTSSynthesisRequest BuildSynthesisRequest(const FString& Text, const FString& ID) override;

	/** Streaming NDJSON decoder (base64 audio + character alignment). */
	virtual TSharedPtr<FTTSStreamDecoder> CreateStreamDecoder() override;

	/** Offline path: parse the one-shot /with-timestamps JSON envelope. */
	virtual void ProcessResponse(const TArray<uint8>& RawResponse, FTTSData& OutResult) override;

public:

	// ── Configuration ──────────────────────────────────────────────────

	/** ElevenLabs voice ID to use for synthesis. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString VoiceID;

	/** ElevenLabs model ID (e.g. "eleven_monolingual_v1"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString ModelID;

	/** ElevenLabs API key. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	/** ISO 639-1 language code to force (e.g. "it" for Italian). Empty lets the
	 *  model auto-detect from the text. Supported by Flash / Turbo v2.5. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString language_code;

	// ── Voice Settings ─────────────────────────────────────────────────

	/** Voice stability (0.0 = more variable, 1.0 = more stable). */
	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float stability;

	/** Similarity boost (0.0 = less similar, 1.0 = more similar to original voice). */
	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float similarity_boost;

	/** Speaking style exaggeration (0.0 = neutral, 1.0 = fully expressive). */
	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float style;

	/** Whether to apply the speaker boost filter. */
	UPROPERTY(EditAnywhere, Category = "Voice Settings")
	bool use_speaker_boost;

	/** Playback speed: 0.7 (slower) .. 1.2 (faster); 1.0 = normal. */
	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.7", UIMax = "1.2"))
	float speed = 1.0f;

	// ── Pronunciation ──────────────────────────────────────────────────

	/** Whole-word respelling rules applied to the text before synthesis: key =
	 *  word as written, value = respelling that pronounces correctly (e.g.
	 *  "epilessia" -> "epilessìa"). This is the Flash v2.5 alias mechanism --
	 *  the model samples stress inconsistently on uncommon words, and a
	 *  respelling pins it. Matching is whole-word, case-insensitive. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pronunciation", Config)
	TMap<FString, FString> PronunciationMap;
};
