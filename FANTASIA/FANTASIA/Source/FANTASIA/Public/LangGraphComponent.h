#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "LangGraphComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingLangGraphThreadCreateResponseEvent, FString, threadID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIncomingLangGraphResponseEvent, FString, LangGraphResponse, GPTRoleType, role);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIncomingLangGraphStreamResponseEvent, FString, LangGraphResponse, GPTRoleType, role, bool, endStream);

UCLASS(ClassGroup = (OpenAI), meta = (BlueprintSpawnableComponent), config=Game)
class ULangGraphComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	void OnLangGraphResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void OnLangGraphPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived);

	void OnLangGraphThreadCreateResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

public:
	// Sets default values for this component's properties
	ULangGraphComponent();

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString endpoint;
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	int port;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingLangGraphResponseEvent IncomingLangGraphResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingLangGraphStreamResponseEvent IncomingLangGraphStreamResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingLangGraphThreadCreateResponseEvent LangGraphThreadCreateResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create LangGraph thread"), Category = "LangGraph")
	void createLangGraphThread(FString threadID);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Delete LangGraph thread"), Category = "LangGraph")
	void deleteLangGraphThread(FString threadID);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LangGraph query", AutoCreateRefTerm = "messages"), Category = "LangGraph")
	void langGraphQuery(TArray<FChatTurn> messages, FString threadID, FString assistantID, FString model = "openai/gpt-4o", int recursionLimit = 10, bool stream = false);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};