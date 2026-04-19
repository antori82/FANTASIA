/**
 * @file paramObject.h
 * @brief Lightweight parameter container exposed to Blueprints.
 */

#pragma once

#include "CoreMinimal.h"
#include "paramObject.generated.h"

/**
 * A simple array-of-strings wrapper used to pass multi-valued parameters
 * through Blueprint-accessible APIs (e.g. Neo4j query parameters).
 */
USTRUCT(BlueprintType)
struct FparamValues
{
	GENERATED_BODY()

	/** The parameter values. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> values;

};