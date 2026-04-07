#if WITH_AGRUM_BINDING

#include "Misc/AutomationTest.h"
#include "BayesianNetwork.h"

// Helper: build a simple Rain -> WetGrass <- Sprinkler network
static UBayesianNetwork* BuildRainSprinklerNetwork()
{
	UBayesianNetwork* BN = NewObject<UBayesianNetwork>();

	BN->addLabelizedVariable(TEXT("Rain"), TEXT("Is it raining?"), {TEXT("false"), TEXT("true")});
	BN->addLabelizedVariable(TEXT("Sprinkler"), TEXT("Is sprinkler on?"), {TEXT("false"), TEXT("true")});
	BN->addLabelizedVariable(TEXT("WetGrass"), TEXT("Is grass wet?"), {TEXT("false"), TEXT("true")});

	BN->addArc(TEXT("Rain"), TEXT("WetGrass"));
	BN->addArc(TEXT("Sprinkler"), TEXT("WetGrass"));

	// P(Rain): 20% chance of rain
	BN->fillCPT(TEXT("Rain"), {0.8f, 0.2f});
	// P(Sprinkler): 40% chance sprinkler is on
	BN->fillCPT(TEXT("Sprinkler"), {0.6f, 0.4f});
	// P(WetGrass | Rain, Sprinkler): ordered by parent instantiation
	// R=f,S=f -> wet=0.0;  R=f,S=t -> wet=0.9;  R=t,S=f -> wet=0.8;  R=t,S=t -> wet=0.99
	BN->fillCPT(TEXT("WetGrass"), {1.0f, 0.0f, 0.1f, 0.9f, 0.2f, 0.8f, 0.01f, 0.99f});

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
	// Adding same arc again should be a no-op
	BN->addArc(TEXT("Rain"), TEXT("WetGrass"));
	TestEqual(TEXT("No duplicate arc"), BN->arcs.Num(), ArcsBefore);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetInference, "FANTASIA.BayesianNetwork.Inference",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetInference::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildRainSprinklerNetwork();
	BN->Init();

	// Use the non-dynamic delegate for C++ lambda binding
	bool bDone = false;
	BN->OnInferenceReady.AddLambda([&bDone]() { bDone = true; });
	BN->makeInference();

	// Busy-wait up to 2 seconds
	double Start = FPlatformTime::Seconds();
	while (!bDone && (FPlatformTime::Seconds() - Start) < 2.0)
	{
		FPlatformProcess::Sleep(0.01f);
	}

	if (!bDone)
	{
		AddError(TEXT("Inference timed out"));
		return false;
	}

	TMap<FString, float> Posterior = BN->getPosterior(TEXT("WetGrass"));
	TestTrue(TEXT("Posterior non-empty"), Posterior.Num() > 0);

	// Posterior should sum to ~1.0
	float Sum = 0.0f;
	for (const auto& Pair : Posterior) Sum += Pair.Value;
	TestTrue(TEXT("Sum ~1"), FMath::IsNearlyEqual(Sum, 1.0f, 0.01f));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBayesNetEntropy, "FANTASIA.BayesianNetwork.Entropy",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBayesNetEntropy::RunTest(const FString& Parameters)
{
	UBayesianNetwork* BN = BuildRainSprinklerNetwork();
	BN->Init();

	bool bDone = false;
	BN->OnInferenceReady.AddLambda([&bDone]() { bDone = true; });
	BN->makeInference();

	double Start = FPlatformTime::Seconds();
	while (!bDone && (FPlatformTime::Seconds() - Start) < 2.0)
		FPlatformProcess::Sleep(0.01f);

	if (!bDone)
	{
		AddError(TEXT("Inference timed out"));
		return false;
	}

	double Entropy = BN->getEntropy(TEXT("Rain"));
	TestTrue(TEXT("Entropy > 0"), Entropy > 0.0);
	return true;
}

#endif // WITH_AGRUM_BINDING
