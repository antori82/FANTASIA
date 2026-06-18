/**
 * @file ACEElevenLabsTTSComponent.h
 * @brief ElevenLabs TTS with NVIDIA Audio2Face lip-sync.
 *
 * Combines the ElevenLabs voice-synthesis settings with the A2F consumer
 * task from UACERESTTTSComponent, giving Blueprints a single component
 * that exposes A2Fpointer, A2FParameters, A2FProvider, and
 * EmotionParameters alongside the ElevenLabs voice configuration.
 */

#pragma once

#include "CoreMinimal.h"
#include "ACERESTTTSComponent.h"
#include "ACEElevenLabsTTSComponent.generated.h"

/**
 * @brief ElevenLabs text-to-speech with Audio2Face animation.
 *
 * Inherits all A2F plumbing (A2Fpointer, A2FParameters, A2FProvider,
 * EmotionParameters, consumer task) from UACERESTTTSComponent and
 * overrides BuildSynthesisRequest to target the ElevenLabs streaming API.
 *
 * @see UACERESTTTSComponent, UElevenLabsTTSComponent
 */
UCLASS(meta = (BlueprintSpawnableComponent), Config = Game)
class FANTASIAACE_API UACEElevenLabsTTSComponent : public UACERESTTTSComponent
{
	GENERATED_BODY()

public:
	UACEElevenLabsTTSComponent();

protected:
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
};
