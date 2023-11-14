#include "AzureNLUThread.h"

using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Intent;

AzureNLUThread* AzureNLUThread::Runnable = NULL;

AzureNLUThread::AzureNLUThread(shared_ptr<SpeechConfig> config, shared_ptr<LanguageUnderstandingModel> model) : StopTaskCounter(0)
{
	NLUConfig = config;
	NLUModel = model;
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

AzureNLUThread* AzureNLUThread::setup(shared_ptr<SpeechConfig> config, shared_ptr<LanguageUnderstandingModel> model)
{
	//if (!Runnable && FPlatformProcess::SupportsMultithreading())
	if (FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new AzureNLUThread(config, model);
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

TArray<UNLUEntity*> AzureNLUThread::BuildEntitiesTree(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUEntity*> entities) {
	for (TSharedPtr<FJsonValue> item : items) {

		uint8 index = entities.Add(NewObject <UNLUEntity>());

		entities[index]->entity = item->AsObject()->GetStringField("entity");
		entities[index]->type = item->AsObject()->GetStringField("type");
		entities[index]->startIndex = item->AsObject()->GetIntegerField("startIndex");
		entities[index]->endIndex = item->AsObject()->GetIntegerField("endIndex");
		entities[index]->score = item->AsObject()->GetNumberField("score");

		entities[index]->childName = item->AsObject()->GetStringField("childName");
		TArray<TSharedPtr<FJsonValue>> children = item->AsObject()->GetArrayField("children");
		entities[index]->children = BuildEntitiesTree(children, entities[index]->children);
	}
	return entities;
}

void AzureNLUThread::StartOneShotRecognition()
{
	recognizer = IntentRecognizer::FromConfig(NLUConfig);
	recognizer->AddAllIntents(NLUModel);
	recognizer->Properties.SetProperty("show-all-intents", "true");
	recognizer->Properties.SetProperty("verbose", "true");

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
				if (FileMessageObject->Get()->TryGetStringField("query", stringField)) {

					NLUResponse.query = FileMessageObject->Get()->GetStringField("query");
					NLUResponse.topIntent = FileMessageObject->Get()->GetObjectField("topScoringIntent")->GetStringField("intent");
					NLUResponse.score = FileMessageObject->Get()->GetObjectField("topScoringIntent")->GetNumberField("score");

					if (FileMessageObject->Get()->TryGetArrayField("entities", arrayField)) {

						TArray<TSharedPtr<FJsonValue>> jsonEntities = FileMessageObject->Get()->GetArrayField("entities");
						TArray<UNLUEntity*> entities;

						NLUResponse.entities = BuildEntitiesTree(jsonEntities, NLUResponse.entities);
					}
				}
				NLUResultAvailable.Broadcast(NLUResponse);
			}
		}
	}
	else if (result->Reason == ResultReason::RecognizedSpeech)
	{
		//cout << "RECOGNIZED: Text=" << result->Text << " (intent could not be recognized)" << std::endl;
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