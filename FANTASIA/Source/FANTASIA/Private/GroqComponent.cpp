// Fill out your copyright notice in the Description page of Project Settings.


#include "GroqComponent.h"
#include "Misc/Base64.h"
// Sets default values for this component's properties
UGroqComponent::UGroqComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UGroqComponent::OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		FString checkRole;
		GPTRoleType role = GPTRoleType::ASSISTANT;

		if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
			FString temp = Response->GetContentAsString();
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				TArray<TSharedPtr<FJsonValue>> results = FileMessageObject->Get()->GetArrayField(TEXT("choices"));

				checkRole = results[0]->AsObject()->GetObjectField(TEXT("message"))->GetStringField(TEXT("role"));

				if (checkRole == "system")
					role = GPTRoleType::SYSTEM;
				else if (checkRole == "assistant")
					role = GPTRoleType::ASSISTANT;
				else if (checkRole == "function")
					role = GPTRoleType::FUNCTION;
				else if (checkRole == "user")
					role = GPTRoleType::USER;

				IncomingChatGPTResponse.Broadcast(results[0]->AsObject()->GetObjectField(TEXT("message"))->GetStringField(TEXT("content")), role);
			}
		}
	}
}

void UGroqComponent::OnGPTPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived) {
	FHttpResponsePtr test;
	FString message, data, checkRole, outFragment = "";
	const FRegexPattern myPattern(TEXT("data: (\\{.*\\})"));
	static GPTRoleType role = GPTRoleType::ASSISTANT;
	static int blocksRead = 0;
	int blocksReading = 0;
	TArray<TSharedPtr<FJsonValue>> results;
	FString endStream = "";

	if (bytesReceived > 0) {
		test = request->GetResponse();
		message = test->GetContentAsString();
		FRegexMatcher myMatcher(myPattern, message);

		while (myMatcher.FindNext())
		{
			blocksReading++;
			if (blocksReading > blocksRead) {
				data = myMatcher.GetCaptureGroup(1);

				TSharedPtr<FJsonValue> JsonValue;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(data);

				if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
					const TSharedPtr<FJsonObject>* FileMessageObject;

					if (JsonValue->TryGetObject(FileMessageObject)) {
						results = FileMessageObject->Get()->GetArrayField(TEXT("choices"));
						results[0]->AsObject()->TryGetStringField(TEXT("finish_reason"), endStream);
						if (endStream != "stop") {
							blocksRead++;

							results[0]->AsObject()->TryGetStringField(TEXT("role"), checkRole);
							if (checkRole == "system")
								role = GPTRoleType::SYSTEM;
							else if (checkRole == "assistant")
								role = GPTRoleType::ASSISTANT;
							else if (checkRole == "function")
								role = GPTRoleType::FUNCTION;
							else if (checkRole == "user")
								role = GPTRoleType::USER;

							outFragment.Append(results[0]->AsObject()->GetObjectField(TEXT("delta"))->GetStringField(TEXT("content")));
						}
						else
							blocksRead = 0;
					}
				}
			}
		}
		IncomingGPTStreamResponse.Broadcast(outFragment, role, endStream == "stop");
	}
}

void UGroqComponent::getGPTCompletion(TArray<FChatTurn> messages, FString apiMethod, bool stream) {
	FHttpModule* Http = &FHttpModule::Get();
	FString payload;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	
	Request->SetURL("https://api.groq.com/openai/v1/chat/completions");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"), "Bearer " + Key);
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());

	TArray<TSharedPtr<FJsonValue>> jsonMessages;
	for (int i = 0; i < messages.Num(); i++) {
		TSharedPtr<FJsonObject> turn = MakeShareable(new FJsonObject());
		FText enumValueText;
		UEnum::GetDisplayValueAsText(messages[i].role, enumValueText);
		turn->SetStringField("role", enumValueText.ToString().ToLower());
		turn->SetStringField("content", messages[i].content);
		if (stream)
			Request->OnRequestProgress64().BindUObject(this, &UGroqComponent::OnGPTPartialResponseReceived);
		else
			Request->OnProcessRequestComplete().BindUObject(this, &UGroqComponent::OnGPTResponseReceived);

		jsonMessages.Add(MakeShareable(new FJsonValueObject(turn)));
	}
	payloadObject->SetArrayField(TEXT("messages"), jsonMessages);
	payloadObject->SetStringField("model", apiMethod);
	payloadObject->SetBoolField("stream", stream);

	FJsonSerializer::Serialize(payloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&payload));

	Request->SetContentAsString(payload);
	Request->ProcessRequest();
}

// Called when the game starts
void UGroqComponent::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void UGroqComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
