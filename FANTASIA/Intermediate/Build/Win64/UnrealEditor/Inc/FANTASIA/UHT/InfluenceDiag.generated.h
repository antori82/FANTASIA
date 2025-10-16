// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "InfluenceDiag.h"

#ifdef FANTASIA_InfluenceDiag_generated_h
#error "InfluenceDiag.generated.h already included, missing '#pragma once' in InfluenceDiag.h"
#endif
#define FANTASIA_InfluenceDiag_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

 
 struct FArrayFloat;
enum class InfluenceNodeType : uint8;

// ********** Begin ScriptStruct FInfluenceDiagArcStruct *******************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_46_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FInfluenceDiagArcStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FInfluenceDiagArcStruct;
// ********** End ScriptStruct FInfluenceDiagArcStruct *********************************************

// ********** Begin ScriptStruct FInfluenceDiagNodeStruct ******************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_58_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FInfluenceDiagNodeStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FInfluenceDiagNodeStruct;
// ********** End ScriptStruct FInfluenceDiagNodeStruct ********************************************

// ********** Begin ScriptStruct FArrayFloat *******************************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_79_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FArrayFloat_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FArrayFloat;
// ********** End ScriptStruct FArrayFloat *********************************************************

// ********** Begin Delegate FIDInferenceAvailableEvent ********************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_87_DELEGATE \
FANTASIA_API void FIDInferenceAvailableEvent_DelegateWrapper(const FMulticastScriptDelegate& IDInferenceAvailableEvent);


// ********** End Delegate FIDInferenceAvailableEvent **********************************************

// ********** Begin Class UInfluenceDiag ***********************************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_RPC_WRAPPERS \
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


FANTASIA_API UClass* Z_Construct_UClass_UInfluenceDiag_NoRegister();

#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_INCLASS \
private: \
	static void StaticRegisterNativesUInfluenceDiag(); \
	friend struct Z_Construct_UClass_UInfluenceDiag_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UInfluenceDiag_NoRegister(); \
public: \
	DECLARE_CLASS2(UInfluenceDiag, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UInfluenceDiag_NoRegister) \
	DECLARE_SERIALIZER(UInfluenceDiag)


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UInfluenceDiag(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UInfluenceDiag) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UInfluenceDiag); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UInfluenceDiag); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UInfluenceDiag(UInfluenceDiag&&) = delete; \
	UInfluenceDiag(const UInfluenceDiag&) = delete; \
	NO_API virtual ~UInfluenceDiag();


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_89_PROLOG
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_RPC_WRAPPERS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_INCLASS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h_92_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UInfluenceDiag;

// ********** End Class UInfluenceDiag *************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_InfluenceDiag_h

// ********** Begin Enum InferenceIDAlgs ***********************************************************
#define FOREACH_ENUM_INFERENCEIDALGS(op) \
	op(InferenceIDAlgs::ShaferShenoyLIMID) 

enum class InferenceIDAlgs : uint8;
template<> struct TIsUEnumClass<InferenceIDAlgs> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<InferenceIDAlgs>();
// ********** End Enum InferenceIDAlgs *************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
