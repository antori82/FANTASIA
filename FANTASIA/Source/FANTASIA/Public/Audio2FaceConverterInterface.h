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
    virtual void PlayAudio(TArray<float> Data) = 0;
};