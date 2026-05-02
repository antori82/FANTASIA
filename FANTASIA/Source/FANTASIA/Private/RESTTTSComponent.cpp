/**
 * @file RESTTTSComponent.cpp
 * @brief Implementation of URESTTTSComponent -- generic REST-based TTS with streaming and Audio2Face.
 */

#include "RESTTTSComponent.h"
#include "Async/Async.h"

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
 * Launches the Audio2Face consumer async task. The task drains per-call
 * audio buffers in submission order (PlaybackOrder), batches samples, and
 * feeds them to ACE AnimateFromAudioSamples. Multiple TTSSynthesize calls
 * may issue HTTP requests in parallel -- their per-call buffers fill up
 * out of order, but this task plays them in call order, marking each
 * buffer's tail with bIsLastChunk=true so A2F closes each utterance
 * cleanly. Buffers are removed from BuffersByCaller and freed once
 * fully drained; PlaybackComplete fires for the caller's id at that point.
 */
void URESTTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	bIsPlaying.store(true);

#if FANTASIA_WITH_ACE
	// Use Async (not AsyncTask) so we get a future we can join on in EndPlay.
	// Without the join, component EndPlay returns while the consumer is still
	// in its 50 ms wake cycle; if BP EndPlay then deallocates ACE resources
	// immediately after (as the Alice/MetaFamily setup does), the consumer can
	// reach into half-torn-down ACE state via AnimateFromAudioSamples and
	// trigger a use-after-free in NVIDIA's DirectML DLL (nvdxgdmal64.dll).
	ConsumerTaskFuture = Async(EAsyncExecution::ThreadPool, [this]()
	{
		// Audio-realtime pacing: send exactly one BATCH_SIZE batch per
		// AnimateFromAudioSamples call and sleep its audio duration. Burst-
		// feeding huge batches makes ACE spawn overlapping audio outputs.
		constexpr int32 SampleRateHz = 16000;
		constexpr float BatchSeconds = float(A2F_STREAMING_BATCH_SIZE) / float(SampleRateHz);
		constexpr float PaceSleep = BatchSeconds * 0.95f;

		// outData persists across slot transitions: a slot's tail samples
		// stay buffered and combine with the next slot's head into a full
		// BATCH_SIZE batch. Keeps every send the same size so the pacing
		// sleep stays accurate.
		TArray<float> outData;
		outData.Reserve(A2F_STREAMING_BATCH_SIZE);

		auto SendOutData = [&](bool bIsLastChunk)
		{
			if (outData.Num() == 0) return;
			UACEAudioCurveSourceComponent* TypedA2F = Cast<UACEAudioCurveSourceComponent>(A2Fpointer);
			UAudio2FaceParameters* TypedParams = Cast<UAudio2FaceParameters>(A2FParameters);
			if (IsValid(TypedA2F))
			{
				FAudio2FaceEmotion AceEmotion = ConvertToACEEmotion(EmotionParameters);
				FACERuntimeModule::Get().AnimateFromAudioSamples(
					TypedA2F, outData, 1, SampleRateHz, bIsLastChunk,
					AceEmotion, TypedParams, A2FProvider);
			}
			outData.Empty();
			FPlatformProcess::Sleep(PaceSleep);
		};

		while (bIsPlaying.load(std::memory_order_relaxed))
		{
			ConsumerWakeEvent->Wait(50);
			ConsumerWakeEvent->Reset();

			// ── Cancellation path ──────────────────────────────────────
			if (bNeedsFlush.load(std::memory_order_acquire))
			{
				FPlaybackOrderEntry discard;
				while (PlaybackOrder.Dequeue(discard)) {}
				{
					FScopeLock Lock(&BuffersMutex);
					BuffersByCaller.Empty();
				}
				CurrentPlayback.Reset();
				outData.Empty();
				bNeedsFlush.store(false, std::memory_order_release);
				continue;
			}

			// ── Acquire next entry if idle ─────────────────────────────
			if (!CurrentPlayback.IsSet())
			{
				FPlaybackOrderEntry NextEntry;
				if (!PlaybackOrder.Dequeue(NextEntry))
				{
					// Nothing queued. If end-of-turn was signaled, send
					// the buffered tail with bIsLastChunk=true so ACE
					// finalizes the session and OnAnimationEnded fires
					// (BP unmutes Whisper). If the last batch landed on
					// a boundary and outData is empty, send one zeroed
					// sample just to carry the close flag.
					if (bTurnEndSignaled.load(std::memory_order_acquire))
					{
						if (outData.Num() > 0)
						{
							SendOutData(true);
						}
						else
						{
							UACEAudioCurveSourceComponent* TypedA2F = Cast<UACEAudioCurveSourceComponent>(A2Fpointer);
							UAudio2FaceParameters* TypedParams = Cast<UAudio2FaceParameters>(A2FParameters);
							if (IsValid(TypedA2F))
							{
								TArray<float> Tail;
								Tail.Add(0.0f);
								FAudio2FaceEmotion AceEmotion = ConvertToACEEmotion(EmotionParameters);
								FACERuntimeModule::Get().AnimateFromAudioSamples(
									TypedA2F, Tail, 1, SampleRateHz, /*bIsLastChunk=*/true,
									AceEmotion, TypedParams, A2FProvider);
							}
						}
						bTurnEndSignaled.store(false, std::memory_order_release);
					}
					continue;
				}
				CurrentPlayback = NextEntry;
			}

			FAudioBuffer* Target = CurrentPlayback->Buffer;
			if (!Target)
			{
				CurrentPlayback.Reset();
				ConsumerWakeEvent->Trigger();
				continue;
			}

			// ── Top up outData from current slot (up to BATCH_SIZE) ────
			bool bSlotFullyConsumed = false;
			{
				FScopeLock BufferLock(&Target->Mutex);
				const int32 NeedMore = A2F_STREAMING_BATCH_SIZE - outData.Num();
				const int32 Available = Target->Samples.Num() - Target->ConsumedSamples;
				const int32 ToTake = FMath::Min(NeedMore, Available);
				if (ToTake > 0)
				{
					outData.Append(Target->Samples.GetData() + Target->ConsumedSamples, ToTake);
					Target->ConsumedSamples += ToTake;
				}
				// Memory order matters: HandleResult sets bSynthesisComplete
				// AFTER its final append; acquire semantics here ensures we
				// see those last samples.
				const bool bComplete = Target->bSynthesisComplete.load(std::memory_order_acquire);
				const bool bFullyDrained = (Target->ConsumedSamples >= Target->Samples.Num());
				bSlotFullyConsumed = bComplete && bFullyDrained;
			}

			// ── Retire slot if consumed (carry outData into next slot) ─
			if (bSlotFullyConsumed)
			{
				const FString FinishedCallerId = CurrentPlayback->CallerId;
				FAudioBuffer* FinishedBuffer = CurrentPlayback->Buffer;

				{
					FScopeLock Lock(&BuffersMutex);
					if (TArray<TUniquePtr<FAudioBuffer>>* List = BuffersByCaller.Find(FinishedCallerId))
					{
						for (int32 i = 0; i < List->Num(); ++i)
						{
							if ((*List)[i].Get() == FinishedBuffer)
							{
								List->RemoveAt(i);
								break;
							}
						}
						if (List->Num() == 0)
						{
							BuffersByCaller.Remove(FinishedCallerId);
						}
					}
				}

				CurrentPlayback.Reset();
				AsyncTask(ENamedThreads::GameThread, [this, FinishedCallerId]()
				{
					PlaybackComplete.Broadcast(FinishedCallerId);
				});
				// Wake immediately so the next slot's samples flow
				// without the 50 ms Wait timeout.
				ConsumerWakeEvent->Trigger();
			}

			// ── Send if we have a full batch ───────────────────────────
			if (outData.Num() >= A2F_STREAMING_BATCH_SIZE)
			{
				SendOutData(false);
				if (CurrentPlayback.IsSet() || !PlaybackOrder.IsEmpty())
				{
					ConsumerWakeEvent->Trigger();
				}
			}
		}
	});
#endif // FANTASIA_WITH_ACE
}

void URESTTTSComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Signal the consumer task to exit, then wait for it to actually finish
	// BEFORE handing control back to UE. This matters because the enclosing
	// actor's BP EndPlay typically fires immediately after this one and, in
	// the Alice/MetaFamily flow, Blueprint deallocates the A2F provider on
	// EndPlay. If we don't join here, the consumer might still be mid-
	// AnimateFromAudioSamples when ACE starts tearing down GPU resources,
	// causing a use-after-free in NVIDIA's DirectML DLL (nvdxgdmal64.dll).
	bIsPlaying.store(false);
	ConsumerWakeEvent->Trigger();

#if FANTASIA_WITH_ACE
	if (ConsumerTaskFuture.IsValid())
	{
		ConsumerTaskFuture.Wait();
	}
#endif

	Super::EndPlay(EndPlayReason);
}


/**
 * Processes a complete HTTP response: WAV detection + resample, stash in
 * Buffer (for TTSGetSound retrieval by caller id), and -- in non-streaming
 * mode -- push the full audio into the per-call buffer. Marks synthesis
 * complete so the consumer task knows it can retire the buffer once drained.
 *
 * The buffer pointer was captured directly in the HTTP closure, so we
 * write to the right buffer even when many calls share the same caller id.
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

#if FANTASIA_WITH_ACE
	if (Target)
	{
		// Streaming mode: HandlePartialResult already pushed everything and
		// the OnProcessRequestComplete callback flushed the trailing bytes.
		// Here we just mark synthesis complete so the consumer can retire
		// the buffer once it's fully drained.
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
		ConsumerWakeEvent->Trigger();
	}
#endif // FANTASIA_WITH_ACE

	AsyncTask(ENamedThreads::GameThread, [this, id]()
	{
		SynthesisReady.Broadcast(id);
	});
}

/** Converts a streaming PCM chunk to float samples and appends them to
 *  the request's specific per-call buffer (captured by pointer in the
 *  HTTP closure -- never looked up by id). The consumer task drains
 *  buffers in submission order via PlaybackOrder. */
void URESTTTSComponent::HandlePartialResult(TArray<uint8> response, FString id, FAudioBuffer* Target)
{
	const int32 NumBytes = response.Num();
	if (NumBytes < 2) return;

#if FANTASIA_WITH_ACE
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
	}
	if (IsValid(A2Fpointer))
	{
		ConsumerWakeEvent->Trigger();
	}
#endif // FANTASIA_WITH_ACE

	AsyncTask(ENamedThreads::GameThread, [this, id]()
	{
		PartialSynthesisReady.Broadcast(id);
	});
}

/** Reserves a per-call audio buffer in submission order BEFORE issuing the
 *  HTTP request. The buffer is appended to the caller-id's list (so callers
 *  reusing the same id stack their buffers without collision); the global
 *  PlaybackOrder FIFO records the (caller id, buffer pointer) so the
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
	// The consumer only acts on the flag when the queue is empty AND a
	// slot is fully consumed -- and our new buffer guarantees the queue
	// is non-empty at this moment. So the close defers naturally to
	// THIS buffer's tail, with no race against earlier buffers.
	if (bEndTurn)
	{
		EndTurn();
	}
}

/** Signal that the current turn is over (without synthesizing more
 *  text). Common case is the bEndTurn parameter on TTSSynthesize; this
 *  standalone variant is for edge cases (e.g., closing the stream when
 *  the LLM produced no final sentence). Safe to call from the game
 *  thread. */
void URESTTTSComponent::EndTurn()
{
	bTurnEndSignaled.store(true, std::memory_order_release);
	ConsumerWakeEvent->Trigger();
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

	// Per-request streaming counters, shared between the progress and
	// completion lambdas. Used to live as member variables, but that was
	// a parallelism bug: a second TTSSynthesize starting would reset the
	// first request's counters, dropping or duplicating its trailing
	// bytes. Heap-shared via TSharedRef so both closures see the same
	// state with no contention from other in-flight requests.
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
