#include "TestComponents.h"
#include <iostream>

UTestComponents::UTestComponents()
{
    PrimaryComponentTick.bCanEverTick = true;
    everything_start = std::chrono::high_resolution_clock::now();
}

UTestComponents::~UTestComponents()
{
    everything_end = std::chrono::high_resolution_clock::now();
    total_duration = everything_end - everything_start;

    UE_LOG(LogTemp, Warning, TEXT("Tutti i test eseguiti in %f secondi"), total_duration.count());
}


void UTestComponents::SWIPrologComponentTest()
{
    function_start = std::chrono::high_resolution_clock::now();
    //chiamata
    function_end = std::chrono::high_resolution_clock::now();
}


void UTestComponents::InfluenceDiagramTest() 
{
    function_start = std::chrono::high_resolution_clock::now();
    //chiamata
    function_end = std::chrono::high_resolution_clock::now();
}

void UTestComponents::TTSAzureTest()
{
    function_start = std::chrono::high_resolution_clock::now();
    //chiamata
    function_end = std::chrono::high_resolution_clock::now();
}

void UTestComponents::TTSGeneralTest()
{
    function_start = std::chrono::high_resolution_clock::now();
    //chiamata
    function_end = std::chrono::high_resolution_clock::now();
}

void UTestComponents::Audio2FaceTest()
{
    function_start = std::chrono::high_resolution_clock::now();
    //chiamata
    function_end = std::chrono::high_resolution_clock::now();
}

void UTestComponents::OllamaComponentsTest()
{
    function_start = std::chrono::high_resolution_clock::now();
    //chiamata
    function_end = std::chrono::high_resolution_clock::now();
}

void UTestComponents::OpenAIComponentTest()
{
    function_start = std::chrono::high_resolution_clock::now();
    //chiamata
    function_end = std::chrono::high_resolution_clock::now();
}