#include "Audio2FaceComponent.h"

using namespace std;

UAudio2FaceComponent::UAudio2FaceComponent() {
    PlayerA2F_name = TEXT("/World/audio2face/audio_player_streaming");
    server_url = TEXT("localhost:50051");

    PrimaryComponentTick.bCanEverTick = false;
}


void UAudio2FaceComponent::ReadAudioFile(USoundWave* SoundWave, bool tts)
{
	TArray<float>  AudioData;
	int32 sampleRate;
    if (tts)
        LoadSoundWaveFromTTS_Internal(AudioData, sampleRate, SoundWave);
    else
    	LoadSoundWaveFromFile_Internal(AudioData, sampleRate, SoundWave);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("sending audio.."));
  
	A2FaceFMyThread(AudioData, sampleRate);
    PrintTimeReadAudiofile();
}

void UAudio2FaceComponent::A2FaceFMyThread(TArray<float> AudioData, int32 sampleRate) {
    if (MyThread!=NULL &&  MyThread->IsThreadRunning()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("L'audio ancora in esecuzione,riprovare piu tardi"));
    }
    else {
        MyThread = FMyThread::setup(PlayerA2F_name, server_url, AudioData, sampleRate);
        FPlatformProcess::Sleep(0.01);
    }
}

void UAudio2FaceComponent::LoadSoundWaveFromTTS_Internal(TArray<float>& OutAudioData, int32& sampleRate, USoundWave* SoundWave) {
    OutAudioData.Empty();
    for (int i = 0; i < SoundWave->RawPCMDataSize; i += 2) {
        float NormalizedSample = 0.0f;

        int16 Sample = *reinterpret_cast<int16*>(&SoundWave->RawPCMData[i]);
        NormalizedSample = Sample / 32768.0f;

        OutAudioData.Add(NormalizedSample);
    }
    sampleRate = 16000;
}

void UAudio2FaceComponent::LoadSoundWaveFromFile_Internal(TArray<float>& OutAudioData, int32& sampleRate, USoundWave* SoundWave)
{
    TArray<uint8> AudioBytes;
    uint32 SampleRate;
    uint16 NumChannels;
    if (SoundWave!=NULL && SoundWave->GetImportedSoundWaveData(AudioBytes, SampleRate, NumChannels)) {
        TArray<float> AudioData;
        for (int32 i = 0; i < AudioBytes.Num(); i += 2 * NumChannels) {
            float NormalizedSample = 0.0f;

            if (NumChannels == 2) {
                int16 Sample1 = *reinterpret_cast<int16*>(&AudioBytes[i]);
                int16 Sample2 = *reinterpret_cast<int16*>(&AudioBytes[i + 2]);
                NormalizedSample = (Sample1 + Sample2) / 2.0f / 32768.0f;
            }
            else {
                int16 Sample = *reinterpret_cast<int16*>(&AudioBytes[i]);
                NormalizedSample = Sample / 32768.0f;
            }

            AudioData.Add(NormalizedSample);

        }
        OutAudioData = AudioData;
        sampleRate = SampleRate;
    }
    else {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Errore nella apertura del soundwave"));
    }
}

void UAudio2FaceComponent::PrintTimeReadAudiofile() {
    Fine = FDateTime::UtcNow();
    FTimespan TempoTrascorso = Fine - Inizio;
    int32 MillisecondiTrascorsi = TempoTrascorso.GetTotalMilliseconds();
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

