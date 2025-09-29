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

FMyThread::FMyThread(FString inPlayerA2F_name, FString inserver_url, int32 inSampleRate) : StopTaskCounter(0)
{

    PlayerA2F_name = inPlayerA2F_name;
    server_url = inserver_url;
    SampleRate = inSampleRate;

    Thread = FRunnableThread::Create(this, TEXT("A2FaceThread"), 0, TPri_Normal);
}

FMyThread::~FMyThread() {
    if (Thread != NULL) {
        delete Thread;
        Thread = NULL;
    }
}

FMyThread* FMyThread::setup(FString inPlayerA2F_name, FString inserver_url, int32 inSampleRate)
{
    if (!Runnable && FPlatformProcess::SupportsMultithreading())
    {
        grpc_init();
        Runnable = new FMyThread(inPlayerA2F_name, inserver_url, inSampleRate);
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

    while (!StopRecording) {
        if (!AudioData.IsEmpty()) {
            PushAudioStreamRequest* requestAudio = new PushAudioStreamRequest();
           
            lockAudioBuffer.Lock();
            requestAudio->set_audio_data(AudioData.GetData(), AudioData.Num() * sizeof(float));
            writer->Write(*requestAudio);
            AudioData.Empty();
            lockAudioBuffer.Unlock();
        }
    }

    writer->WritesDone();
    Status status = writer->Finish();

    bIsRunning = false;
    Shutdown();
}

void FMyThread::QueueAudio(TArray<float> data) {
    lockAudioBuffer.Lock();
    AudioData.Append(data);
    lockAudioBuffer.Unlock();
}
