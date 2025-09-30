// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OllamaComponent.h"

#ifdef FANTASIA_OllamaComponent_generated_h
#error "OllamaComponent.generated.h already included, missing '#pragma once' in OllamaComponent.h"
#endif
#define FANTASIA_OllamaComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FChatTurn;

// ********** Begin Class UOllamaComponent *********************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execgetGPTCompletion);


FANTASIA_API UClass* Z_Construct_UClass_UOllamaComponent_NoRegister();

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUOllamaComponent(); \
	friend struct Z_Construct_UClass_UOllamaComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UOllamaComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UOllamaComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UOllamaComponent_NoRegister) \
	DECLARE_SERIALIZER(UOllamaComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UOllamaComponent(UOllamaComponent&&) = delete; \
	UOllamaComponent(const UOllamaComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOllamaComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOllamaComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UOllamaComponent) \
	NO_API virtual ~UOllamaComponent();


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_9_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_INCLASS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UOllamaComponent;

// ********** End Class UOllamaComponent ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
