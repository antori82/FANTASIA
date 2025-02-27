// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "FANTASIA.h"
#include "CoreMinimal.h"
#include "svm.h"

#include "LibSVM.generated.h"


USTRUCT(BlueprintType)
struct FCLFSample {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString sampleID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double CLFclass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double> features;
};

USTRUCT(BlueprintType)
struct FCLFResult {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString sampleID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double> probabilities;
};

UENUM(BlueprintType)
enum class LibSVMTypes : uint8 {
	C_SVC = C_SVC UMETA(DisplayName = "C-SVC"),
	NU_SVC = NU_SVC UMETA(DisplayName = "nu-SVC"),
	ONE_CLASS_SVM = ONE_CLASS UMETA(DisplayName = "one-class SVM"),
	EPSILON_SVR = EPSILON_SVR UMETA(DisplayName = "epsilon-SVR"),
	NU_SVR = NU_SVR UMETA(DisplayName = "nu-SVR")
};

UENUM(BlueprintType)
enum class LibSVMKernels : uint8 {
	LINEAR = LINEAR UMETA(DisplayName = "Linear"),
	POLYNOMIAL = POLY UMETA(DisplayName = "Polynomial"),
	RBF = RBF UMETA(DisplayName = "RBF"),
	SIGMOID = SIGMOID UMETA(DisplayName = "Sigmoid")
};

USTRUCT(BlueprintType)
struct FSVMParameters {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	LibSVMTypes SVMType = LibSVMTypes::C_SVC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	LibSVMKernels KernelType = LibSVMKernels::RBF;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double C = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double gamma = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double degree = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double coef0 = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double nu = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double svrEpsilon = 0.1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double cachesize = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double epsilon = 0.001;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool shrinking = true;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<double> classWeights;
};

UCLASS(Blueprintable, BlueprintType, meta = (DisplayName = "SVM"))
class FANTASIA_API ULibSVM : public UObject
{
	GENERATED_UCLASS_BODY()

private:
	struct svm_model* model = NULL;
	struct svm_problem prob;
	int nFeatures = 0;
	struct svm_parameter svmParameters;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCLFSample> trainingSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FSVMParameters SVMParameters;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SVM Train", Keywords = "SVM Train Fit"), Category = "SVM")
	void train();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SVM Predict", Keywords = "SVM Predict"), Category = "SVM")
	TArray<struct FCLFResult> predict(TArray<FCLFSample> samples);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load SVM", Keywords = "Load SVM"), Category = "SVM")
	void load(FString path);
};
