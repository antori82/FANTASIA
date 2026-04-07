// Fill out your copyright notice in the Description page of Project Settings.

#include "SWIPrologComponent.h"


// Sets default values for this component's properties
USWIPrologComponent::USWIPrologComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USWIPrologComponent::SWIPLsubmitQuery(USWIPrologTerm* inRuleOrFactTerm) {
	ThreadHandle->submitQuery(inRuleOrFactTerm);
}

void USWIPrologComponent::SWIPLqueryString(const FString& Query) {
	ThreadHandle->submitQueryString(Query);
}

void USWIPrologComponent::SWIPLfindAll(const FString& Query) {
	ThreadHandle->submitFindAll(Query);
}

void USWIPrologComponent::SWIPLassert(USWIPrologObject* prologObject, bool asFirstClause) {
	ThreadHandle->SWIPLassert(prologObject, asFirstClause);
}

void USWIPrologComponent::SWIPLretract(USWIPrologTerm* ruleOrFactTerm) {
	ThreadHandle->SWIPLretract(ruleOrFactTerm);
}

void USWIPrologComponent::openPrologFile(const FString& filename) {
	ThreadHandle->openPrologFile(filename);
}

void USWIPrologComponent::SWIPLconsultString(const FString& PrologCode) {
	ThreadHandle->consultString(PrologCode);
}

void USWIPrologComponent::HandleInferenceComplete() {
	SolutionAvailable.Broadcast(ThreadHandle->currentSolution);
}

void USWIPrologComponent::HandleAllSolutions(TArray<USWIPrologSolution*> solutions) {
	AllSolutionsReady.Broadcast(solutions);
}

void USWIPrologComponent::HandleQueryError(FString errorMessage) {
	QueryFailed.Broadcast(errorMessage);
}

void USWIPrologComponent::nextSolution() {
	ThreadHandle->requestNextSolution();
}

// Called when the game starts
void USWIPrologComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!ThreadHandle)
	{
		SolutionAvailableDelegate InferenceAvailableSubscriber;
		InferenceAvailableSubscriber.BindUObject(this, &USWIPrologComponent::HandleInferenceComplete);

		ThreadHandle = SWIPrologThread::setup();
		SolutionAvailableHandle = ThreadHandle->SolutionAvailableSubscribeUser(InferenceAvailableSubscriber);

		AllSolutionsHandle = ThreadHandle->AllSolutionsReady.AddUObject(this, &USWIPrologComponent::HandleAllSolutions);
		QueryErrorHandle = ThreadHandle->QueryError.AddUObject(this, &USWIPrologComponent::HandleQueryError);
	}
}

// Called when the game ends
void USWIPrologComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (ThreadHandle)
	{
		ThreadHandle->SolutionAvailableUnsubscribeUser(SolutionAvailableHandle);
		ThreadHandle->AllSolutionsReady.Remove(AllSolutionsHandle);
		ThreadHandle->QueryError.Remove(QueryErrorHandle);
	}
}
