// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ElevenLabsTTSComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USoundWave;
#ifdef FANTASIA_ElevenLabsTTSComponent_generated_h
#error "ElevenLabsTTSComponent.generated.h already included, missing '#pragma once' in ElevenLabsTTSComponent.h"
#endif
#define FANTASIA_ElevenLabsTTSComponent_generated_h

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTTSGetSound); \
	DECLARE_FUNCTION(execTTSSynthesize);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_22_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUElevenLabsTTSComponent(); \
	friend struct Z_Construct_UClass_UElevenLabsTTSComponent_Statics; \
public: \
	DECLARE_CLASS(UElevenLabsTTSComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UElevenLabsTTSComponent)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_22_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UElevenLabsTTSComponent(UElevenLabsTTSComponent&&); \
	UElevenLabsTTSComponent(const UElevenLabsTTSComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UElevenLabsTTSComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UElevenLabsTTSComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UElevenLabsTTSComponent) \
	NO_API virtual ~UElevenLabsTTSComponent();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_19_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_22_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_22_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_22_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h_22_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UElevenLabsTTSComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
