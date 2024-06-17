// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "FANTASIAEditor.h"
#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"

#include "BayesianNetworkFactory.generated.h"

class FANTASIAEDITOR_API FBayesianNetworkActions : public FAssetTypeActions_Base
{
public:

	FText GetName() const;
	FColor GetTypeColor() const;
};

UCLASS()
class FANTASIAEDITOR_API UBayesianNetworkFactory : public UFactory
{
	GENERATED_BODY()
public:
	UBayesianNetworkFactory(const FObjectInitializer& ObjectInitializer);
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool FactoryCanImport(const FString& Filename) override;
	//virtual UObject* FactoryCreateBinary(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) ;
	virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled);
};
