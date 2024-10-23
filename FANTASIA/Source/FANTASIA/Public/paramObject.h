#pragma once

#include "CoreMinimal.h"
#include "paramObject.generated.h"


//If you want this to appear in BP, make sure to use this instead
USTRUCT(BlueprintType)
struct FparamValues
{
	GENERATED_BODY()

	//Always make USTRUCT variables into UPROPERTY()
	//    any non-UPROPERTY() struct vars are not replicated
	
	// So to simplify your life for later debugging, always use UPROPERTY()
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> values;

};