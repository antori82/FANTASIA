// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FANTASIA.h"

#include "CoreMinimal.h"
#include "FANTASIATypes.h"


#include "Audio2FaceThread.h"
#include "Audio2FaceConverterInterface.h"


#include <string>
#include <sound/soundwaveprocedural.h>
#include <kismet/gameplaystatics.h>
#include "Sound/SoundWave.h"
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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent , implements = "Audio2FaceConverterInterface"))
class FANTASIA_API UAudio2FaceComponent : public UActorComponent, public IAudio2FaceConverterInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudio2FaceComponent();
	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	FString PlayerA2F_name;

	TArray<float> AudioData;
	bool stream = false;

	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	FString server_url;
	FMyThread* MyThread;
	FDateTime Inizio;
	FDateTime Fine;
	
	virtual void PlayAudio(TArray<float> data) override;//funzione di richiamo dall'interfaccia A2F

	void A2FaceFMyThread(int32 sampleRate);	
	void LoadRawSoundFromTTS(const TArray<float>* soundData);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ReceivingDataFunction(const TArray<float>& data);
};
