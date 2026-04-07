#pragma once

#include "CoreMinimal.h"
#include "BoltPackStream.h"

namespace BoltMsg
{
	constexpr uint8 HELLO=0x01, GOODBYE=0x02, RESET=0x0F, RUN=0x10, BEGIN=0x11, COMMIT=0x12, ROLLBACK=0x13, DISCARD=0x2F, PULL=0x3F, LOGON=0x6A;
	constexpr uint8 SUCCESS=0x70, RECORD=0x71, IGNORED=0x7E, FAILURE=0x7F;
}

namespace BoltStruct
{
	constexpr uint8 NODE=0x4E, RELATIONSHIP=0x52, UNBOUND_RELATIONSHIP=0x72, PATH=0x50;
}

struct FBoltServerMessage
{
	uint8 Tag = 0;
	FBoltValueArray Fields;
	FBoltValueMap Metadata;
};

// Cursor-based dechunker — avoids O(n) RemoveAt(0) on every chunk
class FBoltDechunker
{
public:
	void Accumulate(const void* Data, SIZE_T Length);
	bool HasCompleteMessage() const;
	bool PopMessage(TArray<uint8>& OutMessage);
	void Reset();
private:
	TArray<uint8> IncomingBuffer;
	int32 ReadCursor = 0;
	TArray<TArray<uint8>> CompletedMessages;
	int32 MessageReadIndex = 0;
	TArray<uint8> CurrentMessageChunks;
	void ProcessBuffer();
	void CompactIfNeeded();
};

namespace BoltFraming
{
	TArray<uint8> ChunkMessage(const TArray<uint8>& MessageData, int32 MaxChunkSize = 16384);
	const TArray<uint8>& BuildHandshake();
}

namespace BoltMessages
{
	TArray<uint8> BuildHello(const FString& UserAgent, const FString& Principal, const FString& Credentials);
	TArray<uint8> BuildHello51(const FString& UserAgent);
	TArray<uint8> BuildHello53(const FString& UserAgent);
	TArray<uint8> BuildLogon(const FString& Principal, const FString& Credentials);
	TArray<uint8> BuildRun(const FString& Query, const FBoltValueMap& Parameters, const FBoltValueMap& Extra);
	TArray<uint8> BuildPull(int64 N = -1, int64 Qid = -1);
	TArray<uint8> BuildBegin(const FString& Database);

	// Cached static messages — no heap allocation per call
	const TArray<uint8>& BuildCommit();
	const TArray<uint8>& BuildRollback();
	const TArray<uint8>& BuildReset();
	const TArray<uint8>& BuildGoodbye();

	// Pipeline: RUN + PULL in a single WebSocket send (saves one round-trip)
	TArray<uint8> BuildRunAndPull(const FString& Query, const FBoltValueMap& Parameters, const FBoltValueMap& Extra, int64 PullN = -1);
}

FBoltServerMessage ParseBoltServerMessage(const TArray<uint8>& DechunkedMessage);
