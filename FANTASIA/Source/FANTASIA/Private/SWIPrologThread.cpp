/**
 * @file SWIPrologThread.cpp
 * @brief Implementation of the SWI-Prolog worker thread, command dispatch, and term translation.
 */

// Fill out your copyright notice in the Description page of Project Settings.
#include "SWIPrologThread.h"
#include "Async/Async.h"

// ── Static Members ───────────────────────────────────────────────────────────

SWIPrologThread* SWIPrologThread::Runnable = NULL;
std::atomic<bool> SWIPrologThread::stop{false};
std::atomic<bool> SWIPrologThread::initialised{false};

// ── Construction / Destruction ────────────────────────────────────────────────

SWIPrologThread::SWIPrologThread() : StopTaskCounter(0) {
	WakeEvent = FPlatformProcess::GetSynchEventFromPool(false);
	Thread = FRunnableThread::Create(this, TEXT("SWIPrologThread"), 0, TPri_Normal);
}

SWIPrologThread::~SWIPrologThread() {
	delete Thread;
	Thread = NULL;
	FPlatformProcess::ReturnSynchEventToPool(WakeEvent);
	WakeEvent = nullptr;
}

// ── FRunnable Interface ──────────────────────────────────────────────────────

bool SWIPrologThread::Init() {
	return true;
}

uint32 SWIPrologThread::Run() {
	stop.store(false, std::memory_order_relaxed);
	initialised.store(false, std::memory_order_relaxed);
	executeCommands();
	return 0;
}

void SWIPrologThread::Stop() {
	StopTaskCounter.Increment();
}

void SWIPrologThread::EnsureCompletion() {
	Stop();
	stop.store(true, std::memory_order_release);
	if (WakeEvent)
	{
		WakeEvent->Trigger();
	}
}

void SWIPrologThread::Shutdown() {
	if (Runnable) {
		Runnable->EnsureCompletion();
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

// ── Internal Helpers (worker thread) ─────────────────────────────────────────

void SWIPrologThread::openPrologFile_(const FString& filename) {
	try {
		PlCall("consult", PlTermv(PlAtom(TCHAR_TO_ANSI(*filename))));
		UE_LOG(LogTemp, Warning, TEXT("File %s opened successfully"), *filename);
	}
	catch (const PlException& err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while consulting file: %s"), *FsError);
		broadcastError(FsError);
	}
}

// --- Public command submission (called from game thread) ---
// All of these translate UObjects to strings on the calling (game) thread,
// then enqueue plain data for the worker. No UObject* crosses threads.

void SWIPrologThread::openPrologFile(const FString& filename) {
	FPrologCommand Cmd;
	Cmd.Type = EPrologCommandType::ConsultFile;
	Cmd.StringData = filename;
	CommandQueue.Enqueue(MoveTemp(Cmd));
	WakeEvent->Trigger();
}

void SWIPrologThread::consultString(const FString& prologCode) {
	FPrologCommand Cmd;
	Cmd.Type = EPrologCommandType::ConsultString;
	Cmd.StringData = prologCode;
	CommandQueue.Enqueue(MoveTemp(Cmd));
	WakeEvent->Trigger();
}

void SWIPrologThread::SWIPLassert(USWIPrologObject* prologObject, bool firstClause) {
	// Translate on game thread — safe to access UObject here
	FString translated;
	if (USWIPrologTerm* fact = Cast<USWIPrologTerm>(prologObject))
		translated = translateTerm(fact);
	else
		translated = translateRule(Cast<USWIPrologRule>(prologObject));

	FPrologCommand Cmd;
	Cmd.Type = EPrologCommandType::Assert;
	Cmd.StringData = MoveTemp(translated);
	Cmd.BoolData = firstClause;
	CommandQueue.Enqueue(MoveTemp(Cmd));
	WakeEvent->Trigger();
}

void SWIPrologThread::SWIPLretract(USWIPrologTerm* ruleOrFactTerm) {
	// Translate on game thread — safe to access UObject here
	FPrologCommand Cmd;
	Cmd.Type = EPrologCommandType::Retract;
	Cmd.StringData = translateTerm(ruleOrFactTerm);
	CommandQueue.Enqueue(MoveTemp(Cmd));
	WakeEvent->Trigger();
}

void SWIPrologThread::submitQuery(USWIPrologTerm* inRuleOrFactTerm) {
	// Translate the UObject term tree to a Prolog string on the game thread,
	// so no UObject pointer crosses to the worker thread.
	FPrologCommand Cmd;
	Cmd.Type = EPrologCommandType::QueryString;
	Cmd.StringData = translateTerm(inRuleOrFactTerm);
	CommandQueue.Enqueue(MoveTemp(Cmd));
	WakeEvent->Trigger();
}

void SWIPrologThread::submitQueryString(const FString& queryString) {
	FPrologCommand Cmd;
	Cmd.Type = EPrologCommandType::QueryString;
	Cmd.StringData = queryString;
	CommandQueue.Enqueue(MoveTemp(Cmd));
	WakeEvent->Trigger();
}

void SWIPrologThread::submitFindAll(const FString& queryString) {
	FPrologCommand Cmd;
	Cmd.Type = EPrologCommandType::FindAll;
	Cmd.StringData = queryString;
	CommandQueue.Enqueue(MoveTemp(Cmd));
	WakeEvent->Trigger();
}

void SWIPrologThread::requestNextSolution() {
	FPrologCommand Cmd;
	Cmd.Type = EPrologCommandType::NextSolution;
	CommandQueue.Enqueue(MoveTemp(Cmd));
	WakeEvent->Trigger();
}

// ── Query Execution (worker thread) ──────────────────────────────────────────

void SWIPrologThread::nextSolution() {
	if (myQuery == NULL)
	{
		return;
	}

	int bResult;
	try {
		bResult = myQuery->next_solution();

		// Build result data on the worker thread (plain data, no UObjects)
		TArray<FString> resultSet;
		resultSet.Reserve(inArity);
		bool verified = (bResult == PL_S_TRUE);

		for (int i = 0; i < inArity; i++) {
			resultSet.Emplace(ANSI_TO_TCHAR(inQueryElements[i].as_string().c_str()));
		}

		// Marshal to game thread: create UObject and broadcast there
		AsyncTask(ENamedThreads::GameThread, [this, ResultSet = MoveTemp(resultSet), verified]() mutable {
			currentSolution = NewObject<USWIPrologSolution>();
			currentSolution->verified = verified;
			currentSolution->resultSet = MoveTemp(ResultSet);
			SolutionAvailable.Broadcast();
		});
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error occurred while performing query: %s"), *FsError);
		broadcastError(FsError);
	}
}

// ── Prolog Engine Initialization ─────────────────────────────────────────────

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
		(void)dir[1].unify_atom(PlAtom(TCHAR_TO_ANSI(*resFolderPath)));
		PlCall("working_directory", dir);

		UE_LOG(LogTemp, Display, TEXT("Prolog initialised succesfully"));
	}
}

// ── Term Translation (game thread) ───────────────────────────────────────────

FString SWIPrologThread::translateTerm(UObject* term) {
	if (USWIPrologAtom* atom = Cast<USWIPrologAtom>(term)) {
		FString result;
		result.Reserve(atom->atomValue.Len() + 2);
		result.AppendChar('\'');
		result.Append(atom->atomValue);
		result.AppendChar('\'');
		return result;
	}
	if (USWIPrologVariable* var = Cast<USWIPrologVariable>(term)) {
		FString result;
		result.Reserve(var->varName.Len() + 1);
		result.AppendChar('_');
		result.Append(var->varName);
		return result;
	}
	if (USWIPrologInteger* num = Cast<USWIPrologInteger>(term)) {
		return FString::FromInt(num->intValue);
	}
	if (USWIPrologFloat* num = Cast<USWIPrologFloat>(term)) {
		return FString::SanitizeFloat(num->floatValue);
	}
	if (USWIPrologCut* cut = Cast<USWIPrologCut>(term)) {
		return TEXT("!");
	}
	if (USWIPrologCompound* compound = Cast<USWIPrologCompound>(term)) {
		const TArray<USWIPrologTerm*>& arguments = compound->arguments;
		int32 numArgs = arguments.Num();
		FString result;
		result.Reserve(64);
		result.Append(compound->compoundName);
		result.AppendChar('(');
		for (int i = 0; i < numArgs; i++) {
			if (i > 0) result.AppendChar(',');
			result.Append(translateTerm(arguments[i]));
		}
		result.AppendChar(')');
		return result;
	}
	if (USWIPrologList* list = Cast<USWIPrologList>(term)) {
		int32 numElements = list->elements.Num();
		FString result;
		result.Reserve(64);
		result.AppendChar('[');
		for (int i = 0; i < numElements; i++) {
			if (i > 0) result.AppendChar(',');
			result.Append(translateTerm(list->elements[i]));
		}
		result.AppendChar(']');
		return result;
	}
	if (USWIPrologHeadToTail* list = Cast<USWIPrologHeadToTail>(term)) {
		int32 numHeadElements = list->headElements.Num();
		FString result;
		result.Reserve(64);
		result.AppendChar('[');
		for (int i = 0; i < numHeadElements; i++) {
			if (i > 0) result.AppendChar(',');
			result.Append(translateTerm(list->headElements[i]));
		}
		result.AppendChar('|');
		result.Append(translateTerm(list->tail));
		result.AppendChar(']');
		return result;
	}
	return TEXT("");
}

FString SWIPrologThread::translateRule(UObject* rule) {
	USWIPrologRule* rulePtr = Cast<USWIPrologRule>(rule);
	FString result;
	result.Reserve(128);
	result.Append(translateTerm(rulePtr->head));
	result.Append(TEXT(":-"));
	result.Append(translateRuleBody(rulePtr->body));
	return result;
}

FString SWIPrologThread::translateRuleBody(UObject* ruleBodyObject) {
	if (USWIPrologTerm* term = Cast<USWIPrologTerm>(ruleBodyObject)) {
		return translateTerm(term);
	}
	USWIPrologRuleBody* ruleBody = Cast<USWIPrologRuleBody>(ruleBodyObject);

	const TCHAR* swiOperator;
	switch (ruleBody->prologOperator) {
	case SWIPrologOperation::OR:          swiOperator = TEXT(";");    break;
	case SWIPrologOperation::CONDITION:   swiOperator = TEXT("->");   break;
	case SWIPrologOperation::AND:         swiOperator = TEXT(",");    break;
	case SWIPrologOperation::DIVIDE:      swiOperator = TEXT("/");    break;
	case SWIPrologOperation::EQUAL:       swiOperator = TEXT("=:=");  break;
	case SWIPrologOperation::IS:          swiOperator = TEXT(" is "); break;
	case SWIPrologOperation::MINUS:       swiOperator = TEXT("-");    break;
	case SWIPrologOperation::MULTIPLY:    swiOperator = TEXT("*");    break;
	case SWIPrologOperation::PLUS:        swiOperator = TEXT("+");    break;
	case SWIPrologOperation::UNEQUAL:     swiOperator = TEXT("=\\="); break;
	case SWIPrologOperation::LESSTHAN:    swiOperator = TEXT("<");    break;
	case SWIPrologOperation::MORETHAN:    swiOperator = TEXT(">");    break;
	case SWIPrologOperation::LESSOREQUAL: swiOperator = TEXT("=<");   break;
	case SWIPrologOperation::MOREOREQUAL: swiOperator = TEXT(">=");   break;
	case SWIPrologOperation::TERMEQUAL:   swiOperator = TEXT("==");   break;
	case SWIPrologOperation::TERMNOTEQUAL:swiOperator = TEXT("\\=="); break;
	default:                              swiOperator = TEXT(",");    break;
	}

	FString result;
	result.Reserve(128);

	if (USWIPrologTerm* firstTerm = Cast<USWIPrologTerm>(ruleBody->firstRule))
		result.Append(translateTerm(firstTerm));
	else
		result.Append(translateRuleBody(ruleBody->firstRule));

	result.Append(swiOperator);

	if (USWIPrologTerm* secondTerm = Cast<USWIPrologTerm>(ruleBody->secondRule))
		result.Append(translateTerm(secondTerm));
	else
		result.Append(translateRuleBody(ruleBody->secondRule));

	return result;
}

void SWIPrologThread::broadcastError(const FString& errorMessage) {
	AsyncTask(ENamedThreads::GameThread, [this, Error = errorMessage]() {
		QueryError.Broadcast(Error);
	});
}

void SWIPrologThread::executeQueryFromString(const FString& queryString) {
	if (myQuery != NULL)
		myQuery->close_destroy();

	try {
		// Parse the string as a Prolog term using term_to_atom
		PlTermv av(2);
		(void)av[1].unify_atom(PlAtom(TCHAR_TO_ANSI(*queryString)));
		PlCall("term_to_atom", av);
		// av[0] now holds the parsed term — extract functor and arity
		std::string functorName = av[0].name().as_string();
		size_t arity = av[0].arity();

		PlTermv queryElements(arity);
		for (size_t i = 0; i < arity; i++) {
			(void)queryElements[i].unify_term(av[0][i + 1]);
		}

		myQuery = new PlQuery(functorName.c_str(), queryElements);
		inArity = static_cast<int>(arity);
		inQueryElements = queryElements;

		nextSolution();
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error parsing query string '%s': %s"), *queryString, *FsError);
		broadcastError(FsError);
	}
}

void SWIPrologThread::executeFindAll(const FString& queryString) {
	if (myQuery != NULL)
	{
		myQuery->close_destroy();
		myQuery = NULL;
	}

	try {
		PlTermv av(2);
		(void)av[1].unify_atom(PlAtom(TCHAR_TO_ANSI(*queryString)));
		PlCall("term_to_atom", av);
		std::string functorName = av[0].name().as_string();
		size_t arity = av[0].arity();

		PlTermv queryElements(arity);
		for (size_t i = 0; i < arity; i++) {
			(void)queryElements[i].unify_term(av[0][i + 1]);
		}

		PlQuery query(functorName.c_str(), queryElements);

		// Collect raw results on worker thread (plain data, no UObjects)
		struct FSolutionData {
			TArray<FString> ResultSet;
			bool Verified;
		};
		TArray<FSolutionData> allResults;

		int bResult;
		while (true) {
			bResult = query.next_solution();
			if (bResult == PL_S_FALSE)
				break;

			FSolutionData& data = allResults.AddDefaulted_GetRef();
			data.Verified = (bResult == PL_S_TRUE);
			data.ResultSet.Reserve(static_cast<int32>(arity));
			for (size_t i = 0; i < arity; i++) {
				data.ResultSet.Emplace(ANSI_TO_TCHAR(queryElements[i].as_string().c_str()));
			}

			if (bResult != PL_S_TRUE)
				break;
		}

		// Marshal to game thread: create UObjects there
		AsyncTask(ENamedThreads::GameThread, [this, Results = MoveTemp(allResults)]() {
			TArray<USWIPrologSolution*> Solutions;
			Solutions.Reserve(Results.Num());
			for (const auto& Data : Results) {
				USWIPrologSolution* Sol = NewObject<USWIPrologSolution>();
				Sol->verified = Data.Verified;
				Sol->resultSet = Data.ResultSet;
				Solutions.Add(Sol);
			}
			AllSolutionsReady.Broadcast(Solutions);
		});
	}
	catch (PlException err) {
		FString FsError = FString(ANSI_TO_TCHAR(err.what()));
		UE_LOG(LogTemp, Warning, TEXT("error in findall for '%s': %s"), *queryString, *FsError);
		broadcastError(FsError);
	}
}

// ── Command Dispatch (worker thread) ─────────────────────────────────────────

void SWIPrologThread::processCommand(const FPrologCommand& Command) {
	switch (Command.Type)
	{
	case EPrologCommandType::ConsultFile:
		openPrologFile_(Command.StringData);
		break;

	case EPrologCommandType::ConsultString:
		try {
			FString consultCmd = FString::Printf(TEXT("atom_to_term('%s', T, _), assert(T)"), *Command.StringData);
			PlCall(TCHAR_TO_ANSI(*consultCmd));
		}
		catch (PlException err) {
			FString FsError = FString(ANSI_TO_TCHAR(err.what()));
			UE_LOG(LogTemp, Warning, TEXT("error consulting string: %s"), *FsError);
			broadcastError(FsError);
		}
		break;

	case EPrologCommandType::Assert:
		try {
			PlCall(Command.BoolData ? "asserta" : "assertz", PlTermv(PlCompound(TCHAR_TO_ANSI(*Command.StringData))));
		}
		catch (PlException err) {
			FString FsError = FString(ANSI_TO_TCHAR(err.what()));
			UE_LOG(LogTemp, Warning, TEXT("error occurred while asserting rule or fact: %s"), *FsError);
			broadcastError(FsError);
		}
		break;

	case EPrologCommandType::Retract:
		try {
			PlCall("retract", PlTermv(PlCompound(TCHAR_TO_ANSI(*Command.StringData))));
		}
		catch (PlException err) {
			FString FsError = FString(ANSI_TO_TCHAR(err.what()));
			UE_LOG(LogTemp, Warning, TEXT("error occurred while retracting rule or fact: %s"), *FsError);
			broadcastError(FsError);
		}
		break;

	case EPrologCommandType::QueryString:
		executeQueryFromString(Command.StringData);
		break;

	case EPrologCommandType::NextSolution:
		nextSolution();
		break;

	case EPrologCommandType::FindAll:
		executeFindAll(Command.StringData);
		break;
	}
}

// ── Main Loop ────────────────────────────────────────────────────────────────

void SWIPrologThread::executeCommands() {
	while (!stop.load(std::memory_order_relaxed)) {

		if (!initialised.load(std::memory_order_relaxed)) {
			startProlog();
			initialised.store(true, std::memory_order_relaxed);
		}

		// Block until a command is enqueued or stop is requested
		WakeEvent->Wait();

		// Process all queued commands
		FPrologCommand Command;
		while (CommandQueue.Dequeue(Command)) {
			if (stop.load(std::memory_order_relaxed)) break;
			processCommand(Command);
		}
	}
}
