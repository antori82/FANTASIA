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

enum class EBoltConnectionState : uint8
{
	Disconnected,
	Connecting,
	HandshakePending,
	Authenticating,
	LogonPending,
	Ready,
	Streaming,
	TxReady,
	TxStreaming,
	Failed,
	Closed
};

enum class EBoltQueryPhase : uint8
{
	Idle,
	WaitingRunSuccess,
	WaitingPullRecords
};

struct FBoltPendingCommand
{
	Neo4jOperation Operation;
	FString Query;
	TMap<FString, FString> Parameters;
	FString Database;
	FString TransactionID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingNeo4jResponseEvent, FNeo4jResponse, Neo4jResponse);

UCLASS(ClassGroup = (Neo4j), meta = (BlueprintSpawnableComponent), config=Game)
class UNeo4jComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNeo4jComponent();

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString endpoint;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	int port;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString user;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString password;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	bool UseSSL = false;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingNeo4jResponseEvent IncomingResponse;

	UPROPERTY(BlueprintReadOnly)
	FString response;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query", AutoCreateRefTerm = "parameters"), Category = "Neo4j")
	void submitQuery(FString query, Neo4jOperation operation, FString transactionID, TMap<FString, FString> parameters, FString database);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	// --- Transport-agnostic ---
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

	// --- WebSocket transport (UseSSL == false) ---
	TSharedPtr<IWebSocket> WebSocket;
	void OnWebSocketConnected();
	void OnWebSocketConnectionError(const FString& Error);
	void OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
	void OnWebSocketBinaryMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining);

	// --- TCP+TLS transport (UseSSL == true) ---
	void* SslCtx = nullptr;    // SSL_CTX*
	void* SslHandle = nullptr; // SSL*
	void* SslBio = nullptr;    // BIO* (owns the socket)
	FRunnableThread* RecvThread = nullptr;
	std::atomic<bool> bRecvThreadRunning{false};
	void TcpSslConnect(const FString& Hostname, int32 InPort);
	void TcpSslDisconnect();
	void TcpRecvLoop();

	// --- Transport dispatch ---
	void SendRawBytes(const uint8* Data, int32 Len);
	void OnDataReceived(const void* Data, SIZE_T Size);

	// --- Bolt protocol (transport-agnostic) ---
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

	// --- Helpers ---
	FString ExtractHostname(const FString& Url);
	bool ShouldUseSSL(const FString& Url);

	friend class FNeo4jRecvRunnable;
};
