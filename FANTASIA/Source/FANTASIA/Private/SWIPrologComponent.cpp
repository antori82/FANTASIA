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

void USWIPrologComponent::SWIPLsubmitQuery(USWIPrologTerm* inRuleOrFactTerm, FSWIPrologResponse& outResponse) {
	int arity = 0;
	char* queryTerm;
	TArray<FString> inElements;
	if (USWIPrologCompound* compound = Cast<USWIPrologCompound>(inRuleOrFactTerm)) {
		queryTerm = TCHAR_TO_ANSI(*compound->compoundName);
		UE_LOG(LogTemp, Display, TEXT("Query name %s part of the compound"), *compound->compoundName);
		for (USWIPrologTerm* term : compound->arguments) {
			arity = arity + 1;
			inElements.Add(translateTerm(term));
			UE_LOG(LogTemp, Display, TEXT("Query element %s part of the compound"), *translateTerm(term));
		}
	}
	else {
		USWIPrologAtom* atom = Cast<USWIPrologAtom>(inRuleOrFactTerm);
		queryTerm = TCHAR_TO_ANSI(*atom->atomValue);
	}
	PlTermv queryElements(arity);
	int32 index = 0;
	for (FString element : inElements) {
		char* term = TCHAR_TO_ANSI(*element);
		queryElements[index] = PlCompound(term);
		index++;
		UE_LOG(LogTemp, Display, TEXT("element %s inside query vector"), *element);
	}
	PlQuery myQuery(queryTerm, queryElements);
	FSWIPrologResponse currentResponse;
	currentResponse.arity = arity;
	currentResponse.queryName = FString(ANSI_TO_TCHAR(queryTerm));
	TArray<FString> resultSet;
	int bResult;
	try {
		bResult = myQuery.next_solution();
		while (bResult == PL_S_TRUE) {
			UE_LOG(LogTemp, Display, TEXT("query solution development"));
			USWIPrologSolution* currentSolution = NewObject<USWIPrologSolution>();
			for (int i = 0; i < arity; i++) {
				FString sResult = FString(ANSI_TO_TCHAR(queryElements[i].as_string().c_str()));
				currentSolution->resultSet.Add(sResult);
			}
			UE_LOG(LogTemp, Display, TEXT("Solution set"));
			currentResponse.results.Add(currentSolution);
			UE_LOG(LogTemp, Display, TEXT("Solution added"));
			bResult = myQuery.next_solution();
		}
		outResponse = currentResponse;
		UE_LOG(LogTemp, Display, TEXT("Query %s performed succesfully, containing %d results"), *outResponse.queryName, outResponse.results.Num());
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while performing query: %s"), *FsError);
	}
	
}

void USWIPrologComponent::SWIPLassert(USWIPrologObject* prologObject, bool asFirstClause, bool& bResult) {
	FString ruleOrFact;

	if (USWIPrologTerm* fact = Cast<USWIPrologTerm>(prologObject))
		ruleOrFact = translateTerm(fact);
	else 
		ruleOrFact = translateRule(Cast<USWIPrologRule>(prologObject));
	
	char* stringRuleOrFact = TCHAR_TO_ANSI(*ruleOrFact);
	try {
		PlCall(asFirstClause ? "asserta" : "assertz", PlTermv(PlCompound(stringRuleOrFact)));
		bResult = true;
		UE_LOG(LogTemp, Display, TEXT("Assert Fact %s successful"), *ruleOrFact);
	}
	catch (PlException err) {
		bResult = false;
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while asserting rule or fact: %s"), *FsError);
	}
}

void USWIPrologComponent::SWIPLretract(USWIPrologTerm* ruleOrFactTerm, bool& bResult) {
	FString ruleOrFact = translateTerm(ruleOrFactTerm);
	char* stringRuleOrFact = TCHAR_TO_ANSI(*ruleOrFact);
	try {
		PlCall("retract", PlTermv(PlCompound(stringRuleOrFact)));
		bResult = true;
		UE_LOG(LogTemp, Display, TEXT("Retract successful"));
	}
	catch (PlException err) {
		bResult = false;
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while asserting rule or fact: %s"), *FsError);
	}
}

void USWIPrologComponent::SWIPLresetProlog()
{
	try {
		//prologEngine->cleanup();
		char* result ;
		if (!PL_initialise(1, &result)) {
			PL_halt(1);
			UE_LOG(LogTemp, Warning, TEXT("failed to initialise prolog"));
		}
		else {
			FString RelativePath = FPaths::GameSourceDir();
			RelativePath = FPaths::GetPath("../plugins/FANTASIA/ThirdParty/SWIProlog/libs/libswipl.dll");
			FString ResourcePath = FPaths::GameSourceDir();
			ResourcePath = FPaths::GetPath("../Resources");
			FString FullResourcePath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
			char* resourceResult = TCHAR_TO_ANSI(*FullResourcePath);
			PlTermv pv(2);
			pv[0] = PlAtom(result);
			pv[1] = PlAtom(resourceResult);
			PlCall("working_directory", pv);
			UE_LOG(LogTemp, Warning, TEXT("prolog restarted succesfully"));
		}
	}
	catch (PlException e) {
		UE_LOG(LogTemp, Display, TEXT("cleanup failed"));
	}
}

//TODO:: make sure it works
void USWIPrologComponent::openPrologFile(const FString filename) {
	char* myfile = TCHAR_TO_ANSI(*filename);
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

	FString RelativePath = FPaths::ProjectDir();
	RelativePath = FPaths::GetPath(RelativePath + "Plugins/FANTASIA/FANTASIA/Binaries/Win64/libswipl.dll");
	FString FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
	char* result = TCHAR_TO_ANSI(*FullPath);
	if (!PL_initialise(argc, &result)) {
		PL_halt(1);
		UE_LOG(LogTemp, Warning, TEXT("failed to initialise prolog"));
	}
	else {
		resFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
		resFolderPath = resFolderPath + "Resources/";
		char* resPathString = TCHAR_TO_ANSI(*resFolderPath);

		PlTermv dir(2);
		dir[1].unify_atom(PlAtom(resPathString));
		PlCall("working_directory", dir);
		
		UE_LOG(LogTemp, Display, TEXT("prolog initialised succesfully"));
		UE_LOG(LogTemp, Display, TEXT("path for prolog: %s, working directory: %s"), *FullPath, *resFolderPath);
	}
}

FString USWIPrologComponent::translateTerm(UObject* term) {
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
	if (USWIPrologCut* cut = Cast<USWIPrologCut>(term)) {
		return "!";
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
		UObject* tail = list->tail;
		FString tailString = "";
		if (USWIPrologVariable* tailVar = Cast<USWIPrologVariable>(tail)) {
			tailString = "_" + tailVar->varName;
		}
		else if (USWIPrologList* tailList = Cast<USWIPrologList>(tail)) {
			tailString = translateTerm(tailList);
		}
		else {
			USWIPrologHeadToTail* headToTail = Cast<USWIPrologHeadToTail>(tail);
			tailString = translateTerm(headToTail);
		}
		return "[" + headTerms + "|" + tailString + "]";
	}
	return "";
}

FString USWIPrologComponent::translateRule(UObject* rule) {
	USWIPrologRule* rulePtr = Cast<USWIPrologRule>(rule);
	FString head = translateTerm(rulePtr->head);
	FString body = translateRuleBody(rulePtr->body);
	return head + ":-" + body;
}

FString USWIPrologComponent::translateRuleBody(UObject* ruleBodyObject) {
	if (USWIPrologTerm* term = Cast<USWIPrologTerm>(ruleBodyObject)) {
		return translateTerm(term);
	}
	USWIPrologRuleBody* ruleBody = Cast<USWIPrologRuleBody>(ruleBodyObject);
	FString swiOperator;
	switch (ruleBody->prologOperator) {
	case SWIPrologOperation::OR:
		swiOperator = ";";
		break;
	case SWIPrologOperation::CONDITION:
		swiOperator = "->";
		break;
	case SWIPrologOperation::AND:
		swiOperator = ",";
		break;
	case SWIPrologOperation::DIVIDE:
		swiOperator = "/";
		break;
	case SWIPrologOperation::EQUAL:
		swiOperator = "=:=";
		break;
	case SWIPrologOperation::IS:
		swiOperator = " is ";
		break;
	case SWIPrologOperation::MINUS:
		swiOperator = "-";
		break;
	case SWIPrologOperation::MULTIPLY:
		swiOperator = "*";
		break;
	case SWIPrologOperation::PLUS:
		swiOperator = "+";
		break;
	case SWIPrologOperation::UNEQUAL:
		swiOperator = "=\\=";
		break;
	case SWIPrologOperation::LESSTHAN:
		swiOperator = "<";
		break;
	case SWIPrologOperation::MORETHAN:
		swiOperator = ">";
		break;
	case SWIPrologOperation::LESSOREQUAL:
		swiOperator = "=<";
		break;
	case SWIPrologOperation::MOREOREQUAL:
		swiOperator = ">=";
		break;
	case SWIPrologOperation::TERMEQUAL:
		swiOperator = "==";
		break;
	case SWIPrologOperation::TERMNOTEQUAL:
		swiOperator = "\\==";
		break;
	}
	FString firstString = "";
	FString secondString = "";
	UObject* first = ruleBody->firstRule;
	UObject* second = ruleBody->secondRule;
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
