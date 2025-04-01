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

FMyThread::FMyThread(FString inPlayerA2F_name, FString inserver_url, TArray<float> inAudioData, int32 inSampleRate) : StopTaskCounter(0)
{
    PlayerA2F_name = inPlayerA2F_name;
    server_url = inserver_url;
    AudioData = inAudioData;//audio che arriva al componente Audio2Face
    SampleRate = inSampleRate;

    Thread = FRunnableThread::Create(this, TEXT("A2FaceThread"), 0, TPri_Normal);
}

FMyThread::~FMyThread() {
    if (Thread != NULL) {
        delete Thread;
        Thread = NULL;
    }
}

FMyThread* FMyThread::setup(FString inPlayerA2F_name, FString inserver_url, TArray<float> inAudioData, int32 inSampleRate)
{
    if (!Runnable && FPlatformProcess::SupportsMultithreading())
    {
        grpc_init();
        Runnable = new FMyThread(inPlayerA2F_name, inserver_url, inAudioData, inSampleRate);
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
void FMyThread::SendToAudio2FaceGrpc()
{
    string url = TCHAR_TO_UTF8(*server_url);
    std::shared_ptr<Channel> channel2 = grpc::CreateChannel(url, grpc::InsecureChannelCredentials());

    std::unique_ptr<Audio2Face::Stub> stub2 = Audio2Face::NewStub(channel2);

    string PlayerA2FaceName = TCHAR_TO_UTF8(*PlayerA2F_name);
    int chunk_size = SampleRate / 10;
    bool block_until_playback_is_finished = true;

    ClientContext context;
    PushAudioRequestStart start_marker;
    start_marker.set_instance_name(PlayerA2FaceName);
    start_marker.set_samplerate(SampleRate);
    start_marker.set_block_until_playback_is_finished(block_until_playback_is_finished);

    PushAudioStreamRequest* request = new PushAudioStreamRequest();
    request->set_allocated_start_marker(&start_marker);

    PushAudioStreamResponse response;
    std::unique_ptr<grpc::ClientWriter<PushAudioStreamRequest>> writer(stub2->PushAudioStream(&context, &response));
    writer->Write(*request);

    for (int32 i = 0; i < AudioData.Num(); i += chunk_size) {
        if (StopRecording == true) {
            break;
        }
       
        int32 chunk_end = FMath::Min(i + chunk_size, AudioData.Num());
        const float* chunk_data = AudioData.GetData() + i;
        chunk_size = chunk_end - i;
        PushAudioStreamRequest* requestAudio = new PushAudioStreamRequest();//mettilo in .h
        requestAudio->set_audio_data(chunk_data, chunk_size * sizeof(float));//richiama questa cosa ogni volta che un requestAudio è chiamato
        if (!writer->Write(*requestAudio)) {
            break;
        }
    }

    writer->WritesDone();
    Status status = writer->Finish();

    if (status.ok()) {
        if (response.success()) {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Audio stream pushed successfully!"));
        }
    }
    else {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Audio stream failed to push!"));
    }
    bIsRunning = false;
    Shutdown();
}


