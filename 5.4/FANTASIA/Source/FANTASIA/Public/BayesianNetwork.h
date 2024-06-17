// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "FANTASIA.h"
#include "FANTASIATypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime\Core\Public\Misc\Paths.h"
#include "Runtime\Core\Public\Misc\FileHelper.h"
#include <Runtime/Core/Public/Async/Async.h>

#include "agrum/BN/BayesNet.h"
#include "agrum/BN/io/BIF/BIFWriter.h"
#include "agrum/BN/io/BIF/BIFReader.h"
#include "agrum/BN/inference/lazyPropagation.h"
#include "agrum/BN/inference/ShaferShenoyInference.h"
#include "agrum/BN/inference/variableElimination.h"
#include <agrum/BN/algorithms/MarkovBlanket.h>

#include "MathUtilities.h"
#include "BayesianNetwork.generated.h"

USTRUCT(BlueprintType)
struct FMapContainer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, float> Map;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FGetPosteriorDelegate, FMapContainer, outMap);

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class InferenceAlgs : uint8
{
	Lazy_Propagation UMETA(DisplayName = "Lazy Propagation"),
	ShaferShenoy UMETA(DisplayName = "Shafer Shenoy Inference"),
	VariableElimination UMETA(DisplayName = "Variable Elimination")
};


USTRUCT(Blueprintable)
struct FBayesianArcStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Tail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Head;
};

USTRUCT(Blueprintable)
struct FBayesianNodeStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FString name;

	UPROPERTY(EditAnywhere)
	TArray<FString> variables;

	UPROPERTY(EditAnywhere)
	TArray<double> values;

	UPROPERTY(EditAnywhere)
	TArray<FString> parents;
};


UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UBayesianNetwork : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	gum::BayesNet<double> bn;
	gum::JointTargetedInference<double>* inference = new gum::ShaferShenoyInference<double>(&bn);
	bool initialized = false;

public:

	UPROPERTY(EditAnywhere)
	TArray<FBayesianNodeStruct> serializedNodes;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> nodeNames;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> nodeDescriptions;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> arcs;

	void setBN(const FString& Filename);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init"), Category = "Bayesian_Network")
	void Init();
	
	UPROPERTY(BlueprintReadWrite)
	InferenceAlgs InferenceAlgorithm = InferenceAlgs::ShaferShenoy;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "makeInference", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Bayesian_Network")
	void makeInference();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getPosterior", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Bayesian_Network")
	TMap<FString, float> getPosterior(FString variable);

	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "getPosterior", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Bayesian_Network")
	//void getPosterior(FGetPosteriorDelegate outMap, FString variable);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addEvidence"), Category = "Bayesian_Network")
	void addEvidence(FString variable, TArray<float> data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseAllEvidence"), Category = "Bayesian_Network")
	void eraseAllEvidence();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseEvidence"), Category = "Bayesian_Network")
	void eraseEvidence(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getEntropy"), Category = "Bayesian_Network")
	double getEntropy(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addDiscretizedVariable"), Category = "Bayesian_Network")
	void addDiscretizedVariable(FString variable, FString description, float minTick, float maxTick, float nPoints, BayesianNodeType nodeType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addLabelizedVariable"), Category = "Bayesian_Network")
	void addLabelizedVariable(FString variable, FString description, TArray<FString> labels);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addArc"), Category = "Bayesian_Network")
	void addArc(FString parent, FString child);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillWith"), Category = "Bayesian_Network")
	void fillWith(FString variable, float value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "writeBIF"), Category = "Bayesian_Network")
	void writeBIF(FString file);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "clear"), Category = "Bayesian_Network")
	void erase(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "idFromName"), Category = "Bayesian_Network")
	int idFromName(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getMarkovBlanketNodes"), Category = "Bayesian_Network")
	TArray<FString> getMarkovBlanketNodes(FString variable);
};
