// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OpenAIComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FANTASIA_OpenAIComponent_generated_h
#error "OpenAIComponent.generated.h already included, missing '#pragma once' in OpenAIComponent.h"
#endif
#define FANTASIA_OpenAIComponent_generated_h

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_8_DELEGATE \
FANTASIA_API void FIncomingGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingGPTResponseEvent, const FString& GPTResponse);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_SPARSE_DATA
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execgetGPTCompletion);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execgetGPTCompletion);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_ACCESSORS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUOpenAIComponent(); \
	friend struct Z_Construct_UClass_UOpenAIComponent_Statics; \
public: \
	DECLARE_CLASS(UOpenAIComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UOpenAIComponent)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_INCLASS \
private: \
	static void StaticRegisterNativesUOpenAIComponent(); \
	friend struct Z_Construct_UClass_UOpenAIComponent_Statics; \
public: \
	DECLARE_CLASS(UOpenAIComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UOpenAIComponent)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UOpenAIComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UOpenAIComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOpenAIComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOpenAIComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UOpenAIComponent(UOpenAIComponent&&); \
	NO_API UOpenAIComponent(const UOpenAIComponent&); \
public: \
	NO_API virtual ~UOpenAIComponent();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UOpenAIComponent(UOpenAIComponent&&); \
	NO_API UOpenAIComponent(const UOpenAIComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOpenAIComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOpenAIComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UOpenAIComponent) \
	NO_API virtual ~UOpenAIComponent();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_10_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UOpenAIComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
