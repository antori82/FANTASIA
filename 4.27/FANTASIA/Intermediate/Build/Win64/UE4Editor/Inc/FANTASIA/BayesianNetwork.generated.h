// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
 
#ifdef FANTASIA_BayesianNetwork_generated_h
#error "BayesianNetwork.generated.h already included, missing '#pragma once' in BayesianNetwork.h"
#endif
#define FANTASIA_BayesianNetwork_generated_h

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_50_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FBayesianNodeStruct>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_SPARSE_DATA
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_RPC_WRAPPERS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_RPC_WRAPPERS_NO_PURE_DECLS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBayesianNetworkFactory(); \
	friend struct Z_Construct_UClass_UBayesianNetworkFactory_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetworkFactory, UFactory, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetworkFactory)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_INCLASS \
private: \
	static void StaticRegisterNativesUBayesianNetworkFactory(); \
	friend struct Z_Construct_UClass_UBayesianNetworkFactory_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetworkFactory, UFactory, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetworkFactory)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_STANDARD_CONSTRUCTORS \
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


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UBayesianNetworkFactory(UBayesianNetworkFactory&&); \
	NO_API UBayesianNetworkFactory(const UBayesianNetworkFactory&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UBayesianNetworkFactory); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UBayesianNetworkFactory); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UBayesianNetworkFactory)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_PRIVATE_PROPERTY_OFFSET
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_92_PROLOG
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_RPC_WRAPPERS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_INCLASS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_RPC_WRAPPERS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_INCLASS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_95_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UBayesianNetworkFactory>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_SPARSE_DATA
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execgetEntropy); \
	DECLARE_FUNCTION(execeraseEvidence); \
	DECLARE_FUNCTION(execeraseAllEvidence); \
	DECLARE_FUNCTION(execaddEvidence); \
	DECLARE_FUNCTION(execgetPosterior); \
	DECLARE_FUNCTION(execmakeInference); \
	DECLARE_FUNCTION(execInit);


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execgetEntropy); \
	DECLARE_FUNCTION(execeraseEvidence); \
	DECLARE_FUNCTION(execeraseAllEvidence); \
	DECLARE_FUNCTION(execaddEvidence); \
	DECLARE_FUNCTION(execgetPosterior); \
	DECLARE_FUNCTION(execmakeInference); \
	DECLARE_FUNCTION(execInit);


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUBayesianNetwork(); \
	friend struct Z_Construct_UClass_UBayesianNetwork_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetwork, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetwork)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_INCLASS \
private: \
	static void StaticRegisterNativesUBayesianNetwork(); \
	friend struct Z_Construct_UClass_UBayesianNetwork_Statics; \
public: \
	DECLARE_CLASS(UBayesianNetwork, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UBayesianNetwork)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_STANDARD_CONSTRUCTORS \
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


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_ENHANCED_CONSTRUCTORS \
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


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_PRIVATE_PROPERTY_OFFSET
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_104_PROLOG
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_RPC_WRAPPERS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_INCLASS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_RPC_WRAPPERS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_INCLASS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_107_ENHANCED_CONSTRUCTORS \
static_assert(false, "Unknown access specifier for GENERATED_BODY() macro in class BayesianNetwork."); \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UBayesianNetwork>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h


#define FOREACH_ENUM_INFERENCEALGS(op) \
	op(InferenceAlgs::Lazy_Propagation) \
	op(InferenceAlgs::ShaferShenoy) \
	op(InferenceAlgs::VariableElimination) 

enum class InferenceAlgs : uint8;
template<> FANTASIA_API UEnum* StaticEnum<InferenceAlgs>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
