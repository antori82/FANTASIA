/**
 * @file LangGraphComponent.cpp
 * @brief Implementation of ULangGraphComponent -- thread-based LangGraph agent queries.
 */

// Fill out your copyright notice in the Description page of Project Settings.


#include "LangGraphComponent.h"
#include "Misc/Base64.h"

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
		IncomingLangGraphResponse.Broadcast(FString(), GPTRoleType::ASSISTANT);
		return;
	}

	const FJsonObject& Outer = **OuterPtr;

	const TArray<TSharedPtr<FJsonValue>>* MessagesPtr = nullptr;
	if (!Outer.TryGetArrayField(TEXT("messages"), MessagesPtr) || !MessagesPtr || MessagesPtr->Num() == 0)
	{
		// Pipeline completed with no message content — signal completion with empty string
		IncomingLangGraphResponse.Broadcast(FString(), GPTRoleType::ASSISTANT);
		return;
	}

	const TSharedPtr<FJsonObject> LastMsg = MessagesPtr->Last()->AsObject();
	if (!LastMsg.IsValid())
	{
		IncomingLangGraphResponse.Broadcast(FString(), GPTRoleType::ASSISTANT);
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

	FString Content;
	LastMsg->TryGetStringField(TEXT("content"), Content);
	IncomingLangGraphResponse.Broadcast(Content, role);
}

// ── Streaming (SSE updates) response handler ────────────────────────────────

void ULangGraphComponent::FlushSentenceBuffer(bool bEndStream)
{
	if (SentenceBuffer.Len() > 0 || bEndStream)
	{
		IncomingLangGraphSentenceResponse.Broadcast(SentenceBuffer.TrimStartAndEnd(), StreamCurrentRole, bEndStream);
		SentenceBuffer.Empty();
	}
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

	// Match each SSE "updates" event by capturing the JSON object on the data line.
	// Greedy `\{.*\}` works because `.` does not cross newlines, so the match is
	// bounded to a single data line. Partial events (no closing brace yet) do not
	// match, so we never advance past incomplete data. Compiled once per process.
	static const FRegexPattern SsePattern(TEXT("event:\\s*updates\\s+data:\\s*(\\{.*\\})"));

	FRegexMatcher Matcher(SsePattern, FullBuffer);
	Matcher.SetLimits(StreamScanOffset, FullLen);

	int32 LastMatchEnd = StreamScanOffset;

	while (Matcher.FindNext())
	{
		LastMatchEnd = Matcher.GetMatchEnding();
		const FString Update = Matcher.GetCaptureGroup(1);

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Update);
		if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
			continue;

		const TSharedPtr<FJsonObject>* OuterPtr = nullptr;
		if (!JsonValue->TryGetObject(OuterPtr) || !OuterPtr || !OuterPtr->IsValid())
			continue;

		const FJsonObject& Outer = **OuterPtr;
		if (Outer.Values.Num() == 0)
			continue;

		// Grab the first (typically only) node-update key without allocating a TArray.
		const TSharedPtr<FJsonValue>& FirstValue = Outer.Values.CreateConstIterator()->Value;
		const TSharedPtr<FJsonObject> Inner = FirstValue.IsValid() ? FirstValue->AsObject() : nullptr;
		if (!Inner.IsValid())
			continue;

		const TArray<TSharedPtr<FJsonValue>>* MessagesPtr = nullptr;
		if (!Inner->TryGetArrayField(TEXT("messages"), MessagesPtr) || !MessagesPtr || MessagesPtr->Num() == 0)
			continue;

		const TSharedPtr<FJsonObject> FirstMsg = (*MessagesPtr)[0]->AsObject();
		if (!FirstMsg.IsValid())
			continue;

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

		FString Content;
		FirstMsg->TryGetStringField(TEXT("content"), Content);

		// Token-level delegate (per-event, in arrival order).
		IncomingLangGraphStreamResponse.Broadcast(Content, role, false);

		// Sentence-level buffering for TTS: only assistant text drives the buffer.
		// Boundary pairs (i, i+1) with i+1 <= PrevLen-1 were already checked last
		// append; new pairs start at i = PrevLen - 1.
		if (role == GPTRoleType::ASSISTANT && Content.Len() > 0)
		{
			const int32 PrevLen = SentenceBuffer.Len();
			const int32 ScanStart = PrevLen > 0 ? PrevLen - 1 : 0;
			SentenceBuffer.Append(MoveTemp(Content));

			int32 FlushUpTo = -1;
			const int32 BufLen = SentenceBuffer.Len();
			const TCHAR* BufData = *SentenceBuffer;
			for (int32 i = ScanStart; i < BufLen - 1; i++)
			{
				const TCHAR C = BufData[i];
				if ((C == '.' || C == '!' || C == '?' || C == ':' || C == ';') && FChar::IsWhitespace(BufData[i + 1]))
					FlushUpTo = i + 1;
			}

			if (FlushUpTo >= 0)
			{
				const FString Sentence = SentenceBuffer.Left(FlushUpTo + 1).TrimStartAndEnd();
				SentenceBuffer.RemoveAt(0, FlushUpTo + 1);
				if (Sentence.Len() > 0)
					IncomingLangGraphSentenceResponse.Broadcast(Sentence, StreamCurrentRole, false);
			}
		}
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
	IncomingLangGraphStreamResponse.Broadcast(FString(), StreamCurrentRole, true);
}

// ── Thread-creation response handler ────────────────────────────────────────

void ULangGraphComponent::OnLangGraphThreadCreateResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	// Always broadcast exactly once — callers rely on this for synchronization.
	// Broadcast an empty string on any error path so listeners can detect failure.
	FString ThreadID;

	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation request failed (transport error)"));
		LangGraphThreadCreateResponse.Broadcast(ThreadID);
		return;
	}

	const int32 StatusCode = Response->GetResponseCode();
	const FString Body = Response->GetContentAsString();

	if (StatusCode < 200 || StatusCode >= 300)
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation HTTP %d: %s"), StatusCode, *Body);
		LangGraphThreadCreateResponse.Broadcast(ThreadID);
		return;
	}

	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Body);
	if (!FJsonSerializer::Deserialize(Reader, JsonValue) || !JsonValue.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation response was not valid JSON: %s"), *Body);
		LangGraphThreadCreateResponse.Broadcast(ThreadID);
		return;
	}

	const TSharedPtr<FJsonObject>* Obj = nullptr;
	if (!JsonValue->TryGetObject(Obj) || !Obj || !(*Obj).IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation response was not a JSON object: %s"), *Body);
		LangGraphThreadCreateResponse.Broadcast(ThreadID);
		return;
	}

	if (!(*Obj)->TryGetStringField(TEXT("thread_id"), ThreadID))
	{
		UE_LOG(LogTemp, Error, TEXT("LangGraph: thread creation response missing 'thread_id' field: %s"), *Body);
	}

	LangGraphThreadCreateResponse.Broadcast(ThreadID);
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
			IncomingLangGraphStreamResponse.Broadcast(FString(), GPTRoleType::ASSISTANT, true);
			IncomingLangGraphSentenceResponse.Broadcast(FString(), GPTRoleType::ASSISTANT, true);
		}
		else
		{
			IncomingLangGraphResponse.Broadcast(FString(), GPTRoleType::ASSISTANT);
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
		payloadObject->SetStringField(TEXT("stream_mode"), TEXT("updates"));
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

