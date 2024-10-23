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

public:
	// Sets default values for this component's properties
	UGroqComponent();

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingChatGPTResponseEvent IncomingChatGPTResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetChatGPTCompletion", AutoCreateRefTerm = "messages"), Category = "GPT")
	void getChatGPTCompletion(TArray<FChatTurn> messages, FString apiMethod = "llama3-8b-8192");

	void OnChatGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
};