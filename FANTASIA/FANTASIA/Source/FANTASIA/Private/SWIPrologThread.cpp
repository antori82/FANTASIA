// Fill out your copyright notice in the Description page of Project Settings.
#include "SWIPrologThread.h"


SWIPrologThread* SWIPrologThread::Runnable = NULL;
bool SWIPrologThread::stop = false;

SWIPrologThread::SWIPrologThread() : StopTaskCounter(0) {
	Thread = FRunnableThread::Create(this, TEXT("SWIPrologThread"), 0, TPri_BelowNormal);
}

SWIPrologThread::~SWIPrologThread() {
	delete Thread;
	Thread = NULL;
}

bool SWIPrologThread::Init() {
	return true;
}

uint32 SWIPrologThread::Run() {
	startProlog();
	stop = false;
	currentSolution = NewObject<USWIPrologSolution>();
	executeCommands();
	return 0;
}

void SWIPrologThread::Stop() {
	StopTaskCounter.Increment();
}

void SWIPrologThread::EnsureCompletion() {
	Stop();
	//Thread->WaitForCompletion();
}

void SWIPrologThread::Shutdown() {
	if (Runnable) {
		stop = true;
		Runnable = NULL;
	}
}

SWIPrologThread* SWIPrologThread::setup() {
	if (!Runnable)
		Runnable = new SWIPrologThread();
	return Runnable;
}

FDelegateHandle SWIPrologThread::SolutionAvailableSubscribeUser(SolutionAvailableDelegate& UseDelegate) {
	return SolutionAvailable.Add(UseDelegate);
}

void SWIPrologThread::SolutionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) {
	SolutionAvailable.Remove(DelegateHandle);
}

void SWIPrologThread::openPrologFile_(FString filename) {
	char* myfile = TCHAR_TO_ANSI(*filename);
	try {
		PlCall("consult", PlTermv(PlAtom(myfile)));
		UE_LOG(LogTemp, Warning, TEXT("File %s opened successfully"), *filename);
	}
	catch (const PlException& err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while consulting file: %s"), *FsError);
	}
}

void SWIPrologThread::openPrologFile(FString filename) {
	consultFile = filename;
}

void SWIPrologThread::SWIPLassert(USWIPrologObject* prologObject, bool asFirstClause, bool& bResult) {
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

void SWIPrologThread::SWIPLretract(USWIPrologTerm* ruleOrFactTerm, bool& bResult) {
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

void SWIPrologThread::startProlog() {

	std::string ProjectPath = TCHAR_TO_UTF8(*FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()));
	std::string SWIPath = "/Plugins/FANTASIA/FANTASIA/ThirdParty/SWIProlog/swiTest/swipl";

	std::string HomePath = "SWI_HOME_DIR=" + ProjectPath + SWIPath;

	if (_putenv(HomePath.c_str()) != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add Prolog home environment variable"));
		return;
	}

	char* av[1];
	av[0] = (char*)"swipl";

	int argc = 1;

	if (!PL_initialise(argc, av))
	{
		PL_halt(1);
		UE_LOG(LogTemp, Warning, TEXT("Failed to initialise prolog"));
	}
	else {
		resFolderPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + "Resources/";
		PlTermv dir(2);
		dir[1].unify_atom(PlAtom(TCHAR_TO_ANSI(*resFolderPath)));
		PlCall("working_directory", dir);

		UE_LOG(LogTemp, Display, TEXT("Prolog initialised succesfully"));

	}
}

FString SWIPrologThread::translateTerm(UObject* term) {
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
			if ((i + 1) < arguments.Num()) terms = terms + ",";
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

FString SWIPrologThread::translateRule(UObject* rule) {
	USWIPrologRule* rulePtr = Cast<USWIPrologRule>(rule);
	FString head = translateTerm(rulePtr->head);
	FString body = translateRuleBody(rulePtr->body);
	return head + ":-" + body;
}

FString SWIPrologThread::translateRuleBody(UObject* ruleBodyObject) {
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

void SWIPrologThread::executeCommands() {
	while (true) {
		if (stop)
			break;

		if (consultFile != "")
		{
			openPrologFile_(consultFile);
			consultFile = "";
		}
			

		if (IsValid(currentQuery)) {
			if (myQuery != NULL)
				myQuery->close_destroy();

			int arity = 0;
			char* queryTerm;
			TArray<FString> inElements;
			if (USWIPrologCompound* compound = Cast<USWIPrologCompound>(currentQuery)) {
				queryTerm = TCHAR_TO_ANSI(*compound->compoundName);
				UE_LOG(LogTemp, Display, TEXT("Query name %s part of the compound"), *compound->compoundName);
				for (USWIPrologTerm* term : compound->arguments) {
					arity = arity + 1;
					inElements.Add(translateTerm(term));
					UE_LOG(LogTemp, Display, TEXT("Query element %s part of the compound"), *translateTerm(term));
				}
			}
			else {
				USWIPrologAtom* atom = Cast<USWIPrologAtom>(currentQuery);
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

			myQuery = new PlQuery(queryTerm, queryElements);

			inArity = arity;
			inQueryElements = queryElements;

			nextSolution();
			currentQuery = NULL;
			//currentQuery->ConditionalBeginDestroy();
		}
	}
}


void SWIPrologThread::nextSolution() {
	int bResult;
	try {
		bResult = myQuery->next_solution();
		if (bResult == PL_S_FALSE)
			currentSolution->verified = false;
		if (bResult == PL_S_TRUE)
			currentSolution->verified = true;

		currentSolution->resultSet.Empty();

		for (int i = 0; i < inArity; i++) {
			FString sResult = FString(ANSI_TO_TCHAR(inQueryElements[i].as_string().c_str()));
			currentSolution->resultSet.Add(sResult);
		}
		SolutionAvailable.Broadcast();
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while performing query: %s"), *FsError);
	}
}

void SWIPrologThread::submitQuery(USWIPrologTerm* inRuleOrFactTerm) {
	currentQuery = inRuleOrFactTerm;
}
