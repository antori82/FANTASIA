// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OpenAIComponent.h"

#ifdef FANTASIA_OpenAIComponent_generated_h
#error "OpenAIComponent.generated.h already included, missing '#pragma once' in OpenAIComponent.h"
#endif
#define FANTASIA_OpenAIComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FChatTurn;

// ********** Begin Class UOpenAIComponent *********************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execgetGPTCompletion);


FANTASIA_API UClass* Z_Construct_UClass_UOpenAIComponent_NoRegister();

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUOpenAIComponent(); \
	friend struct Z_Construct_UClass_UOpenAIComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UOpenAIComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UOpenAIComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UOpenAIComponent_NoRegister) \
	DECLARE_SERIALIZER(UOpenAIComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UOpenAIComponent(UOpenAIComponent&&) = delete; \
	UOpenAIComponent(const UOpenAIComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOpenAIComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOpenAIComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UOpenAIComponent) \
	NO_API virtual ~UOpenAIComponent();


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_9_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_INCLASS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UOpenAIComponent;

// ********** End Class UOpenAIComponent ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
