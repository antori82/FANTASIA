#pragma once


#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Audio2FaceConverterInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UAudio2FaceConverterInterface : public UInterface
{
    GENERATED_BODY()
};

class IAudio2FaceConverterInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Audio2FaceInterface")
    void PlayAudio(const TArray<float>& Data);
};