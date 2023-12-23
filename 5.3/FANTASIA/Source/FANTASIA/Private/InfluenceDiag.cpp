// Fill out your copyright notice in the Description page of Project Settings.


#include "InfluenceDiag.h"
#include <vector>


std::vector<float> myIDLinspace(float start, float end, int points)
{
	std::vector<float> res(points);
	float step = (end - start) / (points - 1);
	int i = 0;
	float cand;

	for (auto& e : res)
	{
		cand = start + step * i++;
		if (cand < end)
			e = cand;
		else
			e = end;
	}

	return res;

}

UInfluenceDiag::UInfluenceDiag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

void UInfluenceDiag::Init()
{
	if (!initialized) {
		initialized = true;
	}

	switch (InferenceAlgorithm)
	{
	case InferenceIDAlgs::ShaferShenoyLIMID:
		inference = new gum::ShaferShenoyLIMIDInference<double>(&id);
		break;
	}
}

void UInfluenceDiag::makeInference()
{
	try {
		inference->makeInference();
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
}

TMap<FString, float> UInfluenceDiag::getPosterior(FString variable)
{
	const std::string nodeName(TCHAR_TO_UTF8(*variable));
	TMap<FString, float> out;
	unsigned int j;

	try {
		gum::Potential<double> result = inference->posterior(nodeName);
		gum::Instantiation inst(result);

		for (inst.setFirst(), j = 0; !inst.end(); ++inst, ++j)
			out.Add(FString(result.variable(0).label(j).c_str()), result.get(inst));
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());

	return out;
}

TMap<FString, float> UInfluenceDiag::getPosteriorUtility(FString variable)
{
	const std::string nodeName(TCHAR_TO_UTF8(*variable));
	TMap<FString, float> out;
	unsigned int j;

	if (id.isUtilityNode(nodeName)) {
		try {
			gum::Potential<double> result = inference->posteriorUtility(nodeName);
			gum::Instantiation inst(result);

			for (inst.setFirst(), j = 0; !inst.end(); ++inst, ++j)
				out.Add(FString(result.variable(0).label(j).c_str()), result.get(inst));
		}
		catch (gum::NotFound& e)
			UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
	}
	return out;
}

TMap<FString, float> UInfluenceDiag::getMEU()
{
	TMap<FString, float> out;

	try {
		std::pair MEU = inference->MEU();

		out.Add("MEU", MEU.first);
		out.Add("Variance", MEU.second);
	}
	catch (gum::OperationNotAllowed& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());

	return out;
}

double UInfluenceDiag::getEntropy(FString variable)
{
	if (!variable.IsEmpty())
		return (float)inference->posterior((TCHAR_TO_UTF8(*variable))).entropy();
	return 0;
}

TMap<FString, FArrayFloat> UInfluenceDiag::optimalDecision(FString variable)
{
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
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());

	return out;
}

void UInfluenceDiag::addEvidence(FString variable, TArray<float> data)
{
	std::vector<double> vec;
	for (const float value : data)
		vec.push_back(value);

	auto var = TCHAR_TO_UTF8(*variable);

	if (inference->hasEvidence(var))
		inference->eraseEvidence(var);
	inference->addEvidence(var, vec);
}

void UInfluenceDiag::eraseAllEvidence()
{
	inference->eraseAllEvidence();
}

void UInfluenceDiag::eraseEvidence(FString variable)
{
	inference->eraseEvidence(TCHAR_TO_UTF8(*variable));
}

void UInfluenceDiag::addDiscretizedVariable(FString variable, FString description, float minTick, float maxTick, float nPoints, InfluenceNodeType nodeType)
{
	if (!nodeNames.Contains(variable)) 
	{
		gum::DiscretizedVariable<float> newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description));
		std::vector<float> ticks = myIDLinspace(minTick, maxTick, nPoints);

		for (float i : ticks)
			newNode.addTick(i);

		switch (nodeType) {
		case InfluenceNodeType::CHANCE: id.addChanceNode(newNode); break;
		case InfluenceNodeType::UTILITY: id.addUtilityNode(newNode); break;
		case InfluenceNodeType::DECISION: id.addDecisionNode(newNode); break;
		}

		nodeNames.Add(variable);
		nodeDescriptions.Add(variable, description);
	}
}

void UInfluenceDiag::addLabelizedVariable(FString variable, FString description, TArray<FString> labels, InfluenceNodeType nodeType)
{
	if (!nodeNames.Contains(variable))
	{
		gum::LabelizedVariable newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description), 0);
		nodeNames.Add(variable);
		nodeDescriptions.Add(variable, description);

		for (FString label : labels)
			newNode.addLabel(TCHAR_TO_UTF8(*label));

		switch (nodeType) {
		case InfluenceNodeType::CHANCE: id.addChanceNode(newNode); break;
		case InfluenceNodeType::UTILITY: id.addUtilityNode(newNode); break;
		case InfluenceNodeType::DECISION: id.addDecisionNode(newNode); break;
		}
	}
}

void UInfluenceDiag::addArc(FString parent, FString child)
{
	FString newArc = parent + "_" + child;

	for (FString arc : arcs)
		if (arc == newArc)
			return;

	try {
		id.addArc(TCHAR_TO_UTF8(*parent), TCHAR_TO_UTF8(*child));
		arcs.Add(newArc);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs while adding arc"), e.errorType().c_str(), e.errorContent().c_str());
}

void UInfluenceDiag::fillCPT(FString variable, TArray<float> values)
{
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	if (!id.isUtilityNode(nodeName)) {
		std::vector<double> cptValues;
		for (float value : values)
			cptValues.push_back(value);

		try {
			id.cpt(nodeName).fillWith(cptValues);
		}
		catch (gum::NotFound& e)
			UE_LOG(LogTemp, Warning, TEXT("%hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
	}
}

void UInfluenceDiag::fillUtility(FString variable, TArray<float> values)
{
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	if (id.isUtilityNode(nodeName)) {
		std::vector<double> utilityValues;
		for (float value : values)
			utilityValues.push_back(value);

		try {
			id.utility(nodeName).fillWith(utilityValues);
		}
		catch (gum::NotFound& e)
			UE_LOG(LogTemp, Warning, TEXT("%hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
	}
}

void UInfluenceDiag::writeBIFXML(FString file)
{
	auto writer = gum::BIFXMLIDWriter<double>();
	writer.write(TCHAR_TO_UTF8(*file), id);
}

void UInfluenceDiag::erase(FString variable)
{
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	TArray<FString> toRemove;

	for (FString arc : arcs)
		if (arc.Contains(variable))
			toRemove.Add(arc);

	for (FString arc : toRemove)
		arcs.Remove(arc);

	id.erase(nodeName);
	nodeNames.Remove(variable);
	nodeDescriptions.Remove(variable);
}

int UInfluenceDiag::idFromName(FString variable)
{
	return id.idFromName(TCHAR_TO_UTF8(*variable));
}

bool UInfluenceDiag::decisionOrderExists()
{
	return id.decisionOrderExists();
}

TArray<int> UInfluenceDiag::decisionOrder()
{
	TArray<int> out;
	std::vector<gum::NodeId> decisionSequence;
	decisionSequence = id.decisionOrder();
	
	for (gum::NodeId idx : decisionSequence)
		out.Add(idx);

	return out;
}
