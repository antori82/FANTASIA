// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WhisperTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWhisperASR, Log, All);

// ─── Language enum (subset of Whisper-supported languages) ────────────────────

UENUM(BlueprintType)
enum class EWhisperLanguage : uint8
{
	Auto		UMETA(DisplayName = "Auto-Detect"),
	English		UMETA(DisplayName = "English"),
	Spanish		UMETA(DisplayName = "Spanish"),
	French		UMETA(DisplayName = "French"),
	German		UMETA(DisplayName = "German"),
	Italian		UMETA(DisplayName = "Italian"),
	Portuguese	UMETA(DisplayName = "Portuguese"),
	Russian		UMETA(DisplayName = "Russian"),
	Chinese		UMETA(DisplayName = "Chinese"),
	Japanese	UMETA(DisplayName = "Japanese"),
	Korean		UMETA(DisplayName = "Korean"),
	Arabic		UMETA(DisplayName = "Arabic"),
	Hindi		UMETA(DisplayName = "Hindi"),
	Dutch		UMETA(DisplayName = "Dutch"),
	Turkish		UMETA(DisplayName = "Turkish"),
	Polish		UMETA(DisplayName = "Polish"),
	Swedish		UMETA(DisplayName = "Swedish"),
	Ukrainian	UMETA(DisplayName = "Ukrainian"),
};

// ─── Model size presets ──────────────────────────────────────────────────────

UENUM(BlueprintType)
enum class EWhisperModelSize : uint8
{
	Tiny		UMETA(DisplayName = "Tiny (~75MB)"),
	Base		UMETA(DisplayName = "Base (~142MB)"),
	Small		UMETA(DisplayName = "Small (~466MB)"),
	Medium		UMETA(DisplayName = "Medium (~1.5GB)"),
	Large		UMETA(DisplayName = "Large (~2.9GB)"),
};

// ─── Task type ───────────────────────────────────────────────────────────────

UENUM(BlueprintType)
enum class EWhisperTask : uint8
{
	Transcribe	UMETA(DisplayName = "Transcribe"),
	Translate	UMETA(DisplayName = "Translate to English"),
};

// ─── Status of the ASR subsystem ─────────────────────────────────────────────

UENUM(BlueprintType)
enum class EWhisperStatus : uint8
{
	Uninitialized	UMETA(DisplayName = "Uninitialized"),
	Loading			UMETA(DisplayName = "Loading Model"),
	Ready			UMETA(DisplayName = "Ready"),
	Processing		UMETA(DisplayName = "Processing Audio"),
	Error			UMETA(DisplayName = "Error"),
};

// ─── A single transcription segment ─────────────────────────────────────────

USTRUCT(BlueprintType)
struct FANTASIA_API FWhisperSegment
{
	GENERATED_BODY()

	/** Start time of this segment in seconds */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	float StartTime = 0.f;

	/** End time of this segment in seconds */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	float EndTime = 0.f;

	/** Transcribed text of this segment */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	FString Text;

	/** Confidence/probability (0..1) — average token probability */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	float Confidence = 0.f;
};

// ─── Full transcription result ───────────────────────────────────────────────

USTRUCT(BlueprintType)
struct FANTASIA_API FWhisperResult
{
	GENERATED_BODY()

	/** Whether transcription succeeded */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	bool bSuccess = false;

	/** Concatenated full text of all segments */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	FString FullText;

	/** Detected or specified language */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	FString Language;

	/** Individual timed segments */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	TArray<FWhisperSegment> Segments;

	/** Processing duration in seconds */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	float ProcessingTimeSeconds = 0.f;

	/** Error message if bSuccess is false */
	UPROPERTY(BlueprintReadOnly, Category = "WhisperASR")
	FString ErrorMessage;
};

// ─── Configuration for a transcription request ──────────────────────────────

USTRUCT(BlueprintType)
struct FANTASIA_API FWhisperConfig
{
	GENERATED_BODY()

	/** Language hint (Auto = let Whisper detect) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR")
	EWhisperLanguage Language = EWhisperLanguage::Auto;

	/** Transcribe or translate-to-English */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR")
	EWhisperTask Task = EWhisperTask::Transcribe;

	/** Number of threads for inference (0 = auto) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR", meta = (ClampMin = "0", ClampMax = "32"))
	int32 NumThreads = 0;

	/** Maximum segment length in characters (0 = unlimited) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR")
	int32 MaxSegmentLength = 0;

	/** Enable token-level timestamps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR")
	bool bTokenTimestamps = false;

	/** Initial prompt / context to guide transcription */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR")
	FString InitialPrompt;

	/** Suppress non-speech tokens */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR")
	bool bSuppressNonSpeech = true;

	/** Temperature for sampling (0 = greedy) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WhisperASR", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Temperature = 0.0f;
};

// ─── Delegates ───────────────────────────────────────────────────────────────

/** Fired when model loading completes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWhisperModelLoaded, bool, bSuccess);

/** Fired when transcription completes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWhisperTranscriptionComplete, const FWhisperResult&, Result);

/** Fired per-segment during streaming transcription */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWhisperSegmentReady, const FWhisperSegment&, Segment);

/** Fired when status changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWhisperStatusChanged, EWhisperStatus, NewStatus);
