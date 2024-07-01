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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASIA_API UAudio2FaceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudio2FaceComponent();
	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	FString PlayerA2F_name;

	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	FString server_url;
	FMyThread* MyThread;
	FDateTime Inizio;
	FDateTime Fine;
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NvidiaReadAudioFile", Keywords = "Nvidia Plugin"), Category = "Audio2Face")
	void ReadAudioFile(USoundWave* SoundWave, bool tts);

	void A2FaceFMyThread(TArray<float> AudioData, int32 sampleRate);
	void LoadSoundWaveFromTTS_Internal(TArray<float>& OutAudioData, int32& sampleRate, USoundWave* SoundWave);
	void LoadSoundWaveFromFile_Internal(TArray<float>& OutAudioData, int32& sampleRate, USoundWave* SoundWave);
	void PrintTimeReadAudiofile();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
};
