// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#ifndef grpcc
#define grpcc
#include "EnableGrpcIncludes.h"
#include "Audio2Face/audio2face.grpc.pb.h"
#include "Audio2Face/audio2face.pb.h"
#include "DisableGrpcIncludes.h"
#include <grpcpp/grpcpp.h>

#endif // !grpc




#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "Templates/UniquePtr.h"


// FakeWriter.h
class FFakeWriter {
public:
	bool Write(const nvidia::audio2face::PushAudioStreamRequest& request) {
		UE_LOG(LogTemp, Log, TEXT("Simulazione invio chunk - dimensione: %d bytes"), request.audio_data().size());
		return true; // Simula che l'invio abbia avuto successo
	}

	void WritesDone() {
		UE_LOG(LogTemp, Log, TEXT("Fine scrittura simulata"));
	}

	grpc::Status Finish() {
		// Simula una risposta positiva
		grpc::Status status;
		return grpc::Status::OK;
	}
};



class FMyThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static FMyThread* Runnable;
	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	FString PlayerA2F_name;
	FString server_url;
	TArray<float> AudioData;
	int32 SampleRate;
	bool StopRecording = false;
	bool stream = false;

	//stream audio//spostato dal cpp
	nvidia::audio2face::PushAudioStreamRequest* requestAudio;

public:
	bool bIsRunning;
	//~~~ Thread Core Functions ~~~

	//Constructor
	FMyThread(FString inPlayerA2F_name, FString inserver_url, TArray<float>  inAudioData, int32 inSampleRate, bool stream);
	virtual ~FMyThread();
	static FMyThread* setup(FString inPlayerA2F_name, FString inserver_url, TArray<float>  inAudioData, int32 inSampleRate, bool stream);

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	

	
	virtual void Stop();
	// End FRunnable interface
	UFUNCTION(BlueprintCallable, Category = "Audio2FaceTEST")
	void SendToAudio2FaceGrpc();
	void StopSending();
	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();
	/** Checks if the thread is running */
	bool IsThreadRunning() const;
}; 
