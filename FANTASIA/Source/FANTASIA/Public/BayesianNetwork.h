// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#pragma warning (disable : 4263)
#pragma warning (disable : 4264)
#pragma warning (disable : 4265)
#pragma warning (disable : 4701)
#pragma warning (disable : 4996)

#include "FANTASIA.h"
#include "FANTASIATypes.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime\Core\Public\Misc\Paths.h"
#include "Runtime\Core\Public\Misc\FileHelper.h"
#include <Runtime/Core/Public/Async/Async.h>
#include <atomic>

#include "agrum/BN/BayesNet.h"
#include "agrum/BN/io/BIF/BIFWriter.h"
#include "agrum/BN/io/BIF/BIFReader.h"
#include "agrum/BN/inference/lazyPropagation.h"
#include "agrum/BN/inference/ShaferShenoyInference.h"
#include "agrum/BN/inference/variableElimination.h"
#include <agrum/BN/algorithms/MarkovBlanket.h>

#include "MathUtilities.h"
#include "BayesianNetwork.generated.h"

#pragma warning (default : 4263)
#pragma warning (default : 4264)
#pragma warning (default : 4265)
#pragma warning (default : 4701)
#pragma warning (default : 4996)

USTRUCT(BlueprintType)
struct FMapContainer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, float> Map;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> variables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double> values;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> parents;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBNInferenceAvailableEvent);

UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UBayesianNetwork : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	gum::BayesNet<double> bn;
	TUniquePtr<gum::JointTargetedInference<double>> inference;
	bool initialized = false;
	std::atomic<bool> bInferenceRunning{false};
	TSet<FString> arcSet;
	TSet<FString> nodeNameSet;

	void CreateInferenceEngine();

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FBNInferenceAvailableEvent InferenceReady;

	FSimpleMulticastDelegate OnInferenceReady;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FBayesianNodeStruct> serializedNodes;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> nodeNames;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> nodeDescriptions;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> arcs;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadFromBIF"), Category = "Bayesian_Network")
	void setBN(const FString& Filename);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init"), Category = "Bayesian_Network")
	void Init();

	UPROPERTY(BlueprintReadWrite)
	InferenceAlgs InferenceAlgorithm = InferenceAlgs::ShaferShenoy;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "makeInference", Keywords = "Inference"), Category = "Bayesian_Network")
	void makeInference();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getPosterior", Keywords = "Inference"), Category = "Bayesian_Network")
	TMap<FString, float> getPosterior(const FString& variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "setEvidence"), Category = "Bayesian_Network")
	void setEvidence(const FString& variable, const TArray<float>& data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseAllEvidence"), Category = "Bayesian_Network")
	void eraseAllEvidence();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseEvidence"), Category = "Bayesian_Network")
	void eraseEvidence(const FString& variable);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getEntropy"), Category = "Bayesian_Network")
	double getEntropy(const FString& variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addDiscretizedVariable"), Category = "Bayesian_Network")
	void addDiscretizedVariable(const FString& variable, const FString& description, float minTick, float maxTick, float nPoints, BayesianNodeType nodeType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addLabelizedVariable"), Category = "Bayesian_Network")
	void addLabelizedVariable(const FString& variable, const FString& description, const TArray<FString>& labels);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addArc"), Category = "Bayesian_Network")
	void addArc(const FString& parent, const FString& child);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillWith"), Category = "Bayesian_Network")
	void fillWith(const FString& variable, float value);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillCPT"), Category = "Bayesian_Network")
	void fillCPT(const FString& variable, const TArray<float>& values);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "writeBIF"), Category = "Bayesian_Network")
	void writeBIF(const FString& file);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "EraseNode"), Category = "Bayesian_Network")
	void erase(const FString& variable);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "idFromName"), Category = "Bayesian_Network")
	int idFromName(const FString& variable);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getMarkovBlanketNodes"), Category = "Bayesian_Network")
	TArray<FString> getMarkovBlanketNodes(const FString& variable);
};
