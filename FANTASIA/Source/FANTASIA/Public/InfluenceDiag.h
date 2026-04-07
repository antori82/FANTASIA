// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#pragma warning (disable : 4263)
#pragma warning (disable : 4264)
#pragma warning (disable : 4265)
#pragma warning (disable : 4701)

#include "FANTASIA.h"
#include "FANTASIATypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime\Core\Public\Misc\Paths.h"
#include "Runtime\Core\Public\Misc\FileHelper.h"
#include <Runtime/Core/Public/Async/Async.h>
#include <atomic>

#include "agrum/ID/influenceDiagram.h"
#include "agrum/ID/inference/tools/influenceDiagramInference.h"
#include "agrum/ID/inference/ShaferShenoyLIMIDInference.h"
#include "agrum/ID/io/BIFXML/BIFXMLIDWriter.h"

#include "MathUtilities.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InfluenceDiag.generated.h"

#pragma warning (default : 4263)
#pragma warning (default : 4264)
#pragma warning (default : 4265)
#pragma warning (default : 4701)

USTRUCT(Blueprintable)
struct FInfluenceDiagArcStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Tail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Head;
};

USTRUCT(Blueprintable)
struct FInfluenceDiagNodeStruct
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	InfluenceNodeType nodeType = InfluenceNodeType::CHANCE;
};

USTRUCT(Blueprintable)
struct FArrayFloat
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<float> arrayFloat;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIDInferenceAvailableEvent);

UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UInfluenceDiag : public UObject
{
	GENERATED_UCLASS_BODY()

private:
	gum::InfluenceDiagram<double> id;
	TUniquePtr<gum::InfluenceDiagramInference<double>> inference;
	bool initialized = false;
	std::atomic<bool> bInferenceRunning{false};
	TSet<FString> arcSet;
	TSet<FString> nodeNameSet;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIDInferenceAvailableEvent InferenceReady;

	FSimpleMulticastDelegate OnInferenceReady;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInfluenceDiagNodeStruct> serializedNodes;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> nodeNames;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> nodeDescriptions;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> arcs;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init"), Category = "Influence_Diagram")
	void Init();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "makeInference", Keywords = "Inference"), Category = "Influence_Diagram")
	void makeInference();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getPosterior", Keywords = "Inference"), Category = "Influence_Diagram")
	TMap<FString, float> getPosterior(const FString& variable);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getPosteriorUtility", Keywords = "Inference"), Category = "Influence_Diagram")
	TMap<FString, float> getPosteriorUtility(const FString& variable);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getMEU", Keywords = "Inference"), Category = "Influence_Diagram")
	TMap<FString, float> getMEU();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getEntropy"), Category = "Influence_Diagram")
	double getEntropy(const FString& variable);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "optimalDecision", Keywords = "Inference"), Category = "Influence_Diagram")
	TMap<FString, FArrayFloat> optimalDecision(const FString& variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addEvidence"), Category = "Influence_Diagram")
	void addEvidence(const FString& variable, const TArray<float>& data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseAllEvidence"), Category = "Influence_Diagram")
	void eraseAllEvidence();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseEvidence"), Category = "Influence_Diagram")
	void eraseEvidence(const FString& variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addDiscretizedVariable"), Category = "Influence_Diagram")
	void addDiscretizedVariable(const FString& variable, const FString& description, float minTick, float maxTick, float nPoints, InfluenceNodeType nodeType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addLabelizedVariable"), Category = "Influence_Diagram")
	void addLabelizedVariable(const FString& variable, const FString& description, const TArray<FString>& labels, InfluenceNodeType nodeType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addArc"), Category = "Influence_Diagram")
	void addArc(const FString& parent, const FString& child);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillCPT"), Category = "Influence_Diagram")
	void fillCPT(const FString& variable, const TArray<float>& values);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillUtility"), Category = "Influence_Diagram")
	void fillUtility(const FString& variable, const TArray<float>& values);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "writeBIFXML"), Category = "Influence_Diagram")
	void writeBIFXML(const FString& file);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "EraseNode"), Category = "Influence_Diagram")
	void erase(const FString& variable);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "idFromName"), Category = "Influence_Diagram")
	int idFromName(const FString& variable);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "decisionOrderExists"), Category = "Influence_Diagram")
	bool decisionOrderExists();

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "decisionOrder"), Category = "Influence_Diagram")
	TArray<int> decisionOrder();
};
