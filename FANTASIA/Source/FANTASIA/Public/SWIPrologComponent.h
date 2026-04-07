#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "SWIPrologThread.h"
#include "SWIPrologComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSolutionAvailableEvent, USWIPrologSolution*, solution);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllSolutionsEvent, const TArray<USWIPrologSolution*>&, Solutions);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FQueryFailedEvent, FString, ErrorMessage);

UCLASS(ClassGroup = (SWIProlog), meta = (BlueprintSpawnableComponent), config = Game)
class USWIPrologComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	FDelegateHandle SolutionAvailableHandle;
	FDelegateHandle AllSolutionsHandle;
	FDelegateHandle QueryErrorHandle;
	SWIPrologThread* ThreadHandle = nullptr;

	void HandleInferenceComplete();
	void HandleAllSolutions(TArray<USWIPrologSolution*> Solutions);
	void HandleQueryError(FString ErrorMessage);

public:
	// Sets default values for this component's properties
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
