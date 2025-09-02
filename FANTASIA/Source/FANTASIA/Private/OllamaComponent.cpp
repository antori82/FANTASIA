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

void UOllamaComponent::OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (bWasSuccessful) {
		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		FString checkRole;
		GPTRoleType role;

		if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
			FString temp = Response->GetContentAsString();
			UE_LOG(LogTemp, Warning, TEXT("Complete response: %s"), *temp);
			const TSharedPtr<FJsonObject>* FileMessageObject;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				if (FileMessageObject->Get()->TryGetField(TEXT("error"))) {
					UE_LOG(LogTemp, Error, TEXT("[OpenAIComponent] %hs: %hs"), TCHAR_TO_UTF8(*FileMessageObject->Get()->GetObjectField(TEXT("error"))->GetStringField(TEXT("type"))), TCHAR_TO_UTF8(*FileMessageObject->Get()->GetObjectField(TEXT("error"))->GetStringField(TEXT("code"))));
					return;
				}

				TArray<TSharedPtr<FJsonValue>> results = FileMessageObject->Get()->GetArrayField(TEXT("choices"));

				FString debugOutput;
				TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&debugOutput);
				FJsonSerializer::Serialize(results[0], "", Writer);
				UE_LOG(LogTemp, Warning, TEXT("First choice JSON: %s"), *debugOutput);


				if (results.Num() > 0 && results[0]->Type == EJson::Object)
				{
					TSharedPtr<FJsonObject> choiceObject = results[0]->AsObject();
					if (choiceObject->HasField(TEXT("message")))
					{
						TSharedPtr<FJsonObject> messageObject = choiceObject->GetObjectField(TEXT("message"));

						if (messageObject->HasField(TEXT("content")))
						{
							FString content = messageObject->GetStringField(TEXT("content"));
							UE_LOG(LogTemp, Warning, TEXT("Content: %s"), *content);
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("Il campo 'content' non è presente in 'message'"));
						}
					}
				}


				checkRole = results[0]->AsObject()->GetObjectField(TEXT("message"))->GetStringField(TEXT("role"));

				if (checkRole == "system")
					role = GPTRoleType::SYSTEM;
				else if (checkRole == "assistant")
					role = GPTRoleType::ASSISTANT;
				else if (checkRole == "function")
					role = GPTRoleType::FUNCTION;
				else if (checkRole == "user")
					role = GPTRoleType::USER;


				//IncomingGPTResponse.Broadcast(results[0]->AsObject()->GetObjectField(TEXT("message"))->GetStringField(TEXT("content")), role);
				IncomingGPTResponse.Broadcast(results[0]->AsObject()->GetObjectField(TEXT("choices"))->GetStringField(TEXT("content")), role);
			}
		}
	}
}

void UOllamaComponent::OnGPTPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived) {
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
		UE_LOG(LogTemp, Warning, TEXT("[GPT Stream] Lunghezza contenuto: %d bytes"), message.Len());



		while (myMatcher.FindNext())
		{
			blocksReading++;
			if (blocksReading > blocksRead) {
				data = myMatcher.GetCaptureGroup(1);

				//UE_LOG(LogTemp, Warning, TEXT("[GPT Stream] Raw buffer:\n%s"), *message);


				TSharedPtr<FJsonValue> JsonValue;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(data);

				if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
					const TSharedPtr<FJsonObject>* FileMessageObject;

					if (JsonValue->TryGetObject(FileMessageObject)) {
						results = FileMessageObject->Get()->GetArrayField(TEXT("choices"));

						TSharedPtr<FJsonObject> ChoiceObj = results[0]->AsObject();

						const TSharedPtr<FJsonObject>* DeltaObj;

						if (ChoiceObj->TryGetObjectField(TEXT("delta"), DeltaObj))
						{
							FString Fragment;
							if ((*DeltaObj)->TryGetStringField(TEXT("content"), Fragment))
							{
								// Accumula solo se non vuoto
								outFragment.Append(Fragment);
								UE_LOG(LogTemp, Warning, TEXT("[GPT Stream] Dati aggiornati: \"%s\""), *outFragment);
								IncomingGPTStreamResponse.Broadcast(outFragment, role, endStream == "stop");//broadcast
							}
						}

						results[0]->AsObject()->TryGetStringField(TEXT("finish_reason"), endStream);
						if (endStream != "stop") {

							blocksRead++; // WE CONTINUE (A)

							results[0]->AsObject()->TryGetStringField(TEXT("role"), checkRole);
							if (checkRole == "system")
								role = GPTRoleType::SYSTEM;
							else if (checkRole == "assistant")
								role = GPTRoleType::ASSISTANT;
							else if (checkRole == "function")
								role = GPTRoleType::FUNCTION;
							else if (checkRole == "user")
								role = GPTRoleType::USER;

							//outFragment.Append(results[0]->AsObject()->GetObjectField(TEXT("message"))->GetStringField(TEXT("content")));
						}
						else {
							blocksRead = 0;
							UE_LOG(LogTemp, Warning, TEXT("[GPT Stream] Detected finish_reason == stop"));
						}
					}
				}
			}

		}

	}
}

void UOllamaComponent::getGPTCompletion(TArray<FChatTurn> messages, FString apiMethod, bool stream) {
	FHttpModule* Http = &FHttpModule::Get();
	FString payload;
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();

	Request->SetURL("http://localhost:1234/api/v0/chat/completions");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
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
	payloadObject->SetStringField(TEXT("model"), apiMethod);
	payloadObject->SetBoolField("stream", stream);

	FJsonSerializer::Serialize(payloadObject.ToSharedRef(), TJsonWriterFactory<>::Create(&payload));
	Request->SetContentAsString(payload);



	if (stream) {
		Request->OnRequestProgress64().BindUObject(this, &UOllamaComponent::OnGPTPartialResponseReceived);
	}
	else {
		Request->OnProcessRequestComplete().BindUObject(this, &UOllamaComponent::OnGPTResponseReceived);
	}

	Request->ProcessRequest();
	UE_LOG(LogTemp, Warning, TEXT("[GPT Request] Request sent"));
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
