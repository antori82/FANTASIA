// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "FANTASIATypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FTTSData;
#ifdef FANTASIA_FANTASIATypes_generated_h
#error "FANTASIATypes.generated.h already included, missing '#pragma once' in FANTASIATypes.h"
#endif
#define FANTASIA_FANTASIATypes_generated_h

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_36_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTTSTimedStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FTTSTimedStruct>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_48_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTTSData_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FTTSData>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_57_DELEGATE \
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


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_58_DELEGATE \
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


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_64_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FNeo4jResponse_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FNeo4jResponse>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_79_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FNLUResponse_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FNLUResponse>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_SPARSE_DATA
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_RPC_WRAPPERS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_ACCESSORS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNLUEntity(); \
	friend struct Z_Construct_UClass_UNLUEntity_Statics; \
public: \
	DECLARE_CLASS(UNLUEntity, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNLUEntity)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_INCLASS \
private: \
	static void StaticRegisterNativesUNLUEntity(); \
	friend struct Z_Construct_UClass_UNLUEntity_Statics; \
public: \
	DECLARE_CLASS(UNLUEntity, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNLUEntity)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNLUEntity(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNLUEntity) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLUEntity); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLUEntity); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNLUEntity(UNLUEntity&&); \
	NO_API UNLUEntity(const UNLUEntity&); \
public: \
	NO_API virtual ~UNLUEntity();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNLUEntity(UNLUEntity&&); \
	NO_API UNLUEntity(const UNLUEntity&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLUEntity); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLUEntity); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNLUEntity) \
	NO_API virtual ~UNLUEntity();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_94_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_97_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNLUEntity>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_SPARSE_DATA
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_RPC_WRAPPERS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_ACCESSORS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultRow(); \
	friend struct Z_Construct_UClass_UNeo4jResultRow_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultRow, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultRow)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultRow(); \
	friend struct Z_Construct_UClass_UNeo4jResultRow_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultRow, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultRow)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultRow(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultRow) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultRow); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultRow); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultRow(UNeo4jResultRow&&); \
	NO_API UNeo4jResultRow(const UNeo4jResultRow&); \
public: \
	NO_API virtual ~UNeo4jResultRow();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultRow(UNeo4jResultRow&&); \
	NO_API UNeo4jResultRow(const UNeo4jResultRow&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultRow); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultRow); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultRow) \
	NO_API virtual ~UNeo4jResultRow();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_124_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_127_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultRow>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_SPARSE_DATA
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_RPC_WRAPPERS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_ACCESSORS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCell(); \
	friend struct Z_Construct_UClass_UNeo4jResultCell_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCell, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCell)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultCell(); \
	friend struct Z_Construct_UClass_UNeo4jResultCell_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCell, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCell)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultCell(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultCell) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCell); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCell); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCell(UNeo4jResultCell&&); \
	NO_API UNeo4jResultCell(const UNeo4jResultCell&); \
public: \
	NO_API virtual ~UNeo4jResultCell();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCell(UNeo4jResultCell&&); \
	NO_API UNeo4jResultCell(const UNeo4jResultCell&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCell); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCell); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCell) \
	NO_API virtual ~UNeo4jResultCell();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_136_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_139_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCell>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_SPARSE_DATA
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_RPC_WRAPPERS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_ACCESSORS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellNode(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellNode_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellNode, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellNode)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellNode(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellNode_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellNode, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellNode)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultCellNode(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultCellNode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellNode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellNode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellNode(UNeo4jResultCellNode&&); \
	NO_API UNeo4jResultCellNode(const UNeo4jResultCellNode&); \
public: \
	NO_API virtual ~UNeo4jResultCellNode();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellNode(UNeo4jResultCellNode&&); \
	NO_API UNeo4jResultCellNode(const UNeo4jResultCellNode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellNode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellNode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellNode) \
	NO_API virtual ~UNeo4jResultCellNode();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_145_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_148_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellNode>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_SPARSE_DATA
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_RPC_WRAPPERS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_ACCESSORS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellRelationship(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellRelationship_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellRelationship, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellRelationship)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellRelationship(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellRelationship_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellRelationship, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellRelationship)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultCellRelationship(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultCellRelationship) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellRelationship); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellRelationship); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellRelationship(UNeo4jResultCellRelationship&&); \
	NO_API UNeo4jResultCellRelationship(const UNeo4jResultCellRelationship&); \
public: \
	NO_API virtual ~UNeo4jResultCellRelationship();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellRelationship(UNeo4jResultCellRelationship&&); \
	NO_API UNeo4jResultCellRelationship(const UNeo4jResultCellRelationship&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellRelationship); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellRelationship); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellRelationship) \
	NO_API virtual ~UNeo4jResultCellRelationship();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_163_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_166_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellRelationship>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_SPARSE_DATA
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_RPC_WRAPPERS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_ACCESSORS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellSimple(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellSimple_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellSimple, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellSimple)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_INCLASS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellSimple(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellSimple_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellSimple, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellSimple)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UNeo4jResultCellSimple(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UNeo4jResultCellSimple) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellSimple); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellSimple); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellSimple(UNeo4jResultCellSimple&&); \
	NO_API UNeo4jResultCellSimple(const UNeo4jResultCellSimple&); \
public: \
	NO_API virtual ~UNeo4jResultCellSimple();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UNeo4jResultCellSimple(UNeo4jResultCellSimple&&); \
	NO_API UNeo4jResultCellSimple(const UNeo4jResultCellSimple&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellSimple); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellSimple); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellSimple) \
	NO_API virtual ~UNeo4jResultCellSimple();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_181_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_184_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellSimple>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h


#define FOREACH_ENUM_BAYESIANNODETYPE(op) \
	op(BayesianNodeType::NORMAL) \
	op(BayesianNodeType::AMPLITUDE) \
	op(BayesianNodeType::AND) \
	op(BayesianNodeType::COUNT) \
	op(BayesianNodeType::EXISTS) \
	op(BayesianNodeType::FORALL) \
	op(BayesianNodeType::MAX) \
	op(BayesianNodeType::MEDIAN) 

enum class BayesianNodeType : uint8;
template<> struct TIsUEnumClass<BayesianNodeType> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<BayesianNodeType>();

#define FOREACH_ENUM_TTSVOICETYPE(op) \
	op(TTSVoiceType::NEURAL) \
	op(TTSVoiceType::STANDARD) 

enum class TTSVoiceType : uint8;
template<> struct TIsUEnumClass<TTSVoiceType> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<TTSVoiceType>();

#define FOREACH_ENUM_NEO4JOPERATION(op) \
	op(Neo4jOperation::SINGLE_REQUEST) \
	op(Neo4jOperation::BEGIN_TRANSACTION) \
	op(Neo4jOperation::COMMIT_TRANSACTION) \
	op(Neo4jOperation::ROLLBACK_TRANSACTION) \
	op(Neo4jOperation::ADD_TO_TRANSACTION) 

enum class Neo4jOperation : uint8;
template<> struct TIsUEnumClass<Neo4jOperation> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<Neo4jOperation>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
