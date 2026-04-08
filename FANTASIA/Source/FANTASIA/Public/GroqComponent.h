/**
 * @file GroqComponent.h
 * @brief Deprecated Groq chat-completion component for Unreal Engine.
 * @deprecated This component is deprecated. Use UOpenAICompatibleComponent with a Groq preset instead.
 * @see UOpenAICompatibleComponent, UOpenAICompatibleComponent::MakeGroqConfig
 */

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "GroqComponent.generated.h"

/**
 * @brief Actor component that sends chat-completion requests to the Groq API.
 *
 * @deprecated This component is deprecated. Use UOpenAICompatibleComponent with
 *             ELLMProvider::Groq or UOpenAICompatibleComponent::MakeGroqConfig().
 * @see UOpenAICompatibleComponent
 */
UCLASS(ClassGroup = (Groq), meta = (BlueprintSpawnableComponent), config=Game)
class UGroqComponent : public UActorComponent
{
	GENERATED_BODY()

	// ── Private HTTP callbacks ──────────────────────────────────────────

private:

	/** @brief Callback invoked when a non-streaming GPT response is received. */
	void OnGPTResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/** @brief Callback invoked incrementally during a streaming GPT response. */
	void OnGPTPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived);

	// ── Public interface ────────────────────────────────────────────────

public:
	/** @brief Sets default values for this component's properties. */
	UGroqComponent();

	/** @brief Groq API key used for authentication. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	/** @brief Delegate broadcast with the full response (non-streaming path). */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	/** @brief Delegate broadcast with the full chat response (non-streaming path, legacy alias). */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingChatGPTResponse;

	/** @brief Delegate broadcast with each streaming token chunk and end-of-stream flag. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTStreamResponseEvent IncomingGPTStreamResponse;

	/**
	 * @brief Sends a chat-completion request to the Groq API.
	 * @param messages  Ordered conversation turns to send.
	 * @param apiMethod Groq model identifier (default: "llama3-8b-8192").
	 * @param stream    If true, tokens are delivered incrementally via IncomingGPTStreamResponse.
	 * @deprecated Use UOpenAICompatibleComponent::GetChatCompletion instead.
	 * @see UOpenAICompatibleComponent::GetChatCompletion
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetGroqGPTCompletion", AutoCreateRefTerm = "messages", DeprecatedFunction, DeprecationMessage = "Use OpenAICompatibleComponent instead."), Category = "GPT")
	void getGPTCompletion(TArray<FChatTurn> messages, FString apiMethod = "llama3-8b-8192", bool stream = false);

	/** @brief Called every frame (tick is disabled by default). */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** @brief Called when the game starts or when spawned. */
	virtual void BeginPlay() override;
};