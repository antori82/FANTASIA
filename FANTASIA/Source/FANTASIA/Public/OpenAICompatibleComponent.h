#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "OpenAICompatibleComponent.generated.h"

UENUM(BlueprintType)
enum class ELLMProvider : uint8
{
	Custom		= 0 UMETA(DisplayName = "Custom"),
	OpenAI		= 1 UMETA(DisplayName = "OpenAI"),
	Groq		= 2 UMETA(DisplayName = "Groq"),
	Ollama		= 3 UMETA(DisplayName = "Ollama"),
	LMStudio	= 4 UMETA(DisplayName = "LM Studio"),
	vLLM		= 5 UMETA(DisplayName = "vLLM"),
};

USTRUCT(BlueprintType)
struct FOpenAICompatibleConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM", Config)
	FString URL = TEXT("https://api.openai.com/v1/chat/completions");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM", Config)
	FString APIKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM", Config)
	FString DefaultModel = TEXT("gpt-4-turbo-preview");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM", Config, meta = (ClampMin = "1", ClampMax = "300"))
	int32 TimeoutSeconds = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM", Config)
	bool bRequiresAuth = true;
};

UCLASS(ClassGroup = (LLM), meta = (BlueprintSpawnableComponent), config = Game)
class FANTASIA_API UOpenAICompatibleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOpenAICompatibleComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LLM|Configuration")
	FOpenAICompatibleConfig Config;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LLM|Events")
	FIncomingGPTResponseEvent IncomingGPTResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LLM|Events")
	FIncomingGPTStreamResponseEvent IncomingGPTStreamResponse;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "LLM|Events")
	FIncomingGPTStreamResponseEvent IncomingSentenceResponse;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Chat Completion", AutoCreateRefTerm = "messages"), Category = "LLM")
	void GetChatCompletion(const TArray<FChatTurn>& messages, bool bStream = false, const FString& ModelOverride = TEXT(""));

	UFUNCTION(BlueprintCallable, Category = "LLM|Configuration", meta = (DisplayName = "Apply Provider Preset"))
	void ApplyPreset(ELLMProvider Provider);

	UFUNCTION(BlueprintPure, Category = "LLM|Presets", meta = (DisplayName = "Make OpenAI Config"))
	static FOpenAICompatibleConfig MakeOpenAIConfig();

	UFUNCTION(BlueprintPure, Category = "LLM|Presets", meta = (DisplayName = "Make Groq Config"))
	static FOpenAICompatibleConfig MakeGroqConfig();

	UFUNCTION(BlueprintPure, Category = "LLM|Presets", meta = (DisplayName = "Make Ollama Config"))
	static FOpenAICompatibleConfig MakeOllamaConfig();

	UFUNCTION(BlueprintPure, Category = "LLM|Presets", meta = (DisplayName = "Make LM Studio Config"))
	static FOpenAICompatibleConfig MakeLMStudioConfig();

	UFUNCTION(BlueprintPure, Category = "LLM|Presets", meta = (DisplayName = "Make vLLM Config"))
	static FOpenAICompatibleConfig MakeVLLMConfig();

private:
	int32 StreamParseOffset = 0;
	GPTRoleType StreamCurrentRole = GPTRoleType::ASSISTANT;
	FString SentenceBuffer;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnPartialResponseReceived(FHttpRequestPtr Request, uint64 BytesSent, uint64 BytesReceived);
	void FlushSentenceBuffer(bool bEndStream);

	static GPTRoleType ParseRole(const FString& RoleString);
	static const FString& RoleToString(GPTRoleType Role);
};
