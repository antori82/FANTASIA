// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralTTSComponent.h"

using namespace std;

// Sets default values for this component's properties
UGeneralTTSComponent::UGeneralTTSComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGeneralTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!Speaker) {
		Speaker = NewObject<UAudioComponent>(this);
		Speaker->RegisterComponent();
	}
}

// Called every frame
void UGeneralTTSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}
}

void UGeneralTTSComponent::getResult(FTTSData response, FString id)
{
	handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);
	handle->Shutdown();

	Buffer.Remove(id);
	Buffer.Add(id, response);
	idSynthesisReady = id;
}


void UGeneralTTSComponent::TTSSynthesize(FString ssml, FString id)
{
	FTTSResultAvailableDelegate TTSResultSubscriber;
	TTSResultSubscriber.BindUObject(this, &UGeneralTTSComponent::getResult);
	handle = GeneralTTSThread::setup(ssml, id, Endpoint, A2Fpointer);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
    //SendToA2FaceComponent(id);//aggiunto da mettere nel thread
}

USoundWave* UGeneralTTSComponent::TTSGetSound(FString id) {
	USoundWaveProcedural* SyntheticVoice = NewObject<USoundWaveProcedural>();
	SyntheticVoice->SetSampleRate(SamplingRate);
	SyntheticVoice->NumChannels = 1;
	const int32 BytesDataPerSecond = SamplingRate;
	SyntheticVoice->RawPCMDataSize = Buffer[id].AudioData.Num() * sizeof(uint8);
	SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SamplingRate);
	SyntheticVoice->QueueAudio((const uint8*)Buffer[id].AudioData.GetData(), SyntheticVoice->RawPCMDataSize);
	return SyntheticVoice;
}

TArray<float> UGeneralTTSComponent::TTSGetRawSound(FString id) {
	TArray<float> AudioData;

	for (int i = 0; i < Buffer[id].AudioData.Num() * sizeof(uint8); i += 2) {
		float NormalizedSample = 0.0f;
		int16 Sample = *reinterpret_cast<int16*>(&Buffer[id].AudioData.GetData()[i]);
		NormalizedSample = Sample / 32768.0f;

		AudioData.Add(NormalizedSample);
	}

    FString Output;
    for (float Value : AudioData)
    {
        Output += FString::Printf(TEXT("%.2f "), Value);
    }

    UE_LOG(LogTemp, Warning, TEXT("AudioData: %s"), *Output);



    A2Fpointer->LoadRawSoundFromTTS(&AudioData);//chiama direttamente la funzione

    A2Fpointer->PlayAudio(AudioData);

	return AudioData;//returnare un puntatore alla memoria, non una copia
}


TArray<float> UGeneralTTSComponent::TTSGetRawSoundfromPath(const FString& FilePath) 
{
    TArray<uint8> RawFileData;

    // Legge il file (.wav) in un array di byte
    if (!FFileHelper::LoadFileToArray(RawFileData, *FilePath))
    {
        UE_LOG(LogTemp, Error, TEXT("Impossibile caricare il file: %s"), *FilePath);
        return TArray<float>();
    }

    // Usa FWaveModInfo per leggere i dati del file .wav
    FWaveModInfo WaveInfo;
    if (!WaveInfo.ReadWaveInfo(RawFileData.GetData(), RawFileData.Num()))
    {
        UE_LOG(LogTemp, Error, TEXT("Impossibile interpretare il file .wav: %s"), *FilePath);
        return TArray<float>();
    }

    // Calcola il numero di sample: il WaveInfo contiene la dimensione in byte dei sample
    // e pBitsPerSample indica la quantità di bit per sample (solitamente 16)
    int32 BitsPerSample = *WaveInfo.pBitsPerSample;
    int32 NumBytesPerSample = BitsPerSample / 8;
    int32 NumSamples = WaveInfo.SampleDataSize / NumBytesPerSample;

    TArray<float> FloatData;
    FloatData.Reserve(NumSamples);

    // In questo esempio assumiamo che il file sia a 16 bit per sample.
    // Se usi un formato diverso dovrai regolare la conversione.
    if (BitsPerSample == 16)
    {
        const int16* SampleData = reinterpret_cast<const int16*>(WaveInfo.SampleDataStart);
        for (int32 i = 0; i < NumSamples; i++)
        {
            int16 SampleValue = SampleData[i];
            // Converti in float normalizzando (l'intervallo per i 16 bit è -32768 a 32767)
            float FloatValue = SampleValue / 32768.0f;
            FloatData.Add(FloatValue);
        }
    }
    else if (BitsPerSample == 32)
    {
        const int32* SampleData = reinterpret_cast<const int32*>(WaveInfo.SampleDataStart);
        for (int32 i = 0; i < NumSamples; i++)
        {
            int32 SampleValue = SampleData[i];
            // Assumendo che l'intervallo per 32-bit sia -2147483648 a 2147483647
            float FloatValue = SampleValue / 2147483648.0f;
            FloatData.Add(FloatValue);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Formato dei sample non gestito: %d bit per sample"), BitsPerSample);
    }

    const int32 MaxSamplesToPrint = 20;
    FString Output = TEXT("Valori FloatData: ");
    for (int32 i = 0; i < FMath::Min(MaxSamplesToPrint, FloatData.Num()); ++i)
    {
        Output += FString::Printf(TEXT("%.4f, "), FloatData[i]);
    }
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Output);
    UE_LOG(LogTemp, Warning, TEXT("Totale sample audio estratti: %d"), FloatData.Num());



    return FloatData;
}

void UGeneralTTSComponent::SendToA2FaceComponent(FString id)
{
    if (A2Fpointer)
    {
        A2Fpointer->ReceivingDataFunction(TTSGetRawSound(id));
    }
}





