#pragma once
#pragma warning (disable : 4800)
#pragma warning (disable : 4673)
#pragma warning (disable : 4670)
#pragma warning (disable : 4668)
#pragma warning (disable : 4834)

#include "FANTASIATypes.h"
#include "Containers/Queue.h"
#include <atomic>
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#pragma push_macro("verify")
#undef verify
#include <SWI-cpp2.h>
#pragma pop_macro("verify")
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"

#pragma warning (default : 4800)
#pragma warning (default : 4673)
#pragma warning (default : 4670)
#pragma warning (default : 4668)
#pragma warning (default : 4834)

DECLARE_DELEGATE(SolutionAvailableDelegate);
DECLARE_EVENT(SWIPrologThread, SolutionAvailableEvent);

enum class EPrologCommandType : uint8
{
	ConsultFile,
	ConsultString,
	Assert,
	Retract,
	QueryString,
	NextSolution,
	FindAll
};

struct FPrologCommand
{
	EPrologCommandType Type;
	FString StringData;
	bool BoolData = false;
};

class SWIPrologThread : public FRunnable
{

private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static SWIPrologThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Event to wake the worker thread when commands are enqueued */
	FEvent* WakeEvent;

	/** Lock-free MPSC command queue (multiple game-thread producers, single worker consumer) */
	TQueue<FPrologCommand, EQueueMode::Mpsc> CommandQueue;

	PlQuery* myQuery = NULL;
	FString resFolderPath;
	PlTermv inQueryElements;
	int inArity = 0;
	static std::atomic<bool> initialised;
	static std::atomic<bool> stop;

	FString translateTerm(UObject* term);
	FString translateRule(UObject* rule);
	FString translateRuleBody(UObject* ruleBodyObject);

	void startProlog();
	void executeCommands();
	void openPrologFile_(const FString& filename);
	void processCommand(const FPrologCommand& Command);
	void executeQueryFromString(const FString& queryString);
	void executeFindAll(const FString& queryString);
	void nextSolution();
	void broadcastError(const FString& errorMessage);

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	SWIPrologThread();

	SolutionAvailableEvent SolutionAvailable;

	// Delegate for all-solutions results (FindAll)
	DECLARE_EVENT_OneParam(SWIPrologThread, FAllSolutionsReadyEvent, TArray<USWIPrologSolution*>);
	FAllSolutionsReadyEvent AllSolutionsReady;

	// Delegate for query errors
	DECLARE_EVENT_OneParam(SWIPrologThread, FQueryErrorEvent, FString);
	FQueryErrorEvent QueryError;

	/** Latest solution snapshot, safe to read from game thread only inside delegate callbacks */
	USWIPrologSolution* currentSolution = nullptr;

	virtual ~SWIPrologThread();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static SWIPrologThread* setup();

	/** Submit a query from UObject term tree. Translates to string on calling thread. */
	void submitQuery(USWIPrologTerm* inRuleOrFactTerm);
	void submitQueryString(const FString& queryString);
	void submitFindAll(const FString& queryString);
	void requestNextSolution();
	void openPrologFile(const FString& filename);
	void consultString(const FString& prologCode);
	void SWIPLassert(USWIPrologObject* prologObject, bool firstClause);
	void SWIPLretract(USWIPrologTerm* ruleOrFactTerm);

	FDelegateHandle SolutionAvailableSubscribeUser(SolutionAvailableDelegate& UseDelegate);
	void SolutionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};
