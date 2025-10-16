// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Audio2FaceComponent.h"

#ifdef FANTASIA_Audio2FaceComponent_generated_h
#error "Audio2FaceComponent.generated.h already included, missing '#pragma once' in Audio2FaceComponent.h"
#endif
#define FANTASIA_Audio2FaceComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Delegate FLoadSceneCompleteEvent ***********************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_29_DELEGATE \
FANTASIA_API void FLoadSceneCompleteEvent_DelegateWrapper(const FMulticastScriptDelegate& LoadSceneCompleteEvent, bool sceneReady);


// ********** End Delegate FLoadSceneCompleteEvent *************************************************

// ********** Begin Class UAudio2FaceComponent *****************************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execConnect); \
	DECLARE_FUNCTION(execLoadScene); \
	DECLARE_FUNCTION(execQueueAudio);


FANTASIA_API UClass* Z_Construct_UClass_UAudio2FaceComponent_NoRegister();

#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_34_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAudio2FaceComponent(); \
	friend struct Z_Construct_UClass_UAudio2FaceComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UAudio2FaceComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(UAudio2FaceComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UAudio2FaceComponent_NoRegister) \
	DECLARE_SERIALIZER(UAudio2FaceComponent)


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_34_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	UAudio2FaceComponent(UAudio2FaceComponent&&) = delete; \
	UAudio2FaceComponent(const UAudio2FaceComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAudio2FaceComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAudio2FaceComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAudio2FaceComponent) \
	NO_API virtual ~UAudio2FaceComponent();


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_31_PROLOG
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_34_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_34_INCLASS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_34_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAudio2FaceComponent;

// ********** End Class UAudio2FaceComponent *******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
