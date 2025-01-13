// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BayesianNetworkFactory.h"
#include "BayesianNetwork.h"


FText FBayesianNetworkActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_BayesianNetwork", "Bayesian Network");
}

FColor FBayesianNetworkActions::GetTypeColor() const
{
	return FColor::White;
}

UBayesianNetworkFactory::UBayesianNetworkFactory(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("bif;")) + NSLOCTEXT("UBayesianNetworkFactory", "FormatBif", "Bayesian Network File").ToString());

	bCreateNew = false;
	bText = false;
	bEditorImport = true;
	bEditAfterNew = false;
	SupportedClass = UBayesianNetwork::StaticClass();
}

UObject* UBayesianNetworkFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UBayesianNetwork* BNAsset = NewObject< FANTASIA_API UBayesianNetwork>(InParent, InClass, InName, Flags);
	return BNAsset;
}

bool UBayesianNetworkFactory::FactoryCanImport(const FString& Filename)
{
	const FString Extension = FPaths::GetExtension(Filename);

	if (Extension == TEXT("bif"))
		return true;
	return false;
}

UObject* UBayesianNetworkFactory::FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled)
{
	UBayesianNetwork* bnObject = NewObject<FANTASIA_API UBayesianNetwork>(InParent, InClass, InName, Flags);

	bnObject->setBN(Filename);
	return bnObject;
}

