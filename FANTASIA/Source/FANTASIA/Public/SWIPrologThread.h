#pragma once
#pragma warning (disable : 4800)
#pragma warning (disable : 4673)
#pragma warning (disable : 4670)
#pragma warning (disable : 4668)
#pragma warning (disable : 4834)

#include "FANTASIATypes.h"
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

class SWIPrologThread : public FRunnable
{

private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static SWIPrologThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	PlQuery* myQuery = NULL;
	FString resFolderPath;
	PlTermv inQueryElements;
	USWIPrologTerm* currentQuery = NULL;
	FString consultFile = "";
	int inArity;

	static bool stop;
	FString translateTerm(UObject* term);
	FString translateRule(UObject* rule);
	FString translateRuleBody(UObject* ruleBodyObject);

	void startProlog();
	void executeCommands();
	void openPrologFile_(FString myfile);

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	SWIPrologThread();

	SolutionAvailableEvent SolutionAvailable;
	USWIPrologSolution* currentSolution = NewObject<USWIPrologSolution>();

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

	void submitQuery(USWIPrologTerm* inRuleOrFactTerm);
	void nextSolution();
	void openPrologFile(FString myfile);
	void SWIPLassert(USWIPrologObject* prologObject, bool asFirstClause, bool& bResult);
	void SWIPLretract(USWIPrologTerm* ruleOrFactTerm, bool& bResult);

	FDelegateHandle SolutionAvailableSubscribeUser(SolutionAvailableDelegate& UseDelegate);
	void SolutionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};