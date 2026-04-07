#include "Misc/AutomationTest.h"
#include "MathUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLinspaceTwoPoints, "FANTASIA.MathUtilities.Linspace.TwoPoints",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FLinspaceTwoPoints::RunTest(const FString& Parameters)
{
	std::vector<float> Result = Linspace(0.0f, 1.0f, 2);
	TestEqual(TEXT("Size"), (int32)Result.size(), 2);
	TestTrue(TEXT("Start"), FMath::IsNearlyEqual(Result[0], 0.0f, 0.001f));
	TestTrue(TEXT("End"), FMath::IsNearlyEqual(Result[1], 1.0f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLinspaceThreePoints, "FANTASIA.MathUtilities.Linspace.ThreePoints",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FLinspaceThreePoints::RunTest(const FString& Parameters)
{
	std::vector<float> Result = Linspace(0.0f, 10.0f, 3);
	TestEqual(TEXT("Size"), (int32)Result.size(), 3);
	TestTrue(TEXT("Start"), FMath::IsNearlyEqual(Result[0], 0.0f, 0.001f));
	TestTrue(TEXT("Mid"), FMath::IsNearlyEqual(Result[1], 5.0f, 0.001f));
	TestTrue(TEXT("End"), FMath::IsNearlyEqual(Result[2], 10.0f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLinspaceFivePoints, "FANTASIA.MathUtilities.Linspace.FivePoints",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FLinspaceFivePoints::RunTest(const FString& Parameters)
{
	std::vector<float> Result = Linspace(0.0f, 4.0f, 5);
	TestEqual(TEXT("Size"), (int32)Result.size(), 5);
	for (int i = 0; i < 5; i++)
	{
		TestTrue(*FString::Printf(TEXT("Point %d"), i),
			FMath::IsNearlyEqual(Result[i], (float)i, 0.001f));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLinspaceNegativeRange, "FANTASIA.MathUtilities.Linspace.NegativeRange",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FLinspaceNegativeRange::RunTest(const FString& Parameters)
{
	std::vector<float> Result = Linspace(-5.0f, 5.0f, 3);
	TestEqual(TEXT("Size"), (int32)Result.size(), 3);
	TestTrue(TEXT("Start"), FMath::IsNearlyEqual(Result[0], -5.0f, 0.001f));
	TestTrue(TEXT("Mid"), FMath::IsNearlyEqual(Result[1], 0.0f, 0.001f));
	TestTrue(TEXT("End"), FMath::IsNearlyEqual(Result[2], 5.0f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FKDEEvaluate, "FANTASIA.MathUtilities.KDE.Evaluate",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FKDEEvaluate::RunTest(const FString& Parameters)
{
	UKernelDensityEstimator* KDE = NewObject<UKernelDensityEstimator>();
	TArray<float> Data = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
	KDE->setData(Data);

	float AtMean = KDE->evaluate(3.0f);
	TestTrue(TEXT("Positive at mean"), AtMean > 0.0f);

	float AtTail = KDE->evaluate(100.0f);
	TestTrue(TEXT("Lower at tail"), AtTail < AtMean);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FKDEGetPdf, "FANTASIA.MathUtilities.KDE.GetPdf",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FKDEGetPdf::RunTest(const FString& Parameters)
{
	UKernelDensityEstimator* KDE = NewObject<UKernelDensityEstimator>();
	TArray<float> Data = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
	KDE->setData(Data);

	TMap<float, float> Pdf = KDE->getPdf(0.0f, 6.0f, 10);
	TestEqual(TEXT("Point count"), Pdf.Num(), 10);

	// Values should be normalized (sum to ~1.0)
	float Sum = 0.0f;
	for (const auto& Pair : Pdf)
	{
		Sum += Pair.Value;
		TestTrue(TEXT("Non-negative"), Pair.Value >= 0.0f);
	}
	TestTrue(TEXT("Sum ~1.0"), FMath::IsNearlyEqual(Sum, 1.0f, 0.01f));
	return true;
}
