/**
 * @file Neo4jComponent.cpp
 * @brief Implementation of UNeo4jComponent — Bolt handshake, transport, query dispatch, and result conversion.
 */

#include "Neo4jComponent.h"
#include "BoltProtocol.h"
#include "WebSocketsModule.h"
#include "Async/Async.h"

// OpenSSL's ossl_typ.h defines 'UI' which conflicts with UE's UI namespace
#define UI UI_ST
THIRD_PARTY_INCLUDES_START
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
THIRD_PARTY_INCLUDES_END
#undef UI

UNeo4jComponent::UNeo4jComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	port = 7687;
}

// ============================================================================
// Helpers
// ============================================================================

FString UNeo4jComponent::ExtractHostname(const FString& Url)
{
	FString Host = Url;
	int32 SchemeEnd = Host.Find(TEXT("://"));
	if (SchemeEnd != INDEX_NONE) Host = Host.Mid(SchemeEnd + 3);
	int32 PortPos = Host.Find(TEXT(":"));
	if (PortPos != INDEX_NONE) Host = Host.Left(PortPos);
	int32 SlashPos = Host.Find(TEXT("/"));
	if (SlashPos != INDEX_NONE) Host = Host.Left(SlashPos);
	return Host;
}

bool UNeo4jComponent::ShouldUseSSL(const FString& Url)
{
	return Url.StartsWith(TEXT("neo4j+s://")) || Url.StartsWith(TEXT("neo4j+ssc://"))
		|| Url.StartsWith(TEXT("bolt+s://")) || Url.StartsWith(TEXT("bolt+ssc://"))
		|| Url.StartsWith(TEXT("https://")) || Url.StartsWith(TEXT("wss://"));
}

// ============================================================================
// Lifecycle
// ============================================================================

void UNeo4jComponent::BeginPlay()
{
	Super::BeginPlay();
	Dechunker = MakeUnique<FBoltDechunker>();

	// Auto-detect SSL from endpoint scheme
	if (ShouldUseSSL(endpoint))
		UseSSL = true;
	else if (endpoint.StartsWith(TEXT("neo4j://")) || endpoint.StartsWith(TEXT("bolt://"))
		|| endpoint.StartsWith(TEXT("http://")) || endpoint.StartsWith(TEXT("ws://")))
		UseSSL = false;
	// else: respect the UseSSL property as configured

	if (UseSSL)
	{
		FString Hostname = ExtractHostname(endpoint);
		UE_LOG(LogTemp, Log, TEXT("Neo4j: Connecting via TCP+TLS to %s:%d"), *Hostname, port);
		ConnectionState = EBoltConnectionState::Connecting;
		TcpSslConnect(Hostname, port);
	}
	else
	{
		FWebSocketsModule::Get();

		FString WsUrl = endpoint;
		if (WsUrl.StartsWith(TEXT("neo4j+s://")) || WsUrl.StartsWith(TEXT("neo4j+ssc://")))
			WsUrl = TEXT("wss://") + WsUrl.Mid(WsUrl.Find(TEXT("://")) + 3);
		else if (WsUrl.StartsWith(TEXT("neo4j://")))
			WsUrl = TEXT("ws://") + WsUrl.Mid(8);
		else if (WsUrl.StartsWith(TEXT("bolt+s://")) || WsUrl.StartsWith(TEXT("bolt+ssc://")))
			WsUrl = TEXT("wss://") + WsUrl.Mid(WsUrl.Find(TEXT("://")) + 3);
		else if (WsUrl.StartsWith(TEXT("bolt://")))
			WsUrl = TEXT("ws://") + WsUrl.Mid(7);
		else if (WsUrl.StartsWith(TEXT("http://")))
			WsUrl = TEXT("ws://") + WsUrl.Mid(7);
		else if (WsUrl.StartsWith(TEXT("https://")))
			WsUrl = TEXT("wss://") + WsUrl.Mid(8);
		else if (!WsUrl.StartsWith(TEXT("ws://")) && !WsUrl.StartsWith(TEXT("wss://")))
			WsUrl = TEXT("ws://") + WsUrl;

		WsUrl += TEXT(":") + FString::FromInt(port);

		WebSocket = FWebSocketsModule::Get().CreateWebSocket(WsUrl, TEXT(""));
		WebSocket->OnConnected().AddUObject(this, &UNeo4jComponent::OnWebSocketConnected);
		WebSocket->OnConnectionError().AddUObject(this, &UNeo4jComponent::OnWebSocketConnectionError);
		WebSocket->OnClosed().AddUObject(this, &UNeo4jComponent::OnWebSocketClosed);
		WebSocket->OnRawMessage().AddUObject(this, &UNeo4jComponent::OnWebSocketBinaryMessage);

		UE_LOG(LogTemp, Log, TEXT("Neo4j: Connecting via WebSocket to %s"), *WsUrl);
		ConnectionState = EBoltConnectionState::Connecting;
		WebSocket->Connect();
	}
}

void UNeo4jComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Clean close: RESET (kills open tx) + GOODBYE (releases connection slot)
	if (ConnectionState != EBoltConnectionState::Closed && ConnectionState != EBoltConnectionState::Disconnected)
	{
		if (ConnectionState == EBoltConnectionState::TxReady || ConnectionState == EBoltConnectionState::TxStreaming
			|| ConnectionState == EBoltConnectionState::Streaming || ConnectionState == EBoltConnectionState::Failed)
			SendChunkedMessage(BoltMessages::BuildReset());

		SendChunkedMessage(BoltMessages::BuildGoodbye());

		// Give the server a moment to process GOODBYE before we tear down the socket
		if (UseSSL && SslBio)
			BIO_flush(static_cast<BIO*>(SslBio));
	}

	if (UseSSL)
	{
		TcpSslDisconnect();
	}
	else
	{
		if (WebSocket.IsValid() && WebSocket->IsConnected())
			WebSocket->Close();
	}
	ConnectionState = EBoltConnectionState::Closed;
	Super::EndPlay(EndPlayReason);
}

void UNeo4jComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// ============================================================================
// TCP+TLS Transport
// ============================================================================

// Background receive thread runnable — must be defined before TcpSslConnect uses it
class FNeo4jRecvRunnable : public FRunnable
{
public:
	FNeo4jRecvRunnable(UNeo4jComponent* InOwner) : Owner(InOwner) {}
	virtual uint32 Run() override { Owner->TcpRecvLoop(); return 0; }
private:
	UNeo4jComponent* Owner;
};

void UNeo4jComponent::TcpSslConnect(const FString& Hostname, int32 InPort)
{
	// Initialize OpenSSL context
	SSL_CTX* Ctx = SSL_CTX_new(TLS_client_method());
	if (!Ctx)
	{
		UE_LOG(LogTemp, Error, TEXT("Neo4j: SSL_CTX_new failed"));
		ConnectionState = EBoltConnectionState::Closed;
		return;
	}
	SslCtx = Ctx;

	// Use OpenSSL's BIO for connection — it handles DNS, TCP connect, and TLS in one go
	BIO* Bio = BIO_new_ssl_connect(Ctx);
	if (!Bio)
	{
		UE_LOG(LogTemp, Error, TEXT("Neo4j: BIO_new_ssl_connect failed"));
		SSL_CTX_free(Ctx); SslCtx = nullptr;
		ConnectionState = EBoltConnectionState::Closed;
		return;
	}
	SslBio = Bio;

	// Get the SSL handle from the BIO chain
	SSL* Ssl = nullptr;
	BIO_get_ssl(Bio, &Ssl);
	if (!Ssl)
	{
		UE_LOG(LogTemp, Error, TEXT("Neo4j: BIO_get_ssl failed"));
		TcpSslDisconnect();
		return;
	}
	SslHandle = Ssl;
	SSL_set_mode(Ssl, SSL_MODE_AUTO_RETRY);

	// Set SNI hostname (required for Aura)
	SSL_set_tlsext_host_name(Ssl, TCHAR_TO_ANSI(*Hostname));

	// Set connection target
	FString ConnTarget = FString::Printf(TEXT("%s:%d"), *Hostname, InPort);
	BIO_set_conn_hostname(Bio, TCHAR_TO_ANSI(*ConnTarget));

	// Connect + TLS handshake
	if (BIO_do_connect(Bio) <= 0)
	{
		unsigned long ErrCode = ERR_get_error();
		char ErrBuf[256];
		ERR_error_string_n(ErrCode, ErrBuf, sizeof(ErrBuf));
		UE_LOG(LogTemp, Error, TEXT("Neo4j: BIO_do_connect failed to %s: %hs"), *ConnTarget, ErrBuf);
		TcpSslDisconnect();
		return;
	}

	if (BIO_do_handshake(Bio) <= 0)
	{
		unsigned long ErrCode = ERR_get_error();
		char ErrBuf[256];
		ERR_error_string_n(ErrCode, ErrBuf, sizeof(ErrBuf));
		UE_LOG(LogTemp, Error, TEXT("Neo4j: TLS handshake failed: %hs"), ErrBuf);
		TcpSslDisconnect();
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Neo4j: TLS connected to %s"), *ConnTarget);

	// Send Bolt handshake
	ConnectionState = EBoltConnectionState::HandshakePending;
	HandshakeBuffer.Empty();
	SendBoltHandshake();

	// Start background receive thread
	bRecvThreadRunning.store(true);
	RecvThread = FRunnableThread::Create(
		new class FNeo4jRecvRunnable(this),
		TEXT("Neo4jRecvThread"));
}

void UNeo4jComponent::TcpRecvLoop()
{
	uint8 Buffer[16384];
	BIO* Bio = static_cast<BIO*>(SslBio);

	while (bRecvThreadRunning.load())
	{
		int BytesRead = BIO_read(Bio, Buffer, sizeof(Buffer));
		if (BytesRead > 0)
		{
			TArray<uint8> Data;
			Data.Append(Buffer, BytesRead);

			AsyncTask(ENamedThreads::GameThread, [this, RecvData = MoveTemp(Data)]()
			{
				if (ConnectionState != EBoltConnectionState::Closed)
					OnDataReceived(RecvData.GetData(), RecvData.Num());
			});
		}
		else if (BytesRead == 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Neo4j: Server closed connection"));
			AsyncTask(ENamedThreads::GameThread, [this]() { ConnectionState = EBoltConnectionState::Closed; });
			break;
		}
		else
		{
			if (!BIO_should_retry(Bio))
			{
				UE_LOG(LogTemp, Error, TEXT("Neo4j: BIO_read error"));
				AsyncTask(ENamedThreads::GameThread, [this]() { ConnectionState = EBoltConnectionState::Closed; });
				break;
			}
		}
	}
}

void UNeo4jComponent::TcpSslDisconnect()
{
	bRecvThreadRunning.store(false);

	// Shut down SSL to unblock the recv thread's BIO_read.
	// SSL_shutdown sends close_notify and causes BIO_read to return 0 or error.
	if (SslHandle)
	{
		SSL_shutdown(static_cast<SSL*>(SslHandle));
	}

	// Wait for recv thread to exit before freeing resources
	if (RecvThread)
	{
		RecvThread->WaitForCompletion();
		delete RecvThread;
		RecvThread = nullptr;
	}

	// Now safe to free — recv thread is no longer accessing the BIO
	if (SslBio)
	{
		BIO_free_all(static_cast<BIO*>(SslBio));
		SslBio = nullptr;
		SslHandle = nullptr; // freed by BIO_free_all
	}

	if (SslCtx)
	{
		SSL_CTX_free(static_cast<SSL_CTX*>(SslCtx));
		SslCtx = nullptr;
	}
}

// ============================================================================
// Transport Dispatch
// ============================================================================

void UNeo4jComponent::SendRawBytes(const uint8* Data, int32 Len)
{
	if (UseSSL)
	{
		if (SslBio)
		{
			BIO* Bio = static_cast<BIO*>(SslBio);
			int32 Sent = 0;
			while (Sent < Len)
			{
				int Written = BIO_write(Bio, Data + Sent, Len - Sent);
				if (Written <= 0)
				{
					if (!BIO_should_retry(Bio))
					{
						UE_LOG(LogTemp, Error, TEXT("Neo4j: BIO_write failed"));
						break;
					}
					continue;
				}
				Sent += Written;
			}
		}
	}
	else
	{
		if (WebSocket.IsValid())
			WebSocket->Send(Data, Len, true);
	}
}

void UNeo4jComponent::OnDataReceived(const void* Data, SIZE_T Size)
{
	if (ConnectionState == EBoltConnectionState::HandshakePending)
	{
		HandshakeBuffer.Append(static_cast<const uint8*>(Data), Size);
		if (HandshakeBuffer.Num() >= 4)
			HandleHandshakeResponse();
		return;
	}

	Dechunker->Accumulate(Data, Size);

	TArray<uint8> MsgData;
	while (Dechunker->PopMessage(MsgData))
	{
		FBoltServerMessage Msg = ParseBoltServerMessage(MsgData);
		HandleServerMessage(Msg);
	}
}

// ============================================================================
// WebSocket Callbacks (delegate to OnDataReceived)
// ============================================================================

void UNeo4jComponent::OnWebSocketConnected()
{
	UE_LOG(LogTemp, Log, TEXT("Neo4j: WebSocket connected, sending Bolt handshake"));
	ConnectionState = EBoltConnectionState::HandshakePending;
	HandshakeBuffer.Empty();
	SendBoltHandshake();
}

void UNeo4jComponent::OnWebSocketConnectionError(const FString& Error)
{
	UE_LOG(LogTemp, Error, TEXT("Neo4j: WebSocket connection error: %s"), *Error);
	ConnectionState = EBoltConnectionState::Closed;
}

void UNeo4jComponent::OnWebSocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean)
{
	UE_LOG(LogTemp, Log, TEXT("Neo4j: WebSocket closed (code=%d, reason=%s, clean=%d)"), StatusCode, *Reason, bWasClean);
	ConnectionState = EBoltConnectionState::Closed;
}

void UNeo4jComponent::OnWebSocketBinaryMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining)
{
	OnDataReceived(Data, Size);
}

// ============================================================================
// Bolt Handshake
// ============================================================================

void UNeo4jComponent::SendBoltHandshake()
{
	const TArray<uint8>& Handshake = BoltFraming::BuildHandshake();
	SendRawBytes(Handshake.GetData(), Handshake.Num());
}

void UNeo4jComponent::HandleHandshakeResponse()
{
	// Server response: 4 bytes in format [patch, range_or_zero, minor, major]
	uint8 B0 = HandshakeBuffer[0]; // patch
	uint8 B1 = HandshakeBuffer[1]; // range (0 in response)
	uint8 B2 = HandshakeBuffer[2]; // minor
	uint8 B3 = HandshakeBuffer[3]; // major

	if (B0 == 0 && B1 == 0 && B2 == 0 && B3 == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Neo4j: Bolt handshake failed - no compatible version"));
		ConnectionState = EBoltConnectionState::Closed;
		return;
	}

	NegotiatedBoltMajor = B3;
	NegotiatedBoltMinor = B2;

	UE_LOG(LogTemp, Log, TEXT("Neo4j: Bolt version negotiated: %d.%d"), NegotiatedBoltMajor, NegotiatedBoltMinor);
	ConnectionState = EBoltConnectionState::Authenticating;
	SendAuthentication();
}

void UNeo4jComponent::SendAuthentication()
{
	FString UserAgent = TEXT("FANTASIA/1.0 Unreal Engine");
	if (NegotiatedBoltMajor >= 5 && NegotiatedBoltMinor >= 3)
	{
		// Bolt 5.3+: HELLO with bolt_agent map (no auth), then LOGON
		SendChunkedMessage(BoltMessages::BuildHello53(UserAgent));
	}
	else if (NegotiatedBoltMajor >= 5 && NegotiatedBoltMinor >= 1)
	{
		// Bolt 5.1-5.2: HELLO with user_agent string (no auth), then LOGON
		SendChunkedMessage(BoltMessages::BuildHello51(UserAgent));
	}
	else
	{
		// Bolt 4.x / 5.0: HELLO with auth included
		SendChunkedMessage(BoltMessages::BuildHello(UserAgent, user, password));
	}
}

// ============================================================================
// State Machine (unchanged — transport-agnostic)
// ============================================================================

void UNeo4jComponent::HandleServerMessage(const FBoltServerMessage& Msg)
{
	switch (ConnectionState)
	{
	case EBoltConnectionState::Authenticating:
	{
		if (Msg.Tag == BoltMsg::SUCCESS)
		{
			if (NegotiatedBoltMajor >= 5 && NegotiatedBoltMinor >= 1)
			{
				// Bolt 5.1+: HELLO succeeded, now send LOGON with credentials
				ConnectionState = EBoltConnectionState::LogonPending;
				SendChunkedMessage(BoltMessages::BuildLogon(user, password));
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Neo4j: Authenticated (Bolt %d.%d)"), NegotiatedBoltMajor, NegotiatedBoltMinor);
				ConnectionState = EBoltConnectionState::Ready;
				ProcessNextCommand();
			}
		}
		else if (Msg.Tag == BoltMsg::FAILURE)
		{
			FString Code = Msg.Metadata.Contains(TEXT("code")) ? Msg.Metadata[TEXT("code")]->AsString() : TEXT("unknown");
			FString Message = Msg.Metadata.Contains(TEXT("message")) ? Msg.Metadata[TEXT("message")]->AsString() : TEXT("unknown");
			UE_LOG(LogTemp, Error, TEXT("Neo4j: Auth failed: %s - %s"), *Code, *Message);
			ConnectionState = EBoltConnectionState::Closed;
		}
		break;
	}

	case EBoltConnectionState::LogonPending:
	{
		if (Msg.Tag == BoltMsg::SUCCESS)
		{
			UE_LOG(LogTemp, Log, TEXT("Neo4j: Authenticated via LOGON (Bolt %d.%d)"), NegotiatedBoltMajor, NegotiatedBoltMinor);
			ConnectionState = EBoltConnectionState::Ready;
			ProcessNextCommand();
		}
		else if (Msg.Tag == BoltMsg::FAILURE)
		{
			FString Code = Msg.Metadata.Contains(TEXT("code")) ? Msg.Metadata[TEXT("code")]->AsString() : TEXT("unknown");
			FString Message = Msg.Metadata.Contains(TEXT("message")) ? Msg.Metadata[TEXT("message")]->AsString() : TEXT("unknown");
			UE_LOG(LogTemp, Error, TEXT("Neo4j: LOGON failed: %s - %s"), *Code, *Message);
			ConnectionState = EBoltConnectionState::Closed;
		}
		break;
	}

	case EBoltConnectionState::Ready:
	case EBoltConnectionState::TxReady:
	{
		if (Msg.Tag == BoltMsg::SUCCESS)
		{
			if (CurrentOperation == Neo4jOperation::BEGIN_TRANSACTION)
			{
				TransactionCounter++;
				ActiveTransactionID = FString::Printf(TEXT("bolt-%d"), TransactionCounter);
				ConnectionState = EBoltConnectionState::TxReady;
				FNeo4jResponse Neo4jResp;
				Neo4jResp.transactionID = ActiveTransactionID;
				IncomingResponse.Broadcast(Neo4jResp);
			}
			else if (CurrentOperation == Neo4jOperation::COMMIT_TRANSACTION)
			{
				FNeo4jResponse Neo4jResp;
				Neo4jResp.transactionID = ActiveTransactionID;
				ActiveTransactionID.Empty();
				ConnectionState = EBoltConnectionState::Ready;
				IncomingResponse.Broadcast(Neo4jResp);
			}
			else if (CurrentOperation == Neo4jOperation::ROLLBACK_TRANSACTION)
			{
				FNeo4jResponse Neo4jResp;
				Neo4jResp.transactionID = ActiveTransactionID;
				ActiveTransactionID.Empty();
				ConnectionState = EBoltConnectionState::Ready;
				IncomingResponse.Broadcast(Neo4jResp);
			}
			ProcessNextCommand();
		}
		else if (Msg.Tag == BoltMsg::FAILURE)
		{
			FString Code = Msg.Metadata.Contains(TEXT("code")) ? Msg.Metadata[TEXT("code")]->AsString() : TEXT("unknown");
			FString Message = Msg.Metadata.Contains(TEXT("message")) ? Msg.Metadata[TEXT("message")]->AsString() : TEXT("unknown");
			UE_LOG(LogTemp, Error, TEXT("Neo4j: Query failed: %s - %s"), *Code, *Message);
			ConnectionState = EBoltConnectionState::Failed;
			SendChunkedMessage(BoltMessages::BuildReset());
		}
		break;
	}

	case EBoltConnectionState::Streaming:
	case EBoltConnectionState::TxStreaming:
	{
		if (QueryPhase == EBoltQueryPhase::WaitingRunSuccess)
		{
			if (Msg.Tag == BoltMsg::SUCCESS)
			{
				CurrentFieldNames.Empty();
				if (Msg.Metadata.Contains(TEXT("fields")))
				{
					const FBoltValuePtr& FieldsVal = Msg.Metadata[TEXT("fields")];
					if (FieldsVal && FieldsVal->Type == EBoltValueType::List)
					{
						CurrentFieldNames.Reserve(FieldsVal->ListVal.Num());
						for (const FBoltValuePtr& F : FieldsVal->ListVal)
							CurrentFieldNames.Add(F->StringVal);
					}
				}
				QueryPhase = EBoltQueryPhase::WaitingPullRecords;
			}
			else if (Msg.Tag == BoltMsg::FAILURE)
			{
				FString Code = Msg.Metadata.Contains(TEXT("code")) ? Msg.Metadata[TEXT("code")]->AsString() : TEXT("unknown");
				FString Message = Msg.Metadata.Contains(TEXT("message")) ? Msg.Metadata[TEXT("message")]->AsString() : TEXT("unknown");
				UE_LOG(LogTemp, Error, TEXT("Neo4j: RUN failed: %s - %s"), *Code, *Message);
				QueryPhase = EBoltQueryPhase::Idle;
				ConnectionState = EBoltConnectionState::Failed;
				SendChunkedMessage(BoltMessages::BuildReset());
			}
		}
		else if (QueryPhase == EBoltQueryPhase::WaitingPullRecords)
		{
			if (Msg.Tag == BoltMsg::RECORD)
			{
				CurrentRecords.Emplace(MoveTemp(const_cast<FBoltServerMessage&>(Msg).Fields));
			}
			else if (Msg.Tag == BoltMsg::SUCCESS)
			{
				FNeo4jResponse Neo4jResp = ConvertBoltRecordsToResponse();
				QueryPhase = EBoltQueryPhase::Idle;
				ConnectionState = (ConnectionState == EBoltConnectionState::TxStreaming)
					? EBoltConnectionState::TxReady : EBoltConnectionState::Ready;
				IncomingResponse.Broadcast(Neo4jResp);
				ProcessNextCommand();
			}
			else if (Msg.Tag == BoltMsg::FAILURE)
			{
				FString Code = Msg.Metadata.Contains(TEXT("code")) ? Msg.Metadata[TEXT("code")]->AsString() : TEXT("unknown");
				FString Message = Msg.Metadata.Contains(TEXT("message")) ? Msg.Metadata[TEXT("message")]->AsString() : TEXT("unknown");
				UE_LOG(LogTemp, Error, TEXT("Neo4j: PULL failed: %s - %s"), *Code, *Message);
				QueryPhase = EBoltQueryPhase::Idle;
				ConnectionState = EBoltConnectionState::Failed;
				SendChunkedMessage(BoltMessages::BuildReset());
			}
		}
		break;
	}

	case EBoltConnectionState::Failed:
	{
		if (Msg.Tag == BoltMsg::SUCCESS)
		{
			UE_LOG(LogTemp, Log, TEXT("Neo4j: Connection reset, returning to Ready"));
			ActiveTransactionID.Empty();
			ConnectionState = EBoltConnectionState::Ready;
			ProcessNextCommand();
		}
		else if (Msg.Tag == BoltMsg::FAILURE)
		{
			UE_LOG(LogTemp, Error, TEXT("Neo4j: RESET failed, closing connection"));
			ConnectionState = EBoltConnectionState::Closed;
		}
		break;
	}

	default:
		break;
	}
}

// ============================================================================
// Command Queue
// ============================================================================

void UNeo4jComponent::submitQuery(FString query, Neo4jOperation operation, FString transactionID, TMap<FString, FString> parameters, FString database)
{
	if (database.IsEmpty())
		database = TEXT("neo4j");

	FBoltPendingCommand Cmd;
	Cmd.Operation = operation;
	Cmd.Query = query;
	Cmd.Parameters = parameters;
	Cmd.Database = database;
	Cmd.TransactionID = transactionID;

	if (ConnectionState == EBoltConnectionState::Ready || ConnectionState == EBoltConnectionState::TxReady)
		DispatchCommand(Cmd);
	else
		PendingCommands.Add(MoveTemp(Cmd));
}

void UNeo4jComponent::ProcessNextCommand()
{
	if (PendingCommandIndex >= PendingCommands.Num()) return;
	if (ConnectionState != EBoltConnectionState::Ready && ConnectionState != EBoltConnectionState::TxReady) return;

	FBoltPendingCommand Cmd = MoveTemp(PendingCommands[PendingCommandIndex]);
	PendingCommandIndex++;
	if (PendingCommandIndex == PendingCommands.Num()) { PendingCommands.Empty(); PendingCommandIndex = 0; }
	DispatchCommand(Cmd);
}

void UNeo4jComponent::DispatchCommand(const FBoltPendingCommand& Cmd)
{
	CurrentOperation = Cmd.Operation;
	CurrentDatabase = Cmd.Database;
	CurrentRecords.Reset();
	CurrentFieldNames.Reset();

	FBoltValueMap BoltParams = ConvertParameters(Cmd.Parameters);

	switch (Cmd.Operation)
	{
	case Neo4jOperation::SINGLE_REQUEST:
	{
		FBoltValueMap Extra;
		Extra.Add(TEXT("db"), FBoltValue::MakeString(Cmd.Database));
		ConnectionState = EBoltConnectionState::Streaming;
		QueryPhase = EBoltQueryPhase::WaitingRunSuccess;
		TArray<uint8> Pipelined = BoltMessages::BuildRunAndPull(Cmd.Query, BoltParams, Extra);
		SendRawBytes(Pipelined.GetData(), Pipelined.Num());
		break;
	}
	case Neo4jOperation::BEGIN_TRANSACTION:
		SendChunkedMessage(BoltMessages::BuildBegin(Cmd.Database));
		break;
	case Neo4jOperation::ADD_TO_TRANSACTION:
	{
		FBoltValueMap Extra;
		ConnectionState = EBoltConnectionState::TxStreaming;
		QueryPhase = EBoltQueryPhase::WaitingRunSuccess;
		TArray<uint8> Pipelined = BoltMessages::BuildRunAndPull(Cmd.Query, BoltParams, Extra);
		SendRawBytes(Pipelined.GetData(), Pipelined.Num());
		break;
	}
	case Neo4jOperation::COMMIT_TRANSACTION:
		SendChunkedMessage(BoltMessages::BuildCommit());
		break;
	case Neo4jOperation::ROLLBACK_TRANSACTION:
		SendChunkedMessage(BoltMessages::BuildRollback());
		break;
	default:
		break;
	}
}

void UNeo4jComponent::SendChunkedMessage(const TArray<uint8>& MessageData)
{
	TArray<uint8> Chunked = BoltFraming::ChunkMessage(MessageData);
	SendRawBytes(Chunked.GetData(), Chunked.Num());
}

// ============================================================================
// Parameter Conversion
// ============================================================================

FBoltValueMap UNeo4jComponent::ConvertParameters(const TMap<FString, FString>& InParams)
{
	FBoltValueMap Out;
	for (const auto& Pair : InParams)
	{
		const FString& Val = Pair.Value;
		if (Val.StartsWith(TEXT("[")))
		{
			FBoltValueArray Items;
			FString Trimmed = Val.Mid(1, Val.Len() - 2);
			TArray<FString> Parts;
			Trimmed.ParseIntoArray(Parts, TEXT(","));
			for (FString& Part : Parts)
			{
				Part.TrimStartAndEndInline();
				Part = Part.Replace(TEXT("\""), TEXT(""));
				Items.Add(FBoltValue::MakeString(Part));
			}
			Out.Add(Pair.Key, FBoltValue::MakeList(MoveTemp(Items)));
		}
		else
			Out.Add(Pair.Key, FBoltValue::MakeString(Val));
	}
	return Out;
}

// ============================================================================
// Response Conversion
// ============================================================================

FNeo4jResponse UNeo4jComponent::ConvertBoltRecordsToResponse()
{
	FNeo4jResponse Resp;
	Resp.transactionID = ActiveTransactionID;
	Resp.headers = CurrentFieldNames;

	for (const FBoltValueArray& RecordFields : CurrentRecords)
	{
		UNeo4jResultRow* Row = NewObject<UNeo4jResultRow>();
		for (int32 i = 0; i < Resp.headers.Num() && i < RecordFields.Num(); i++)
			Row->cells.Add(Resp.headers[i], ConvertBoltValueToCell(RecordFields[i]));
		Resp.rows.Add(Row);
	}
	return Resp;
}

UNeo4jResultCell* UNeo4jComponent::ConvertBoltValueToCell(const FBoltValuePtr& Value)
{
	if (Value && Value->Type == EBoltValueType::Structure)
	{
		const FBoltStructure& S = Value->StructVal;
		if (S.Tag == BoltStruct::NODE && S.Fields.Num() >= 3)
		{
			UNeo4jResultCellNode* Cell = NewObject<UNeo4jResultCellNode>();
			Cell->id = static_cast<int>(S.Fields[0]->IntVal);
			if (S.Fields[1]->Type == EBoltValueType::List)
				for (const auto& Label : S.Fields[1]->ListVal)
					Cell->labels.Add(Label->StringVal);
			if (S.Fields[2]->Type == EBoltValueType::Map)
			{
				for (const auto& Prop : S.Fields[2]->MapVal)
				{
					if (Prop.Value->Type == EBoltValueType::List)
					{
						FString List;
						for (const auto& Item : Prop.Value->ListVal)
						{
							if (!List.IsEmpty()) List += TEXT("|");
							List += Item->AsString();
						}
						Cell->properties.Add(Prop.Key, List);
					}
					else
						Cell->properties.Add(Prop.Key, Prop.Value->AsString());
				}
			}
			return Cell;
		}
		else if (S.Tag == BoltStruct::RELATIONSHIP && S.Fields.Num() >= 5)
		{
			UNeo4jResultCellRelationship* Cell = NewObject<UNeo4jResultCellRelationship>();
			Cell->id = static_cast<int>(S.Fields[0]->IntVal);
			Cell->label = S.Fields[3]->StringVal;
			if (S.Fields[4]->Type == EBoltValueType::Map)
			{
				for (const auto& Prop : S.Fields[4]->MapVal)
				{
					if (Prop.Value->Type == EBoltValueType::List)
					{
						FString List;
						for (const auto& Item : Prop.Value->ListVal)
						{
							if (!List.IsEmpty()) List += TEXT("|");
							List += Item->AsString();
						}
						Cell->properties.Add(Prop.Key, List);
					}
					else
						Cell->properties.Add(Prop.Key, Prop.Value->AsString());
				}
			}
			return Cell;
		}
	}

	UNeo4jResultCellSimple* Cell = NewObject<UNeo4jResultCellSimple>();
	Cell->value = Value ? Value->AsString() : TEXT("");
	return Cell;
}
