// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "BayesianNetwork.h"

#ifdef FANTASIA_BayesianNetwork_generated_h
#error "BayesianNetwork.generated.h already included, missing '#pragma once' in BayesianNetwork.h"
#endif
#define FANTASIA_BayesianNetwork_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

 
enum class BayesianNodeType : uint8;

// ********** Begin ScriptStruct FMapContainer *****************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_44_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FMapContainer_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FMapContainer;
// ********** End ScriptStruct FMapContainer *******************************************************

// ********** Begin ScriptStruct FBayesianArcStruct ************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_62_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBayesianArcStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FBayesianArcStruct;
// ********** End ScriptStruct FBayesianArcStruct **************************************************

// ********** Begin ScriptStruct FBayesianNodeStruct ***********************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_74_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FBayesianNodeStruct;
// ********** End ScriptStruct FBayesianNodeStruct *************************************************

// ********** Begin Delegate FBNInferenceAvailableEvent ********************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_89_DELEGATE \
FANTASIA_API void FBNInferenceAvailableEvent_DelegateWrapper(const FMulticastScriptDelegate& BNInferenceAvailableEvent);


// ********** End Delegate FBNInferenceAvailableEvent **********************************************

// ********** Begin Class UBayesianNetwork *********************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_94_RPC_WRAPPERS \
	DECLARE_FUNCTION(execgetMarkovBlanketNodes); \
	DECLARE_FUNCTION(execidFromName); \
	DECLARE_FUNCTION(execerase); \
	DECLARE_FUNCTION(execwriteBIF); \
	DECLARE_FUNCTION(execfillCPT); \
	DECLARE_FUNCTION(execfillWith); \
	DECLARE_FUNCTION(execaddArc); \
	DECLARE_FUNCTION(execaddLabelizedVariable); \
	DECLARE_FUNCTION(execaddDiscretizedVariable); \
	DECLARE_FUNCTION(execgetEntropy); \
	DECLARE_FUNCTION(execeraseEvidence); \
	DECLARE_FUNCTION(execeraseAllEvidence); \
	DECLARE_FUNCTION(execsetEvidence); \
	DECLARE_FUNCTION(execgetPosterior); \
	DECLARE_FUNCTION(execmakeInference); \
	DECLARE_FUNCTION(execInit);


FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetwork_NoRegister();

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_94_INCLASS \
private: \
	static void StaticRegisterNativesUBayesianNetwork(); \
	friend struct Z_Construct_UClass_UBayesianNetwork_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetwork_NoRegister(); \
public: \
	DECLARE_CLASS2(UBayesianNetwork, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UBayesianNetwork_NoRegister) \
	DECLARE_SERIALIZER(UBayesianNetwork)


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_94_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBayesianNetwork(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBayesianNetwork) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBayesianNetwork); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBayesianNetwork); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UBayesianNetwork(UBayesianNetwork&&) = delete; \
	UBayesianNetwork(const UBayesianNetwork&) = delete; \
	NO_API virtual ~UBayesianNetwork();


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_91_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_94_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_94_RPC_WRAPPERS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_94_INCLASS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_94_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UBayesianNetwork;

// ********** End Class UBayesianNetwork ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h

// ********** Begin Enum InferenceAlgs *************************************************************
#define FOREACH_ENUM_INFERENCEALGS(op) \
	op(InferenceAlgs::Lazy_Propagation) \
	op(InferenceAlgs::ShaferShenoy) \
	op(InferenceAlgs::VariableElimination) 

enum class InferenceAlgs : uint8;
template<> struct TIsUEnumClass<InferenceAlgs> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<InferenceAlgs>();
// ********** End Enum InferenceAlgs ***************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
