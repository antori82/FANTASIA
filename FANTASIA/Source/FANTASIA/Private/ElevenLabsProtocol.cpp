/**
 * @file ElevenLabsProtocol.cpp
 * @brief Implementation of FElevenLabsProtocol -- ElevenLabs request + alignment decode.
 */

#include "ElevenLabsProtocol.h"
#include "Misc/Base64.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace
{
	constexpr int32 ElevenLabsSampleRate = 16000;

	/** UTF-8 bytes [Start, Start+Len) -> FString (null-terminates a local copy). */
	FString Utf8ToString(const uint8* Data, int32 Len)
	{
		if (Len <= 0)
		{
			return FString();
		}
		TArray<uint8> Buf;
		Buf.Append(Data, Len);
		Buf.Add(0);
		return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(Buf.GetData())));
	}

	/** Decode base64 pcm_16000 audio and append it as floats to Target->Samples.
	 *  Caller must hold Target->Mutex. Returns the number of samples added. */
	int32 AppendAudioFromBase64(const FString& AudioBase64, FAudioBuffer* Target)
	{
		if (AudioBase64.IsEmpty())
		{
			return 0;
		}
		TArray<uint8> Pcm;
		if (!FBase64::Decode(AudioBase64, Pcm))
		{
			return 0;
		}
		const int32 NumSamples = Pcm.Num() / 2;
		const uint8* Raw = Pcm.GetData();
		Target->Samples.Reserve(Target->Samples.Num() + NumSamples);
		for (int32 i = 0; i < NumSamples; ++i)
		{
			Target->Samples.Add(static_cast<float>(*reinterpret_cast<const int16*>(Raw + i * 2)) / 32768.0f);
		}
		return NumSamples;
	}

	/** Last character_end_times_seconds value in an alignment object, or 0. */
	float AlignmentMaxEnd(const TSharedPtr<FJsonObject>& Alignment)
	{
		const TArray<TSharedPtr<FJsonValue>>* Ends = nullptr;
		if (Alignment.IsValid() && Alignment->TryGetArrayField(TEXT("character_end_times_seconds"), Ends) && Ends->Num() > 0)
		{
			return static_cast<float>((*Ends).Last()->AsNumber());
		}
		return 0.f;
	}

	/** Append the characters of an alignment object to OutChars, adding
	 *  TimeOffset to each time and BaseCharIndex to each char index. */
	void AppendCharsFromAlignment(const TSharedPtr<FJsonObject>& Alignment, float TimeOffset,
		int32 BaseCharIndex, TArray<FTTSSegmentTiming>& OutChars)
	{
		if (!Alignment.IsValid())
		{
			return;
		}
		const TArray<TSharedPtr<FJsonValue>>* Chars = nullptr;
		const TArray<TSharedPtr<FJsonValue>>* Starts = nullptr;
		const TArray<TSharedPtr<FJsonValue>>* Ends = nullptr;
		if (!Alignment->TryGetArrayField(TEXT("characters"), Chars))
		{
			return;
		}
		Alignment->TryGetArrayField(TEXT("character_start_times_seconds"), Starts);
		Alignment->TryGetArrayField(TEXT("character_end_times_seconds"), Ends);

		const int32 N = Chars->Num();
		OutChars.Reserve(OutChars.Num() + N);
		for (int32 i = 0; i < N; ++i)
		{
			FTTSSegmentTiming Seg;
			Seg.Text = (*Chars)[i]->AsString();
			Seg.StartSeconds = (Starts && Starts->IsValidIndex(i)) ? static_cast<float>((*Starts)[i]->AsNumber()) + TimeOffset : TimeOffset;
			Seg.EndSeconds = (Ends && Ends->IsValidIndex(i)) ? static_cast<float>((*Ends)[i]->AsNumber()) + TimeOffset : Seg.StartSeconds;
			Seg.CharStart = BaseCharIndex + i;
			Seg.CharEnd = BaseCharIndex + i + 1;
			OutChars.Add(MoveTemp(Seg));
		}
	}

	/**
	 * Streaming decoder for ElevenLabs /stream/with-timestamps: newline-delimited
	 * JSON objects, each carrying base64 audio + (optional) character alignment.
	 * Buffers partial lines across Feed calls and re-derives the word list from
	 * the accumulated characters so word boundaries stay correct across chunks.
	 */
	struct FElevenLabsStreamDecoder final : public FTTSStreamDecoder
	{
		virtual void Feed(TArrayView<const uint8> NewBytes, FAudioBuffer* Target) override
		{
			if (!Target || NewBytes.Num() == 0)
			{
				return;
			}
			LineBuffer.Append(NewBytes.GetData(), NewBytes.Num());

			int32 LineStart = 0;
			for (int32 i = 0; i < LineBuffer.Num(); ++i)
			{
				if (LineBuffer[i] == '\n')
				{
					ProcessLine(Utf8ToString(LineBuffer.GetData() + LineStart, i - LineStart), Target);
					LineStart = i + 1;
				}
			}
			if (LineStart > 0)
			{
				LineBuffer.RemoveAt(0, LineStart, EAllowShrinking::No);
			}
		}

		virtual void Finish(FAudioBuffer* Target) override
		{
			// Flush a trailing object that wasn't newline-terminated.
			if (Target && LineBuffer.Num() > 0)
			{
				ProcessLine(Utf8ToString(LineBuffer.GetData(), LineBuffer.Num()), Target);
				LineBuffer.Reset();
			}
		}

	private:
		void ProcessLine(const FString& Line, FAudioBuffer* Target)
		{
			const FString Trimmed = Line.TrimStartAndEnd();
			if (Trimmed.IsEmpty())
			{
				return;
			}

			TSharedPtr<FJsonObject> Root;
			const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Trimmed);
			if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
			{
				return;
			}

			FString AudioB64;
			Root->TryGetStringField(TEXT("audio_base64"), AudioB64);

			TSharedPtr<FJsonObject> Alignment;
			const TSharedPtr<FJsonObject>* AlignmentPtr = nullptr;
			if (Root->TryGetObjectField(TEXT("alignment"), AlignmentPtr) && AlignmentPtr)
			{
				Alignment = *AlignmentPtr;
			}

			FScopeLock BufferLock(&Target->Mutex);

			const int32 AddedSamples = AppendAudioFromBase64(AudioB64, Target);
			const float ChunkDuration = static_cast<float>(AddedSamples) / static_cast<float>(ElevenLabsSampleRate);
			const float RunningOffset = static_cast<float>(AccumulatedSamples) / static_cast<float>(ElevenLabsSampleRate);

			if (Alignment.IsValid())
			{
				// Per-chunk relative-vs-absolute detection: chunk-relative end
				// times can't exceed this chunk's own audio duration; if they do,
				// the stream is already emitting absolute times (no offset).
				const float ChunkMaxEnd = AlignmentMaxEnd(Alignment);
				const float Offset = (ChunkMaxEnd <= ChunkDuration + 0.1f) ? RunningOffset : 0.f;
				AppendCharsFromAlignment(Alignment, Offset, Target->Characters.Num(), Target->Characters);
				Target->Words = FElevenLabsProtocol::WordsFromCharacters(Target->Characters);
			}

			AccumulatedSamples += AddedSamples;
		}

		TArray<uint8> LineBuffer;
		int64 AccumulatedSamples = 0;
	};
}

FTTSSynthesisRequest FElevenLabsProtocol::BuildRequest(const FString& VoiceID, const FString& ModelID,
	const FString& Key, const FElevenLabsVoiceSettings& Settings,
	const FString& Text, const FString& ID, bool bStreaming)
{
	FTTSSynthesisRequest Request;
	Request.ID = ID;
	Request.OriginalText = Text;
	Request.bStreaming = bStreaming;

	const TCHAR* Path = bStreaming ? TEXT("stream/with-timestamps") : TEXT("with-timestamps");
	Request.URL = FString::Printf(
		TEXT("https://api.elevenlabs.io/v1/text-to-speech/%s/%s?output_format=pcm_16000"), *VoiceID, Path);

	Request.Headers.Add(TEXT("Content-Type"), TEXT("application/json"));
	Request.Headers.Add(TEXT("xi-api-key"), Key);

	const TSharedPtr<FJsonObject> Payload = MakeShareable(new FJsonObject());
	const TSharedPtr<FJsonObject> VoiceSettings = MakeShareable(new FJsonObject());
	VoiceSettings->SetNumberField(TEXT("stability"), Settings.Stability);
	VoiceSettings->SetNumberField(TEXT("similarity_boost"), Settings.SimilarityBoost);
	VoiceSettings->SetNumberField(TEXT("style"), Settings.Style);
	VoiceSettings->SetBoolField(TEXT("use_speaker_boost"), Settings.bUseSpeakerBoost);
	Payload->SetStringField(TEXT("text"), Text);
	Payload->SetStringField(TEXT("model_id"), ModelID);
	Payload->SetObjectField(TEXT("voice_settings"), VoiceSettings);

	FString Body;
	FJsonSerializer::Serialize(Payload.ToSharedRef(), TJsonWriterFactory<>::Create(&Body));
	Request.Body = Body;
	return Request;
}

TSharedPtr<FTTSStreamDecoder> FElevenLabsProtocol::MakeStreamDecoder()
{
	return MakeShared<FElevenLabsStreamDecoder>();
}

void FElevenLabsProtocol::ParseOffline(const TArray<uint8>& Json, FTTSData& OutResult)
{
	// Json may alias OutResult.AudioData; deserialize into a tree first, then
	// overwrite AudioData with the decoded PCM.
	const FString Text = Utf8ToString(Json.GetData(), Json.Num());

	TSharedPtr<FJsonObject> Root;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Text);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		return;
	}

	FString AudioB64;
	Root->TryGetStringField(TEXT("audio_base64"), AudioB64);
	TArray<uint8> Pcm;
	if (!AudioB64.IsEmpty())
	{
		FBase64::Decode(AudioB64, Pcm);
	}

	TArray<FTTSSegmentTiming> Chars;
	const TSharedPtr<FJsonObject>* AlignmentPtr = nullptr;
	if (Root->TryGetObjectField(TEXT("alignment"), AlignmentPtr) && AlignmentPtr)
	{
		AppendCharsFromAlignment(*AlignmentPtr, 0.f, 0, Chars);
	}

	OutResult.AudioData = MoveTemp(Pcm);
	OutResult.Words = WordsFromCharacters(Chars);
	OutResult.Characters = MoveTemp(Chars);
}

TArray<FTTSSegmentTiming> FElevenLabsProtocol::WordsFromCharacters(const TArray<FTTSSegmentTiming>& Characters)
{
	TArray<FTTSSegmentTiming> Words;
	FTTSSegmentTiming Current;
	bool bInWord = false;

	for (const FTTSSegmentTiming& Ch : Characters)
	{
		const bool bIsSpace = Ch.Text.IsEmpty() || FChar::IsWhitespace(Ch.Text[0]);
		if (bIsSpace)
		{
			if (bInWord)
			{
				Words.Add(Current);
				bInWord = false;
			}
		}
		else if (!bInWord)
		{
			Current = Ch; // seeds Text/Start/End/CharStart/CharEnd from the first char
			bInWord = true;
		}
		else
		{
			Current.Text += Ch.Text;
			Current.EndSeconds = Ch.EndSeconds;
			Current.CharEnd = Ch.CharEnd;
		}
	}
	if (bInWord)
	{
		Words.Add(Current);
	}
	return Words;
}
