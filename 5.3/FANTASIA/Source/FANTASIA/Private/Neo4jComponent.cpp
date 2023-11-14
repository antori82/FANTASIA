// Fill out your copyright notice in the Description page of Project Settings.


#include "Neo4jComponent.h"
#include "Misc/Base64.h"
// Sets default values for this component's properties
UNeo4jComponent::UNeo4jComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UNeo4jComponent::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FNeo4jResponse neo4jResponse;
	FRegexPattern pattern(TEXT("\\d+$"));
	TArray<FString> location;

	if (bWasSuccessful) {
		FString responseCode = "Response code : " + FString::FromInt(Response->GetResponseCode());
		if (Response->GetResponseCode() == 200 || Response->GetResponseCode() == 201) {
			Response->GetHeader("Location").ParseIntoArray(location, TEXT("/"));

			if (location.Num() == 0)
				Response->GetHeader("commit").ParseIntoArray(location, TEXT("/"));

			if (location.Num() > 0)
				neo4jResponse.transactionID = location[location.Num() - 1];
			TSharedPtr<FJsonValue> JsonValue;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
			if (FJsonSerializer::Deserialize(Reader, JsonValue)) {
				FString temp = Response->GetContentAsString();

				const TSharedPtr<FJsonObject>* FileMessageObject;

				if (JsonValue->TryGetObject(FileMessageObject)) {
					TArray<TSharedPtr<FJsonValue>> results = FileMessageObject->Get()->GetArrayField("results");
					for (TSharedPtr<FJsonValue> result : results) {
						TArray<TSharedPtr<FJsonValue>> columns = result->AsObject()->GetArrayField("columns");
						if (neo4jResponse.headers.Num() == 0)
							for (TSharedPtr<FJsonValue> header : columns)
								neo4jResponse.headers.Add(header->AsString());

						TArray<TSharedPtr<FJsonValue>> data = result->AsObject()->GetArrayField("data");

						for (TSharedPtr<FJsonValue> datum : data) {
							TArray<TSharedPtr<FJsonValue>> jsonRow = datum->AsObject()->GetArrayField("row");
							TArray<TSharedPtr<FJsonValue>> jsonMeta = datum->AsObject()->GetArrayField("meta");
							TArray<TSharedPtr<FJsonValue>> jsonNodes = datum->AsObject()->GetObjectField("graph")->GetArrayField("nodes");
							TArray<TSharedPtr<FJsonValue>> jsonRelationships = datum->AsObject()->GetObjectField("graph")->GetArrayField("relationships");

							FString list = "";

							neo4jResponse.rows.Add(NewObject<UNeo4jResultRow>());

							for (int i = 0; i < neo4jResponse.headers.Num(); i++) {
								//TSharedPtr<FJsonObject> metaData = jsonMeta[i]->AsObject();

								if (jsonMeta[i]->TryGetObject(FileMessageObject)) {
									if (!FileMessageObject->Get()->TryGetField("type").IsValid()) {
										neo4jResponse.rows.Last()->cells.Add(neo4jResponse.headers[i], NewObject<UNeo4jResultCellSimple>());
										((UNeo4jResultCellSimple*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->value = jsonRow[i]->AsString();
									}
									else if (FileMessageObject->Get()->GetStringField("type") == "node") {
										neo4jResponse.rows.Last()->cells.Add(neo4jResponse.headers[i], NewObject<UNeo4jResultCellNode>());
										((UNeo4jResultCellNode*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->id = FileMessageObject->Get()->GetIntegerField("id");

										for (int j = 0; j < jsonNodes.Num() && ((UNeo4jResultCellNode*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->labels.Num() == 0 && ((UNeo4jResultCellNode*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->properties.Num() == 0; j++) {
											if (FCString::Atoi(*jsonNodes[j]->AsObject()->GetStringField("id")) == FileMessageObject->Get()->GetIntegerField("id")) {
												for (TSharedPtr<FJsonValue> label : jsonNodes[j]->AsObject()->GetArrayField("labels"))
													((UNeo4jResultCellNode*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->labels.Add(label->AsString());
												for (TMap<FString, TSharedPtr<FJsonValue>>::TIterator nodesIt = jsonNodes[j]->AsObject()->GetObjectField("properties")->Values.CreateIterator(); nodesIt; ++nodesIt) {
													if (nodesIt.Value()->AsArray().Num() == 0)
														((UNeo4jResultCellNode*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->properties.Add(*nodesIt.Key(), *nodesIt.Value()->AsString());
													else {
														list = "";
														for (TSharedPtr<FJsonValue> item : nodesIt.Value()->AsArray())
															list.Append(item->AsString() + "|");
														((UNeo4jResultCellNode*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->properties.Add(*nodesIt.Key(), list.LeftChop(1));
													}
												}
											}
										}
									}
									else if (FileMessageObject->Get()->GetStringField("type") == "relationship") {
										neo4jResponse.rows.Last()->cells.Add(neo4jResponse.headers[i], NewObject<UNeo4jResultCellRelationship>());
										((UNeo4jResultCellRelationship*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->id = FileMessageObject->Get()->GetIntegerField("id");

										for (int j = 0; j < jsonRelationships.Num() && ((UNeo4jResultCellRelationship*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->label.IsEmpty() && ((UNeo4jResultCellRelationship*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->properties.Num() == 0; j++) {
											if (FCString::Atoi(*jsonRelationships[j]->AsObject()->GetStringField("id")) == FileMessageObject->Get()->GetIntegerField("id")) {
												((UNeo4jResultCellRelationship*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->label = jsonRelationships[j]->AsObject()->GetStringField("label");
												for (TMap<FString, TSharedPtr<FJsonValue>>::TIterator RelsIt = jsonRelationships[j]->AsObject()->GetObjectField("properties")->Values.CreateIterator(); RelsIt; ++RelsIt) {
													if (RelsIt.Value()->AsArray().Num() == 0)
														((UNeo4jResultCellNode*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->properties.Add(*RelsIt.Key(), *RelsIt.Value()->AsString());
													else {
														list = "";
														for (TSharedPtr<FJsonValue> item : RelsIt.Value()->AsArray())
															list.Append(item->AsString() + "|");
														((UNeo4jResultCellNode*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->properties.Add(*RelsIt.Key(), list.LeftChop(1));
													}
												}
											}
										}
									}
								}
								else {
									neo4jResponse.rows.Last()->cells.Add(neo4jResponse.headers[i], NewObject<UNeo4jResultCellSimple>());
									((UNeo4jResultCellSimple*)neo4jResponse.rows.Last()->cells[neo4jResponse.headers[i]])->value = jsonRow[i]->AsString();
								}
							}
						}
					}
					//IncomingResponse.Broadcast(neo4jResponse);
				}
				IncomingResponse.Broadcast(neo4jResponse);
			}
		}
	}

}

void UNeo4jComponent::submitQuery(FString query, Neo4jOperation operation, FString transactionID, TMap<FString, FString> parameters, FString database = "neo4j") {
	FString path;
	FString method;
	FString prefix;

	FHttpModule* Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UNeo4jComponent::OnResponseReceived);

	if (useV4)
		prefix = "/db/data/transaction";
	else
		prefix = "/db/" + database + "/tx";

	switch (operation)
	{
	case Neo4jOperation::SINGLE_REQUEST:
		path = prefix + "/commit";
		method = "POST";
		break;
	case Neo4jOperation::BEGIN_TRANSACTION:
		path = prefix;
		method = "POST";
		break;
	case Neo4jOperation::COMMIT_TRANSACTION:
		path = prefix + "/" + transactionID + "/commit";
		method = "POST";
		break;
	case Neo4jOperation::ROLLBACK_TRANSACTION:
		path = prefix + "/" + transactionID;
		method = "DELETE";
		break;
	case Neo4jOperation::ADD_TO_TRANSACTION:
		path = prefix + "/" + transactionID;
		method = "POST";
		break;
	default:
		break;
	}

	Request->SetURL(endpoint + ":" + FString::FromInt(port) + path);
	Request->SetVerb(method);
	Request->SetHeader(TEXT("Authorization"), "Basic " + FBase64::Encode(user + ":" + password));
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	if (query.IsEmpty())
		query = "MATCH (n) RETURN n LIMIT 1";

	query.ReplaceInline(TEXT("\r\n"), TEXT(" "));
	query.ReplaceInline(TEXT("\n"), TEXT(" "));
	query.ReplaceInline(TEXT("\\"), TEXT("\\\\"));
	query.ReplaceInline(TEXT("\""), TEXT("\\\""));
	FString payload = "{\"statements\" : [{\"statement\" : \"" + query + "\", ";
	TArray<FString> keys;
	if (parameters.GetKeys(keys) > 0) {
		payload += "\"parameters\": {";
		for (FString key : keys) {
			FString paramString = *parameters.Find(key);
			if (paramString.StartsWith("["))
				payload = payload + "\"" + key + "\": " + paramString + ", ";
			else {
				paramString = paramString.Replace(TEXT("\""), TEXT("\\\""));
				payload = payload + "\"" + key + "\": \"" + paramString + "\", ";
			}
		}
		payload = payload.LeftChop(2) + "}, ";
	}
	//payload = payload + "\"database\": { name: \"" + database + "\"}}, ";

	Request->SetContentAsString(payload + "\"resultDataContents\" : [ \"row\", \"graph\" ]}]}");
	Request->ProcessRequest();
}

// Called when the game starts
void UNeo4jComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UNeo4jComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
