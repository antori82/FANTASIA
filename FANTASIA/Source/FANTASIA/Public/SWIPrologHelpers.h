/**
 * @file SWIPrologHelpers.h
 * @brief Blueprint function library for constructing Prolog term objects (atoms, variables, compounds, lists, etc.).
 */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FANTASIATypes.h"
#include "SWIPrologHelpers.generated.h"

/**
 * @brief Static Blueprint helper functions for building Prolog term trees.
 *
 * Use these pure functions in Blueprint graphs to construct the USWIPrologTerm
 * objects required by USWIPrologComponent::SWIPLsubmitQuery and SWIPLassert.
 *
 * @see USWIPrologComponent
 */
UCLASS()
class FANTASIA_API USWIPrologHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * @brief Create a Prolog atom from a string value.
	 * @param Value The atom's textual content (e.g. "tom").
	 * @return A new USWIPrologAtom instance.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Atom"), Category = "SWIProlog|Helpers")
	static USWIPrologAtom* MakeAtom(const FString& Value);

	/**
	 * @brief Create a Prolog variable from a name.
	 * @param Name The variable identifier (e.g. "X"). An underscore prefix is added automatically.
	 * @return A new USWIPrologVariable instance.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Variable"), Category = "SWIProlog|Helpers")
	static USWIPrologVariable* MakeVariable(const FString& Name);

	/**
	 * @brief Create a Prolog compound term (functor with arguments).
	 * @param Name The functor name (e.g. "parent").
	 * @param Arguments Ordered array of sub-term arguments.
	 * @return A new USWIPrologCompound instance.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Compound"), Category = "SWIProlog|Helpers")
	static USWIPrologCompound* MakeCompound(const FString& Name, const TArray<USWIPrologTerm*>& Arguments);

	/**
	 * @brief Create a Prolog integer term.
	 * @param Value The integer value.
	 * @return A new USWIPrologInteger instance.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Integer"), Category = "SWIProlog|Helpers")
	static USWIPrologInteger* MakeInteger(int32 Value);

	/**
	 * @brief Create a Prolog float term.
	 * @param Value The floating-point value.
	 * @return A new USWIPrologFloat instance.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Float"), Category = "SWIProlog|Helpers")
	static USWIPrologFloat* MakeFloat(float Value);

	/**
	 * @brief Create a Prolog list from an array of terms.
	 * @param Elements The terms that form the list.
	 * @return A new USWIPrologList instance.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog List"), Category = "SWIProlog|Helpers")
	static USWIPrologList* MakeList(const TArray<USWIPrologTerm*>& Elements);
};
