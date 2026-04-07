#if WITH_AGRUM_BINDING

#include "Misc/AutomationTest.h"
#include "InfluenceDiag.h"
#include "Async/TaskGraphInterfaces.h"

static void PumpGameThreadID(const bool& bCondition, double TimeoutSeconds = 3.0)
{
	const double Start = FPlatformTime::Seconds();
	while (!bCondition && (FPlatformTime::Seconds() - Start) < TimeoutSeconds)
	{
		FTaskGraphInterface::Get().ProcessThreadUntilIdle(ENamedThreads::GameThread);
		FPlatformProcess::Sleep(0.01f);
	}
}

// Build a valid influence diagram for inference.
// aGrUM requires utility nodes to have EXACTLY domainSize == 1 (single label).
//
// Structure:
//   Weather (chance, {sunny,rainy}) --> Umbrella (decision, {no,yes})
//   Weather --> Satisfaction (utility, {u})   <-- single label!
//   Umbrella --> Satisfaction
//
// Utility table has 2*2 = 4 entries (one per Weather x Umbrella combination).
static UInfluenceDiag* BuildValidDiagram()
{
	UInfluenceDiag* ID = NewObject<UInfluenceDiag>();

	ID->addLabelizedVariable(TEXT("Weather"), TEXT("Weather"),
		{TEXT("sunny"), TEXT("rainy")}, InfluenceNodeType::CHANCE);
	ID->addLabelizedVariable(TEXT("Umbrella"), TEXT("Take umbrella"),
		{TEXT("no"), TEXT("yes")}, InfluenceNodeType::DECISION);
	// Utility node: MUST have exactly 1 label (aGrUM constraint)
	ID->addLabelizedVariable(TEXT("Satisfaction"), TEXT("Satisfaction"),
		{TEXT("u")}, InfluenceNodeType::UTILITY);

	// Informational arc: decision maker observes Weather before choosing
	ID->addArc(TEXT("Weather"), TEXT("Umbrella"));
	// Functional arcs: both affect utility
	ID->addArc(TEXT("Weather"), TEXT("Satisfaction"));
	ID->addArc(TEXT("Umbrella"), TEXT("Satisfaction"));

	// P(Weather): 70% sunny, 30% rainy
	ID->fillCPT(TEXT("Weather"), {0.7f, 0.3f});

	// Utility table: indexed by parent combinations
	// Values: sunny+no=100, sunny+yes=80, rainy+no=10, rainy+yes=70
	ID->fillUtility(TEXT("Satisfaction"), {100.0f, 80.0f, 10.0f, 70.0f});

	return ID;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagAddNodes, "FANTASIA.InfluenceDiag.AddNodes",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagAddNodes::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = NewObject<UInfluenceDiag>();

	ID->addLabelizedVariable(TEXT("Weather"), TEXT("Weather condition"),
		{TEXT("sunny"), TEXT("rainy")}, InfluenceNodeType::CHANCE);
	ID->addLabelizedVariable(TEXT("TakeUmbrella"), TEXT("Take umbrella?"),
		{TEXT("no"), TEXT("yes")}, InfluenceNodeType::DECISION);

	TestEqual(TEXT("Node count"), ID->nodeNames.Num(), 2);
	TestTrue(TEXT("Has Weather"), ID->nodeNames.Contains(TEXT("Weather")));
	TestTrue(TEXT("Has TakeUmbrella"), ID->nodeNames.Contains(TEXT("TakeUmbrella")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagDuplicateNode, "FANTASIA.InfluenceDiag.DuplicateNode",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagDuplicateNode::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = NewObject<UInfluenceDiag>();

	ID->addLabelizedVariable(TEXT("Weather"), TEXT("Weather condition"),
		{TEXT("sunny"), TEXT("rainy")}, InfluenceNodeType::CHANCE);
	ID->addLabelizedVariable(TEXT("Weather"), TEXT("duplicate"),
		{TEXT("a"), TEXT("b")}, InfluenceNodeType::CHANCE);

	TestEqual(TEXT("Still 1 node"), ID->nodeNames.Num(), 1);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagArcs, "FANTASIA.InfluenceDiag.Arcs",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagArcs::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = NewObject<UInfluenceDiag>();

	ID->addLabelizedVariable(TEXT("A"), TEXT("chance node"),
		{TEXT("x"), TEXT("y")}, InfluenceNodeType::CHANCE);
	ID->addLabelizedVariable(TEXT("D"), TEXT("decision node"),
		{TEXT("d1"), TEXT("d2")}, InfluenceNodeType::DECISION);

	ID->addArc(TEXT("A"), TEXT("D"));
	TestEqual(TEXT("1 arc"), ID->arcs.Num(), 1);

	ID->addArc(TEXT("A"), TEXT("D"));
	TestEqual(TEXT("Still 1 arc"), ID->arcs.Num(), 1);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagDescriptions, "FANTASIA.InfluenceDiag.Descriptions",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagDescriptions::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = NewObject<UInfluenceDiag>();

	ID->addLabelizedVariable(TEXT("Weather"), TEXT("Weather condition"),
		{TEXT("sunny"), TEXT("rainy")}, InfluenceNodeType::CHANCE);

	TestTrue(TEXT("Has desc"), ID->nodeDescriptions.Contains(TEXT("Weather")));
	TestEqual(TEXT("Desc value"), ID->nodeDescriptions[TEXT("Weather")], FString(TEXT("Weather condition")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagEraseNode, "FANTASIA.InfluenceDiag.EraseNode",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagEraseNode::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = NewObject<UInfluenceDiag>();

	ID->addLabelizedVariable(TEXT("A"), TEXT("chance"),
		{TEXT("x"), TEXT("y")}, InfluenceNodeType::CHANCE);
	ID->addLabelizedVariable(TEXT("D"), TEXT("decision"),
		{TEXT("d1"), TEXT("d2")}, InfluenceNodeType::DECISION);
	ID->addArc(TEXT("A"), TEXT("D"));

	TestEqual(TEXT("2 nodes before"), ID->nodeNames.Num(), 2);
	ID->erase(TEXT("D"));
	TestEqual(TEXT("1 node after"), ID->nodeNames.Num(), 1);
	TestFalse(TEXT("D removed"), ID->nodeNames.Contains(TEXT("D")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagUtilityNode, "FANTASIA.InfluenceDiag.UtilityNode",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagUtilityNode::RunTest(const FString& Parameters)
{
	// Verify a valid diagram with utility node can be constructed
	UInfluenceDiag* ID = BuildValidDiagram();
	TestEqual(TEXT("3 nodes"), ID->nodeNames.Num(), 3);
	TestEqual(TEXT("3 arcs"), ID->arcs.Num(), 3);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInfluenceDiagInference, "FANTASIA.InfluenceDiag.Inference",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FInfluenceDiagInference::RunTest(const FString& Parameters)
{
	UInfluenceDiag* ID = BuildValidDiagram();
	ID->Init();

	bool bDone = false;
	ID->OnInferenceReady.AddLambda([&bDone]() { bDone = true; });
	ID->makeInference();

	PumpGameThreadID(bDone);

	if (!bDone)
	{
		AddError(TEXT("Inference timed out — async callback never fired"));
		return false;
	}

	// MEU should return a non-empty result
	TMap<FString, float> MEU = ID->getMEU();
	TestTrue(TEXT("MEU non-empty"), MEU.Num() > 0);

	// Posterior for the chance node should be a valid distribution
	TMap<FString, float> WeatherPosterior = ID->getPosterior(TEXT("Weather"));
	TestTrue(TEXT("Weather posterior non-empty"), WeatherPosterior.Num() > 0);

	float Sum = 0.0f;
	for (const auto& Pair : WeatherPosterior) Sum += Pair.Value;
	TestTrue(TEXT("Weather posterior sums to ~1"), FMath::IsNearlyEqual(Sum, 1.0f, 0.01f));

	return true;
}

#endif // WITH_AGRUM_BINDING
