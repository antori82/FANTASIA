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

	FString RelativePath = FPaths::GameSourceDir();
	FString FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
	char* result = TCHAR_TO_ANSI(*FullPath);
	PlTermv initav(2);
	initav[1] = PlAtom(result);
	PlCall("working_directory", initav);

	UE_LOG(LogTemp, Display, TEXT("query started!"));
	PlCall("consult", PlTermv(PlAtom("bigProject")));
	PlTermv arrayv(2);
	PlTerm_tail tail(arrayv[1]); //tail of the prolog list
	PlTerm temp(PlTerm(PlAtom("the")));
	if (!tail.append(temp)) {
		UE_LOG(LogTemp, Warning, TEXT("couldn't add atom to list..."));
	}
	PlTerm temp1(PlTerm(PlAtom("woman")));
	if (!tail.append(temp1)) {
		UE_LOG(LogTemp, Warning, TEXT("couldn't add atom to list..."));
	}
	PlTerm temp2(PlTerm(PlAtom("likes")));
	if (!tail.append(temp2)) {
		UE_LOG(LogTemp, Warning, TEXT("couldn't add atom to list..."));
	}
	PlTerm temp3(PlTerm(PlAtom("the")));
	if (!tail.append(temp3)) {
		UE_LOG(LogTemp, Warning, TEXT("couldn't add atom to list..."));
	}
	PlTerm temp4(PlTerm(PlAtom("man")));
	if (!tail.append(temp4)) {
		UE_LOG(LogTemp, Warning, TEXT("couldn't add atom to list..."));
	}

	if (!tail.close()) {
		UE_LOG(LogTemp, Warning, TEXT("couldn't unify tail of list with []..."));
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("list created!"));
	}

	PlQuery query("smallProject", "main", arrayv);
	try {
		PlCheckFail(query.next_solution());
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred: %s"), *FString(err.what()));
	}
	catch (PlFail f) {
		UE_LOG(LogTemp, Warning, TEXT("query failed"));
	}


	


	outString = arrayv[0].as_string().c_str();
	/*
	try {
		PlCall("consult", PlTermv(PlAtom("knowledge_base")));
	}
	catch (const PlException& err) {
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString("couldn't open prolog file... error: ") + FString(err.what()));
	//	cerr << "couldn't open prolog file... error: " << err.what();
		
	}
	PlTermv av(1);
	
	PlQuery q("character", av);
	q.next_solution();
	//cout << "out: " << av[0].as_string() << "\n";
	*/

}

void USWIPrologComponent::openPrologFile(const FString filename) {
	//char* myfile = TCHAR_TO_ANSI(*filename);
	FString filePath = FPaths::EngineSourceDir();
	filePath = FPaths::GetPath("./bigProject.pl");
	char* myfile = TCHAR_TO_ANSI(*filePath);
	try {
		PlCall("consult", PlTermv(PlAtom(myfile)));
	}
	catch (const PlException& err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred: %s"), *FsError);
	}
}

void USWIPrologComponent::startProlog() {
	if (_putenv("SWI_HOME_DIR=C:\\Program Files\\swipl")) return;
	int argc = 1;

	FString RelativePath = FPaths::GameSourceDir();
	RelativePath = FPaths::GetPath("../plugins/FANTASIA/ThirdParty/SWIProlog/libs/libswipl.dll");
	FString FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
	char* result = TCHAR_TO_ANSI(*FullPath);
	if (!PL_initialise(argc, &result)) {
		PL_halt(1);
		UE_LOG(LogTemp, Warning, TEXT("failed to initialise prolog"));
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("prolog initialised succesfully"));
		UE_LOG(LogTemp, Display, TEXT("path for prolog: %s"), *FullPath);
	}
		

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
