#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"

#include "LmstudioComponent.generated.h"

UCLASS(ClassGroup = (OpenAI), meta = (BlueprintSpawnableComponent), config = Game)
class ULmstudioComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void OnGPTPartialResponseReceived(FHttpRequestPtr Request, uint64 bytesSent, uint64 bytesReceived);


public:

	ULmstudioComponent();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTStreamResponseEvent IncomingGPTStreamResponse;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetLmStudioCompletion", AutoCreateRefTerm = "messages"), Category = "GPT")
	void getGPTCompletion(TArray<FChatTurn> messages, FString apiMethod = "gpt-4-turbo-preview", bool stream = false);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

};