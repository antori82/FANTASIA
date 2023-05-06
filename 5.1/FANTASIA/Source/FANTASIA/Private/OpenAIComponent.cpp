// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenAIComponent.h"
#include "Misc/Base64.h"
// Sets default values for this component's properties
UOpenAIComponent::UOpenAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UOpenAIComponent::OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {

		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonValue))
		{
			FString temp = Response->GetContentAsString();
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				TArray<TSharedPtr<FJsonValue>> results = FileMessageObject->Get()->GetArrayField("choices");
				IncomingGPTResponse.Broadcast(results[0]->AsObject()->GetStringField("text"));
			}
		}		
	}
}

void UOpenAIComponent::getGPTCompletion(FString prompt, TArray<FString> stopSequences, FString apiMethod, int maxTokens, float temperature) {
	FHttpModule* Http = &FHttpModule::Get();
	FString payload;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UOpenAIComponent::OnGPTResponseReceived);
	Request->SetURL("https://api.openai.com/v1/engines/" + apiMethod + "/completions");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Authorization"), "Bearer " + Key);
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");

	TSharedPtr<FJsonObject> payloadObject = MakeShareable(new FJsonObject());
	payloadObject->SetNumberField("max_tokens", maxTokens);
	payloadObject->SetNumberField("temperature", temperature);
	payloadObject->SetStringField("prompt", prompt);

	TArray<TSharedPtr<FJsonValue>> StopSequences;
	for (int i = 0; i < stopSequences.Num(); i++)
		StopSequences.Add(MakeShareable(new FJsonValueString(stopSequences[i])));
	payloadObject->SetArrayField(TEXT("stop"), StopSequences);

	FJsonSerializer::Serialize(payloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&payload));

	Request->SetContentAsString(payload);
	Request->ProcessRequest();
}

// Called when the game starts
void UOpenAIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UOpenAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

