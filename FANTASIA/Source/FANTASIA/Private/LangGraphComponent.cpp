/**
 * @file LangGraphComponent.cpp
 * @brief Implementation of ULangGraphComponent -- thread-based LangGraph agent queries.
 */

// Fill out your copyright notice in the Description page of Project Settings.


#include "LangGraphComponent.h"
#include "Misc/Base64.h"
#include "Async/Async.h"

// All broadcasts in this file fire from inside HTTP callbacks
// (OnRequestProgress64 / OnProcessRequestComplete), which are invoked by
// FHttpManager::Tick while it is iterating its global Requests array.
// If a Blueprint listener responds by calling something that creates a
// new HTTP request -- e.g. RESTTTSComponent::TTSSynthesize -> IssueHttpRequest
// -> HttpRequest->ProcessRequest() -> FHttpManager::AddRequest -- the
// Requests array mutates mid-iteration and the engine ensures with
// "Array has changed during ranged-for iteration!". The iterator state
// is then corrupt, so the very next progress callback dereferences a
// freed pointer (sentinel 0xFFFFFFFFFFFFFFFF) and the process crashes
// with EXCEPTION_ACCESS_VIOLATION inside FHttpManager::Tick.
//
// The fix is to defer every broadcast to the next game-thread task
// processing point. AsyncTask(ENamedThreads::GameThread, ...) enqueues
// the work even when we are already on the game thread, so the BP
// listener chain runs AFTER FHttpManager::Tick's iteration ends, and
// any new HTTP requests it creates are appended safely.
//
// We capture a TWeakObjectPtr to guard against the component being
// torn down between enqueue and dispatch (e.g. PIE end, level unload).
template <typename DelegateT, typename... ArgsT>
static void DeferredBroadcast(ULangGraphComponent* Self, DelegateT& Delegate, ArgsT... Args)
{
	TWeakObjectPtr<ULangGraphComponent> WeakSelf(Self);
	AsyncTask(ENamedThreads::GameThread, [WeakSelf, &Delegate, Args...]()
	{
		if (WeakSelf.IsValid())
		{
			Delegate.Broadcast(Args...);
		}
	});
}

// Read the `content` field from a LangChain-shaped message or chunk JSON
// object. OpenAI-compatible providers serialize `content` as a flat
// string; Anthropic serializes it as an array of content blocks like
//   [{"type": "text", "text": "..."}, {"type": "tool_use", ...}, ...]
// In streamed AIMessageChunks the same array shape carries each token
// (a single-element array with the per-token text). Without this helper
// every Anthropic token would be dropped at the TryGetStringField call
// site and the avatar would speak silence.
static FString ExtractTextContent(const TSharedPtr<FJsonObject>& MsgOrChunk)
{
	if (!MsgOrChunk.IsValid())
		return FString();

	// String form -- OpenAI / serialized non-streaming responses.
	FString AsString;
	if (MsgOrChunk->TryGetStringField(TEXT("content"), AsString))
		return AsString;

	// Array form -- Anthropic, both /runs/wait final messages and
	// streamed AIMessageChunks. Concatenate every "text" block.
	const TArray<TSharedPtr<FJsonValue>>* Blocks = nullptr;
	if (!MsgOrChunk->TryGetArrayField(TEXT("content"), Blocks) || !Blocks)
		return FString();

	FString Out;
	for (const TSharedPtr<FJsonValue>& BlockValue : *Blocks)
	{
		if (!BlockValue.IsValid())
			continue;
		const TSharedPtr<FJsonObject> Block = BlockValue->AsObject();
		if (!Block.IsValid())
			continue;
		FString BlockType;
		if (!Block->TryGetStringField(TEXT("type"), BlockType) || BlockType != TEXT("text"))
			continue;
		FString BlockText;
		if (Block->TryGetStringField(TEXT("text"), BlockText))
			Out.Append(BlockText);
	}
	return Out;
}

ULangGraphComponent::ULangGraphComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// ── Non-streaming query response handler ────────────────────────────────────

void ULangGraphComponent::OnLangGraphResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!bWasSuccessful || !Response.IsValid())
		return;

	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		return;

	const TSharedPtr<FJsonObject>* OuterPtr = nullptr;
	if (!JsonValue->TryGetObject(OuterPtr) || !OuterPtr || !OuterPtr->IsValid())
	{
		// Valid JSON but no object — treat as empty completion
		DeferredBroadcast(this, IncomingLangGraphResponse, FString(), GPTRoleType::ASSISTANT);
		return;
	}

	const FJsonObject& Outer = **OuterPtr;

	const TArray<TSharedPtr<FJsonValue>>* MessagesPtr = nullptr;
	if (!Outer.TryGetArrayField(TEXT("messages"), MessagesPtr) || !MessagesPtr || MessagesPtr->Num() == 0)
	{
		// Pipeline completed with no message content — signal completion with empty string
		DeferredBroadcast(this, IncomingLangGraphResponse, FString(), GPTRoleType::ASSISTANT);
		return;
	}

	const TSharedPtr<FJsonObject> LastMsg = MessagesPtr->Last()->AsObject();
	if (!LastMsg.IsValid())
	{
		DeferredBroadcast(this, IncomingLangGraphResponse, FString(), GPTRoleType::ASSISTANT);
		return;
	}

	GPTRoleType role = GPTRoleType::ASSISTANT;
	FString checkRole;
	if (LastMsg->TryGetStringField(TEXT("type"), checkRole))
	{
		if      (checkRole == TEXT("system"))   role = GPTRoleType::SYSTEM;
		else if (checkRole == TEXT("ai"))       role = GPTRoleType::ASSISTANT;
		else if (checkRole == TEXT("function")) role = GPTRoleType::FUNCTION;
		else if (checkRole == TEXT("human"))    role = GPTRoleType::USER;
	}

	const FString Content = ExtractTextContent(LastMsg);
	DeferredBroadcast(this, IncomingLangGraphResponse, Content, role);
}

// ── Streaming (SSE updates + messages) response handler ────────────────────

void ULangGraphComponent::FlushSentenceBuffer(bool bEndStream)
{
	if (SentenceBuffer.Len() > 0 || bEndStream)
	{
		DeferredBroadcast(this, IncomingLangGraphSentenceResponse, SentenceBuffer.TrimStartAndEnd(), StreamCurrentRole, bEndStream);
		SentenceBuffer.Empty();
	}
}

void ULangGraphComponent::AppendAndFlushSentences(const FString& Text)
{
	if (Text.IsEmpty())
		return;

	// New sentence boundaries can only appear straddling the buffer's previous
	// last char and the new text, or inside the new text itself. Re-scanning
	// from PrevLen-1 catches both cases without re-checking already-flushed
	// regions.
	const int32 PrevLen = SentenceBuffer.Len();
	int32 ScanStart = PrevLen > 0 ? PrevLen - 1 : 0;
	SentenceBuffer.Append(Text);

	// Flush at every boundary, not just the last one. A single token can
	// contain multiple complete sentences (especially when the model emits
	// a burst at end-of-stream); merging them into one TTS call produces
	// ~30 s "sentences" that overrun the per-buffer pacing budget. Splitting
	// at the first boundary, then looping, gives one TTS call per sentence
	// in submission order.
	while (true)
	{
		int32 FlushUpTo = -1;
		const int32 BufLen = SentenceBuffer.Len();
		const TCHAR* BufData = *SentenceBuffer;
		for (int32 i = ScanStart; i < BufLen - 1; i++)
		{
			const TCHAR C = BufData[i];
			if ((C == '.' || C == '!' || C == '?' || C == ':' || C == ';') && FChar::IsWhitespace(BufData[i + 1]))
			{
				FlushUpTo = i + 1;
				break;
			}
		}

		if (FlushUpTo < 0)
			break;

		const FString Sentence = SentenceBuffer.Left(FlushUpTo + 1).TrimStartAndEnd();
		SentenceBuffer.RemoveAt(0, FlushUpTo + 1);
		if (Sentence.Len() > 0)
			DeferredBroadcast(this, IncomingLangGraphSentenceResponse, Sentence, StreamCurrentRole, false);

		// After a flush, the remainder is fresh content; rescan from the start.
		ScanStart = 0;
	}
}

void ULangGraphComponent::ProcessUpdatesEvent(const FString& Payload)
{
	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Payload);
	if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		return;

	const TSharedPtr<FJsonObject>* OuterPtr = nullptr;
	if (!JsonValue->TryGetObject(OuterPtr) || !OuterPtr || !OuterPtr->IsValid())
		return;

	const FJsonObject& Outer = **OuterPtr;
	if (Outer.Values.Num() == 0)
		return;

	// Grab the first (typically only) node-update key without allocating a TArray.
	const TSharedPtr<FJsonValue>& FirstValue = Outer.Values.CreateConstIterator()->Value;
	const TSharedPtr<FJsonObject> Inner = FirstValue.IsValid() ? FirstValue->AsObject() : nullptr;
	if (!Inner.IsValid())
		return;

	const TArray<TSharedPtr<FJsonValue>>* MessagesPtr = nullptr;
	if (!Inner->TryGetArrayField(TEXT("messages"), MessagesPtr) || !MessagesPtr || MessagesPtr->Num() == 0)
		return;

	const TSharedPtr<FJsonObject> FirstMsg = (*MessagesPtr)[0]->AsObject();
	if (!FirstMsg.IsValid())
		return;

	GPTRoleType role = GPTRoleType::ASSISTANT;
	FString checkRole;
	if (FirstMsg->TryGetStringField(TEXT("type"), checkRole))
	{
		if      (checkRole == TEXT("system")) role = GPTRoleType::SYSTEM;
		else if (checkRole == TEXT("ai"))     role = GPTRoleType::ASSISTANT;
		else if (checkRole == TEXT("tool"))   role = GPTRoleType::FUNCTION;
		else if (checkRole == TEXT("human"))  role = GPTRoleType::USER;
	}
	StreamCurrentRole = role;

	const FString Content = ExtractTextContent(FirstMsg);

	// Token-level delegate (per-event, in arrival order).
	DeferredBroadcast(this, IncomingLangGraphStreamResponse, Content, role, false);

	// NOTE: do NOT feed Content into AppendAndFlushSentences here. The
	// `updates` event for an assistant node carries the FULL synthesized
	// message, which `messages-tuple` already streamed token-by-token into
	// the sentence buffer. Re-appending the whole message duplicates every
	// sentence -- the duplicated text gets merged into one giant TTS call
	// that re-speaks the entire turn (observed: 65 s of audio in a single
	// "sentence" buffer when the turn was ~30 s of real content).
}

void ULangGraphComponent::ProcessMessagesEvent(const FString& Payload)
{
	// LangGraph's `messages` stream mode wraps each LLM token chunk as a
	// 2-element JSON array: [chunk_object, metadata_object]. We only need
	// the chunk; the metadata is currently ignored.
	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Payload);
	if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
		return;

	const TArray<TSharedPtr<FJsonValue>>* TuplePtr = nullptr;
	if (!JsonValue->TryGetArray(TuplePtr) || !TuplePtr || TuplePtr->Num() < 1)
		return;

	const TSharedPtr<FJsonObject> Chunk = (*TuplePtr)[0]->AsObject();
	if (!Chunk.IsValid())
		return;

	// Skip tokens emitted by structured-output calls (e.g. the LangGraph
	// agent's triage node, which streams a JSON object whose colons would
	// otherwise be misread as sentence boundaries by the TTS pipeline).
	// The metadata tuple element carries the originating node's name.
	if (TuplePtr->Num() >= 2)
	{
		const TSharedPtr<FJsonObject> Metadata = (*TuplePtr)[1]->AsObject();
		if (Metadata.IsValid())
		{
			FString NodeName;
			if (Metadata->TryGetStringField(TEXT("langgraph_node"), NodeName)
				&& NodeName == TEXT("triage"))
				return;
		}
	}

	// Only keep AI text chunks. The messages stream interleaves several types:
	//   "AIMessageChunk" -- the model's tokens (what we want).
	//   "tool"           -- the tool's return value (search results, raw JSON).
	//   "system"/"human" -- echoes of system/user messages (not produced by streaming
	//                       in practice, but defensively filtered).
	// Without this guard, tool-result JSON ends up in the TTS sentence buffer.
	FString ChunkType;
	if (Chunk->TryGetStringField(TEXT("type"), ChunkType)
		&& ChunkType != TEXT("AIMessageChunk"))
		return;

	// Skip chunks that are part of a tool-call plan: their text content (if any)
	// is reasoning about which tool to call, not the user-facing reply. Guarding
	// here keeps tool-planning text out of the TTS sentence buffer.
	const TArray<TSharedPtr<FJsonValue>>* ToolCallChunks = nullptr;
	if (Chunk->TryGetArrayField(TEXT("tool_call_chunks"), ToolCallChunks)
		&& ToolCallChunks && ToolCallChunks->Num() > 0)
		return;

	// Anthropic streams each token as a single-element content-block array
	// (e.g. [{"type":"text","text":"Hey"}]). OpenAI streams content as a
	// flat string. ExtractTextContent collapses both shapes to a string so
	// the sentence buffer sees the same form regardless of provider.
	const FString Token = ExtractTextContent(Chunk);
	if (Token.IsEmpty())
		return;

	StreamCurrentRole = GPTRoleType::ASSISTANT;

	// Per-token raw stream broadcast for consumers that want token-level events.
	DeferredBroadcast(this, IncomingLangGraphStreamResponse, Token, GPTRoleType::ASSISTANT, false);

	// Feed into the sentence buffer; complete sentences fan out to
	// IncomingLangGraphSentenceResponse for TTS pipelining.
	AppendAndFlushSentences(Token);
}

void ULangGraphComponent::OnLangGraphPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived) {
	if (bytesReceived == 0 || !request.IsValid())
		return;

	FHttpResponsePtr Response = request->GetResponse();
	if (!Response.IsValid())
		return;

	const FString FullBuffer = Response->GetContentAsString();
	const int32 FullLen = FullBuffer.Len();
	if (FullLen <= StreamScanOffset)
		return;

	// One regex matches both event types we subscribe to, including subgraph-
	// namespaced variants emitted when stream_subgraphs=true:
	//   - "event: updates                  data: {...}"  parent-level node delta
	//   - "event: updates|qa_node:<id>     data: {...}"  subgraph node delta
	//   - "event: messages|qa_node:<id>    data: [...]"  per-token LLM chunk inside subgraph
	// `.` does not cross newlines, so the match is bounded to a single data
	// line. Partial events (no closing bracket yet) don't match, so we never
	// advance past incomplete data. Compiled once per process.
	static const FRegexPattern SsePattern(
		TEXT("event:\\s*(updates|messages)(?:\\|[^\\s]+)?\\s+data:\\s*(\\{.*\\}|\\[.*\\])")
	);

	FRegexMatcher Matcher(SsePattern, FullBuffer);
	Matcher.SetLimits(StreamScanOffset, FullLen);

	int32 LastMatchEnd = StreamScanOffset;

	while (Matcher.FindNext())
	{
		LastMatchEnd = Matcher.GetMatchEnding();
		const FString EventName = Matcher.GetCaptureGroup(1);
		const FString Payload   = Matcher.GetCaptureGroup(2);

		if (EventName == TEXT("updates"))
			ProcessUpdatesEvent(Payload);
		else if (EventName == TEXT("messages"))
			ProcessMessagesEvent(Payload);
	}

	StreamScanOffset = LastMatchEnd;
}

void ULangGraphComponent::OnLangGraphStreamComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	// Catch any final event(s) the progress callback may have missed (e.g. arrived
	// in the same chunk as the connection close).
	if (bWasSuccessful && Request.IsValid() && Response.IsValid())
		OnLangGraphPartialResponseReceived(Request, 0, /*bytesReceived=*/1);

	// Flush whatever remains in the sentence buffer with the end-of-stream flag,
	// then signal end-of-stream on the token-level delegate as well.
	FlushSentenceBuffer(true);
	DeferredBroadcast(this, IncomingLangGraphStreamResponse, FString(), StreamCurrentRole, true);
}

// ── Thread-creation response handler ────────────────────────────────────────

void ULangGraphComponent::OnLangGraphThreadCreateResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	// Always broadcast exactly once — callers rely on this for synchronization.
	// Broadcast an empty string on any error path so listeners can detect failure.
	FString ThreadID;

	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation request failed (transport error)"));
		DeferredBroadcast(this, LangGraphThreadCreateResponse, ThreadID);
		return;
	}

	const int32 StatusCode = Response->GetResponseCode();
	const FString Body = Response->GetContentAsString();

	if (StatusCode < 200 || StatusCode >= 300)
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation HTTP %d: %s"), StatusCode, *Body);
		DeferredBroadcast(this, LangGraphThreadCreateResponse, ThreadID);
		return;
	}

	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Body);
	if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation response was not valid JSON: %s"), *Body);
		DeferredBroadcast(this, LangGraphThreadCreateResponse, ThreadID);
		return;
	}

	const TSharedPtr<FJsonObject>* Obj = nullptr;
	if (!JsonValue->TryGetObject(Obj) || !Obj || !(*Obj).IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation response was not a JSON object: %s"), *Body);
		DeferredBroadcast(this, LangGraphThreadCreateResponse, ThreadID);
		return;
	}

	if (!(*Obj)->TryGetStringField(TEXT("thread_id"), ThreadID))
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation response missing 'thread_id' field: %s"), *Body);
	}

	DeferredBroadcast(this, LangGraphThreadCreateResponse, ThreadID);
}

// ── Thread lifecycle ────────────────────────────────────────────────────────

void ULangGraphComponent::createLangGraphThread(FString threadID) {
	// LangGraph Platform requires thread_id to be a valid UUID. If the caller
	// passes an empty string or anything else, substitute a freshly-generated
	// UUID so we don't incur an HTTP 422 round-trip. The actual id assigned
	// by the server is broadcast via LangGraphThreadCreateResponse so callers
	// can learn what to use for subsequent queries.
	FGuid Parsed;
	if (!FGuid::Parse(threadID, Parsed))
	{
		if (!threadID.IsEmpty())
		{
			UE_LOG(LogTemp, Warning,
				TEXT("LangGraph: thread_id '%s' is not a valid UUID; substituting a generated one"),
				*threadID);
		}
		threadID = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphensLower);
	}

	FHttpModule* Http = &FHttpModule::Get();
	FString payload;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->SetURL(endpoint + ":" + FString::FromInt(port) + "/threads");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());

	payloadObject->SetStringField("thread_id", threadID);
	payloadObject->SetStringField("if_exists", "do_nothing");

	Request->OnProcessRequestComplete().BindUObject(this, &ULangGraphComponent::OnLangGraphThreadCreateResponseReceived);

	FJsonSerializer::Serialize(payloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&payload));

	Request->SetContentAsString(payload);
	Request->ProcessRequest();
}

void ULangGraphComponent::deleteLangGraphThread(FString threadID) {
	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->SetURL(endpoint + ":" + FString::FromInt(port) + "/threads/" + threadID);
	Request->SetVerb("DELETE");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	Request->ProcessRequest();
}

// ── Query execution ─────────────────────────────────────────────────────────

void ULangGraphComponent::langGraphQuery(const TArray<FChatTurn>& messages, FString threadID, FString assistantID, FString model, int recursionLimit, bool stream) {
	// Guard against empty thread IDs — otherwise the URL becomes ".../threads//runs/stream"
	// which the server rejects and wastes a round-trip. This typically indicates the
	// caller never received a valid thread ID from createLangGraphThread (e.g. the
	// creation request failed and broadcast an empty string on the error path).
	if (threadID.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: langGraphQuery called with empty threadID; aborting request"));
		if (stream)
		{
			DeferredBroadcast(this, IncomingLangGraphStreamResponse, FString(), GPTRoleType::ASSISTANT, true);
			DeferredBroadcast(this, IncomingLangGraphSentenceResponse, FString(), GPTRoleType::ASSISTANT, true);
		}
		else
		{
			DeferredBroadcast(this, IncomingLangGraphResponse, FString(), GPTRoleType::ASSISTANT);
		}
		return;
	}

	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());
	payloadObject->SetStringField("assistant_id", assistantID);

	TArray<TSharedPtr<FJsonValue>> jsonMessages;
	jsonMessages.Reserve(messages.Num());
	for (const FChatTurn& Turn : messages)
	{
		// Fast role → string mapping (avoids UEnum reflection lookup per message).
		const TCHAR* RoleStr = TEXT("user");
		switch (Turn.role)
		{
			case GPTRoleType::SYSTEM:    RoleStr = TEXT("system");    break;
			case GPTRoleType::ASSISTANT: RoleStr = TEXT("assistant"); break;
			case GPTRoleType::USER:      RoleStr = TEXT("user");      break;
			case GPTRoleType::FUNCTION:  RoleStr = TEXT("function");  break;
		}

		TSharedPtr<FJsonObject> TurnObj = MakeShareable(new FJsonObject());
		TurnObj->SetStringField(TEXT("role"), RoleStr);
		TurnObj->SetStringField(TEXT("content"), Turn.content);
		jsonMessages.Add(MakeShareable(new FJsonValueObject(TurnObj)));
	}

	TSharedPtr<FJsonObject> inputObject = MakeShareable(new FJsonObject());
	inputObject->SetArrayField(TEXT("messages"), jsonMessages);
	payloadObject->SetObjectField("input", inputObject);

	// Build URL once; both branches share the common prefix.
	const FString UrlBase = endpoint + TEXT(":") + FString::FromInt(port) + TEXT("/threads/") + threadID + TEXT("/runs/");

	if (stream) {
		// Reset per-stream state so the next progress callback starts fresh.
		StreamScanOffset = 0;
		StreamCurrentRole = GPTRoleType::ASSISTANT;
		SentenceBuffer.Reset(512);

		Request->OnRequestProgress64().BindUObject(this, &ULangGraphComponent::OnLangGraphPartialResponseReceived);
		Request->OnProcessRequestComplete().BindUObject(this, &ULangGraphComponent::OnLangGraphStreamComplete);

		// Subscribe to two complementary stream modes:
		//   - "updates":        per-node state deltas (one event per node completion).
		//                       Used for triage/agent completion semantics.
		//   - "messages-tuple": per-token LLM chunks emitted as `[chunk, metadata]`.
		//                       Streams as the model generates so TTS can start
		//                       speaking the first sentence while later tokens
		//                       are still being produced.
		// stream_subgraphs=true is required for token events from inside a
		// `create_react_agent` (or any nested compiled graph) to bubble up to
		// the parent SSE stream. Without it, only the parent's direct LLM
		// calls would emit messages events.
		TArray<TSharedPtr<FJsonValue>> StreamModes;
		StreamModes.Add(MakeShareable(new FJsonValueString(TEXT("updates"))));
		StreamModes.Add(MakeShareable(new FJsonValueString(TEXT("messages-tuple"))));
		payloadObject->SetArrayField(TEXT("stream_mode"), StreamModes);
		payloadObject->SetBoolField(TEXT("stream_subgraphs"), true);

		Request->SetURL(UrlBase + TEXT("stream"));
	}
	else {
		Request->OnProcessRequestComplete().BindUObject(this, &ULangGraphComponent::OnLangGraphResponseReceived);
		Request->SetURL(UrlBase + TEXT("wait"));
	}

	TSharedPtr<FJsonObject> configurableObject = MakeShareable(new FJsonObject());
	configurableObject->SetStringField(TEXT("model"), model);

	TSharedPtr<FJsonObject> configObject = MakeShareable(new FJsonObject());
	configObject->SetNumberField(TEXT("recursion_limit"), recursionLimit);
	configObject->SetObjectField(TEXT("configurable"), configurableObject);

	payloadObject->SetObjectField(TEXT("config"), configObject);

	FString payload;
	FJsonSerializer::Serialize(payloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&payload));

	Request->SetContentAsString(payload);
	Request->ProcessRequest();
}

// Called when the game starts
void ULangGraphComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

