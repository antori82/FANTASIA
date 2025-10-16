#include "Audio2FaceComponent.h"

//using namespace std;

UAudio2FaceComponent::UAudio2FaceComponent() {
    //A2FPlayerName = TEXT("/World/audio2face/audio_player_streaming");
    //endpoint = TEXT("localhost:50051");

    PrimaryComponentTick.bCanEverTick = false;
}


void UAudio2FaceComponent::QueueAudio(TArray<float> data)
{
    MyThread->QueueAudio(data);
}

void UAudio2FaceComponent::A2FaceFMyThread(int32 sampleRate) {
    if (MyThread==NULL) 
        MyThread = FMyThread::setup(A2FPlayerName, endpoint + ":" + FString::FromInt(port), sampleRate);
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

void UAudio2FaceComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (bWasSuccessful) {
        FString temp = Response->GetContentAsString();
        FTimerHandle timerHandle;
        const TSharedPtr<FJsonObject>* FileMessageObject;

        TSharedPtr<FJsonValue> JsonValue;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
        if (FJsonSerializer::Deserialize(Reader, JsonValue))
            if (JsonValue->TryGetObject(FileMessageObject))
                LoadSceneComplete.Broadcast(FileMessageObject->Get()->GetStringField(TEXT("status")) == "OK");
    }
}

void UAudio2FaceComponent::LoadScene(FString sceneName) {
    FHttpModule* Http = &FHttpModule::Get();
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
    Request->OnProcessRequestComplete().BindUObject(this, &UAudio2FaceComponent::OnResponseReceived);

    Request->SetURL(endpoint + ":8011" + "/A2F/USD/Load");
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    FString x = "{\"file_name\" : \"" + FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + "../Resources/" + sceneName) + "\"}";

    Request->SetContentAsString("{\"file_name\" : \"" + FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + "../Resources/" + sceneName) + "\"}");
    Request->ProcessRequest();
}

void UAudio2FaceComponent::Connect() {
    A2FaceFMyThread(16000);
}