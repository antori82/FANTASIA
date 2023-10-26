#include "AzureTTSThread.h"

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

AzureTTSThread* AzureTTSThread::Runnable = NULL;

AzureTTSThread::AzureTTSThread(shared_ptr<SpeechConfig> config, FString inLanguage, FString inVoice, FString inKey, FString inRegion, FString inSsml, FString inID) : StopTaskCounter(0)
{
	TTSConfig = config;
	Language = inLanguage;
	Voice = inVoice;
	Key = inKey;
	Region = inRegion;
	ssml = inSsml;
	id = inID;
	Thread = FRunnableThread::Create(this, TEXT("AzureTTSThread"), 0, TPri_Normal);
}

AzureTTSThread::~AzureTTSThread() {
	delete Thread;
	Thread = NULL;
}

AzureTTSThread* AzureTTSThread::setup(shared_ptr<SpeechConfig> config, FString Language, FString Voice, FString Key, FString Region, FString ssml, FString id)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new AzureTTSThread(config, Language, Voice, Key, Region, ssml, id);
	}
	return Runnable;
}

bool AzureTTSThread::Init()
{
	return true;
}

uint32 AzureTTSThread::Run()
{
	Synthesize();
	return 0;
}

void AzureTTSThread::Stop()
{
	StopTaskCounter.Increment();
}

void AzureTTSThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void AzureTTSThread::Shutdown()
{
	if (Runnable)
	{
		//Runnable->EnsureCompletion();
		//delete Runnable;
		Runnable = NULL;
	}
}

void AzureTTSThread::Synthesize()
{
	synthesizer = SpeechSynthesizer::FromConfig(TTSConfig, NULL);

	ssml = "<!--ID=B7267351-473F-409D-9765-754A8EBCDE05;Version=1|{\"VoiceNameToIdMapItems\":[{\"Id\":\"735db598 - 81e2 - 408f - b039 - f7afef686748\",\"Name\":\"Microsoft Server Speech Text to Speech Voice(" + Language + ", " + Voice + ")\",\"VoiceType\":\"StandardVoice\"}]}--><speak xmlns=\"http://www.w3.org/2001/10/synthesis\" xmlns:mstts=\"http://www.w3.org/2001/mstts\" xmlns:emo=\"http://www.w3.org/2009/10/emotionml\" version=\"1.0\" xml:lang=\"" + Language + "\"><voice name=\"Microsoft Server Speech Text to Speech Voice (" + Language + ", " + Voice + ")\">" + ssml + "</voice></speak>";

	auto result = synthesizer->SpeakSsmlAsync(std::string(TCHAR_TO_UTF8(*ssml))).get();

	if (result->Reason == ResultReason::SynthesizingAudioCompleted) {
		FTTSData newData;

		auto stream = AudioDataStream::FromResult(result);
		uint8_t buffer[1];

		while (stream->CanReadData(1)) {
			stream->ReadData(buffer, 1);
			newData.AudioData.Add((uint8)buffer[0]);
		}

		newData.ssml = ssml;
		
		TTSResultAvailable.Broadcast(newData, id);
		//Shutdown();
	}
	else if (result->Reason == ResultReason::Canceled)
	{
		auto cancellation = SpeechSynthesisCancellationDetails::FromResult(result);

		if (cancellation->Reason == CancellationReason::Error)
			FString  error= UTF8_TO_TCHAR(cancellation->ErrorDetails.c_str());
	}
}

FDelegateHandle AzureTTSThread::TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate)
{
	return TTSResultAvailable.Add(UseDelegate);
}

void AzureTTSThread::TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	TTSResultAvailable.Remove(DelegateHandle);
}