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

void UGroqComponent::OnChatGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
			FString temp = Response->GetContentAsString();
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				TArray<TSharedPtr<FJsonValue>> results = FileMessageObject->Get()->GetArrayField(TEXT("choices"));
				IncomingChatGPTResponse.Broadcast(results[0]->AsObject()->GetObjectField(TEXT("message"))->GetStringField(TEXT("content")), results[0]->AsObject()->GetObjectField(TEXT("message"))->GetStringField(TEXT("role")));
			}
		}
	}
}

void UGroqComponent::getChatGPTCompletion(TArray<FChatTurn> messages, FString apiMethod) {
	FHttpModule* Http = &FHttpModule::Get();
	FString payload;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UGroqComponent::OnChatGPTResponseReceived);
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

		jsonMessages.Add(MakeShareable(new FJsonValueObject(turn)));
	}
	payloadObject->SetArrayField(TEXT("messages"), jsonMessages);
	payloadObject->SetStringField("model", apiMethod);

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
