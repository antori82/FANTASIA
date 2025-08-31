#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "SWIPrologThread.h"
#include "SWIPrologComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSolutionAvailableEvent, USWIPrologSolution*, solution); 

UCLASS(ClassGroup = (SWIProlog), meta = (BlueprintSpawnableComponent), config = Game)
class USWIPrologComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	FDelegateHandle SolutionAvailableHandle;
	PlQuery* myQuery;
	FString resFolderPath;
	PlTermv inQueryElements;
	USWIPrologTerm* currentQuery;
	FString consultFile = "";
	int inArity;
	SWIPrologThread* handle;

	void inferenceComplete();

public:
	// Sets default values for this component's properties
	USWIPrologComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FSolutionAvailableEvent SolutionAvailable;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLsubmitQuery(USWIPrologTerm* inRuleOrFact);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Next solution", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void nextSolution();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Assert", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLassert(USWIPrologObject* prologObject, bool asFirstClause, bool& bResult);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Retract", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLretract(USWIPrologTerm* ruleOrFact, bool& bResult);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Prolog file", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void openPrologFile(const FString filename);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};