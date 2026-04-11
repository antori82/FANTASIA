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

// ----------------------------------------------------------------------------
// Hot-path helpers (file-scope)
// ----------------------------------------------------------------------------

/** Extract a string field from a Bolt metadata map with a single lookup. */
static FString GetMetadataString(const FBoltValueMap& Metadata, const TCHAR* Key, const TCHAR* DefaultValue = TEXT("unknown"))
{
	if (const FBoltValuePtr* Ptr = Metadata.Find(Key))
	{
		if (*Ptr) return (*Ptr)->AsString();
	}
	return DefaultValue;
}

/** Copy a Bolt property map into a UObject string→string map with reserve + list join. */
static void CopyBoltPropertiesToMap(const FBoltValueMap& Src, TMap<FString, FString>& Dest)
{
	Dest.Reserve(Src.Num());
	for (const auto& Prop : Src)
	{
		if (!Prop.Value) continue;
		if (Prop.Value->Type == EBoltValueType::List)
		{
			// Pipe-join list values into a single string.
			const FBoltValueArray& Items = Prop.Value->ListVal;
			FString Joined;
			const int32 ItemCount = Items.Num();
			for (int32 i = 0; i < ItemCount; i++)
			{
				if (i > 0) Joined += TEXT("|");
				if (Items[i]) Joined += Items[i]->AsString();
			}
			Dest.Add(Prop.Key, MoveTemp(Joined));
		}
		else
		{
			Dest.Add(Prop.Key, Prop.Value->AsString());
		}
	}
}

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

bool UNeo4jComponent::SchemeRequiresRouting(const FString& Url)
{
	// neo4j:// / neo4j+s:// / neo4j+ssc:// all require the routing protocol.
	// bolt:// / bolt+s:// / bolt+ssc:// are direct connections.
	return Url.StartsWith(TEXT("neo4j://")) || Url.StartsWith(TEXT("neo4j+s://")) || Url.StartsWith(TEXT("neo4j+ssc://"));
}

// ============================================================================
// Lifecycle
// ============================================================================

void UNeo4jComponent::BeginPlay()
{
	Super::BeginPlay();

	// Auto-detect SSL from endpoint scheme
	if (ShouldUseSSL(endpoint))
		UseSSL = true;
	else if (endpoint.StartsWith(TEXT("bolt://"))
		|| endpoint.StartsWith(TEXT("http://")) || endpoint.StartsWith(TEXT("ws://")))
		UseSSL = false;
	// else: respect the UseSSL property as configured

	// Detect whether the URL scheme requires the Bolt routing protocol
	// (neo4j://, neo4j+s://, neo4j+ssc://). These are used by clustered
	// deployments and Neo4j Aura and require discovering a backend server
	// via dbms.routing.getRoutingTable before any Cypher query can run.
	bNeedsRouting = SchemeRequiresRouting(endpoint);
	bRoutingDone = false;

	const FString Hostname = ExtractHostname(endpoint);
	InitiateConnection(Hostname, port);
}

void UNeo4jComponent::InitiateConnection(const FString& Hostname, int32 InPort)
{
	// Reset per-connection state (chunker, handshake buffer, phase flags).
	Dechunker = MakeUnique<FBoltDechunker>();
	HandshakeBuffer.Empty();
	QueryPhase = EBoltQueryPhase::Idle;
	RoutingPhase = EBoltRoutingPhase::Idle;
	NegotiatedBoltMajor = 0;
	NegotiatedBoltMinor = 0;

	ActiveHostname = Hostname;
	ActivePort = InPort;

	if (UseSSL)
	{
		++ConnectionEpoch;
		UE_LOG(LogTemp, Log, TEXT("Neo4j: Connecting via TCP+TLS to %s:%d"), *Hostname, InPort);
		ConnectionState = EBoltConnectionState::Connecting;
		TcpSslConnect(Hostname, InPort);
	}
	else
	{
		FWebSocketsModule::Get();

		// Build a ws:// / wss:// URL from a bare hostname (routing / reconnect path)
		// or from an existing full URL (original BeginPlay path).
		FString WsUrl = Hostname;
		if (WsUrl.Contains(TEXT("://")))
		{
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
		}
		else
		{
			WsUrl = TEXT("ws://") + WsUrl;
		}

		WsUrl += TEXT(":") + FString::FromInt(InPort);

		// Bump the epoch so any stale callbacks from a previously torn-down
		// socket will be filtered out in the OnWebSocket* handlers.
		const int32 Epoch = ++ConnectionEpoch;
		TWeakObjectPtr<UNeo4jComponent> WeakThis(this);

		WebSocket = FWebSocketsModule::Get().CreateWebSocket(WsUrl, TEXT(""));
		WebSocket->OnConnected().AddLambda([WeakThis, Epoch]()
		{
			if (UNeo4jComponent* Self = WeakThis.Get())
				Self->OnWebSocketConnected(Epoch);
		});
		WebSocket->OnConnectionError().AddLambda([WeakThis, Epoch](const FString& Error)
		{
			if (UNeo4jComponent* Self = WeakThis.Get())
				Self->OnWebSocketConnectionError(Epoch, Error);
		});
		WebSocket->OnClosed().AddLambda([WeakThis, Epoch](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			if (UNeo4jComponent* Self = WeakThis.Get())
				Self->OnWebSocketClosed(Epoch, StatusCode, Reason, bWasClean);
		});
		WebSocket->OnRawMessage().AddLambda([WeakThis, Epoch](const void* Data, SIZE_T Size, SIZE_T BytesRemaining)
		{
			if (UNeo4jComponent* Self = WeakThis.Get())
				Self->OnWebSocketBinaryMessage(Epoch, Data, Size, BytesRemaining);
		});

		UE_LOG(LogTemp, Log, TEXT("Neo4j: Connecting via WebSocket to %s"), *WsUrl);
		ConnectionState = EBoltConnectionState::Connecting;
		WebSocket->Connect();
	}
}

void UNeo4jComponent::TearDownCurrentConnection()
{
	// Send GOODBYE if we're still in an authenticated state (best-effort).
	if (ConnectionState != EBoltConnectionState::Closed
		&& ConnectionState != EBoltConnectionState::Disconnected
		&& ConnectionState != EBoltConnectionState::Connecting
		&& ConnectionState != EBoltConnectionState::HandshakePending)
	{
		const TArray<uint8>& GoodbyeFramed = BoltMessages::BuildGoodbyeFramed();
		SendRawBytes(GoodbyeFramed.GetData(), GoodbyeFramed.Num());
		if (UseSSL && SslBio)
			BIO_flush(static_cast<BIO*>(SslBio));
	}

	if (UseSSL)
	{
		TcpSslDisconnect();
	}
	else
	{
		if (WebSocket.IsValid())
		{
			if (WebSocket->IsConnected())
				WebSocket->Close();
			WebSocket.Reset();
		}
	}

	ConnectionState = EBoltConnectionState::Disconnected;
}

void UNeo4jComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Clean close: RESET (kills open tx) + GOODBYE (releases connection slot)
	if (ConnectionState != EBoltConnectionState::Closed && ConnectionState != EBoltConnectionState::Disconnected)
	{
		if (ConnectionState == EBoltConnectionState::TxReady || ConnectionState == EBoltConnectionState::TxStreaming
			|| ConnectionState == EBoltConnectionState::Streaming || ConnectionState == EBoltConnectionState::Failed)
		{
			const TArray<uint8>& ResetFramed = BoltMessages::BuildResetFramed();
			SendRawBytes(ResetFramed.GetData(), ResetFramed.Num());
		}

		const TArray<uint8>& GoodbyeFramed = BoltMessages::BuildGoodbyeFramed();
		SendRawBytes(GoodbyeFramed.GetData(), GoodbyeFramed.Num());

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

	// Snapshot the epoch at the time this thread was started. Any game-thread
	// tasks this loop dispatches will carry this epoch. When they run, they
	// check that the component is still on the same connection epoch — if we
	// have since torn down this connection and reconnected (e.g. during
	// routing), the old tasks are silently discarded.
	const int32 Epoch = ConnectionEpoch;
	TWeakObjectPtr<UNeo4jComponent> WeakThis(this);

	while (bRecvThreadRunning.load())
	{
		int BytesRead = BIO_read(Bio, Buffer, sizeof(Buffer));
		if (BytesRead > 0)
		{
			TArray<uint8> Data;
			Data.Append(Buffer, BytesRead);

			AsyncTask(ENamedThreads::GameThread, [WeakThis, Epoch, RecvData = MoveTemp(Data)]()
			{
				UNeo4jComponent* Self = WeakThis.Get();
				if (!Self || Self->ConnectionEpoch != Epoch) return;
				if (Self->ConnectionState != EBoltConnectionState::Closed)
					Self->OnDataReceived(RecvData.GetData(), RecvData.Num());
			});
		}
		else if (BytesRead == 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Neo4j: Server closed connection"));
			AsyncTask(ENamedThreads::GameThread, [WeakThis, Epoch]()
			{
				UNeo4jComponent* Self = WeakThis.Get();
				if (!Self || Self->ConnectionEpoch != Epoch) return;
				Self->ConnectionState = EBoltConnectionState::Closed;
			});
			break;
		}
		else
		{
			if (!BIO_should_retry(Bio))
			{
				UE_LOG(LogTemp, Error, TEXT("Neo4j: BIO_read error"));
				AsyncTask(ENamedThreads::GameThread, [WeakThis, Epoch]()
				{
					UNeo4jComponent* Self = WeakThis.Get();
					if (!Self || Self->ConnectionEpoch != Epoch) return;
					Self->ConnectionState = EBoltConnectionState::Closed;
				});
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

void UNeo4jComponent::OnWebSocketConnected(int32 Epoch)
{
	// Ignore callbacks from stale sockets (e.g. the frontend socket after
	// we've torn it down during routing reconnect).
	if (Epoch != ConnectionEpoch) return;

	UE_LOG(LogTemp, Log, TEXT("Neo4j: WebSocket connected, sending Bolt handshake"));
	ConnectionState = EBoltConnectionState::HandshakePending;
	HandshakeBuffer.Empty();
	SendBoltHandshake();
}

void UNeo4jComponent::OnWebSocketConnectionError(int32 Epoch, const FString& Error)
{
	if (Epoch != ConnectionEpoch) return;
	UE_LOG(LogTemp, Error, TEXT("Neo4j: WebSocket connection error: %s"), *Error);
	ConnectionState = EBoltConnectionState::Closed;
}

void UNeo4jComponent::OnWebSocketClosed(int32 Epoch, int32 StatusCode, const FString& Reason, bool bWasClean)
{
	// Stale close event from a previous connection — do not clobber the
	// state of the current (newly reconnected) socket.
	if (Epoch != ConnectionEpoch) return;
	UE_LOG(LogTemp, Log, TEXT("Neo4j: WebSocket closed (code=%d, reason=%s, clean=%d)"), StatusCode, *Reason, bWasClean);
	ConnectionState = EBoltConnectionState::Closed;
}

void UNeo4jComponent::OnWebSocketBinaryMessage(int32 Epoch, const void* Data, SIZE_T Size, SIZE_T BytesRemaining)
{
	if (Epoch != ConnectionEpoch) return;
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
				OnAuthenticationComplete();
			}
		}
		else if (Msg.Tag == BoltMsg::FAILURE)
		{
			UE_LOG(LogTemp, Error, TEXT("Neo4j: Auth failed: %s - %s"),
				*GetMetadataString(Msg.Metadata, TEXT("code")),
				*GetMetadataString(Msg.Metadata, TEXT("message")));
			ConnectionState = EBoltConnectionState::Closed;
		}
		break;
	}

	case EBoltConnectionState::LogonPending:
	{
		if (Msg.Tag == BoltMsg::SUCCESS)
		{
			UE_LOG(LogTemp, Log, TEXT("Neo4j: Authenticated via LOGON (Bolt %d.%d)"), NegotiatedBoltMajor, NegotiatedBoltMinor);
			OnAuthenticationComplete();
		}
		else if (Msg.Tag == BoltMsg::FAILURE)
		{
			UE_LOG(LogTemp, Error, TEXT("Neo4j: LOGON failed: %s - %s"),
				*GetMetadataString(Msg.Metadata, TEXT("code")),
				*GetMetadataString(Msg.Metadata, TEXT("message")));
			ConnectionState = EBoltConnectionState::Closed;
		}
		break;
	}

	case EBoltConnectionState::RoutingDiscovery:
	{
		HandleRoutingMessage(Msg);
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
			UE_LOG(LogTemp, Error, TEXT("Neo4j: Query failed: %s - %s"),
				*GetMetadataString(Msg.Metadata, TEXT("code")),
				*GetMetadataString(Msg.Metadata, TEXT("message")));
			ConnectionState = EBoltConnectionState::Failed;
			const TArray<uint8>& ResetFramed = BoltMessages::BuildResetFramed();
			SendRawBytes(ResetFramed.GetData(), ResetFramed.Num());
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
				CurrentFieldNames.Reset();
				if (const FBoltValuePtr* FieldsPtr = Msg.Metadata.Find(TEXT("fields")))
				{
					if (*FieldsPtr && (*FieldsPtr)->Type == EBoltValueType::List)
					{
						const FBoltValueArray& FieldList = (*FieldsPtr)->ListVal;
						CurrentFieldNames.Reserve(FieldList.Num());
						for (const FBoltValuePtr& F : FieldList)
							CurrentFieldNames.Add(F->StringVal);
					}
				}
				QueryPhase = EBoltQueryPhase::WaitingPullRecords;
			}
			else if (Msg.Tag == BoltMsg::FAILURE)
			{
				UE_LOG(LogTemp, Error, TEXT("Neo4j: RUN failed: %s - %s"),
					*GetMetadataString(Msg.Metadata, TEXT("code")),
					*GetMetadataString(Msg.Metadata, TEXT("message")));
				QueryPhase = EBoltQueryPhase::Idle;
				ConnectionState = EBoltConnectionState::Failed;
				const TArray<uint8>& ResetFramed = BoltMessages::BuildResetFramed();
				SendRawBytes(ResetFramed.GetData(), ResetFramed.Num());
			}
		}
		else if (QueryPhase == EBoltQueryPhase::WaitingPullRecords)
		{
			if (Msg.Tag == BoltMsg::RECORD)
			{
				// Move the record fields out of the message — Fields is a
				// TArray<TSharedPtr>, so this is a single pointer swap.
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
				UE_LOG(LogTemp, Error, TEXT("Neo4j: PULL failed: %s - %s"),
					*GetMetadataString(Msg.Metadata, TEXT("code")),
					*GetMetadataString(Msg.Metadata, TEXT("message")));
				QueryPhase = EBoltQueryPhase::Idle;
				ConnectionState = EBoltConnectionState::Failed;
				const TArray<uint8>& ResetFramed = BoltMessages::BuildResetFramed();
				SendRawBytes(ResetFramed.GetData(), ResetFramed.Num());
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
	// An empty database string means "use the server's default database".
	// The dispatch code below will omit the "db" extra entirely so the server
	// picks its own default (which may not be literally named "neo4j" — for
	// example on Neo4j Aura it's the instance ID).
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
		// Only include "db" when the caller actually specified a database;
		// otherwise the server uses its default.
		if (!Cmd.Database.IsEmpty())
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
	{
		const TArray<uint8>& Framed = BoltMessages::BuildCommitFramed();
		SendRawBytes(Framed.GetData(), Framed.Num());
		break;
	}
	case Neo4jOperation::ROLLBACK_TRANSACTION:
	{
		const TArray<uint8>& Framed = BoltMessages::BuildRollbackFramed();
		SendRawBytes(Framed.GetData(), Framed.Num());
		break;
	}
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
// Routing Discovery (Bolt routing for clustered / Aura deployments)
// ============================================================================

void UNeo4jComponent::OnAuthenticationComplete()
{
	// If the URL scheme is routing-aware and we haven't yet discovered the
	// backend server, send the routing query. Otherwise proceed to Ready.
	if (bNeedsRouting && !bRoutingDone)
	{
		ConnectionState = EBoltConnectionState::RoutingDiscovery;
		SendRoutingQuery();
	}
	else
	{
		ConnectionState = EBoltConnectionState::Ready;
		ProcessNextCommand();
	}
}

void UNeo4jComponent::SendRoutingQuery()
{
	// Determine which database the client wants — needed for routing so the
	// server can return the correct backend shard. We look at the first
	// pending command; if none are queued yet we fall back to "neo4j" which
	// is the default database name on most setups.
	FString TargetDatabase;
	if (PendingCommands.Num() > PendingCommandIndex)
		TargetDatabase = PendingCommands[PendingCommandIndex].Database;
	if (TargetDatabase.IsEmpty())
		TargetDatabase = TEXT("neo4j");

	// Build the call: CALL dbms.routing.getRoutingTable($context, $database)
	// - $context is an empty map (no client-side routing hints)
	// - $database is the string we want to route for
	const FString Query = TEXT("CALL dbms.routing.getRoutingTable($context, $database)");

	FBoltValueMap Params;
	FBoltValueMap EmptyContext;
	Params.Add(TEXT("context"), FBoltValue::MakeMap(MoveTemp(EmptyContext)));
	Params.Add(TEXT("database"), FBoltValue::MakeString(TargetDatabase));

	// The routing procedure lives in the "system" database on newer Neo4j
	// versions; older versions accept it from any database. Routing against
	// "system" works in both cases.
	FBoltValueMap Extra;
	Extra.Add(TEXT("db"), FBoltValue::MakeString(TEXT("system")));

	RoutingRecords.Reset();
	RoutingPhase = EBoltRoutingPhase::WaitingRunSuccess;

	UE_LOG(LogTemp, Log, TEXT("Neo4j: Sending routing discovery query for database '%s'"), *TargetDatabase);

	TArray<uint8> Pipelined = BoltMessages::BuildRunAndPull(Query, Params, Extra);
	SendRawBytes(Pipelined.GetData(), Pipelined.Num());
}

void UNeo4jComponent::HandleRoutingMessage(const FBoltServerMessage& Msg)
{
	if (RoutingPhase == EBoltRoutingPhase::WaitingRunSuccess)
	{
		if (Msg.Tag == BoltMsg::SUCCESS)
		{
			// RUN acknowledged; next messages will be RECORD(s) then final SUCCESS.
			RoutingPhase = EBoltRoutingPhase::WaitingPullRecords;
		}
		else if (Msg.Tag == BoltMsg::FAILURE)
		{
			UE_LOG(LogTemp, Error, TEXT("Neo4j: Routing query RUN failed: %s - %s"),
				*GetMetadataString(Msg.Metadata, TEXT("code")),
				*GetMetadataString(Msg.Metadata, TEXT("message")));
			RoutingPhase = EBoltRoutingPhase::Idle;
			ConnectionState = EBoltConnectionState::Failed;
			const TArray<uint8>& ResetFramed = BoltMessages::BuildResetFramed();
			SendRawBytes(ResetFramed.GetData(), ResetFramed.Num());
		}
		return;
	}

	if (RoutingPhase == EBoltRoutingPhase::WaitingPullRecords)
	{
		if (Msg.Tag == BoltMsg::RECORD)
		{
			RoutingRecords.Emplace(MoveTemp(const_cast<FBoltServerMessage&>(Msg).Fields));
		}
		else if (Msg.Tag == BoltMsg::SUCCESS)
		{
			// PULL complete — we should have exactly one record with [ttl, servers, db?].
			FString WriteAddress;
			for (const FBoltValueArray& Record : RoutingRecords)
			{
				WriteAddress = PickWriteAddressFromRoutingRecord(Record);
				if (!WriteAddress.IsEmpty())
					break;
			}

			RoutingPhase = EBoltRoutingPhase::Idle;
			RoutingRecords.Reset();

			if (WriteAddress.IsEmpty())
			{
				UE_LOG(LogTemp, Error, TEXT("Neo4j: Routing table returned no WRITE server address"));
				ConnectionState = EBoltConnectionState::Closed;
				return;
			}

			UE_LOG(LogTemp, Log, TEXT("Neo4j: Routing discovered backend address '%s'"), *WriteAddress);
			bRoutingDone = true;
			ReconnectToBackendAddress(WriteAddress);
		}
		else if (Msg.Tag == BoltMsg::FAILURE)
		{
			UE_LOG(LogTemp, Error, TEXT("Neo4j: Routing query PULL failed: %s - %s"),
				*GetMetadataString(Msg.Metadata, TEXT("code")),
				*GetMetadataString(Msg.Metadata, TEXT("message")));
			RoutingPhase = EBoltRoutingPhase::Idle;
			ConnectionState = EBoltConnectionState::Failed;
			const TArray<uint8>& ResetFramed = BoltMessages::BuildResetFramed();
			SendRawBytes(ResetFramed.GetData(), ResetFramed.Num());
		}
	}
}

FString UNeo4jComponent::PickWriteAddressFromRoutingRecord(const FBoltValueArray& RecordFields)
{
	// Neo4j's dbms.routing.getRoutingTable returns a record with columns:
	//   [0] ttl :: INTEGER
	//   [1] servers :: LIST OF MAP { addresses: LIST OF STRING, role: STRING }
	//   [2] db :: STRING (optional, Neo4j 4.3+)
	//
	// We scan the servers list, find a WRITE entry, and return the first
	// "host:port" address from its addresses list.
	if (RecordFields.Num() < 2) return FString();

	const FBoltValuePtr& ServersVal = RecordFields[1];
	if (!ServersVal || ServersVal->Type != EBoltValueType::List) return FString();

	FString FirstWrite, FirstRead, FirstRoute;

	for (const FBoltValuePtr& ServerEntry : ServersVal->ListVal)
	{
		if (!ServerEntry || ServerEntry->Type != EBoltValueType::Map) continue;

		const FBoltValueMap& EntryMap = ServerEntry->MapVal;
		const FBoltValuePtr* RolePtr = EntryMap.Find(TEXT("role"));
		const FBoltValuePtr* AddrPtr = EntryMap.Find(TEXT("addresses"));
		if (!RolePtr || !AddrPtr || !(*RolePtr) || !(*AddrPtr)) continue;

		const FString Role = (*RolePtr)->StringVal;
		if ((*AddrPtr)->Type != EBoltValueType::List || (*AddrPtr)->ListVal.Num() == 0) continue;

		const FString FirstAddr = (*AddrPtr)->ListVal[0]->StringVal;
		if (Role == TEXT("WRITE") && FirstWrite.IsEmpty())      FirstWrite = FirstAddr;
		else if (Role == TEXT("READ") && FirstRead.IsEmpty())   FirstRead = FirstAddr;
		else if (Role == TEXT("ROUTE") && FirstRoute.IsEmpty()) FirstRoute = FirstAddr;
	}

	// Prefer WRITE, fall back to READ, then ROUTE.
	if (!FirstWrite.IsEmpty()) return FirstWrite;
	if (!FirstRead.IsEmpty())  return FirstRead;
	return FirstRoute;
}

void UNeo4jComponent::ReconnectToBackendAddress(const FString& AddressHostPort)
{
	// Parse "host:port" (IPv4 or hostname). IPv6 with brackets isn't expected
	// from routing output in practice.
	FString BackendHost = AddressHostPort;
	int32 BackendPort = port;
	int32 Colon = BackendHost.Find(TEXT(":"), ESearchCase::CaseSensitive, ESearchDir::FromEnd);
	if (Colon != INDEX_NONE)
	{
		BackendPort = FCString::Atoi(*BackendHost.Mid(Colon + 1));
		BackendHost = BackendHost.Left(Colon);
	}

	// Tear down the frontend connection first (GOODBYE + close socket).
	TearDownCurrentConnection();

	// Now reconnect to the backend host:port using the same transport mode
	// (TCP+TLS or WebSocket). The new connection will do handshake + HELLO +
	// LOGON again; since bRoutingDone is now true, OnAuthenticationComplete
	// will skip routing and go straight to Ready, dispatching any queued
	// pending commands.
	InitiateConnection(BackendHost, BackendPort);
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
	// Move field names into the response — CurrentFieldNames will be reset on
	// the next DispatchCommand, so there's no need to keep a copy here.
	Resp.headers = MoveTemp(CurrentFieldNames);

	const int32 NumRows = CurrentRecords.Num();
	const int32 NumCols = Resp.headers.Num();
	Resp.rows.Reserve(NumRows);

	for (FBoltValueArray& RecordFields : CurrentRecords)
	{
		UNeo4jResultRow* Row = NewObject<UNeo4jResultRow>();
		const int32 RecordNum = RecordFields.Num();
		const int32 Lim = FMath::Min(NumCols, RecordNum);
		Row->cells.Reserve(Lim);
		for (int32 i = 0; i < Lim; i++)
			Row->cells.Add(Resp.headers[i], ConvertBoltValueToCell(RecordFields[i]));
		Resp.rows.Add(Row);
	}

	// We've consumed all records — drop them so the next query starts clean.
	CurrentRecords.Reset();
	return Resp;
}

UNeo4jResultCell* UNeo4jComponent::ConvertBoltValueToCell(const FBoltValuePtr& Value)
{
	if (Value && Value->Type == EBoltValueType::Structure)
	{
		const FBoltStructure& S = Value->StructVal;
		const int32 NumFields = S.Fields.Num();

		if (S.Tag == BoltStruct::NODE && NumFields >= 3)
		{
			UNeo4jResultCellNode* Cell = NewObject<UNeo4jResultCellNode>();
			Cell->id = static_cast<int>(S.Fields[0]->IntVal);

			// Labels (Field 1 — list of strings)
			if (S.Fields[1]->Type == EBoltValueType::List)
			{
				const FBoltValueArray& Labels = S.Fields[1]->ListVal;
				Cell->labels.Reserve(Labels.Num());
				for (const FBoltValuePtr& Label : Labels)
					if (Label) Cell->labels.Add(Label->StringVal);
			}

			// Properties (Field 2 — map)
			if (S.Fields[2]->Type == EBoltValueType::Map)
				CopyBoltPropertiesToMap(S.Fields[2]->MapVal, Cell->properties);

			return Cell;
		}
		else if (S.Tag == BoltStruct::RELATIONSHIP && NumFields >= 5)
		{
			UNeo4jResultCellRelationship* Cell = NewObject<UNeo4jResultCellRelationship>();
			Cell->id = static_cast<int>(S.Fields[0]->IntVal);
			Cell->label = S.Fields[3]->StringVal;

			// Properties (Field 4 — map)
			if (S.Fields[4]->Type == EBoltValueType::Map)
				CopyBoltPropertiesToMap(S.Fields[4]->MapVal, Cell->properties);

			return Cell;
		}
	}

	UNeo4jResultCellSimple* Cell = NewObject<UNeo4jResultCellSimple>();
	Cell->value = Value ? Value->AsString() : TEXT("");
	return Cell;
}
