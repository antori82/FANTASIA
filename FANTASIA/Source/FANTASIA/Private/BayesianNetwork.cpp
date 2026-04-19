/**
 * @file BayesianNetwork.cpp
 * @brief Implementation of UBayesianNetwork -- aGrUM-based Bayesian network with async inference.
 */

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BayesianNetwork.h"
#include <vector>

// ── Static Utility Functions ─────────────────────────────────────────────────

/** Convert a TArray<float> to a std::vector<double> for aGrUM API consumption. */
static std::vector<double> ToStdVector(const TArray<float>& Values)
{
	std::vector<double> Result;
	Result.reserve(Values.Num());
	for (const float V : Values)
		Result.push_back(static_cast<double>(V));
	return Result;
}

/** Convert an aGrUM Potential into a Blueprint-friendly TMap<FString, float>. */
static TMap<FString, float> PotentialToMap(const gum::Potential<double>& Result)
{
	TMap<FString, float> Out;
	const auto& Var = Result.variable(0);
	Out.Reserve(Var.domainSize());
	gum::Instantiation Inst(Result);
	unsigned int j = 0;
	for (Inst.setFirst(); !Inst.end(); ++Inst, ++j)
		Out.Add(FString(Var.label(j).c_str()), Result.get(Inst));
	return Out;
}

// ── Construction ─────────────────────────────────────────────────────────────

UBayesianNetwork::UBayesianNetwork(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
}

// ── Inference Engine ─────────────────────────────────────────────────────────

void UBayesianNetwork::CreateInferenceEngine() {
	switch (InferenceAlgorithm)
	{
	case InferenceAlgs::Lazy_Propagation:
		inference.Reset(new gum::LazyPropagation<double>(&bn)); break;
	case InferenceAlgs::ShaferShenoy:
		inference.Reset(new gum::ShaferShenoyInference<double>(&bn)); break;
	case InferenceAlgs::VariableElimination:
		inference.Reset(new gum::VariableElimination<double>(&bn)); break;
	}
}

void UBayesianNetwork::Init() {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Cannot reinitialize while inference is running"));
		return;
	}
	CreateInferenceEngine();
	initialized = true;
}

void UBayesianNetwork::makeInference() {
	if (!inference)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Inference engine not initialized. Call Init() first."));
		return;
	}

	if (bInferenceRunning.exchange(true))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Inference already in progress"));
		return;
	}

	// Prevent GC from collecting this UObject while async work is in flight
	AddToRoot();

	gum::JointTargetedInference<double>* InfPtr = inference.Get();

	AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this, InfPtr]()
	{
		try {
			InfPtr->makeInference();
		}
		catch (gum::NotFound& e) {
			UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
		}

		AsyncTask(ENamedThreads::GameThread, [this]()
		{
			bInferenceRunning.store(false);
			RemoveFromRoot();
			InferenceReady.Broadcast();
			OnInferenceReady.Broadcast();
		});
	});
}

TMap<FString, float> UBayesianNetwork::getPosterior(const FString& variable) {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Cannot read posterior while inference is running"));
		return TMap<FString, float>();
	}

	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	try {
		return PotentialToMap(inference->posterior(nodeName));
	}
	catch (gum::NotFound& e)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
		TMap<FString, float> out;
		out.Add(FString("NOTFOUND"), 0.0);
		return out;
	}
}

void UBayesianNetwork::writeBIF(const FString& file) {
	auto writer = gum::BIFWriter<double>();
	writer.write(TCHAR_TO_UTF8(*file), bn);
}

void UBayesianNetwork::erase(const FString& variable) {
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	arcs.RemoveAllSwap([&](const FString& arc) {
		if (arc.Contains(variable)) {
			arcSet.Remove(arc);
			return true;
		}
		return false;
	});

	bn.erase(nodeName);
	nodeNames.Remove(variable);
	nodeNameSet.Remove(variable);
	nodeDescriptions.Remove(variable);
}

// ── BIF Loading ──────────────────────────────────────────────────────────────

void UBayesianNetwork::setBN(const FString& Filename) {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Cannot load BIF while inference is running"));
		return;
	}
	gum::BIFReader<double> reader(&bn, TCHAR_TO_UTF8(*Filename));
	int result = reader.proceed();
	unsigned int j;
	FBayesianNodeStruct newNode;

	CreateInferenceEngine();

	serializedNodes.Reserve(bn.size());
	for (int i : bn.nodes()) {
		gum::Instantiation inst(bn.cpt(i));
		const auto& var = bn.variable(i);

		newNode.name = FString(var.name().c_str());
		newNode.variables.Empty();
		newNode.values.Empty();
		newNode.parents.Empty();
		newNode.variables.Reserve(var.domainSize());
		for (inst.setFirst(), j = 0; !inst.end(); ++inst, j++) {
			if (j < var.domainSize())
				newNode.variables.Add(FString(var.label(j).c_str()));
			newNode.values.Add(bn.cpt(i).get(inst));
		}
		for (auto parent : bn.parents(i)) {
			newNode.parents.Add(FString(bn.variable(parent).name().c_str()));
		}
		serializedNodes.Add(newNode);
	}
	initialized = true;
}

// ── Network Construction ─────────────────────────────────────────────────────

void UBayesianNetwork::addLabelizedVariable(const FString& variable, const FString& description, const TArray<FString>& labels) {
	if (!nodeNameSet.Contains(variable)) {
		gum::LabelizedVariable newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description), 0);

		for (const FString& label : labels)
			newNode.addLabel(TCHAR_TO_UTF8(*label));

		bn.add(newNode);

		nodeNames.Add(variable);
		nodeNameSet.Add(variable);
		nodeDescriptions.Add(variable, description);
	}
}

void UBayesianNetwork::addDiscretizedVariable(const FString& variable, const FString& description, float minTick, float maxTick, float nPoints, BayesianNodeType nodeType) {
	if (!nodeNameSet.Contains(variable)) {
		gum::DiscretizedVariable<float> newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description));
		std::vector<float> ticks = Linspace(minTick, maxTick, nPoints);

		for (float i : ticks)
			newNode.addTick(i);

		switch (nodeType) {
		case BayesianNodeType::NORMAL: bn.add(newNode); break;
		case BayesianNodeType::AMPLITUDE: bn.addAMPLITUDE(newNode); break;
		case BayesianNodeType::AND: bn.addAND(newNode); break;
		case BayesianNodeType::COUNT: bn.addCOUNT(newNode); break;
		case BayesianNodeType::EXISTS: bn.addEXISTS(newNode); break;
		case BayesianNodeType::FORALL: bn.addFORALL(newNode); break;
		case BayesianNodeType::MAX: bn.addMAX(newNode); break;
		case BayesianNodeType::MEDIAN: bn.addMEDIAN(newNode); break;
		case BayesianNodeType::MIN: bn.addMIN(newNode); break;
		}
		nodeNames.Add(variable);
		nodeNameSet.Add(variable);
		nodeDescriptions.Add(variable, description);
	}
}

void UBayesianNetwork::addArc(const FString& parent, const FString& child) {
	FString newArc = parent + "_" + child;

	if (arcSet.Contains(newArc))
		return;

	try {
		bn.addArc(TCHAR_TO_UTF8(*parent), TCHAR_TO_UTF8(*child));
		arcs.Add(newArc);
		arcSet.Add(newArc);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs while adding arc"), e.errorType().c_str(), e.errorContent().c_str());
}

int UBayesianNetwork::idFromName(const FString& variable) {
	if (nodeNameSet.Contains(variable))
		return bn.idFromName(TCHAR_TO_UTF8(*variable));
	UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs does not exist"), TCHAR_TO_UTF8(*variable));
	return -1;
}

void UBayesianNetwork::fillWith(const FString& variable, float value) {
	try {
		bn.cpt(TCHAR_TO_UTF8(*variable)).fillWith(value);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
}

void UBayesianNetwork::fillCPT(const FString& variable, const TArray<float>& values) {
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	try {
		bn.cpt(nodeName).fillWith(ToStdVector(values));
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
}

// ── Evidence ─────────────────────────────────────────────────────────────────

void UBayesianNetwork::setEvidence(const FString& variable, const TArray<float>& data) {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Cannot set evidence while inference is running"));
		return;
	}

	auto var = TCHAR_TO_UTF8(*variable);

	try {
		if (inference->hasEvidence(var))
			inference->eraseEvidence(var);
		inference->addEvidence(var, ToStdVector(data));
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs while adding evidence"), e.errorType().c_str(), e.errorContent().c_str());
}

TArray<FString> UBayesianNetwork::getMarkovBlanketNodes(const FString& variable) {
	TArray<FString> markovBlanketNodes;

	if (nodeNameSet.Contains(variable)) {
		gum::MarkovBlanket markovBlanket = gum::MarkovBlanket(bn, TCHAR_TO_UTF8(*variable));
		markovBlanketNodes.Reserve(markovBlanket.nodes().size());

		for (auto node : markovBlanket.nodes())
			markovBlanketNodes.Add(bn.variable(node).name().c_str());
	}
	return markovBlanketNodes;
}

void UBayesianNetwork::eraseAllEvidence() {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Cannot erase evidence while inference is running"));
		return;
	}
	inference->eraseAllEvidence();
}

void UBayesianNetwork::eraseEvidence(const FString& variable) {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Cannot erase evidence while inference is running"));
		return;
	}
	inference->eraseEvidence(TCHAR_TO_UTF8(*variable));
}

double UBayesianNetwork::getEntropy(const FString& variable) {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] Cannot read entropy while inference is running"));
		return 0;
	}
	if (!variable.IsEmpty() and nodeNameSet.Contains(variable))
		return (float) inference->H(TCHAR_TO_UTF8(*variable));
	return 0;
}
