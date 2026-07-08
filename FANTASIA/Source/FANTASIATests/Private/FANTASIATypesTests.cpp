/**
 * @file FANTASIATypesTests.cpp
 * @brief Tests for FANTASIA data types: FChatTurn, FSVMParameters, FWhisperConfig,
 *        FWhisperResult, FTTSSegmentTiming, FTTSData, FElevenLabsVoiceSettings
 *        defaults, and Neo4j result cell class hierarchy.
 */

#include "Misc/AutomationTest.h"
#include "FANTASIATypes.h"
#include "ElevenLabsProtocol.h"
#include "WhisperTypes.h"
#include "LibSVM.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FChatTurnDefaults, "FANTASIA.Types.FChatTurn.Defaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FChatTurnDefaults::RunTest(const FString& Parameters)
{
	FChatTurn Turn;
	TestEqual(TEXT("Default role is USER"), Turn.role, GPTRoleType::USER);
	TestEqual(TEXT("Default content is empty"), Turn.content, FString(TEXT("")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSVMParametersDefaults, "FANTASIA.Types.FSVMParameters.Defaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FSVMParametersDefaults::RunTest(const FString& Parameters)
{
	FSVMParameters Params;
	TestEqual(TEXT("SVMType"), Params.SVMType, LibSVMTypes::C_SVC);
	TestEqual(TEXT("KernelType"), Params.KernelType, LibSVMKernels::RBF);
	TestTrue(TEXT("C"), FMath::IsNearlyEqual(Params.C, 1.0, 0.001));
	TestTrue(TEXT("gamma"), FMath::IsNearlyEqual(Params.gamma, 0.1, 0.001));
	TestTrue(TEXT("degree"), FMath::IsNearlyEqual(Params.degree, 3.0, 0.001));
	TestTrue(TEXT("coef0"), FMath::IsNearlyEqual(Params.coef0, 0.0, 0.001));
	TestTrue(TEXT("nu"), FMath::IsNearlyEqual(Params.nu, 0.5, 0.001));
	TestTrue(TEXT("svrEpsilon"), FMath::IsNearlyEqual(Params.svrEpsilon, 0.1, 0.001));
	TestTrue(TEXT("cachesize"), FMath::IsNearlyEqual(Params.cachesize, 100.0, 0.001));
	TestTrue(TEXT("epsilon"), FMath::IsNearlyEqual(Params.epsilon, 0.001, 0.0001));
	TestTrue(TEXT("shrinking"), Params.shrinking);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperConfigDefaults, "FANTASIA.Types.FWhisperConfig.Defaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperConfigDefaults::RunTest(const FString& Parameters)
{
	FWhisperConfig Config;
	TestEqual(TEXT("Language"), Config.Language, EWhisperLanguage::Auto);
	TestEqual(TEXT("Task"), Config.Task, EWhisperTask::Transcribe);
	TestEqual(TEXT("NumThreads"), Config.NumThreads, 0);
	TestEqual(TEXT("MaxSegmentLength"), Config.MaxSegmentLength, 0);
	TestFalse(TEXT("bTokenTimestamps"), Config.bTokenTimestamps);
	TestTrue(TEXT("bSuppressNonSpeech"), Config.bSuppressNonSpeech);
	TestTrue(TEXT("Temperature"), FMath::IsNearlyEqual(Config.Temperature, 0.0f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWhisperResultDefaults, "FANTASIA.Types.FWhisperResult.Defaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FWhisperResultDefaults::RunTest(const FString& Parameters)
{
	FWhisperResult Result;
	TestFalse(TEXT("bSuccess"), Result.bSuccess);
	TestTrue(TEXT("FullText empty"), Result.FullText.IsEmpty());
	TestEqual(TEXT("No segments"), Result.Segments.Num(), 0);
	TestTrue(TEXT("ProcessingTime"), FMath::IsNearlyEqual(Result.ProcessingTimeSeconds, 0.0f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTTSSegmentTimingDefaults, "FANTASIA.Types.FTTSSegmentTiming.Defaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FTTSSegmentTimingDefaults::RunTest(const FString& Parameters)
{
	FTTSSegmentTiming Seg;
	TestTrue(TEXT("Text empty"), Seg.Text.IsEmpty());
	TestTrue(TEXT("StartSeconds"), FMath::IsNearlyEqual(Seg.StartSeconds, 0.f, 0.001f));
	TestTrue(TEXT("EndSeconds"), FMath::IsNearlyEqual(Seg.EndSeconds, 0.f, 0.001f));
	TestEqual(TEXT("CharStart"), Seg.CharStart, 0);
	TestEqual(TEXT("CharEnd"), Seg.CharEnd, 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTTSDataDefaults, "FANTASIA.Types.FTTSData.Defaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FTTSDataDefaults::RunTest(const FString& Parameters)
{
	FTTSData Data;
	TestEqual(TEXT("AudioData empty"), Data.AudioData.Num(), 0);
	TestEqual(TEXT("Words empty"), Data.Words.Num(), 0);
	TestEqual(TEXT("Characters empty"), Data.Characters.Num(), 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsVoiceSettingsDefaults, "FANTASIA.Types.FElevenLabsVoiceSettings.Defaults",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsVoiceSettingsDefaults::RunTest(const FString& Parameters)
{
	FElevenLabsVoiceSettings Settings;
	TestTrue(TEXT("Stability"), FMath::IsNearlyEqual(Settings.Stability, 0.f, 0.001f));
	TestTrue(TEXT("SimilarityBoost"), FMath::IsNearlyEqual(Settings.SimilarityBoost, 0.f, 0.001f));
	TestTrue(TEXT("Style"), FMath::IsNearlyEqual(Settings.Style, 0.f, 0.001f));
	TestFalse(TEXT("bUseSpeakerBoost"), Settings.bUseSpeakerBoost);
	TestTrue(TEXT("Speed default 1.0"), FMath::IsNearlyEqual(Settings.Speed, 1.f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNeo4jCellHierarchy, "FANTASIA.Types.Neo4jCellHierarchy",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FNeo4jCellHierarchy::RunTest(const FString& Parameters)
{
	TestTrue(TEXT("Node is child of Cell"),
		UNeo4jResultCellNode::StaticClass()->IsChildOf(UNeo4jResultCell::StaticClass()));
	TestTrue(TEXT("Relationship is child of Cell"),
		UNeo4jResultCellRelationship::StaticClass()->IsChildOf(UNeo4jResultCell::StaticClass()));
	TestTrue(TEXT("Simple is child of Cell"),
		UNeo4jResultCellSimple::StaticClass()->IsChildOf(UNeo4jResultCell::StaticClass()));
	return true;
}
