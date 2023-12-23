// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "BayesianNetwork.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
 
enum class BayesianNodeType : uint8;
struct FMapContainer;
#ifdef FANTASIA_BayesianNetwork_generated_h
#error "BayesianNetwork.generated.h already included, missing '#pragma once' in BayesianNetwork.h"
#endif
#define FANTASIA_BayesianNetwork_generated_h

#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_30_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FMapContainer_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FMapContainer>();

#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_36_DELEGATE \
FANTASIA_API void FGetPosteriorDelegate_DelegateWrapper(const FScriptDelegate& GetPosteriorDelegate, FMapContainer outMap);


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_50_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBayesianArcStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FBayesianArcStruct>();

#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_62_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FBayesianNodeStruct>();

#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_SPARSE_DATA
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execgetMarkovBlanketNodes); \
	DECLARE_FUNCTION(execidFromName); \
	DECLARE_FUNCTION(execerase); \
	DECLARE_FUNCTION(execwriteBIF); \
	DECLARE_FUNCTION(execfillWith); \
	DECLARE_FUNCTION(execaddArc); \
	DECLARE_FUNCTION(execaddLabelizedVariable); \
	DECLARE_FUNCTION(execaddDiscretizedVariable); \
	DECLARE_FUNCTION(execgetEntropy); \
	DECLARE_FUNCTION(execeraseEvidence); \
	DECLARE_FUNCTION(execeraseAllEvidence); \
	DECLARE_FUNCTION(execaddEvidence); \
	DECLARE_FUNCTION(execgetPosterior); \
	DECLARE_FUNCTION(execmakeInference); \
	DECLARE_FUNCTION(execInit);


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_INCLASS \
private: \
	static void StaticRegisterNativesUBayesianNetwork(); \
	friend struct Z_Construct_UClass_UBayesianNetwork_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetwork, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetwork)


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBayesianNetwork(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBayesianNetwork) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBayesianNetwork); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBayesianNetwork); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBayesianNetwork(UBayesianNetwork&&); \
	NO_API UBayesianNetwork(const UBayesianNetwork&); \
public: \
	NO_API virtual ~UBayesianNetwork();


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_78_PROLOG
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_SPARSE_DATA \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_RPC_WRAPPERS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_INCLASS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_81_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UBayesianNetwork>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h


#define FOREACH_ENUM_INFERENCEALGS(op) \
	op(InferenceAlgs::Lazy_Propagation) \
	op(InferenceAlgs::ShaferShenoy) \
	op(InferenceAlgs::VariableElimination) 

enum class InferenceAlgs : uint8;
template<> struct TIsUEnumClass<InferenceAlgs> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<InferenceAlgs>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
