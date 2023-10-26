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
	//switch (ASRMode) {
	//case EAzureASREnum::ASR_CONTINUOUS:
	//	StopContinuousRecognition();
	//}
}

AzureNLUThread* AzureNLUThread::setup(shared_ptr<SpeechConfig> config, std::vector<std::shared_ptr<LanguageUnderstandingModel>> models)
{
	//if (!Runnable && FPlatformProcess::SupportsMultithreading())
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
		//Runnable->EnsureCompletion();
		//delete Runnable;
		Runnable = NULL;
	}
}

TArray<UNLUEntity*> AzureNLUThread::BuildEntities(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUEntity*> entities) {
	const TArray<TSharedPtr<FJsonValue>>* arrayField;
	TArray<TSharedPtr<FJsonValue>> children;

	for (TSharedPtr<FJsonValue> item : items) {

		uint8 index = entities.Add(NewObject <UNLUEntity>());

		entities[index]->entity = item->AsObject()->GetStringField("text");
		entities[index]->type = item->AsObject()->GetStringField("category");
		entities[index]->startIndex = item->AsObject()->GetIntegerField("offset");
		entities[index]->endIndex = item->AsObject()->GetIntegerField("offset") + item->AsObject()->GetIntegerField("length");
		entities[index]->score = item->AsObject()->GetNumberField("confidenceScore");

		if (item->AsObject()->TryGetArrayField("resolutions", arrayField)) {
			children = item->AsObject()->GetArrayField("resolutions");
			for (TSharedPtr<FJsonValue> child : children) {
				uint8 childIndex = entities[index]->children.Add(NewObject <UNLUEntity>());

				entities[index]->children[childIndex]->entity = child->AsObject()->GetStringField("value");
				entities[index]->children[childIndex]->type = child->AsObject()->GetStringField("resolutionKind");
			}
		}

		if (item->AsObject()->TryGetArrayField("extraInformation", arrayField)) {
			children = item->AsObject()->GetArrayField("extraInformation");
			for (TSharedPtr<FJsonValue> child : children) {
				uint8 childIndex = entities[index]->children.Add(NewObject <UNLUEntity>());

				entities[index]->children[childIndex]->type = child->AsObject()->GetStringField("extraInformationKind");

				if (entities[index]->children[childIndex]->type == "ListKey")
					entities[index]->children[childIndex]->entity = child->AsObject()->GetStringField("key");
				else
					entities[index]->children[childIndex]->entity = child->AsObject()->GetStringField("value");
			}
		}
	}
	return entities;
}

TArray<UNLUIntent*> AzureNLUThread::BuildIntents(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUIntent*> intents) {

	for (TSharedPtr<FJsonValue> item : items) {

		uint8 index = intents.Add(NewObject <UNLUIntent>());

		intents[index]->intent = item->AsObject()->GetStringField("category");
		intents[index]->confidence = item->AsObject()->GetStringField("confidenceScore");
	}
	return intents;
}

void AzureNLUThread::StartOneShotRecognition()
{
	auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();
	recognizer = IntentRecognizer::FromConfig(NLUConfig, audioConfig);
	recognizer->ApplyLanguageModels(NLUModels);

	//recognizer = IntentRecognizer::FromConfig(NLUConfig);
	//recognizer->AddAllIntents(NLUModel);
	//recognizer->Properties.SetProperty("show-all-intents", "true");
	//recognizer->Properties.SetProperty("verbose", "true");

	auto result = recognizer->RecognizeOnceAsync().get();

	if (result->Reason == ResultReason::RecognizedIntent)
	{
		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(result->Properties.GetProperty(PropertyId::LanguageUnderstandingServiceResponse_JsonResult).c_str());
		FString temp = result->Properties.GetProperty(PropertyId::LanguageUnderstandingServiceResponse_JsonResult).c_str();
		const TSharedPtr<FJsonObject>* FileMessageObject;
		const TArray<TSharedPtr<FJsonValue>>* arrayField;
		FString stringField;

		if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
			FNLUResponse NLUResponse;

			if (JsonValue->TryGetObject(FileMessageObject)) {
				if (FileMessageObject->Get()->GetObjectField("result")->TryGetStringField("query", stringField)) {

					NLUResponse.query = FileMessageObject->Get()->GetObjectField("result")->GetStringField("query");
					NLUResponse.intents = BuildIntents(FileMessageObject->Get()->GetObjectField("result")->GetObjectField("prediction")->GetArrayField("intents"), NLUResponse.intents);

					if (FileMessageObject->Get()->GetObjectField("result")->GetObjectField("prediction")->TryGetArrayField("entities", arrayField)) {

						TArray<TSharedPtr<FJsonValue>> jsonEntities = FileMessageObject->Get()->GetObjectField("result")->GetObjectField("prediction")->GetArrayField("entities");
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
		FString test = UTF8_TO_TCHAR(result->Text.c_str());
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Could not recognise intent for \"%s\""), result->Text);
	}
	else if (result->Reason == ResultReason::NoMatch)
	{
		//cout << "NOMATCH: Speech could not be recognized." << std::endl;
	}
	else if (result->Reason == ResultReason::Canceled)
	{
		/*auto cancellation = CancellationDetails::FromResult(result);
		cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

		if (cancellation->Reason == CancellationReason::Error)
		{
			cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
			cout << "CANCELED: ErrorDetails=" << cancellation->ErrorDetails << std::endl;
			cout << "CANCELED: Did you update the subscription info?" << std::endl;
		}*/
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