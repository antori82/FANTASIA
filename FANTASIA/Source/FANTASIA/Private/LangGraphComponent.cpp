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
	if (bWasSuccessful) {

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		FString checkRole;
		GPTRoleType role = GPTRoleType::ASSISTANT;

		if (FJsonSerializer::Deserialize(Reader, JsonValue))
		{
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				const TArray<TSharedPtr<FJsonValue>>& messages = FileMessageObject->Get()->GetArrayField(TEXT("messages"));

				if (messages.Num() == 0)
				{
					// Pipeline completed with no message content — signal completion with empty string
					IncomingLangGraphResponse.Broadcast(FString(), GPTRoleType::ASSISTANT);
					return;
				}

				checkRole = messages.Last()->AsObject()->GetStringField(TEXT("type"));

				if (checkRole == "system")
					role = GPTRoleType::SYSTEM;
				else if (checkRole == "ai")
					role = GPTRoleType::ASSISTANT;
				else if (checkRole == "function")
					role = GPTRoleType::FUNCTION;
				else if (checkRole == "human")
					role = GPTRoleType::USER;

				IncomingLangGraphResponse.Broadcast(messages.Last()->AsObject()->GetStringField(TEXT("content")), role);
			}
			else
			{
				// Valid JSON but no object — treat as empty completion
				IncomingLangGraphResponse.Broadcast(FString(), GPTRoleType::ASSISTANT);
			}
		}
	}
}

// ── Streaming (SSE updates) response handler ────────────────────────────────

void ULangGraphComponent::OnLangGraphPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived) {
	FHttpResponsePtr test;
	FString message;

	if (bytesReceived > 0) {

		FString checkRole, update;
		GPTRoleType role;

		test = request->GetResponse();
		message = test->GetContentAsString();

		const FRegexPattern myPattern(TEXT("event: updates\\s*data:(.*)"));

		FRegexMatcher myMatcher(myPattern, message);

		while (myMatcher.FindNext())
			update = myMatcher.GetCaptureGroup(1);

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(update);

		if (FJsonSerializer::Deserialize(Reader, JsonValue))
		{
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				TArray<FString> keys;
				FileMessageObject->Get()->Values.GetKeys(keys);

				if (keys.Num() == 0)
				{
					IncomingLangGraphStreamResponse.Broadcast(FString(), GPTRoleType::ASSISTANT, true);
					return;
				}

				FString key = keys[0];
				const TArray<TSharedPtr<FJsonValue>>& messages = FileMessageObject->Get()->GetObjectField(key)->GetArrayField(TEXT("messages"));

				if (messages.Num() == 0)
				{
					// Stream update with no messages — signal completion
					IncomingLangGraphStreamResponse.Broadcast(FString(), GPTRoleType::ASSISTANT, true);
					return;
				}

				checkRole = messages[0]->AsObject()->GetStringField(TEXT("type"));

				if (checkRole == "system")
					role = GPTRoleType::SYSTEM;
				else if (checkRole == "ai")
					role = GPTRoleType::ASSISTANT;
				else if (checkRole == "tool")
					role = GPTRoleType::FUNCTION;
				else if (checkRole == "human")
					role = GPTRoleType::USER;

				IncomingLangGraphStreamResponse.Broadcast(messages[0]->AsObject()->GetStringField(TEXT("content")), role, role == GPTRoleType::ASSISTANT);
			}
		}
	}
}

// ── Thread-creation response handler ────────────────────────────────────────

void ULangGraphComponent::OnLangGraphThreadCreateResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	FHttpResponsePtr test;
	FString message, threadID;

	if (bWasSuccessful) {
		test = Request->GetResponse();
		message = test->GetContentAsString();

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(message);

		if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				threadID = FileMessageObject->Get()->GetStringField(TEXT("thread_id"));
				LangGraphThreadCreateResponse.Broadcast(threadID);
			}
		}
	}
}

// ── Thread lifecycle ────────────────────────────────────────────────────────

void ULangGraphComponent::createLangGraphThread(FString threadID) {
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

void ULangGraphComponent::langGraphQuery(TArray<FChatTurn> messages, FString threadID, FString assistantID, FString model, int recursionLimit, bool stream) {
	FHttpModule* Http = &FHttpModule::Get();
	FString payload;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());

	payloadObject->SetStringField("assistant_id", assistantID);

	TArray<TSharedPtr<FJsonValue>> jsonMessages;
	for (int i = 0; i < messages.Num(); i++)
	{
		TSharedPtr<FJsonObject> turn = MakeShareable(new FJsonObject());
		FText enumValueText;
		UEnum::GetDisplayValueAsText(messages[i].role, enumValueText);
		turn->SetStringField("role", enumValueText.ToString().ToLower());
		turn->SetStringField("content", messages[i].content);

		jsonMessages.Add(MakeShareable(new FJsonValueObject(turn)));
	}

	TSharedPtr<FJsonObject> inputObject = MakeShareable(new FJsonObject());

	inputObject->SetArrayField(TEXT("messages"), jsonMessages);
	payloadObject->SetObjectField("input", inputObject);

	if (stream) {
		Request->OnRequestProgress64().BindUObject(this, &ULangGraphComponent::OnLangGraphPartialResponseReceived);
		payloadObject->SetStringField("stream_mode", "updates");
		Request->SetURL(endpoint + ":" + FString::FromInt(port) + "/threads/" + threadID + "/runs/stream");
	}
	else {
		Request->OnProcessRequestComplete().BindUObject(this, &ULangGraphComponent::OnLangGraphResponseReceived);
		Request->SetURL(endpoint + ":" + FString::FromInt(port) + "/threads/" + threadID + "/runs/wait");
	}
	
	

	TSharedPtr<FJsonObject> configObject = MakeShareable(new FJsonObject());
	TSharedPtr<FJsonObject> configurableObject = MakeShareable(new FJsonObject());

	configurableObject->SetStringField("model", model);

	configObject->SetNumberField("recursion_limit", recursionLimit);
	configObject->SetObjectField("configurable", configurableObject);

	payloadObject->SetObjectField("config", configObject);

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

