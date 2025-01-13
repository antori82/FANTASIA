// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OpenAIComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FChatTurn;
#ifdef FANTASIA_OpenAIComponent_generated_h
#error "OpenAIComponent.generated.h already included, missing '#pragma once' in OpenAIComponent.h"
#endif
#define FANTASIA_OpenAIComponent_generated_h

#define FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execgetGPTCompletion);


#define FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUOpenAIComponent(); \
	friend struct Z_Construct_UClass_UOpenAIComponent_Statics; \
public: \
	DECLARE_CLASS(UOpenAIComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UOpenAIComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UOpenAIComponent(UOpenAIComponent&&); \
	UOpenAIComponent(const UOpenAIComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOpenAIComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOpenAIComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UOpenAIComponent) \
	NO_API virtual ~UOpenAIComponent();


#define FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_9_PROLOG
#define FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_INCLASS_NO_PURE_DECLS \
	FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UOpenAIComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
