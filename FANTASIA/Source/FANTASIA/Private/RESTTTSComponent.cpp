#include "RESTTTSComponent.h"

URESTTTSComponent::URESTTTSComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void URESTTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	isPlaying.store(true);

	FTTSResultAvailableDelegate TTSResultSubscriber;
	FTTSPartialResultAvailableDelegate TTSPartialResultSubscriber;

	TTSResultSubscriber.BindUObject(this, &URESTTTSComponent::getResult);
	TTSPartialResultSubscriber.BindUObject(this, &URESTTTSComponent::getPartialResult);

	ThreadHandle = new RESTTTSThread();
	TTSResultAvailableHandle = ThreadHandle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
	TTSPartialResultAvailableHandle = ThreadHandle->TTSPartialResultAvailableSubscribeUser(TTSPartialResultSubscriber);

	AsyncTask(ENamedThreads::AnyHiPriThreadNormalTask, [this]()
	{
		TArray<float> outData;
		outData.Reserve(A2F_STREAMING_BATCH_SIZE);
		float item;

		while (isPlaying.load(std::memory_order_relaxed))
		{
			ConsumerWakeEvent->Wait(50);
			ConsumerWakeEvent->Reset();

			if (needsFlush.load(std::memory_order_acquire))
			{
				while (sendData.Dequeue(item)) {}
				outData.Empty();
				bufferOpen.store(false);
				needsFlush.store(false, std::memory_order_release);
				continue;
			}

			if (!sendData.IsEmpty())
				bufferOpen.store(true);

			if (usingStreamingBuffer.load(std::memory_order_acquire) && sendData.Dequeue(item))
			{
				outData.Add(item);

				while (outData.Num() < A2F_STREAMING_BATCH_SIZE && sendData.Dequeue(item))
				{
					outData.Add(item);
				}

				if (outData.Num() >= A2F_STREAMING_BATCH_SIZE)
				{
					FACERuntimeModule::Get().AnimateFromAudioSamples(
						A2Fpointer, outData, 1, 16000, false,
						EmotionParameters, A2FParameters, A2FProvider);
					outData.Empty();
				}
			}
			else if (!usingStreamingBuffer.load(std::memory_order_acquire) && bufferOpen.load())
			{
				while (sendData.Dequeue(item))
					outData.Add(item);
				FACERuntimeModule::Get().AnimateFromAudioSamples(
					A2Fpointer, outData, 1, 16000, true,
					EmotionParameters, A2FParameters, A2FProvider);
				outData.Empty();
				bufferOpen.store(false);
			}
		}
	});
}

void URESTTTSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	isPlaying.store(false);
	ConsumerWakeEvent->Trigger();

	if (ThreadHandle)
	{
		ThreadHandle->EnsureCompletion();
		delete ThreadHandle;
		ThreadHandle = nullptr;
	}
}

void URESTTTSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Acquire ensures all Buffer/id writes from the HTTP thread are visible
	if (bSynthesisResultReady.load(std::memory_order_acquire))
	{
		bSynthesisResultReady.store(false, std::memory_order_relaxed);
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady.Empty();
	}

	if (bPartialResultReady.load(std::memory_order_acquire))
	{
		bPartialResultReady.store(false, std::memory_order_relaxed);
		PartialSynthesisReady.Broadcast(idPartialSynthesisReady);
		idPartialSynthesisReady.Empty();
	}
}

void URESTTTSComponent::getResult(FTTSData response, FString id)
{
	if (IsValid(A2Fpointer) && usingStreamingBuffer.load())
	{
		usingStreamingBuffer.store(false);
		needsFlush.store(true, std::memory_order_release);
		ConsumerWakeEvent->Trigger();
	}

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
	idSynthesisReady = id;
	// Release ensures Buffer write is visible before game thread reads it via acquire in TickComponent
	bSynthesisResultReady.store(true, std::memory_order_release);
}

void URESTTTSComponent::getPartialResult(TArray<uint8> response, FString id)
{
	const int32 NumBytes = response.Num();
	if (NumBytes < 2) return;

	const uint8* RawData = response.GetData();
	for (int32 i = 0; i <= NumBytes - 2; i += 2)
	{
		sendData.Enqueue(static_cast<float>(*reinterpret_cast<const int16*>(RawData + i)) / 32768.0f);
	}

	if (IsValid(A2Fpointer) && !usingStreamingBuffer.load() && !bufferOpen.load())
	{
		usingStreamingBuffer.store(true);
		bufferOpen.store(true);
	}

	ConsumerWakeEvent->Trigger();

	idPartialSynthesisReady = id;
	bPartialResultReady.store(true, std::memory_order_release);
}

void URESTTTSComponent::TTSSynthesize(FString text, FString id)
{
	ThreadHandle->Synthesize(BuildSynthesisRequest(text, id));
}

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
