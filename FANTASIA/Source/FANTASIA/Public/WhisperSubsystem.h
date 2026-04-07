// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WhisperTypes.h"
#include "WhisperSubsystem.generated.h"

// Forward-declare whisper.cpp opaque type
struct whisper_context;

/**
 * UWhisperSubsystem
 *
 * Game-instance subsystem that manages the Whisper ASR model lifecycle
 * and provides transcription APIs exposed to Blueprints.
 *
 * Usage (Blueprint):
 *   1. Call LoadModel with a path to a .bin GGML model file.
 *   2. Wait for OnModelLoaded to fire with bSuccess=true.
 *   3. Call TranscribeAudioFile or TranscribeAudioData.
 *   4. Receive results via OnTranscriptionComplete.
 */
UCLASS()
class FANTASIA_API UWhisperSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// ── Lifecycle ─────────────────────────────────────────────────────────

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// ── Delegates (Blueprint-assignable) ──────────────────────────────────

	/** Broadcast when model loading finishes (async) */
	UPROPERTY(BlueprintAssignable, Category = "WhisperASR|Events")
	FOnWhisperModelLoaded OnModelLoaded;

	/** Broadcast when a full transcription completes */
	UPROPERTY(BlueprintAssignable, Category = "WhisperASR|Events")
	FOnWhisperTranscriptionComplete OnTranscriptionComplete;

	/** Broadcast per segment during transcription */
	UPROPERTY(BlueprintAssignable, Category = "WhisperASR|Events")
	FOnWhisperSegmentReady OnSegmentReady;

	/** Broadcast when internal status changes */
	UPROPERTY(BlueprintAssignable, Category = "WhisperASR|Events")
	FOnWhisperStatusChanged OnStatusChanged;

	// ── Model management ─────────────────────────────────────────────────

	/**
	 * Load a Whisper GGML model from disk (async, fires OnModelLoaded).
	 *
	 * @param ModelFilePath  Absolute path to a .bin ggml model file.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Model")
	void LoadModel(const FString& ModelFilePath);

	/**
	 * Load a model using a preset size.  Looks for ggml-<size>.bin in
	 * the plugin's Content/Models directory.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Model")
	void LoadModelBySize(EWhisperModelSize Size);

	/**
	 * Load a model by filename (e.g. "ggml-base.en-q8_0.bin").
	 * Searches the standard model directories for a matching file.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Model")
	void LoadModelByName(const FString& ModelFileName);

	/** Unload the currently loaded model and free memory */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Model")
	void UnloadModel();

	/** Returns true if a model is loaded and ready */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Model")
	bool IsModelLoaded() const;

	/** Returns the current subsystem status */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Model")
	EWhisperStatus GetStatus() const { return CurrentStatus; }

	/** Returns true if the plugin was compiled with CUDA GPU support */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Model")
	static bool IsGPUSupported();

	/**
	 * When true and GPU support is compiled in, models are loaded onto the GPU.
	 * Set this BEFORE calling LoadModel / LoadModelBySize / LoadModelByName.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Model")
	bool bUseGPU = true;

	/** GPU device index (0 = first CUDA device). Only relevant when bUseGPU is true. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR|Model")
	int32 GPUDeviceIndex = 0;

	// ── Transcription (file-based) ───────────────────────────────────────

	/**
	 * Transcribe a WAV audio file on disk (async, fires OnTranscriptionComplete).
	 * The file must be 16-bit PCM WAV, mono, 16 kHz (Whisper's native format).
	 *
	 * @param WavFilePath  Path to the .wav file.
	 * @param Config       Transcription parameters.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Transcription")
	void TranscribeAudioFile(const FString& WavFilePath, FWhisperConfig Config);

	// ── Transcription (raw PCM data) ─────────────────────────────────────

	/**
	 * Transcribe raw PCM float samples (async, fires OnTranscriptionComplete).
	 * Audio must be mono, 16 kHz, float32 in range [-1, 1].
	 *
	 * @param PCMData  Array of float samples.
	 * @param Config   Transcription parameters.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Transcription")
	void TranscribeAudioData(const TArray<float>& PCMData, FWhisperConfig Config);

	// ── Transcription (synchronous, for C++ callers) ─────────────────────

	/**
	 * Blocking transcription — runs on calling thread.
	 * Prefer the async versions above from Blueprints.
	 */
	FWhisperResult TranscribeSync(const TArray<float>& PCMData, const FWhisperConfig& Config);

	// ── Audio utilities ──────────────────────────────────────────────────

	/**
	 * Load a WAV file and return its samples as float PCM.
	 * Automatically resamples to 16 kHz mono.
	 *
	 * @param WavFilePath  Path to the .wav file.
	 * @param OutSamples   Output float samples.
	 * @return             True on success.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Audio")
	bool LoadWavFile(const FString& WavFilePath, TArray<float>& OutSamples);

	/**
	 * Convert 16-bit integer PCM data to float [-1,1] range.
	 *
	 * @param Int16Data    Raw 16-bit PCM bytes.
	 * @param OutSamples   Output float samples.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Audio")
	static void ConvertInt16ToFloat(const TArray<uint8>& Int16Data, TArray<float>& OutSamples);

	/**
	 * Get the expected Whisper sample rate (16000 Hz).
	 */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Audio")
	static int32 GetWhisperSampleRate() { return 16000; }

	// ── Utility ──────────────────────────────────────────────────────────

	/** Convert language enum to the ISO code string Whisper expects */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Utility")
	static FString LanguageToString(EWhisperLanguage Language);

	/** Get the default model directory (plugin Content/Models) */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Utility")
	static FString GetDefaultModelDirectory();

private:

	/** Raw whisper.cpp context handle */
	whisper_context* WhisperCtx = nullptr;

	/** Current operational status */
	EWhisperStatus CurrentStatus = EWhisperStatus::Uninitialized;

	/** Mutex protecting whisper_full — it is NOT thread-safe on the same context */
	FCriticalSection InferenceMutex;

	/** Set during shutdown to prevent new requests and skip async callbacks */
	FThreadSafeBool bShuttingDown;

	/** Thread-safe status setter that broadcasts delegate */
	void SetStatus(EWhisperStatus NewStatus);

	/** Internal: run full-params inference and build result */
	FWhisperResult RunInference(const TArray<float>& Samples, const FWhisperConfig& Config);
};
