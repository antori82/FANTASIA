#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "OpenAIComponent.generated.h"

UCLASS(ClassGroup = (OpenAI), meta = (BlueprintSpawnableComponent), config=Game)
class UOpenAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenAIComponent();

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingChatGPTResponseEvent IncomingChatGPTResponse;

	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnChatGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetGPTCompletion", AutoCreateRefTerm = "stopSequences"), Category = "GPT")
	void getGPTCompletion(FString prompt, TArray<FString> stopSequences, FString apiMethod = "gpt-4-turbo-preview", int maxTokens = 1000, float temperature = 0.7);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetChatGPTCompletion", AutoCreateRefTerm = "messages"), Category = "GPT")
	void getChatGPTCompletion(TArray<FChatTurn> messages, FString apiMethod = "gpt-4-turbo-preview");

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};