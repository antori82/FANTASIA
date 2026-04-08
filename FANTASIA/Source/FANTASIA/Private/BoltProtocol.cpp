/**
 * @file BoltProtocol.cpp
 * @brief Implementation of Bolt protocol framing, message serialization, and de-chunking.
 */

#include "BoltProtocol.h"

// ============================================================================
// Dechunker — cursor-based to avoid O(n) RemoveAt(0) per chunk
// ============================================================================

void FBoltDechunker::Reset()
{
	IncomingBuffer.Empty();
	ReadCursor = 0;
	CompletedMessages.Empty();
	MessageReadIndex = 0;
	CurrentMessageChunks.Empty();
}

void FBoltDechunker::Accumulate(const void* Data, SIZE_T Length)
{
	IncomingBuffer.Append(static_cast<const uint8*>(Data), static_cast<int32>(Length));
	ProcessBuffer();
}

void FBoltDechunker::ProcessBuffer()
{
	const int32 Total = IncomingBuffer.Num();

	while (ReadCursor + 2 <= Total)
	{
		const uint16 ChunkSize = (uint16(IncomingBuffer[ReadCursor]) << 8) | IncomingBuffer[ReadCursor + 1];

		if (ChunkSize == 0)
		{
			// End-of-message marker
			ReadCursor += 2;
			if (CurrentMessageChunks.Num() > 0)
			{
				CompletedMessages.Add(MoveTemp(CurrentMessageChunks));
				CurrentMessageChunks.Empty();
			}
		}
		else
		{
			if (ReadCursor + 2 + ChunkSize > Total)
				break; // Wait for more data

			CurrentMessageChunks.Append(&IncomingBuffer[ReadCursor + 2], ChunkSize);
			ReadCursor += 2 + ChunkSize;
		}
	}

	CompactIfNeeded();
}

void FBoltDechunker::CompactIfNeeded()
{
	// Compact when cursor has consumed >4KB and >half the buffer
	if (ReadCursor > 4096 && ReadCursor > IncomingBuffer.Num() / 2)
	{
		const int32 Remaining = IncomingBuffer.Num() - ReadCursor;
		if (Remaining > 0)
			FMemory::Memmove(IncomingBuffer.GetData(), IncomingBuffer.GetData() + ReadCursor, Remaining);
		IncomingBuffer.SetNum(Remaining, EAllowShrinking::No);
		ReadCursor = 0;
	}
}

bool FBoltDechunker::HasCompleteMessage() const
{
	return MessageReadIndex < CompletedMessages.Num();
}

bool FBoltDechunker::PopMessage(TArray<uint8>& Out)
{
	if (MessageReadIndex >= CompletedMessages.Num())
		return false;

	Out = MoveTemp(CompletedMessages[MessageReadIndex]);
	MessageReadIndex++;

	// Compact completed messages array when fully consumed
	if (MessageReadIndex == CompletedMessages.Num())
	{
		CompletedMessages.Empty();
		MessageReadIndex = 0;
	}

	return true;
}

// ============================================================================
// Framing — pre-allocated output
// ============================================================================

TArray<uint8> BoltFraming::ChunkMessage(const TArray<uint8>& Msg, int32 Max)
{
	TArray<uint8> R;
	const int32 MsgLen = Msg.Num();
	// Pre-allocate: data + 2-byte headers per chunk + 2-byte terminator
	const int32 NumChunks = (MsgLen + Max - 1) / Max;
	R.Reserve(MsgLen + NumChunks * 2 + 2);

	int32 Off = 0;
	int32 Rem = MsgLen;
	const uint8* Src = Msg.GetData();
	while (Rem > 0)
	{
		const int32 C = FMath::Min(Rem, Max);
		R.Add(static_cast<uint8>((C >> 8) & 0xFF));
		R.Add(static_cast<uint8>(C & 0xFF));
		R.Append(Src + Off, C);
		Off += C;
		Rem -= C;
	}
	R.Add(0);
	R.Add(0);
	return R;
}

const TArray<uint8>& BoltFraming::BuildHandshake()
{
	static const TArray<uint8> Handshake = []()
	{
		TArray<uint8> D;
		D.Reserve(20);
		// Magic preamble
		D.Add(0x60); D.Add(0x60); D.Add(0xB0); D.Add(0x17);
		// Version format per 4-byte slot: [patch, range, minor, major]
		// Bolt 5.0-5.6: patch=0, range=6, minor=6, major=5
		D.Add(0x00); D.Add(0x06); D.Add(0x06); D.Add(0x05);
		// Bolt 4.0-4.4: patch=0, range=4, minor=4, major=4
		D.Add(0x00); D.Add(0x04); D.Add(0x04); D.Add(0x04);
		// empty
		D.Add(0); D.Add(0); D.Add(0); D.Add(0);
		D.Add(0); D.Add(0); D.Add(0); D.Add(0);
		return D;
	}();
	return Handshake;
}

// ============================================================================
// Helpers
// ============================================================================

static void WriteMap(FBoltPackStreamWriter& W, const FBoltValueMap& M)
{
	W.WriteMapHeader(M.Num());
	for (const auto& P : M)
	{
		W.WriteString(P.Key);
		W.WriteValue(P.Value);
	}
}

// ============================================================================
// Messages
// ============================================================================

TArray<uint8> BoltMessages::BuildHello(const FString& UA, const FString& P, const FString& C)
{
	FBoltPackStreamWriter W;
	FBoltValueMap Extra;
	Extra.Add(TEXT("user_agent"), FBoltValue::MakeString(UA));
	Extra.Add(TEXT("scheme"), FBoltValue::MakeString(TEXT("basic")));
	Extra.Add(TEXT("principal"), FBoltValue::MakeString(P));
	Extra.Add(TEXT("credentials"), FBoltValue::MakeString(C));
	W.WriteStructureHeader(BoltMsg::HELLO, 1);
	WriteMap(W, Extra);
	return W.GetBuffer();
}

TArray<uint8> BoltMessages::BuildHello51(const FString& UA)
{
	FBoltPackStreamWriter W;
	FBoltValueMap Extra;
	Extra.Add(TEXT("user_agent"), FBoltValue::MakeString(UA));
	W.WriteStructureHeader(BoltMsg::HELLO, 1);
	WriteMap(W, Extra);
	return W.GetBuffer();
}

TArray<uint8> BoltMessages::BuildHello53(const FString& UA)
{
	// Bolt 5.3+: requires both user_agent (string) AND bolt_agent (Map<String,String>)
	FBoltPackStreamWriter W;
	FBoltValueMap Extra;

	Extra.Add(TEXT("user_agent"), FBoltValue::MakeString(UA));

	FBoltValueMap AgentMap;
	AgentMap.Add(TEXT("product"), FBoltValue::MakeString(UA));
	AgentMap.Add(TEXT("language"), FBoltValue::MakeString(TEXT("C++")));
	AgentMap.Add(TEXT("language_details"), FBoltValue::MakeString(TEXT("UE 5.6")));
	Extra.Add(TEXT("bolt_agent"), FBoltValue::MakeMap(MoveTemp(AgentMap)));

	W.WriteStructureHeader(BoltMsg::HELLO, 1);
	WriteMap(W, Extra);
	return W.GetBuffer();
}

TArray<uint8> BoltMessages::BuildLogon(const FString& P, const FString& C)
{
	FBoltPackStreamWriter W;
	FBoltValueMap Auth;
	Auth.Add(TEXT("scheme"), FBoltValue::MakeString(TEXT("basic")));
	Auth.Add(TEXT("principal"), FBoltValue::MakeString(P));
	Auth.Add(TEXT("credentials"), FBoltValue::MakeString(C));
	W.WriteStructureHeader(BoltMsg::LOGON, 1);
	WriteMap(W, Auth);
	return W.GetBuffer();
}

TArray<uint8> BoltMessages::BuildRun(const FString& Query, const FBoltValueMap& Params, const FBoltValueMap& Extra)
{
	FBoltPackStreamWriter W;
	W.WriteStructureHeader(BoltMsg::RUN, 3);
	W.WriteString(Query);
	WriteMap(W, Params);
	WriteMap(W, Extra);
	return W.GetBuffer();
}

TArray<uint8> BoltMessages::BuildPull(int64 N, int64 Qid)
{
	FBoltPackStreamWriter W;
	W.WriteStructureHeader(BoltMsg::PULL, 1);
	FBoltValueMap Extra;
	Extra.Add(TEXT("n"), FBoltValue::MakeInt(N));
	if (Qid >= 0) Extra.Add(TEXT("qid"), FBoltValue::MakeInt(Qid));
	WriteMap(W, Extra);
	return W.GetBuffer();
}

TArray<uint8> BoltMessages::BuildBegin(const FString& DB)
{
	FBoltPackStreamWriter W;
	W.WriteStructureHeader(BoltMsg::BEGIN, 1);
	FBoltValueMap Extra;
	if (!DB.IsEmpty()) Extra.Add(TEXT("db"), FBoltValue::MakeString(DB));
	WriteMap(W, Extra);
	return W.GetBuffer();
}

// Cached static messages — built once, returned by const ref
const TArray<uint8>& BoltMessages::BuildCommit()
{
	static const TArray<uint8> Msg = []() { FBoltPackStreamWriter W; W.WriteStructureHeader(BoltMsg::COMMIT, 0); return W.GetBuffer(); }();
	return Msg;
}

const TArray<uint8>& BoltMessages::BuildRollback()
{
	static const TArray<uint8> Msg = []() { FBoltPackStreamWriter W; W.WriteStructureHeader(BoltMsg::ROLLBACK, 0); return W.GetBuffer(); }();
	return Msg;
}

const TArray<uint8>& BoltMessages::BuildReset()
{
	static const TArray<uint8> Msg = []() { FBoltPackStreamWriter W; W.WriteStructureHeader(BoltMsg::RESET, 0); return W.GetBuffer(); }();
	return Msg;
}

const TArray<uint8>& BoltMessages::BuildGoodbye()
{
	static const TArray<uint8> Msg = []() { FBoltPackStreamWriter W; W.WriteStructureHeader(BoltMsg::GOODBYE, 0); return W.GetBuffer(); }();
	return Msg;
}

// Pipeline: RUN + PULL concatenated into a single chunked payload (saves a round-trip)
TArray<uint8> BoltMessages::BuildRunAndPull(const FString& Query, const FBoltValueMap& Params, const FBoltValueMap& Extra, int64 PullN)
{
	TArray<uint8> RunChunked = BoltFraming::ChunkMessage(BuildRun(Query, Params, Extra));
	TArray<uint8> PullChunked = BoltFraming::ChunkMessage(BuildPull(PullN));
	RunChunked.Append(PullChunked);
	return RunChunked;
}

// ============================================================================
// Parser
// ============================================================================

FBoltServerMessage ParseBoltServerMessage(const TArray<uint8>& D)
{
	FBoltServerMessage Msg;
	FBoltPackStreamReader Reader(D);
	FBoltValuePtr Val = Reader.ReadValue();
	if (!Val || Val->Type != EBoltValueType::Structure)
	{
		UE_LOG(LogTemp, Error, TEXT("Bolt: Expected structure"));
		return Msg;
	}

	Msg.Tag = Val->StructVal.Tag;
	switch (Msg.Tag)
	{
	case BoltMsg::SUCCESS:
	case BoltMsg::FAILURE:
		if (Val->StructVal.Fields.Num() > 0 && Val->StructVal.Fields[0]->Type == EBoltValueType::Map)
			Msg.Metadata = MoveTemp(Val->StructVal.Fields[0]->MapVal);
		break;
	case BoltMsg::RECORD:
		if (Val->StructVal.Fields.Num() > 0 && Val->StructVal.Fields[0]->Type == EBoltValueType::List)
			Msg.Fields = MoveTemp(Val->StructVal.Fields[0]->ListVal);
		break;
	default:
		break;
	}
	return Msg;
}
