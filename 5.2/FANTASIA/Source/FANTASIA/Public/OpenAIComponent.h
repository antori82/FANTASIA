#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "OpenAIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingGPTResponseEvent, FString, GPTResponse);

UCLASS(ClassGroup = (OpenAI), meta = (BlueprintSpawnableComponent))
class UOpenAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenAIComponent();
	UPROPERTY(EditAnywhere, Category = "Settings")
	FString Key;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetGPTCompletion", AutoCreateRefTerm = "stopSequences"), Category = "GPT")
	void getGPTCompletion(FString prompt, TArray<FString> stopSequences, FString apiMethod = "text-davinci-003", int maxTokens = 1000, float temperature = 0.7);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};