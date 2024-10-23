// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InfluenceDiag.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
 
 struct FArrayFloat;
enum class InfluenceNodeType : uint8;
#ifdef FANTASIA_InfluenceDiag_generated_h
#error "InfluenceDiag.generated.h already included, missing '#pragma once' in InfluenceDiag.h"
#endif
#define FANTASIA_InfluenceDiag_generated_h

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_46_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FInfluenceDiagArcStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FInfluenceDiagArcStruct>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_58_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FInfluenceDiagNodeStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FInfluenceDiagNodeStruct>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_79_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FArrayFloat_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FArrayFloat>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_87_DELEGATE \
FANTASIA_API void FIDInferenceAvailableEvent_DelegateWrapper(const FMulticastScriptDelegate& IDInferenceAvailableEvent);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_RPC_WRAPPERS \
	DECLARE_FUNCTION(execdecisionOrder); \
	DECLARE_FUNCTION(execdecisionOrderExists); \
	DECLARE_FUNCTION(execidFromName); \
	DECLARE_FUNCTION(execerase); \
	DECLARE_FUNCTION(execwriteBIFXML); \
	DECLARE_FUNCTION(execfillUtility); \
	DECLARE_FUNCTION(execfillCPT); \
	DECLARE_FUNCTION(execaddArc); \
	DECLARE_FUNCTION(execaddLabelizedVariable); \
	DECLARE_FUNCTION(execaddDiscretizedVariable); \
	DECLARE_FUNCTION(execeraseEvidence); \
	DECLARE_FUNCTION(execeraseAllEvidence); \
	DECLARE_FUNCTION(execaddEvidence); \
	DECLARE_FUNCTION(execoptimalDecision); \
	DECLARE_FUNCTION(execgetEntropy); \
	DECLARE_FUNCTION(execgetMEU); \
	DECLARE_FUNCTION(execgetPosteriorUtility); \
	DECLARE_FUNCTION(execgetPosterior); \
	DECLARE_FUNCTION(execmakeInference); \
	DECLARE_FUNCTION(execInit);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_INCLASS \
private: \
	static void StaticRegisterNativesUInfluenceDiag(); \
	friend struct Z_Construct_UClass_UInfluenceDiag_Statics; \
public: \
	DECLARE_CLASS(UInfluenceDiag, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UInfluenceDiag)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInfluenceDiag(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInfluenceDiag) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInfluenceDiag); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInfluenceDiag); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UInfluenceDiag(UInfluenceDiag&&); \
	UInfluenceDiag(const UInfluenceDiag&); \
public: \
	NO_API virtual ~UInfluenceDiag();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_89_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UInfluenceDiag>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h


#define FOREACH_ENUM_INFERENCEIDALGS(op) \
	op(InferenceIDAlgs::ShaferShenoyLIMID) 

enum class InferenceIDAlgs : uint8;
template<> struct TIsUEnumClass<InferenceIDAlgs> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<InferenceIDAlgs>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
