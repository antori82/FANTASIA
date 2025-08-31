// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AzureTTSComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class USoundWave;
#ifdef FANTASIA_AzureTTSComponent_generated_h
#error "AzureTTSComponent.generated.h already included, missing '#pragma once' in AzureTTSComponent.h"
#endif
#define FANTASIA_AzureTTSComponent_generated_h

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTTSGetRawSound); \
	DECLARE_FUNCTION(execTTSGetSound); \
	DECLARE_FUNCTION(execTTSSynthesize);


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAzureTTSComponent(); \
	friend struct Z_Construct_UClass_UAzureTTSComponent_Statics; \
public: \
	DECLARE_CLASS(UAzureTTSComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UAzureTTSComponent) \
	virtual UObject* _getUObject() const override { return const_cast<UAzureTTSComponent*>(this); }


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UAzureTTSComponent(UAzureTTSComponent&&); \
	UAzureTTSComponent(const UAzureTTSComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAzureTTSComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAzureTTSComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAzureTTSComponent) \
	NO_API virtual ~UAzureTTSComponent();


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_24_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_INCLASS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_27_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UAzureTTSComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
