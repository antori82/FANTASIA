// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Neo4jComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
 
enum class Neo4jOperation : uint8;
struct FNeo4jResponse;
#ifdef FANTASIA_Neo4jComponent_generated_h
#error "Neo4jComponent.generated.h already included, missing '#pragma once' in Neo4jComponent.h"
#endif
#define FANTASIA_Neo4jComponent_generated_h

#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_9_DELEGATE \
FANTASIA_API void FIncomingNeo4jResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingNeo4jResponseEvent, FNeo4jResponse Neo4jResponse);


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_SPARSE_DATA
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execsubmitQuery);


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jComponent(); \
	friend struct Z_Construct_UClass_UNeo4jComponent_Statics; \
public: \
	DECLARE_CLASS(UNeo4jComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jComponent)


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jComponent(UNeo4jComponent&&); \
	NO_API UNeo4jComponent(const UNeo4jComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jComponent) \
	NO_API virtual ~UNeo4jComponent();


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_11_PROLOG
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_SPARSE_DATA \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_INCLASS_NO_PURE_DECLS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
