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


void USWIPrologComponent::GenericMethod(bool bWasSuccessful)
{
	if (bWasSuccessful)
		std::cout << "generic method called true";
	else
		std::cout << "generic method called false";

}

void USWIPrologComponent::submitQuery(FString query, SWIPrologEnumTest enumItem, FString aString, TMap<FString, FString> aMapOfStrings, FString anotherString = "SWIProlog") {
	std::cout << "query submitted";
}

void USWIPrologComponent::initializeProlog() {
	if (_putenv("SWI_HOME_DIR=C:\\Program Files\\swipl")) return;
	//if (!PL_initialise(1, "Prolog?"))
	//	PL_halt(1);
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
