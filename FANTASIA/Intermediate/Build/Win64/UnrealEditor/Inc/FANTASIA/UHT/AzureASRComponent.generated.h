// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AzureASRComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FANTASIA_AzureASRComponent_generated_h
#error "AzureASRComponent.generated.h already included, missing '#pragma once' in AzureASRComponent.h"
#endif
#define FANTASIA_AzureASRComponent_generated_h

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_22_DELEGATE \
FANTASIA_API void FIncomingPartialASREvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingPartialASREvent, const FString& message);


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_23_DELEGATE \
FANTASIA_API void FIncomingFinalASREvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingFinalASREvent, const FString& message);


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execAzureASRStop); \
	DECLARE_FUNCTION(execAzureASRStart);


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAzureASRComponent(); \
	friend struct Z_Construct_UClass_UAzureASRComponent_Statics; \
public: \
	DECLARE_CLASS(UAzureASRComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UAzureASRComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_28_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UAzureASRComponent(UAzureASRComponent&&); \
	UAzureASRComponent(const UAzureASRComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAzureASRComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAzureASRComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAzureASRComponent) \
	NO_API virtual ~UAzureASRComponent();


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_25_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_28_INCLASS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UAzureASRComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
