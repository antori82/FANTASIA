/**
 * @file RESTTTSComponent.cpp
 * @brief Implementation of URESTTTSComponent -- generic REST-based TTS.
 *
 * No NVIDIA ACE / Audio2Face code here — that lives in the
 * FANTASIAACE plugin's UACERESTTTSComponent subclass.
 */

#include "RESTTTSComponent.h"
#include "Async/Async.h"

URESTTTSComponent::URESTTTSComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URESTTTSComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URESTTTSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


/**
 * Processes a complete HTTP response: WAV detection + resample, stash in
 * Buffer (for TTSGetSound retrieval by caller id), push the full audio
 * into the per-call buffer in non-streaming mode, mark synthesis
 * complete, and wake any subclass-installed consumer.
 *
 * The buffer pointer is captured directly in the HTTP closure, so writes
 * go to the right buffer even when many calls share the same caller id.
 */
void URESTTTSComponent::HandleResult(FTTSData response, FString id, FAudioBuffer* Target)
{
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
		Buffer.FindOrAdd(id) = response;  // copy: we still need response.AudioData below.
		// NOTE: when callers reuse the same id across calls, FindOrAdd
		// overwrites; the most recent synthesis wins for TTSGetSound(id).
		// This matches the pre-existing behavior.
	}

	if (Target)
	{
		// Streaming mode: HandlePartialResult already pushed everything and
		// the OnProcessRequestComplete callback flushed the trailing bytes.
		// Here we just mark synthesis complete so a subclass consumer can
		// retire the buffer once it's fully drained.
		// Non-streaming mode: HandlePartialResult was never called; push
		// the full PCM here, then mark complete.
		if (!bStreaming)
		{
			const int32 NumSamples = response.AudioData.Num() / 2;
			if (NumSamples > 0)
			{
				const uint8* RawData = response.AudioData.GetData();
				FScopeLock BufferLock(&Target->Mutex);
				Target->Samples.Reserve(Target->Samples.Num() + NumSamples);
				for (int32 i = 0; i < NumSamples; ++i)
				{
					Target->Samples.Add(static_cast<float>(*reinterpret_cast<const int16*>(RawData + i*2)) / 32768.0f);
				}
			}
		}
		// Release-store: pairs with the consumer's acquire-load so any
		// samples appended above (or by HandlePartialResult earlier) are
		// visible before the consumer treats this buffer as final.
		Target->bSynthesisComplete.store(true, std::memory_order_release);
		WakeConsumer();
	}

	AsyncTask(ENamedThreads::GameThread, [this, id]()
	{
		SynthesisReady.Broadcast(id);
	});
}

/** Converts a streaming PCM chunk to float samples and appends them to
 *  the request's specific per-call buffer (captured by pointer in the
 *  HTTP closure -- never looked up by id). A subclass consumer drains
 *  buffers in submission order via PlaybackOrder. */
void URESTTTSComponent::HandlePartialResult(TArray<uint8> response, FString id, FAudioBuffer* Target)
{
	const int32 NumBytes = response.Num();
	if (NumBytes < 2) return;

	if (Target)
	{
		const int32 NumSamples = NumBytes / 2;
		const uint8* RawData = response.GetData();
		FScopeLock BufferLock(&Target->Mutex);
		Target->Samples.Reserve(Target->Samples.Num() + NumSamples);
		for (int32 i = 0; i < NumSamples; ++i)
		{
			Target->Samples.Add(static_cast<float>(*reinterpret_cast<const int16*>(RawData + i*2)) / 32768.0f);
		}
		WakeConsumer();
	}

	AsyncTask(ENamedThreads::GameThread, [this, id]()
	{
		PartialSynthesisReady.Broadcast(id);
	});
}

/** Reserves a per-call audio buffer in submission order BEFORE issuing the
 *  HTTP request. The buffer is appended to the caller-id's list (so callers
 *  reusing the same id stack their buffers without collision); the global
 *  PlaybackOrder FIFO records the (caller id, buffer pointer) so a subclass
 *  consumer plays them in TTSSynthesize call order regardless of when each
 *  HTTP completes. The buffer pointer is captured directly in the HTTP
 *  closure -- no by-id lookup that could race. */
void URESTTTSComponent::TTSSynthesize(FString text, FString id, bool bEndTurn)
{
	auto NewBuffer = MakeUnique<FAudioBuffer>();
	FAudioBuffer* RawPtr = NewBuffer.Get();

	{
		FScopeLock Lock(&BuffersMutex);
		BuffersByCaller.FindOrAdd(id).Add(MoveTemp(NewBuffer));
	}
	PlaybackOrder.Enqueue({id, RawPtr});

	IssueHttpRequest(BuildSynthesisRequest(text, id), RawPtr);

	// Set the close-stream flag AFTER the buffer is in PlaybackOrder.
	// A subclass consumer only acts on the flag when the queue is empty
	// AND a slot is fully consumed -- and our new buffer guarantees the
	// queue is non-empty at this moment. So the close defers naturally
	// to THIS buffer's tail, with no race against earlier buffers.
	if (bEndTurn)
	{
		EndTurn();
	}
}

/** Default no-op. UACERESTTTSComponent overrides to set bTurnEndSignaled
 *  and trigger its consumer wake event. */
void URESTTTSComponent::EndTurn()
{
}

/**
 * Creates and sends an HTTP request from the given descriptor. Sets up streaming
 * progress callbacks (if bStreaming) and the completion callback that invokes
 * HandleResult / HandlePartialResult.
 *
 * `Target` is the per-call audio buffer captured in both lambda closures so
 * partial chunks and the final response always land in the right buffer,
 * even when several requests with the same caller id run in parallel.
 */
void URESTTTSComponent::IssueHttpRequest(FTTSSynthesisRequest Request, FAudioBuffer* Target)
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

	// Per-request streaming counters, heap-shared via TSharedRef between
	// the progress and completion lambdas so each request gets its own
	// pair of counters. Sharing through member variables would let a
	// second TTSSynthesize call reset the first request's counters and
	// drop or duplicate its trailing bytes.
	TSharedRef<int64> StreamingNumPtr = MakeShared<int64>(0);
	TSharedRef<int64> PreviousBytesPtr = MakeShared<int64>(0);

	if (bIsStreaming)
	{
		HttpRequest->OnRequestProgress64().BindLambda(
			[this, RequestID, Target, StreamingNumPtr, PreviousBytesPtr]
			(FHttpRequestPtr Req, int64 BytesSent, int64 BytesReceived)
		{
			if (BytesReceived > 0 && *PreviousBytesPtr < BytesReceived && Req->GetResponse().IsValid())
			{
				const TArray<uint8>& Content = Req->GetResponse()->GetContent();
				const int64 len = Content.Num();

				if (*StreamingNumPtr < len)
				{
					const int64 Available = len - *StreamingNumPtr;
					const int64 Aligned = Available - (Available & 1);

					TArray<uint8> SynthResult(&Content[*StreamingNumPtr], Aligned);
					*StreamingNumPtr += Aligned;
					*PreviousBytesPtr = BytesReceived;
					HandlePartialResult(SynthResult, RequestID, Target);
				}
			}
		});
	}

	HttpRequest->OnProcessRequestComplete().BindLambda(
		[this, RequestID, RequestText, bIsStreaming, Target, StreamingNumPtr]
		(FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			const TArray<uint8>& Content = Response->GetContent();

			if (bIsStreaming && Content.Num() > *StreamingNumPtr)
			{
				TArray<uint8> Remaining(&Content[*StreamingNumPtr], Content.Num() - *StreamingNumPtr);
				HandlePartialResult(Remaining, RequestID, Target);
			}

			FTTSData SynthResult;
			SynthResult.AudioData = Content;
			SynthResult.ssml = RequestText;
			HandleResult(SynthResult, RequestID, Target);
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
