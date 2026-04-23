/**
 * @file RESTTTSComponent.h
 * @brief Generic REST-based text-to-speech actor component with streaming and Audio2Face support.
 */

#pragma once

#include "FANTASIA.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "Http.h"
#include <atomic>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"

// NVIDIA ACE types can't be referenced directly in UPROPERTY declarations
// here, because UHT needs the full UCLASS definition at parse time and the
// ACE headers are only available when the NV_ACE_Reference plugin is
// installed. So the Audio2Face pointer UPROPERTYs below use UObject* and
// the .cpp casts to the real ACE types (inside FANTASIA_WITH_ACE guards).
// The Blueprint editor presents a generic object picker; users wire the
// ACE component normally and runtime Cast<> validates the type.
#if FANTASIA_WITH_ACE
#include "ACERuntimeModule.h"
#include "ACEAudioCurveSourceComponent.h"
#endif

#include "RESTTTSComponent.generated.h"

/**
 * @brief Describes a single HTTP request for TTS synthesis.
 *
 * Built by URESTTTSComponent::BuildSynthesisRequest (or subclass overrides)
 * and consumed by IssueHttpRequest.
 */
struct FTTSSynthesisRequest
{
	FString URL;                        /**< Target endpoint URL. */
	TMap<FString, FString> Headers;     /**< HTTP headers to include. */
	FString Body;                       /**< Request body. Empty triggers a GET; non-empty triggers a POST. */
	FString ID;                         /**< Caller-assigned request identifier. */
	FString OriginalText;               /**< Original text submitted for synthesis. */
	bool bStreaming = false;            /**< If true, process audio chunks as they arrive. */
};

/** Number of float samples batched before each Audio2Face streaming call. */
static constexpr int32 A2F_STREAMING_BATCH_SIZE = 100;

/**
 * @brief Generic REST-based text-to-speech actor component.
 *
 * Sends HTTP GET or POST requests to any TTS endpoint, receives PCM audio,
 * auto-detects WAV headers, resamples to 16 kHz, and optionally streams
 * audio chunks to NVIDIA Audio2Face for real-time lip animation.
 *
 * Subclasses (e.g. UElevenLabsTTSComponent) override BuildSynthesisRequest
 * and ProcessResponse to handle provider-specific protocols.
 *
 * @see UElevenLabsTTSComponent, FTTSSynthesisRequest
 */
UCLASS(meta = (BlueprintSpawnableComponent), Config = Game)
class FANTASIA_API URESTTTSComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * @brief Build the HTTP request for a synthesis call.
	 *
	 * Base implementation uses URL, Headers, and BodyTemplate properties.
	 * Subclasses override to build provider-specific requests.
	 *
	 * @param Text  Plain text to synthesize.
	 * @param ID    Caller-assigned request identifier.
	 * @return Populated synthesis request descriptor.
	 */
	virtual FTTSSynthesisRequest BuildSynthesisRequest(const FString& Text, const FString& ID);

	/**
	 * @brief Extract additional data (word timing, lipsync, notifies) from the raw HTTP response.
	 *
	 * Called in HandleResult after WAV detection and resampling.
	 * Base implementation is a no-op.
	 *
	 * @param RawResponse  Raw HTTP response bytes.
	 * @param OutResult    TTS data to populate with extracted metadata.
	 */
	virtual void ProcessResponse(const TArray<uint8>& RawResponse, FTTSData& OutResult);

	/** Expected sample rate of the incoming audio (used when no WAV header is present). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	int32 SampleRate = 16000;

	/** If true, process audio chunks as they arrive (streaming mode). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	bool bStreaming = false;

private:

	// ── Result Buffering ───────────────────────────────────────────────

	/** Maps request IDs to completed TTS data (thread-safe via BufferMutex). */
	TMap<FString, FTTSData> Buffer;

	/** Mutex protecting Buffer access from HTTP callback and game threads. */
	FCriticalSection BufferMutex;

	// ── Streaming State ────────────────────────────────────────────────

	int64 StreamingNum = 0;     /**< Byte offset of the last processed streaming chunk. */
	int64 PreviousBytes = 0;    /**< Previous BytesReceived value for delta detection. */

	/**
	 * @brief Issue an HTTP request from the given synthesis descriptor.
	 * @param Request  Fully populated synthesis request.
	 */
	void IssueHttpRequest(FTTSSynthesisRequest Request);

	/**
	 * @brief Process a complete synthesis response (WAV detection, resampling, buffering).
	 * @param Response  Raw TTS data from the HTTP response.
	 * @param Id        Request identifier.
	 */
	void HandleResult(FTTSData Response, FString Id);

	/**
	 * @brief Process a streaming audio chunk and forward to Audio2Face.
	 * @param Response  Raw PCM bytes from the current streaming chunk.
	 * @param Id        Request identifier.
	 */
	void HandlePartialResult(TArray<uint8> Response, FString Id);

	/**
	 * @brief Parse a WAV header. Returns true if data starts with RIFF/WAVE magic.
	 * @param Data             Raw audio data to inspect.
	 * @param OutSampleRate    Parsed sample rate.
	 * @param OutNumChannels   Parsed channel count.
	 * @param OutBitsPerSample Parsed bits per sample.
	 * @param OutDataOffset    Byte offset where PCM data begins.
	 * @return True if a valid WAV header was found.
	 */
	static bool TryParseWavHeader(const TArray<uint8>& Data, int32& OutSampleRate, int32& OutNumChannels, int32& OutBitsPerSample, int32& OutDataOffset);

	/**
	 * @brief Resample 16-bit PCM audio from SourceRate to 16000 Hz using linear interpolation.
	 * @param PCMData      Pointer to raw PCM data.
	 * @param NumBytes     Number of bytes in PCMData.
	 * @param SourceRate   Original sample rate of the input.
	 * @param NumChannels  Number of audio channels in the input.
	 * @return Resampled mono 16-bit PCM data at 16 kHz.
	 */
	static TArray<uint8> ResampleTo16kHz(const uint8* PCMData, int32 NumBytes, int32 SourceRate, int32 NumChannels);

	// ── Audio2Face Streaming ───────────────────────────────────────────

	std::atomic<bool> bUsingStreamingBuffer{false};  /**< True while streaming chunks to A2F. */
	std::atomic<bool> bBufferOpen{false};             /**< True while the streaming buffer has data. */
	std::atomic<bool> bIsPlaying{false};              /**< Controls the A2F consumer async task lifetime. */
	std::atomic<bool> bNeedsFlush{false};             /**< Signals the consumer to discard queued data. */
	TQueue<float, EQueueMode::Spsc> SendData;         /**< Lock-free queue of normalized float samples for A2F. */
	FEventRef ConsumerWakeEvent{EEventMode::ManualReset}; /**< Wakes the A2F consumer task. */

public:
	URESTTTSComponent();

	// ── Audio2Face Integration ─────────────────────────────────────────
	// UPROPERTYs must be declared unconditionally (UHT forbids #if around
	// UPROPERTYs). To let FANTASIA ship a single DLL that loads with or
	// without NVIDIA ACE, these use UObject* rather than the actual ACE
	// types. The .cpp casts to UACEAudioCurveSourceComponent /
	// UAudio2FaceParameters when FANTASIA_WITH_ACE=1. With ACE absent the
	// pointers can still be set from Blueprint to any UObject but the
	// lipsync code paths are compiled out so the values are simply ignored.

	/** Pointer to the ACE Audio Curve Source component for Audio2Face animation.
	 *  Expected concrete type: UACEAudioCurveSourceComponent (from NV_ACE_Reference). */
	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	UObject* A2Fpointer;

	/** Audio2Face parameters object for animation configuration.
	 *  Expected concrete type: UAudio2FaceParameters (from NV_ACE_Reference). */
	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	UObject* A2FParameters;

	/** Named provider for the Audio2Face animation pipeline. */
	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	FName A2FProvider;

#if FANTASIA_WITH_ACE
	/**
	 * Emotion parameters passed to Audio2Face during streaming.
	 * Not a UPROPERTY: UHT forbids conditional UPROPERTYs, and FAudio2FaceEmotion
	 * is an ACE-defined struct that can't be forward-declared as a by-value field.
	 * In builds without ACE this field is compiled out entirely; users who need
	 * Blueprint-level control over emotion must rebuild the plugin with ACE.
	 */
	FAudio2FaceEmotion EmotionParameters;
#endif // FANTASIA_WITH_ACE

	// ── Events ─────────────────────────────────────────────────────────

	/** Broadcast when a full synthesis result is ready, carrying the request ID. */
	UPROPERTY(BlueprintAssignable, Category = "TTS")
	FSynthesizedEvent SynthesisReady;

	/** Broadcast when a partial (streaming) synthesis chunk arrives. */
	UPROPERTY(BlueprintAssignable, Category = "TTS")
	FPartialSynthesizedEvent PartialSynthesisReady;

	// ── HTTP Configuration ─────────────────────────────────────────────

	/** Base URL for the TTS endpoint. May contain {text} placeholder for GET mode. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", Config)
	FString URL;

	/** HTTP headers to include in every synthesis request. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	TMap<FString, FString> Headers;

	/**
	 * @brief JSON body template. Use {text} as placeholder for the synthesis text.
	 *        If empty, a GET request is made (with {text} URL-encoded in the URL).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", Config, meta = (MultiLine = true))
	FString BodyTemplate;

	// ── Public Methods ─────────────────────────────────────────────────

	/**
	 * @brief Start a text-to-speech synthesis request.
	 * @param text  Plain text to synthesize.
	 * @param id    Unique identifier to retrieve results later.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "TTS"), Category = "TTS")
	void TTSSynthesize(FString text, FString id);

	/**
	 * @brief Retrieve the synthesized audio as a USoundWaveProcedural.
	 * @param id  Identifier of a completed synthesis request.
	 * @return Procedural SoundWave containing 16 kHz mono PCM audio, or nullptr if not found.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "TTS"), Category = "TTS")
	USoundWaveProcedural* TTSGetSound(FString id);

	/**
	 * @brief Retrieve raw PCM audio bytes for a completed synthesis.
	 * @param id  Identifier of a completed synthesis request.
	 * @return Raw 16-bit PCM byte array, or empty if not found.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Raw Sound", Keywords = "TTS"), Category = "TTS")
	TArray<uint8> TTSGetRawSound(FString id);
};
