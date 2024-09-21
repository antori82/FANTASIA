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

void USWIPrologComponent::SWIPLsubmitQuery(USWIPrologTerm* inRuleOrFactTerm, const TArray<FString> inElements, FSWIPrologResponse& outResponse) {
	FString inRuleOrFact = translateTerm(inRuleOrFactTerm);
	char* queryTerm = TCHAR_TO_ANSI(*inRuleOrFact);
	int32 airity = inElements.Num();
	PlTermv queryElements(airity);
	int32 index = 0;
	for (FString element : inElements) {
		char* term = TCHAR_TO_ANSI(*element);
		if (isupper(term[0])) {
			queryElements[index] = PlTerm_var();
			index++;
		}
		else {
			queryElements[index] = PlCompound(term);
			index++;
		}
	}
	PlQuery myQuery(queryTerm, queryElements);
	FSWIPrologResponse currentResponse;
	currentResponse.airity = airity;
	currentResponse.queryName = inRuleOrFact;
	TArray<FString> resultSet;
	bool bResult;
	try {
		bResult = myQuery.next_solution();
		while (bResult) {
			USWIPrologSolution currentSolution;
			currentSolution.bResult = bResult;
			for (int i = 0; i < queryElements.size(); i++) {
				FString sResult = FString(ANSI_TO_TCHAR(queryElements[i].as_string().c_str()));
				currentSolution.resultSet.Add(sResult);
			}
			currentResponse.results.Add(&currentSolution);
			bResult = myQuery.next_solution();
		}
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while performing query: %s"), *FsError);
	}
	
}

void USWIPrologComponent::SWIPLassertFact(USWIPrologTerm* fact, bool& bResult) {
	FString ruleOrFact = translateTerm(fact);
	char* stringRuleOrFact = TCHAR_TO_ANSI(*ruleOrFact);
	try {
		PlCall("assert", PlTermv(PlCompound(stringRuleOrFact)));
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while asserting rule or fact: %s"), *FsError);
	}
}

void USWIPrologComponent::SWIPLassertRule(USWIPrologRule* rule, bool& bResult) {
	FString ruleOrFact = translateRule(rule);
	char* stringRuleOrFact = TCHAR_TO_ANSI(*ruleOrFact);
	try {
		PlCall("assert", PlTermv(PlCompound(stringRuleOrFact)));
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while asserting rule or fact: %s"), *FsError);
	}
}

void USWIPrologComponent::SWIPLretract(USWIPrologTerm* ruleOrFactTerm, bool& bResult) {
	FString ruleOrFact = translateTerm(ruleOrFactTerm);
	char* stringRuleOrFact = TCHAR_TO_ANSI(*ruleOrFact);
	try {
		PlCall("retract", PlTermv(PlCompound(stringRuleOrFact)));
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while asserting rule or fact: %s"), *FsError);
	}
}

//TODO:: make sure it works
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
		UE_LOG(LogTemp, Warning, TEXT("error occurred while consulting file: %s"), *FsError);
	}
}

void USWIPrologComponent::startProlog() {
	if (_putenv("SWI_HOME_DIR=C:\\Program Files\\swipl")) return;
	int argc = 1;

	//TODO:: fix route to path
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

FString USWIPrologComponent::translateTerm(USWIPrologTerm* term) {
	if (USWIPrologAtom* atom = Cast<USWIPrologAtom>(term)) {
		return "'" + atom->atomValue + "'";
	}
	if (USWIPrologVariable* var = Cast<USWIPrologVariable>(term)) {
		return "_" + var->varName;
	}
	if (USWIPrologInteger* num = Cast<USWIPrologInteger>(term)) {
		return FString::FromInt(num->intValue);
	}
	if (USWIPrologFloat* num = Cast<USWIPrologFloat>(term)) {
		return FString::FromInt(num->floatValue);
	}
	if (USWIPrologCompound* compound = Cast<USWIPrologCompound>(term)) {
		TArray arguments = compound->arguments;
		USWIPrologTerm** termRef = arguments.GetData();
		FString terms = "";
		for (int i = 0; i < arguments.Num(); i++) {
			terms = terms + translateTerm(termRef[i]);
			if ((i+1) < arguments.Num()) terms = terms + ",";
		}
		return compound->compoundName + "(" + terms + ")";
	}
	if (USWIPrologList* list = Cast<USWIPrologList>(term)) {
		FString terms = "";
		for (int i = 0; i < list->elements.Num(); i++) {
			terms = terms + translateTerm(list->elements[i]);
			if ((i + 1) < list->elements.Num()) terms = terms + ",";
		}
		return "[" + terms + "]";
	}
	if (USWIPrologHeadToTail* list = Cast<USWIPrologHeadToTail>(term)) {
		FString headTerms = "";
		for (int i = 0; i < list->headElements.Num(); i++) {
			headTerms = headTerms + translateTerm(list->headElements[i]);
			if ((i + 1) < list->headElements.Num()) headTerms = headTerms + ",";
		}
		FString tailString = "";
		if (USWIPrologVariable* tailVar = Cast<USWIPrologVariable>(&list->tail)) {
			tailString = "_" + tailVar->varName;
		}
		else if (USWIPrologList* tailList = Cast<USWIPrologList>(&list->tail)) {
			tailString = translateTerm(tailList);
		}
		else {
			USWIPrologHeadToTail* headToTail = Cast<USWIPrologHeadToTail>(&list->tail);
			tailString = translateTerm(headToTail);
		}
		return "[" + headTerms + "|" + tailString + "]";
	}
}

FString USWIPrologComponent::translateRule(USWIPrologRule* rule) {
	FString head = translateTerm(&rule->head);
	FString body = translateRuleBody(&rule->body);
	return head + ":-" + body;
}

FString USWIPrologComponent::translateRuleBody(USWIPrologRuleBody* ruleBody) {
	FString swiOperator;
	switch (ruleBody->logicOperator) {
	case SWIPrologOperation::OR:
		swiOperator = ";";
		break;
	case SWIPrologOperation::CONDITION:
		swiOperator = "->";
		break;
	case SWIPrologOperation::AND:
		swiOperator = ",";
		break;
	}
	FString firstString = "";
	FString secondString = "";
	ISWIPrologRuleInterface* first = ruleBody->rulePair.Key;
	ISWIPrologRuleInterface* second = ruleBody->rulePair.Value;
	if (USWIPrologTerm* firstTerm = Cast<USWIPrologTerm>(first)) {
		firstString = translateTerm(firstTerm);
	}
	else {
		USWIPrologRuleBody* firstRuleBody = Cast<USWIPrologRuleBody>(first);
		firstString = translateRuleBody(firstRuleBody);
	}
	if (USWIPrologTerm* secondTerm = Cast<USWIPrologTerm>(second)) {
		secondString = translateTerm(secondTerm);
	}
	else {
		USWIPrologRuleBody* secondRuleBody = Cast<USWIPrologRuleBody>(second);
		secondString = translateRuleBody(secondRuleBody);
	}
	return firstString + swiOperator + secondString;
}

// Called when the game starts
void USWIPrologComponent::BeginPlay()
{

	//TODO:: check if correct
	Super::BeginPlay();
	startProlog();

	// ...

}



// Called every frame
void USWIPrologComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
