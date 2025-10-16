// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GeneralTTSComponent.h"

#ifdef FANTASIA_GeneralTTSComponent_generated_h
#error "GeneralTTSComponent.generated.h already included, missing '#pragma once' in GeneralTTSComponent.h"
#endif
#define FANTASIA_GeneralTTSComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class USoundWave;

// ********** Begin Class UGeneralTTSComponent *****************************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTTSGetRawSound); \
	DECLARE_FUNCTION(execTTSGetSound); \
	DECLARE_FUNCTION(execTTSSynthesize);


FANTASIA_API UClass* Z_Construct_UClass_UGeneralTTSComponent_NoRegister();

#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_32_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGeneralTTSComponent(); \
	friend struct Z_Construct_UClass_UGeneralTTSComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UGeneralTTSComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UGeneralTTSComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UGeneralTTSComponent_NoRegister) \
	DECLARE_SERIALIZER(UGeneralTTSComponent) \
	virtual UObject* _getUObject() const override { return const_cast<UGeneralTTSComponent*>(this); }


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_32_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UGeneralTTSComponent(UGeneralTTSComponent&&) = delete; \
	UGeneralTTSComponent(const UGeneralTTSComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGeneralTTSComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGeneralTTSComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGeneralTTSComponent) \
	NO_API virtual ~UGeneralTTSComponent();


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_29_PROLOG
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_32_INCLASS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_32_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UGeneralTTSComponent;

// ********** End Class UGeneralTTSComponent *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
