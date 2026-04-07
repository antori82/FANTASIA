#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FANTASIATypes.h"
#include "SWIPrologHelpers.generated.h"

UCLASS()
class FANTASIA_API USWIPrologHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/** Create a Prolog atom from a string value. */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Atom"), Category = "SWIProlog|Helpers")
	static USWIPrologAtom* MakeAtom(const FString& Value);

	/** Create a Prolog variable from a name. */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Variable"), Category = "SWIProlog|Helpers")
	static USWIPrologVariable* MakeVariable(const FString& Name);

	/** Create a Prolog compound term (functor with arguments). */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Compound"), Category = "SWIProlog|Helpers")
	static USWIPrologCompound* MakeCompound(const FString& Name, const TArray<USWIPrologTerm*>& Arguments);

	/** Create a Prolog integer term. */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Integer"), Category = "SWIProlog|Helpers")
	static USWIPrologInteger* MakeInteger(int32 Value);

	/** Create a Prolog float term. */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog Float"), Category = "SWIProlog|Helpers")
	static USWIPrologFloat* MakeFloat(float Value);

	/** Create a Prolog list from an array of terms. */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Make Prolog List"), Category = "SWIProlog|Helpers")
	static USWIPrologList* MakeList(const TArray<USWIPrologTerm*>& Elements);
};
