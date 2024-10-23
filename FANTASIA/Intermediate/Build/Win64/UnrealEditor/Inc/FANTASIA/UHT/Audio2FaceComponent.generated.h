// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Audio2FaceComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USoundWave;
#ifdef FANTASIA_Audio2FaceComponent_generated_h
#error "Audio2FaceComponent.generated.h already included, missing '#pragma once' in Audio2FaceComponent.h"
#endif
#define FANTASIA_Audio2FaceComponent_generated_h

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execPlayAudio);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_32_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAudio2FaceComponent(); \
	friend struct Z_Construct_UClass_UAudio2FaceComponent_Statics; \
public: \
	DECLARE_CLASS(UAudio2FaceComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UAudio2FaceComponent)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_32_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UAudio2FaceComponent(UAudio2FaceComponent&&); \
	UAudio2FaceComponent(const UAudio2FaceComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAudio2FaceComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAudio2FaceComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAudio2FaceComponent) \
	NO_API virtual ~UAudio2FaceComponent();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_29_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_32_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_32_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UAudio2FaceComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
