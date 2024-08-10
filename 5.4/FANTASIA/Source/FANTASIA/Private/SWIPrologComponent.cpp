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

void USWIPrologComponent::submitQuery(const bool choice, FString& outString) {
	outString = "query started!";
	try {
		PlCall("consult", PlTermv(PlAtom("knowledge_base")));
	}
	catch (const PlException& err) {
		cerr << "couldn't open prolog file... error: " << err.what();
	}
	PlTermv av(1);
	
	PlQuery q("character", av);
	q.next_solution();
	cout << "out: " << av[0].as_string() << "\n";

}

void USWIPrologComponent::startProlog() {
	if (_putenv("SWI_HOME_DIR=C:\\Program Files\\swipl")) return;
	int argc = 1;
	FString path = FPaths::GameSourceDir();
	char myString[200];
	strcpy_s(myString, (const char*)TCHAR_TO_ANSI(*path));
	char* argv[1] = {
		myString
	};
	if (!PL_initialise(argc,argv)){}
		PL_halt(1);
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
