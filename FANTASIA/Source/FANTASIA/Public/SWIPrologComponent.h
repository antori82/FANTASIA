/**
 * @file SWIPrologComponent.h
 * @brief Unreal Engine actor component providing Blueprint access to an embedded SWI-Prolog engine.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "SWIPrologThread.h"
#include "SWIPrologComponent.generated.h"

/** Delegate broadcast when a single Prolog solution becomes available. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSolutionAvailableEvent, USWIPrologSolution*, solution);

/** Delegate broadcast when all solutions for a FindAll query have been collected. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllSolutionsEvent, const TArray<USWIPrologSolution*>&, Solutions);

/** Delegate broadcast when a Prolog query or operation fails with an error. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQueryFailedEvent, FString, ErrorMessage);

/**
 * @brief Actor component that exposes SWI-Prolog logic programming to Blueprints.
 *
 * Attach this component to any actor to consult Prolog files, assert/retract
 * facts and rules, submit queries, and receive solutions asynchronously via
 * delegates. All Prolog work runs on a dedicated background thread managed by
 * SWIPrologThread.
 *
 * @see SWIPrologThread
 * @see USWIPrologHelpers
 */
UCLASS(ClassGroup = (SWIProlog), meta = (BlueprintSpawnableComponent), config = Game)
class USWIPrologComponent : public UActorComponent
{
	GENERATED_BODY()

	// ── Private State ────────────────────────────────────────────────────

private:

	/** Handle for the single-solution delegate subscription. */
	FDelegateHandle SolutionAvailableHandle;

	/** Handle for the all-solutions delegate subscription. */
	FDelegateHandle AllSolutionsHandle;

	/** Handle for the query-error delegate subscription. */
	FDelegateHandle QueryErrorHandle;

	/** Owning pointer to the shared Prolog worker thread. */
	SWIPrologThread* ThreadHandle = nullptr;

	/** Callback invoked on the game thread when a single solution is ready. */
	void HandleInferenceComplete();

	/** Callback invoked on the game thread when all solutions have been collected. */
	void HandleAllSolutions(TArray<USWIPrologSolution*> Solutions);

	/** Callback invoked on the game thread when a query error occurs. */
	void HandleQueryError(FString ErrorMessage);

	// ── Public Interface ─────────────────────────────────────────────────

public:
	/** Default constructor. Disables ticking. */
	USWIPrologComponent();

	/** Fired when a single solution is available (from SubmitQuery / NextSolution). */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FSolutionAvailableEvent SolutionAvailable;

	/** Fired when all solutions have been collected (from FindAll). */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FAllSolutionsEvent AllSolutionsReady;

	/** Fired when a Prolog query or operation produces an error. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FQueryFailedEvent QueryFailed;

	/** Submit a query built from Prolog term objects. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLsubmitQuery(USWIPrologTerm* inRuleOrFact);

	/** Submit a query from a raw Prolog string, e.g. "parent(X, tom)". */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query string"), Category = "SWIProlog")
	void SWIPLqueryString(const FString& Query);

	/** Collect all solutions for a query string at once. Fires AllSolutionsReady when done. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Find all solutions"), Category = "SWIProlog")
	void SWIPLfindAll(const FString& Query);

	/** Request the next solution for the current open query. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Next solution", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void nextSolution();

	/** Assert a fact or rule into the Prolog database. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Assert", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLassert(USWIPrologObject* prologObject, bool asFirstClause);

	/** Retract a fact or rule from the Prolog database. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Retract", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLretract(USWIPrologTerm* ruleOrFact);

	/** Load a .pl Prolog file. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Prolog file", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void openPrologFile(const FString& filename);

	/** Load Prolog clauses from a string (without needing a file). */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Consult string"), Category = "SWIProlog")
	void SWIPLconsultString(const FString& PrologCode);

	// ── Lifecycle ────────────────────────────────────────────────────────

protected:
	/** Initializes the Prolog thread and subscribes to its delegates. */
	virtual void BeginPlay() override;

	/** Unsubscribes from the Prolog thread delegates on teardown. */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
