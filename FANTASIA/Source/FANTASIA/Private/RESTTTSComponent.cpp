/**
 * @file RESTTTSComponent.cpp
 * @brief Implementation of URESTTTSComponent -- generic REST-based TTS with streaming and Audio2Face.
 */

#include "RESTTTSComponent.h"

#if FANTASIA_WITH_ACE
#include "ACERuntimeModule.h"
#include "ACEAudioCurveSourceComponent.h"
#include "Audio2FaceParameters.h" // UAudio2FaceParameters
#include "ACETypes.h" // FAudio2FaceEmotion / FAudio2FaceEmotionOverride

/**
 * Copy FANTASIA's mirror emotion struct into ACE's real FAudio2FaceEmotion
 * field-for-field. Kept in one place so adding a new field to ACE's struct
 * (and our mirror) is a single-site change.
 */
static FAudio2FaceEmotion ConvertToACEEmotion(const FFantasiaAudio2FaceEmotion& Src)
{
	FAudio2FaceEmotion Dst;
	Dst.OverallEmotionStrength    = Src.OverallEmotionStrength;
	Dst.DetectedEmotionContrast   = Src.DetectedEmotionContrast;
	Dst.MaxDetectedEmotions       = Src.MaxDetectedEmotions;
	Dst.DetectedEmotionSmoothing  = Src.DetectedEmotionSmoothing;
	Dst.bEnableEmotionOverride    = Src.bEnableEmotionOverride;
	Dst.EmotionOverrideStrength   = Src.EmotionOverrideStrength;

	Dst.EmotionOverrides.bOverrideAmazement    = Src.EmotionOverrides.bOverrideAmazement;
	Dst.EmotionOverrides.Amazement             = Src.EmotionOverrides.Amazement;
	Dst.EmotionOverrides.bOverrideAnger        = Src.EmotionOverrides.bOverrideAnger;
	Dst.EmotionOverrides.Anger                 = Src.EmotionOverrides.Anger;
	Dst.EmotionOverrides.bOverrideCheekiness   = Src.EmotionOverrides.bOverrideCheekiness;
	Dst.EmotionOverrides.Cheekiness            = Src.EmotionOverrides.Cheekiness;
	Dst.EmotionOverrides.bOverrideDisgust      = Src.EmotionOverrides.bOverrideDisgust;
	Dst.EmotionOverrides.Disgust               = Src.EmotionOverrides.Disgust;
	Dst.EmotionOverrides.bOverrideFear         = Src.EmotionOverrides.bOverrideFear;
	Dst.EmotionOverrides.Fear                  = Src.EmotionOverrides.Fear;
	Dst.EmotionOverrides.bOverrideGrief        = Src.EmotionOverrides.bOverrideGrief;
	Dst.EmotionOverrides.Grief                 = Src.EmotionOverrides.Grief;
	Dst.EmotionOverrides.bOverrideJoy          = Src.EmotionOverrides.bOverrideJoy;
	Dst.EmotionOverrides.Joy                   = Src.EmotionOverrides.Joy;
	Dst.EmotionOverrides.bOverrideOutOfBreath  = Src.EmotionOverrides.bOverrideOutOfBreath;
	Dst.EmotionOverrides.OutOfBreath           = Src.EmotionOverrides.OutOfBreath;
	Dst.EmotionOverrides.bOverridePain         = Src.EmotionOverrides.bOverridePain;
	Dst.EmotionOverrides.Pain                  = Src.EmotionOverrides.Pain;
	Dst.EmotionOverrides.bOverrideSadness      = Src.EmotionOverrides.bOverrideSadness;
	Dst.EmotionOverrides.Sadness               = Src.EmotionOverrides.Sadness;
	return Dst;
}
#endif // FANTASIA_WITH_ACE

URESTTTSComponent::URESTTTSComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

/**
 * Launches the Audio2Face consumer async task that batches float samples from
 * SendData and feeds them to ACE AnimateFromAudioSamples.
 */
void URESTTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	bIsPlaying.store(true);

#if FANTASIA_WITH_ACE
	AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this]()
	{
		TArray<float> outData;
		outData.Reserve(A2F_STREAMING_BATCH_SIZE);
		float item;

		while (bIsPlaying.load(std::memory_order_relaxed))
		{
			ConsumerWakeEvent->Wait(50);
			ConsumerWakeEvent->Reset();

			if (bNeedsFlush.load(std::memory_order_acquire))
			{
				while (SendData.Dequeue(item)) {}
				outData.Empty();
				bBufferOpen.store(false);
				bNeedsFlush.store(false, std::memory_order_release);
				continue;
			}

			if (!SendData.IsEmpty())
				bBufferOpen.store(true);

			if (bUsingStreamingBuffer.load(std::memory_order_acquire) && SendData.Dequeue(item))
			{
				outData.Add(item);

				while (outData.Num() < A2F_STREAMING_BATCH_SIZE && SendData.Dequeue(item))
				{
					outData.Add(item);
				}

				if (outData.Num() >= A2F_STREAMING_BATCH_SIZE)
				{
					UACEAudioCurveSourceComponent* TypedA2F = Cast<UACEAudioCurveSourceComponent>(A2Fpointer);
					UAudio2FaceParameters* TypedParams = Cast<UAudio2FaceParameters>(A2FParameters);
					if (IsValid(TypedA2F))
					{
						FAudio2FaceEmotion AceEmotion = ConvertToACEEmotion(EmotionParameters);
						FACERuntimeModule::Get().AnimateFromAudioSamples(
							TypedA2F, outData, 1, 16000, false,
							AceEmotion, TypedParams, A2FProvider);
					}
					outData.Empty();
				}
			}
			else if (!bUsingStreamingBuffer.load(std::memory_order_acquire) && bBufferOpen.load())
			{
				while (SendData.Dequeue(item))
					outData.Add(item);
				UACEAudioCurveSourceComponent* TypedA2F = Cast<UACEAudioCurveSourceComponent>(A2Fpointer);
				UAudio2FaceParameters* TypedParams = Cast<UAudio2FaceParameters>(A2FParameters);
				if (IsValid(TypedA2F))
				{
					FAudio2FaceEmotion AceEmotion = ConvertToACEEmotion(EmotionParameters);
					FACERuntimeModule::Get().AnimateFromAudioSamples(
						TypedA2F, outData, 1, 16000, true,
						AceEmotion, TypedParams, A2FProvider);
				}
				outData.Empty();
				bBufferOpen.store(false);
			}
		}
	});
#endif // FANTASIA_WITH_ACE
}

void URESTTTSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	bIsPlaying.store(false);
	ConsumerWakeEvent->Trigger();
}


/**
 * Processes a complete HTTP response: flushes streaming state, calls ProcessResponse
 * for subclass metadata extraction, auto-detects WAV headers, resamples to 16 kHz,
 * and stores the result in the thread-safe Buffer.
 */
void URESTTTSComponent::HandleResult(FTTSData response, FString id)
{
#if FANTASIA_WITH_ACE
	// End of the streaming TTS response. Flip bUsingStreamingBuffer to false so
	// the consumer task's drain branch runs on its next wake: it will pull the
	// remaining samples from SendData and call AnimateFromAudioSamples with
	// final=true. We deliberately do NOT trigger bNeedsFlush here — that path
	// discards queued samples and is reserved for explicit cancellation. For
	// short responses (e.g. ElevenLabs finishing in ~60 ms), most of the audio
	// can still be in-flight in SendData at this point; triggering bNeedsFlush
	// would throw it away and only the already-dequeued batch would reach A2F.
	if (IsValid(A2Fpointer) && bUsingStreamingBuffer.load())
	{
		bUsingStreamingBuffer.store(false);
		ConsumerWakeEvent->Trigger();
	}
#endif // FANTASIA_WITH_ACE

	// Let subclasses extract timing/lipsync from the raw response BEFORE we modify AudioData.
	// This avoids copying AudioData into a separate RawResponse array.
	ProcessResponse(response.AudioData, response);

	// WAV auto-detection and resampling
	int32 WavSampleRate = 0;
	int32 WavChannels = 0;
	int32 WavBitsPerSample = 0;
	int32 DataOffset = 0;

	if (TryParseWavHeader(response.AudioData, WavSampleRate, WavChannels, WavBitsPerSample, DataOffset))
	{
		if (WavSampleRate != 16000)
		{
			// Resample directly from the data portion (skip header), produces a new array
			response.AudioData = ResampleTo16kHz(response.AudioData.GetData() + DataOffset,
				response.AudioData.Num() - DataOffset, WavSampleRate, WavChannels);
		}
		else
		{
			// Strip WAV header in-place: shift data down, no allocation
			response.AudioData.RemoveAt(0, DataOffset, EAllowShrinking::No);
		}
	}
	else if (SampleRate != 16000)
	{
		response.AudioData = ResampleTo16kHz(response.AudioData.GetData(),
			response.AudioData.Num(), SampleRate, 1);
	}

	{
		FScopeLock Lock(&BufferMutex);
		Buffer.FindOrAdd(id) = MoveTemp(response);
	}

	AsyncTask(ENamedThreads::GameThread, [this, id]()
	{
		SynthesisReady.Broadcast(id);
	});
}

/** Converts a streaming PCM chunk to float samples and enqueues them for Audio2Face. */
void URESTTTSComponent::HandlePartialResult(TArray<uint8> response, FString id)
{
	const int32 NumBytes = response.Num();
	if (NumBytes < 2) return;

	const uint8* RawData = response.GetData();
	for (int32 i = 0; i <= NumBytes - 2; i += 2)
	{
		SendData.Enqueue(static_cast<float>(*reinterpret_cast<const int16*>(RawData + i)) / 32768.0f);
	}

#if FANTASIA_WITH_ACE
	if (IsValid(A2Fpointer) && !bUsingStreamingBuffer.load() && !bBufferOpen.load())
	{
		bUsingStreamingBuffer.store(true);
		bBufferOpen.store(true);
	}
#endif // FANTASIA_WITH_ACE

	ConsumerWakeEvent->Trigger();

	AsyncTask(ENamedThreads::GameThread, [this, id]()
	{
		PartialSynthesisReady.Broadcast(id);
	});
}

void URESTTTSComponent::TTSSynthesize(FString text, FString id)
{
	IssueHttpRequest(BuildSynthesisRequest(text, id));
}

/**
 * Creates and sends an HTTP request from the given descriptor. Sets up streaming
 * progress callbacks (if bStreaming) and the completion callback that invokes
 * HandleResult / HandlePartialResult.
 */
void URESTTTSComponent::IssueHttpRequest(FTTSSynthesisRequest Request)
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(Request.URL);

	if (Request.Body.IsEmpty())
	{
		HttpRequest->SetVerb("GET");
	}
	else
	{
		HttpRequest->SetVerb("POST");
		HttpRequest->SetContentAsString(Request.Body);
	}

	for (const auto& Header : Request.Headers)
	{
		HttpRequest->SetHeader(Header.Key, Header.Value);
	}

	const FString RequestID = Request.ID;
	const FString RequestText = Request.OriginalText;
	const bool bIsStreaming = Request.bStreaming;

	PreviousBytes = 0;
	StreamingNum = 0;

	if (bIsStreaming)
	{
		HttpRequest->OnRequestProgress64().BindLambda([this, RequestID](FHttpRequestPtr Req, int64 BytesSent, int64 BytesReceived)
		{
			if (BytesReceived > 0 && PreviousBytes < BytesReceived && Req->GetResponse().IsValid())
			{
				const TArray<uint8>& Content = Req->GetResponse()->GetContent();
				const int64 len = Content.Num();

				if (StreamingNum < len)
				{
					const int64 Available = len - StreamingNum;
					const int64 Aligned = Available - (Available & 1);

					TArray<uint8> SynthResult(&Content[StreamingNum], Aligned);
					StreamingNum += Aligned;
					PreviousBytes = BytesReceived;
					HandlePartialResult(SynthResult, RequestID);
				}
			}
		});
	}

	HttpRequest->OnProcessRequestComplete().BindLambda([this, RequestID, RequestText, bIsStreaming](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			const TArray<uint8>& Content = Response->GetContent();

			if (bIsStreaming && Content.Num() > StreamingNum)
			{
				TArray<uint8> Remaining(&Content[StreamingNum], Content.Num() - StreamingNum);
				PreviousBytes = 0;
				StreamingNum = 0;
				HandlePartialResult(Remaining, RequestID);
			}

			FTTSData SynthResult;
			SynthResult.AudioData = Content;
			SynthResult.ssml = RequestText;
			HandleResult(SynthResult, RequestID);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Connection to the TTS endpoint failed."));
		}
	});

	HttpRequest->ProcessRequest();
}

/**
 * Base implementation: uses URL/Headers/BodyTemplate properties.
 * GET mode if BodyTemplate is empty (text is URL-encoded in URL), POST otherwise.
 * JSON-escapes the text before substituting into BodyTemplate.
 */
FTTSSynthesisRequest URESTTTSComponent::BuildSynthesisRequest(const FString& Text, const FString& ID)
{
	FTTSSynthesisRequest Request;
	Request.ID = ID;
	Request.OriginalText = Text;
	Request.bStreaming = bStreaming;
	Request.Headers = Headers;

	if (BodyTemplate.IsEmpty())
	{
		// GET mode: URL-encode {text} in URL
		Request.URL = URL.Replace(TEXT("{text}"), *FGenericPlatformHttp::UrlEncode(Text));
	}
	else
	{
		Request.URL = URL;
		// Single-pass JSON escape instead of 5 separate Replace scans
		FString EscapedText;
		EscapedText.Reserve(Text.Len() + 16);
		for (const TCHAR Ch : Text)
		{
			switch (Ch)
			{
			case TEXT('\\'): EscapedText += TEXT("\\\\"); break;
			case TEXT('"'):  EscapedText += TEXT("\\\""); break;
			case TEXT('\n'): EscapedText += TEXT("\\n");  break;
			case TEXT('\r'): EscapedText += TEXT("\\r");  break;
			case TEXT('\t'): EscapedText += TEXT("\\t");  break;
			default:         EscapedText += Ch;           break;
			}
		}
		Request.Body = BodyTemplate.Replace(TEXT("{text}"), *EscapedText);
	}

	return Request;
}

void URESTTTSComponent::ProcessResponse(const TArray<uint8>& RawResponse, FTTSData& OutResult)
{
	// Base implementation: no additional processing
}

/** Creates a procedural SoundWave from buffered 16 kHz mono PCM data (thread-safe). */
USoundWaveProcedural* URESTTTSComponent::TTSGetSound(FString id)
{
	constexpr float OutputSamplingRate = 16000.f;

	TArray<uint8> AudioCopy;
	{
		FScopeLock Lock(&BufferMutex);
		const FTTSData* Found = Buffer.Find(id);
		if (!Found) return nullptr;
		AudioCopy = Found->AudioData;
	}

	USoundWaveProcedural* SyntheticVoice = NewObject<USoundWaveProcedural>();
	SyntheticVoice->SetSampleRate(OutputSamplingRate);
	SyntheticVoice->NumChannels = 1;
	SyntheticVoice->RawPCMDataSize = AudioCopy.Num();
	SyntheticVoice->Duration = static_cast<float>(AudioCopy.Num()) / (2.f * OutputSamplingRate);
	SyntheticVoice->QueueAudio(AudioCopy.GetData(), AudioCopy.Num());

	return SyntheticVoice;
}

TArray<uint8> URESTTTSComponent::TTSGetRawSound(FString id)
{
	FScopeLock Lock(&BufferMutex);
	const FTTSData* Found = Buffer.Find(id);
	return Found ? Found->AudioData : TArray<uint8>();
}

/**
 * Checks for RIFF/WAVE magic, parses fmt chunk fields, then walks sub-chunks
 * to locate the "data" chunk offset. Falls back to standard 44-byte offset.
 */
bool URESTTTSComponent::TryParseWavHeader(const TArray<uint8>& Data, int32& OutSampleRate, int32& OutNumChannels, int32& OutBitsPerSample, int32& OutDataOffset)
{
	if (Data.Num() < 44)
		return false;

	const uint8* Raw = Data.GetData();

	// Check RIFF + WAVE magic via 32-bit comparisons
	if (*reinterpret_cast<const uint32*>(Raw) != 0x46464952)      // "RIFF" little-endian
		return false;
	if (*reinterpret_cast<const uint32*>(Raw + 8) != 0x45564157)  // "WAVE" little-endian
		return false;

	// Parse fmt chunk fields (standard PCM WAV layout)
	OutNumChannels = *reinterpret_cast<const uint16*>(Raw + 22);
	OutSampleRate = *reinterpret_cast<const int32*>(Raw + 24);
	OutBitsPerSample = *reinterpret_cast<const uint16*>(Raw + 34);

	// Walk chunks starting after "WAVE" (offset 12) to find "data" subchunk.
	// Each chunk: 4-byte ID + 4-byte size + size bytes of payload.
	const int32 TotalSize = Data.Num();
	int32 Pos = 12;
	while (Pos + 8 <= TotalSize)
	{
		const uint32 ChunkID = *reinterpret_cast<const uint32*>(Raw + Pos);
		const int32 ChunkSize = *reinterpret_cast<const int32*>(Raw + Pos + 4);

		if (ChunkID == 0x61746164) // "data" little-endian
		{
			OutDataOffset = Pos + 8;
			return true;
		}

		// Advance to next chunk (chunk sizes are word-aligned in WAV)
		Pos += 8 + ((ChunkSize + 1) & ~1);
	}

	// Fallback: standard 44-byte header
	OutDataOffset = 44;
	return true;
}

/**
 * Resamples multi-channel 16-bit PCM to mono 16 kHz using linear interpolation.
 * Takes the first channel only if input is multi-channel.
 */
TArray<uint8> URESTTTSComponent::ResampleTo16kHz(const uint8* PCMData, int32 NumBytes, int32 SourceRate, int32 NumChannels)
{
	constexpr int32 BytesPerSample = 2; // 16-bit PCM
	const int32 FrameSize = BytesPerSample * NumChannels;
	const int32 NumSourceFrames = NumBytes / FrameSize;

	if (NumSourceFrames < 2)
	{
		return TArray<uint8>(PCMData, NumBytes);
	}

	const int32 NumOutputFrames = FMath::Max(1, static_cast<int32>(static_cast<int64>(NumSourceFrames) * 16000 / SourceRate));
	TArray<uint8> Output;
	Output.SetNumUninitialized(NumOutputFrames * BytesPerSample); // mono 16-bit output

	const int16* SourceSamples = reinterpret_cast<const int16*>(PCMData);
	int16* OutputSamples = reinterpret_cast<int16*>(Output.GetData());

	const float Ratio = static_cast<float>(NumSourceFrames - 1) / static_cast<float>(FMath::Max(1, NumOutputFrames - 1));

	for (int32 i = 0; i < NumOutputFrames; ++i)
	{
		const float SrcPos = i * Ratio;
		const int32 Idx0 = static_cast<int32>(SrcPos);
		const int32 Idx1 = FMath::Min(Idx0 + 1, NumSourceFrames - 1);
		const float Frac = SrcPos - Idx0;

		const int16 S0 = SourceSamples[Idx0 * NumChannels];
		const int16 S1 = SourceSamples[Idx1 * NumChannels];

		OutputSamples[i] = static_cast<int16>(S0 + (S1 - S0) * Frac);
	}

	return Output;
}
