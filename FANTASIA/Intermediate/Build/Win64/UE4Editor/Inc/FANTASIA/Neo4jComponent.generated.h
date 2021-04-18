// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNeo4jResponse;
enum class Neo4jOperation : uint8;
 
#ifdef FANTASIA_Neo4jComponent_generated_h
#error "Neo4jComponent.generated.h already included, missing '#pragma once' in Neo4jComponent.h"
#endif
#define FANTASIA_Neo4jComponent_generated_h

#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_9_DELEGATE \
struct _Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms \
{ \
	FNeo4jResponse Neo4jResponse; \
}; \
static inline void FIncomingNeo4jResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingNeo4jResponseEvent, FNeo4jResponse Neo4jResponse) \
{ \
	_Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms Parms; \
	Parms.Neo4jResponse=Neo4jResponse; \
	IncomingNeo4jResponseEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_SPARSE_DATA
#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execsubmitQuery);


#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execsubmitQuery);


#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jComponent(); \
	friend struct Z_Construct_UClass_UNeo4jComponent_Statics; \
public: \
	DECLARE_CLASS(UNeo4jComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jComponent)


#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jComponent(); \
	friend struct Z_Construct_UClass_UNeo4jComponent_Statics; \
public: \
	DECLARE_CLASS(UNeo4jComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jComponent)


#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jComponent(UNeo4jComponent&&); \
	NO_API UNeo4jComponent(const UNeo4jComponent&); \
public:


#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jComponent(UNeo4jComponent&&); \
	NO_API UNeo4jComponent(const UNeo4jComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jComponent)


#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_PRIVATE_PROPERTY_OFFSET
#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_11_PROLOG
#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_PRIVATE_PROPERTY_OFFSET \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_SPARSE_DATA \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_RPC_WRAPPERS \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_INCLASS \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_PRIVATE_PROPERTY_OFFSET \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_SPARSE_DATA \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_INCLASS_NO_PURE_DECLS \
	Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
