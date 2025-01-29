#include "BayesianInferenceThreads.h"

BayesianInferenceThread* BayesianInferenceThread::Runnable = NULL;

BayesianInferenceThread::BayesianInferenceThread(gum::JointTargetedInference<double>* inference) : StopTaskCounter(0) {
	modelType = BayesianModelType::BAYESIAN_NETWORK;
	BNinferenceEngine = inference;
	Thread = FRunnableThread::Create(this, TEXT("BayesianInferenceThread"), 0, TPri_BelowNormal);
}

BayesianInferenceThread::BayesianInferenceThread(gum::InfluenceDiagramInference<double>* inference) : StopTaskCounter(0) {
	modelType = BayesianModelType::INFLUENCE_DIAGRAM;
	IDinferenceEngine = inference;
	Thread = FRunnableThread::Create(this, TEXT("BayesianInferenceThread"), 0, TPri_BelowNormal);
}

BayesianInferenceThread::~BayesianInferenceThread() {
	delete Thread;
	Thread = NULL;
}

bool BayesianInferenceThread::Init() {
	return true;
}

uint32 BayesianInferenceThread::Run() {
	//makeInference();
	return 0;
}

void BayesianInferenceThread::Stop() {
	StopTaskCounter.Increment();
}

void BayesianInferenceThread::EnsureCompletion() {
	Stop();
	Thread->WaitForCompletion();
}

void BayesianInferenceThread::Shutdown() {
	if (Runnable) {
		Runnable = NULL;
	}
}

BayesianInferenceThread* BayesianInferenceThread::setup(gum::JointTargetedInference<double>* inference) {
	if (FPlatformProcess::SupportsMultithreading()) {
		Runnable = new BayesianInferenceThread(inference);
	}
	return Runnable;
}

BayesianInferenceThread* BayesianInferenceThread::setup(gum::InfluenceDiagramInference<double>* inference) {
	if (FPlatformProcess::SupportsMultithreading()) {
		Runnable = new BayesianInferenceThread(inference);
	}
	return Runnable;
}

void BayesianInferenceThread::makeInference() {
	switch (modelType) {
	case BayesianModelType::BAYESIAN_NETWORK:
		try {
			BNinferenceEngine->makeInference();
			InferenceAvailable.Broadcast();
		}
		catch (gum::NotFound& e)
			UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
		break;
	case BayesianModelType::INFLUENCE_DIAGRAM:
		try {
			IDinferenceEngine->makeInference();
			InferenceAvailable.Broadcast();
		}
		catch (gum::NotFound& e)
			UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
	}
}

FDelegateHandle BayesianInferenceThread::InferenceAvailableSubscribeUser(InferenceAvailableDelegate& UseDelegate) {
	return InferenceAvailable.Add(UseDelegate);
}

void BayesianInferenceThread::InferenceAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) {
	InferenceAvailable.Remove(DelegateHandle);
}