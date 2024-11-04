// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OllamaComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FChatTurn;
#ifdef FANTASIA_OllamaComponent_generated_h
#error "OllamaComponent.generated.h already included, missing '#pragma once' in OllamaComponent.h"
#endif
#define FANTASIA_OllamaComponent_generated_h

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execgetGPTCompletion);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUOllamaComponent(); \
	friend struct Z_Construct_UClass_UOllamaComponent_Statics; \
public: \
	DECLARE_CLASS(UOllamaComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UOllamaComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UOllamaComponent(UOllamaComponent&&); \
	UOllamaComponent(const UOllamaComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOllamaComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOllamaComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UOllamaComponent) \
	NO_API virtual ~UOllamaComponent();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_9_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UOllamaComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
