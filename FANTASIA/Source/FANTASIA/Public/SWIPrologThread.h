/**
 * @file SWIPrologThread.h
 * @brief Dedicated background thread that owns the embedded SWI-Prolog engine and processes Prolog commands.
 */

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

/** Single-cast delegate used by USWIPrologComponent to subscribe to solution notifications. */
DECLARE_DELEGATE(SolutionAvailableDelegate);

/** Multicast event broadcast on the game thread when a single solution is ready. */
DECLARE_EVENT(SWIPrologThread, SolutionAvailableEvent);

/**
 * @brief Identifies the type of command enqueued for the Prolog worker thread.
 */
enum class EPrologCommandType : uint8
{
	ConsultFile,    ///< Load a .pl file via consult/1.
	ConsultString,  ///< Assert clauses from a raw Prolog string.
	Assert,         ///< Assert a translated fact or rule (asserta/assertz).
	Retract,        ///< Retract a translated fact or rule.
	QueryString,    ///< Open a new query from a Prolog string and fetch the first solution.
	NextSolution,   ///< Advance the current open query to its next solution.
	FindAll         ///< Collect every solution for a query in one batch.
};

/**
 * @brief Plain-data command sent from the game thread to the Prolog worker.
 *
 * All UObject translation happens on the game thread before the command is
 * enqueued, so no UObject pointer ever crosses to the worker thread.
 */
struct FPrologCommand
{
	/** The operation to execute. */
	EPrologCommandType Type;

	/** Serialized Prolog string (query, filename, translated term, etc.). */
	FString StringData;

	/** Auxiliary boolean (e.g., asserta vs assertz). */
	bool BoolData = false;
};

/**
 * @brief Singleton FRunnable that owns the SWI-Prolog engine on a dedicated thread.
 *
 * Game-thread callers enqueue FPrologCommand objects via the public submit/request
 * methods. The worker thread dequeues and executes them sequentially, marshalling
 * results back to the game thread through delegates.
 *
 * @note Only one Prolog engine can exist per process. The singleton is created
 *       lazily via setup() and destroyed via Shutdown().
 *
 * @see USWIPrologComponent
 */
class SWIPrologThread : public FRunnable
{

	// ── Private State ────────────────────────────────────────────────────

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

	/** Currently open SWI-Prolog query, or NULL if none is active. */
	PlQuery* myQuery = NULL;

	/** Absolute path to the project Resources/ folder (Prolog working directory). */
	FString resFolderPath;

	/** Term vector holding the current query's argument slots. */
	PlTermv inQueryElements;

	/** Arity of the current open query. */
	int inArity = 0;

	/** True once PL_initialise has succeeded. */
	static std::atomic<bool> initialised;

	/** Signals the worker thread to exit its main loop. */
	static std::atomic<bool> stop;

	/**
	 * @brief Recursively translate a USWIPrologTerm tree into a Prolog string.
	 * @param term The UObject-based Prolog term (atom, variable, compound, list, etc.).
	 * @return A Prolog-syntax string representation.
	 */
	FString translateTerm(UObject* term);

	/**
	 * @brief Translate a USWIPrologRule into a Prolog clause string (Head :- Body).
	 * @param rule The rule UObject.
	 * @return A Prolog clause string.
	 */
	FString translateRule(UObject* rule);

	/**
	 * @brief Recursively translate a rule body (terms joined by operators) into a Prolog string.
	 * @param ruleBodyObject A USWIPrologTerm or USWIPrologRuleBody.
	 * @return The body portion of a Prolog clause.
	 */
	FString translateRuleBody(UObject* ruleBodyObject);

	/** Initialize the SWI-Prolog engine, setting SWI_HOME_DIR and working directory. */
	void startProlog();

	/** Main loop: blocks on WakeEvent, then drains the command queue. */
	void executeCommands();

	/**
	 * @brief Internal helper that calls consult/1 on the worker thread.
	 * @param filename Absolute path to a .pl file.
	 */
	void openPrologFile_(const FString& filename);

	/**
	 * @brief Dispatch a single dequeued command to the appropriate handler.
	 * @param Command The command to process.
	 */
	void processCommand(const FPrologCommand& Command);

	/**
	 * @brief Parse a Prolog string query, open a PlQuery, and fetch the first solution.
	 * @param queryString Prolog query text, e.g. "parent(X, tom)".
	 */
	void executeQueryFromString(const FString& queryString);

	/**
	 * @brief Collect all solutions for a query and broadcast them at once.
	 * @param queryString Prolog query text.
	 */
	void executeFindAll(const FString& queryString);

	/** Advance the current open query to the next solution. */
	void nextSolution();

	/**
	 * @brief Marshal an error message to the game thread and broadcast it.
	 * @param errorMessage Human-readable error description.
	 */
	void broadcastError(const FString& errorMessage);

	// ── Public Interface ─────────────────────────────────────────────────

public:

	/** Construct the thread and start it immediately. */
	SWIPrologThread();

	/** Event broadcast on the game thread when a single solution is available. */
	SolutionAvailableEvent SolutionAvailable;

	/** Event broadcast on the game thread with all collected solutions from FindAll. */
	DECLARE_EVENT_OneParam(SWIPrologThread, FAllSolutionsReadyEvent, TArray<USWIPrologSolution*>);
	FAllSolutionsReadyEvent AllSolutionsReady;

	/** Event broadcast on the game thread when a query encounters an error. */
	DECLARE_EVENT_OneParam(SWIPrologThread, FQueryErrorEvent, FString);
	FQueryErrorEvent QueryError;

	/** Latest solution snapshot, safe to read from game thread only inside delegate callbacks. */
	USWIPrologSolution* currentSolution = nullptr;

	virtual ~SWIPrologThread();

	// ── FRunnable Interface ──────────────────────────────────────────────

	/** @brief Called on the new thread before Run(). @return Always true. */
	virtual bool Init();

	/** @brief Main entry point for the worker thread. @return Exit code (always 0). */
	virtual uint32 Run();

	/** @brief Signals the thread to stop via StopTaskCounter. */
	virtual void Stop();

	// ── Lifecycle ────────────────────────────────────────────────────────

	/** Block until the worker thread has fully stopped. */
	void EnsureCompletion();

	/** Shut down and destroy the singleton worker thread. Safe to call from any thread. */
	static void Shutdown();

	/**
	 * @brief Lazily create (or return) the singleton Prolog thread.
	 * @return Pointer to the running SWIPrologThread instance.
	 */
	static SWIPrologThread* setup();

	// ── Command Submission (game thread) ─────────────────────────────────

	/**
	 * @brief Submit a query built from a UObject term tree.
	 * @param inRuleOrFactTerm Root of the term tree (translated to string on calling thread).
	 */
	void submitQuery(USWIPrologTerm* inRuleOrFactTerm);

	/**
	 * @brief Submit a query from a raw Prolog string.
	 * @param queryString Prolog query text, e.g. "parent(X, tom)".
	 */
	void submitQueryString(const FString& queryString);

	/**
	 * @brief Collect all solutions for a query string. Results arrive via AllSolutionsReady.
	 * @param queryString Prolog query text.
	 */
	void submitFindAll(const FString& queryString);

	/** Request the next solution for the current open query. */
	void requestNextSolution();

	/**
	 * @brief Enqueue a consult command for a .pl file.
	 * @param filename Absolute path to the Prolog source file.
	 */
	void openPrologFile(const FString& filename);

	/**
	 * @brief Enqueue Prolog source code to be asserted from a string.
	 * @param prologCode Prolog clauses as text.
	 */
	void consultString(const FString& prologCode);

	/**
	 * @brief Assert a UObject fact or rule into the Prolog database.
	 * @param prologObject The fact (USWIPrologTerm) or rule (USWIPrologRule).
	 * @param firstClause If true, use asserta; otherwise assertz.
	 */
	void SWIPLassert(USWIPrologObject* prologObject, bool firstClause);

	/**
	 * @brief Retract a fact or rule from the Prolog database.
	 * @param ruleOrFactTerm The term to retract.
	 */
	void SWIPLretract(USWIPrologTerm* ruleOrFactTerm);

	// ── Delegate Management ──────────────────────────────────────────────

	/**
	 * @brief Subscribe a delegate to the SolutionAvailable event.
	 * @param UseDelegate The delegate to bind.
	 * @return Handle that must be passed to SolutionAvailableUnsubscribeUser on teardown.
	 */
	FDelegateHandle SolutionAvailableSubscribeUser(SolutionAvailableDelegate& UseDelegate);

	/**
	 * @brief Unsubscribe a previously registered solution delegate.
	 * @param DelegateHandle The handle returned by SolutionAvailableSubscribeUser.
	 */
	void SolutionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};
