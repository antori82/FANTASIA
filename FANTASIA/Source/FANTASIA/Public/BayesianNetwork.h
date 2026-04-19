/**
 * @file BayesianNetwork.h
 * @brief UObject wrapper around an aGrUM Bayesian network with async inference support.
 */

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#pragma warning (disable : 4263)
#pragma warning (disable : 4264)
#pragma warning (disable : 4265)
#pragma warning (disable : 4701)
#pragma warning (disable : 4996)

#include "FANTASIA.h"
#include "FANTASIATypes.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime\Core\Public\Misc\Paths.h"
#include "Runtime\Core\Public\Misc\FileHelper.h"
#include <Runtime/Core/Public/Async/Async.h>
#include <atomic>

#include "agrum/BN/BayesNet.h"
#include "agrum/BN/io/BIF/BIFWriter.h"
#include "agrum/BN/io/BIF/BIFReader.h"
#include "agrum/BN/inference/lazyPropagation.h"
#include "agrum/BN/inference/ShaferShenoyInference.h"
#include "agrum/BN/inference/variableElimination.h"
#include <agrum/BN/algorithms/MarkovBlanket.h>

#include "MathUtilities.h"
#include "BayesianNetwork.generated.h"

#pragma warning (default : 4263)
#pragma warning (default : 4264)
#pragma warning (default : 4265)
#pragma warning (default : 4701)
#pragma warning (default : 4996)

/**
 * @brief Generic string-to-float map container exposed to Blueprints.
 */
USTRUCT(BlueprintType)
struct FMapContainer
{
	GENERATED_USTRUCT_BODY()

	/** The underlying map. */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, float> Map;
};

/**
 * @brief Serializable representation of a directed arc in a Bayesian network.
 */
USTRUCT(Blueprintable)
struct FBayesianArcStruct
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
 * @brief Serializable snapshot of a single Bayesian network node and its CPT.
 */
USTRUCT(Blueprintable)
struct FBayesianNodeStruct
{
	GENERATED_USTRUCT_BODY()

	/** Node identifier. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	/** Domain labels for this node's variable. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> variables;

	/** Flattened CPT values. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double> values;

	/** Names of parent nodes. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> parents;
};

/** Delegate broadcast on the game thread when Bayesian network inference completes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBNInferenceAvailableEvent);

/**
 * @brief Blueprint-accessible Bayesian network powered by the aGrUM library.
 *
 * Supports programmatic construction of nodes and arcs, loading from BIF files,
 * evidence setting, and asynchronous inference with configurable algorithms
 * (Lazy Propagation, Shafer-Shenoy, Variable Elimination).
 *
 * @see UInfluenceDiag
 */
UCLASS(Blueprintable, BlueprintType)
class FANTASIA_API UBayesianNetwork : public UObject
{
	GENERATED_UCLASS_BODY()

	// ── Private State ────────────────────────────────────────────────────

private:

	/** The underlying aGrUM Bayesian network model. */
	gum::BayesNet<double> bn;

	/** Active inference engine instance (algorithm depends on InferenceAlgorithm). */
	TUniquePtr<gum::JointTargetedInference<double>> inference;

	/** True after Init() or setBN() has completed successfully. */
	bool initialized = false;

	/** Guards against concurrent inference or mutation while inference is in flight. */
	std::atomic<bool> bInferenceRunning{false};

	/** Fast lookup set for duplicate arc detection (stores "parent_child" keys). */
	TSet<FString> arcSet;

	/** Fast lookup set for duplicate node detection. */
	TSet<FString> nodeNameSet;

	/** Instantiate the inference engine based on the current InferenceAlgorithm setting. */
	void CreateInferenceEngine();

	// ── Public Interface ─────────────────────────────────────────────────

public:

	/** Broadcast to Blueprints when asynchronous inference finishes. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FBNInferenceAvailableEvent InferenceReady;

	/** Native C++ multicast delegate for inference completion (non-dynamic). */
	FSimpleMulticastDelegate OnInferenceReady;

	/** Serialized node snapshots, populated by setBN() for editor inspection. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FBayesianNodeStruct> serializedNodes;

	/** Ordered list of node names present in the network. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> nodeNames;

	/** Map from node name to its human-readable description. */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> nodeDescriptions;

	/** List of arc keys in "parent_child" format. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> arcs;

	// ── Network Construction ─────────────────────────────────────────────

	/**
	 * @brief Load a Bayesian network from a BIF file and create the inference engine.
	 * @param Filename Absolute path to the .bif file.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "LoadFromBIF"), Category = "Bayesian_Network")
	void setBN(const FString& Filename);

	/** @brief Create (or recreate) the inference engine from the current network and algorithm. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Init"), Category = "Bayesian_Network")
	void Init();

	/** The inference algorithm to use. Changing this requires a subsequent call to Init(). */
	UPROPERTY(BlueprintReadWrite)
	InferenceAlgs InferenceAlgorithm = InferenceAlgs::ShaferShenoy;

	/**
	 * @brief Add a discretized (tick-based) variable to the network.
	 * @param variable Node name.
	 * @param description Human-readable description.
	 * @param minTick Lower bound of the discretization range.
	 * @param maxTick Upper bound of the discretization range.
	 * @param nPoints Number of tick points.
	 * @param nodeType Aggregator type (NORMAL, AND, OR, etc.).
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addDiscretizedVariable"), Category = "Bayesian_Network")
	void addDiscretizedVariable(const FString& variable, const FString& description, float minTick, float maxTick, float nPoints, BayesianNodeType nodeType);

	/**
	 * @brief Add a labelized (categorical) variable to the network.
	 * @param variable Node name.
	 * @param description Human-readable description.
	 * @param labels Ordered array of label strings for the domain.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addLabelizedVariable"), Category = "Bayesian_Network")
	void addLabelizedVariable(const FString& variable, const FString& description, const TArray<FString>& labels);

	/**
	 * @brief Add a directed arc from a parent node to a child node.
	 * @param parent Name of the parent node.
	 * @param child Name of the child node.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "addArc"), Category = "Bayesian_Network")
	void addArc(const FString& parent, const FString& child);

	/**
	 * @brief Fill the entire CPT of a node with a single value.
	 * @param variable Node name.
	 * @param value The value to fill every CPT entry with.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillWith"), Category = "Bayesian_Network")
	void fillWith(const FString& variable, float value);

	/**
	 * @brief Set the CPT of a node from an explicit array of values.
	 * @param variable Node name.
	 * @param values Flattened CPT values in aGrUM order.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "fillCPT"), Category = "Bayesian_Network")
	void fillCPT(const FString& variable, const TArray<float>& values);

	/**
	 * @brief Remove a node and all its incident arcs from the network.
	 * @param variable Name of the node to erase.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "EraseNode"), Category = "Bayesian_Network")
	void erase(const FString& variable);

	// ── Inference ────────────────────────────────────────────────────────

	/**
	 * @brief Run inference asynchronously. Broadcasts InferenceReady on completion.
	 * @note Requires Init() to have been called first.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "makeInference", Keywords = "Inference"), Category = "Bayesian_Network")
	void makeInference();

	/**
	 * @brief Retrieve the posterior distribution of a variable after inference.
	 * @param variable Node name.
	 * @return Map of label to posterior probability.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getPosterior", Keywords = "Inference"), Category = "Bayesian_Network")
	TMap<FString, float> getPosterior(const FString& variable);

	// ── Evidence ─────────────────────────────────────────────────────────

	/**
	 * @brief Set soft evidence (likelihood) on a variable.
	 * @param variable Node name.
	 * @param data Array of likelihood values matching the domain size.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "setEvidence"), Category = "Bayesian_Network")
	void setEvidence(const FString& variable, const TArray<float>& data);

	/** @brief Remove all evidence from the inference engine. */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseAllEvidence"), Category = "Bayesian_Network")
	void eraseAllEvidence();

	/**
	 * @brief Remove evidence from a single variable.
	 * @param variable Node name.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "eraseEvidence"), Category = "Bayesian_Network")
	void eraseEvidence(const FString& variable);

	// ── Queries ──────────────────────────────────────────────────────────

	/**
	 * @brief Compute the entropy of a variable's posterior distribution.
	 * @param variable Node name.
	 * @return Shannon entropy in nats, or 0 if unavailable.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getEntropy"), Category = "Bayesian_Network")
	double getEntropy(const FString& variable);

	/**
	 * @brief Get the internal aGrUM node ID for a variable by name.
	 * @param variable Node name.
	 * @return The aGrUM NodeId, or -1 if not found.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "idFromName"), Category = "Bayesian_Network")
	int idFromName(const FString& variable);

	/**
	 * @brief Get the names of all nodes in the Markov blanket of a variable.
	 * @param variable Node name.
	 * @return Array of node names forming the Markov blanket.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "getMarkovBlanketNodes"), Category = "Bayesian_Network")
	TArray<FString> getMarkovBlanketNodes(const FString& variable);

	// ── Serialization ────────────────────────────────────────────────────

	/**
	 * @brief Export the network to a BIF file.
	 * @param file Absolute path for the output .bif file.
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "writeBIF"), Category = "Bayesian_Network")
	void writeBIF(const FString& file);
};
