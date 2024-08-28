#include "AzureASRThread.h"

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

AzureASRThread* AzureASRThread::Runnable = NULL;

AzureASRThread::AzureASRThread(shared_ptr<SpeechConfig> config, shared_ptr<AudioConfig> audioInput, EAzureASREnum Mode) : StopTaskCounter(0) {
	ASRMode = Mode;
	ASRConfig = config;
	Thread = FRunnableThread::Create(this, TEXT("AzureASRThread"), 0, TPri_BelowNormal);
}

AzureASRThread::AzureASRThread(shared_ptr<SpeechConfig> config, EAzureASREnum Mode) : StopTaskCounter(0) {
	ASRMode = Mode;
	Thread = FRunnableThread::Create(this, TEXT("AzureASRThread"), 0, TPri_BelowNormal);
}

AzureASRThread::~AzureASRThread() {
	delete Thread;
	Thread = NULL;
}

bool AzureASRThread::Init() {
	recognizer = SpeechRecognizer::FromConfig(ASRConfig);

	return true;
}

uint32 AzureASRThread::Run() {
	switch (ASRMode) {
	case EAzureASREnum::ASR_CONTINUOUS:
		StartContinuousRecognition();
		return 0;
	case EAzureASREnum::ASR_ONESHOT:
		StartOneShotRecognition();
		return 0;
	}
	return -1;
}

void AzureASRThread::Stop() {
	StopTaskCounter.Increment();
	switch (ASRMode) {
	case EAzureASREnum::ASR_CONTINUOUS:
		StopContinuousRecognition();
	}
}

AzureASRThread* AzureASRThread::setup(shared_ptr<SpeechConfig> config, shared_ptr<AudioConfig> audioInput, EAzureASREnum Mode) {
	if (FPlatformProcess::SupportsMultithreading()) {
		Runnable = new AzureASRThread(config, audioInput, Mode);
	}
	return Runnable;
}

AzureASRThread* AzureASRThread::setup(shared_ptr<SpeechConfig> config, EAzureASREnum Mode) {
	if (FPlatformProcess::SupportsMultithreading()) {
		Runnable = new AzureASRThread(config, Mode);
	}
	return Runnable;
}

void AzureASRThread::EnsureCompletion() {
	Stop();
	Thread->WaitForCompletion();
}

void AzureASRThread::Shutdown() {
	if (Runnable) {
		Runnable = NULL;
	}
}

void AzureASRThread::StartContinuousRecognition() {

	// promise for synchronization of recognition end.
	promise<void> recognitionEnd;

	// Subscribes to events.
	recognizer->Recognizing.Connect([&PartialRecognitionAvailable = PartialRecognitionAvailable](const SpeechRecognitionEventArgs& e) {
			PartialRecognitionAvailable.Broadcast(e.Result->Text.c_str());
		});

	recognizer->Recognized.Connect([&FinalRecognitionAvailable = FinalRecognitionAvailable](const SpeechRecognitionEventArgs& e) {
			if (e.Result->Reason == ResultReason::RecognizedSpeech) {
				FinalRecognitionAvailable.Broadcast(e.Result->Text.c_str());
			}
			else if (e.Result->Reason == ResultReason::NoMatch) {
				UE_LOG(LogTemp, Warning, TEXT("[AzureASRComponent] NOMATCH: Speech could not be recognized."));
				FinalRecognitionAvailable.Broadcast("NOMATCH");
			}
		});

	recognizer->Canceled.Connect([&recognitionEnd, &FinalRecognitionAvailable = FinalRecognitionAvailable](const SpeechRecognitionCanceledEventArgs& e) {
			FinalRecognitionAvailable.Broadcast("ERROR");
			switch (e.Reason)
			{
			case CancellationReason::EndOfStream:
				UE_LOG(LogTemp, Warning, TEXT("[AzureASRComponent] CANCELED: Stream closed."));
				break;
			case CancellationReason::Error:
				UE_LOG(LogTemp, Error, TEXT("[AzureASRComponent]: %hs"), e.ErrorDetails.c_str());
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("[AzureASRComponent]: CANCELED: received unknown reason."));
			}
		});

	recognizer->SessionStopped.Connect([&recognitionEnd, &PartialRecognitionAvailable = PartialRecognitionAvailable](const SessionEventArgs& e) {
			//PartialRecognitionAvailable.Broadcast("");
			UE_LOG(LogTemp, Warning, TEXT("[AzureASRComponent]: Session stopped"));
		});

	recognizer->StartContinuousRecognitionAsync().wait();

	// Waits for recognition end.
	recognitionEnd.get_future().wait();

	// Stops recognition.
	recognizer->StopContinuousRecognitionAsync().wait();
}

void AzureASRThread::StopContinuousRecognition() {
	recognizer->StopContinuousRecognitionAsync().get();
}

void AzureASRThread::StartOneShotRecognition()
{
	auto result = recognizer->RecognizeOnceAsync().get();

	// Checks result.
	if (result->Reason == ResultReason::RecognizedSpeech) {
		FinalRecognitionAvailable.Broadcast(UTF8_TO_TCHAR(result->Text.c_str()));
	}
	else if (result->Reason == ResultReason::NoMatch) {
		FinalRecognitionAvailable.Broadcast("NOMATCH");
	}
	else if (result->Reason == ResultReason::Canceled) {
		FinalRecognitionAvailable.Broadcast("CANCELLED");
	}
}

FDelegateHandle AzureASRThread::PartialRecognitionAvailableSubscribeUser(FPartialRecognitionAvailableDelegate& UseDelegate) {
	return PartialRecognitionAvailable.Add(UseDelegate);
}

void AzureASRThread::PartialRecognitionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) {
	PartialRecognitionAvailable.Remove(DelegateHandle);
}

FDelegateHandle AzureASRThread::FinalRecognitionAvailableSubscribeUser(FFinalRecognitionAvailableDelegate& UseDelegate) {
	return FinalRecognitionAvailable.Add(UseDelegate);
}

void AzureASRThread::FinalRecognitionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle) {
	FinalRecognitionAvailable.Remove(DelegateHandle);
}