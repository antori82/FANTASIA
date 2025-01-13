#include "AzureNLUThread.h"

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Intent;
using namespace Microsoft::CognitiveServices::Speech::Audio;

AzureNLUThread* AzureNLUThread::Runnable = NULL;

AzureNLUThread::AzureNLUThread(shared_ptr<SpeechConfig> config, std::vector<std::shared_ptr<LanguageUnderstandingModel>> models) : StopTaskCounter(0)
{
	NLUConfig = config;
	NLUModels = models;
	Thread = FRunnableThread::Create(this, TEXT("AzureNLUThread"), 0, TPri_BelowNormal);
}

AzureNLUThread::~AzureNLUThread() {
	delete Thread;
	Thread = NULL;
}

bool AzureNLUThread::Init()
{
	return true;
}

uint32 AzureNLUThread::Run()
{
	StartOneShotRecognition();
	//Shutdown();
	return 0;
}

void AzureNLUThread::Stop()
{
	StopTaskCounter.Increment();
}

AzureNLUThread* AzureNLUThread::setup(shared_ptr<SpeechConfig> config, std::vector<std::shared_ptr<LanguageUnderstandingModel>> models)
{
	if (FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new AzureNLUThread(config, models);
	}
	return Runnable;
}

void AzureNLUThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void AzureNLUThread::Shutdown()
{
	if (Runnable)
	{
		Runnable = NULL;
	}
}

TArray<UNLUEntity*> AzureNLUThread::BuildEntities(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUEntity*> entities) {
	const TArray<TSharedPtr<FJsonValue>>* arrayField;
	TArray<TSharedPtr<FJsonValue>> children;

	for (TSharedPtr<FJsonValue> item : items) {

		uint8 index = entities.Add(NewObject <UNLUEntity>());

		entities[index]->entity = item->AsObject()->GetStringField(TEXT("text"));
		entities[index]->type = item->AsObject()->GetStringField(TEXT("category"));
		entities[index]->startIndex = item->AsObject()->GetIntegerField(TEXT("offset"));
		entities[index]->endIndex = item->AsObject()->GetIntegerField(TEXT("offset")) + item->AsObject()->GetIntegerField(TEXT("length"));
		entities[index]->score = item->AsObject()->GetNumberField(TEXT("confidenceScore"));

		if (item->AsObject()->TryGetArrayField(TEXT("resolutions"), arrayField)) {
			children = item->AsObject()->GetArrayField(TEXT("resolutions"));
			for (TSharedPtr<FJsonValue> child : children) {
				uint8 childIndex = entities[index]->children.Add(NewObject <UNLUEntity>());

				entities[index]->children[childIndex]->entity = child->AsObject()->GetStringField(TEXT("value"));
				entities[index]->children[childIndex]->type = child->AsObject()->GetStringField(TEXT("resolutionKind"));
			}
		}

		if (item->AsObject()->TryGetArrayField(TEXT("extraInformation"), arrayField)) {
			children = item->AsObject()->GetArrayField(TEXT("extraInformation"));
			for (TSharedPtr<FJsonValue> child : children) {
				uint8 childIndex = entities[index]->children.Add(NewObject <UNLUEntity>());

				entities[index]->children[childIndex]->type = child->AsObject()->GetStringField(TEXT("extraInformationKind"));

				if (entities[index]->children[childIndex]->type == "ListKey")
					entities[index]->children[childIndex]->entity = child->AsObject()->GetStringField(TEXT("key"));
				else
					entities[index]->children[childIndex]->entity = child->AsObject()->GetStringField(TEXT("value"));
			}
		}
	}
	return entities;
}

TArray<UNLUIntent*> AzureNLUThread::BuildIntents(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUIntent*> intents) {

	for (TSharedPtr<FJsonValue> item : items) {

		uint8 index = intents.Add(NewObject <UNLUIntent>());

		intents[index]->intent = item->AsObject()->GetStringField(TEXT("category"));
		intents[index]->confidence = item->AsObject()->GetStringField(TEXT("confidenceScore"));
	}
	return intents;
}

void AzureNLUThread::StartOneShotRecognition()
{
	auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
	recognizer = IntentRecognizer::FromConfig(NLUConfig, audioConfig);
	recognizer->ApplyLanguageModels(NLUModels);

	auto result = recognizer->RecognizeOnceAsync().get();

	if (result->Reason == ResultReason::RecognizedIntent)
	{
		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(UTF8_TO_TCHAR(result->Properties.GetProperty(PropertyId::LanguageUnderstandingServiceResponse_JsonResult).c_str()));
		FString temp = result->Properties.GetProperty(PropertyId::LanguageUnderstandingServiceResponse_JsonResult).c_str();
		const TSharedPtr<FJsonObject>* FileMessageObject;
		const TArray<TSharedPtr<FJsonValue>>* arrayField;
		FString stringField;

		if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
			FNLUResponse NLUResponse;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				if (FileMessageObject->Get()->GetObjectField(TEXT("result"))->TryGetStringField(TEXT("query"), stringField)) {

					NLUResponse.query = FileMessageObject->Get()->GetObjectField(TEXT("result"))->GetStringField(TEXT("query"));
					NLUResponse.intents = BuildIntents(FileMessageObject->Get()->GetObjectField(TEXT("result"))->GetObjectField(TEXT("prediction"))->GetArrayField(TEXT("intents")), NLUResponse.intents);

					if (FileMessageObject->Get()->GetObjectField(TEXT("result"))->GetObjectField(TEXT("prediction"))->TryGetArrayField(TEXT("entities"), arrayField)) {

						TArray<TSharedPtr<FJsonValue>> jsonEntities = FileMessageObject->Get()->GetObjectField(TEXT("result"))->GetObjectField(TEXT("prediction"))->GetArrayField(TEXT("entities"));
						TArray<UNLUEntity*> entities;

						NLUResponse.entities = BuildEntities(jsonEntities, NLUResponse.entities);
					}
				}
				NLUResultAvailable.Broadcast(NLUResponse);
			}
		}
	}
	else if (result->Reason == ResultReason::RecognizedSpeech)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AzureNLUComponent] Could not recognise intent for \"%hs\""), result->Text.c_str());
	}
	else if (result->Reason == ResultReason::NoMatch)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AzureNLUComponent] NOMATCH: Speech could not be recognized."));
		FNLUResponse noMatchResponse;
		UNLUIntent *noMatchIntent = NewObject<UNLUIntent>();

		noMatchResponse.query = "NOMATCH";
		noMatchIntent->intent = "None";
		noMatchIntent->confidence = "1.0";
		noMatchResponse.intents.Add(noMatchIntent);

		TArray<UNLUEntity*> entities;
		noMatchResponse.entities = entities;
		NLUResultAvailable.Broadcast(noMatchResponse);
	}
	else if (result->Reason == ResultReason::Canceled)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AzureNLUComponent] CANCELED: %hs"), CancellationDetails::FromResult(result)->ErrorDetails.c_str());
	}
}

FDelegateHandle AzureNLUThread::NLUResultAvailableSubscribeUser(FNLUResultAvailableDelegate& UseDelegate)
{
	return NLUResultAvailable.Add(UseDelegate);
}

void AzureNLUThread::NLUResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	NLUResultAvailable.Remove(DelegateHandle);
}