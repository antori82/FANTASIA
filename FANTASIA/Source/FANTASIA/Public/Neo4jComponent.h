/**
 * @file Neo4jComponent.h
 * @brief Actor component for executing Cypher queries against a Neo4j database via the Bolt protocol.
 */

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "IWebSocket.h"
#include "BoltPackStream.h"
#include "BoltProtocol.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Neo4jComponent.generated.h"

/** Internal connection state of the Bolt transport layer. */
enum class EBoltConnectionState : uint8
{
	Disconnected,       ///< No connection attempt in progress.
	Connecting,         ///< TCP / WebSocket connection is being established.
	HandshakePending,   ///< Bolt handshake sent, awaiting version negotiation response.
	Authenticating,     ///< HELLO / LOGON sent, awaiting SUCCESS.
	LogonPending,       ///< Bolt 5.1+ two-phase auth: HELLO succeeded, LOGON in flight.
	RoutingDiscovery,   ///< Sent dbms.routing.getRoutingTable, awaiting records + SUCCESS.
	Ready,              ///< Authenticated and idle — ready to accept queries.
	Streaming,          ///< A RUN/PULL cycle is in progress (auto-commit).
	TxReady,            ///< Inside an explicit transaction, idle.
	TxStreaming,        ///< Inside an explicit transaction, RUN/PULL in progress.
	Failed,             ///< A protocol or transport error has occurred.
	Closed              ///< Connection was cleanly closed.
};

/** Phase within the routing discovery query (RUN + PULL). */
enum class EBoltRoutingPhase : uint8
{
	Idle,
	WaitingRunSuccess,
	WaitingPullRecords
};

/** Phase within a single Cypher query execution (RUN → PULL). */
enum class EBoltQueryPhase : uint8
{
	Idle,                ///< No query in progress.
	WaitingRunSuccess,   ///< RUN message sent, waiting for SUCCESS with field names.
	WaitingPullRecords   ///< PULL message sent, collecting RECORD / SUCCESS messages.
};

/** A queued Bolt command awaiting execution. */
struct FBoltPendingCommand
{
	Neo4jOperation Operation;              ///< Auto-commit, begin, commit, rollback, or add-to-tx.
	FString Query;                         ///< Cypher query text.
	TMap<FString, FString> Parameters;     ///< Query parameters (string values).
	FString Database;                      ///< Target database name (empty = default).
	FString TransactionID;                 ///< Transaction ID for explicit-transaction ops.
};

/** Fired when a Cypher query result is available. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingNeo4jResponseEvent, FNeo4jResponse, Neo4jResponse);

/**
 * Actor component that connects to a Neo4j instance over the Bolt binary
 * protocol and executes Cypher queries exposed to Blueprints.
 *
 * Supports both WebSocket transport (plain) and TCP+TLS transport (when
 * @c UseSSL is enabled). Queries may run as auto-commit or inside explicit
 * transactions (BEGIN / ADD / COMMIT / ROLLBACK).
 *
 * @see UBoltProtocol, UBoltPackStream
 */
UCLASS(ClassGroup = (Neo4j), meta = (BlueprintSpawnableComponent), config=Game)
class FANTASIA_API UNeo4jComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNeo4jComponent();

	// ── Configuration ────────────────────────────────────────────────────

	/** Neo4j Bolt endpoint URL or hostname (e.g. "bolt://localhost"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString endpoint;

	/** Bolt listener port (default 7687). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	int port;

	/** Authentication username. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString user;

	/** Authentication password. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString password;

	/** When true, use TCP+TLS (OpenSSL) instead of WebSocket transport. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	bool UseSSL = false;

	// ── Events ───────────────────────────────────────────────────────────

	/** Broadcast when a query result (or transaction acknowledgement) is received. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingNeo4jResponseEvent IncomingResponse;

	/** Raw text of the most recent server response (debugging aid). */
	UPROPERTY(BlueprintReadOnly)
	FString response;

	// ── Public API ───────────────────────────────────────────────────────

	/**
	 * Submit a Cypher query for execution.
	 *
	 * @param query          Cypher query text.
	 * @param operation      Transaction mode (single, begin, add, commit, rollback).
	 * @param transactionID  ID returned by a previous BEGIN operation (empty for auto-commit).
	 * @param parameters     Query parameter map (string → string).
	 * @param database       Target database (empty = server default).
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query", AutoCreateRefTerm = "parameters"), Category = "Neo4j")
	void submitQuery(FString query, Neo4jOperation operation, FString transactionID, TMap<FString, FString> parameters, FString database);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	// ── Transport-agnostic state ─────────────────────────────────────────
	EBoltConnectionState ConnectionState = EBoltConnectionState::Disconnected;
	EBoltQueryPhase QueryPhase = EBoltQueryPhase::Idle;
	int32 NegotiatedBoltMajor = 0;
	int32 NegotiatedBoltMinor = 0;
	TUniquePtr<FBoltDechunker> Dechunker;
	TArray<FBoltPendingCommand> PendingCommands;
	int32 PendingCommandIndex = 0;
	TArray<FString> CurrentFieldNames;
	TArray<FBoltValueArray> CurrentRecords;
	Neo4jOperation CurrentOperation = Neo4jOperation::SINGLE_REQUEST;
	FString CurrentDatabase;
	FString ActiveTransactionID;
	int32 TransactionCounter = 0;
	TArray<uint8> HandshakeBuffer;

	// ── Server-side routing (Neo4j cluster / Aura) ───────────────────────
	bool bNeedsRouting = false;         ///< URL scheme indicates routing-aware driver required.
	bool bRoutingDone = false;          ///< Backend has been discovered and we are connected to it.
	EBoltRoutingPhase RoutingPhase = EBoltRoutingPhase::Idle;
	FString ActiveHostname;             ///< Current hostname we are connected to (frontend or backend).
	int32 ActivePort = 0;               ///< Current port we are connected to.
	TArray<FBoltValueArray> RoutingRecords; ///< Buffered records from the routing discovery call.

	// ── WebSocket transport (UseSSL == false) ────────────────────────────
	TSharedPtr<IWebSocket> WebSocket;
	int32 ConnectionEpoch = 0;  ///< Incremented on every new connection; stale callbacks are filtered.
	void OnWebSocketConnected(int32 Epoch);
	void OnWebSocketConnectionError(int32 Epoch, const FString& Error);
	void OnWebSocketClosed(int32 Epoch, int32 StatusCode, const FString& Reason, bool bWasClean);
	void OnWebSocketBinaryMessage(int32 Epoch, const void* Data, SIZE_T Size, SIZE_T BytesRemaining);

	// ── TCP+TLS transport (UseSSL == true) ───────────────────────────────
	void* SslCtx = nullptr;
	void* SslHandle = nullptr;
	void* SslBio = nullptr;
	FRunnableThread* RecvThread = nullptr;
	std::atomic<bool> bRecvThreadRunning{false};
	void TcpSslConnect(const FString& Hostname, int32 InPort);
	void TcpSslDisconnect();
	void TcpRecvLoop();

	// ── Transport dispatch ───────────────────────────────────────────────
	void SendRawBytes(const uint8* Data, int32 Len);
	void OnDataReceived(const void* Data, SIZE_T Size);

	// ── Bolt protocol logic ─────────────────────────────────────────────
	void SendBoltHandshake();
	void HandleHandshakeResponse();
	void SendAuthentication();
	void HandleServerMessage(const FBoltServerMessage& Msg);
	void ProcessNextCommand();
	void SendChunkedMessage(const TArray<uint8>& MessageData);
	void DispatchCommand(const FBoltPendingCommand& Cmd);
	FNeo4jResponse ConvertBoltRecordsToResponse();
	UNeo4jResultCell* ConvertBoltValueToCell(const FBoltValuePtr& Value);
	FBoltValueMap ConvertParameters(const TMap<FString, FString>& InParams);

	// ── Routing discovery (Bolt routing for clustered / Aura deployments) ───
	void InitiateConnection(const FString& Hostname, int32 InPort);
	void TearDownCurrentConnection();
	void OnAuthenticationComplete();
	void SendRoutingQuery();
	void HandleRoutingMessage(const FBoltServerMessage& Msg);
	void ReconnectToBackendAddress(const FString& AddressHostPort);
	FString PickWriteAddressFromRoutingRecord(const FBoltValueArray& RecordFields);

	// ── Helpers ──────────────────────────────────────────────────────────
	FString ExtractHostname(const FString& Url);
	bool ShouldUseSSL(const FString& Url);
	bool SchemeRequiresRouting(const FString& Url);

	friend class FNeo4jRecvRunnable;
};
