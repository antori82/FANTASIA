/**
 * @file Pcm16StreamDecoderTests.cpp
 * @brief Tests for FPcm16StreamDecoder: raw PCM-16 streaming with odd-byte carry.
 */

#include "Misc/AutomationTest.h"
#include "RESTTTSComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPcm16DecoderBasic, "FANTASIA.Pcm16StreamDecoder.Basic",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPcm16DecoderBasic::RunTest(const FString& Parameters)
{
	FPcm16StreamDecoder Decoder;
	FAudioBuffer Buffer;

	// 4 bytes = 2 little-endian int16 samples: 0x0000 (0) and 0x0040 (16384)
	const uint8 Pcm[] = { 0x00, 0x00, 0x00, 0x40 };
	Decoder.Feed(TArrayView<const uint8>(Pcm, 4), &Buffer);

	TestEqual(TEXT("2 samples decoded"), Buffer.Samples.Num(), 2);
	if (Buffer.Samples.Num() == 2)
	{
		TestTrue(TEXT("Sample 0 = 0"), FMath::IsNearlyEqual(Buffer.Samples[0], 0.f, 0.001f));
		TestTrue(TEXT("Sample 1 = 0.5"), FMath::IsNearlyEqual(Buffer.Samples[1], 0.5f, 0.001f));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPcm16DecoderOddByte, "FANTASIA.Pcm16StreamDecoder.OddByteCarry",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPcm16DecoderOddByte::RunTest(const FString& Parameters)
{
	FPcm16StreamDecoder Decoder;
	FAudioBuffer Buffer;

	// Feed 3 bytes: first 2 produce one sample; the trailing byte is carried.
	const uint8 Chunk1[] = { 0x00, 0x00, 0xFF };
	Decoder.Feed(TArrayView<const uint8>(Chunk1, 3), &Buffer);
	TestEqual(TEXT("After 3 bytes: 1 sample"), Buffer.Samples.Num(), 1);

	// Feed 1 more byte to pair with the carried byte: 0xFF 0x7F = 32767 -> ~1.0
	const uint8 Chunk2[] = { 0x7F };
	Decoder.Feed(TArrayView<const uint8>(Chunk2, 1), &Buffer);
	TestEqual(TEXT("After 4 bytes total: 2 samples"), Buffer.Samples.Num(), 2);

	if (Buffer.Samples.Num() == 2)
	{
		// int16(0x7FFF) = 32767 -> 32767/32768 ~ 0.99997
		TestTrue(TEXT("Carried sample near 1.0"),
			FMath::IsNearlyEqual(Buffer.Samples[1], 32767.f / 32768.f, 0.001f));
	}
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPcm16DecoderEmpty, "FANTASIA.Pcm16StreamDecoder.EmptyFeed",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPcm16DecoderEmpty::RunTest(const FString& Parameters)
{
	FPcm16StreamDecoder Decoder;
	FAudioBuffer Buffer;

	Decoder.Feed(TArrayView<const uint8>(), &Buffer);
	TestEqual(TEXT("Empty feed: 0 samples"), Buffer.Samples.Num(), 0);

	// Single byte: carried, produces nothing until paired.
	const uint8 OneByte[] = { 0x42 };
	Decoder.Feed(TArrayView<const uint8>(OneByte, 1), &Buffer);
	TestEqual(TEXT("1 byte: still 0 samples"), Buffer.Samples.Num(), 0);

	return true;
}
