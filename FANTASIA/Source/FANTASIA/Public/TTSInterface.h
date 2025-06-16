#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TTSInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UTTSInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class FANTASIA_API ITTSInterface
{
	GENERATED_BODY()

public:
	/**
	* To obtain the synthesis sound wave
	*
	*	@param response - synthesis results
	*	@param id - buffer synthesis id
	*
	**/
	virtual void getResult(FTTSData results, FString id) = 0;


	/**
	* To manage speech synthesis
	*
	*	@param ssml - synthesis data
	*	@param id - buffer synthesis id
	*
	**/
	UFUNCTION(Category = "TTS")
	virtual void TTSSynthesize(FString ssml, FString id) PURE_VIRTUAL(ITTSInterface::TTSSynthesize, );


	/**
	* To format the synthesis result into audio playable by Unreal
	*
	*	@parm id - buffer synthesis id
	*
	**/
	UFUNCTION(Category = "TTS")
	virtual USoundWave* TTSGetSound(FString id) PURE_VIRTUAL(ITTSInterface::TTSGetSound, return nullptr;);

	UFUNCTION(Category = "TTS")
	virtual TArray<float> TTSGetRawSound(FString id) PURE_VIRTUAL(ITTSInterface::TTSGetRawSound, TArray<float> empty; return empty;);
};