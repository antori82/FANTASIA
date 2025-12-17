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
private:

	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void OnGPTPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived);

public:
	// Sets default values for this component's properties
	UOpenAIComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTStreamResponseEvent IncomingGPTStreamResponse;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetChatGPTCompletion", AutoCreateRefTerm = "messages"), Category = "GPT")
	void getGPTCompletion(TArray<FChatTurn> messages, FString apiMethod = "gpt-4-turbo-preview", bool stream = false);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};