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

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_5_DELEGATE \
FANTASIA_API void FIncomingGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingGPTResponseEvent, const FString& GPTResponse);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_6_DELEGATE \
FANTASIA_API void FIncomingChatGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingChatGPTResponseEvent, const FString& chatGPTResponse, const FString& role);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_26_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FChatTurn_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FChatTurn>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_73_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTTSTimedStruct_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FTTSTimedStruct>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_85_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FTTSData_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FTTSData>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_94_DELEGATE \
FANTASIA_API void FSynthesizedEvent_DelegateWrapper(const FMulticastScriptDelegate& SynthesizedEvent, const FString& id);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_95_DELEGATE \
FANTASIA_API void FSynthesizedInternalEvent_DelegateWrapper(const FMulticastScriptDelegate& SynthesizedInternalEvent, FTTSData response, const FString& id);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_101_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FNeo4jResponse_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FNeo4jResponse>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_116_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FNLUResponse_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FNLUResponse>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_131_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNLUIntent(); \
	friend struct Z_Construct_UClass_UNLUIntent_Statics; \
public: \
	DECLARE_CLASS(UNLUIntent, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNLUIntent)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_131_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNLUIntent(UNLUIntent&&); \
	UNLUIntent(const UNLUIntent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLUIntent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLUIntent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNLUIntent) \
	NO_API virtual ~UNLUIntent();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_128_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_131_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_131_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_131_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNLUIntent>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_146_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNLUEntity(); \
	friend struct Z_Construct_UClass_UNLUEntity_Statics; \
public: \
	DECLARE_CLASS(UNLUEntity, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNLUEntity)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_146_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNLUEntity(UNLUEntity&&); \
	UNLUEntity(const UNLUEntity&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNLUEntity); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNLUEntity); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNLUEntity) \
	NO_API virtual ~UNLUEntity();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_143_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_146_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_146_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_146_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNLUEntity>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_176_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultRow(); \
	friend struct Z_Construct_UClass_UNeo4jResultRow_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultRow, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultRow)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_176_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNeo4jResultRow(UNeo4jResultRow&&); \
	UNeo4jResultRow(const UNeo4jResultRow&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultRow); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultRow); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultRow) \
	NO_API virtual ~UNeo4jResultRow();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_173_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_176_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_176_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_176_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultRow>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_188_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCell(); \
	friend struct Z_Construct_UClass_UNeo4jResultCell_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCell, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCell)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_188_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNeo4jResultCell(UNeo4jResultCell&&); \
	UNeo4jResultCell(const UNeo4jResultCell&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCell); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCell); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCell) \
	NO_API virtual ~UNeo4jResultCell();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_185_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_188_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_188_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_188_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCell>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_197_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellNode(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellNode_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellNode, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellNode)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_197_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNeo4jResultCellNode(UNeo4jResultCellNode&&); \
	UNeo4jResultCellNode(const UNeo4jResultCellNode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellNode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellNode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellNode) \
	NO_API virtual ~UNeo4jResultCellNode();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_194_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_197_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_197_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_197_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellNode>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_215_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellRelationship(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellRelationship_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellRelationship, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellRelationship)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_215_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNeo4jResultCellRelationship(UNeo4jResultCellRelationship&&); \
	UNeo4jResultCellRelationship(const UNeo4jResultCellRelationship&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellRelationship); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellRelationship); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellRelationship) \
	NO_API virtual ~UNeo4jResultCellRelationship();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_212_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_215_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_215_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_215_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellRelationship>();

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_233_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUNeo4jResultCellSimple(); \
	friend struct Z_Construct_UClass_UNeo4jResultCellSimple_Statics; \
public: \
	DECLARE_CLASS(UNeo4jResultCellSimple, UNeo4jResultCell, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UNeo4jResultCellSimple)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_233_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UNeo4jResultCellSimple(UNeo4jResultCellSimple&&); \
	UNeo4jResultCellSimple(const UNeo4jResultCellSimple&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UNeo4jResultCellSimple); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UNeo4jResultCellSimple); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UNeo4jResultCellSimple) \
	NO_API virtual ~UNeo4jResultCellSimple();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_230_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_233_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_233_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_233_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UNeo4jResultCellSimple>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h


#define FOREACH_ENUM_EAZUREASRENUM(op) \
	op(ASR_CONTINUOUS) \
	op(ASR_ONESHOT) 

enum EAzureASREnum : uint8;
template<> FANTASIA_API UEnum* StaticEnum<EAzureASREnum>();

#define FOREACH_ENUM_CHATGPTROLETYPE(op) \
	op(ChatGPTRoleType::SYSTEM) \
	op(ChatGPTRoleType::ASSISTANT) \
	op(ChatGPTRoleType::USER) \
	op(ChatGPTRoleType::FUNCTION) 

enum class ChatGPTRoleType : uint8;
template<> struct TIsUEnumClass<ChatGPTRoleType> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<ChatGPTRoleType>();

#define FOREACH_ENUM_INFLUENCENODETYPE(op) \
	op(InfluenceNodeType::CHANCE) \
	op(InfluenceNodeType::UTILITY) \
	op(InfluenceNodeType::DECISION) 

enum class InfluenceNodeType : uint8;
template<> struct TIsUEnumClass<InfluenceNodeType> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<InfluenceNodeType>();

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
