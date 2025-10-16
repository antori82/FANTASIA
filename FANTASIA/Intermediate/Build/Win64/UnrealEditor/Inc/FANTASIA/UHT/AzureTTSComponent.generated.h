// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AzureTTSComponent.h"

#ifdef FANTASIA_AzureTTSComponent_generated_h
#error "AzureTTSComponent.generated.h already included, missing '#pragma once' in AzureTTSComponent.h"
#endif
#define FANTASIA_AzureTTSComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class USoundWave;

// ********** Begin Class UAzureTTSComponent *******************************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTTSGetRawSound); \
	DECLARE_FUNCTION(execTTSGetSound); \
	DECLARE_FUNCTION(execTTSSynthesize);


FANTASIA_API UClass* Z_Construct_UClass_UAzureTTSComponent_NoRegister();

#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAzureTTSComponent(); \
	friend struct Z_Construct_UClass_UAzureTTSComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UAzureTTSComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UAzureTTSComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UAzureTTSComponent_NoRegister) \
	DECLARE_SERIALIZER(UAzureTTSComponent) \
	virtual UObject* _getUObject() const override { return const_cast<UAzureTTSComponent*>(this); }


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UAzureTTSComponent(UAzureTTSComponent&&) = delete; \
	UAzureTTSComponent(const UAzureTTSComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAzureTTSComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAzureTTSComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAzureTTSComponent) \
	NO_API virtual ~UAzureTTSComponent();


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_24_PROLOG
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_INCLASS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAzureTTSComponent;

// ********** End Class UAzureTTSComponent *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
