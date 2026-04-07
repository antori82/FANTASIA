// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#include "WhisperBlueprintLibrary.h"
#include "WhisperSubsystem.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
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
	Config.NumThreads = FMath::Clamp(FPlatformMisc::NumberOfCores() / 2, 2, 8);
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
// Dynamic model scanning
// ─────────────────────────────────────────────────────────────────────────────

FWhisperModelInfo UWhisperBlueprintLibrary::ParseModelFileName(const FString& FilePath)
{
	FWhisperModelInfo Info;
	Info.FilePath = FilePath;
	Info.FileName = FPaths::GetCleanFilename(FilePath);

	// Expected pattern: ggml-{size}[.en][-v{N}][-turbo][-{quant}].bin
	// Examples: ggml-base.bin, ggml-base.en.bin, ggml-large-v3-turbo-q5_0.bin

	FString Stem = FPaths::GetBaseFilename(Info.FileName); // strip .bin
	if (!Stem.StartsWith(TEXT("ggml-")))
	{
		Info.DisplayName = Stem;
		return Info;
	}

	// Remove "ggml-" prefix
	FString Body = Stem.Mid(5);

	// Check for .en suffix (English-only) — appears right after size
	// e.g. "base.en", "base.en-q8_0"
	Info.bEnglishOnly = Body.Contains(TEXT(".en"));
	if (Info.bEnglishOnly)
	{
		Body.ReplaceInline(TEXT(".en"), TEXT(""));
	}

	// Split on '-' to extract parts
	TArray<FString> Parts;
	Body.ParseIntoArray(Parts, TEXT("-"), true);

	// First part is always the size
	if (Parts.Num() > 0)
	{
		Info.Size = Parts[0]; // tiny, base, small, medium, large
	}

	// Remaining parts are version tags, "turbo", or quantization
	// Version: starts with "v" followed by a digit (v1, v2, v3)
	// Quantization: matches q{digit}_{digit} pattern (q5_0, q5_1, q8_0)
	// Turbo: literal "turbo"
	TArray<FString> VersionParts;
	for (int32 i = 1; i < Parts.Num(); ++i)
	{
		const FString& Part = Parts[i];

		if (Part.StartsWith(TEXT("q")) && Part.Contains(TEXT("_")))
		{
			Info.Quantization = Part.ToUpper();
		}
		else
		{
			// Version segment: v1, v2, v3, turbo, etc.
			VersionParts.Add(Part);
		}
	}

	if (VersionParts.Num() > 0)
	{
		Info.Version = FString::Join(VersionParts, TEXT("-"));
	}

	// Build display name: "Base", "Large V3 Turbo Q5_0", "Small English Q8_0"
	FString Display = Info.Size;
	// Capitalize first letter
	if (Display.Len() > 0)
	{
		Display[0] = FChar::ToUpper(Display[0]);
	}

	if (!Info.Version.IsEmpty())
	{
		FString VersionDisplay = Info.Version;
		// Capitalize version tokens (v3 -> V3, turbo -> Turbo)
		TArray<FString> VerTokens;
		VersionDisplay.ParseIntoArray(VerTokens, TEXT("-"), true);
		for (FString& Token : VerTokens)
		{
			if (Token.Len() > 0)
			{
				Token[0] = FChar::ToUpper(Token[0]);
			}
		}
		Display += TEXT(" ") + FString::Join(VerTokens, TEXT(" "));
	}

	if (Info.bEnglishOnly)
	{
		Display += TEXT(" English");
	}

	if (!Info.Quantization.IsEmpty())
	{
		Display += TEXT(" ") + Info.Quantization;
	}

	Info.DisplayName = Display;
	return Info;
}

TArray<FWhisperModelInfo> UWhisperBlueprintLibrary::GetAvailableModels()
{
	TArray<FWhisperModelInfo> Results;

	// Locate the FANTASIA plugin base directory
	FString PluginDir;
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("FANTASIA"));
	if (Plugin.IsValid())
	{
		PluginDir = Plugin->GetBaseDir();
	}
	else
	{
		PluginDir = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("FANTASIA"));
	}

	// Collect all directories to scan (same priority order as GetDefaultModelDirectory)
	TArray<FString> SearchDirs;

	// 1. Plugin Resources/ folder
	SearchDirs.Add(FPaths::Combine(PluginDir, TEXT("Resources")));

	// 2. Plugin Content/Models/
	SearchDirs.Add(FPaths::Combine(PluginDir, TEXT("Content"), TEXT("Models")));

	// 3. Project Content/WhisperModels/
	SearchDirs.Add(FPaths::Combine(FPaths::ProjectContentDir(), TEXT("WhisperModels")));

	TSet<FString> SeenFileNames; // avoid duplicates across directories

	for (const FString& Dir : SearchDirs)
	{
		if (!FPaths::DirectoryExists(Dir))
		{
			continue;
		}

		TArray<FString> FoundFiles;
		IFileManager::Get().FindFiles(FoundFiles, *FPaths::Combine(Dir, TEXT("ggml-*.bin")), true, false);

		for (const FString& File : FoundFiles)
		{
			if (SeenFileNames.Contains(File))
			{
				continue;
			}
			SeenFileNames.Add(File);

			FString FullPath = FPaths::Combine(Dir, File);
			FWhisperModelInfo Info = ParseModelFileName(FullPath);
			Results.Add(Info);
		}
	}

	// Sort by size order (tiny < base < small < medium < large), then by version, then quantization
	Results.Sort([](const FWhisperModelInfo& A, const FWhisperModelInfo& B)
	{
		static const TArray<FString> SizeOrder = {
			TEXT("tiny"), TEXT("base"), TEXT("small"), TEXT("medium"), TEXT("large")
		};
		int32 IdxA = SizeOrder.IndexOfByKey(A.Size);
		int32 IdxB = SizeOrder.IndexOfByKey(B.Size);
		if (IdxA == INDEX_NONE) IdxA = SizeOrder.Num();
		if (IdxB == INDEX_NONE) IdxB = SizeOrder.Num();

		if (IdxA != IdxB) return IdxA < IdxB;
		if (A.Version != B.Version) return A.Version < B.Version;
		if (A.bEnglishOnly != B.bEnglishOnly) return !A.bEnglishOnly;
		return A.Quantization < B.Quantization;
	});

	return Results;
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
