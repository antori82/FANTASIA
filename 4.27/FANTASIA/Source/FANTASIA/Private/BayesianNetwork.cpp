// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BayesianNetwork.h"
#include <vector>

/*UBayesianNode::UBayesianNode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{}*/

UBayesianNetwork::UBayesianNetwork(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{}

void UBayesianNetwork::Init() {
	gum::LabelizedVariable newNode("", "", 0);
	std::vector<double> data;
	int i, j;

	if (!initialized) {		
		for (i = 0; i < serializedNodes.Num(); i++) {
			newNode.setName(TCHAR_TO_UTF8(*serializedNodes[i].name));
			newNode.eraseLabels();

			for (FString label : serializedNodes[i].variables)
				newNode.addLabel(TCHAR_TO_UTF8(*label));
			bn.add(newNode);
		}

		for (i = 0; i < serializedNodes.Num(); i++) {
			for (FString parent : serializedNodes[i].parents) {
				bn.addArc(bn.idFromName(TCHAR_TO_UTF8(*parent)), bn.idFromName(TCHAR_TO_UTF8(*serializedNodes[i].name)));
			}
		}

		for (i = 0; i < serializedNodes.Num(); i++) {
			data.clear();
			for (j = 0; j < serializedNodes[i].values.Num(); j++)
				data.push_back(serializedNodes[i].values[j]);
			bn.cpt(TCHAR_TO_UTF8(*serializedNodes[i].name)).fillWith(data);
		}
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


void UBayesianNetwork::makeInference()
{
	try {
		inference->makeInference();
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
}

TMap<FString, float> UBayesianNetwork::getPosterior(FString variable)
{
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
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());

	return out;
}

void UBayesianNetwork::setBN(const FString& Filename) {
	gum::BIFReader<double> reader(&bn, TCHAR_TO_UTF8(*Filename));
	int result = reader.proceed();
	unsigned int j;
	FBayesianNodeStruct newNode;

	switch (InferenceAlgorithm)
	{
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

void UBayesianNetwork::addEvidence(FString variable, TArray<float> data)
{
	std::vector<double> vec;
	for (const float value : data)
		vec.push_back(value);
	inference->addEvidence(TCHAR_TO_UTF8(*variable), vec);
}

void UBayesianNetwork::eraseAllEvidence()
{
	inference->eraseAllEvidence();
}

void UBayesianNetwork::eraseEvidence(FString variable)
{
	inference->eraseEvidence(TCHAR_TO_UTF8(*variable));
}

float UBayesianNetwork::getEntropy(FString variable)
{
	return inference->posterior(TCHAR_TO_UTF8(*variable)).entropy();
}

FText FBayesianNetworkActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_BayesianNetwork", "Bayesian Network");
}

FColor FBayesianNetworkActions::GetTypeColor() const
{
	return FColor::White;
}

UBayesianNetworkFactory::UBayesianNetworkFactory(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("bif;")) + NSLOCTEXT("UBayesianNetworkFactory", "FormatBif", "Bayesian Network File").ToString());

	bCreateNew = false;
	bText = false;
	bEditorImport = true;
	bEditAfterNew = false;
	SupportedClass = UBayesianNetwork::StaticClass();
}

UObject* UBayesianNetworkFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UBayesianNetwork* BNAsset = NewObject<UBayesianNetwork>(InParent, InClass, InName, Flags);
	return BNAsset;
}

bool UBayesianNetworkFactory::FactoryCanImport(const FString& Filename)
{
	const FString Extension = FPaths::GetExtension(Filename);

	if (Extension == TEXT("bif"))
		return true;
	return false;
}

UObject* UBayesianNetworkFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UBayesianNetwork* bnObject = NewObject<UBayesianNetwork>(InParent, InClass, InName, Flags);

	bnObject->setBN(Filename);
	return bnObject;
}