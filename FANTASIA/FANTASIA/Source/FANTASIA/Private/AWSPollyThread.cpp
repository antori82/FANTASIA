#include "AWSPollyThread.h"
#include "Internationalization/Regex.h"

using namespace std;
using namespace Aws::Auth;
using namespace Aws::Polly;

AWSPollyThread* AWSPollyThread::Runnable = NULL;

AWSPollyThread::AWSPollyThread(TTSVoiceType inVoiceType, FString inVoice, FString accessKey, FString secretAccessKey, FString inSsml, FString inID, bool getLipSync) : StopTaskCounter(0)
{
	voiceType = inVoiceType;
	Voice = inVoice;
	AccessKey = accessKey;
	SecretAccessKey = secretAccessKey;
	ssml = inSsml;
	id = inID;
	lipSync = getLipSync;
	Thread = FRunnableThread::Create(this, TEXT("AWSPollyThread"), 0, TPri_Normal);
}

AWSPollyThread::~AWSPollyThread() {
	delete Thread;
	Thread = NULL;
}

AWSPollyThread* AWSPollyThread::setup(TTSVoiceType inVoiceType, FString Voice, FString accessKey, FString secretAccessKey, FString ssml, FString id, bool getLipSync)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new AWSPollyThread(inVoiceType, Voice, accessKey, secretAccessKey, ssml, id, getLipSync);
	}
	return Runnable;
}

bool AWSPollyThread::Init()
{
	return true;
}

uint32 AWSPollyThread::Run()
{
	Synthesize();
	return 0;
}

void AWSPollyThread::Stop()
{
	StopTaskCounter.Increment();
}

void AWSPollyThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void AWSPollyThread::Shutdown()
{
	if (Runnable)
	{
		//Runnable->EnsureCompletion();
		//delete Runnable;
		Runnable = NULL;
	}
}

void AWSPollyThread::Synthesize()
{
	Aws::SDKOptions options;
	Aws::InitAPI(options);

	AWSCredentials credentials= AWSCredentials(Aws::String(TCHAR_TO_UTF8(*AccessKey)), Aws::String(TCHAR_TO_UTF8(*SecretAccessKey)));
	PollyClient client= PollyClient(credentials);
	Model::SynthesizeSpeechRequest speechRequest;

	speechRequest.SetText(Aws::String(TCHAR_TO_UTF8(*ssml)));
	speechRequest.SetVoiceId(Aws::Polly::Model::VoiceIdMapper::GetVoiceIdForName(Aws::String(TCHAR_TO_UTF8(*Voice))));
	speechRequest.SetOutputFormat(Aws::Polly::Model::OutputFormatMapper::GetOutputFormatForName("pcm"));
	speechRequest.SetTextType(Model::TextType::ssml);

	Model::SynthesizeSpeechOutcome speechOutcome = client.SynthesizeSpeech(speechRequest);

	if (speechOutcome.IsSuccess()) {
		FTTSData newData;

		auto result = &speechOutcome.GetResult().GetAudioStream();

		result->seekg(0, std::ios::beg);
		int begin = result->tellg();
		result->seekg(0, std::ios::end);
		int end = result->tellg();
		result->seekg(0, std::ios::beg);

		int size = end - begin;
		char* bytes = new char[size];
		result->read(bytes, size);

		for (int i = 0; i < size; i++)
			newData.AudioData.Add((uint8)bytes[i]);

		if (lipSync) {
			speechRequest.SetOutputFormat(Aws::Polly::Model::OutputFormatMapper::GetOutputFormatForName("json"));
			Aws::Vector <Aws::Polly::Model::SpeechMarkType> marktypes;
			marktypes.push_back(Aws::Polly::Model::SpeechMarkType::ssml);
			marktypes.push_back(Aws::Polly::Model::SpeechMarkType::viseme);
			speechRequest.SetSpeechMarkTypes(marktypes);

			speechOutcome = client.SynthesizeSpeech(speechRequest);

			if (speechOutcome.IsSuccess()) {
				auto result2 = &speechOutcome.GetResult().GetAudioStream();

				result2->seekg(0, std::ios::beg);
				begin = result2->tellg();
				result2->seekg(0, std::ios::end);
				end = result2->tellg();
				result2->seekg(0, std::ios::beg);

				size = end - begin;
				char* bytes2 = new char[size];
				result2->read(bytes2, size);

				FString serializedData = FString(bytes2);
				const FRegexPattern visemePattern(TEXT("\"time\":([0-9]*),\"type\":\"viseme\",\"value\":\"([a-zA-Z]*)\""));

				FRegexMatcher visemeMatcher(visemePattern, serializedData);

				while (visemeMatcher.FindNext()) {
					FTTSTimedStruct newStruct;

					newStruct.time = FCString::Atoi(*visemeMatcher.GetCaptureGroup(1));
					newStruct.data = visemeMatcher.GetCaptureGroup(2);
					newData.lipsync.Add(newStruct);
				}

				const FRegexPattern marksPattern = FRegexPattern("\"time\":([0-9]*),\"type\":\"ssml\",\"start\":[0-9]*,\"end\":[0-9]*,\"value\":\"([0-9A-Za-z]*)\"");
				FRegexMatcher marksMatcher(marksPattern, serializedData);

				while (marksMatcher.FindNext())
				{
					FTTSTimedStruct newStruct;

					newStruct.time = FCString::Atoi(*visemeMatcher.GetCaptureGroup(1));
					newStruct.data = marksMatcher.GetCaptureGroup(2);
					newData.notifies.Add(newStruct);
				}
			}
		}

		newData.ssml = ssml;
		TTSResultAvailable.Broadcast(newData, id);
	}

	Aws::ShutdownAPI(options);
}

FDelegateHandle AWSPollyThread::TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate)
{
	return TTSResultAvailable.Add(UseDelegate);
}

void AWSPollyThread::TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	TTSResultAvailable.Remove(DelegateHandle);
}



