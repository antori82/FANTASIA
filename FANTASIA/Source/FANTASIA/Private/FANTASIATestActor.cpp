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
#include "ElevenLabsTTSComponent.h"
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

	// Components are created lazily inside each Test* function to avoid side effects
	// (e.g. Neo4jComponent opening a WebSocket in BeginPlay with default settings).
}

/** Lazily create and register a UActorComponent on this actor. */
template <typename T>
static T* EnsureComponent(AActor* Owner, T*& Slot, const FName& Name)
{
	if (!Slot)
	{
		Slot = NewObject<T>(Owner, Name);
		Slot->RegisterComponent();
	}
	return Slot;
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

	// Local providers (Ollama/LMStudio/vLLM) don't need an API key, so LLM runs
	// whenever the provider is one of those OR a key is supplied.
	// Custom runs when a URL is supplied (auth key optional).
	const bool bLLMConfigured =
		LLMProvider == ELLMProvider::Ollama ||
		LLMProvider == ELLMProvider::LMStudio ||
		LLMProvider == ELLMProvider::vLLM ||
		(LLMProvider == ELLMProvider::Custom && !LLMCustomURL.IsEmpty()) ||
		(LLMProvider != ELLMProvider::Custom && !LLMAPIKey.IsEmpty());

	// Count expected tests: 7 offline always + online only if configured
	TotalExpected = 7; // BN, ID, SVM, KDE, PrologHelpers, WhisperFormatting, WhisperCapture
	if (bLLMConfigured) TotalExpected++;
	if (!Neo4jPassword.IsEmpty()) TotalExpected++;
	if (!WhisperModelPath.IsEmpty()) TotalExpected++;
	if (!TTSEndpoint.IsEmpty()) TotalExpected++;
	if (!ElevenLabsKey.IsEmpty()) TotalExpected++;
	if (!LangGraphEndpoint.IsEmpty()) TotalExpected++;
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
	TestWhisperCapture();

	// Online tests (skipped if config is empty)
	if (bLLMConfigured)
		TestLLM();
	else
		UE_LOG(LogTemp, Warning, TEXT("[FANTASIA Tests] Skipping LLM test - no API key for cloud provider"));

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

	if (!ElevenLabsKey.IsEmpty())
		TestElevenLabsTTS();
	else
		UE_LOG(LogTemp, Warning, TEXT("[FANTASIA Tests] Skipping ElevenLabs test - no API key"));

	if (!LangGraphEndpoint.IsEmpty())
		TestLangGraph();
	else
		UE_LOG(LogTemp, Warning, TEXT("[FANTASIA Tests] Skipping LangGraph test - no endpoint"));

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

void AFANTASIATestActor::TestWhisperCapture()
{
	TArray<FString> Devices = UWhisperCaptureComponent::GetAvailableInputDevices();
	bool bPass = Devices.Num() > 0;
	ReportTest(TEXT("WhisperCapture"), bPass,
		bPass ? FString::Printf(TEXT("Found %d audio input device(s)"), Devices.Num())
		      : TEXT("No audio input devices enumerated"));
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
	EnsureComponent(this, LLMComponent, TEXT("LLMComponent"));

	// Apply the selected provider preset first (sets URL, default model, timeout, auth flag).
	// For Custom, ApplyPreset is a no-op: we fill in URL and auth flag from our own fields.
	LLMComponent->ApplyPreset(LLMProvider);

	if (LLMProvider == ELLMProvider::Custom)
	{
		LLMComponent->Config.URL = LLMCustomURL;
		LLMComponent->Config.bRequiresAuth = bLLMCustomRequiresAuth;
		LLMComponent->Config.TimeoutSeconds = 60;
	}

	// Override with user-supplied key/model if provided
	LLMComponent->Config.APIKey = LLMAPIKey;
	if (!LLMModel.IsEmpty())
		LLMComponent->Config.DefaultModel = LLMModel;

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
	// Create the component and configure it BEFORE RegisterComponent() runs BeginPlay(),
	// so the connection is attempted with user-supplied credentials rather than defaults.
	if (!Neo4jComponent)
	{
		Neo4jComponent = NewObject<UNeo4jComponent>(this, TEXT("Neo4jComponent"));
		Neo4jComponent->endpoint = Neo4jEndpoint;
		Neo4jComponent->port = Neo4jPort;
		Neo4jComponent->user = Neo4jUser;
		Neo4jComponent->password = Neo4jPassword;
		Neo4jComponent->RegisterComponent();
	}

	Neo4jComponent->IncomingResponse.AddDynamic(this, &AFANTASIATestActor::OnNeo4jResponse);

	TMap<FString, FString> EmptyParams;
	Neo4jComponent->submitQuery(TEXT("RETURN 1 AS n"), Neo4jOperation::SINGLE_REQUEST,
		TEXT(""), EmptyParams, Neo4jDatabase);
}

void AFANTASIATestActor::TestProlog()
{
	EnsureComponent(this, PrologComponent, TEXT("PrologComponent"));

	PrologComponent->AllSolutionsReady.AddDynamic(this, &AFANTASIATestActor::OnPrologAllSolutions);

	// Start clean: retract any leftover facts from previous test runs.
	// SWIPLqueryString executes the goal directly (unlike SWIPLconsultString
	// which wraps input in assert(T)). retractall/1 in SWI-Prolog is a no-op
	// on unknown predicates, so this is safe on the first run.
	PrologComponent->SWIPLqueryString(TEXT("retractall(fantasia_color(_))"));

	// SWIPLconsultString parses ONE term per call (via atom_to_term + assert),
	// so we must assert each fact individually.
	PrologComponent->SWIPLconsultString(TEXT("fantasia_color(red)"));
	PrologComponent->SWIPLconsultString(TEXT("fantasia_color(green)"));
	PrologComponent->SWIPLconsultString(TEXT("fantasia_color(blue)"));
	PrologComponent->SWIPLfindAll(TEXT("fantasia_color(X)"));
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
	// LoadModel accepts both absolute paths and bare filenames, delegating
	// to LoadModelByName internally when given a filename.
	Whisper->LoadModel(WhisperModelPath);
}

void AFANTASIATestActor::TestLangGraph()
{
	if (!LangGraphComponent)
	{
		LangGraphComponent = NewObject<ULangGraphComponent>(this, TEXT("LangGraphComponent"));
		LangGraphComponent->endpoint = LangGraphEndpoint;
		LangGraphComponent->port = LangGraphPort;
		LangGraphComponent->RegisterComponent();
	}

	LangGraphComponent->LangGraphThreadCreateResponse.AddDynamic(this, &AFANTASIATestActor::OnLangGraphThreadCreated);

	// The component substitutes an auto-generated UUID if LangGraphTestThreadID
	// is empty or not a valid UUID, so we can pass it through directly.
	LangGraphComponent->createLangGraphThread(LangGraphTestThreadID);
}

void AFANTASIATestActor::TestTTS()
{
	EnsureComponent(this, TTSComponent, TEXT("TTSComponent"));

	TTSComponent->URL = TTSEndpoint;
	if (!TTSBody.IsEmpty())
		TTSComponent->BodyTemplate = TTSBody;

	TTSComponent->SynthesisReady.AddDynamic(this, &AFANTASIATestActor::OnTTSSynthesisReady);
	TTSComponent->TTSSynthesize(TEXT("Hello, this is a test."), TEXT("test_tts"));
}

void AFANTASIATestActor::TestElevenLabsTTS()
{
	EnsureComponent(this, ElevenLabsComponent, TEXT("ElevenLabsComponent"));

	ElevenLabsComponent->Key = ElevenLabsKey;
	ElevenLabsComponent->VoiceID = ElevenLabsVoiceID;
	ElevenLabsComponent->ModelID = ElevenLabsModelID;

	ElevenLabsComponent->SynthesisReady.AddDynamic(this, &AFANTASIATestActor::OnElevenLabsSynthesisReady);
	ElevenLabsComponent->TTSSynthesize(TEXT("Hello, this is an ElevenLabs test."), TEXT("test_eleven"));
}

// ════════════════════════════════════════════════════════════════════════
// Online Test Callbacks
// ════════════════════════════════════════════════════════════════════════

void AFANTASIATestActor::OnLLMResponse(FString Response, GPTRoleType gptRole)
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

void AFANTASIATestActor::OnElevenLabsSynthesisReady(FString Id)
{
	ElevenLabsComponent->SynthesisReady.RemoveDynamic(this, &AFANTASIATestActor::OnElevenLabsSynthesisReady);
	bool bPass = !Id.IsEmpty();
	ReportTest(TEXT("ElevenLabs"), bPass,
		bPass ? FString::Printf(TEXT("Synthesis complete for id '%s'"), *Id)
		      : TEXT("Synthesis returned empty id"));
}

void AFANTASIATestActor::OnLangGraphThreadCreated(FString ThreadID)
{
	LangGraphComponent->LangGraphThreadCreateResponse.RemoveDynamic(this, &AFANTASIATestActor::OnLangGraphThreadCreated);
	bool bPass = !ThreadID.IsEmpty();
	ReportTest(TEXT("LangGraph"), bPass,
		bPass ? FString::Printf(TEXT("Thread created: %s"), *ThreadID)
		      : TEXT("Thread creation returned empty ID"));

	// Clean up the test thread
	if (bPass && LangGraphComponent)
		LangGraphComponent->deleteLangGraphThread(ThreadID);
}
