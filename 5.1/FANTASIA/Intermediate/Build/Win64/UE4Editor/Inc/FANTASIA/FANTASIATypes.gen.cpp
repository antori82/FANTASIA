// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/FANTASIATypes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFANTASIATypes() {}
// Cross Module References
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FTTSData();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_Neo4jOperation();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_TTSVoiceType();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_BayesianNodeType();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FNLUResponse();
	FANTASIA_API UClass* Z_Construct_UClass_UNLUEntity_NoRegister();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FNeo4jResponse();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultRow_NoRegister();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FTTSTimedStruct();
	FANTASIA_API UClass* Z_Construct_UClass_UNLUEntity();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultRow();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCell_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCell();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellNode_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellNode();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellRelationship_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellRelationship();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellSimple_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellSimple();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventSynthesizedInternalEvent_Parms
		{
			FTTSData response;
			FString id;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_response;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::NewProp_response = { "response", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FANTASIA_eventSynthesizedInternalEvent_Parms, response), Z_Construct_UScriptStruct_FTTSData, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FANTASIA_eventSynthesizedInternalEvent_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::NewProp_response,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::NewProp_id,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "SynthesizedInternalEvent__DelegateSignature", nullptr, nullptr, sizeof(_Script_FANTASIA_eventSynthesizedInternalEvent_Parms), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventSynthesizedEvent_Parms
		{
			FString id;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FANTASIA_eventSynthesizedEvent_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::NewProp_id,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "SynthesizedEvent__DelegateSignature", nullptr, nullptr, sizeof(_Script_FANTASIA_eventSynthesizedEvent_Parms), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static UEnum* Neo4jOperation_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_Neo4jOperation, Z_Construct_UPackage__Script_FANTASIA(), TEXT("Neo4jOperation"));
		}
		return Singleton;
	}
	template<> FANTASIA_API UEnum* StaticEnum<Neo4jOperation>()
	{
		return Neo4jOperation_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_Neo4jOperation(Neo4jOperation_StaticEnum, TEXT("/Script/FANTASIA"), TEXT("Neo4jOperation"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FANTASIA_Neo4jOperation_Hash() { return 699348935U; }
	UEnum* Z_Construct_UEnum_FANTASIA_Neo4jOperation()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("Neo4jOperation"), 0, Get_Z_Construct_UEnum_FANTASIA_Neo4jOperation_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "Neo4jOperation::SINGLE_REQUEST", (int64)Neo4jOperation::SINGLE_REQUEST },
				{ "Neo4jOperation::BEGIN_TRANSACTION", (int64)Neo4jOperation::BEGIN_TRANSACTION },
				{ "Neo4jOperation::COMMIT_TRANSACTION", (int64)Neo4jOperation::COMMIT_TRANSACTION },
				{ "Neo4jOperation::ROLLBACK_TRANSACTION", (int64)Neo4jOperation::ROLLBACK_TRANSACTION },
				{ "Neo4jOperation::ADD_TO_TRANSACTION", (int64)Neo4jOperation::ADD_TO_TRANSACTION },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "ADD_TO_TRANSACTION.DisplayName", "Add to transaction" },
				{ "ADD_TO_TRANSACTION.Name", "Neo4jOperation::ADD_TO_TRANSACTION" },
				{ "BEGIN_TRANSACTION.DisplayName", "Begin transaction" },
				{ "BEGIN_TRANSACTION.Name", "Neo4jOperation::BEGIN_TRANSACTION" },
				{ "BlueprintType", "true" },
				{ "COMMIT_TRANSACTION.DisplayName", "Commit transaction" },
				{ "COMMIT_TRANSACTION.Name", "Neo4jOperation::COMMIT_TRANSACTION" },
				{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
				{ "ROLLBACK_TRANSACTION.DisplayName", "Rollback transaction" },
				{ "ROLLBACK_TRANSACTION.Name", "Neo4jOperation::ROLLBACK_TRANSACTION" },
				{ "SINGLE_REQUEST.DisplayName", "Single request" },
				{ "SINGLE_REQUEST.Name", "Neo4jOperation::SINGLE_REQUEST" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
				nullptr,
				"Neo4jOperation",
				"Neo4jOperation",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* TTSVoiceType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_TTSVoiceType, Z_Construct_UPackage__Script_FANTASIA(), TEXT("TTSVoiceType"));
		}
		return Singleton;
	}
	template<> FANTASIA_API UEnum* StaticEnum<TTSVoiceType>()
	{
		return TTSVoiceType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_TTSVoiceType(TTSVoiceType_StaticEnum, TEXT("/Script/FANTASIA"), TEXT("TTSVoiceType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FANTASIA_TTSVoiceType_Hash() { return 1389091731U; }
	UEnum* Z_Construct_UEnum_FANTASIA_TTSVoiceType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("TTSVoiceType"), 0, Get_Z_Construct_UEnum_FANTASIA_TTSVoiceType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "TTSVoiceType::NEURAL", (int64)TTSVoiceType::NEURAL },
				{ "TTSVoiceType::STANDARD", (int64)TTSVoiceType::STANDARD },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
				{ "NEURAL.DisplayName", "Neural" },
				{ "NEURAL.Name", "TTSVoiceType::NEURAL" },
				{ "STANDARD.DisplayName", "Standard" },
				{ "STANDARD.Name", "TTSVoiceType::STANDARD" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
				nullptr,
				"TTSVoiceType",
				"TTSVoiceType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* BayesianNodeType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_BayesianNodeType, Z_Construct_UPackage__Script_FANTASIA(), TEXT("BayesianNodeType"));
		}
		return Singleton;
	}
	template<> FANTASIA_API UEnum* StaticEnum<BayesianNodeType>()
	{
		return BayesianNodeType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_BayesianNodeType(BayesianNodeType_StaticEnum, TEXT("/Script/FANTASIA"), TEXT("BayesianNodeType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FANTASIA_BayesianNodeType_Hash() { return 648551975U; }
	UEnum* Z_Construct_UEnum_FANTASIA_BayesianNodeType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("BayesianNodeType"), 0, Get_Z_Construct_UEnum_FANTASIA_BayesianNodeType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "BayesianNodeType::NORMAL", (int64)BayesianNodeType::NORMAL },
				{ "BayesianNodeType::AMPLITUDE", (int64)BayesianNodeType::AMPLITUDE },
				{ "BayesianNodeType::AND", (int64)BayesianNodeType::AND },
				{ "BayesianNodeType::COUNT", (int64)BayesianNodeType::COUNT },
				{ "BayesianNodeType::EXISTS", (int64)BayesianNodeType::EXISTS },
				{ "BayesianNodeType::FORALL", (int64)BayesianNodeType::FORALL },
				{ "BayesianNodeType::MAX", (int64)BayesianNodeType::MAX },
				{ "BayesianNodeType::MEDIAN", (int64)BayesianNodeType::MEDIAN },
				{ "BayesianNodeType::MIN", (int64)BayesianNodeType::MIN },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "AMPLITUDE.DisplayName", "AMPLITUDE" },
				{ "AMPLITUDE.Name", "BayesianNodeType::AMPLITUDE" },
				{ "AND.DisplayName", "AND" },
				{ "AND.Name", "BayesianNodeType::AND" },
				{ "BlueprintType", "true" },
				{ "COUNT.DisplayName", "COUNT" },
				{ "COUNT.Name", "BayesianNodeType::COUNT" },
				{ "EXISTS.DisplayName", "EXISTS" },
				{ "EXISTS.Name", "BayesianNodeType::EXISTS" },
				{ "FORALL.DisplayName", "FORALL" },
				{ "FORALL.Name", "BayesianNodeType::FORALL" },
				{ "MAX.DisplayName", "MAX" },
				{ "MAX.Name", "BayesianNodeType::MAX" },
				{ "MEDIAN.DisplayName", "MEDIAN" },
				{ "MEDIAN.Name", "BayesianNodeType::MEDIAN" },
				{ "MIN.DisplayName", "MIN" },
				{ "MIN.Name", "BayesianNodeType::MIN" },
				{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
				{ "NORMAL.DisplayName", "NORMAL" },
				{ "NORMAL.Name", "BayesianNodeType::NORMAL" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
				nullptr,
				"BayesianNodeType",
				"BayesianNodeType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FNLUResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FANTASIA_API uint32 Get_Z_Construct_UScriptStruct_FNLUResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLUResponse, Z_Construct_UPackage__Script_FANTASIA(), TEXT("NLUResponse"), sizeof(FNLUResponse), Get_Z_Construct_UScriptStruct_FNLUResponse_Hash());
	}
	return Singleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FNLUResponse>()
{
	return FNLUResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FNLUResponse(FNLUResponse::StaticStruct, TEXT("/Script/FANTASIA"), TEXT("NLUResponse"), false, nullptr, nullptr);
static struct FScriptStruct_FANTASIA_StaticRegisterNativesFNLUResponse
{
	FScriptStruct_FANTASIA_StaticRegisterNativesFNLUResponse()
	{
		UScriptStruct::DeferCppStructOps<FNLUResponse>(FName(TEXT("NLUResponse")));
	}
} ScriptStruct_FANTASIA_StaticRegisterNativesFNLUResponse;
	struct Z_Construct_UScriptStruct_FNLUResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_query_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_query;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_topIntent_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_topIntent;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_score_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_score;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_entities_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_entities_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_entities;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNLUResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FNLUResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLUResponse>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_query_MetaData[] = {
		{ "Category", "NLUResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_query = { "query", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FNLUResponse, query), METADATA_PARAMS(Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_query_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_query_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_topIntent_MetaData[] = {
		{ "Category", "NLUResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_topIntent = { "topIntent", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FNLUResponse, topIntent), METADATA_PARAMS(Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_topIntent_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_topIntent_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_score_MetaData[] = {
		{ "Category", "NLUResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_score = { "score", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FNLUResponse, score), METADATA_PARAMS(Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_score_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_score_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities_Inner = { "entities", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UNLUEntity_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities_MetaData[] = {
		{ "Category", "NLUResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities = { "entities", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FNLUResponse, entities), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FNLUResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_query,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_topIntent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_score,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FNLUResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"NLUResponse",
		sizeof(FNLUResponse),
		alignof(FNLUResponse),
		Z_Construct_UScriptStruct_FNLUResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FNLUResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FNLUResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FNLUResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("NLUResponse"), sizeof(FNLUResponse), Get_Z_Construct_UScriptStruct_FNLUResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FNLUResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FNLUResponse_Hash() { return 2771551005U; }
class UScriptStruct* FNeo4jResponse::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FANTASIA_API uint32 Get_Z_Construct_UScriptStruct_FNeo4jResponse_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FNeo4jResponse, Z_Construct_UPackage__Script_FANTASIA(), TEXT("Neo4jResponse"), sizeof(FNeo4jResponse), Get_Z_Construct_UScriptStruct_FNeo4jResponse_Hash());
	}
	return Singleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FNeo4jResponse>()
{
	return FNeo4jResponse::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FNeo4jResponse(FNeo4jResponse::StaticStruct, TEXT("/Script/FANTASIA"), TEXT("Neo4jResponse"), false, nullptr, nullptr);
static struct FScriptStruct_FANTASIA_StaticRegisterNativesFNeo4jResponse
{
	FScriptStruct_FANTASIA_StaticRegisterNativesFNeo4jResponse()
	{
		UScriptStruct::DeferCppStructOps<FNeo4jResponse>(FName(TEXT("Neo4jResponse")));
	}
} ScriptStruct_FANTASIA_StaticRegisterNativesFNeo4jResponse;
	struct Z_Construct_UScriptStruct_FNeo4jResponse_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_transactionID_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_transactionID;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_headers_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_headers_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_headers;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_rows_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_rows_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_rows;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNeo4jResponse_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNeo4jResponse>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_transactionID_MetaData[] = {
		{ "Category", "Neo4jResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_transactionID = { "transactionID", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FNeo4jResponse, transactionID), METADATA_PARAMS(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_transactionID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_transactionID_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers_Inner = { "headers", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers_MetaData[] = {
		{ "Category", "Neo4jResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers = { "headers", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FNeo4jResponse, headers), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows_Inner = { "rows", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UNeo4jResultRow_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows_MetaData[] = {
		{ "Category", "Neo4jResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows = { "rows", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FNeo4jResponse, rows), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FNeo4jResponse_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_transactionID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"Neo4jResponse",
		sizeof(FNeo4jResponse),
		alignof(FNeo4jResponse),
		Z_Construct_UScriptStruct_FNeo4jResponse_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FNeo4jResponse()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FNeo4jResponse_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("Neo4jResponse"), sizeof(FNeo4jResponse), Get_Z_Construct_UScriptStruct_FNeo4jResponse_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FNeo4jResponse_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FNeo4jResponse_Hash() { return 2114019406U; }
class UScriptStruct* FTTSData::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FANTASIA_API uint32 Get_Z_Construct_UScriptStruct_FTTSData_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FTTSData, Z_Construct_UPackage__Script_FANTASIA(), TEXT("TTSData"), sizeof(FTTSData), Get_Z_Construct_UScriptStruct_FTTSData_Hash());
	}
	return Singleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FTTSData>()
{
	return FTTSData::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FTTSData(FTTSData::StaticStruct, TEXT("/Script/FANTASIA"), TEXT("TTSData"), false, nullptr, nullptr);
static struct FScriptStruct_FANTASIA_StaticRegisterNativesFTTSData
{
	FScriptStruct_FANTASIA_StaticRegisterNativesFTTSData()
	{
		UScriptStruct::DeferCppStructOps<FTTSData>(FName(TEXT("TTSData")));
	}
} ScriptStruct_FANTASIA_StaticRegisterNativesFTTSData;
	struct Z_Construct_UScriptStruct_FTTSData_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTTSData_Statics::Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTTSData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTTSData>();
	}
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTTSData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"TTSData",
		sizeof(FTTSData),
		alignof(FTTSData),
		nullptr,
		0,
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FTTSData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTTSData()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FTTSData_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("TTSData"), sizeof(FTTSData), Get_Z_Construct_UScriptStruct_FTTSData_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FTTSData_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FTTSData_Hash() { return 562674607U; }
class UScriptStruct* FTTSTimedStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FANTASIA_API uint32 Get_Z_Construct_UScriptStruct_FTTSTimedStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FTTSTimedStruct, Z_Construct_UPackage__Script_FANTASIA(), TEXT("TTSTimedStruct"), sizeof(FTTSTimedStruct), Get_Z_Construct_UScriptStruct_FTTSTimedStruct_Hash());
	}
	return Singleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FTTSTimedStruct>()
{
	return FTTSTimedStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FTTSTimedStruct(FTTSTimedStruct::StaticStruct, TEXT("/Script/FANTASIA"), TEXT("TTSTimedStruct"), false, nullptr, nullptr);
static struct FScriptStruct_FANTASIA_StaticRegisterNativesFTTSTimedStruct
{
	FScriptStruct_FANTASIA_StaticRegisterNativesFTTSTimedStruct()
	{
		UScriptStruct::DeferCppStructOps<FTTSTimedStruct>(FName(TEXT("TTSTimedStruct")));
	}
} ScriptStruct_FANTASIA_StaticRegisterNativesFTTSTimedStruct;
	struct Z_Construct_UScriptStruct_FTTSTimedStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_time_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_time;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_data_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_data;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTTSTimedStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_time_MetaData[] = {
		{ "Category", "TTSTimedStruct" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_time = { "time", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTTSTimedStruct, time), METADATA_PARAMS(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_time_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_time_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_data_MetaData[] = {
		{ "Category", "TTSTimedStruct" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_data = { "data", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FTTSTimedStruct, data), METADATA_PARAMS(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_data_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_data_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_time,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_data,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"TTSTimedStruct",
		sizeof(FTTSTimedStruct),
		alignof(FTTSTimedStruct),
		Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FTTSTimedStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FTTSTimedStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("TTSTimedStruct"), sizeof(FTTSTimedStruct), Get_Z_Construct_UScriptStruct_FTTSTimedStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FTTSTimedStruct_Hash() { return 2178192444U; }
	void UNLUEntity::StaticRegisterNativesUNLUEntity()
	{
	}
	UClass* Z_Construct_UClass_UNLUEntity_NoRegister()
	{
		return UNLUEntity::StaticClass();
	}
	struct Z_Construct_UClass_UNLUEntity_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_entity_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_entity;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_type_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_type;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_startIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_startIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_endIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_endIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_score_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_score;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_childName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_childName;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_children_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_children_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_children;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNLUEntity_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNLUEntity_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Azure" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNLUEntity_Statics::NewProp_entity_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_entity = { "entity", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNLUEntity, entity), METADATA_PARAMS(Z_Construct_UClass_UNLUEntity_Statics::NewProp_entity_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::NewProp_entity_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNLUEntity_Statics::NewProp_type_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_type = { "type", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNLUEntity, type), METADATA_PARAMS(Z_Construct_UClass_UNLUEntity_Statics::NewProp_type_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::NewProp_type_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNLUEntity_Statics::NewProp_startIndex_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_startIndex = { "startIndex", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNLUEntity, startIndex), nullptr, METADATA_PARAMS(Z_Construct_UClass_UNLUEntity_Statics::NewProp_startIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::NewProp_startIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNLUEntity_Statics::NewProp_endIndex_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_endIndex = { "endIndex", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNLUEntity, endIndex), nullptr, METADATA_PARAMS(Z_Construct_UClass_UNLUEntity_Statics::NewProp_endIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::NewProp_endIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNLUEntity_Statics::NewProp_score_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_score = { "score", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNLUEntity, score), METADATA_PARAMS(Z_Construct_UClass_UNLUEntity_Statics::NewProp_score_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::NewProp_score_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNLUEntity_Statics::NewProp_childName_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_childName = { "childName", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNLUEntity, childName), METADATA_PARAMS(Z_Construct_UClass_UNLUEntity_Statics::NewProp_childName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::NewProp_childName_MetaData)) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_children_Inner = { "children", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UNLUEntity_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNLUEntity_Statics::NewProp_children_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_children = { "children", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNLUEntity, children), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UNLUEntity_Statics::NewProp_children_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::NewProp_children_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNLUEntity_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_entity,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_startIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_endIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_score,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_childName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_children_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_children,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNLUEntity_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLUEntity>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UNLUEntity_Statics::ClassParams = {
		&UNLUEntity::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UNLUEntity_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UNLUEntity_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UNLUEntity()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UNLUEntity_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UNLUEntity, 1067791959);
	template<> FANTASIA_API UClass* StaticClass<UNLUEntity>()
	{
		return UNLUEntity::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNLUEntity(Z_Construct_UClass_UNLUEntity, &UNLUEntity::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UNLUEntity"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNLUEntity);
	void UNeo4jResultRow::StaticRegisterNativesUNeo4jResultRow()
	{
	}
	UClass* Z_Construct_UClass_UNeo4jResultRow_NoRegister()
	{
		return UNeo4jResultRow::StaticClass();
	}
	struct Z_Construct_UClass_UNeo4jResultRow_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_cells_ValueProp;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_cells_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_cells_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_cells;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNeo4jResultRow_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultRow_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_ValueProp = { "cells", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, Z_Construct_UClass_UNeo4jResultCell_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_Key_KeyProp = { "cells_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_MetaData[] = {
		{ "Category", "Neo4jResultRow" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells = { "cells", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jResultRow, cells), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jResultRow_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNeo4jResultRow_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultRow>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultRow_Statics::ClassParams = {
		&UNeo4jResultRow::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UNeo4jResultRow_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultRow_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultRow_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultRow_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UNeo4jResultRow()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UNeo4jResultRow_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UNeo4jResultRow, 1954858785);
	template<> FANTASIA_API UClass* StaticClass<UNeo4jResultRow>()
	{
		return UNeo4jResultRow::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNeo4jResultRow(Z_Construct_UClass_UNeo4jResultRow, &UNeo4jResultRow::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UNeo4jResultRow"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultRow);
	void UNeo4jResultCell::StaticRegisterNativesUNeo4jResultCell()
	{
	}
	UClass* Z_Construct_UClass_UNeo4jResultCell_NoRegister()
	{
		return UNeo4jResultCell::StaticClass();
	}
	struct Z_Construct_UClass_UNeo4jResultCell_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNeo4jResultCell_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCell_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNeo4jResultCell_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultCell>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultCell_Statics::ClassParams = {
		&UNeo4jResultCell::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCell_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCell_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UNeo4jResultCell()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UNeo4jResultCell_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UNeo4jResultCell, 3438443832);
	template<> FANTASIA_API UClass* StaticClass<UNeo4jResultCell>()
	{
		return UNeo4jResultCell::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNeo4jResultCell(Z_Construct_UClass_UNeo4jResultCell, &UNeo4jResultCell::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UNeo4jResultCell"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultCell);
	void UNeo4jResultCellNode::StaticRegisterNativesUNeo4jResultCellNode()
	{
	}
	UClass* Z_Construct_UClass_UNeo4jResultCellNode_NoRegister()
	{
		return UNeo4jResultCellNode::StaticClass();
	}
	struct Z_Construct_UClass_UNeo4jResultCellNode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_labels_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_labels_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_labels;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_properties_ValueProp;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_properties_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_properties_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_properties;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNeo4jResultCellNode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UNeo4jResultCell,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellNode_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels_Inner = { "labels", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels_MetaData[] = {
		{ "Category", "Neo4jResultCellNode" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels = { "labels", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jResultCellNode, labels), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_id_MetaData[] = {
		{ "Category", "Neo4jResultCellNode" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jResultCellNode, id), METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_id_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_ValueProp = { "properties", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_Key_KeyProp = { "properties_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_MetaData[] = {
		{ "Category", "Neo4jResultCellNode" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties = { "properties", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jResultCellNode, properties), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jResultCellNode_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNeo4jResultCellNode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultCellNode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::ClassParams = {
		&UNeo4jResultCellNode::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UNeo4jResultCellNode_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellNode_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellNode_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellNode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UNeo4jResultCellNode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UNeo4jResultCellNode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UNeo4jResultCellNode, 2279959818);
	template<> FANTASIA_API UClass* StaticClass<UNeo4jResultCellNode>()
	{
		return UNeo4jResultCellNode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNeo4jResultCellNode(Z_Construct_UClass_UNeo4jResultCellNode, &UNeo4jResultCellNode::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UNeo4jResultCellNode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultCellNode);
	void UNeo4jResultCellRelationship::StaticRegisterNativesUNeo4jResultCellRelationship()
	{
	}
	UClass* Z_Construct_UClass_UNeo4jResultCellRelationship_NoRegister()
	{
		return UNeo4jResultCellRelationship::StaticClass();
	}
	struct Z_Construct_UClass_UNeo4jResultCellRelationship_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_label_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_label;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_id_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_properties_ValueProp;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_properties_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_properties_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_properties;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UNeo4jResultCell,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_label_MetaData[] = {
		{ "Category", "Neo4jResultCellRelationship" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_label = { "label", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jResultCellRelationship, label), METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_label_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_label_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_id_MetaData[] = {
		{ "Category", "Neo4jResultCellRelationship" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jResultCellRelationship, id), METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_id_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_id_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_ValueProp = { "properties", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_Key_KeyProp = { "properties_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_MetaData[] = {
		{ "Category", "Neo4jResultCellRelationship" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties = { "properties", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jResultCellRelationship, properties), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_label,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultCellRelationship>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::ClassParams = {
		&UNeo4jResultCellRelationship::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UNeo4jResultCellRelationship()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UNeo4jResultCellRelationship, 315839719);
	template<> FANTASIA_API UClass* StaticClass<UNeo4jResultCellRelationship>()
	{
		return UNeo4jResultCellRelationship::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNeo4jResultCellRelationship(Z_Construct_UClass_UNeo4jResultCellRelationship, &UNeo4jResultCellRelationship::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UNeo4jResultCellRelationship"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultCellRelationship);
	void UNeo4jResultCellSimple::StaticRegisterNativesUNeo4jResultCellSimple()
	{
	}
	UClass* Z_Construct_UClass_UNeo4jResultCellSimple_NoRegister()
	{
		return UNeo4jResultCellSimple::StaticClass();
	}
	struct Z_Construct_UClass_UNeo4jResultCellSimple_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNeo4jResultCellSimple_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UNeo4jResultCell,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellSimple_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jResultCellSimple_Statics::NewProp_value_MetaData[] = {
		{ "Category", "Neo4jResultCellSimple" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellSimple_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jResultCellSimple, value), METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellSimple_Statics::NewProp_value_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellSimple_Statics::NewProp_value_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jResultCellSimple_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellSimple_Statics::NewProp_value,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNeo4jResultCellSimple_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultCellSimple>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultCellSimple_Statics::ClassParams = {
		&UNeo4jResultCellSimple::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UNeo4jResultCellSimple_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellSimple_Statics::PropPointers),
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UNeo4jResultCellSimple_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellSimple_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UNeo4jResultCellSimple()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UNeo4jResultCellSimple_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UNeo4jResultCellSimple, 509731932);
	template<> FANTASIA_API UClass* StaticClass<UNeo4jResultCellSimple>()
	{
		return UNeo4jResultCellSimple::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNeo4jResultCellSimple(Z_Construct_UClass_UNeo4jResultCellSimple, &UNeo4jResultCellSimple::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UNeo4jResultCellSimple"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultCellSimple);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
