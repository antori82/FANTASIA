/**
 * @file OllamaComponent.h
 * @brief Deprecated Ollama chat-completion component for Unreal Engine.
 * @deprecated This component is deprecated. Use UOpenAICompatibleComponent with an Ollama preset instead.
 * @see UOpenAICompatibleComponent, UOpenAICompatibleComponent::MakeOllamaConfig
 */

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "OllamaComponent.generated.h"

/**
 * @brief Actor component that sends chat-completion requests to a local Ollama server.
 *
 * @deprecated This component is deprecated. Use UOpenAICompatibleComponent with
 *             ELLMProvider::Ollama or UOpenAICompatibleComponent::MakeOllamaConfig().
 * @see UOpenAICompatibleComponent
 */
UCLASS(ClassGroup = (OpenAI), meta = (BlueprintSpawnableComponent), config=Game)
class UOllamaComponent : public UActorComponent
{
	GENERATED_BODY()

	// ── Private HTTP callbacks ──────────────────────────────────────────

private:

	/** @brief Callback invoked when a non-streaming response is received. */
	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/** @brief Callback invoked incrementally during a streaming response. */
	void OnGPTPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived);

	// ── Public interface ────────────────────────────────────────────────

public:
	/** @brief Sets default values for this component's properties. */
	UOllamaComponent();

	/** @brief Ollama server hostname or IP (e.g. "http://localhost"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString endpoint;

	/** @brief Ollama server port (default Ollama port is 11434). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	int port;

	/** @brief Delegate broadcast with the full response when streaming is disabled. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	/** @brief Delegate broadcast with each streaming token chunk and end-of-stream flag. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTStreamResponseEvent IncomingGPTStreamResponse;

	/**
	 * @brief Sends a chat-completion request to the Ollama /api/chat endpoint.
	 * @param messages Ordered conversation turns to send.
	 * @param model    Ollama model name (default: "llama3").
	 * @param stream   If true, tokens are delivered incrementally via IncomingGPTStreamResponse.
	 * @deprecated Use UOpenAICompatibleComponent::GetChatCompletion instead.
	 * @see UOpenAICompatibleComponent::GetChatCompletion
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetOllamaGPTCompletion", AutoCreateRefTerm = "messages", DeprecatedFunction, DeprecationMessage = "Use OpenAICompatibleComponent instead."), Category = "GPT")
	void getGPTCompletion(TArray<FChatTurn> messages, FString model = "llama3", bool stream = false);

	/** @brief Called every frame. */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** @brief Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

};