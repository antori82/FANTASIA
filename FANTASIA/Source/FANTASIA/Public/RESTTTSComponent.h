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
#include "Async/Future.h"
#include <atomic>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"

// NVIDIA ACE types can't be referenced directly in UPROPERTY declarations
// here: UHT needs the full UCLASS definition at parse time and the ACE
// headers are only available when the NV_ACE_Reference plugin is installed.
// So A2Fpointer / A2FParameters use UObject* in the reflected layout and
// EmotionParameters uses the FANTASIA-local mirror struct
// FFantasiaAudio2FaceEmotion (declared in FANTASIATypes.h). The .cpp casts
// pointers to the real ACE types and copies the emotion fields into a real
// FAudio2FaceEmotion inside #if FANTASIA_WITH_ACE. Blueprint authoring
// experience matches the old API; runtime Cast<> validates pointer types.

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
 * @brief Per-request audio buffer used for serial playback.
 *
 * One buffer is created per TTSSynthesize call and lives in a per-caller
 * list (BuffersByCaller) until both synthesis is complete and the
 * consumer has drained it. HTTP callbacks capture the buffer pointer
 * directly, so there is no by-id lookup that could clobber an in-flight
 * slot when the same caller id is reused (e.g. BP always passing
 * "Answer" for every sentence in a turn).
 *
 * Synthesis runs in parallel across many calls; playback is serial,
 * driven by PlaybackOrder (FIFO of buffer pointers in submission order).
 */
struct FAudioBuffer
{
	TArray<float> Samples;                          /**< Mono float samples at 16 kHz, in time order. */
	int32 ConsumedSamples = 0;                      /**< Count already pushed to A2F. */
	std::atomic<bool> bSynthesisComplete{false};    /**< Set once HTTP response is fully processed. */
	FCriticalSection Mutex;                         /**< Protects Samples + ConsumedSamples. */
};

/** Submission-order entry: caller id (for delegate broadcasts) + raw
 *  pointer to the audio buffer. The buffer's lifetime is owned by the
 *  TUniquePtr inside BuffersByCaller; we only remove it (and free it)
 *  AFTER bSynthesisComplete is observed AND the consumer has drained
 *  it, so the raw pointer is stable for as long as the consumer or HTTP
 *  callback could be holding it. */
struct FPlaybackOrderEntry
{
	FString CallerId;
	FAudioBuffer* Buffer;
};

/** Broadcast when a request's audio has finished playing (drained into A2F).
 *  This is a SEPARATE signal from SynthesisReady (which fires when the HTTP
 *  response has been received). PlaybackComplete is what callers should bind
 *  to if they need "Federico finished speaking sentence N" semantics. The
 *  Id is the caller's id passed to TTSSynthesize. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlaybackCompleteEvent, FString, Id);

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

	/**
	 * @brief Issue an HTTP request from the given synthesis descriptor.
	 *
	 * The HTTP callbacks capture `Target` directly so they push samples
	 * into the right buffer without any by-id lookup. This is what makes
	 * same-id-reuse safe.
	 *
	 * @param Request  Fully populated synthesis request.
	 * @param Target   Buffer to receive samples for this request. Owned
	 *                 by BuffersByCaller; pointer is stable for the
	 *                 buffer's lifetime.
	 */
	void IssueHttpRequest(FTTSSynthesisRequest Request, FAudioBuffer* Target);

	/**
	 * @brief Process a complete synthesis response (WAV detection, resampling, buffering).
	 * @param Response  Raw TTS data from the HTTP response.
	 * @param Id        Caller's request identifier (used for Buffer storage and SynthesisReady broadcast).
	 * @param Target    Per-call audio buffer to populate (non-streaming) and mark complete.
	 */
	void HandleResult(FTTSData Response, FString Id, FAudioBuffer* Target);

	/**
	 * @brief Process a streaming audio chunk and forward to Audio2Face.
	 * @param Response  Raw PCM bytes from the current streaming chunk.
	 * @param Id        Caller's request identifier (used for PartialSynthesisReady broadcast).
	 * @param Target    Per-call audio buffer to append to.
	 */
	void HandlePartialResult(TArray<uint8> Response, FString Id, FAudioBuffer* Target);

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

	// ── Audio2Face Serial Playback ─────────────────────────────────────

	std::atomic<bool> bIsPlaying{false};              /**< Controls the A2F consumer async task lifetime. */
	std::atomic<bool> bNeedsFlush{false};             /**< Signals the consumer to discard queued data. */
	FEventRef ConsumerWakeEvent{EEventMode::ManualReset}; /**< Wakes the A2F consumer task. */
	TFuture<void> ConsumerTaskFuture;                 /**< Handle to the A2F consumer task, joined in EndPlay. */

	/** Per-caller-id list of audio buffers, in submission order for that
	 *  id. TTSSynthesize appends a new buffer to the list for the given
	 *  id; the consumer drains from the head and pops once a buffer is
	 *  fully played. The same id can have many in-flight buffers (e.g.
	 *  when BP passes "Answer" for every sentence in a turn) without
	 *  collisions, because each buffer is its own object accessed via
	 *  raw pointer captured in the HTTP callback. */
	TMap<FString, TArray<TUniquePtr<FAudioBuffer>>> BuffersByCaller;
	FCriticalSection BuffersMutex;

	/** Global submission-order FIFO of (caller id, buffer pointer).
	 *  Cross-id ordering: if BP submits ("Answer", S1) then ("Answer", S2)
	 *  then ("Greeting", G1), the consumer plays S1 -> S2 -> G1.
	 *  SPSC: game thread is producer, consumer task is consumer. */
	TQueue<FPlaybackOrderEntry, EQueueMode::Spsc> PlaybackOrder;

	/** Entry currently being drained. Touched only by the consumer task. */
	TOptional<FPlaybackOrderEntry> CurrentPlayback;

	/** Set by EndTurn(); read by the consumer to decide when to send
	 *  bIsLastChunk=true to ACE. Reset by the consumer after that
	 *  closing chunk is dispatched. We can't infer turn end from
	 *  PlaybackOrder.IsEmpty(): TTS synthesis is faster than the
	 *  LangGraph sentence cadence, so the queue legitimately empties
	 *  between sentences within the same turn. Closing on empty would
	 *  finalize the ACE session mid-turn and force the next sentence
	 *  to re-open it. */
	std::atomic<bool> bTurnEndSignaled{false};

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

	/**
	 * Emotion parameters passed to Audio2Face during streaming.
	 * Uses FANTASIA's mirror struct (FFantasiaAudio2FaceEmotion) so Blueprint
	 * access works whether or not ACE is present. When FANTASIA_WITH_ACE=1
	 * the .cpp copies these fields into ACE's real FAudio2FaceEmotion before
	 * calling AnimateFromAudioSamples.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TTS")
	FFantasiaAudio2FaceEmotion EmotionParameters;

	// ── Events ─────────────────────────────────────────────────────────

	/** Broadcast when a full synthesis result is ready, carrying the request ID. */
	UPROPERTY(BlueprintAssignable, Category = "TTS")
	FSynthesizedEvent SynthesisReady;

	/** Broadcast when a partial (streaming) synthesis chunk arrives. */
	UPROPERTY(BlueprintAssignable, Category = "TTS")
	FPartialSynthesizedEvent PartialSynthesisReady;

	/** Broadcast when a request's audio has finished draining into A2F
	 *  (i.e. Federico has finished speaking that sentence). Bind to this
	 *  if you need to schedule follow-up actions after playback ends; it's
	 *  the correct signal for "is the avatar still talking?", whereas
	 *  SynthesisReady only tells you "the HTTP response arrived". */
	UPROPERTY(BlueprintAssignable, Category = "TTS")
	FPlaybackCompleteEvent PlaybackComplete;

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
	 *
	 * @param text       Plain text to synthesize.
	 * @param id         Unique identifier to retrieve results later.
	 * @param bEndTurn   If true, signal that this is the LAST sentence of
	 *                   the current turn. The consumer closes the ACE
	 *                   session cleanly (bIsLastChunk=true) on this
	 *                   buffer's tail; OnAnimationEnded then fires so the
	 *                   BP can unmute Whisper. If false (default), the
	 *                   stream stays open and the next TTSSynthesize
	 *                   continues it. Wire this from
	 *                   `IncomingLangGraphSentenceResponse`'s `EndStream`
	 *                   pin -- one TTS Start node, no Branch needed.
	 *
	 * Why the explicit signal: streamed synthesis (ElevenLabs) completes
	 * faster than the upstream LLM produces the next sentence, so the
	 * playback queue legitimately empties between sentences in the same
	 * turn. Inferring "turn over" from an empty queue would close the
	 * ACE session mid-turn.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "TTS"), Category = "TTS")
	void TTSSynthesize(FString text, FString id, bool bEndTurn = false);

	/**
	 * @brief Signal end-of-turn without synthesizing any new text.
	 *
	 * The common case is to use TTSSynthesize(text, id, bEndTurn=true)
	 * which folds the signal into the last sentence call. This standalone
	 * variant is for edge cases where you need to close the stream
	 * without a final sentence (e.g., the LLM produced no final message
	 * but you want the avatar to reset).
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS End Turn", Keywords = "TTS"), Category = "TTS")
	void EndTurn();

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
