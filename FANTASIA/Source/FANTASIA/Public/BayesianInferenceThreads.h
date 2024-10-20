#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "Core.h"
#include "FANTASIATypes.h"

#pragma warning (disable : 4263)
#pragma warning (disable : 4264)
#pragma warning (disable : 4265)
#pragma warning (disable : 4701)
#pragma warning (disable : 4996)

#include "agrum/BN/BayesNet.h"
#include "agrum/BN/inference/lazyPropagation.h"
#include "agrum/BN/inference/ShaferShenoyInference.h"
#include "agrum/BN/inference/variableElimination.h"

#pragma warning (default : 4263)
#pragma warning (default : 4264)
#pragma warning (default : 4265)
#pragma warning (default : 4701)
#pragma warning (default : 4996)


DECLARE_DELEGATE(InferenceAvailableDelegate);
DECLARE_EVENT(BayesianInferenceThread, InferenceAvailableEvent);

enum class BayesianModelType : uint8 {
	BAYESIAN_NETWORK = 0,
	INFLUENCE_DIAGRAM = 1,
};

//~~~~~ Multi Threading ~~~
class BayesianInferenceThread : public FRunnable
{

private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static BayesianInferenceThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;
	BayesianModelType modelType;
	InferenceAvailableEvent InferenceAvailable;
	gum::JointTargetedInference<double>* BNinferenceEngine;

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	BayesianInferenceThread(gum::JointTargetedInference<double>* inference);

	virtual ~BayesianInferenceThread();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static BayesianInferenceThread* setup(gum::JointTargetedInference<double>* inference);

	void makeInference();

	FDelegateHandle InferenceAvailableSubscribeUser(InferenceAvailableDelegate& UseDelegate);
	void InferenceAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};
