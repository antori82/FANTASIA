/**
 * @file OpenAICompatibleComponent.cpp
 * @brief Implementation of UOpenAICompatibleComponent -- unified LLM chat-completion component.
 */

#include "OpenAICompatibleComponent.h"

// NOTE: do NOT declare an FRegexPattern at namespace scope. Its constructor
// reaches into the ICU regex singleton, which is not yet initialized when
// global static initializers run in a monolithic build (Shipping/DebugGame).
// The result is `Assertion failed: Singleton (ICURegex.cpp:104)` followed by
// `__debugbreak`, which terminates the process before WinMain — silently,
// because GLog isn't up yet either. Editor builds dodge this because the
// FANTASIA module is its own DLL, loaded by LoadLibrary AFTER ICU init, so
// the global is constructed late enough for the singleton to exist.
// The pattern is now a function-static at the only call site below.

// ── Construction ────────────────────────────────────────────────────────────

UOpenAICompatibleComponent::UOpenAICompatibleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// ── Role conversion helpers ─────────────────────────────────────────────────

GPTRoleType UOpenAICompatibleComponent::ParseRole(const FString& RoleString)
{
	if (RoleString.Len() == 0)
		return GPTRoleType::ASSISTANT;

	switch (RoleString[0])
	{
	case 'a': return GPTRoleType::ASSISTANT;
	case 's': return GPTRoleType::SYSTEM;
	case 'u': return GPTRoleType::USER;
	case 'f': return GPTRoleType::FUNCTION;
	default:  return GPTRoleType::ASSISTANT;
	}
}

const FString& UOpenAICompatibleComponent::RoleToString(GPTRoleType Role)
{
	static const FString Assistant(TEXT("assistant"));
	static const FString System(TEXT("system"));
	static const FString User(TEXT("user"));
	static const FString Function(TEXT("function"));

	switch (Role)
	{
	case GPTRoleType::SYSTEM:    return System;
	case GPTRoleType::USER:      return User;
	case GPTRoleType::FUNCTION:  return Function;
	default:                     return Assistant;
	}
}

// ── Sentence-level buffering for TTS ────────────────────────────────────────

void UOpenAICompatibleComponent::FlushSentenceBuffer(bool bEndStream)
{
	if (SentenceBuffer.Len() > 0 || bEndStream)
	{
		IncomingSentenceResponse.Broadcast(SentenceBuffer.TrimStartAndEnd(), StreamCurrentRole, bEndStream);
		SentenceBuffer.Empty();
	}
}

// ── Chat-completion request ─────────────────────────────────────────────────

void UOpenAICompatibleComponent::GetChatCompletion(const TArray<FChatTurn>& messages, bool bStream, const FString& ModelOverride)
{
	StreamParseOffset = 0;
	StreamCurrentRole = GPTRoleType::ASSISTANT;
	SentenceBuffer.Reset(512);
	bStreamingActive = bStream;

	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	// Always bind completion callback for error handling; additionally bind progress for streaming
	Request->OnProcessRequestComplete().BindUObject(this, &UOpenAICompatibleComponent::OnRequestCompleted);
	if (bStream)
		Request->OnRequestProgress64().BindUObject(this, &UOpenAICompatibleComponent::OnPartialResponseReceived);

	Request->SetURL(Config.URL);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));

	if (Config.bRequiresAuth)
	{
		if (Config.APIKey.IsEmpty())
		{
			UE_LOG(LogTemp, Error, TEXT("[OpenAICompatible] API key is required but empty."));
			return;
		}
		Request->SetHeader(TEXT("Authorization"), TEXT("Bearer ") + Config.APIKey);
	}

	Request->SetTimeout(Config.TimeoutSeconds);

	TSharedPtr<FJsonObject> PayloadObject = MakeShareable(new FJsonObject());
	TArray<TSharedPtr<FJsonValue>> JsonMessages;
	JsonMessages.Reserve(messages.Num());

	for (const FChatTurn& Turn : messages)
	{
		TSharedPtr<FJsonObject> TurnObj = MakeShareable(new FJsonObject());
		TurnObj->SetStringField(TEXT("role"), RoleToString(Turn.role));
		TurnObj->SetStringField(TEXT("content"), Turn.content);
		JsonMessages.Add(MakeShareable(new FJsonValueObject(TurnObj)));
	}

	PayloadObject->SetArrayField(TEXT("messages"), JsonMessages);
	PayloadObject->SetStringField(TEXT("model"), ModelOverride.IsEmpty() ? Config.DefaultModel : ModelOverride);
	PayloadObject->SetBoolField(TEXT("stream"), bStream);

	FString Payload;
	FJsonSerializer::Serialize(PayloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&Payload));
	Request->SetContentAsString(Payload);

	Request->ProcessRequest();
}

// ── Request completion handler (error detection + non-streaming results) ────

void UOpenAICompatibleComponent::OnRequestCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("[OpenAICompatible] Request failed (no response)."));
		return;
	}

	const int32 Code = Response->GetResponseCode();
	if (Code < 200 || Code >= 300)
	{
		UE_LOG(LogTemp, Error, TEXT("[OpenAICompatible] HTTP %d: %s"), Code, *Response->GetContentAsString());
		return;
	}

	// Streaming mode: data was already handled by OnPartialResponseReceived; nothing more to do
	if (bStreamingActive)
		return;

	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (!FJsonSerializer::Deserialize(Reader, JsonValue))
	{
		UE_LOG(LogTemp, Error, TEXT("[OpenAICompatible] Failed to parse JSON response."));
		return;
	}

	const TSharedPtr<FJsonObject>* RootObject;
	if (!JsonValue->TryGetObject(RootObject))
	{
		UE_LOG(LogTemp, Error, TEXT("[OpenAICompatible] Response is not a JSON object."));
		return;
	}

	if ((*RootObject)->HasField(TEXT("error")))
	{
		const TSharedPtr<FJsonObject> ErrorObj = (*RootObject)->GetObjectField(TEXT("error"));
		UE_LOG(LogTemp, Error, TEXT("[OpenAICompatible] API error: %s - %s"),
			*ErrorObj->GetStringField(TEXT("type")),
			*ErrorObj->GetStringField(TEXT("message")));
		return;
	}

	const TArray<TSharedPtr<FJsonValue>>& Choices = (*RootObject)->GetArrayField(TEXT("choices"));
	if (Choices.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("[OpenAICompatible] Response contains no choices."));
		return;
	}

	const TSharedPtr<FJsonObject> MessageObj = Choices[0]->AsObject()->GetObjectField(TEXT("message"));
	const FString Content = MessageObj->GetStringField(TEXT("content"));
	const GPTRoleType Role = ParseRole(MessageObj->GetStringField(TEXT("role")));

	IncomingGPTResponse.Broadcast(Content, Role);
}

// ── Streaming (SSE) response handler ────────────────────────────────────────

void UOpenAICompatibleComponent::OnPartialResponseReceived(FHttpRequestPtr Request, uint64 BytesSent, uint64 BytesReceived)
{
	if (BytesReceived == 0)
		return;

	FHttpResponsePtr Response = Request->GetResponse();
	if (!Response.IsValid())
		return;

	const FString FullContent = Response->GetContentAsString();
	const int32 ContentLen = FullContent.Len();

	// Nothing new since last callback
	if (ContentLen <= StreamParseOffset)
		return;

	// Function-static: compiled once on first call, thread-safe per C++11
	// magic statics. Must NOT be promoted to namespace scope — see the note
	// at the top of this file about the ICU regex singleton.
	static const FRegexPattern SSEPattern(TEXT("data: (\\{.*\\})"));

	// Scan only the unparsed tail of the buffer via SetLimits (avoids the Mid copy)
	FRegexMatcher Matcher(SSEPattern, FullContent);
	Matcher.SetLimits(StreamParseOffset, ContentLen);

	FString OutFragment;
	OutFragment.Reserve((ContentLen - StreamParseOffset) / 2);
	bool bEndStream = false;
	int32 LastMatchEnd = StreamParseOffset;

	while (Matcher.FindNext())
	{
		LastMatchEnd = Matcher.GetMatchEnding();

		const FString Data = Matcher.GetCaptureGroup(1);
		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Data);

		if (!FJsonSerializer::Deserialize(Reader, JsonValue))
			continue;

		const TSharedPtr<FJsonObject>* ChunkObject;
		if (!JsonValue->TryGetObject(ChunkObject))
			continue;

		const TArray<TSharedPtr<FJsonValue>>& Choices = (*ChunkObject)->GetArrayField(TEXT("choices"));
		if (Choices.Num() == 0)
			continue;

		const TSharedPtr<FJsonObject> Choice = Choices[0]->AsObject();

		FString FinishReason;
		Choice->TryGetStringField(TEXT("finish_reason"), FinishReason);

		if (FinishReason == TEXT("stop"))
		{
			bEndStream = true;
		}
		else
		{
			const TSharedPtr<FJsonObject>* DeltaObj;
			if (Choice->TryGetObjectField(TEXT("delta"), DeltaObj))
			{
				FString RoleStr;
				if ((*DeltaObj)->TryGetStringField(TEXT("role"), RoleStr))
					StreamCurrentRole = ParseRole(RoleStr);

				FString Content;
				if ((*DeltaObj)->TryGetStringField(TEXT("content"), Content))
					OutFragment.Append(MoveTemp(Content));
			}
		}
	}

	// Absolute offset past the last fully matched SSE event
	StreamParseOffset = LastMatchEnd;

	// Token-level delegate: only broadcast when there's actual content or stream end
	if (OutFragment.Len() > 0 || bEndStream)
		IncomingGPTStreamResponse.Broadcast(OutFragment, StreamCurrentRole, bEndStream);

	// Sentence-level buffering for TTS: accumulate tokens, flush on sentence boundaries
	if (OutFragment.Len() > 0)
	{
		// Boundary pairs (i, i+1) with i+1 <= PrevLen-1 were already checked last callback.
		// New pairs start at i = PrevLen - 1 (last old char + first new char).
		const int32 PrevLen = SentenceBuffer.Len();
		const int32 ScanStart = PrevLen > 0 ? PrevLen - 1 : 0;
		SentenceBuffer.Append(MoveTemp(OutFragment));

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
				IncomingSentenceResponse.Broadcast(Sentence, StreamCurrentRole, false);
		}
	}

	// End of stream: flush whatever remains in the buffer
	if (bEndStream)
		FlushSentenceBuffer(true);
}

// ── Provider presets ────────────────────────────────────────────────────────

void UOpenAICompatibleComponent::ApplyPreset(ELLMProvider Provider)
{
	switch (Provider)
	{
	case ELLMProvider::OpenAI:   Config = MakeOpenAIConfig();   break;
	case ELLMProvider::Groq:     Config = MakeGroqConfig();     break;
	case ELLMProvider::Ollama:   Config = MakeOllamaConfig();   break;
	case ELLMProvider::LMStudio: Config = MakeLMStudioConfig(); break;
	case ELLMProvider::vLLM:     Config = MakeVLLMConfig();     break;
	default: break;
	}
}

FOpenAICompatibleConfig UOpenAICompatibleComponent::MakeOpenAIConfig()
{
	FOpenAICompatibleConfig C;
	C.URL = TEXT("https://api.openai.com/v1/chat/completions");
	C.DefaultModel = TEXT("gpt-4-turbo-preview");
	C.TimeoutSeconds = 60;
	C.bRequiresAuth = true;
	return C;
}

FOpenAICompatibleConfig UOpenAICompatibleComponent::MakeGroqConfig()
{
	FOpenAICompatibleConfig C;
	C.URL = TEXT("https://api.groq.com/openai/v1/chat/completions");
	C.DefaultModel = TEXT("llama-3.3-70b-versatile");
	C.TimeoutSeconds = 30;
	C.bRequiresAuth = true;
	return C;
}

FOpenAICompatibleConfig UOpenAICompatibleComponent::MakeOllamaConfig()
{
	FOpenAICompatibleConfig C;
	C.URL = TEXT("http://localhost:11434/v1/chat/completions");
	C.DefaultModel = TEXT("llama3");
	C.TimeoutSeconds = 120;
	C.bRequiresAuth = false;
	return C;
}

FOpenAICompatibleConfig UOpenAICompatibleComponent::MakeLMStudioConfig()
{
	FOpenAICompatibleConfig C;
	C.URL = TEXT("http://localhost:1234/v1/chat/completions");
	C.DefaultModel = TEXT("local-model");
	C.TimeoutSeconds = 120;
	C.bRequiresAuth = false;
	return C;
}

FOpenAICompatibleConfig UOpenAICompatibleComponent::MakeVLLMConfig()
{
	FOpenAICompatibleConfig C;
	C.URL = TEXT("http://localhost:8000/v1/chat/completions");
	C.DefaultModel = TEXT("default");
	C.TimeoutSeconds = 120;
	C.bRequiresAuth = false;
	return C;
}
