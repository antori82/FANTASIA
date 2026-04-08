/**
 * @file InfluenceDiag.h
 * @brief UObject wrapper around an aGrUM influence diagram with decision-theoretic inference.
 */

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#pragma warning (disable : 4263)
#pragma warning (disable : 4264)
#pragma warning (disable : 4265)
#pragma warning (disable : 4701)

#include "FANTASIA.h"
#include "FANTASIATypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime\Core\Public\Misc\Paths.h"
#include "Runtime\Core\Public\Misc\FileHelper.h"
#include <Runtime/Core/Public/Async/Async.h>
#include <atomic>

#include "agrum/ID/influenceDiagram.h"
#include "agrum/ID/inference/tools/influenceDiagramInference.h"
#include "agrum/ID/inference/ShaferShenoyLIMIDInference.h"
#include "agrum/ID/io/BIFXML/BIFXMLIDWriter.h"

#include "MathUtilities.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InfluenceDiag.generated.h"

#pragma warning (default : 4263)
#pragma warning (default : 4264)
#pragma warning (default : 4265)
#pragma warning (default : 4701)

/**
 * @brief Serializable representation of a directed arc in an influence diagram.
 */
USTRUCT(Blueprintable)
struct FInfluenceDiagArcStruct
{
	GENERATED_USTRUCT_BODY()

	/** Name of the parent (tail) node. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Tail;

	/** Name of the child (head) node. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Head;
};

/**
 * @brief Serializable snapshot of a single influence diagram node and its probability/utility table.
 */
USTRUCT(Blueprintable)
struct FInfluenceDiagNodeStruct
{
	GENERATED_USTRUCT_BODY()

	/** Node identifier. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	/** Domain labels for this node's variable. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> variables;

	/** Flattened CPT or utility table values. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double> values;

	/** Names of parent nodes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> parents;

	/** Whether this node is a chance, decision, or utility node. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	InfluenceNodeType nodeType = InfluenceNodeType::CHANCE;
};

/**
 * @brief Simple wrapper around a float array, used for returning multi-valued results to Blueprints.
 */
USTRUCT(Blueprintable)
struct FArrayFloat
{
	GENERATED_USTRUCT_BODY()

public:
	/** The float values. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<float> arrayFloat;

};

/** Delegate broadcast on the game thread when influence diagram inference completes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FIDInferenceAvailableEvent);

/**
 * @brief Blueprint-accessible influence diagram powered by the aGrUM library.
 *
 * Extends probabilistic reasoning with decision and utility nodes, enabling
 * maximum expected utility (MEU) computation and optimal decision retrieval.
 * Uses Shafer-Shenoy LIMID inference asynchronously.
 *
 * @see UBayesianNetwork
 */
UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UInfluenceDiag : public UObject
{
	GENERATED_UCLASS_BODY()

	// ── Private State ────────────────────────────────────────────────────

private:
	/** The underlying aGrUM influence diagram model. */
	gum::InfluenceDiagram<double> id;

	/** Active inference engine (Shafer-Shenoy LIMID). */
	TUniquePtr<gum::InfluenceDiagramInference<double>> inference;

	/** True after Init() has completed successfully. */
	bool initialized = false;

	/** Guards against concurrent inference or mutation while inference is in flight. */
	std::atomic<bool> bInferenceRunning{false};

	/** Fast lookup set for duplicate arc detection (stores "parent_child" keys). */
	TSet<FString> arcSet;

	/** Fast lookup set for duplicate node detection. */
	TSet<FString> nodeNameSet;

	// ── Public Interface ─────────────────────────────────────────────────

public:
	/** Broadcast to Blueprints when asynchronous inference finishes. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIDInferenceAvailableEvent InferenceReady;

	/** Native C++ multicast delegate for inference completion (non-dynamic). */
	FSimpleMulticastDelegate OnInferenceReady;

	/** Serialized node snapshots for editor inspection. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInfluenceDiagNodeStruct> serializedNodes;

	/** Ordered list of node names present in the diagram. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> nodeNames;

	/** Map from node name to its human-readable description. */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> nodeDescriptions;

	/** List of arc keys in "parent_child" format. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> arcs;

	// ── Initialization ───────────────────────────────────────────────────

	/** @brief Create the Shafer-Shenoy LIMID inference engine for this diagram. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init"), Category = "Influence_Diagram")
	void Init();

	// ── Inference ────────────────────────────────────────────────────────

	/**
	 * @brief Run inference asynchronously. Broadcasts InferenceReady on completion.
	 * @note Requires Init() to have been called first.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "makeInference", Keywords = "Inference"), Category = "Influence_Diagram")
	void makeInference();

	/**
	 * @brief Retrieve the posterior distribution of a chance variable after inference.
	 * @param variable Node name.
	 * @return Map of label to posterior probability.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getPosterior", Keywords = "Inference"), Category = "Influence_Diagram")
	TMap<FString, float> getPosterior(const FString& variable);

	/**
	 * @brief Retrieve the posterior utility values for a utility node.
	 * @param variable Utility node name.
	 * @return Map of label to expected utility.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getPosteriorUtility", Keywords = "Inference"), Category = "Influence_Diagram")
	TMap<FString, float> getPosteriorUtility(const FString& variable);

	/**
	 * @brief Compute the maximum expected utility (MEU) and its variance.
	 * @return Map with keys "MEU" and "Variance".
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getMEU", Keywords = "Inference"), Category = "Influence_Diagram")
	TMap<FString, float> getMEU();

	/**
	 * @brief Compute the entropy of a variable's posterior distribution.
	 * @param variable Node name.
	 * @return Shannon entropy in nats, or 0 if unavailable.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getEntropy"), Category = "Influence_Diagram")
	double getEntropy(const FString& variable);

	/**
	 * @brief Retrieve the optimal decision policy for a decision node.
	 * @param variable Decision node name.
	 * @return Map from parent-condition key to optimal choice probabilities.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "optimalDecision", Keywords = "Inference"), Category = "Influence_Diagram")
	TMap<FString, FArrayFloat> optimalDecision(const FString& variable);

	// ── Evidence ─────────────────────────────────────────────────────────

	/**
	 * @brief Set soft evidence (likelihood) on a variable.
	 * @param variable Node name.
	 * @param data Array of likelihood values matching the domain size.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addEvidence"), Category = "Influence_Diagram")
	void addEvidence(const FString& variable, const TArray<float>& data);

	/** @brief Remove all evidence from the inference engine. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseAllEvidence"), Category = "Influence_Diagram")
	void eraseAllEvidence();

	/**
	 * @brief Remove evidence from a single variable.
	 * @param variable Node name.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseEvidence"), Category = "Influence_Diagram")
	void eraseEvidence(const FString& variable);

	// ── Diagram Construction ─────────────────────────────────────────────

	/**
	 * @brief Add a discretized (tick-based) variable to the diagram.
	 * @param variable Node name.
	 * @param description Human-readable description.
	 * @param minTick Lower bound of the discretization range.
	 * @param maxTick Upper bound of the discretization range.
	 * @param nPoints Number of tick points.
	 * @param nodeType Whether this is a CHANCE, DECISION, or UTILITY node.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addDiscretizedVariable"), Category = "Influence_Diagram")
	void addDiscretizedVariable(const FString& variable, const FString& description, float minTick, float maxTick, float nPoints, InfluenceNodeType nodeType);

	/**
	 * @brief Add a labelized (categorical) variable to the diagram.
	 * @param variable Node name.
	 * @param description Human-readable description.
	 * @param labels Ordered array of label strings for the domain.
	 * @param nodeType Whether this is a CHANCE, DECISION, or UTILITY node.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addLabelizedVariable"), Category = "Influence_Diagram")
	void addLabelizedVariable(const FString& variable, const FString& description, const TArray<FString>& labels, InfluenceNodeType nodeType);

	/**
	 * @brief Add a directed arc from a parent node to a child node.
	 * @param parent Name of the parent node.
	 * @param child Name of the child node.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addArc"), Category = "Influence_Diagram")
	void addArc(const FString& parent, const FString& child);

	/**
	 * @brief Set the CPT of a chance node from an explicit array of values.
	 * @param variable Chance node name.
	 * @param values Flattened CPT values in aGrUM order.
	 * @note Has no effect on utility nodes; use fillUtility() instead.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillCPT"), Category = "Influence_Diagram")
	void fillCPT(const FString& variable, const TArray<float>& values);

	/**
	 * @brief Set the utility table of a utility node from an explicit array of values.
	 * @param variable Utility node name.
	 * @param values Flattened utility values in aGrUM order.
	 * @note Has no effect on non-utility nodes; use fillCPT() instead.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillUtility"), Category = "Influence_Diagram")
	void fillUtility(const FString& variable, const TArray<float>& values);

	/**
	 * @brief Remove a node and all its incident arcs from the diagram.
	 * @param variable Name of the node to erase.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "EraseNode"), Category = "Influence_Diagram")
	void erase(const FString& variable);

	// ── Queries ──────────────────────────────────────────────────────────

	/**
	 * @brief Get the internal aGrUM node ID for a variable by name.
	 * @param variable Node name.
	 * @return The aGrUM NodeId.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "idFromName"), Category = "Influence_Diagram")
	int idFromName(const FString& variable);

	/**
	 * @brief Check whether a valid decision order exists for this influence diagram.
	 * @return True if a temporal ordering of decision nodes can be determined.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "decisionOrderExists"), Category = "Influence_Diagram")
	bool decisionOrderExists();

	/**
	 * @brief Retrieve the ordered sequence of decision node IDs.
	 * @return Array of aGrUM NodeIds in decision order.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "decisionOrder"), Category = "Influence_Diagram")
	TArray<int> decisionOrder();

	// ── Serialization ────────────────────────────────────────────────────

	/**
	 * @brief Export the influence diagram to a BIFXML file.
	 * @param file Absolute path for the output .bifxml file.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "writeBIFXML"), Category = "Influence_Diagram")
	void writeBIFXML(const FString& file);
};
