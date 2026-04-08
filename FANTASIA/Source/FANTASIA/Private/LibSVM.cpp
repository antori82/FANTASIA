/**
 * @file LibSVM.cpp
 * @brief Implementation of ULibSVM — training, prediction, and model loading.
 */

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LibSVM.h"


ULibSVM::ULibSVM(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
}

void ULibSVM::FreeProblem() {
	for (int i = 0; i < prob.l; i++)
		FMemory::Free(prob.x[i]);

	FMemory::Free(prob.x);
	FMemory::Free(prob.y);

	prob.x = nullptr;
	prob.y = nullptr;
	prob.l = 0;
}

void ULibSVM::FreeModel() {
	if (model) {
		svm_free_and_destroy_model(&model);
		model = nullptr;
	}
}

void ULibSVM::BeginDestroy() {
	FreeModel();
	FreeProblem();
	Super::BeginDestroy();
}

void ULibSVM::load(FString path) {
	FreeModel();
	model = svm_load_model(TCHAR_TO_UTF8(*path));
}

void ULibSVM::train() {
	FreeModel();
	FreeProblem();

	nFeatures = trainingSet[0].features.Num();

	prob.l = trainingSet.Num();
	prob.y = (double*) FMemory::Malloc(prob.l * sizeof(double));
	prob.x = (struct svm_node**) FMemory::Malloc(prob.l * sizeof(struct svm_node*));

	for (int i = 0; i < prob.l; i++)
		prob.x[i] = (struct svm_node*) FMemory::Malloc((nFeatures + 1) * sizeof(struct svm_node));

	if (prob.x != NULL) {
		for (int i = 0; i < prob.l; i++) {
			for (int j = 0; j < nFeatures; j++) {
				prob.x[i][j].value = trainingSet[i].features[j];
				prob.x[i][j].index = j;
			}
			prob.x[i][nFeatures].index = -1;
			prob.x[i][nFeatures].value = 0;
			prob.y[i] = trainingSet[i].CLFclass;
		}

		svmParameters.svm_type = (int) SVMParameters.SVMType;
		svmParameters.kernel_type = (int) SVMParameters.KernelType;
		svmParameters.C = SVMParameters.C;
		svmParameters.gamma = SVMParameters.gamma;
		svmParameters.degree = (int) SVMParameters.degree;
		svmParameters.coef0 = SVMParameters.coef0;
		svmParameters.nu = SVMParameters.nu;
		svmParameters.p = SVMParameters.svrEpsilon;
		svmParameters.cache_size = SVMParameters.cachesize;
		svmParameters.eps = SVMParameters.epsilon;
		svmParameters.shrinking = SVMParameters.shrinking ? 1 : 0;
		svmParameters.probability = 1;
		svmParameters.nr_weight = 0;
		svmParameters.weight_label = nullptr;
		svmParameters.weight = nullptr;

		model = svm_train(&prob, &svmParameters);
	}
}


TArray<struct FCLFResult> ULibSVM::predict(const TArray<FCLFSample>& samples) {
	TArray<struct FCLFResult> result;

	if (!model || samples.Num() == 0)
		return result;

	int nr_class = model->nr_class;
	int numFeatures = samples[0].features.Num();

	struct svm_node* x = (struct svm_node*) FMemory::Malloc((numFeatures + 1) * sizeof(struct svm_node));
	double* prob_estimates = (double*) FMemory::Malloc(nr_class * sizeof(double));

	if (x != nullptr && prob_estimates != nullptr) {
		x[numFeatures].index = -1;

		result.Reserve(samples.Num());

		for (const FCLFSample& sample : samples) {
			for (int i = 0; i < sample.features.Num(); i++) {
				x[i].value = sample.features[i];
				x[i].index = i;
			}

			svm_predict_probability(model, x, prob_estimates);

			FCLFResult& sampleResult = result.AddDefaulted_GetRef();
			sampleResult.sampleID = sample.sampleID;
			sampleResult.probabilities.SetNumUninitialized(nr_class);
			FMemory::Memcpy(sampleResult.probabilities.GetData(), prob_estimates, nr_class * sizeof(double));
		}
	}

	FMemory::Free(x);
	FMemory::Free(prob_estimates);

	return result;
}
