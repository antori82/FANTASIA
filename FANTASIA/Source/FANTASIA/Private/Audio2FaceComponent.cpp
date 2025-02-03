﻿#include "Audio2FaceComponent.h"

//using namespace std;

UAudio2FaceComponent::UAudio2FaceComponent() {
    PlayerA2F_name = TEXT("/World/audio2face/audio_player_streaming");
    server_url = TEXT("localhost:50051");

    PrimaryComponentTick.bCanEverTick = false;
}


void UAudio2FaceComponent::PlayAudio(TArray<float> data)
{
	int32 sampleRate = 16000;
   
    LoadRawSoundFromTTS(data);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("sending audio.."));
  
	A2FaceFMyThread(sampleRate);
}

void UAudio2FaceComponent::A2FaceFMyThread(int32 sampleRate) {
    if (MyThread!=NULL &&  MyThread->IsThreadRunning()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("L'audio ancora in esecuzione,riprovare piu tardi"));
    }
    else {
        MyThread = FMyThread::setup(PlayerA2F_name, server_url, AudioData, sampleRate);
    }
}

void UAudio2FaceComponent::LoadRawSoundFromTTS(TArray<float> soundData) {
    AudioData.Empty();
    AudioData = soundData;

    //for (int i = 0; i < size; i += 2) {
    //    float NormalizedSample = 0.0f;
    //    int16 Sample = *reinterpret_cast<int16*>(&rawSound[i]);
    //    NormalizedSample = Sample / 32768.0f;

    //    AudioData.Add(NormalizedSample);
    //}
}

// Called when the game starts
void UAudio2FaceComponent::BeginPlay() {
	Super::BeginPlay();
}

void UAudio2FaceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);
    if (MyThread != NULL && MyThread->IsThreadRunning()) {
        MyThread->StopSending();
    }
}

// Called every frame
void UAudio2FaceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

