// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Audio2FaceThread.h"

using namespace grpc;
using namespace std;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace nvidia;
using audio2face::Audio2Face;
using audio2face::PushAudioRequestStart;
using audio2face::PushAudioStreamRequest;
using audio2face::PushAudioStreamResponse;


FMyThread* FMyThread::Runnable = NULL;

FMyThread::FMyThread(FString inPlayerA2F_name, FString inserver_url, TArray<float> inAudioData, int32 inSampleRate, bool str) : StopTaskCounter(0)
{
    PlayerA2F_name = inPlayerA2F_name;
    server_url = inserver_url;
    AudioData = inAudioData;//audio che arriva al componente Audio2Face
    SampleRate = inSampleRate;
    stream = str;

    Thread = FRunnableThread::Create(this, TEXT("A2FaceThread"), 0, TPri_Normal);
}

FMyThread::~FMyThread() {
    if (Thread != NULL) {
        delete Thread;
        Thread = NULL;
    }
}

FMyThread* FMyThread::setup(FString inPlayerA2F_name, FString inserver_url, TArray<float> inAudioData, int32 inSampleRate, bool stream)
{
    if (!Runnable && FPlatformProcess::SupportsMultithreading())
    {
        grpc_init();
        Runnable = new FMyThread(inPlayerA2F_name, inserver_url, inAudioData, inSampleRate, stream);
    }
    return Runnable;
}


bool FMyThread::Init()
{
    return true;
}

uint32 FMyThread::Run()
{
    bIsRunning = true;
    //discrimina se è in streaming o meno, se lo è voglio che mi manda a una funzione che devo scrivereio
    //e che mi gestisce l'arrivo dei dati o meno dal TTS, quindi voglio che rimane in attesa appena arrivano
    //i dati e chiude quando finisce l'arrivo dei dati
    /*if (!stream)
    {
        SendToAudio2FaceGrpc();
    }
    else SendStreamAudio2FaceGrpc();*/

    SendToAudio2FaceGrpc();
    
    return 0;
}

void FMyThread::Stop()
{
    StopTaskCounter.Increment();
}

void FMyThread::EnsureCompletion()
{
    Stop();
    Thread->WaitForCompletion();
}

void FMyThread::Shutdown()
{
    if (Runnable)
    {
        grpc_shutdown();
        Runnable->StopRecording = false;
        Runnable = NULL;
    }
}

bool FMyThread::IsThreadRunning() const {
    return bIsRunning;
}

void FMyThread::StopSending() {
    StopRecording = true;
}

//void FMyThread::SendToAudio2FaceGrpc()
//{
//    int chunk_size = SampleRate / 10; // 100ms per chunk
//    int originalChunkSize = chunk_size;
//
//    for (int32 i = 0; i < AudioData.Num(); i += originalChunkSize) {
//        if (StopRecording || StopTaskCounter.GetValue() > 0) {
//            break;
//        }
//
//        int32 currentChunk = FMath::Min(originalChunkSize, AudioData.Num() - i);
//        const float* chunk_data = AudioData.GetData() + i;
//
//        // Log minimale del buffer corrente
//        FString ChunkLog = TEXT("Streaming Chunk: [");
//        for (int32 j = 0; j < FMath::Min(5, currentChunk); ++j) {
//            ChunkLog += FString::Printf(TEXT("%.4f "), chunk_data[j]);
//        }
//        ChunkLog += TEXT("...]");
//
//        UE_LOG(LogTemp, Log, TEXT("%s"), *ChunkLog);
//    }
//
//    UE_LOG(LogTemp, Warning, TEXT("Fine test stream buffer (simulato)"));
//    bIsRunning = false;
//    Shutdown();
//}

void FMyThread::SendToAudio2FaceGrpc()//da testare
{
    string url = TCHAR_TO_UTF8(*server_url);
    std::shared_ptr<Channel> channel2 = grpc::CreateChannel(url, grpc::InsecureChannelCredentials());

    //sostituire con auto
    std::unique_ptr<Audio2Face::Stub> stub2 = Audio2Face::NewStub(channel2); // modificato, aveva 2 argomenti, il secondo null, ma non accettava null

    //creo un nuovo oggetto che verrà richiamato quando viene inviato uno stream audio

    string PlayerA2FaceName = TCHAR_TO_UTF8(*PlayerA2F_name);
    int chunk_size = SampleRate / 10;
    bool block_until_playback_is_finished = true;

    ClientContext context;
    PushAudioRequestStart start_marker;
    start_marker.set_instance_name(PlayerA2FaceName);
    start_marker.set_samplerate(SampleRate);
    start_marker.set_block_until_playback_is_finished(block_until_playback_is_finished);


    //messaggio iniziale col marker
    PushAudioStreamRequest* request = new PushAudioStreamRequest();
    request->set_allocated_start_marker(&start_marker);

    //writer Stream per l'invio dei dati
    PushAudioStreamResponse response;
    std::unique_ptr<grpc::ClientWriter<PushAudioStreamRequest>> writer(stub2->PushAudioStream(&context, &response));
    writer->Write(*request);
    delete request;


    int originalChunkSize = chunk_size;

    for (int32 i = 0; i < AudioData.Num(); i += originalChunkSize) {
        if (StopRecording || StopTaskCounter.GetValue() > 0) {
            break;
        }
       
        int32 currentChunk = FMath::Min(i + chunk_size, AudioData.Num() - i );
        const float* chunk_data = AudioData.GetData() + i;
        //******************************Da eliminare, testing************************

        int32 numValuesToShow = FMath::Min(5, currentChunk);
        FString debugStr = TEXT("Chunk values: ");
        for (int32 j = 0; j < numValuesToShow; ++j) {
            debugStr += FString::Printf(TEXT("%.3f "), chunk_data[j]);
            UE_LOG(LogTemp, Log, TEXT("%s"), *debugStr);
        }
        if (GEngine) {
            // Visualizza il messaggio sullo schermo per 5 secondi, colore verde
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, debugStr);
        }

        //******************************Da eliminare, testing************************
        requestAudio = new PushAudioStreamRequest();


        requestAudio->set_audio_data(chunk_data, currentChunk * sizeof(float));//richiama questa cosa ogni volta che un requestAudio è chiamato
        if (!writer->Write(*requestAudio)) {
            delete requestAudio;
            break;
        }
        delete requestAudio;
    }

    writer->WritesDone();
    Status status = writer->Finish();

    if (status.ok() && response.success()) {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Audio stream pushed successfully!"));
    }
    else {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Audio stream failed to push!"));
    }
    bIsRunning = false;
    Shutdown();
}


