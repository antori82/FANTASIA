/**
 * @file LibSVM.h
 * @brief Blueprint-accessible Support Vector Machine (SVM) classifier using libsvm.
 *
 * Provides types for training samples, prediction results, SVM hyper-parameters,
 * and the ULibSVM UObject wrapper around the libsvm C library.
 */

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once


#include "FANTASIA.h"
#include "CoreMinimal.h"
#include "svm.h"

#include "LibSVM.generated.h"


/** A single labelled sample used for SVM training or prediction. */
USTRUCT(BlueprintType)
struct FCLFSample {

	GENERATED_BODY()

	/** Unique identifier for this sample (for tracking in results). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString sampleID;

	/** Class label for supervised learning (ignored during prediction). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double CLFclass;

	/** Feature vector. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double> features;
};

/** Prediction result for a single sample. */
USTRUCT(BlueprintType)
struct FCLFResult {

	GENERATED_BODY()

	/** Identifier of the predicted sample (matches FCLFSample::sampleID). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString sampleID;

	/** Per-class probability estimates (requires probability model). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double> probabilities;
};

/** SVM formulation type (maps to libsvm svm_type constants). */
UENUM(BlueprintType)
enum class LibSVMTypes : uint8 {
	C_SVC = C_SVC UMETA(DisplayName = "C-SVC"),                   ///< C-Support Vector Classification.
	NU_SVC = NU_SVC UMETA(DisplayName = "nu-SVC"),                 ///< Nu-Support Vector Classification.
	ONE_CLASS_SVM = ONE_CLASS UMETA(DisplayName = "one-class SVM"),///< One-class SVM (novelty detection).
	EPSILON_SVR = EPSILON_SVR UMETA(DisplayName = "epsilon-SVR"),  ///< Epsilon-Support Vector Regression.
	NU_SVR = NU_SVR UMETA(DisplayName = "nu-SVR")                  ///< Nu-Support Vector Regression.
};

/** Kernel function type for the SVM. */
UENUM(BlueprintType)
enum class LibSVMKernels : uint8 {
	LINEAR = LINEAR UMETA(DisplayName = "Linear"),           ///< Linear kernel: u'*v.
	POLYNOMIAL = POLY UMETA(DisplayName = "Polynomial"),     ///< Polynomial kernel: (gamma*u'*v + coef0)^degree.
	RBF = RBF UMETA(DisplayName = "RBF"),                    ///< Radial Basis Function (Gaussian) kernel.
	SIGMOID = SIGMOID UMETA(DisplayName = "Sigmoid")         ///< Sigmoid kernel: tanh(gamma*u'*v + coef0).
};

/** Blueprint-configurable SVM hyper-parameters. */
USTRUCT(BlueprintType)
struct FSVMParameters {

	GENERATED_BODY()

	/** SVM formulation type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	LibSVMTypes SVMType = LibSVMTypes::C_SVC;

	/** Kernel function. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	LibSVMKernels KernelType = LibSVMKernels::RBF;

	/** Regularization parameter (C-SVC, epsilon-SVR, nu-SVR). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double C = 1;

	/** Kernel coefficient for RBF, polynomial, and sigmoid kernels. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double gamma = 0.1;

	/** Degree of the polynomial kernel. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double degree = 3;

	/** Independent term in polynomial / sigmoid kernels. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double coef0 = 0;

	/** Nu parameter for nu-SVC, one-class SVM, and nu-SVR. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double nu = 0.5;

	/** Epsilon in the loss function of epsilon-SVR. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double svrEpsilon = 0.1;

	/** Kernel cache size in MB. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double cachesize = 100;

	/** Stopping tolerance for the optimization. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double epsilon = 0.001;

	/** Whether to use the shrinking heuristic. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool shrinking = true;
};

/**
 * Blueprint-accessible wrapper around the libsvm C library.
 *
 * Allows training an SVM model from labelled samples, predicting
 * class probabilities for new samples, and loading pre-trained models
 * from disk — all exposed to Blueprints.
 *
 * @note The underlying svm_model and svm_problem are freed automatically
 *       on destruction.
 */
UCLASS(Blueprintable, BlueprintType, meta = (DisplayName = "SVM"))
class FANTASIA_API ULibSVM : public UObject
{
	GENERATED_UCLASS_BODY()

private:
	struct svm_model* model = nullptr;
	struct svm_problem prob = {};
	int nFeatures = 0;
	struct svm_parameter svmParameters = {};

	void FreeProblem();
	void FreeModel();

public:

	virtual void BeginDestroy() override;

	/** Training samples used by train(). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCLFSample> trainingSet;

	/** Hyper-parameter configuration for the SVM. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FSVMParameters SVMParameters;

	/**
	 * Train the SVM model using the current trainingSet and SVMParameters.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SVM Train", Keywords = "SVM Train Fit"), Category = "SVM")
	void train();

	/**
	 * Predict class probabilities for the given samples.
	 *
	 * @param samples  Input samples to classify.
	 * @return         Per-sample prediction results with probability estimates.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SVM Predict", Keywords = "SVM Predict"), Category = "SVM")
	TArray<struct FCLFResult> predict(const TArray<FCLFSample>& samples);

	/**
	 * Load a pre-trained SVM model from a file on disk.
	 *
	 * @param path  Absolute path to the saved model file.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load SVM", Keywords = "Load SVM"), Category = "SVM")
	void load(FString path);
};
