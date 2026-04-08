/**
 * @file FANTASIATestActor.h
 * @brief Blueprint-friendly test actor that exercises every FANTASIA component.
 *
 * Drop this actor into any level, configure credentials in the Details panel,
 * and call RunAllTests (or individual Test* functions) from Blueprint.
 * Results appear as on-screen messages and are broadcast via OnTestCompleted.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FANTASIATypes.h"
#include "FANTASIATestActor.generated.h"

class UOpenAICompatibleComponent;
class UNeo4jComponent;
class USWIPrologComponent;
class UWhisperCaptureComponent;
class URESTTTSComponent;
class UElevenLabsTTSComponent;
class ULangGraphComponent;
class UBayesianNetwork;
class UInfluenceDiag;
class ULibSVM;
class UKernelDensityEstimator;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnFANTASIATestCompleted, FString, TestName, bool, bSuccess, FString, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFANTASIAAllTestsCompleted, int32, Passed, int32, Failed);

UCLASS(Blueprintable, meta = (DisplayName = "FANTASIA Test Actor"))
class FANTASIATESTS_API AFANTASIATestActor : public AActor
{
	GENERATED_BODY()

public:
	AFANTASIATestActor();

	// ── Events ──────────────────────────────────────────────────────────

	/** Fired after each individual test completes. */
	UPROPERTY(BlueprintAssignable, Category = "FANTASIA Tests|Events")
	FOnFANTASIATestCompleted OnTestCompleted;

	/** Fired after RunAllTests finishes all tests. */
	UPROPERTY(BlueprintAssignable, Category = "FANTASIA Tests|Events")
	FOnFANTASIAAllTestsCompleted OnAllTestsCompleted;

	// ── Components (visible in Details panel) ───────────────────────────

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FANTASIA Tests|Components")
	UOpenAICompatibleComponent* LLMComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FANTASIA Tests|Components")
	UNeo4jComponent* Neo4jComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FANTASIA Tests|Components")
	USWIPrologComponent* PrologComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FANTASIA Tests|Components")
	UWhisperCaptureComponent* WhisperCapture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FANTASIA Tests|Components")
	URESTTTSComponent* TTSComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FANTASIA Tests|Components")
	ULangGraphComponent* LangGraphComponent;

	// ── Online Test Configuration ───────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|LLM")
	FString OpenAIKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|LLM")
	FString OpenAIModel = TEXT("gpt-4-turbo-preview");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|Neo4j")
	FString Neo4jEndpoint = TEXT("localhost");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|Neo4j")
	int32 Neo4jPort = 7687;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|Neo4j")
	FString Neo4jUser = TEXT("neo4j");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|Neo4j")
	FString Neo4jPassword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|TTS")
	FString TTSEndpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|TTS")
	FString TTSBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FANTASIA Tests|Whisper")
	FString WhisperModelPath;

	// ── Test Functions (all BlueprintCallable) ──────────────────────────

	/** Run all tests. Offline tests always run; online tests are skipped if credentials are empty. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests")
	void RunAllTests();

	// Offline tests — no credentials needed

	/** Build a Bayesian Network, run inference, verify posteriors. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Offline")
	void TestBayesianNetwork();

	/** Build an Influence Diagram, run inference, verify MEU. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Offline")
	void TestInfluenceDiag();

	/** Train SVM on separable data, predict, verify results. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Offline")
	void TestSVM();

	/** Set KDE data, evaluate density, verify PDF normalization. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Offline")
	void TestKDE();

	/** Create Prolog terms (atoms, compounds, lists), verify properties. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Offline")
	void TestPrologHelpers();

	/** Exercise Whisper formatting (SRT/VTT) and model name parsing. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Offline")
	void TestWhisperFormatting();

	// Online tests — need credentials / services

	/** Send a chat completion to the LLM, verify response arrives. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Online")
	void TestLLM();

	/** Submit a RETURN 1 AS n query to Neo4j, verify response. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Online")
	void TestNeo4j();

	/** Consult Prolog code and query for solutions. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Online")
	void TestProlog();

	/** Load a Whisper model and check status. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Online")
	void TestWhisperModel();

	/** Synthesize text via the REST TTS endpoint. */
	UFUNCTION(BlueprintCallable, Category = "FANTASIA Tests|Online")
	void TestTTS();

private:
	void ReportTest(const FString& Name, bool bSuccess, const FString& Msg);

	// Callbacks for online test delegates (must be UFUNCTION for dynamic binding)
	UFUNCTION()
	void OnLLMResponse(FString Response, GPTRoleType Role);

	UFUNCTION()
	void OnNeo4jResponse(FNeo4jResponse Response);

	UFUNCTION()
	void OnPrologAllSolutions(const TArray<USWIPrologSolution*>& Solutions);

	UFUNCTION()
	void OnWhisperModelLoaded(bool bSuccess);

	UFUNCTION()
	void OnTTSSynthesisReady(FString Id);

	UPROPERTY()
	UBayesianNetwork* BayesianNet = nullptr;

	UPROPERTY()
	UInfluenceDiag* InfluenceDiagram = nullptr;

	UPROPERTY()
	ULibSVM* SVMClassifier = nullptr;

	UPROPERTY()
	UKernelDensityEstimator* KDE = nullptr;

	int32 PassCount = 0;
	int32 FailCount = 0;
	int32 TotalExpected = 0;
};
