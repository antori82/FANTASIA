/**
 * @file ElevenLabsProtocolTests.cpp
 * @brief Tests for FElevenLabsProtocol alignment decoding (word grouping + offline parse).
 *
 * Pure / deterministic: no network or ACE. Exercises the character->word
 * grouping and the one-shot /with-timestamps JSON envelope parse.
 */

#include "Misc/AutomationTest.h"
#include "ElevenLabsProtocol.h"
#include "FANTASIATypes.h"

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
