#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "GroqComponent.generated.h"

UCLASS(ClassGroup = (Groq), meta = (BlueprintSpawnableComponent), config=Game)
class UGroqComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void OnGPTPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived);

public:
	// Sets default values for this component's properties
	UGroqComponent();

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingChatGPTResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTStreamResponseEvent IncomingGPTStreamResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetGroqGPTCompletion", AutoCreateRefTerm = "messages"), Category = "GPT")
	void getGPTCompletion(TArray<FChatTurn> messages, FString apiMethod = "llama3-8b-8192", bool stream = false);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
};