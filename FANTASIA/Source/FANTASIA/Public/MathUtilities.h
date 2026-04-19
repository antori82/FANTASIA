/**
 * @file MathUtilities.h
 * @brief Mathematical utilities — kernel density estimation and helper functions.
 */

#pragma once

#include "FANTASIA.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "kde.h"
#include <vector>

#include "MathUtilities.generated.h"

/**
 * Generate a linearly-spaced vector of floats.
 *
 * @param Start   First value.
 * @param End     Last value.
 * @param Points  Number of points (must be >= 2).
 * @return        std::vector of evenly-spaced values from Start to End.
 */
FANTASIA_API std::vector<float> Linspace(float Start, float End, int Points);

/**
 * Blueprint-accessible Kernel Density Estimator (KDE).
 *
 * Wraps a Gaussian KDE (via the kdepp header-only library) so that
 * probability density estimation can be driven from Blueprints.
 *
 * Usage:
 *   1. Call SetData() with a training sample array.
 *   2. Call Evaluate() for point-wise density queries, or
 *   3. Call GetPDF() to sample the full density curve.
 */
UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UKernelDensityEstimator : public UObject
{
	GENERATED_UCLASS_BODY()

private:

	/** Internal training sample buffer. */
	std::vector<float> data;

public:

	/**
	 * Replace the training data with a new sample array.
	 *
	 * @param newData  New observation values used to build the KDE.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "SetData"), Category = "Kernel_Density_Estimation")
		void setData(TArray<float> newData);

	/**
	 * Evaluate the estimated probability density at a single point.
	 *
	 * @param point  The value at which to evaluate the PDF.
	 * @return       Estimated density f(point).
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Evaluate"), Category = "Kernel_Density_Estimation")
		float evaluate(float point);

	/**
	 * Sample the estimated PDF over a uniform grid.
	 *
	 * @param min     Lower bound of the evaluation range.
	 * @param max     Upper bound of the evaluation range.
	 * @param points  Number of equally-spaced sample points.
	 * @return        Map from sample position to estimated density.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "GetPDF"), Category = "Kernel_Density_Estimation")
		TMap<float,float> getPdf(float min, float max, int points);
};