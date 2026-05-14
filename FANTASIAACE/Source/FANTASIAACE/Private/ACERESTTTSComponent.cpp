/**
 * @file ACERESTTTSComponent.cpp
 * @brief Implementation of UACERESTTTSComponent (A2F lip-sync extension).
 */

#include "ACERESTTTSComponent.h"
#include "ACERuntimeModule.h"
#include "ACEAudioCurveSourceComponent.h"
#include "Audio2FaceParameters.h"
#include "Async/Async.h"

UACERESTTTSComponent::UACERESTTTSComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

/**
 * Launches the Audio2Face consumer async task. The task drains per-call
 * audio buffers (allocated by the parent URESTTTSComponent::TTSSynthesize
 * and stashed in PlaybackOrder) in submission order, batches samples,
 * and feeds them to ACE AnimateFromAudioSamples. Multiple TTSSynthesize
 * calls may issue HTTP requests in parallel -- their per-call buffers
 * fill out of order, but this task plays them in call order, marking
 * each buffer's tail with bIsLastChunk=true so A2F closes each utterance
 * cleanly. Buffers are removed from BuffersByCaller and freed once
 * fully drained; PlaybackComplete fires for the caller's id at that point.
 */
void UACERESTTTSComponent::BeginPlay()
{
    Super::BeginPlay();

    bIsPlaying.store(true);

    // Use Async (not AsyncTask) so we get a future we can join on in EndPlay.
    // Without the join, component EndPlay returns while the consumer is still
    // in its 50 ms wake cycle; if BP EndPlay then deallocates ACE resources
    // immediately after (as the Alice/MetaFamily setup does), the consumer can
    // reach into half-torn-down ACE state via AnimateFromAudioSamples and
    // trigger a use-after-free in NVIDIA's DirectML DLL (nvdxgdmal64.dll).
    ConsumerTaskFuture = Async(EAsyncExecution::ThreadPool, [this]()
    {
        // Audio-realtime pacing: send exactly one BATCH_SIZE batch per
        // AnimateFromAudioSamples call and sleep its audio duration. Burst-
        // feeding huge batches makes ACE spawn overlapping audio outputs.
        constexpr int32 SampleRateHz = 16000;
        constexpr float BatchSeconds = float(A2F_STREAMING_BATCH_SIZE) / float(SampleRateHz);
        constexpr float PaceSleep = BatchSeconds * 0.95f;

        // outData persists across slot transitions: a slot's tail samples
        // stay buffered and combine with the next slot's head into a full
        // BATCH_SIZE batch. Keeps every send the same size so the pacing
        // sleep stays accurate.
        TArray<float> outData;
        outData.Reserve(A2F_STREAMING_BATCH_SIZE);

        auto SendOutData = [&](bool bIsLastChunk)
        {
            if (outData.Num() == 0) return;
            if (IsValid(A2Fpointer))
            {
                FACERuntimeModule::Get().AnimateFromAudioSamples(
                    A2Fpointer, outData, 1, SampleRateHz, bIsLastChunk,
                    EmotionParameters, A2FParameters, A2FProvider);
            }
            outData.Empty();
            FPlatformProcess::Sleep(PaceSleep);
        };

        while (bIsPlaying.load(std::memory_order_relaxed))
        {
            ConsumerWakeEvent->Wait(50);
            ConsumerWakeEvent->Reset();

            // ── Cancellation path ──────────────────────────────────────
            if (bNeedsFlush.load(std::memory_order_acquire))
            {
                FPlaybackOrderEntry discard;
                while (PlaybackOrder.Dequeue(discard)) {}
                {
                    FScopeLock Lock(&BuffersMutex);
                    BuffersByCaller.Empty();
                }
                CurrentPlayback.Reset();
                outData.Empty();
                bNeedsFlush.store(false, std::memory_order_release);
                continue;
            }

            // ── Acquire next entry if idle ─────────────────────────────
            if (!CurrentPlayback.IsSet())
            {
                FPlaybackOrderEntry NextEntry;
                if (!PlaybackOrder.Dequeue(NextEntry))
                {
                    // Nothing queued. If end-of-turn was signaled, send
                    // the buffered tail with bIsLastChunk=true so ACE
                    // finalizes the session and OnAnimationEnded fires
                    // (BP unmutes Whisper). If the last batch landed on
                    // a boundary and outData is empty, send one zeroed
                    // sample just to carry the close flag.
                    if (bTurnEndSignaled.load(std::memory_order_acquire))
                    {
                        if (outData.Num() > 0)
                        {
                            SendOutData(true);
                        }
                        else
                        {
                            if (IsValid(A2Fpointer))
                            {
                                TArray<float> Tail;
                                Tail.Add(0.0f);
                                FACERuntimeModule::Get().AnimateFromAudioSamples(
                                    A2Fpointer, Tail, 1, SampleRateHz, /*bIsLastChunk=*/true,
                                    EmotionParameters, A2FParameters, A2FProvider);
                            }
                        }
                        bTurnEndSignaled.store(false, std::memory_order_release);
                    }
                    continue;
                }
                CurrentPlayback = NextEntry;
            }

            FAudioBuffer* Target = CurrentPlayback->Buffer;
            if (!Target)
            {
                CurrentPlayback.Reset();
                ConsumerWakeEvent->Trigger();
                continue;
            }

            // ── Top up outData from current slot (up to BATCH_SIZE) ────
            bool bSlotFullyConsumed = false;
            {
                FScopeLock BufferLock(&Target->Mutex);
                const int32 NeedMore = A2F_STREAMING_BATCH_SIZE - outData.Num();
                const int32 Available = Target->Samples.Num() - Target->ConsumedSamples;
                const int32 ToTake = FMath::Min(NeedMore, Available);
                if (ToTake > 0)
                {
                    outData.Append(Target->Samples.GetData() + Target->ConsumedSamples, ToTake);
                    Target->ConsumedSamples += ToTake;
                }
                // Memory order matters: HandleResult sets bSynthesisComplete
                // AFTER its final append; acquire semantics here ensures we
                // see those last samples.
                const bool bComplete = Target->bSynthesisComplete.load(std::memory_order_acquire);
                const bool bFullyDrained = (Target->ConsumedSamples >= Target->Samples.Num());
                bSlotFullyConsumed = bComplete && bFullyDrained;
            }

            // ── Retire slot if consumed (carry outData into next slot) ─
            if (bSlotFullyConsumed)
            {
                const FString FinishedCallerId = CurrentPlayback->CallerId;
                FAudioBuffer* FinishedBuffer = CurrentPlayback->Buffer;

                {
                    FScopeLock Lock(&BuffersMutex);
                    if (TArray<TUniquePtr<FAudioBuffer>>* List = BuffersByCaller.Find(FinishedCallerId))
                    {
                        for (int32 i = 0; i < List->Num(); ++i)
                        {
                            if ((*List)[i].Get() == FinishedBuffer)
                            {
                                List->RemoveAt(i);
                                break;
                            }
                        }
                        if (List->Num() == 0)
                        {
                            BuffersByCaller.Remove(FinishedCallerId);
                        }
                    }
                }

                CurrentPlayback.Reset();
                AsyncTask(ENamedThreads::GameThread, [this, FinishedCallerId]()
                {
                    PlaybackComplete.Broadcast(FinishedCallerId);
                });
                // Wake immediately so the next slot's samples flow
                // without the 50 ms Wait timeout.
                ConsumerWakeEvent->Trigger();
            }

            // ── Send if we have a full batch ───────────────────────────
            if (outData.Num() >= A2F_STREAMING_BATCH_SIZE)
            {
                SendOutData(false);
                if (CurrentPlayback.IsSet() || !PlaybackOrder.IsEmpty())
                {
                    ConsumerWakeEvent->Trigger();
                }
            }
        }
    });
}

void UACERESTTTSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Signal the consumer task to exit, then wait for it to actually finish
    // BEFORE handing control back to UE. This matters because the enclosing
    // actor's BP EndPlay typically fires immediately after this one and, in
    // the Alice/MetaFamily flow, Blueprint deallocates the A2F provider on
    // EndPlay. If we don't join here, the consumer might still be mid-
    // AnimateFromAudioSamples when ACE starts tearing down GPU resources,
    // causing a use-after-free in NVIDIA's DirectML DLL (nvdxgdmal64.dll).
    bIsPlaying.store(false);
    ConsumerWakeEvent->Trigger();

    if (ConsumerTaskFuture.IsValid())
    {
        ConsumerTaskFuture.Wait();
    }

    Super::EndPlay(EndPlayReason);
}

void UACERESTTTSComponent::EndTurn()
{
    bTurnEndSignaled.store(true, std::memory_order_release);
    ConsumerWakeEvent->Trigger();
}

void UACERESTTTSComponent::WakeConsumer()
{
    ConsumerWakeEvent->Trigger();
}
