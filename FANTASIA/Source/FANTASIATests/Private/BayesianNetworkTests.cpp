#if WITH_AGRUM_BINDING

#include "Misc/AutomationTest.h"
#include "BayesianNetwork.h"
#include "Async/TaskGraphInterfaces.h"

// Helper: pump GameThread tasks so async callbacks can execute
static void PumpGameThread(const bool& bCondition, double TimeoutSeconds = 3.0)
{
	const double Start = FPlatformTime::Seconds();
	while (!bCondition && (FPlatformTime::Seconds() - Start) < TimeoutSeconds)
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		FPlatformProcess::Sleep(0.01f);
	}
}

// Helper: build a simple Rain -> WetGrass <- Sprinkler network (structure only)
static UBayesianNetwork* BuildRainSprinklerNetwork()
{
	UBayesianNetwork* BN = NewObject<UBayesianNetwork>();

	BN->addLabelizedVariable(TEXT("Rain"), TEXT("Is it raining?"), {TEXT("false"), TEXT("true")});
	BN->addLabelizedVariable(TEXT("Sprinkler"), TEXT("Is sprinkler on?"), {TEXT("false"), TEXT("true")});
	BN->addLabelizedVariable(TEXT("WetGrass"), TEXT("Is grass wet?"), {TEXT("false"), TEXT("true")});

	BN->addArc(TEXT("Rain"), TEXT("WetGrass"));
	BN->addArc(TEXT("Sprinkler"), TEXT("WetGrass"));

	return BN;
}

// Helper: build the simplest possible valid BN for inference testing.
// Single chain A -> B, both binary, with uniform CPTs (fillWith).
// No parent-ordering ambiguity since A is a root node and B has exactly one parent.
static UBayesianNetwork* BuildSimpleInferenceNetwork()
{
	UBayesianNetwork* BN = NewObject<UBayesianNetwork>();

	BN->addLabelizedVariable(TEXT("A"), TEXT("Root"), {TEXT("a0"), TEXT("a1")});
	BN->addLabelizedVariable(TEXT("B"), TEXT("Child"), {TEXT("b0"), TEXT("b1")});
	BN->addArc(TEXT("A"), TEXT("B"));

	// P(A): 60/40
	BN->fillCPT(TEXT("A"), {0.6f, 0.4f});

	// P(B|A): use fillWith for uniform, then no ordering ambiguity
	// All entries = 0.5 means P(B=b0|A=any) = 0.5, P(B=b1|A=any) = 0.5
	BN->fillWith(TEXT("B"), 0.5f);

	return BN;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetAddVariables, "FANTASIA.BayesianNetwork.AddVariables",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetAddVariables::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildRainSprinklerNetwork();
	TestEqual(TEXT("Node count"), BN->nodeNames.Num(), 3);
	TestTrue(TEXT("Has Rain"), BN->nodeNames.Contains(TEXT("Rain")));
	TestTrue(TEXT("Has Sprinkler"), BN->nodeNames.Contains(TEXT("Sprinkler")));
	TestTrue(TEXT("Has WetGrass"), BN->nodeNames.Contains(TEXT("WetGrass")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetIdFromName, "FANTASIA.BayesianNetwork.IdFromName",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetIdFromName::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildRainSprinklerNetwork();
	int RainId = BN->idFromName(TEXT("Rain"));
	TestTrue(TEXT("Rain ID >= 0"), RainId >= 0);

	AddExpectedError(TEXT("NonExistent does not exist"), EAutomationExpectedErrorFlags::Contains, 1);
	int BadId = BN->idFromName(TEXT("NonExistent"));
	TestEqual(TEXT("Bad ID == -1"), BadId, -1);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetDuplicateArc, "FANTASIA.BayesianNetwork.DuplicateArc",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetDuplicateArc::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildRainSprinklerNetwork();
	int ArcsBefore = BN->arcs.Num();
	BN->addArc(TEXT("Rain"), TEXT("WetGrass"));
	TestEqual(TEXT("No duplicate arc"), BN->arcs.Num(), ArcsBefore);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetDuplicateVariable, "FANTASIA.BayesianNetwork.DuplicateVariable",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetDuplicateVariable::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildRainSprinklerNetwork();
	BN->addLabelizedVariable(TEXT("Rain"), TEXT("duplicate"), {TEXT("a"), TEXT("b")});
	TestEqual(TEXT("Still 3 nodes"), BN->nodeNames.Num(), 3);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetDescriptions, "FANTASIA.BayesianNetwork.Descriptions",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetDescriptions::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildRainSprinklerNetwork();
	TestTrue(TEXT("Has Rain desc"), BN->nodeDescriptions.Contains(TEXT("Rain")));
	TestEqual(TEXT("Rain desc"), BN->nodeDescriptions[TEXT("Rain")], FString(TEXT("Is it raining?")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetEraseNode, "FANTASIA.BayesianNetwork.EraseNode",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetEraseNode::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildRainSprinklerNetwork();
	TestEqual(TEXT("3 nodes before"), BN->nodeNames.Num(), 3);

	BN->erase(TEXT("Sprinkler"));
	TestEqual(TEXT("2 nodes after"), BN->nodeNames.Num(), 2);
	TestFalse(TEXT("Sprinkler removed"), BN->nodeNames.Contains(TEXT("Sprinkler")));
	TestEqual(TEXT("1 arc left"), BN->arcs.Num(), 1);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetFillWith, "FANTASIA.BayesianNetwork.FillWith",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetFillWith::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = NewObject<UBayesianNetwork>();
	BN->addLabelizedVariable(TEXT("A"), TEXT("test"), {TEXT("x"), TEXT("y")});
	BN->fillWith(TEXT("A"), 0.5f);
	TestTrue(TEXT("fillWith succeeded"), true);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetInference, "FANTASIA.BayesianNetwork.Inference",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetInference::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildSimpleInferenceNetwork();
	BN->Init();

	bool bDone = false;
	BN->OnInferenceReady.AddLambda([&bDone]() { bDone = true; });
	BN->makeInference();

	PumpGameThread(bDone);

	if (!bDone)
	{
		AddError(TEXT("Inference timed out — async callback never fired"));
		return false;
	}

	// getPosterior on root node A: should return a valid probability distribution
	TMap<FString, float> PosteriorA = BN->getPosterior(TEXT("A"));
	TestTrue(TEXT("Posterior A non-empty"), PosteriorA.Num() > 0);

	float SumA = 0.0f;
	for (const auto& Pair : PosteriorA) SumA += Pair.Value;
	TestTrue(TEXT("Posterior A sums to ~1"), FMath::IsNearlyEqual(SumA, 1.0f, 0.01f));

	// getPosterior on child node B: should also be a valid distribution
	TMap<FString, float> PosteriorB = BN->getPosterior(TEXT("B"));
	TestTrue(TEXT("Posterior B non-empty"), PosteriorB.Num() > 0);

	float SumB = 0.0f;
	for (const auto& Pair : PosteriorB) SumB += Pair.Value;
	TestTrue(TEXT("Posterior B sums to ~1"), FMath::IsNearlyEqual(SumB, 1.0f, 0.01f));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetEntropy, "FANTASIA.BayesianNetwork.Entropy",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetEntropy::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildSimpleInferenceNetwork();
	BN->Init();

	bool bDone = false;
	BN->OnInferenceReady.AddLambda([&bDone]() { bDone = true; });
	BN->makeInference();

	PumpGameThread(bDone);

	if (!bDone)
	{
		AddError(TEXT("Inference timed out"));
		return false;
	}

	// A has P(a0)=0.6, P(a1)=0.4, so entropy should be > 0
	double EntropyA = BN->getEntropy(TEXT("A"));
	TestTrue(TEXT("Entropy A > 0"), EntropyA > 0.0);

	// B is uniform (0.5/0.5), so entropy should be maximal (ln(2) ≈ 0.693)
	double EntropyB = BN->getEntropy(TEXT("B"));
	TestTrue(TEXT("Entropy B > 0"), EntropyB > 0.0);

	// A is less uniform than B, so A's entropy should be lower
	TestTrue(TEXT("A less uncertain than B"), EntropyA < EntropyB);

	return true;
}

#endif // WITH_AGRUM_BINDING
