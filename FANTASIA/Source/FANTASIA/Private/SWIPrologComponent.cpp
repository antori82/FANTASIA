// Fill out your copyright notice in the Description page of Project Settings.

#include "SWIPrologComponent.h"
#include "Misc/Base64.h"
#include "Async/Async.h"
#include <iostream>


// Sets default values for this component's properties
USWIPrologComponent::USWIPrologComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USWIPrologComponent::SWIPLsubmitQuery(USWIPrologTerm* inRuleOrFactTerm) {
	
	handle->submitQuery(inRuleOrFactTerm);
}

void USWIPrologComponent::SWIPLassert(USWIPrologObject* prologObject, bool asFirstClause, bool& bResult) {
	handle->SWIPLassert(prologObject, asFirstClause, bResult);
}

void USWIPrologComponent::SWIPLretract(USWIPrologTerm* ruleOrFactTerm, bool& bResult) {
	handle->SWIPLretract(ruleOrFactTerm, bResult);
}


void USWIPrologComponent::openPrologFile(const FString filename) {
	handle->openPrologFile(filename);
}

void USWIPrologComponent::inferenceComplete() {
	SolutionAvailable.Broadcast(handle->currentSolution);
}

void USWIPrologComponent::nextSolution() {
	handle->nextSolution();
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

	}
}

// Called when the game starts
void USWIPrologComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	handle->SolutionAvailableUnsubscribeUser(SolutionAvailableHandle);
}



// Called every frame
void USWIPrologComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

