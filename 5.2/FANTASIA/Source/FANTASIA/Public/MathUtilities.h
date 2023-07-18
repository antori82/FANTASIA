#pragma once

#include "FANTASIA.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "kde.h"

#include "MathUtilities.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UKernelDensityEstimator : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	std::vector<float> data;

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetData"), Category = "Kernel_Density_Estimation")
		void setData(TArray<float> newData);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Evaluate"), Category = "Kernel_Density_Estimation")
		float evaluate(float point);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "GetPDF"), Category = "Kernel_Density_Estimation")
		TMap<float,float> getPdf(float min, float max, int points);
};