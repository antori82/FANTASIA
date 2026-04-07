// Fill out your copyright notice in the Description page of Project Settings.


#include "InfluenceDiag.h"
#include <vector>

static std::vector<double> ToStdVector(const TArray<float>& Values)
{
	std::vector<double> Result;
	Result.reserve(Values.Num());
	for (const float V : Values)
		Result.push_back(static_cast<double>(V));
	return Result;
}

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

UInfluenceDiag::UInfluenceDiag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

void UInfluenceDiag::Init()
{
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot reinitialize while inference is running"));
		return;
	}
	inference.Reset(new gum::ShaferShenoyLIMIDInference<double>(&id));
	initialized = true;
}

void UInfluenceDiag::makeInference()
{
	if (!inference)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Inference engine not initialized. Call Init() first."));
		return;
	}

	if (bInferenceRunning.exchange(true))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Inference already in progress"));
		return;
	}

	// Prevent GC from collecting this UObject while async work is in flight
	AddToRoot();

	gum::InfluenceDiagramInference<double>* InfPtr = inference.Get();

	AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this, InfPtr]()
	{
		try {
			InfPtr->makeInference();
		}
		catch (gum::NotFound& e) {
			UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
		}

		AsyncTask(ENamedThreads::GameThread, [this]()
		{
			bInferenceRunning.store(false);
			RemoveFromRoot();
			InferenceReady.Broadcast();
		});
	});
}

TMap<FString, float> UInfluenceDiag::getPosterior(const FString& variable)
{
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot read posterior while inference is running"));
		return TMap<FString, float>();
	}

	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	try {
		return PotentialToMap(inference->posterior(nodeName));
	}
	catch (gum::NotFound& e) {
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
	}

	return TMap<FString, float>();
}

TMap<FString, float> UInfluenceDiag::getPosteriorUtility(const FString& variable)
{
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot read posterior utility while inference is running"));
		return TMap<FString, float>();
	}

	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	if (id.isUtilityNode(nodeName)) {
		try {
			return PotentialToMap(inference->posteriorUtility(nodeName));
		}
		catch (gum::NotFound& e)
			UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
	}
	return TMap<FString, float>();
}

TMap<FString, float> UInfluenceDiag::getMEU() {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot read MEU while inference is running"));
		return TMap<FString, float>();
	}

	TMap<FString, float> out;

	try {
		std::pair MEU = inference->MEU();

		out.Add("MEU", MEU.first);
		out.Add("Variance", MEU.second);
	}
	catch (gum::OperationNotAllowed& e)
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());

	return out;
}

double UInfluenceDiag::getEntropy(const FString& variable) {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot read entropy while inference is running"));
		return 0;
	}
	if (!variable.IsEmpty())
		return (float)inference->posterior((TCHAR_TO_UTF8(*variable))).entropy();
	return 0;
}

TMap<FString, FArrayFloat> UInfluenceDiag::optimalDecision(const FString& variable) {
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot read optimal decision while inference is running"));
		return TMap<FString, FArrayFloat>();
	}

	TMap<FString, FArrayFloat> out;

	try {
		gum::Potential<double> result = inference->optimalDecision(TCHAR_TO_UTF8(*variable));

		auto table = result.content();
		gum::Instantiation inst(*table);

		const auto& decisionVariable = table->variable(0);
		const gum::Size nbparents = table->nbrDim() - 1;

		// For each combinations of parents' conditions
		for (inst.setFirst(); !inst.end(); inst.incNotVar(decisionVariable)) {
			FString parentsConditions;
			FArrayFloat optimalChoices;

			if (nbparents > 0) {

				// Collect the combination
				parentsConditions.Append("|");
				for (gum::Idx i = 1; i <= nbparents; i++) {
					FString parentsCondition(table->variable(i).label(inst.val(i)).c_str());
					parentsConditions.Append(parentsCondition);
					parentsConditions.Append("|");
				}
			}

			// Collect the optimal choices
			for (inst.setFirstVar(decisionVariable); !inst.end(); inst.incVar(decisionVariable))
				optimalChoices.arrayFloat.Add(table->get(inst));

			out.Add(parentsConditions, optimalChoices);

			inst.setFirstVar(decisionVariable);
		}
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());

	return out;
}

void UInfluenceDiag::addEvidence(const FString& variable, const TArray<float>& data)
{
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot set evidence while inference is running"));
		return;
	}

	auto var = TCHAR_TO_UTF8(*variable);

	if (inference->hasEvidence(var))
		inference->eraseEvidence(var);
	inference->addEvidence(var, ToStdVector(data));
}

void UInfluenceDiag::eraseAllEvidence()
{
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot erase evidence while inference is running"));
		return;
	}
	inference->eraseAllEvidence();
}

void UInfluenceDiag::eraseEvidence(const FString& variable)
{
	if (bInferenceRunning.load())
	{
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] Cannot erase evidence while inference is running"));
		return;
	}
	inference->eraseEvidence(TCHAR_TO_UTF8(*variable));
}

void UInfluenceDiag::addDiscretizedVariable(const FString& variable, const FString& description, float minTick, float maxTick, float nPoints, InfluenceNodeType nodeType)
{
	if (!nodeNameSet.Contains(variable))  {
		gum::DiscretizedVariable<float> newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description));
		std::vector<float> ticks = Linspace(minTick, maxTick, nPoints);

		for (float i : ticks)
			newNode.addTick(i);

		switch (nodeType) {
		case InfluenceNodeType::CHANCE: id.addChanceNode(newNode); break;
		case InfluenceNodeType::UTILITY: id.addUtilityNode(newNode); break;
		case InfluenceNodeType::DECISION: id.addDecisionNode(newNode); break;
		}
		nodeNames.Add(variable);
		nodeNameSet.Add(variable);
		nodeDescriptions.Add(variable, description);
	}
}

void UInfluenceDiag::addLabelizedVariable(const FString& variable, const FString& description, const TArray<FString>& labels, InfluenceNodeType nodeType)
{
	if (!nodeNameSet.Contains(variable)) {
		gum::LabelizedVariable newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description), 0);
		nodeNames.Add(variable);
		nodeNameSet.Add(variable);
		nodeDescriptions.Add(variable, description);

		for (const FString& label : labels)
			newNode.addLabel(TCHAR_TO_UTF8(*label));

		switch (nodeType) {
		case InfluenceNodeType::CHANCE: id.addChanceNode(newNode); break;
		case InfluenceNodeType::UTILITY: id.addUtilityNode(newNode); break;
		case InfluenceNodeType::DECISION: id.addDecisionNode(newNode); break;
		}
	}
}

void UInfluenceDiag::addArc(const FString& parent, const FString& child) {
	FString newArc = parent + "_" + child;

	if (arcSet.Contains(newArc))
		return;

	try {
		id.addArc(TCHAR_TO_UTF8(*parent), TCHAR_TO_UTF8(*child));
		arcs.Add(newArc);
		arcSet.Add(newArc);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs while adding arc"), e.errorType().c_str(), e.errorContent().c_str());
}

void UInfluenceDiag::fillCPT(const FString& variable, const TArray<float>& values) {
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	if (!id.isUtilityNode(nodeName)) {
		try {
			id.cpt(nodeName).fillWith(ToStdVector(values));
		}
		catch (gum::NotFound& e)
			UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
	}
}

void UInfluenceDiag::fillUtility(const FString& variable, const TArray<float>& values) {
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	if (id.isUtilityNode(nodeName)) {
		try {
			id.utility(nodeName).fillWith(ToStdVector(values));
		}
		catch (gum::NotFound& e)
			UE_LOG(LogTemp, Warning, TEXT("[Influence Diagram] %hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
	}
}

void UInfluenceDiag::writeBIFXML(const FString& file) {
	auto writer = gum::BIFXMLIDWriter<double>();
	writer.write(TCHAR_TO_UTF8(*file), id);
}

void UInfluenceDiag::erase(const FString& variable) {
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	arcs.RemoveAllSwap([&](const FString& arc) {
		if (arc.Contains(variable)) {
			arcSet.Remove(arc);
			return true;
		}
		return false;
	});

	id.erase(nodeName);
	nodeNames.Remove(variable);
	nodeNameSet.Remove(variable);
	nodeDescriptions.Remove(variable);
}

int UInfluenceDiag::idFromName(const FString& variable) {
	return id.idFromName(TCHAR_TO_UTF8(*variable));
}

bool UInfluenceDiag::decisionOrderExists() {
	return id.decisionOrderExists();
}

TArray<int> UInfluenceDiag::decisionOrder() {
	TArray<int> out;
	std::vector<gum::NodeId> decisionSequence = id.decisionOrder();
	out.Reserve(decisionSequence.size());

	for (gum::NodeId idx : decisionSequence)
		out.Add(idx);

	return out;
}
