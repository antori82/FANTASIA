/**
 * @file LangGraphComponent.h
 * @brief Actor component for querying a LangGraph server with thread-based conversations.
 */

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FANTASIATypes.h"
#include "LangGraphComponent.generated.h"

/** @brief Delegate broadcast when a LangGraph thread is successfully created. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIncomingLangGraphThreadCreateResponseEvent, FString, threadID);

/** @brief Delegate broadcast with the full LangGraph response (non-streaming). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIncomingLangGraphResponseEvent, FString, LangGraphResponse, GPTRoleType, role);

/** @brief Delegate broadcast with each streaming LangGraph update; the final call has endStream=true. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIncomingLangGraphStreamResponseEvent, FString, LangGraphResponse, GPTRoleType, role, bool, endStream);

/**
 * @brief Actor component that communicates with a LangGraph server for
 *        thread-based, multi-turn agent conversations.
 *
 * Manages thread lifecycle (create/delete) and sends queries to a LangGraph
 * deployment via its REST API. Supports both blocking (wait) and streaming
 * (SSE updates) response modes.
 */
UCLASS(ClassGroup = (OpenAI), meta = (BlueprintSpawnableComponent), config=Game)
class ULangGraphComponent : public UActorComponent
{
	GENERATED_BODY()

	// ── Private HTTP callbacks ──────────────────────────────────────────

private:

	/** @brief Callback for non-streaming LangGraph query responses. */
	void OnLangGraphResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/** @brief Callback invoked incrementally as streaming SSE updates arrive. */
	void OnLangGraphPartialResponseReceived(FHttpRequestPtr request, uint64 bytesSent, uint64 bytesReceived);

	/** @brief Callback invoked when the streaming SSE connection closes; flushes the sentence buffer and signals end-of-stream. */
	void OnLangGraphStreamComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/** @brief Callback invoked when a thread-creation request completes. */
	void OnLangGraphThreadCreateResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/** @brief Byte offset past the last fully-matched SSE event in the stream buffer. */
	int32 StreamScanOffset = 0;

	/** @brief Role carried forward across streaming update events; used by both token- and sentence-level delegates. */
	GPTRoleType StreamCurrentRole = GPTRoleType::ASSISTANT;

	/** @brief Accumulates streamed assistant text until a sentence boundary is detected. */
	FString SentenceBuffer;

	/**
	 * @brief Process a single `event: updates` payload (per-node state delta).
	 * @param Payload JSON object captured after the `data:` line.
	 */
	void ProcessUpdatesEvent(const FString& Payload);

	/**
	 * @brief Process a single `event: messages` payload (per-token LLM chunk).
	 * @param Payload JSON array `[chunk, metadata]` captured after the `data:` line.
	 */
	void ProcessMessagesEvent(const FString& Payload);

	/**
	 * @brief Append assistant text to SentenceBuffer and flush completed sentences.
	 *
	 * Called by both Update and Messages branches so token-level (per-chunk) and
	 * node-level (per-state-delta) streams share one consistent sentence boundary
	 * scan. Only assistant-role text reaches this method.
	 * @param Text Newly-arrived assistant content to append.
	 */
	void AppendAndFlushSentences(const FString& Text);

	/**
	 * @brief Broadcasts any remaining text in SentenceBuffer and clears it.
	 * @param bEndStream If true, signals the end of the stream to listeners.
	 */
	void FlushSentenceBuffer(bool bEndStream);

	// ── Public interface ────────────────────────────────────────────────

public:
	/** @brief Sets default values for this component's properties. */
	ULangGraphComponent();

	/** @brief LangGraph server hostname or IP (e.g. "http://localhost"). */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString endpoint;

	/** @brief LangGraph server port. */
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	int port;

	// ── Events ──────────────────────────────────────────────────────────

	/** @brief Broadcast with the full response content from a non-streaming query. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingLangGraphResponseEvent IncomingLangGraphResponse;

	/** @brief Broadcast with each streaming update chunk; the final call has endStream=true. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingLangGraphStreamResponseEvent IncomingLangGraphStreamResponse;

	/**
	 * @brief Broadcast with complete sentences accumulated during streaming.
	 *
	 * Useful for driving text-to-speech: streamed assistant text is buffered until
	 * sentence-ending punctuation is detected, then flushed as a single sentence.
	 * The final call has endStream=true with whatever remains in the buffer.
	 */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingLangGraphStreamResponseEvent IncomingLangGraphSentenceResponse;

	/** @brief Broadcast when a thread is created, providing the new thread ID. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIncomingLangGraphThreadCreateResponseEvent LangGraphThreadCreateResponse;

	// ── Blueprint-callable methods ──────────────────────────────────────

	/**
	 * @brief Creates a conversation thread on the LangGraph server.
	 * @param threadID Desired thread identifier; if it already exists the server does nothing.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create LangGraph thread"), Category = "LangGraph")
	void createLangGraphThread(FString threadID);

	/**
	 * @brief Deletes a conversation thread from the LangGraph server.
	 * @param threadID Identifier of the thread to delete.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Delete LangGraph thread"), Category = "LangGraph")
	void deleteLangGraphThread(FString threadID);

	/**
	 * @brief Sends a multi-turn query to a LangGraph assistant within a thread.
	 * @param messages       Ordered conversation turns to send.
	 * @param threadID       Thread in which the conversation takes place.
	 * @param assistantID    LangGraph assistant identifier to invoke.
	 * @param model          Model identifier forwarded to the assistant (default: "openai/gpt-4o").
	 * @param recursionLimit Maximum graph recursion depth (default: 10).
	 * @param stream         If true, responses arrive incrementally via IncomingLangGraphStreamResponse.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LangGraph query", AutoCreateRefTerm = "messages"), Category = "LangGraph")
	void langGraphQuery(const TArray<FChatTurn>& messages, FString threadID, FString assistantID, FString model = "openai/gpt-4o", int recursionLimit = 10, bool stream = false);



protected:
	/** @brief Called when the game starts or when spawned. */
	virtual void BeginPlay() override;

};