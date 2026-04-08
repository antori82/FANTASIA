/**
 * @file BoltProtocol.h
 * @brief Neo4j Bolt binary protocol — message tags, framing, de-chunking, and message builders.
 *
 * Implements the Bolt v4.x / v5.x wire protocol used by UNeo4jComponent to
 * communicate with a Neo4j server. Provides:
 *   - Message tag constants (BoltMsg namespace)
 *   - Structure tag constants for graph entities (BoltStruct namespace)
 *   - Chunk-level framing and de-chunking (BoltFraming, FBoltDechunker)
 *   - High-level message serialization (BoltMessages namespace)
 *   - Server-message deserialization (ParseBoltServerMessage)
 *
 * @see BoltPackStream.h, Neo4jComponent.h
 */

#pragma once

#include "CoreMinimal.h"
#include "BoltPackStream.h"

// ── Bolt message tags ───────────────────────────────────────────────────────

/** Client → server and server → client message type tags. */
namespace BoltMsg
{
	constexpr uint8 HELLO=0x01, GOODBYE=0x02, RESET=0x0F, RUN=0x10, BEGIN=0x11, COMMIT=0x12, ROLLBACK=0x13, DISCARD=0x2F, PULL=0x3F, LOGON=0x6A;
	constexpr uint8 SUCCESS=0x70, RECORD=0x71, IGNORED=0x7E, FAILURE=0x7F;
}

/** PackStream structure tags for graph entities embedded in RECORD messages. */
namespace BoltStruct
{
	constexpr uint8 NODE=0x4E, RELATIONSHIP=0x52, UNBOUND_RELATIONSHIP=0x72, PATH=0x50;
}

// ── Server message representation ───────────────────────────────────────────

/** A single parsed server message (SUCCESS, RECORD, FAILURE, or IGNORED). */
struct FBoltServerMessage
{
	uint8 Tag = 0;                ///< Message type tag (one of BoltMsg constants).
	FBoltValueArray Fields;       ///< Positional fields (e.g. columns in a RECORD).
	FBoltValueMap Metadata;       ///< Key-value metadata (e.g. "fields", "t_first").
};

// ── Dechunker ───────────────────────────────────────────────────────────────

/**
 * Cursor-based Bolt chunk de-framer.
 *
 * Bolt messages arrive as a sequence of length-prefixed chunks terminated by
 * a zero-length chunk. This class accumulates raw bytes, reassembles them
 * into complete de-chunked messages, and provides a FIFO pop interface.
 */
class FBoltDechunker
{
public:
	/** Feed raw transport bytes into the accumulator. */
	void Accumulate(const void* Data, SIZE_T Length);

	/** Returns true if at least one fully-reassembled message is ready. */
	bool HasCompleteMessage() const;

	/** Pop the oldest complete message into @p OutMessage. Returns false if none ready. */
	bool PopMessage(TArray<uint8>& OutMessage);

	/** Discard all state (used on disconnect / reset). */
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

// ── Framing helpers ─────────────────────────────────────────────────────────

/** Low-level Bolt chunk framing utilities. */
namespace BoltFraming
{
	/**
	 * Split a serialized message into Bolt chunks of at most @p MaxChunkSize bytes,
	 * terminated by a zero-length chunk.
	 */
	TArray<uint8> ChunkMessage(const TArray<uint8>& MessageData, int32 MaxChunkSize = 16384);

	/** Return the 20-byte Bolt handshake preamble (cached). */
	const TArray<uint8>& BuildHandshake();
}

// ── Message builders ────────────────────────────────────────────────────────

/** Functions that serialize complete Bolt client messages into byte arrays. */
namespace BoltMessages
{
	/** Build a HELLO message (Bolt 4.x — includes credentials). */
	TArray<uint8> BuildHello(const FString& UserAgent, const FString& Principal, const FString& Credentials);

	/** Build a HELLO message for Bolt 5.1+ (credentials sent separately via LOGON). */
	TArray<uint8> BuildHello51(const FString& UserAgent);

	/** Build a HELLO message for Bolt 5.3+. */
	TArray<uint8> BuildHello53(const FString& UserAgent);

	/** Build a LOGON message (Bolt 5.1+ two-phase authentication). */
	TArray<uint8> BuildLogon(const FString& Principal, const FString& Credentials);

	/** Build a RUN message to execute a Cypher query. */
	TArray<uint8> BuildRun(const FString& Query, const FBoltValueMap& Parameters, const FBoltValueMap& Extra);

	/** Build a PULL message to retrieve result records. */
	TArray<uint8> BuildPull(int64 N = -1, int64 Qid = -1);

	/** Build a BEGIN message to open an explicit transaction. */
	TArray<uint8> BuildBegin(const FString& Database);

	/** Cached COMMIT message (no dynamic fields). */
	const TArray<uint8>& BuildCommit();

	/** Cached ROLLBACK message. */
	const TArray<uint8>& BuildRollback();

	/** Cached RESET message. */
	const TArray<uint8>& BuildReset();

	/** Cached GOODBYE message. */
	const TArray<uint8>& BuildGoodbye();

	/**
	 * Pipeline a RUN + PULL in a single send (saves one round-trip).
	 */
	TArray<uint8> BuildRunAndPull(const FString& Query, const FBoltValueMap& Parameters, const FBoltValueMap& Extra, int64 PullN = -1);
}

/**
 * Parse a de-chunked byte buffer into a structured FBoltServerMessage.
 *
 * @param DechunkedMessage  Raw de-chunked message bytes.
 * @return Parsed server message with tag, fields, and metadata.
 */
FBoltServerMessage ParseBoltServerMessage(const TArray<uint8>& DechunkedMessage);
