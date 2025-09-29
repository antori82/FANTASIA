#include "Audio2FaceComponent.h"

//using namespace std;

UAudio2FaceComponent::UAudio2FaceComponent() {
    PlayerA2F_name = TEXT("/World/audio2face/audio_player_streaming");
    server_url = TEXT("localhost:50051");

    PrimaryComponentTick.bCanEverTick = false;
}


void UAudio2FaceComponent::QueueAudio(TArray<float> data)
{
    MyThread->QueueAudio(data);
}

void UAudio2FaceComponent::A2FaceFMyThread(int32 sampleRate) {
    if (MyThread!=NULL &&  MyThread->IsThreadRunning()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("L'audio ancora in esecuzione,riprovare piu tardi"));
    }
    else {
        MyThread = FMyThread::setup(PlayerA2F_name, server_url, sampleRate);
    }
}

void UAudio2FaceComponent::LoadSoundWaveFromTTS(USoundWave* sound) {
    TArray<uint8> tempData;
    uint32 sampleRate;
    uint16 numChannels;

    AudioData.Empty();
    sound->GetImportedSoundWaveData(tempData, sampleRate, numChannels);

    for (int i = 0; i < tempData.Num(); i += 2) {
        float NormalizedSample = 0.0f;
        
        int16 Sample = *reinterpret_cast<int16*>(&tempData);
        NormalizedSample = Sample / 32768.0f;

        AudioData.Add(NormalizedSample);
    }
}

// Called when the game starts
void UAudio2FaceComponent::BeginPlay() {
	Super::BeginPlay();
    A2FaceFMyThread(16000);
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

