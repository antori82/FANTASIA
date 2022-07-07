// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FANTASIA.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime\Core\Public\Misc\Paths.h"
#include "Runtime\Core\Public\Misc\FileHelper.h"

#include "agrum/BN/BayesNet.h"
#include "agrum/BN/io/BIF/BIFWriter.h"
#include "agrum/BN/io/BIF/BIFReader.h"
#include "agrum/BN/inference/lazyPropagation.h"
#include "agrum/BN/inference/ShaferShenoyInference.h"
#include "agrum/BN/inference/variableElimination.h"

#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"
#include "BayesianNetwork.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class InferenceAlgs : uint8
{
	Lazy_Propagation UMETA(DisplayName = "Lazy Propagation"),
	ShaferShenoy UMETA(DisplayName = "Shafer Shenoy Inference"),
	VariableElimination UMETA(DisplayName = "Variable Elimination")
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

/*
UCLASS(BlueprintType)
class FANTASIA_API UBayesianNode : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY()
	FString name;

	UPROPERTY()
	TArray<FString> variables;

	UPROPERTY()
	TArray<double> values;
};
*/

class FANTASIA_API FBayesianNetworkActions : public FAssetTypeActions_Base
{
public:

	FText GetName() const;
	FColor GetTypeColor() const;
	};

UCLASS()
class FANTASIA_API UBayesianNetworkFactory : public UFactory
{
	GENERATED_BODY()
public:
	UBayesianNetworkFactory(const FObjectInitializer& ObjectInitializer);
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	//virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) ;
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled);
};

UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UBayesianNetwork : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	gum::BayesNet<double> bn;
	gum::JointTargetedInference<double>* inference = new gum::LazyPropagation<double>(&bn);
	bool initialized = false;

public:

	UPROPERTY(EditAnywhere)
		TArray<FBayesianNodeStruct> serializedNodes;

	void setBN(const FString& Filename);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init"), Category = "Bayesian_Network")
	void Init();
	
	UPROPERTY(BlueprintReadWrite)
	InferenceAlgs InferenceAlgorithm = InferenceAlgs::Lazy_Propagation;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "makeInference", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Bayesian_Network")
	void makeInference();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getPosterior", Keywords = "Inference", AutoCreateRefTerm = "evidences"), Category = "Bayesian_Network")
	TMap<FString, float> getPosterior(FString variable);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addEvidence"), Category = "Bayesian_Network")
	void addEvidence(FString variable, TArray<float> data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseAllEvidence"), Category = "Bayesian_Network")
	void eraseAllEvidence();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseEvidence"), Category = "Bayesian_Network")
	void eraseEvidence(FString variable);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "getEntropy"), Category = "Bayesian_Network")
	float getEntropy(FString variable);
};