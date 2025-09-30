// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AzureNLUComponent.h"

#ifdef FANTASIA_AzureNLUComponent_generated_h
#error "AzureNLUComponent.generated.h already included, missing '#pragma once' in AzureNLUComponent.h"
#endif
#define FANTASIA_AzureNLUComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FNLUResponse;

// ********** Begin Delegate FIncomingNLUEvent *****************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_23_DELEGATE \
FANTASIA_API void FIncomingNLUEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingNLUEvent, FNLUResponse NLUResponse);


// ********** End Delegate FIncomingNLUEvent *******************************************************

// ********** Begin Class UAzureNLUComponent *******************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execAzureNLUStart);


FANTASIA_API UClass* Z_Construct_UClass_UAzureNLUComponent_NoRegister();

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAzureNLUComponent(); \
	friend struct Z_Construct_UClass_UAzureNLUComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UAzureNLUComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UAzureNLUComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UAzureNLUComponent_NoRegister) \
	DECLARE_SERIALIZER(UAzureNLUComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_28_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UAzureNLUComponent(UAzureNLUComponent&&) = delete; \
	UAzureNLUComponent(const UAzureNLUComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAzureNLUComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAzureNLUComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAzureNLUComponent) \
	NO_API virtual ~UAzureNLUComponent();


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_25_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_28_INCLASS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAzureNLUComponent;

// ********** End Class UAzureNLUComponent *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
