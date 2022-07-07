// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FTTSData;
#ifdef FANTASIA_FANTASIATypes_generated_h
#error "FANTASIATypes.generated.h already included, missing '#pragma once' in FANTASIATypes.h"
#endif
#define FANTASIA_FANTASIATypes_generated_h

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_66_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FNLUResponse_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FNLUResponse>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_51_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FNeo4jResponse_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FNeo4jResponse>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_35_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTTSData_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FTTSData>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_23_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTTSTimedStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FTTSTimedStruct>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_45_DELEGATE \
struct _Script_FANTASIA_eventSynthesizedInternalEvent_Parms \
{ \
	FTTSData response; \
	FString id; \
}; \
static inline void FSynthesizedInternalEvent_DelegateWrapper(const FMulticastScriptDelegate& SynthesizedInternalEvent, FTTSData response, const FString& id) \
{ \
	_Script_FANTASIA_eventSynthesizedInternalEvent_Parms Parms; \
	Parms.response=response; \
	Parms.id=id; \
	SynthesizedInternalEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_44_DELEGATE \
struct _Script_FANTASIA_eventSynthesizedEvent_Parms \
{ \
	FString id; \
}; \
static inline void FSynthesizedEvent_DelegateWrapper(const FMulticastScriptDelegate& SynthesizedEvent, const FString& id) \
{ \
	_Script_FANTASIA_eventSynthesizedEvent_Parms Parms; \
	Parms.id=id; \
	SynthesizedEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_SPARSE_DATA
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_RPC_WRAPPERS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_RPC_WRAPPERS_NO_PURE_DECLS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNLUEntity(); \
	friend struct Z_Construct_UClass_UNLUEntity_Statics; \
public: \
	DECLARE_CLASS(UNLUEntity, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNLUEntity)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_INCLASS \
private: \
	static void StaticRegisterNativesUNLUEntity(); \
	friend struct Z_Construct_UClass_UNLUEntity_Statics; \
public: \
	DECLARE_CLASS(UNLUEntity, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNLUEntity)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLUEntity(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLUEntity) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLUEntity); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLUEntity); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNLUEntity(UNLUEntity&&); \
	NO_API UNLUEntity(const UNLUEntity&); \
public:


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNLUEntity(UNLUEntity&&); \
	NO_API UNLUEntity(const UNLUEntity&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLUEntity); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLUEntity); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNLUEntity)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_PRIVATE_PROPERTY_OFFSET
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_81_PROLOG
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_RPC_WRAPPERS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_INCLASS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_RPC_WRAPPERS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_INCLASS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_84_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNLUEntity>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_SPARSE_DATA
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_RPC_WRAPPERS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_RPC_WRAPPERS_NO_PURE_DECLS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultRow(); \
	friend struct Z_Construct_UClass_UNeo4jResultRow_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultRow, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultRow)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultRow(); \
	friend struct Z_Construct_UClass_UNeo4jResultRow_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultRow, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultRow)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultRow(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultRow) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultRow); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultRow); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultRow(UNeo4jResultRow&&); \
	NO_API UNeo4jResultRow(const UNeo4jResultRow&); \
public:


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultRow(UNeo4jResultRow&&); \
	NO_API UNeo4jResultRow(const UNeo4jResultRow&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultRow); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultRow); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultRow)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_PRIVATE_PROPERTY_OFFSET
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_111_PROLOG
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_RPC_WRAPPERS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_INCLASS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_RPC_WRAPPERS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_INCLASS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_114_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultRow>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_SPARSE_DATA
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_RPC_WRAPPERS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_RPC_WRAPPERS_NO_PURE_DECLS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCell(); \
	friend struct Z_Construct_UClass_UNeo4jResultCell_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCell, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCell)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultCell(); \
	friend struct Z_Construct_UClass_UNeo4jResultCell_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCell, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCell)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultCell(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultCell) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCell); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCell); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCell(UNeo4jResultCell&&); \
	NO_API UNeo4jResultCell(const UNeo4jResultCell&); \
public:


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCell(UNeo4jResultCell&&); \
	NO_API UNeo4jResultCell(const UNeo4jResultCell&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCell); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCell); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCell)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_PRIVATE_PROPERTY_OFFSET
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_123_PROLOG
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_RPC_WRAPPERS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_INCLASS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_RPC_WRAPPERS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_INCLASS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_126_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCell>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_SPARSE_DATA
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_RPC_WRAPPERS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_RPC_WRAPPERS_NO_PURE_DECLS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellNode(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellNode_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellNode, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellNode)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellNode(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellNode_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellNode, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellNode)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultCellNode(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultCellNode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellNode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellNode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellNode(UNeo4jResultCellNode&&); \
	NO_API UNeo4jResultCellNode(const UNeo4jResultCellNode&); \
public:


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellNode(UNeo4jResultCellNode&&); \
	NO_API UNeo4jResultCellNode(const UNeo4jResultCellNode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellNode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellNode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellNode)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_PRIVATE_PROPERTY_OFFSET
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_132_PROLOG
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_RPC_WRAPPERS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_INCLASS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_RPC_WRAPPERS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_INCLASS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_135_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellNode>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_SPARSE_DATA
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_RPC_WRAPPERS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_RPC_WRAPPERS_NO_PURE_DECLS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellRelationship(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellRelationship_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellRelationship, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellRelationship)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellRelationship(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellRelationship_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellRelationship, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellRelationship)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultCellRelationship(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultCellRelationship) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellRelationship); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellRelationship); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellRelationship(UNeo4jResultCellRelationship&&); \
	NO_API UNeo4jResultCellRelationship(const UNeo4jResultCellRelationship&); \
public:


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellRelationship(UNeo4jResultCellRelationship&&); \
	NO_API UNeo4jResultCellRelationship(const UNeo4jResultCellRelationship&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellRelationship); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellRelationship); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellRelationship)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_PRIVATE_PROPERTY_OFFSET
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_150_PROLOG
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_RPC_WRAPPERS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_INCLASS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_RPC_WRAPPERS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_INCLASS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_153_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellRelationship>();

#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_SPARSE_DATA
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_RPC_WRAPPERS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_RPC_WRAPPERS_NO_PURE_DECLS
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellSimple(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellSimple_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellSimple, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellSimple)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellSimple(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellSimple_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellSimple, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellSimple)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultCellSimple(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultCellSimple) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellSimple); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellSimple); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellSimple(UNeo4jResultCellSimple&&); \
	NO_API UNeo4jResultCellSimple(const UNeo4jResultCellSimple&); \
public:


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellSimple(UNeo4jResultCellSimple&&); \
	NO_API UNeo4jResultCellSimple(const UNeo4jResultCellSimple&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellSimple); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellSimple); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellSimple)


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_PRIVATE_PROPERTY_OFFSET
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_168_PROLOG
#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_RPC_WRAPPERS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_INCLASS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_PRIVATE_PROPERTY_OFFSET \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_SPARSE_DATA \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_RPC_WRAPPERS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_INCLASS_NO_PURE_DECLS \
	Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_171_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellSimple>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Hologram5G_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h


#define FOREACH_ENUM_NEO4JOPERATION(op) \
	op(Neo4jOperation::SINGLE_REQUEST) \
	op(Neo4jOperation::BEGIN_TRANSACTION) \
	op(Neo4jOperation::COMMIT_TRANSACTION) \
	op(Neo4jOperation::ROLLBACK_TRANSACTION) \
	op(Neo4jOperation::ADD_TO_TRANSACTION) 

enum class Neo4jOperation : uint8;
template<> FANTASIA_API UEnum* StaticEnum<Neo4jOperation>();

#define FOREACH_ENUM_TTSVOICETYPE(op) \
	op(TTSVoiceType::NEURAL) \
	op(TTSVoiceType::STANDARD) 

enum class TTSVoiceType : uint8;
template<> FANTASIA_API UEnum* StaticEnum<TTSVoiceType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
