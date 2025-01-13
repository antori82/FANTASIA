#pragma once

#include "FANTASIA.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "GeneralTTSThread.h"
#include <speechapi_cxx.h>
#include <iostream>
#include <string>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include "TTSInterface.h"
#include "GeneralTTSComponent.generated.h"

using namespace std;

UCLASS(meta = (BlueprintSpawnableComponent))
class UGeneralTTSComponent : public UActorComponent, public ITTSInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGeneralTTSComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TMap<FString, FTTSData> Buffer;
	TMap<FString, FString> PendingSSML;
	shared_ptr<SpeechConfig> config;
	GeneralTTSThread* handle;

	FDelegateHandle TTSResultAvailableHandle;

	void getResult(FTTSData response, FString id) override;

	FSynthesizedInternalEvent synthesisReadyInternal;

	FString idSynthesisReady = "";

public:

	UPROPERTY(BlueprintReadWrite, Category = "Speech to Text")
	UAudioComponent* Speaker;

	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
	FSynthesizedEvent SynthesisReady;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	FString Endpoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", meta = (DisplayName = "Sampling Rate", ClampMin = "8000", ClampMax = "96000", Default = "44100"))
	int32 SamplingRate = 44100;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "Plugin TTS"), Category = "TTS")
	void TTSSynthesize(FString ssml, FString id) override;

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound General", Keywords = "Plugin TTS"), Category = "TTS")
	USoundWave* TTSGetSound(FString id) override;
};