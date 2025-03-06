// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AWSPollyComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USoundWave;
struct FTTSTimedStruct;
#ifdef FANTASIA_AWSPollyComponent_generated_h
#error "AWSPollyComponent.generated.h already included, missing '#pragma once' in AWSPollyComponent.h"
#endif
#define FANTASIA_AWSPollyComponent_generated_h

#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTTSGetRawSound); \
	DECLARE_FUNCTION(execAWSPollyGetNotifies); \
	DECLARE_FUNCTION(execAWSPollyGetLipSync); \
	DECLARE_FUNCTION(execAWSPollyGetSound); \
	DECLARE_FUNCTION(execAWSPollySynthesize);


#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_20_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAWSPollyComponent(); \
	friend struct Z_Construct_UClass_UAWSPollyComponent_Statics; \
public: \
	DECLARE_CLASS(UAWSPollyComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UAWSPollyComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_20_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UAWSPollyComponent(UAWSPollyComponent&&); \
	UAWSPollyComponent(const UAWSPollyComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAWSPollyComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAWSPollyComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAWSPollyComponent) \
	NO_API virtual ~UAWSPollyComponent();


#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_17_PROLOG
#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_20_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_20_INCLASS_NO_PURE_DECLS \
	FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_20_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UAWSPollyComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
