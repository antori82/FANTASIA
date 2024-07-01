// Fill out your copyright notice in the Description page of Project Settings.


#include "OllamaComponent.h"
#include "Misc/Base64.h"
// Sets default values for this component's properties
UOllamaComponent::UOllamaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UOllamaComponent::OnOllamaGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonValue))
		{
			FString temp = Response->GetContentAsString();
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				IncomingGPTResponse.Broadcast(FileMessageObject->Get()->GetStringField("response"));
			}
		}
	}
}


void UOllamaComponent::getOllamaGPTCompletion(FString prompt, FString model) {
	FHttpModule* Http = &FHttpModule::Get();
	FString payload;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UOllamaComponent::OnOllamaGPTResponseReceived);
	Request->SetURL(endpoint + ":" + FString::FromInt(port) + "/api/generate");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());
	payloadObject->SetStringField("prompt", prompt);
	payloadObject->SetStringField("model", model);
	payloadObject->SetBoolField("stream", false);

	FJsonSerializer::Serialize(payloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&payload));

	Request->SetContentAsString(payload);
	Request->ProcessRequest();
}

void UOllamaComponent::OnOllamaChatGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonValue))
		{
			FString temp = Response->GetContentAsString();
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				IncomingChatGPTResponse.Broadcast(FileMessageObject->Get()->GetObjectField("message")->GetStringField("content"), FileMessageObject->Get()->GetObjectField("message")->GetStringField("role"));
			}
		}
	}
}

void UOllamaComponent::getOllamaChatGPTCompletion(TArray<FChatTurn> messages, FString model) {
	FHttpModule* Http = &FHttpModule::Get();
	FString payload;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UOllamaComponent::OnOllamaChatGPTResponseReceived);
	Request->SetURL(endpoint + ":" + FString::FromInt(port) + "/api/chat");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());


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
	payloadObject->SetArrayField(TEXT("messages"), jsonMessages);
	payloadObject->SetStringField("model", model);
	payloadObject->SetBoolField("stream", false);

	FJsonSerializer::Serialize(payloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&payload));

	Request->SetContentAsString(payload);
	Request->ProcessRequest();
}

// Called when the game starts
void UOllamaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UOllamaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
