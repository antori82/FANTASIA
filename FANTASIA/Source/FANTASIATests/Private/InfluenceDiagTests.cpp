#if WITH_AGRUM_BINDING

#include "Misc/AutomationTest.h"
#include "InfluenceDiag.h"

// Helper: build a simple Weather -> TakeUmbrella -> Satisfaction influence diagram
static UInfluenceDiag* BuildUmbrellaDecision()
{
	UInfluenceDiag* ID = NewObject<UInfluenceDiag>();

	// Chance node: Weather (sunny or rainy)
	ID->addLabelizedVariable(TEXT("Weather"), TEXT("Weather condition"),
		{TEXT("sunny"), TEXT("rainy")}, InfluenceNodeType::CHANCE);

	// Decision node: TakeUmbrella (yes or no)
	ID->addLabelizedVariable(TEXT("TakeUmbrella"), TEXT("Take umbrella?"),
		{TEXT("no"), TEXT("yes")}, InfluenceNodeType::DECISION);

	// Utility node: Satisfaction
	ID->addLabelizedVariable(TEXT("Satisfaction"), TEXT("How satisfied"),
		{TEXT("low"), TEXT("high")}, InfluenceNodeType::UTILITY);

	// Arcs
	ID->addArc(TEXT("Weather"), TEXT("Satisfaction"));
	ID->addArc(TEXT("TakeUmbrella"), TEXT("Satisfaction"));
	ID->addArc(TEXT("Weather"), TEXT("TakeUmbrella")); // informational arc

	// P(Weather): 70% sunny, 30% rainy
	ID->fillCPT(TEXT("Weather"), {0.7f, 0.3f});

	// Utility(Satisfaction | Weather, TakeUmbrella):
	// Weather=sunny, Umbrella=no  -> utility 100
	// Weather=sunny, Umbrella=yes -> utility  80 (carrying umbrella unnecessarily)
	// Weather=rainy, Umbrella=no  -> utility  10 (getting wet)
	// Weather=rainy, Umbrella=yes -> utility  70 (dry but carrying umbrella)
	ID->fillUtility(TEXT("Satisfaction"), {100.0f, 80.0f, 10.0f, 70.0f});

	return ID;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagStructure, "FANTASIA.InfluenceDiag.Structure",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagStructure::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = BuildUmbrellaDecision();
	TestEqual(TEXT("Node count"), ID->nodeNames.Num(), 3);
	TestTrue(TEXT("Has Weather"), ID->nodeNames.Contains(TEXT("Weather")));
	TestTrue(TEXT("Has TakeUmbrella"), ID->nodeNames.Contains(TEXT("TakeUmbrella")));
	TestTrue(TEXT("Has Satisfaction"), ID->nodeNames.Contains(TEXT("Satisfaction")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagDecisionOrder, "FANTASIA.InfluenceDiag.DecisionOrder",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagDecisionOrder::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = BuildUmbrellaDecision();
	TestTrue(TEXT("Decision order exists"), ID->decisionOrderExists());

	TArray<int> Order = ID->decisionOrder();
	TestTrue(TEXT("Order non-empty"), Order.Num() > 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagInference, "FANTASIA.InfluenceDiag.Inference",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagInference::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = BuildUmbrellaDecision();
	ID->Init();

	bool bDone = false;
	ID->OnInferenceReady.AddLambda([&bDone]() { bDone = true; });
	ID->makeInference();

	double Start = FPlatformTime::Seconds();
	while (!bDone && (FPlatformTime::Seconds() - Start) < 2.0)
		FPlatformProcess::Sleep(0.01f);

	if (!bDone)
	{
		AddError(TEXT("Inference timed out"));
		return false;
	}

	TMap<FString, float> MEU = ID->getMEU();
	TestTrue(TEXT("MEU non-empty"), MEU.Num() > 0);

	return true;
}

#endif // WITH_AGRUM_BINDING
