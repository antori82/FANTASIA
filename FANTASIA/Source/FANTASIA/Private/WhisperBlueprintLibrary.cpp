// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#include "WhisperBlueprintLibrary.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"

// ─────────────────────────────────────────────────────────────────────────────
// Result helpers
// ─────────────────────────────────────────────────────────────────────────────

FString UWhisperBlueprintLibrary::GetFullText(const FWhisperResult& Result)
{
	return Result.FullText;
}

int32 UWhisperBlueprintLibrary::GetSegmentCount(const FWhisperResult& Result)
{
	return Result.Segments.Num();
}

FWhisperSegment UWhisperBlueprintLibrary::GetSegment(const FWhisperResult& Result, int32 Index)
{
	if (Result.Segments.IsValidIndex(Index))
	{
		return Result.Segments[Index];
	}
	return FWhisperSegment();
}

float UWhisperBlueprintLibrary::GetTotalDuration(const FWhisperResult& Result)
{
	if (Result.Segments.Num() > 0)
	{
		return Result.Segments.Last().EndTime;
	}
	return 0.f;
}

FString UWhisperBlueprintLibrary::FormatAsSRT(const FWhisperResult& Result)
{
	FString Output;

	for (int32 i = 0; i < Result.Segments.Num(); ++i)
	{
		const FWhisperSegment& Seg = Result.Segments[i];

		// SRT index (1-based)
		Output += FString::Printf(TEXT("%d\n"), i + 1);

		// Timestamps: HH:MM:SS,mmm --> HH:MM:SS,mmm
		Output += FString::Printf(TEXT("%s --> %s\n"),
			*FormatSRTTimestamp(Seg.StartTime),
			*FormatSRTTimestamp(Seg.EndTime));

		// Text
		Output += Seg.Text + TEXT("\n\n");
	}

	return Output;
}

FString UWhisperBlueprintLibrary::FormatAsVTT(const FWhisperResult& Result)
{
	FString Output = TEXT("WEBVTT\n\n");

	for (int32 i = 0; i < Result.Segments.Num(); ++i)
	{
		const FWhisperSegment& Seg = Result.Segments[i];

		// Timestamps: HH:MM:SS.mmm --> HH:MM:SS.mmm
		Output += FString::Printf(TEXT("%s --> %s\n"),
			*FormatVTTTimestamp(Seg.StartTime),
			*FormatVTTTimestamp(Seg.EndTime));

		Output += Seg.Text + TEXT("\n\n");
	}

	return Output;
}

// ─────────────────────────────────────────────────────────────────────────────
// Config helpers
// ─────────────────────────────────────────────────────────────────────────────

FWhisperConfig UWhisperBlueprintLibrary::MakeDefaultConfig()
{
	FWhisperConfig Config;
	Config.Language = EWhisperLanguage::Auto;
	Config.Task = EWhisperTask::Transcribe;
	Config.NumThreads = 0; // auto
	Config.bSuppressNonSpeech = true;
	Config.Temperature = 0.0f;
	return Config;
}

FWhisperConfig UWhisperBlueprintLibrary::MakeRealtimeConfig()
{
	FWhisperConfig Config;
	Config.Language = EWhisperLanguage::English; // skip detection for speed
	Config.Task = EWhisperTask::Transcribe;
	Config.NumThreads = 4;
	Config.bSuppressNonSpeech = true;
	Config.Temperature = 0.0f;
	Config.MaxSegmentLength = 0;
	Config.bTokenTimestamps = false;
	return Config;
}

// ─────────────────────────────────────────────────────────────────────────────
// Model file helpers
// ─────────────────────────────────────────────────────────────────────────────

FString UWhisperBlueprintLibrary::GetModelFileName(EWhisperModelSize Size, bool bEnglishOnly)
{
	FString SizeName;
	switch (Size)
	{
	case EWhisperModelSize::Tiny:   SizeName = TEXT("tiny");   break;
	case EWhisperModelSize::Base:   SizeName = TEXT("base");   break;
	case EWhisperModelSize::Small:  SizeName = TEXT("small");  break;
	case EWhisperModelSize::Medium: SizeName = TEXT("medium"); break;
	case EWhisperModelSize::Large:  SizeName = TEXT("large");  break;
	}

	if (bEnglishOnly && Size != EWhisperModelSize::Large)
	{
		return FString::Printf(TEXT("ggml-%s.en.bin"), *SizeName);
	}

	return FString::Printf(TEXT("ggml-%s.bin"), *SizeName);
}

bool UWhisperBlueprintLibrary::DoesModelFileExist(const FString& FilePath)
{
	return FPaths::FileExists(FilePath);
}

// ─────────────────────────────────────────────────────────────────────────────
// Timestamp formatting
// ─────────────────────────────────────────────────────────────────────────────

FString UWhisperBlueprintLibrary::FormatSRTTimestamp(float Seconds)
{
	int32 TotalMs = FMath::RoundToInt(Seconds * 1000.0f);
	int32 Ms  = TotalMs % 1000;
	int32 Sec = (TotalMs / 1000) % 60;
	int32 Min = (TotalMs / 60000) % 60;
	int32 Hr  = TotalMs / 3600000;

	return FString::Printf(TEXT("%02d:%02d:%02d,%03d"), Hr, Min, Sec, Ms);
}

FString UWhisperBlueprintLibrary::FormatVTTTimestamp(float Seconds)
{
	int32 TotalMs = FMath::RoundToInt(Seconds * 1000.0f);
	int32 Ms  = TotalMs % 1000;
	int32 Sec = (TotalMs / 1000) % 60;
	int32 Min = (TotalMs / 60000) % 60;
	int32 Hr  = TotalMs / 3600000;

	return FString::Printf(TEXT("%02d:%02d:%02d.%03d"), Hr, Min, Sec, Ms);
}
