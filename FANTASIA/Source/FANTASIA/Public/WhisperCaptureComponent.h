// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WhisperTypes.h"

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4456 4457 4458 4459 4244 4267 4800 4756 4100 4127 4189 4706 4702 4310 4305 4242 4389)
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#include "AudioCapture.h"

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#include "WhisperCaptureComponent.generated.h"

// Forward declarations
class UWhisperSubsystem;

/**
 * UWhisperCaptureComponent
 *
 * Actor component that opens the system microphone via UE 5.6's
 * Audio::FAudioCapture, resamples to 16 kHz mono float, buffers audio,
 * and feeds it to the Whisper subsystem for transcription.
 *
 * Drop onto any Actor. Call StartCapture / StopCapture from Blueprints.
 * Results arrive via OnCaptureTranscriptionComplete (and optionally
 * per-segment via OnStreamingSegment in streaming mode).
 */
UCLASS(ClassGroup = (WhisperASR), meta = (BlueprintSpawnableComponent,
	DisplayName = "Whisper Audio Capture"))
class WHISPERASR_API UWhisperCaptureComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UWhisperCaptureComponent();
	virtual ~UWhisperCaptureComponent();

	// ── Configuration ────────────────────────────────────────────────────

	/** Transcription config used for captured audio */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Capture")
	FWhisperConfig TranscriptionConfig;

	/**
	 * If true, automatically transcribe every N seconds of buffered audio
	 * while capture is active (chunked streaming mode).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Capture")
	bool bStreamingMode = false;

	/** Seconds between streaming transcriptions (if bStreamingMode) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Capture",
		meta = (EditCondition = "bStreamingMode", ClampMin = "1.0", ClampMax = "30.0"))
	float StreamingIntervalSeconds = 5.0f;

	/**
	 * Overlap in seconds between consecutive chunks. The last N seconds
	 * of each chunk are kept and prepended to the next one. This prevents
	 * words at chunk boundaries from being cut in half and garbled.
	 * Recommended: 1.0–2.0 seconds.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Capture",
		meta = (EditCondition = "bStreamingMode", ClampMin = "0.0", ClampMax = "5.0"))
	float StreamingOverlapSeconds = 1.0f;

	/**
	 * Maximum buffer duration in seconds. Oldest samples are discarded
	 * when the buffer exceeds this length.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Capture",
		meta = (ClampMin = "1.0", ClampMax = "300.0"))
	float MaxBufferDurationSeconds = 30.0f;

	/**
	 * Minimum peak amplitude to consider as speech (voice activity gate).
	 * Audio chunks where no sample exceeds this value are discarded as silence.
	 * Your mic showed peak ~0.09 during speech and ~0.004 during silence,
	 * so 0.01 is a good default. Set to 0.0 to disable.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Capture",
		meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VadEnergyThreshold = 0.01f;

	/**
	 * Index of the audio input device to use.
	 * -1 = system default microphone.
	 * Use GetAvailableInputDevices to enumerate options.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Capture")
	int32 AudioDeviceIndex = -1;

	// ── Events ───────────────────────────────────────────────────────────

	/** Fired when captured audio finishes transcription */
	UPROPERTY(BlueprintAssignable, Category = "WhisperASR|Capture|Events")
	FOnWhisperTranscriptionComplete OnCaptureTranscriptionComplete;

	/** Fired per-segment during streaming transcription */
	UPROPERTY(BlueprintAssignable, Category = "WhisperASR|Capture|Events")
	FOnWhisperSegmentReady OnStreamingSegment;

	// ── Controls ─────────────────────────────────────────────────────────

	/** Open the microphone and begin capturing audio. Returns false if device fails to open. */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Capture")
	bool StartCapture();

	/** Stop the microphone and transcribe whatever is in the buffer */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Capture")
	void StopCapture();

	/** Stop the microphone and discard the buffer (no transcription) */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Capture")
	void CancelCapture();

	/** Manually trigger transcription of the current buffer */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Capture")
	void TranscribeBuffer();

	/** Clear the audio buffer without transcribing */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Capture")
	void ClearBuffer();

	/** Check if the microphone is currently active */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Capture")
	bool IsCapturing() const { return bIsCapturing; }

	/** Current buffer duration in seconds */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Capture")
	float GetBufferDuration() const;

	/** Current RMS audio level (0–1) — useful for VU meter widgets */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Capture")
	float GetCurrentAudioLevel() const;

	/**
	 * Enumerate available audio input (microphone) devices.
	 * Returns display names; the array index is the DeviceIndex.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Capture")
	static TArray<FString> GetAvailableInputDevices();

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

private:

	// ── Audio capture internals ──────────────────────────────────────────

	/** Platform audio capture handle (UE 5.6 AudioCaptureCore) */
	TUniquePtr<Audio::FAudioCapture> AudioCapture;

	/** Sample rate reported by the opened device */
	int32 DeviceSampleRate = 0;

	/** Channel count reported by the opened device */
	int32 DeviceNumChannels = 0;

	/** Opens the audio capture device; returns true on success */
	bool OpenCaptureDevice();

	/** Closes and releases the audio capture device */
	void CloseCaptureDevice();

	// ── Buffer management ────────────────────────────────────────────────

	/**
	 * The main audio buffer: 16 kHz mono float32.
	 * Written from the audio callback thread, read from the game thread.
	 * Access is serialized through BufferCritSection.
	 */
	TArray<float> AudioBuffer;

	/** Protects AudioBuffer from concurrent audio-thread / game-thread access */
	mutable FCriticalSection BufferCritSection;

	/** Tracks whether a transcription is currently in-flight */
	FThreadSafeBool bTranscriptionInFlight;

	bool bIsCapturing = false;
	float StreamingTimer = 0.f;

	/** Whether the previous tick interval detected speech */
	bool bWasSpeaking = false;

	/** Accumulated result across streaming intervals during speech.
	 *  OnCaptureTranscriptionComplete fires with this when silence is detected. */
	FWhisperResult AccumulatedResult;

	/** Atomic so GetCurrentAudioLevel() is safe from any thread */
	FThreadSafeCounter CurrentRMSLevelFixed; // stored as int = value * 10000

	void SetRMSLevel(float Value);
	float GetRMSLevel() const;

	/** Enforce MaxBufferDurationSeconds (caller must hold BufferCritSection) */
	void TrimBufferLocked();

	/** Compute RMS energy of the last N samples */
	static float ComputeRMS(const float* Samples, int32 Count);

	// ── Resampling state ─────────────────────────────────────────────────

	/**
	 * Fractional sample accumulator for the linear resampler.
	 * Persists between callbacks so we don't drift.
	 */
	double ResamplePhase = 0.0;

	/**
	 * Resample + mix to mono in one pass.
	 * Appends output to OutBuffer. Caller must hold BufferCritSection.
	 */
	void ResampleAndMixToMono(const float* InAudio, int32 NumFrames,
		int32 NumChannels, int32 SrcRate, TArray<float>& OutBuffer);

	// ── Delegate handlers ────────────────────────────────────────────────

	UFUNCTION()
	void HandleTranscriptionResult(const FWhisperResult& Result);

	UFUNCTION()
	void HandleSegmentReady(const FWhisperSegment& Segment);
};
