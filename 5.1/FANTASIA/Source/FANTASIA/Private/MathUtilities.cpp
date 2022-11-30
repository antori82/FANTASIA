#include "MathUtilities.h"

std::vector<float> linspace(float start, float end, size_t points)
{
	std::vector<float> res(points);
	float step = (end - start) / (points - 1);
	size_t i = 0;
	for (auto& e : res)
	{
		e = start + step * i++;
	}
	return res;
}

UKernelDensityEstimator::UKernelDensityEstimator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

void UKernelDensityEstimator::setData(TArray<float> newData) {

	data.clear();
	for (int i = 0; i < newData.Num(); i++)
		data.push_back(newData[i]);
}

float UKernelDensityEstimator::evaluate(float point) {
	kdepp::Kde1d_f kernel(data);

	return kernel.eval(point);
}

TMap<float,float> UKernelDensityEstimator::getPdf(float min, float max, int nPoints) {
	TMap<float, float> out;
	float ev;
	float sum = 0.0;

	std::vector<float> points = linspace(min, max, nPoints);
	std::vector<float> values;

	for (float val : points) {
		ev = evaluate(val);
		values.push_back(ev);
		sum += ev;
	}

	for (int i = 0; i < size(points); i++)
		out.Add(points[i], values[i]/sum);

	return out;
}