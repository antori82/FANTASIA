// Fill out your copyright notice in the Description page of Project Settings.

#include "SWIPrologComponent.h"


// Sets default values for this component's properties
USWIPrologComponent::USWIPrologComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USWIPrologComponent::SWIPLsubmitQuery(USWIPrologTerm* inRuleOrFactTerm) {
	handle->submitQuery(inRuleOrFactTerm);
}

void USWIPrologComponent::SWIPLqueryString(const FString& Query) {
	handle->submitQueryString(Query);
}

void USWIPrologComponent::SWIPLfindAll(const FString& Query) {
	handle->submitFindAll(Query);
}

void USWIPrologComponent::SWIPLassert(USWIPrologObject* prologObject, bool asFirstClause) {
	handle->SWIPLassert(prologObject, asFirstClause);
}

void USWIPrologComponent::SWIPLretract(USWIPrologTerm* ruleOrFactTerm) {
	handle->SWIPLretract(ruleOrFactTerm);
}

void USWIPrologComponent::openPrologFile(const FString& filename) {
	handle->openPrologFile(filename);
}

void USWIPrologComponent::SWIPLconsultString(const FString& PrologCode) {
	handle->consultString(PrologCode);
}

void USWIPrologComponent::inferenceComplete() {
	SolutionAvailable.Broadcast(handle->currentSolution);
}

void USWIPrologComponent::onAllSolutions(TArray<USWIPrologSolution*> solutions) {
	AllSolutionsReady.Broadcast(solutions);
}

void USWIPrologComponent::onQueryError(FString errorMessage) {
	QueryFailed.Broadcast(errorMessage);
}

void USWIPrologComponent::nextSolution() {
	handle->requestNextSolution();
}

// Called when the game starts
void USWIPrologComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!handle)
	{
		SolutionAvailableDelegate InferenceAvailableSubscriber;
		InferenceAvailableSubscriber.BindUObject(this, &USWIPrologComponent::inferenceComplete);

		handle = SWIPrologThread::setup();
		SolutionAvailableHandle = handle->SolutionAvailableSubscribeUser(InferenceAvailableSubscriber);

		AllSolutionsHandle = handle->AllSolutionsReady.AddUObject(this, &USWIPrologComponent::onAllSolutions);
		QueryErrorHandle = handle->QueryError.AddUObject(this, &USWIPrologComponent::onQueryError);
	}
}

// Called when the game ends
void USWIPrologComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (handle)
	{
		handle->SolutionAvailableUnsubscribeUser(SolutionAvailableHandle);
		handle->AllSolutionsReady.Remove(AllSolutionsHandle);
		handle->QueryError.Remove(QueryErrorHandle);
	}
}
