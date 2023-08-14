#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "OpenAIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingGPTResponseEvent, FString, GPTResponse);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIncomingChatGPTResponseEvent, FString, chatGPTResponse, FString, role);

UENUM(BlueprintType)
enum class ChatGPTRoleType : uint8 {
	SYSTEM = 0 UMETA(DisplayName = "SYSTEM"),
	ASSISTANT = 1 UMETA(DisplayName = "ASSISTANT"),
	USER = 2 UMETA(DisplayName = "USER"),
	FUNCTION = 3 UMETA(DisplayName = "FUNCTION"),
	};

USTRUCT(Blueprintable)
struct FChatTurn
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	ChatGPTRoleType role = ChatGPTRoleType::USER;

	UPROPERTY(BlueprintReadWrite)
	FString content = TEXT("");
};

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

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingChatGPTResponseEvent IncomingChatGPTResponse;

	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnChatGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetGPTCompletion", AutoCreateRefTerm = "stopSequences"), Category = "GPT")
	void getGPTCompletion(FString prompt, TArray<FString> stopSequences, FString apiMethod = "text-davinci-003", int maxTokens = 1000, float temperature = 0.7);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetChatGPTCompletion", AutoCreateRefTerm = "messages"), Category = "GPT")
	void getChatGPTCompletion(TArray<FChatTurn> messages, FString apiMethod = "gpt-4");

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};