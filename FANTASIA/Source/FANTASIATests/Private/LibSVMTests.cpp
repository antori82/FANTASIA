/**
 * @file LibSVMTests.cpp
 * @brief Tests for ULibSVM: prediction without a model, training on linearly
 *        separable data, and empty-sample edge case.
 */

#include "Misc/AutomationTest.h"
#include "LibSVM.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLibSVMPredictNoModel, "FANTASIA.LibSVM.PredictNoModel",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FLibSVMPredictNoModel::RunTest(const FString& Parameters)
{
	ULibSVM* SVM = NewObject<ULibSVM>();

	FCLFSample Sample;
	Sample.sampleID = TEXT("test");
	Sample.CLFclass = 0;
	Sample.features = {1.0, 2.0};

	TArray<FCLFResult> Results = SVM->predict({Sample});
	TestEqual(TEXT("Empty result on null model"), Results.Num(), 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLibSVMTrainAndPredict, "FANTASIA.LibSVM.TrainAndPredict",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FLibSVMTrainAndPredict::RunTest(const FString& Parameters)
{
	ULibSVM* SVM = NewObject<ULibSVM>();

	// Linearly separable data: class 0 in low region, class 1 in high region
	FCLFSample S1; S1.sampleID = TEXT("s1"); S1.CLFclass = 0; S1.features = {0.0, 0.0};
	FCLFSample S2; S2.sampleID = TEXT("s2"); S2.CLFclass = 0; S2.features = {1.0, 0.0};
	FCLFSample S3; S3.sampleID = TEXT("s3"); S3.CLFclass = 0; S3.features = {0.0, 1.0};
	FCLFSample S4; S4.sampleID = TEXT("s4"); S4.CLFclass = 1; S4.features = {10.0, 10.0};
	FCLFSample S5; S5.sampleID = TEXT("s5"); S5.CLFclass = 1; S5.features = {11.0, 10.0};
	FCLFSample S6; S6.sampleID = TEXT("s6"); S6.CLFclass = 1; S6.features = {10.0, 11.0};

	SVM->trainingSet = {S1, S2, S3, S4, S5, S6};
	SVM->SVMParameters.SVMType = LibSVMTypes::C_SVC;
	SVM->SVMParameters.KernelType = LibSVMKernels::RBF;
	SVM->SVMParameters.C = 10.0;
	SVM->SVMParameters.gamma = 0.1;

	SVM->train();

	// Predict on test samples
	FCLFSample T1; T1.sampleID = TEXT("t1"); T1.CLFclass = 0; T1.features = {0.5, 0.5};
	FCLFSample T2; T2.sampleID = TEXT("t2"); T2.CLFclass = 1; T2.features = {10.5, 10.5};

	TArray<FCLFResult> Results = SVM->predict({T1, T2});
	TestEqual(TEXT("Result count"), Results.Num(), 2);
	TestEqual(TEXT("ID preserved"), Results[0].sampleID, FString(TEXT("t1")));
	TestEqual(TEXT("ID preserved"), Results[1].sampleID, FString(TEXT("t2")));

	// Each result should have probability estimates (2 classes)
	TestTrue(TEXT("T1 has probs"), Results[0].probabilities.Num() > 0);
	TestTrue(TEXT("T2 has probs"), Results[1].probabilities.Num() > 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FLibSVMPredictEmpty, "FANTASIA.LibSVM.PredictEmptySamples",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FLibSVMPredictEmpty::RunTest(const FString& Parameters)
{
	ULibSVM* SVM = NewObject<ULibSVM>();

	// Train first
	FCLFSample S1; S1.sampleID = TEXT("s1"); S1.CLFclass = 0; S1.features = {0.0, 0.0};
	FCLFSample S2; S2.sampleID = TEXT("s2"); S2.CLFclass = 1; S2.features = {10.0, 10.0};
	SVM->trainingSet = {S1, S2};
	SVM->train();

	// Predict with empty array
	TArray<FCLFSample> Empty;
	TArray<FCLFResult> Results = SVM->predict(Empty);
	TestEqual(TEXT("Empty input -> empty output"), Results.Num(), 0);
	return true;
}
