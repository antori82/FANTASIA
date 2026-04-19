/**
 * @file OpenAIComponent.h
 * @brief Deprecated OpenAI chat-completion component for Unreal Engine.
 * @deprecated This component is deprecated. Use UOpenAICompatibleComponent instead.
 * @see UOpenAICompatibleComponent
 */

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "OpenAIComponent.generated.h"

/**
 * @brief Actor component that sends chat-completion requests to the OpenAI API.
 *
 * @deprecated This component is deprecated. Use UOpenAICompatibleComponent, which
 *             supports OpenAI and several other OpenAI-compatible providers through
 *             a single, configurable interface.
 * @see UOpenAICompatibleComponent
 */
UCLASS(ClassGroup = (OpenAI), meta = (BlueprintSpawnableComponent), config=Game)
class UOpenAIComponent : public UActorComponent
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
	UOpenAIComponent();

	/** @brief Delegate broadcast with each streaming token chunk and end-of-stream flag. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTStreamResponseEvent IncomingGPTStreamResponse;

	/** @brief OpenAI API key used for authentication. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	/** @brief Delegate broadcast with the full response when streaming is disabled. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingGPTResponseEvent IncomingGPTResponse;

	/**
	 * @brief Sends a chat-completion request to the OpenAI API.
	 * @param messages  Ordered conversation turns to send.
	 * @param apiMethod OpenAI model identifier (default: "gpt-4-turbo-preview").
	 * @param stream    If true, tokens are delivered incrementally via IncomingGPTStreamResponse.
	 * @deprecated Use UOpenAICompatibleComponent::GetChatCompletion instead.
	 * @see UOpenAICompatibleComponent::GetChatCompletion
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetChatGPTCompletion", AutoCreateRefTerm = "messages", DeprecatedFunction, DeprecationMessage = "Use OpenAICompatibleComponent instead."), Category = "GPT")
	void getGPTCompletion(TArray<FChatTurn> messages, FString apiMethod = "gpt-4-turbo-preview", bool stream = false);

	/** @brief Called every frame (tick is disabled by default). */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** @brief Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

};