// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LibSVM.h"


ULibSVM::ULibSVM(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer) {
}


void ULibSVM::load(FString path) {
	model = svm_load_model(TCHAR_TO_UTF8(*path));
}

void ULibSVM::train() {
	
	for (int i = 0; i < prob.l; i++)
		FMemory::Free(prob.x[i]);

	FMemory::Free(prob.x);
	FMemory::Free(prob.y);

	nFeatures = trainingSet[0].features.Num();

	prob.l = trainingSet.Num();
	prob.y = (double*) FMemory::Malloc(trainingSet.Num() * sizeof(double));
	prob.x = (struct svm_node**) FMemory::Malloc(trainingSet.Num() * sizeof(struct svm_node*));

	for (int i=0; i< trainingSet.Num(); i++)
		prob.x[i] = (struct svm_node*) FMemory::Malloc((nFeatures + 1) * sizeof(struct svm_node));

	if (prob.x != NULL) {
		for (int i = 0; i < trainingSet.Num(); i++) {
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
		svmParameters.cache_size = SVMParameters.cachesize;
		svmParameters.eps = SVMParameters.epsilon;

		//svmParameters.nr_weight = SVMParameters.classWeights.Num();
		//svmParameters. = (double*) FMemory::Malloc(SVMParameters.classWeights.Num() * sizeof(double));
		//for (int i = 0; i < SVMParameters.classWeights.Num());
		//	SVMParameters.classWeights[i] = SVMParameters.classWeights[i];
		
		svmParameters.probability = 1;
		svmParameters.shrinking = SVMParameters.shrinking ? 1 : 0;

		model = svm_train(&prob, &svmParameters);
	}
}


TArray<struct FCLFResult> ULibSVM::predict(TArray<FCLFSample> samples) {
	double* prob_estimates = NULL;
	int svm_type = model->param.svm_type;
	int nr_class = model->nr_class;
	struct svm_node* x;
	TArray<struct FCLFResult> result;
	struct FCLFResult sampleResult;

	x = (struct svm_node*) FMemory::Malloc((samples[0].features.Num() + 1) * sizeof(struct svm_node));
	prob_estimates = (double*) FMemory::Malloc(nr_class * sizeof(double));

	if (x != NULL && prob_estimates != NULL) {
		x[samples[0].features.Num()].index = -1;

		for (FCLFSample sample : samples) {

			for (int i = 0; i < sample.features.Num(); i++) {
				x[i].value = sample.features[i];
				x[i].index = i;
			}

			svm_predict_probability(model, x, prob_estimates);

			sampleResult.probabilities.Empty();
			for (int i = 0; i < nr_class; i++)
				sampleResult.probabilities.Add(prob_estimates[i]);

			sampleResult.sampleID = sample.sampleID;
			result.Add(sampleResult);
		}

		FMemory::Free(x);
		FMemory::Free(prob_estimates);
	}
	

	return result;
}