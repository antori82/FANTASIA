// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ElevenLabsTTSComponent.h"

#ifdef FANTASIA_ElevenLabsTTSComponent_generated_h
#error "ElevenLabsTTSComponent.generated.h already included, missing '#pragma once' in ElevenLabsTTSComponent.h"
#endif
#define FANTASIA_ElevenLabsTTSComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class USoundWaveProcedural;

// ********** Begin Class UElevenLabsTTSComponent **************************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTTSGetPartialRawSound); \
	DECLARE_FUNCTION(execTTSGetRawSound); \
	DECLARE_FUNCTION(execTTSGetSound); \
	DECLARE_FUNCTION(execTTSSynthesize);


FANTASIA_API UClass* Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister();

#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUElevenLabsTTSComponent(); \
	friend struct Z_Construct_UClass_UElevenLabsTTSComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UElevenLabsTTSComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister) \
	DECLARE_SERIALIZER(UElevenLabsTTSComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_27_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UElevenLabsTTSComponent(UElevenLabsTTSComponent&&) = delete; \
	UElevenLabsTTSComponent(const UElevenLabsTTSComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UElevenLabsTTSComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UElevenLabsTTSComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UElevenLabsTTSComponent) \
	NO_API virtual ~UElevenLabsTTSComponent();


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_24_PROLOG
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_27_INCLASS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UElevenLabsTTSComponent;

// ********** End Class UElevenLabsTTSComponent ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
