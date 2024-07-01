#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "OllamaComponent.generated.h"

UCLASS(ClassGroup = (OpenAI), meta = (BlueprintSpawnableComponent), config=Game)
class UOllamaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOllamaComponent();

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString endpoint;
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	int port;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingChatGPTResponseEvent IncomingChatGPTResponse;

	void OnOllamaGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnOllamaChatGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetOllamaGPTCompletion"), Category = "GPT")
	void getOllamaGPTCompletion(FString prompt, FString model = "llama3");

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetOllamaChatGPTCompletion", AutoCreateRefTerm = "messages"), Category = "GPT")
	void getOllamaChatGPTCompletion(TArray<FChatTurn> messages, FString model = "llama3");

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};