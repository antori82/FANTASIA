// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WhisperTypes.h"
#include "WhisperBlueprintLibrary.generated.h"

/**
 * Static Blueprint helper functions for Whisper ASR.
 * These do not require a subsystem reference.
 */
UCLASS()
class FANTASIA_API UWhisperBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// ── Result helpers ───────────────────────────────────────────────────

	/** Get the plain full text from a transcription result */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Result",
		meta = (DisplayName = "Get Full Text", CompactNodeTitle = "FullText"))
	static FString GetFullText(const FWhisperResult& Result);

	/** Get segment count */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Result")
	static int32 GetSegmentCount(const FWhisperResult& Result);

	/** Get a specific segment by index */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Result")
	static FWhisperSegment GetSegment(const FWhisperResult& Result, int32 Index);

	/** Get total audio duration from segments */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Result")
	static float GetTotalDuration(const FWhisperResult& Result);

	/** Format result as SRT subtitle string */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Result")
	static FString FormatAsSRT(const FWhisperResult& Result);

	/** Format result as VTT subtitle string */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Result")
	static FString FormatAsVTT(const FWhisperResult& Result);

	// ── Config helpers ───────────────────────────────────────────────────

	/** Create a default transcription config */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Config",
		meta = (DisplayName = "Make Default Config"))
	static FWhisperConfig MakeDefaultConfig();

	/** Create a config tuned for real-time / low-latency use */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Config",
		meta = (DisplayName = "Make Realtime Config"))
	static FWhisperConfig MakeRealtimeConfig();

	// ── Model file helpers ───────────────────────────────────────────────

	/** Get the expected filename for a model size (e.g. "ggml-base.en.bin") */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Model")
	static FString GetModelFileName(EWhisperModelSize Size, bool bEnglishOnly = false);

	/** Check if a model file exists at the given path */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Model")
	static bool DoesModelFileExist(const FString& FilePath);

	/**
	 * Scan the model search directories for ggml-*.bin files and return
	 * info about each discovered model, parsed from the HuggingFace
	 * whisper.cpp naming convention.
	 */
	UFUNCTION(BlueprintCallable, Category = "WhisperASR|Model")
	static TArray<FWhisperModelInfo> GetAvailableModels();

	/**
	 * Parse a ggml model filename into a FWhisperModelInfo struct.
	 * The naming convention is: ggml-{size}[.en][-v{N}][-turbo][-{quant}].bin
	 */
	UFUNCTION(BlueprintPure, Category = "WhisperASR|Model")
	static FWhisperModelInfo ParseModelFileName(const FString& FilePath);

private:

	/** Internal: format seconds as HH:MM:SS,mmm for SRT */
	static FString FormatSRTTimestamp(float Seconds);

	/** Internal: format seconds as HH:MM:SS.mmm for VTT */
	static FString FormatVTTTimestamp(float Seconds);
};
