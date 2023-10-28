// Fill out your copyright notice in the Description page of Project Settings.

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

#include "agrum/ID/influenceDiagram.h"
#include "agrum/ID/inference/tools/influenceDiagramInference.h"
#include "agrum/ID/inference/ShaferShenoyLIMIDInference.h"
#include "agrum/ID/io/BIFXML/BIFXMLIDWriter.h"

#include "MathUtilities.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InfluenceDiag.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class InferenceIDAlgs : uint8
{
	ShaferShenoyLIMID UMETA(DisplayName = "Shafer Shenoy LIMID Inference"),
};

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
struct FInflueceDiagNodeStruct
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

	UPROPERTY(EditAnywhere)
	InfluenceNodeType nodeType;
};

USTRUCT(Blueprintable)
struct FArrayFloat 
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<float> arrayFloat;
	
};

UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UInfluenceDiag : public UObject
{
	GENERATED_UCLASS_BODY()

private:
	gum::InfluenceDiagram<double> id;
	gum::InfluenceDiagramInference<double>* inference = new gum::ShaferShenoyLIMIDInference<double>(&id);
	bool initialized = false;

public:

	UPROPERTY(EditAnywhere)
	TArray<FInflueceDiagNodeStruct> serializedNodes;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> nodeNames;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> nodeDescriptions;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> arcs;

	UPROPERTY(BlueprintReadWrite)
	InferenceIDAlgs InferenceAlgorithm = InferenceIDAlgs::ShaferShenoyLIMID;

	// Read ID from a BIFXML file
	//void setID(const FString& Filename);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init"), Category = "Influence_Diagram")
	void Init();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "makeInference", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Influence_Diagram")
	void makeInference();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getPosterior", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Influence_Diagram")
	TMap<FString, float> getPosterior(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getPosteriorUtility", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Influence_Diagram")
	TMap<FString, float> getPosteriorUtility(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getMEU", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Influence_Diagram")
	TMap<FString, float> getMEU();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getEntropy"), Category = "Influence_Diagram")
	double getEntropy(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "optimalDecision", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Influence_Diagram")
	TMap<FString, FArrayFloat> optimalDecision(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addEvidence"), Category = "Influence_Diagram")
	void addEvidence(FString variable, TArray<float> data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseAllEvidence"), Category = "Influence_Diagram")
	void eraseAllEvidence();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseEvidence"), Category = "Influence_Diagram")
	void eraseEvidence(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addDiscretizedVariable"), Category = "Influence_Diagram")
	void addDiscretizedVariable(FString variable, FString description, float minTick, float maxTick, float nPoints, InfluenceNodeType nodeType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addLabelizedVariable"), Category = "Influence_Diagram")
	void addLabelizedVariable(FString variable, FString description, TArray<FString> labels, InfluenceNodeType nodeType);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addArc"), Category = "Influence_Diagram")
	void addArc(FString parent, FString child);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillCPT"), Category = "Influence_Diagram")
	void fillCPT(FString variable, TArray<float> values);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillUtility"), Category = "Influence_Diagram")
	void fillUtility(FString variable, TArray<float> values);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "writeBIFXML"), Category = "Influence_Diagram")
	void writeBIFXML(FString file);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "clear"), Category = "Influence_Diagram")
	void erase(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "idFromName"), Category = "Influence_Diagram")
	int idFromName(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "decisionOrderExists"), Category = "Influence_Diagram")
	bool decisionOrderExists();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "decisionOrder"), Category = "Influence_Diagram")
	TArray<int> decisionOrder();

};
