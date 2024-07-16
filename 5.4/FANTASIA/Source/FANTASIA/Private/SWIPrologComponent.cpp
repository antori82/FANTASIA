// Fill out your copyright notice in the Description page of Project Settings.


#include "SWIPrologComponent.h"
#include "Misc/Base64.h"
#include <iostream>
// Sets default values for this component's properties
USWIPrologComponent::USWIPrologComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


const char* USWIPrologComponent::GenericMethod(bool bWasSuccessful)
{
	if (bWasSuccessful)
		return "Hello True World!";
	else
		return "Hello False World!";

}

void USWIPrologComponent::submitQuery(const bool choice, FString& outString) {
	outString = USWIPrologComponent::GenericMethod(choice);
}

// Called when the game starts
void USWIPrologComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void USWIPrologComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
