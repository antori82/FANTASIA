/**
 * @file FANTASIATestActor.cpp
 * @brief Implementation of the Blueprint-friendly FANTASIA test actor.
 */

#include "FANTASIATestActor.h"

#include "OpenAICompatibleComponent.h"
#include "Neo4jComponent.h"
#include "SWIPrologComponent.h"
#include "SWIPrologHelpers.h"
#include "WhisperCaptureComponent.h"
#include "WhisperSubsystem.h"
#include "WhisperBlueprintLibrary.h"
#include "WhisperTypes.h"
#include "RESTTTSComponent.h"
#include "LangGraphComponent.h"
#include "BayesianNetwork.h"
#include "InfluenceDiag.h"
#include "LibSVM.h"
#include "MathUtilities.h"
#include "FANTASIATypes.h"
#include "Engine/Engine.h"

AFANTASIATestActor::AFANTASIATestActor()
{
	PrimaryActorTick.bCanEverTick = false;

	LLMComponent = CreateDefaultSubobject<UOpenAICompatibleComponent>(TEXT("LLMComponent"));
	Neo4jComponent = CreateDefaultSubobject<UNeo4jComponent>(TEXT("Neo4jComponent"));
	PrologComponent = CreateDefaultSubobject<USWIPrologComponent>(TEXT("PrologComponent"));
	WhisperCapture = CreateDefaultSubobject<UWhisperCaptureComponent>(TEXT("WhisperCapture"));
	TTSComponent = CreateDefaultSubobject<URESTTTSComponent>(TEXT("TTSComponent"));
	LangGraphComponent = CreateDefaultSubobject<ULangGraphComponent>(TEXT("LangGraphComponent"));
}

// ════════════════════════════════════════════════════════════════════════
// Helpers
// ════════════════════════════════════════════════════════════════════════

void AFANTASIATestActor::ReportTest(const FString& Name, bool bSuccess, const FString& Msg)
{
	const FString Tag = bSuccess ? TEXT("PASS") : TEXT("FAIL");

	UE_LOG(LogTemp, Log, TEXT("[FANTASIA Test] %s: %s - %s"), *Tag, *Name, *Msg);

	if (GEngine)
	{
		const FColor Color = bSuccess ? FColor::Green : FColor::Red;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, Color,
			FString::Printf(TEXT("[%s] %s: %s"), *Tag, *Name, *Msg));
	}

	OnTestCompleted.Broadcast(Name, bSuccess, Msg);

	if (bSuccess) PassCount++; else FailCount++;

	if ((PassCount + FailCount) >= TotalExpected && TotalExpected > 0)
	{
		UE_LOG(LogTemp, Log, TEXT("[FANTASIA Tests] Complete: %d passed, %d failed out of %d"),
			PassCount, FailCount, TotalExpected);
		OnAllTestsCompleted.Broadcast(PassCount, FailCount);
	}
}

// ════════════════════════════════════════════════════════════════════════
// RunAllTests
// ════════════════════════════════════════════════════════════════════════

void AFANTASIATestActor::RunAllTests()
{
	PassCount = 0;
	FailCount = 0;

	// Count expected tests: 6 offline always + online only if configured
	TotalExpected = 6;
	if (!OpenAIKey.IsEmpty()) TotalExpected++;
	if (!Neo4jPassword.IsEmpty()) TotalExpected++;
	if (!WhisperModelPath.IsEmpty()) TotalExpected++;
	if (!TTSEndpoint.IsEmpty()) TotalExpected++;
	// Prolog is local but needs the DLL to be loaded at runtime
	TotalExpected++;

	UE_LOG(LogTemp, Log, TEXT("[FANTASIA Tests] Starting %d tests..."), TotalExpected);

	// Offline tests
	TestBayesianNetwork();
	TestInfluenceDiag();
	TestSVM();
	TestKDE();
	TestPrologHelpers();
	TestWhisperFormatting();

	// Online tests (skipped if config is empty)
	if (!OpenAIKey.IsEmpty())
		TestLLM();
	else
		UE_LOG(LogTemp, Warning, TEXT("[FANTASIA Tests] Skipping LLM test - no API key"));

	if (!Neo4jPassword.IsEmpty())
		TestNeo4j();
	else
		UE_LOG(LogTemp, Warning, TEXT("[FANTASIA Tests] Skipping Neo4j test - no password"));

	if (!WhisperModelPath.IsEmpty())
		TestWhisperModel();
	else
		UE_LOG(LogTemp, Warning, TEXT("[FANTASIA Tests] Skipping Whisper model test - no model path"));

	if (!TTSEndpoint.IsEmpty())
		TestTTS();
	else
		UE_LOG(LogTemp, Warning, TEXT("[FANTASIA Tests] Skipping TTS test - no endpoint"));

	TestProlog();
}

// ════════════════════════════════════════════════════════════════════════
// Offline Tests
// ════════════════════════════════════════════════════════════════════════

void AFANTASIATestActor::TestBayesianNetwork()
{
#if WITH_AGRUM_BINDING
	BayesianNet = NewObject<UBayesianNetwork>(this);

	BayesianNet->addLabelizedVariable(TEXT("A"), TEXT("Root"), {TEXT("a0"), TEXT("a1")});
	BayesianNet->addLabelizedVariable(TEXT("B"), TEXT("Child"), {TEXT("b0"), TEXT("b1")});
	BayesianNet->addArc(TEXT("A"), TEXT("B"));
	BayesianNet->fillCPT(TEXT("A"), {0.6f, 0.4f});
	BayesianNet->fillWith(TEXT("B"), 0.5f);
	BayesianNet->Init();

	BayesianNet->OnInferenceReady.AddLambda([this]()
	{
		TMap<FString, float> Posterior = BayesianNet->getPosterior(TEXT("A"));
		float Sum = 0.f;
		for (const auto& P : Posterior) Sum += P.Value;
		bool bPass = Posterior.Num() > 0 && FMath::IsNearlyEqual(Sum, 1.0f, 0.01f);
		ReportTest(TEXT("BayesianNetwork"), bPass,
			bPass ? TEXT("Posterior sums to 1.0") : TEXT("Invalid posterior distribution"));
	});

	BayesianNet->makeInference();
#else
	ReportTest(TEXT("BayesianNetwork"), false, TEXT("Skipped - aGrUM binding not available"));
#endif
}

void AFANTASIATestActor::TestInfluenceDiag()
{
#if WITH_AGRUM_BINDING
	InfluenceDiagram = NewObject<UInfluenceDiag>(this);

	InfluenceDiagram->addLabelizedVariable(TEXT("Weather"), TEXT("Weather"),
		{TEXT("sunny"), TEXT("rainy")}, InfluenceNodeType::CHANCE);
	InfluenceDiagram->addLabelizedVariable(TEXT("Umbrella"), TEXT("Take umbrella"),
		{TEXT("no"), TEXT("yes")}, InfluenceNodeType::DECISION);
	InfluenceDiagram->addLabelizedVariable(TEXT("Satisfaction"), TEXT("Satisfaction"),
		{TEXT("u")}, InfluenceNodeType::UTILITY);

	InfluenceDiagram->addArc(TEXT("Weather"), TEXT("Umbrella"));
	InfluenceDiagram->addArc(TEXT("Weather"), TEXT("Satisfaction"));
	InfluenceDiagram->addArc(TEXT("Umbrella"), TEXT("Satisfaction"));

	InfluenceDiagram->fillCPT(TEXT("Weather"), {0.7f, 0.3f});
	InfluenceDiagram->fillUtility(TEXT("Satisfaction"), {100.0f, 80.0f, 10.0f, 70.0f});

	InfluenceDiagram->Init();

	InfluenceDiagram->OnInferenceReady.AddLambda([this]()
	{
		TMap<FString, float> MEU = InfluenceDiagram->getMEU();
		bool bPass = MEU.Num() > 0;
		ReportTest(TEXT("InfluenceDiag"), bPass,
			bPass ? FString::Printf(TEXT("MEU returned %d entries"), MEU.Num())
			      : TEXT("MEU returned empty"));
	});

	InfluenceDiagram->makeInference();
#else
	ReportTest(TEXT("InfluenceDiag"), false, TEXT("Skipped - aGrUM binding not available"));
#endif
}

void AFANTASIATestActor::TestSVM()
{
	SVMClassifier = NewObject<ULibSVM>(this);

	FCLFSample S1; S1.sampleID = TEXT("s1"); S1.CLFclass = 0; S1.features = {0.0, 0.0};
	FCLFSample S2; S2.sampleID = TEXT("s2"); S2.CLFclass = 0; S2.features = {1.0, 0.0};
	FCLFSample S3; S3.sampleID = TEXT("s3"); S3.CLFclass = 1; S3.features = {10.0, 10.0};
	FCLFSample S4; S4.sampleID = TEXT("s4"); S4.CLFclass = 1; S4.features = {11.0, 10.0};

	SVMClassifier->trainingSet = {S1, S2, S3, S4};
	SVMClassifier->SVMParameters.C = 10.0;
	SVMClassifier->SVMParameters.gamma = 0.1;
	SVMClassifier->train();

	FCLFSample T1; T1.sampleID = TEXT("t1"); T1.features = {0.5, 0.5};
	FCLFSample T2; T2.sampleID = TEXT("t2"); T2.features = {10.5, 10.5};
	TArray<FCLFResult> Results = SVMClassifier->predict({T1, T2});

	bool bPass = Results.Num() == 2
		&& Results[0].probabilities.Num() > 0
		&& Results[1].probabilities.Num() > 0;

	ReportTest(TEXT("SVM"), bPass,
		bPass ? FString::Printf(TEXT("Predicted %d samples with probabilities"), Results.Num())
		      : TEXT("Prediction failed or returned no probabilities"));
}

void AFANTASIATestActor::TestKDE()
{
	KDE = NewObject<UKernelDensityEstimator>(this);
	KDE->setData({1.0f, 2.0f, 3.0f, 4.0f, 5.0f});

	float AtMean = KDE->evaluate(3.0f);
	TMap<float, float> Pdf = KDE->getPdf(0.0f, 6.0f, 10);

	float Sum = 0.f;
	for (const auto& P : Pdf) Sum += P.Value;

	bool bPass = AtMean > 0.f && Pdf.Num() == 10 && FMath::IsNearlyEqual(Sum, 1.0f, 0.01f);

	ReportTest(TEXT("KDE"), bPass,
		bPass ? FString::Printf(TEXT("Density at mean=%.4f, PDF normalized (sum=%.4f)"), AtMean, Sum)
		      : FString::Printf(TEXT("Failed: density=%.4f, points=%d, sum=%.4f"), AtMean, Pdf.Num(), Sum));
}

void AFANTASIATestActor::TestPrologHelpers()
{
	USWIPrologAtom* Atom = USWIPrologHelpers::MakeAtom(TEXT("hello"));
	USWIPrologVariable* Var = USWIPrologHelpers::MakeVariable(TEXT("X"));
	USWIPrologInteger* Int = USWIPrologHelpers::MakeInteger(42);
	USWIPrologFloat* Flt = USWIPrologHelpers::MakeFloat(3.14f);

	TArray<USWIPrologTerm*> ListElems;
	ListElems.Add(Atom);
	ListElems.Add(Int);
	USWIPrologList* List = USWIPrologHelpers::MakeList(ListElems);

	TArray<USWIPrologTerm*> CompArgs;
	CompArgs.Add(Atom);
	CompArgs.Add(List);
	USWIPrologCompound* Compound = USWIPrologHelpers::MakeCompound(TEXT("test"), CompArgs);

	bool bPass = Atom != nullptr && Atom->atomValue == TEXT("hello")
		&& Var != nullptr && Var->varName == TEXT("X")
		&& Int != nullptr && Int->intValue == 42
		&& Flt != nullptr && FMath::IsNearlyEqual(Flt->floatValue, 3.14f, 0.01f)
		&& List != nullptr && List->elements.Num() == 2
		&& Compound != nullptr && Compound->compoundName == TEXT("test") && Compound->arguments.Num() == 2;

	ReportTest(TEXT("PrologHelpers"), bPass,
		bPass ? TEXT("All term types created correctly")
		      : TEXT("One or more term creation failures"));
}

void AFANTASIATestActor::TestWhisperFormatting()
{
	// Build a test result
	FWhisperResult Result;
	Result.bSuccess = true;
	Result.FullText = TEXT("Hello world.");
	FWhisperSegment Seg;
	Seg.StartTime = 0.0f;
	Seg.EndTime = 1.5f;
	Seg.Text = TEXT("Hello world.");
	Result.Segments.Add(Seg);

	FString SRT = UWhisperBlueprintLibrary::FormatAsSRT(Result);
	FString VTT = UWhisperBlueprintLibrary::FormatAsVTT(Result);
	FString FullText = UWhisperBlueprintLibrary::GetFullText(Result);
	int32 SegCount = UWhisperBlueprintLibrary::GetSegmentCount(Result);
	FWhisperConfig DefaultCfg = UWhisperBlueprintLibrary::MakeDefaultConfig();

	// Model name parsing
	FWhisperModelInfo Info = UWhisperBlueprintLibrary::ParseModelFileName(TEXT("ggml-large-v3-turbo-q5_0.bin"));

	bool bPass = SRT.Contains(TEXT("-->")) && SRT.Contains(TEXT(","))   // SRT uses comma
		&& VTT.StartsWith(TEXT("WEBVTT")) && VTT.Contains(TEXT("."))   // VTT uses dot
		&& FullText == TEXT("Hello world.")
		&& SegCount == 1
		&& DefaultCfg.Language == EWhisperLanguage::Auto
		&& Info.Size == TEXT("large")
		&& Info.Version == TEXT("v3-turbo")
		&& Info.Quantization == TEXT("Q5_0");

	ReportTest(TEXT("WhisperFormatting"), bPass,
		bPass ? TEXT("SRT, VTT, config, and model parsing all correct")
		      : TEXT("One or more formatting/parsing checks failed"));
}

// ════════════════════════════════════════════════════════════════════════
// Online Tests
// ════════════════════════════════════════════════════════════════════════

void AFANTASIATestActor::TestLLM()
{
	LLMComponent->Config.APIKey = OpenAIKey;
	LLMComponent->Config.DefaultModel = OpenAIModel;
	LLMComponent->ApplyPreset(ELLMProvider::OpenAI);
	LLMComponent->Config.APIKey = OpenAIKey;
	if (!OpenAIModel.IsEmpty())
		LLMComponent->Config.DefaultModel = OpenAIModel;

	LLMComponent->IncomingGPTResponse.AddDynamic(this, &AFANTASIATestActor::OnLLMResponse);

	TArray<FChatTurn> Messages;
	FChatTurn Turn;
	Turn.role = GPTRoleType::USER;
	Turn.content = TEXT("Reply with exactly: FANTASIA_TEST_OK");
	Messages.Add(Turn);

	LLMComponent->GetChatCompletion(Messages);
}

void AFANTASIATestActor::TestNeo4j()
{
	Neo4jComponent->endpoint = Neo4jEndpoint;
	Neo4jComponent->port = Neo4jPort;
	Neo4jComponent->user = Neo4jUser;
	Neo4jComponent->password = Neo4jPassword;

	Neo4jComponent->IncomingResponse.AddDynamic(this, &AFANTASIATestActor::OnNeo4jResponse);

	TMap<FString, FString> EmptyParams;
	Neo4jComponent->submitQuery(TEXT("RETURN 1 AS n"), Neo4jOperation::SINGLE_REQUEST,
		TEXT(""), EmptyParams, TEXT(""));
}

void AFANTASIATestActor::TestProlog()
{
	PrologComponent->AllSolutionsReady.AddDynamic(this, &AFANTASIATestActor::OnPrologAllSolutions);

	PrologComponent->SWIPLconsultString(TEXT("color(red). color(green). color(blue)."));
	PrologComponent->SWIPLfindAll(TEXT("color(X)"));
}

void AFANTASIATestActor::TestWhisperModel()
{
	UWhisperSubsystem* Whisper = GetGameInstance()->GetSubsystem<UWhisperSubsystem>();
	if (!Whisper)
	{
		ReportTest(TEXT("WhisperModel"), false, TEXT("WhisperSubsystem not available"));
		return;
	}

	Whisper->OnModelLoaded.AddDynamic(this, &AFANTASIATestActor::OnWhisperModelLoaded);
	Whisper->LoadModel(WhisperModelPath);
}

void AFANTASIATestActor::TestTTS()
{
	TTSComponent->URL = TTSEndpoint;
	if (!TTSBody.IsEmpty())
		TTSComponent->BodyTemplate = TTSBody;

	TTSComponent->SynthesisReady.AddDynamic(this, &AFANTASIATestActor::OnTTSSynthesisReady);
	TTSComponent->TTSSynthesize(TEXT("Hello, this is a test."), TEXT("test_tts"));
}

// ════════════════════════════════════════════════════════════════════════
// Online Test Callbacks
// ════════════════════════════════════════════════════════════════════════

void AFANTASIATestActor::OnLLMResponse(FString Response, GPTRoleType Role)
{
	LLMComponent->IncomingGPTResponse.RemoveDynamic(this, &AFANTASIATestActor::OnLLMResponse);
	bool bPass = !Response.IsEmpty();
	ReportTest(TEXT("LLM"), bPass,
		bPass ? FString::Printf(TEXT("Got response (%d chars)"), Response.Len())
		      : TEXT("Empty response"));
}

void AFANTASIATestActor::OnNeo4jResponse(FNeo4jResponse Response)
{
	Neo4jComponent->IncomingResponse.RemoveDynamic(this, &AFANTASIATestActor::OnNeo4jResponse);
	bool bPass = Response.rows.Num() > 0;
	ReportTest(TEXT("Neo4j"), bPass,
		bPass ? FString::Printf(TEXT("Got %d rows"), Response.rows.Num())
		      : TEXT("No rows returned"));
}

void AFANTASIATestActor::OnPrologAllSolutions(const TArray<USWIPrologSolution*>& Solutions)
{
	PrologComponent->AllSolutionsReady.RemoveDynamic(this, &AFANTASIATestActor::OnPrologAllSolutions);
	bool bPass = Solutions.Num() == 3;
	ReportTest(TEXT("Prolog"), bPass,
		bPass ? FString::Printf(TEXT("Found %d solutions for color(X)"), Solutions.Num())
		      : FString::Printf(TEXT("Expected 3 solutions, got %d"), Solutions.Num()));
}

void AFANTASIATestActor::OnWhisperModelLoaded(bool bSuccess)
{
	UWhisperSubsystem* Whisper = GetGameInstance()->GetSubsystem<UWhisperSubsystem>();
	if (Whisper)
		Whisper->OnModelLoaded.RemoveDynamic(this, &AFANTASIATestActor::OnWhisperModelLoaded);

	ReportTest(TEXT("WhisperModel"), bSuccess,
		bSuccess ? TEXT("Model loaded successfully")
		         : TEXT("Model failed to load"));
}

void AFANTASIATestActor::OnTTSSynthesisReady(FString Id)
{
	TTSComponent->SynthesisReady.RemoveDynamic(this, &AFANTASIATestActor::OnTTSSynthesisReady);
	bool bPass = !Id.IsEmpty();
	ReportTest(TEXT("TTS"), bPass,
		bPass ? FString::Printf(TEXT("Synthesis complete for id '%s'"), *Id)
		      : TEXT("Synthesis returned empty id"));
}
