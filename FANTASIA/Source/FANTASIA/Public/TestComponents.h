#pragma once

#include <iostream>
#include <chrono>
#include "SWIPrologComponent.h"
#include "InfluenceDiag.h"
#include "AzureTTSComponent.h"
#include "GeneralTTSComponent.h"
#include "Audio2FaceComponent.h"
#include "OllamaComponent.h"
#include "OpenAIComponent.h"

#include "TestComponents.generated.h"



//includes tutte le funzioni

UCLASS(ClassGroup = (TestComponents), meta = (BlueprintSpawnableComponent), config = Game)
class UTestComponents : public UActorComponent 
{
	
	GENERATED_BODY()

private:
	std::chrono::high_resolution_clock::time_point function_start;
	std::chrono::high_resolution_clock::time_point function_end;
	std::chrono::high_resolution_clock::time_point everything_start;
	std::chrono::high_resolution_clock::time_point everything_end;

	std::chrono::duration<double> single_delta;
	std::chrono::duration<double> total_delta;

protected:


public:
	UTestComponents();
	~UTestComponents();

	void SWIPrologComponentTest();

	void InfluenceDiagramTest();

	void TTSAzureTest();

	void TTSGeneralTest();

	void Audio2FaceTest();

	void OllamaComponentTest();

	void OpenAIComponentTest();
};
	

	