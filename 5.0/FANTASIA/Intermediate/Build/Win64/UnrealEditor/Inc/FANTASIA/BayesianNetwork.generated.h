// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FMapContainer;
enum class BayesianNodeType : uint8;
 
#ifdef FANTASIA_BayesianNetwork_generated_h
#error "BayesianNetwork.generated.h already included, missing '#pragma once' in BayesianNetwork.h"
#endif
#define FANTASIA_BayesianNetwork_generated_h

#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_29_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FMapContainer_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FMapContainer>();

#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_35_DELEGATE \
struct _Script_FANTASIA_eventGetPosteriorDelegate_Parms \
{ \
	FMapContainer outMap; \
}; \
static inline void FGetPosteriorDelegate_DelegateWrapper(const FScriptDelegate& GetPosteriorDelegate, FMapContainer outMap) \
{ \
	_Script_FANTASIA_eventGetPosteriorDelegate_Parms Parms; \
	Parms.outMap=outMap; \
	GetPosteriorDelegate.ProcessDelegate<UObject>(&Parms); \
}


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_48_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBayesianArcStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FBayesianArcStruct>();

#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_60_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FBayesianNodeStruct>();

#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_SPARSE_DATA
#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_RPC_WRAPPERS
#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBayesianNetworkFactory(); \
	friend struct Z_Construct_UClass_UBayesianNetworkFactory_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetworkFactory, UFactory, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetworkFactory)


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_INCLASS \
private: \
	static void StaticRegisterNativesUBayesianNetworkFactory(); \
	friend struct Z_Construct_UClass_UBayesianNetworkFactory_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetworkFactory, UFactory, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetworkFactory)


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBayesianNetworkFactory(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBayesianNetworkFactory) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBayesianNetworkFactory); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBayesianNetworkFactory); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBayesianNetworkFactory(UBayesianNetworkFactory&&); \
	NO_API UBayesianNetworkFactory(const UBayesianNetworkFactory&); \
public:


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBayesianNetworkFactory(UBayesianNetworkFactory&&); \
	NO_API UBayesianNetworkFactory(const UBayesianNetworkFactory&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBayesianNetworkFactory); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBayesianNetworkFactory); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBayesianNetworkFactory)


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_83_PROLOG
#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_SPARSE_DATA \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_RPC_WRAPPERS \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_INCLASS \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_SPARSE_DATA \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_INCLASS_NO_PURE_DECLS \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_86_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UBayesianNetworkFactory>();

#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_SPARSE_DATA
#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_RPC_WRAPPERS \
 \
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


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_RPC_WRAPPERS_NO_PURE_DECLS \
 \
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


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBayesianNetwork(); \
	friend struct Z_Construct_UClass_UBayesianNetwork_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetwork, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetwork)


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_INCLASS \
private: \
	static void StaticRegisterNativesUBayesianNetwork(); \
	friend struct Z_Construct_UClass_UBayesianNetwork_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetwork, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetwork)


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBayesianNetwork(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBayesianNetwork) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBayesianNetwork); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBayesianNetwork); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBayesianNetwork(UBayesianNetwork&&); \
	NO_API UBayesianNetwork(const UBayesianNetwork&); \
public:


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UBayesianNetwork(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBayesianNetwork(UBayesianNetwork&&); \
	NO_API UBayesianNetwork(const UBayesianNetwork&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBayesianNetwork); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBayesianNetwork); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBayesianNetwork)


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_PROLOG
#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_SPARSE_DATA \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_RPC_WRAPPERS \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_INCLASS \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_SPARSE_DATA \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_INCLASS_NO_PURE_DECLS \
	FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_98_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class BayesianNetwork."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UBayesianNetwork>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h


#define FOREACH_ENUM_INFERENCEALGS(op) \
	op(InferenceAlgs::Lazy_Propagation) \
	op(InferenceAlgs::ShaferShenoy) \
	op(InferenceAlgs::VariableElimination) 

enum class InferenceAlgs : uint8;
template<> FANTASIA_API UEnum* StaticEnum<InferenceAlgs>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
