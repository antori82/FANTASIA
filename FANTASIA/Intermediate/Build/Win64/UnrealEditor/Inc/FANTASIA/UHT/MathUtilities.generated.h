// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MathUtilities.h"

#ifdef FANTASIA_MathUtilities_generated_h
#error "MathUtilities.generated.h already included, missing '#pragma once' in MathUtilities.h"
#endif
#define FANTASIA_MathUtilities_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

 

// ********** Begin Class UKernelDensityEstimator **************************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h_12_RPC_WRAPPERS \
	DECLARE_FUNCTION(execgetPdf); \
	DECLARE_FUNCTION(execevaluate); \
	DECLARE_FUNCTION(execsetData);


FANTASIA_API UClass* Z_Construct_UClass_UKernelDensityEstimator_NoRegister();

#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h_12_INCLASS \
private: \
	static void StaticRegisterNativesUKernelDensityEstimator(); \
	friend struct Z_Construct_UClass_UKernelDensityEstimator_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UKernelDensityEstimator_NoRegister(); \
public: \
	DECLARE_CLASS2(UKernelDensityEstimator, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UKernelDensityEstimator_NoRegister) \
	DECLARE_SERIALIZER(UKernelDensityEstimator)


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UKernelDensityEstimator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UKernelDensityEstimator) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UKernelDensityEstimator); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UKernelDensityEstimator); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UKernelDensityEstimator(UKernelDensityEstimator&&) = delete; \
	UKernelDensityEstimator(const UKernelDensityEstimator&) = delete; \
	NO_API virtual ~UKernelDensityEstimator();


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h_9_PROLOG
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h_12_RPC_WRAPPERS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h_12_INCLASS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UKernelDensityEstimator;

// ********** End Class UKernelDensityEstimator ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
