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
}

AzureNLUThread* AzureNLUThread::setup(shared_ptr<SpeechConfig> config, shared_ptr<LanguageUnderstandingModel> model)
{
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
		Runnable = NULL;
	}
}

TArray<UNLUEntity*> AzureNLUThread::BuildEntitiesTree(TArray<TSharedPtr<FJsonValue>> items, TArray<UNLUEntity*> entities) {
	for (TSharedPtr<FJsonValue> item : items) {

		uint8 index= entities.Add(NewObject <UNLUEntity>());

		entities[index]->entity = item->AsObject()->GetStringField("entity");
		entities[index]->type = item->AsObject()->GetStringField("type");
		entities[index]->startIndex = item->AsObject()->GetIntegerField("startIndex");
		entities[index]->endIndex = item->AsObject()->GetIntegerField("endIndex");
		entities[index]->score = item->AsObject()->GetNumberField("score");

		entities[index]->childName = item->AsObject()->GetStringField("childName");

		TArray<TSharedPtr<FJsonValue>> children = item->AsObject()->GetArrayField("children");
		entities[index]->children= BuildEntitiesTree(children, entities[index]->children);
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

	//TODO: Add better error management
	if (result->Reason == ResultReason::RecognizedIntent)
	{
		TSharedPtr<FJsonValue> JsonValue;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(result->Properties.GetProperty(PropertyId::LanguageUnderstandingServiceResponse_JsonResult).c_str());

		if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
			FNLUResponse NLUResponse;
			NLUResponse.query= JsonValue->AsObject()->GetStringField("query");
			NLUResponse.topIntent= JsonValue->AsObject()->GetObjectField("topScoringIntent")->GetStringField("intent");
			NLUResponse.score= JsonValue->AsObject()->GetObjectField("topScoringIntent")->GetNumberField("score");
			
			TArray<TSharedPtr<FJsonValue>> jsonEntities = JsonValue->AsObject()->GetArrayField("entities");
			TArray<UNLUEntity*> entities;

			NLUResponse.entities= BuildEntitiesTree(jsonEntities, NLUResponse.entities);

			NLUResultAvailable.Broadcast(NLUResponse);
		}
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