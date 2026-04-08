/**
 * @file WhisperBlueprintLibraryTests.cpp
 * @brief Tests for UWhisperBlueprintLibrary: result accessors, SRT/VTT subtitle
 *        formatting, config factory helpers, and model file name parsing.
 */

#include "Misc/AutomationTest.h"
#include "WhisperBlueprintLibrary.h"
#include "WhisperTypes.h"

/**
 * @brief Creates a sample FWhisperResult with two segments for use in tests.
 * @return A successful FWhisperResult containing two timed segments.
 */
static FWhisperResult MakeTestResult()
{
	FWhisperResult Result;
	Result.bSuccess = true;
	Result.FullText = TEXT("Hello world. How are you?");
	Result.Language = TEXT("en");
	Result.ProcessingTimeSeconds = 1.5f;

	FWhisperSegment Seg1;
	Seg1.StartTime = 0.0f;
	Seg1.EndTime = 1.5f;
	Seg1.Text = TEXT("Hello world.");
	Seg1.Confidence = 0.95f;

	FWhisperSegment Seg2;
	Seg2.StartTime = 1.5f;
	Seg2.EndTime = 3.0f;
	Seg2.Text = TEXT("How are you?");
	Seg2.Confidence = 0.88f;

	Result.Segments.Add(Seg1);
	Result.Segments.Add(Seg2);
	return Result;
}

// ============================================================================
// Result Helpers
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperGetFullText, "FANTASIA.WhisperBlueprintLibrary.GetFullText",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperGetFullText::RunTest(const FString& Parameters)
{
	FWhisperResult Result = MakeTestResult();
	TestEqual(TEXT("Full text"), UWhisperBlueprintLibrary::GetFullText(Result), Result.FullText);

	FWhisperResult Empty;
	TestTrue(TEXT("Empty result"), UWhisperBlueprintLibrary::GetFullText(Empty).IsEmpty());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperGetSegmentCount, "FANTASIA.WhisperBlueprintLibrary.GetSegmentCount",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperGetSegmentCount::RunTest(const FString& Parameters)
{
	TestEqual(TEXT("Count"), UWhisperBlueprintLibrary::GetSegmentCount(MakeTestResult()), 2);
	TestEqual(TEXT("Empty"), UWhisperBlueprintLibrary::GetSegmentCount(FWhisperResult()), 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperGetSegment, "FANTASIA.WhisperBlueprintLibrary.GetSegment",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperGetSegment::RunTest(const FString& Parameters)
{
	FWhisperResult Result = MakeTestResult();
	FWhisperSegment Seg = UWhisperBlueprintLibrary::GetSegment(Result, 0);
	TestEqual(TEXT("Seg 0 text"), Seg.Text, FString(TEXT("Hello world.")));

	// Invalid index returns default segment
	FWhisperSegment Invalid = UWhisperBlueprintLibrary::GetSegment(Result, 99);
	TestTrue(TEXT("Invalid text empty"), Invalid.Text.IsEmpty());
	TestTrue(TEXT("Invalid start 0"), FMath::IsNearlyEqual(Invalid.StartTime, 0.0f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperGetTotalDuration, "FANTASIA.WhisperBlueprintLibrary.GetTotalDuration",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperGetTotalDuration::RunTest(const FString& Parameters)
{
	TestTrue(TEXT("Duration"), FMath::IsNearlyEqual(
		UWhisperBlueprintLibrary::GetTotalDuration(MakeTestResult()), 3.0f, 0.001f));
	TestTrue(TEXT("Empty"), FMath::IsNearlyEqual(
		UWhisperBlueprintLibrary::GetTotalDuration(FWhisperResult()), 0.0f, 0.001f));
	return true;
}

// ============================================================================
// SRT / VTT Formatting
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperFormatSRT, "FANTASIA.WhisperBlueprintLibrary.FormatAsSRT",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperFormatSRT::RunTest(const FString& Parameters)
{
	FWhisperResult Result = MakeTestResult();
	FString SRT = UWhisperBlueprintLibrary::FormatAsSRT(Result);

	// 1-based index
	TestTrue(TEXT("Starts with 1"), SRT.StartsWith(TEXT("1\n")));
	// Comma separator in timestamps
	TestTrue(TEXT("Comma separator"), SRT.Contains(TEXT("00:00:00,000")));
	// Contains arrow
	TestTrue(TEXT("Arrow"), SRT.Contains(TEXT(" --> ")));
	// Contains segment text
	TestTrue(TEXT("Text"), SRT.Contains(TEXT("Hello world.")));

	// Empty result
	FString EmptySRT = UWhisperBlueprintLibrary::FormatAsSRT(FWhisperResult());
	TestTrue(TEXT("Empty SRT"), EmptySRT.IsEmpty());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperFormatVTT, "FANTASIA.WhisperBlueprintLibrary.FormatAsVTT",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperFormatVTT::RunTest(const FString& Parameters)
{
	FWhisperResult Result = MakeTestResult();
	FString VTT = UWhisperBlueprintLibrary::FormatAsVTT(Result);

	// Header
	TestTrue(TEXT("VTT header"), VTT.StartsWith(TEXT("WEBVTT\n\n")));
	// Dot separator
	TestTrue(TEXT("Dot separator"), VTT.Contains(TEXT("00:00:00.000")));
	// Contains text
	TestTrue(TEXT("Text"), VTT.Contains(TEXT("How are you?")));

	// Empty result still has header
	FString EmptyVTT = UWhisperBlueprintLibrary::FormatAsVTT(FWhisperResult());
	TestEqual(TEXT("Empty VTT"), EmptyVTT, FString(TEXT("WEBVTT\n\n")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperSRTTimestampHour, "FANTASIA.WhisperBlueprintLibrary.SRT.HourTimestamp",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperSRTTimestampHour::RunTest(const FString& Parameters)
{
	FWhisperResult Result;
	Result.bSuccess = true;
	FWhisperSegment Seg;
	Seg.StartTime = 3661.5f; // 1h 1m 1s 500ms
	Seg.EndTime = 3662.0f;
	Seg.Text = TEXT("test");
	Result.Segments.Add(Seg);

	FString SRT = UWhisperBlueprintLibrary::FormatAsSRT(Result);
	TestTrue(TEXT("Hour timestamp"), SRT.Contains(TEXT("01:01:01,500")));
	return true;
}

// ============================================================================
// Config Helpers
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperMakeDefaultConfig, "FANTASIA.WhisperBlueprintLibrary.MakeDefaultConfig",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperMakeDefaultConfig::RunTest(const FString& Parameters)
{
	FWhisperConfig Config = UWhisperBlueprintLibrary::MakeDefaultConfig();
	TestEqual(TEXT("Language"), Config.Language, EWhisperLanguage::Auto);
	TestEqual(TEXT("Task"), Config.Task, EWhisperTask::Transcribe);
	TestEqual(TEXT("NumThreads"), Config.NumThreads, 0);
	TestTrue(TEXT("SuppressNonSpeech"), Config.bSuppressNonSpeech);
	TestTrue(TEXT("Temperature"), FMath::IsNearlyEqual(Config.Temperature, 0.0f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperMakeRealtimeConfig, "FANTASIA.WhisperBlueprintLibrary.MakeRealtimeConfig",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperMakeRealtimeConfig::RunTest(const FString& Parameters)
{
	FWhisperConfig Config = UWhisperBlueprintLibrary::MakeRealtimeConfig();
	TestEqual(TEXT("Language"), Config.Language, EWhisperLanguage::English);
	int32 ExpectedThreads = FMath::Clamp(FPlatformMisc::NumberOfCores() / 2, 2, 8);
	TestEqual(TEXT("NumThreads"), Config.NumThreads, ExpectedThreads);
	TestTrue(TEXT("SuppressNonSpeech"), Config.bSuppressNonSpeech);
	return true;
}

// ============================================================================
// Model File Names
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperGetModelFileName, "FANTASIA.WhisperBlueprintLibrary.GetModelFileName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperGetModelFileName::RunTest(const FString& Parameters)
{
	TestEqual(TEXT("Tiny"), UWhisperBlueprintLibrary::GetModelFileName(EWhisperModelSize::Tiny),
		FString(TEXT("ggml-tiny.bin")));
	TestEqual(TEXT("Base"), UWhisperBlueprintLibrary::GetModelFileName(EWhisperModelSize::Base),
		FString(TEXT("ggml-base.bin")));
	TestEqual(TEXT("Small EN"), UWhisperBlueprintLibrary::GetModelFileName(EWhisperModelSize::Small, true),
		FString(TEXT("ggml-small.en.bin")));
	TestEqual(TEXT("Medium"), UWhisperBlueprintLibrary::GetModelFileName(EWhisperModelSize::Medium),
		FString(TEXT("ggml-medium.bin")));
	// Large ignores bEnglishOnly
	TestEqual(TEXT("Large EN ignored"), UWhisperBlueprintLibrary::GetModelFileName(EWhisperModelSize::Large, true),
		FString(TEXT("ggml-large.bin")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperParseModelFileName, "FANTASIA.WhisperBlueprintLibrary.ParseModelFileName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperParseModelFileName::RunTest(const FString& Parameters)
{
	// Simple model
	FWhisperModelInfo Info1 = UWhisperBlueprintLibrary::ParseModelFileName(TEXT("/path/ggml-base.bin"));
	TestEqual(TEXT("Size"), Info1.Size, FString(TEXT("base")));
	TestFalse(TEXT("Not EN"), Info1.bEnglishOnly);
	TestTrue(TEXT("No version"), Info1.Version.IsEmpty());
	TestTrue(TEXT("No quant"), Info1.Quantization.IsEmpty());

	// English model
	FWhisperModelInfo Info2 = UWhisperBlueprintLibrary::ParseModelFileName(TEXT("/path/ggml-base.en.bin"));
	TestTrue(TEXT("EN"), Info2.bEnglishOnly);
	TestEqual(TEXT("Size"), Info2.Size, FString(TEXT("base")));

	// Complex model with version + turbo + quantization
	FWhisperModelInfo Info3 = UWhisperBlueprintLibrary::ParseModelFileName(TEXT("/path/ggml-large-v3-turbo-q5_0.bin"));
	TestEqual(TEXT("Size"), Info3.Size, FString(TEXT("large")));
	TestEqual(TEXT("Version"), Info3.Version, FString(TEXT("v3-turbo")));
	TestEqual(TEXT("Quant"), Info3.Quantization, FString(TEXT("Q5_0")));
	TestFalse(TEXT("Not EN"), Info3.bEnglishOnly);

	// Display name capitalization
	TestTrue(TEXT("Display starts with Large"), Info3.DisplayName.StartsWith(TEXT("Large")));
	return true;
}
