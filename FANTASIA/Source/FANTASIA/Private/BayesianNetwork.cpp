// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BayesianNetwork.h"
#include <vector>


std::vector<float> myLinspace(float start, float end, int points) {
	std::vector<float> res(points);
	float step = (end - start) / (points - 1);
	int i = 0;
	float cand;

	for (auto& e : res) {
		cand = start + step * i++;
		if (cand < end)
			e = cand;
		else
			e = end;
	}
	return res;
}

UBayesianNetwork::UBayesianNetwork(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
}

void UBayesianNetwork::Init() {
	if (!initialized) {	
		initialized = true;
	}

	switch (InferenceAlgorithm)
	{
	case InferenceAlgs::Lazy_Propagation:
		inference = new gum::LazyPropagation<double>(&bn); break;
	case InferenceAlgs::ShaferShenoy:
		inference = new gum::ShaferShenoyInference<double>(&bn); break;
	case InferenceAlgs::VariableElimination:
		inference = new gum::VariableElimination<double>(&bn); break;
	}
}

void UBayesianNetwork::inferenceComplete() {
	//handle->Shutdown();
	InferenceReady.Broadcast();
}

void UBayesianNetwork::makeInference() {
	if (!handle) {
		InferenceAvailableDelegate InferenceAvailableSubscriber;

		InferenceAvailableSubscriber.BindUObject(this, &UBayesianNetwork::inferenceComplete);

		handle = BayesianInferenceThread::setup(inference);
		InferenceAvailableHandle = handle->InferenceAvailableSubscribeUser(InferenceAvailableSubscriber);
	}
	handle->makeInference();
}

TMap<FString, float> UBayesianNetwork::getPosterior(FString variable) {
	const std::string nodeName(TCHAR_TO_UTF8(*variable));
	TMap<FString, float> out;
	unsigned int j;

	try {
		gum::Potential<double> result = inference->posterior(nodeName);
		gum::Instantiation inst(result);
		
		for (inst.setFirst(), j=0; !inst.end(); ++inst, ++j)
			out.Add(FString(result.variable(0).label(j).c_str()), result.get(inst));
	}
	catch (gum::NotFound& e)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
		out.Add(FString("NOTFOUND"), 0.0);
	}
	return out;
}

void UBayesianNetwork::writeBIF(FString file) {
	auto writer = gum::BIFWriter<double>();
	writer.write(TCHAR_TO_UTF8(*file), bn);
}

void UBayesianNetwork::erase(FString variable) {
	const std::string nodeName(TCHAR_TO_UTF8(*variable));
	
	TArray<FString> toRemove;

	for (FString arc : arcs)
		if (arc.Contains(variable))
			toRemove.Add(arc);

	for (FString arc : toRemove)
		arcs.Remove(arc);
	
	bn.erase(nodeName);
	nodeNames.Remove(variable);
	nodeDescriptions.Remove(variable);
}

void UBayesianNetwork::setBN(const FString& Filename) {
	gum::BIFReader<double> reader(&bn, TCHAR_TO_UTF8(*Filename));
	int result = reader.proceed();
	unsigned int j;
	FBayesianNodeStruct newNode;

	switch (InferenceAlgorithm) {
		case InferenceAlgs::Lazy_Propagation:
			inference = new gum::LazyPropagation<double>(&bn); break;
		case InferenceAlgs::ShaferShenoy:
			inference = new gum::ShaferShenoyInference<double>(&bn); break;
		case InferenceAlgs::VariableElimination:
			inference = new gum::VariableElimination<double>(&bn); break;
	}

	for (int i : bn.nodes()) {
		gum::Instantiation inst(bn.cpt(i));
		
		newNode.variables.Empty();
		newNode.values.Empty();
		newNode.parents.Empty();
		for (inst.setFirst(), j = 0; !inst.end(); ++inst, j++) {
			newNode.name = FString(bn.variable(i).name().c_str());
			if (j < bn.variable(i).domainSize())
				newNode.variables.Add(FString(bn.variable(i).label(j).c_str()));
			newNode.values.Add(bn.cpt(i).get(inst));
		}
		for (auto parent : bn.parents(i)) {
			newNode.parents.Add(FString(bn.variable(parent).name().c_str()));
		}
		serializedNodes.Add(newNode);
	}
	initialized = true;
}

void UBayesianNetwork::addLabelizedVariable(FString variable, FString description, TArray<FString> labels) {
	if (!nodeNames.Contains(variable)) {
		gum::LabelizedVariable newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description), 0);

		for (FString label : labels)
			newNode.addLabel(TCHAR_TO_UTF8(*label));

		bn.add(newNode);

		nodeNames.Add(variable);
		nodeDescriptions.Add(variable, description);
	}
}

void UBayesianNetwork::addDiscretizedVariable(FString variable, FString description, float minTick, float maxTick, float nPoints, BayesianNodeType nodeType) {
	if (!nodeNames.Contains(variable)) {
		gum::DiscretizedVariable<float> newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description));
		std::vector<float> ticks = myLinspace(minTick, maxTick, nPoints);

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
		nodeDescriptions.Add(variable, description);
	}
}

void UBayesianNetwork::addArc(FString parent, FString child) {

	FString newArc = parent + "_" + child;
	
	for (FString arc : arcs)
		if (arc == newArc)
			return;
	try {
		bn.addArc(TCHAR_TO_UTF8(*parent), TCHAR_TO_UTF8(*child));
		arcs.Add(newArc);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs while adding arc"), e.errorType().c_str(), e.errorContent().c_str());
}

int UBayesianNetwork::idFromName(FString variable) {
	if (nodeNames.Contains(variable))
		return bn.idFromName(TCHAR_TO_UTF8(*variable));
	UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs does not exist"), TCHAR_TO_UTF8(*variable));
	return -1;
}

void UBayesianNetwork::fillWith(FString variable, float value) {
	try {
		bn.cpt(TCHAR_TO_UTF8(*variable)).fillWith(value);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
}

void UBayesianNetwork::fillCPT(FString variable, TArray<float> values) {
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	std::vector<double> cptValues;
	for (float value : values)
		cptValues.push_back(value);

	try {
		bn.cpt(nodeName).fillWith(cptValues);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());	
}

void UBayesianNetwork::setEvidence(FString variable, TArray<float> data) {
	std::vector<double> vec;
	for (const float value : data)
		vec.push_back(value);

	auto var = TCHAR_TO_UTF8(*variable);

	try {
		if (inference->hasEvidence(var))
			inference->eraseEvidence(var);
		inference->addEvidence(var, vec);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("[Bayesian Network] %hs from %hs while adding evidence"), e.errorType().c_str(), e.errorContent().c_str());
}

TArray<FString> UBayesianNetwork::getMarkovBlanketNodes(FString variable) {
	TArray<FString> markovBlaketNodes;

	if (nodeNames.Contains(variable)) {
		gum::MarkovBlanket markovBlanket = gum::MarkovBlanket(bn, TCHAR_TO_UTF8(*variable));

		for (auto node : markovBlanket.nodes())
			markovBlaketNodes.Add(bn.variable(node).name().c_str());
	}
	return markovBlaketNodes;
}

void UBayesianNetwork::eraseAllEvidence() {
	inference->eraseAllEvidence();
}

void UBayesianNetwork::eraseEvidence(FString variable) {
	inference->eraseEvidence(TCHAR_TO_UTF8(*variable));
}

double UBayesianNetwork::getEntropy(FString variable) {
	if (!variable.IsEmpty() and nodeNames.Contains(variable))
		return (float) inference->H(TCHAR_TO_UTF8(*variable));
	return 0;
}

