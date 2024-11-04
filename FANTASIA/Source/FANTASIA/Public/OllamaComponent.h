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

private:

	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void OnGPTPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived);

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
	FIncomingGPTStreamResponseEvent IncomingGPTStreamResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetOllamaGPTCompletion", AutoCreateRefTerm = "messages"), Category = "GPT")
	void getGPTCompletion(TArray<FChatTurn> messages, FString model = "llama3", bool stream = false);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};