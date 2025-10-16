// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FANTASIA.h"

#include "CoreMinimal.h"
#include "FANTASIATypes.h"

#include "Audio2FaceThread.h"
#include <string>
#include <sound/soundwaveprocedural.h>
#include <kismet/gameplaystatics.h>
#include "Sound/SoundWave.h"
#include "Sound/SoundWaveProcedural.h"
#include "Misc/FileHelper.h"
#include "AudioDecompress.h"
#include "Components/ActorComponent.h"

//HTTP REST Request
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/Guid.h"
#include "Logging/LogMacros.h"
////
#include "Audio2FaceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadSceneCompleteEvent, bool, sceneReady);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASIA_API UAudio2FaceComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	TArray<float> AudioData;
	FMyThread* MyThread;

	void A2FaceFMyThread(int32 sampleRate);
	void LoadSoundWaveFromTTS(USoundWave* sound);

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void signalSceneComplete();

public:	
	// Sets default values for this component's properties
	UAudio2FaceComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FLoadSceneCompleteEvent LoadSceneComplete;

	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	FString endpoint;

	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	uint32 port;
	
	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	FString A2FPlayerName;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Play Audio"), Category = "Audio2Face")
	void QueueAudio(TArray<float> data);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Scene"), Category = "Audio2Face")
	void LoadScene(FString sceneName = "Audio2Face.usd");

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Connect"), Category = "Audio2Face")
	void Connect();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
