/**
 * @file ACERESTTTSComponent.h
 * @brief URESTTTSComponent subclass that animates a face from synthesized
 *        audio via NVIDIA Audio2Face.
 *
 * Lives in the optional FANTASIAACE plugin. Hard depends on NVIDIA's
 * NV_ACE_Reference plugin (ACERuntime + ACECore modules). The base
 * URESTTTSComponent populates per-call FAudioBuffer objects and stages
 * them in PlaybackOrder; this subclass installs the async consumer task
 * that drains them in submission order and feeds them to
 * UACEAudioCurveSourceComponent.
 */

#pragma once

#include "CoreMinimal.h"
#include "RESTTTSComponent.h"
#include "ACETypes.h" // FAudio2FaceEmotion
#include "Async/Future.h"
#include <atomic>

#include "ACERESTTTSComponent.generated.h"

class UACEAudioCurveSourceComponent;
class UAudio2FaceParameters;

/**
 * @brief REST TTS with NVIDIA Audio2Face lip-sync.
 *
 * Adds:
 *   - Strongly-typed A2F pointer UPROPERTYs (UACEAudioCurveSourceComponent,
 *     UAudio2FaceParameters), no Object* indirection.
 *   - FAudio2FaceEmotion EmotionParameters using the real ACE struct.
 *   - An async consumer task launched in BeginPlay that drains the parent
 *     class's per-call playback buffers and animates the face.
 *   - End-of-turn finalization via overridden EndTurn() so the ACE stream
 *     closes cleanly on the last sentence and OnAnimationEnded fires.
 */
UCLASS(meta = (BlueprintSpawnableComponent), Config = Game)
class FANTASIAACE_API UACERESTTTSComponent : public URESTTTSComponent
{
    GENERATED_BODY()

public:
    UACERESTTTSComponent();

    virtual void EndTurn() override;

    // ── A2F UPROPERTYs (strongly typed; visible to Blueprints) ─────────

    /** ACE audio-curve-source component that receives the animation. */
    UPROPERTY(BlueprintReadWrite, Category = "TTS")
    UACEAudioCurveSourceComponent* A2Fpointer;

    /** Audio2Face parameters object for animation configuration. */
    UPROPERTY(BlueprintReadWrite, Category = "TTS")
    UAudio2FaceParameters* A2FParameters;

    /** Named provider for the Audio2Face animation pipeline. */
    UPROPERTY(BlueprintReadWrite, Category = "TTS")
    FName A2FProvider;

    /** Emotion parameters passed to Audio2Face during streaming. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TTS")
    FAudio2FaceEmotion EmotionParameters;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    /** Triggered by the core class whenever new audio samples are
     *  available (HandleResult / HandlePartialResult). We wake the
     *  consumer so it picks up the new samples on its next iteration. */
    virtual void WakeConsumer() override;

private:
    // ── Consumer task lifecycle ────────────────────────────────────────

    /** Controls the consumer task's loop. Set false in EndPlay. */
    std::atomic<bool> bIsPlaying{false};

    /** Cancellation signal: drop queued buffers + reset state. */
    std::atomic<bool> bNeedsFlush{false};

    /** Set by EndTurn(); read by the consumer to decide when to send
     *  bIsLastChunk=true to ACE so the session finalises and
     *  OnAnimationEnded fires. */
    std::atomic<bool> bTurnEndSignaled{false};

    /** Wakes the consumer task on new samples / end-of-turn. */
    FEventRef ConsumerWakeEvent{EEventMode::ManualReset};

    /** Handle to the consumer task, joined in EndPlay so we don't tear
     *  down ACE state while AnimateFromAudioSamples is still in flight. */
    TFuture<void> ConsumerTaskFuture;
};
