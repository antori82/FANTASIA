/**
 * @file ElevenLabsProtocolTests.cpp
 * @brief Tests for FElevenLabsProtocol: request building (speed, language_code),
 *        pronunciation alias map, word grouping, streaming NDJSON decoder, and
 *        offline JSON parse.
 *
 * Pure / deterministic: no network or ACE.
 */

#include "Misc/AutomationTest.h"
#include "ElevenLabsProtocol.h"
#include "FANTASIATypes.h"
#include "Misc/Base64.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace
{
	FTTSSegmentTiming MakeChar(const FString& Text, float Start, float End, int32 Index)
	{
		FTTSSegmentTiming C;
		C.Text = Text;
		C.StartSeconds = Start;
		C.EndSeconds = End;
		C.CharStart = Index;
		C.CharEnd = Index + 1;
		return C;
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsWordsFromChars, "FANTASIA.ElevenLabs.WordsFromCharacters",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsWordsFromChars::RunTest(const FString& Parameters)
{
	// "Hi there" -> two words split on the space.
	TArray<FTTSSegmentTiming> Chars;
	Chars.Add(MakeChar(TEXT("H"), 0.00f, 0.10f, 0));
	Chars.Add(MakeChar(TEXT("i"), 0.10f, 0.20f, 1));
	Chars.Add(MakeChar(TEXT(" "), 0.20f, 0.25f, 2));
	Chars.Add(MakeChar(TEXT("t"), 0.30f, 0.40f, 3));
	Chars.Add(MakeChar(TEXT("h"), 0.40f, 0.50f, 4));
	Chars.Add(MakeChar(TEXT("e"), 0.50f, 0.60f, 5));
	Chars.Add(MakeChar(TEXT("r"), 0.60f, 0.70f, 6));
	Chars.Add(MakeChar(TEXT("e"), 0.70f, 0.80f, 7));

	const TArray<FTTSSegmentTiming> Words = FElevenLabsProtocol::WordsFromCharacters(Chars);

	TestEqual(TEXT("Word count"), Words.Num(), 2);
	if (Words.Num() == 2)
	{
		TestEqual(TEXT("Word 0 text"), Words[0].Text, FString(TEXT("Hi")));
		TestEqual(TEXT("Word 0 start"), Words[0].StartSeconds, 0.00f, 0.001f);
		TestEqual(TEXT("Word 0 end"), Words[0].EndSeconds, 0.20f, 0.001f);
		TestEqual(TEXT("Word 0 charStart"), Words[0].CharStart, 0);
		TestEqual(TEXT("Word 0 charEnd"), Words[0].CharEnd, 2);

		TestEqual(TEXT("Word 1 text"), Words[1].Text, FString(TEXT("there")));
		TestEqual(TEXT("Word 1 start"), Words[1].StartSeconds, 0.30f, 0.001f);
		TestEqual(TEXT("Word 1 end"), Words[1].EndSeconds, 0.80f, 0.001f);
		TestEqual(TEXT("Word 1 charStart"), Words[1].CharStart, 3);
		TestEqual(TEXT("Word 1 charEnd"), Words[1].CharEnd, 8);
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsApplyPronunciations, "FANTASIA.ElevenLabs.ApplyPronunciations",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsApplyPronunciations::RunTest(const FString& Parameters)
{
	TMap<FString, FString> Map;
	Map.Add(TEXT("epilessia"), TEXT("epilessìa")); // epilessìa

	// Empty map is a pass-through (no allocation, identical string).
	TestEqual(TEXT("Empty map unchanged"),
		FElevenLabsProtocol::ApplyPronunciations(TMap<FString, FString>(), TEXT("L'epilessia")),
		FString(TEXT("L'epilessia")));

	// Whole-word match mid-sentence, surrounding punctuation preserved.
	TestEqual(TEXT("Mid-sentence match"),
		FElevenLabsProtocol::ApplyPronunciations(Map, TEXT("Soffre di epilessia, dice.")),
		FString(TEXT("Soffre di epilessìa, dice.")));

	// Case-insensitive match; a leading capital is preserved on the replacement.
	TestEqual(TEXT("Sentence-start capital preserved"),
		FElevenLabsProtocol::ApplyPronunciations(Map, TEXT("Epilessia diagnosticata.")),
		FString(TEXT("Epilessìa diagnosticata.")));

	// A key that is only a substring of a longer word must NOT be replaced.
	TestEqual(TEXT("No partial-word match"),
		FElevenLabsProtocol::ApplyPronunciations(Map, TEXT("antiepilessiaco")),
		FString(TEXT("antiepilessiaco")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsParseOffline, "FANTASIA.ElevenLabs.ParseOffline",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsParseOffline::RunTest(const FString& Parameters)
{
	// audio_base64 "AAAAQA==" decodes to 4 bytes (two int16 samples: 0 and 16384).
	const FString Json = TEXT("{")
		TEXT("\"audio_base64\":\"AAAAQA==\",")
		TEXT("\"alignment\":{")
		TEXT("\"characters\":[\"H\",\"i\"],")
		TEXT("\"character_start_times_seconds\":[0.0,0.1],")
		TEXT("\"character_end_times_seconds\":[0.1,0.2]")
		TEXT("}}");

	TArray<uint8> JsonBytes;
	const FTCHARToUTF8 Utf8(*Json);
	JsonBytes.Append(reinterpret_cast<const uint8*>(Utf8.Get()), Utf8.Length());

	FTTSData Result;
	FElevenLabsProtocol::ParseOffline(JsonBytes, Result);

	TestEqual(TEXT("Decoded PCM byte count"), Result.AudioData.Num(), 4);
	TestEqual(TEXT("Character count"), Result.Characters.Num(), 2);
	TestEqual(TEXT("Word count"), Result.Words.Num(), 1);
	if (Result.Words.Num() == 1)
	{
		TestEqual(TEXT("Word text"), Result.Words[0].Text, FString(TEXT("Hi")));
		TestEqual(TEXT("Word start"), Result.Words[0].StartSeconds, 0.0f, 0.001f);
		TestEqual(TEXT("Word end"), Result.Words[0].EndSeconds, 0.2f, 0.001f);
	}
	return true;
}

// ============================================================================
// BuildRequest
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsBuildRequestSpeed, "FANTASIA.ElevenLabs.BuildRequest.Speed",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsBuildRequestSpeed::RunTest(const FString& Parameters)
{
	FElevenLabsVoiceSettings Settings;
	Settings.Speed = 0.8f;

	FTTSSynthesisRequest Req = FElevenLabsProtocol::BuildRequest(
		TEXT("voice123"), TEXT("model_v2"), TEXT("key"), Settings,
		TEXT("test"), TEXT("id1"), false);

	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Req.Body);
	TestTrue(TEXT("Body parses"), FJsonSerializer::Deserialize(Reader, Root) && Root.IsValid());

	const TSharedPtr<FJsonObject>* VS = nullptr;
	TestTrue(TEXT("voice_settings present"), Root->TryGetObjectField(TEXT("voice_settings"), VS) && VS != nullptr);
	if (VS)
	{
		double SpeedVal = 0.0;
		TestTrue(TEXT("speed field exists"), (*VS)->TryGetNumberField(TEXT("speed"), SpeedVal));
		TestTrue(TEXT("speed value"), FMath::IsNearlyEqual(static_cast<float>(SpeedVal), 0.8f, 0.001f));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsBuildRequestLanguageCode, "FANTASIA.ElevenLabs.BuildRequest.LanguageCode",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsBuildRequestLanguageCode::RunTest(const FString& Parameters)
{
	FElevenLabsVoiceSettings Settings;

	// With language code
	FTTSSynthesisRequest ReqWithLang = FElevenLabsProtocol::BuildRequest(
		TEXT("voice123"), TEXT("model_v2"), TEXT("key"), Settings,
		TEXT("Ciao"), TEXT("id1"), false, TEXT("it"));

	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ReqWithLang.Body);
	TestTrue(TEXT("Body parses"), FJsonSerializer::Deserialize(Reader, Root) && Root.IsValid());

	FString LangCode;
	TestTrue(TEXT("language_code present"), Root->TryGetStringField(TEXT("language_code"), LangCode));
	TestEqual(TEXT("language_code value"), LangCode, FString(TEXT("it")));

	// Without language code: field should be absent
	FTTSSynthesisRequest ReqNoLang = FElevenLabsProtocol::BuildRequest(
		TEXT("voice123"), TEXT("model_v2"), TEXT("key"), Settings,
		TEXT("Hello"), TEXT("id2"), false);

	TSharedPtr<FJsonObject> Root2;
	TSharedRef<TJsonReader<>> Reader2 = TJsonReaderFactory<>::Create(ReqNoLang.Body);
	TestTrue(TEXT("Body2 parses"), FJsonSerializer::Deserialize(Reader2, Root2) && Root2.IsValid());
	TestFalse(TEXT("language_code absent"), Root2->HasField(TEXT("language_code")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsBuildRequestURL, "FANTASIA.ElevenLabs.BuildRequest.URL",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsBuildRequestURL::RunTest(const FString& Parameters)
{
	FElevenLabsVoiceSettings Settings;

	FTTSSynthesisRequest Streaming = FElevenLabsProtocol::BuildRequest(
		TEXT("v1"), TEXT("m1"), TEXT("k"), Settings, TEXT("x"), TEXT("id"), true);
	TestTrue(TEXT("Streaming URL"), Streaming.URL.Contains(TEXT("stream/with-timestamps")));
	TestTrue(TEXT("Streaming flag"), Streaming.bStreaming);

	FTTSSynthesisRequest OneShot = FElevenLabsProtocol::BuildRequest(
		TEXT("v1"), TEXT("m1"), TEXT("k"), Settings, TEXT("x"), TEXT("id"), false);
	TestTrue(TEXT("Offline URL"), OneShot.URL.Contains(TEXT("with-timestamps")));
	TestFalse(TEXT("Offline URL no stream"), OneShot.URL.Contains(TEXT("stream/")));
	TestFalse(TEXT("Offline flag"), OneShot.bStreaming);

	return true;
}

// ============================================================================
// WordsFromCharacters — edge cases
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsWordsFromCharsEmpty, "FANTASIA.ElevenLabs.WordsFromCharacters.Empty",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsWordsFromCharsEmpty::RunTest(const FString& Parameters)
{
	TArray<FTTSSegmentTiming> Empty;
	TestEqual(TEXT("Empty -> 0 words"), FElevenLabsProtocol::WordsFromCharacters(Empty).Num(), 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsWordsFromCharsSingle, "FANTASIA.ElevenLabs.WordsFromCharacters.SingleChar",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsWordsFromCharsSingle::RunTest(const FString& Parameters)
{
	TArray<FTTSSegmentTiming> Chars;
	Chars.Add(MakeChar(TEXT("A"), 0.f, 0.1f, 0));

	const TArray<FTTSSegmentTiming> Words = FElevenLabsProtocol::WordsFromCharacters(Chars);
	TestEqual(TEXT("One word"), Words.Num(), 1);
	if (Words.Num() == 1)
	{
		TestEqual(TEXT("Text"), Words[0].Text, FString(TEXT("A")));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsWordsFromCharsMultipleSpaces, "FANTASIA.ElevenLabs.WordsFromCharacters.MultipleSpaces",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsWordsFromCharsMultipleSpaces::RunTest(const FString& Parameters)
{
	TArray<FTTSSegmentTiming> Chars;
	Chars.Add(MakeChar(TEXT("A"), 0.0f, 0.1f, 0));
	Chars.Add(MakeChar(TEXT(" "), 0.1f, 0.2f, 1));
	Chars.Add(MakeChar(TEXT(" "), 0.2f, 0.3f, 2));
	Chars.Add(MakeChar(TEXT("B"), 0.3f, 0.4f, 3));

	const TArray<FTTSSegmentTiming> Words = FElevenLabsProtocol::WordsFromCharacters(Chars);
	TestEqual(TEXT("Two words despite double space"), Words.Num(), 2);
	if (Words.Num() == 2)
	{
		TestEqual(TEXT("Word 0"), Words[0].Text, FString(TEXT("A")));
		TestEqual(TEXT("Word 1"), Words[1].Text, FString(TEXT("B")));
		TestEqual(TEXT("Word 1 charStart"), Words[1].CharStart, 3);
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsWordsFromCharsTrailingSpace, "FANTASIA.ElevenLabs.WordsFromCharacters.TrailingSpace",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsWordsFromCharsTrailingSpace::RunTest(const FString& Parameters)
{
	TArray<FTTSSegmentTiming> Chars;
	Chars.Add(MakeChar(TEXT("O"), 0.0f, 0.1f, 0));
	Chars.Add(MakeChar(TEXT("k"), 0.1f, 0.2f, 1));
	Chars.Add(MakeChar(TEXT(" "), 0.2f, 0.3f, 2));

	const TArray<FTTSSegmentTiming> Words = FElevenLabsProtocol::WordsFromCharacters(Chars);
	TestEqual(TEXT("One word, trailing space dropped"), Words.Num(), 1);
	if (Words.Num() == 1)
	{
		TestEqual(TEXT("Text"), Words[0].Text, FString(TEXT("Ok")));
		TestEqual(TEXT("CharEnd"), Words[0].CharEnd, 2);
	}
	return true;
}

// ============================================================================
// Streaming NDJSON decoder
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsStreamDecoderBasic, "FANTASIA.ElevenLabs.StreamDecoder.Basic",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsStreamDecoderBasic::RunTest(const FString& Parameters)
{
	TSharedPtr<FTTSStreamDecoder> Decoder = FElevenLabsProtocol::MakeStreamDecoder();
	TestTrue(TEXT("Decoder created"), Decoder.IsValid());

	FAudioBuffer Buffer;

	// Two NDJSON lines: line 1 carries "A " (word + trailing space),
	// line 2 carries "B" (second word). Each has 4 bytes of audio
	// (2 int16 samples). "AAAAQA==" = 4 bytes: int16(0), int16(16384).
	const FString Line1 = TEXT("{\"audio_base64\":\"AAAAQA==\",\"alignment\":{")
		TEXT("\"characters\":[\"A\",\" \"],")
		TEXT("\"character_start_times_seconds\":[0.0,0.1],")
		TEXT("\"character_end_times_seconds\":[0.1,0.15]}}\n");

	const FString Line2 = TEXT("{\"audio_base64\":\"AAAAQA==\",\"alignment\":{")
		TEXT("\"characters\":[\"B\"],")
		TEXT("\"character_start_times_seconds\":[0.0],")
		TEXT("\"character_end_times_seconds\":[0.1]}}\n");

	const FTCHARToUTF8 Utf8Line1(*Line1);
	const FTCHARToUTF8 Utf8Line2(*Line2);

	Decoder->Feed(TArrayView<const uint8>(
		reinterpret_cast<const uint8*>(Utf8Line1.Get()), Utf8Line1.Length()), &Buffer);

	TestEqual(TEXT("After line 1: 2 samples"), Buffer.Samples.Num(), 2);
	TestEqual(TEXT("After line 1: 2 chars"), Buffer.Characters.Num(), 2);
	TestEqual(TEXT("After line 1: 1 word"), Buffer.Words.Num(), 1);

	Decoder->Feed(TArrayView<const uint8>(
		reinterpret_cast<const uint8*>(Utf8Line2.Get()), Utf8Line2.Length()), &Buffer);

	TestEqual(TEXT("After line 2: 4 samples"), Buffer.Samples.Num(), 4);
	TestEqual(TEXT("After line 2: 3 chars"), Buffer.Characters.Num(), 3);
	TestEqual(TEXT("After line 2: 2 words"), Buffer.Words.Num(), 2);

	if (Buffer.Words.Num() == 2)
	{
		TestEqual(TEXT("Word 0 text"), Buffer.Words[0].Text, FString(TEXT("A")));
		TestEqual(TEXT("Word 1 text"), Buffer.Words[1].Text, FString(TEXT("B")));
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsStreamDecoderPartialLine, "FANTASIA.ElevenLabs.StreamDecoder.PartialLine",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsStreamDecoderPartialLine::RunTest(const FString& Parameters)
{
	TSharedPtr<FTTSStreamDecoder> Decoder = FElevenLabsProtocol::MakeStreamDecoder();
	FAudioBuffer Buffer;

	// Feed a line split across two chunks to exercise partial-line buffering.
	const FString Full = TEXT("{\"audio_base64\":\"AAAAQA==\",\"alignment\":{")
		TEXT("\"characters\":[\"X\"],")
		TEXT("\"character_start_times_seconds\":[0.0],")
		TEXT("\"character_end_times_seconds\":[0.1]}}");

	const FString Half1 = Full.Left(Full.Len() / 2);
	const FString Half2 = Full.Mid(Full.Len() / 2);

	const FTCHARToUTF8 Utf8H1(*Half1);
	const FTCHARToUTF8 Utf8H2(*Half2);

	Decoder->Feed(TArrayView<const uint8>(
		reinterpret_cast<const uint8*>(Utf8H1.Get()), Utf8H1.Length()), &Buffer);

	// No complete line yet — nothing decoded.
	TestEqual(TEXT("Mid-line: 0 samples"), Buffer.Samples.Num(), 0);

	// Finish flushes the buffered partial line.
	Decoder->Feed(TArrayView<const uint8>(
		reinterpret_cast<const uint8*>(Utf8H2.Get()), Utf8H2.Length()), &Buffer);
	Decoder->Finish(&Buffer);

	TestEqual(TEXT("After finish: 2 samples"), Buffer.Samples.Num(), 2);
	TestEqual(TEXT("After finish: 1 word"), Buffer.Words.Num(), 1);
	if (Buffer.Words.Num() == 1)
	{
		TestEqual(TEXT("Word text"), Buffer.Words[0].Text, FString(TEXT("X")));
	}
	return true;
}

// ============================================================================
// ApplyPronunciations — additional edge cases
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsPronunciationsMultipleKeys, "FANTASIA.ElevenLabs.ApplyPronunciations.MultipleKeys",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsPronunciationsMultipleKeys::RunTest(const FString& Parameters)
{
	TMap<FString, FString> Map;
	Map.Add(TEXT("alfa"), TEXT("alpha"));
	Map.Add(TEXT("beta"), TEXT("bèta"));

	TestEqual(TEXT("Both replaced"),
		FElevenLabsProtocol::ApplyPronunciations(Map, TEXT("alfa e beta")),
		FString(TEXT("alpha e bèta")));

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FElevenLabsPronunciationsEmptyText, "FANTASIA.ElevenLabs.ApplyPronunciations.EmptyText",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FElevenLabsPronunciationsEmptyText::RunTest(const FString& Parameters)
{
	TMap<FString, FString> Map;
	Map.Add(TEXT("x"), TEXT("y"));

	TestTrue(TEXT("Empty text unchanged"),
		FElevenLabsProtocol::ApplyPronunciations(Map, TEXT("")).IsEmpty());
	return true;
}
