#include "AzureASRThread.h"

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

AzureASRThread* AzureASRThread::Runnable = NULL;

AzureASRThread::AzureASRThread(shared_ptr<SpeechConfig> config, shared_ptr<AudioConfig> audioInput, EAzureASREnum Mode) : StopTaskCounter(0)
{
	ASRMode = Mode;
	ASRConfig = config;
	Thread = FRunnableThread::Create(this, TEXT("AzureASRThread"), 0, TPri_BelowNormal);
}

AzureASRThread::AzureASRThread(shared_ptr<SpeechConfig> config, EAzureASREnum Mode) : StopTaskCounter(0)
{
	ASRMode = Mode;
	Thread = FRunnableThread::Create(this, TEXT("AzureASRThread"), 0, TPri_BelowNormal);
}

AzureASRThread::~AzureASRThread() {
	delete Thread;
	Thread = NULL;
}

bool AzureASRThread::Init()
{
	recognizer = SpeechRecognizer::FromConfig(ASRConfig);

	return true;
}

uint32 AzureASRThread::Run()
{
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

void AzureASRThread::Stop()
{
	StopTaskCounter.Increment();
	switch (ASRMode) {
	case EAzureASREnum::ASR_CONTINUOUS:
		StopContinuousRecognition();
	}
}

AzureASRThread* AzureASRThread::setup(shared_ptr<SpeechConfig> config, shared_ptr<AudioConfig> audioInput, EAzureASREnum Mode)
{
	if (FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new AzureASRThread(config, audioInput, Mode);
	}
	return Runnable;
}

AzureASRThread* AzureASRThread::setup(shared_ptr<SpeechConfig> config, EAzureASREnum Mode)
{
	if (FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new AzureASRThread(config, Mode);
	}
	return Runnable;
}

void AzureASRThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void AzureASRThread::Shutdown()
{
	if (Runnable)
	{
		//Runnable->EnsureCompletion();
		//delete Runnable;
		Runnable = NULL;
	}
}

void AzureASRThread::StartContinuousRecognition() {

	// promise for synchronization of recognition end.
	promise<void> recognitionEnd;

	// Subscribes to events.
	recognizer->Recognizing.Connect([&PartialRecognitionAvailable = PartialRecognitionAvailable](const SpeechRecognitionEventArgs& e)
		{
			PartialRecognitionAvailable.Broadcast(e.Result->Text.c_str());
		});

	recognizer->Recognized.Connect([&PartialRecognitionAvailable = PartialRecognitionAvailable](const SpeechRecognitionEventArgs& e)
		{
			FString message = "Recognized: ";
			PartialRecognitionAvailable.Broadcast(message.Append(e.Result->Text.c_str()));
			if (e.Result->Reason == ResultReason::RecognizedSpeech)
			{
				//FString message = "Recognized: ";
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message.Append(e.Result->Text.c_str()));
			}
			else if (e.Result->Reason == ResultReason::NoMatch)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "NOMATCH: Speech could not be recognized.");
			}
		});

	recognizer->Canceled.Connect([&recognitionEnd, &PartialRecognitionAvailable = PartialRecognitionAvailable](const SpeechRecognitionCanceledEventArgs& e)
		{
			PartialRecognitionAvailable.Broadcast(e.ErrorDetails.c_str());
			//recognitionEnd.set_value();
			/*switch (e.Reason)
			{
			case CancellationReason::EndOfStream:
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "CANCELED: Reach the end of the file.");
				break;

			case CancellationReason::Error:
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, message.Append(e.ErrorDetails.c_str()));
				break;

			default:
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "CANCELED: received unknown reason.");
			}*/
		});

	recognizer->SessionStopped.Connect([&recognitionEnd, &PartialRecognitionAvailable = PartialRecognitionAvailable](const SessionEventArgs& e)
		{
			PartialRecognitionAvailable.Broadcast("Test3");
			//recognitionEnd.set_value();
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Session stopped.");
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
	if (result->Reason == ResultReason::RecognizedSpeech)
	{
		PartialRecognitionAvailable.Broadcast(UTF8_TO_TCHAR(result->Text.c_str()));
	}
	else if (result->Reason == ResultReason::NoMatch)
	{
		PartialRecognitionAvailable.Broadcast("No match");
	}
	else if (result->Reason == ResultReason::Canceled)
	{
		PartialRecognitionAvailable.Broadcast("Cancelled");
	}
}

FDelegateHandle AzureASRThread::PartialRecognitionAvailableSubscribeUser(FPartialRecognitionAvailableDelegate& UseDelegate)
{
	return PartialRecognitionAvailable.Add(UseDelegate);
}

void AzureASRThread::PartialRecognitionAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	PartialRecognitionAvailable.Remove(DelegateHandle);
}