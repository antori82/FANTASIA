#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "FANTASIATypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Neo4jComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingNeo4jResponseEvent, FNeo4jResponse, Neo4jResponse);

UCLASS(ClassGroup = (Neo4j), meta = (BlueprintSpawnableComponent))
class UNeo4jComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UNeo4jComponent();
	UPROPERTY(EditAnywhere, Category = "Settings")
	FString endpoint;
	UPROPERTY(EditAnywhere, Category = "Settings")
	int port;
	UPROPERTY(EditAnywhere, Category = "Settings")
	FString user;
	UPROPERTY(EditAnywhere, Category = "Settings")
	FString password;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingNeo4jResponseEvent IncomingResponse;
	UPROPERTY(BlueprintReadOnly)
	FString response;
	UPROPERTY(EditAnywhere, Category = "Settings")
	bool useV4;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query", AutoCreateRefTerm = "parameters"), Category = "Neo4j")
	void submitQuery(FString query, Neo4jOperation operation, FString transactionID, TMap<FString, FString> parameters, FString database);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};