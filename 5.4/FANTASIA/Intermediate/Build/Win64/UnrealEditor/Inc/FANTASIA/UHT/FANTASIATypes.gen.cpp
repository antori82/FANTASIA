// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/FANTASIATypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFANTASIATypes() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCell();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCell_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellNode();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellNode_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellRelationship();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellRelationship_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellSimple();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultCellSimple_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultRow();
FANTASIA_API UClass* Z_Construct_UClass_UNeo4jResultRow_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UNLUEntity();
FANTASIA_API UClass* Z_Construct_UClass_UNLUEntity_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UNLUIntent();
FANTASIA_API UClass* Z_Construct_UClass_UNLUIntent_NoRegister();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_BayesianNodeType();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_ChatGPTRoleType();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_InfluenceNodeType();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_Neo4jOperation();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_TTSVoiceType();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FChatTurn();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FNeo4jResponse();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FNLUResponse();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FTTSData();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FTTSTimedStruct();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Delegate FIncomingGPTResponseEvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingGPTResponseEvent_Parms
	{
		FString GPTResponse;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_GPTResponse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::NewProp_GPTResponse = { "GPTResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms, GPTResponse), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::NewProp_GPTResponse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingGPTResponseEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingGPTResponseEvent, const FString& GPTResponse)
{
	struct _Script_FANTASIA_eventIncomingGPTResponseEvent_Parms
	{
		FString GPTResponse;
	};
	_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms Parms;
	Parms.GPTResponse=GPTResponse;
	IncomingGPTResponseEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingGPTResponseEvent

// Begin Delegate FIncomingChatGPTResponseEvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms
	{
		FString chatGPTResponse;
		FString role;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_chatGPTResponse;
	static const UECodeGen_Private::FStrPropertyParams NewProp_role;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::NewProp_chatGPTResponse = { "chatGPTResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms, chatGPTResponse), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::NewProp_role = { "role", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms, role), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::NewProp_chatGPTResponse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::NewProp_role,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingChatGPTResponseEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingChatGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingChatGPTResponseEvent, const FString& chatGPTResponse, const FString& role)
{
	struct _Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms
	{
		FString chatGPTResponse;
		FString role;
	};
	_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms Parms;
	Parms.chatGPTResponse=chatGPTResponse;
	Parms.role=role;
	IncomingChatGPTResponseEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingChatGPTResponseEvent

// Begin Enum ChatGPTRoleType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ChatGPTRoleType;
static UEnum* ChatGPTRoleType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ChatGPTRoleType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ChatGPTRoleType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_ChatGPTRoleType, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("ChatGPTRoleType"));
	}
	return Z_Registration_Info_UEnum_ChatGPTRoleType.OuterSingleton;
}
template<> FANTASIA_API UEnum* StaticEnum<ChatGPTRoleType>()
{
	return ChatGPTRoleType_StaticEnum();
}
struct Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "ASSISTANT.DisplayName", "ASSISTANT" },
		{ "ASSISTANT.Name", "ChatGPTRoleType::ASSISTANT" },
		{ "BlueprintType", "true" },
		{ "FUNCTION.DisplayName", "FUNCTION" },
		{ "FUNCTION.Name", "ChatGPTRoleType::FUNCTION" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
		{ "SYSTEM.DisplayName", "SYSTEM" },
		{ "SYSTEM.Name", "ChatGPTRoleType::SYSTEM" },
		{ "USER.DisplayName", "USER" },
		{ "USER.Name", "ChatGPTRoleType::USER" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ChatGPTRoleType::SYSTEM", (int64)ChatGPTRoleType::SYSTEM },
		{ "ChatGPTRoleType::ASSISTANT", (int64)ChatGPTRoleType::ASSISTANT },
		{ "ChatGPTRoleType::USER", (int64)ChatGPTRoleType::USER },
		{ "ChatGPTRoleType::FUNCTION", (int64)ChatGPTRoleType::FUNCTION },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	"ChatGPTRoleType",
	"ChatGPTRoleType",
	Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FANTASIA_ChatGPTRoleType()
{
	if (!Z_Registration_Info_UEnum_ChatGPTRoleType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ChatGPTRoleType.InnerSingleton, Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ChatGPTRoleType.InnerSingleton;
}
// End Enum ChatGPTRoleType

// Begin ScriptStruct FChatTurn
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ChatTurn;
class UScriptStruct* FChatTurn::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ChatTurn.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ChatTurn.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FChatTurn, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("ChatTurn"));
	}
	return Z_Registration_Info_UScriptStruct_ChatTurn.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FChatTurn>()
{
	return FChatTurn::StaticStruct();
}
struct Z_Construct_UScriptStruct_FChatTurn_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_role_MetaData[] = {
		{ "Category", "ChatTurn" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_content_MetaData[] = {
		{ "Category", "ChatTurn" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_role;
	static const UECodeGen_Private::FStrPropertyParams NewProp_content;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FChatTurn>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role = { "role", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChatTurn, role), Z_Construct_UEnum_FANTASIA_ChatGPTRoleType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_role_MetaData), NewProp_role_MetaData) }; // 1359525058
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_content = { "content", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChatTurn, content), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_content_MetaData), NewProp_content_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FChatTurn_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_content,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChatTurn_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FChatTurn_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"ChatTurn",
	Z_Construct_UScriptStruct_FChatTurn_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChatTurn_Statics::PropPointers),
	sizeof(FChatTurn),
	alignof(FChatTurn),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChatTurn_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FChatTurn_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FChatTurn()
{
	if (!Z_Registration_Info_UScriptStruct_ChatTurn.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ChatTurn.InnerSingleton, Z_Construct_UScriptStruct_FChatTurn_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_ChatTurn.InnerSingleton;
}
// End ScriptStruct FChatTurn

// Begin Enum InfluenceNodeType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_InfluenceNodeType;
static UEnum* InfluenceNodeType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_InfluenceNodeType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_InfluenceNodeType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_InfluenceNodeType, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("InfluenceNodeType"));
	}
	return Z_Registration_Info_UEnum_InfluenceNodeType.OuterSingleton;
}
template<> FANTASIA_API UEnum* StaticEnum<InfluenceNodeType>()
{
	return InfluenceNodeType_StaticEnum();
}
struct Z_Construct_UEnum_FANTASIA_InfluenceNodeType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "CHANCE.DisplayName", "CHANCE" },
		{ "CHANCE.Name", "InfluenceNodeType::CHANCE" },
		{ "DECISION.DisplayName", "DECISION" },
		{ "DECISION.Name", "InfluenceNodeType::DECISION" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
		{ "UTILITY.DisplayName", "UTILITY" },
		{ "UTILITY.Name", "InfluenceNodeType::UTILITY" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "InfluenceNodeType::CHANCE", (int64)InfluenceNodeType::CHANCE },
		{ "InfluenceNodeType::UTILITY", (int64)InfluenceNodeType::UTILITY },
		{ "InfluenceNodeType::DECISION", (int64)InfluenceNodeType::DECISION },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_InfluenceNodeType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	"InfluenceNodeType",
	"InfluenceNodeType",
	Z_Construct_UEnum_FANTASIA_InfluenceNodeType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_InfluenceNodeType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_InfluenceNodeType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_InfluenceNodeType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FANTASIA_InfluenceNodeType()
{
	if (!Z_Registration_Info_UEnum_InfluenceNodeType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_InfluenceNodeType.InnerSingleton, Z_Construct_UEnum_FANTASIA_InfluenceNodeType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_InfluenceNodeType.InnerSingleton;
}
// End Enum InfluenceNodeType

// Begin Enum BayesianNodeType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_BayesianNodeType;
static UEnum* BayesianNodeType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_BayesianNodeType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_BayesianNodeType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_BayesianNodeType, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("BayesianNodeType"));
	}
	return Z_Registration_Info_UEnum_BayesianNodeType.OuterSingleton;
}
template<> FANTASIA_API UEnum* StaticEnum<BayesianNodeType>()
{
	return BayesianNodeType_StaticEnum();
}
struct Z_Construct_UEnum_FANTASIA_BayesianNodeType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
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
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
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
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_BayesianNodeType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	"BayesianNodeType",
	"BayesianNodeType",
	Z_Construct_UEnum_FANTASIA_BayesianNodeType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_BayesianNodeType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_BayesianNodeType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_BayesianNodeType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FANTASIA_BayesianNodeType()
{
	if (!Z_Registration_Info_UEnum_BayesianNodeType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_BayesianNodeType.InnerSingleton, Z_Construct_UEnum_FANTASIA_BayesianNodeType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_BayesianNodeType.InnerSingleton;
}
// End Enum BayesianNodeType

// Begin Enum TTSVoiceType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_TTSVoiceType;
static UEnum* TTSVoiceType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_TTSVoiceType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_TTSVoiceType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_TTSVoiceType, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("TTSVoiceType"));
	}
	return Z_Registration_Info_UEnum_TTSVoiceType.OuterSingleton;
}
template<> FANTASIA_API UEnum* StaticEnum<TTSVoiceType>()
{
	return TTSVoiceType_StaticEnum();
}
struct Z_Construct_UEnum_FANTASIA_TTSVoiceType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
		{ "NEURAL.DisplayName", "Neural" },
		{ "NEURAL.Name", "TTSVoiceType::NEURAL" },
		{ "STANDARD.DisplayName", "Standard" },
		{ "STANDARD.Name", "TTSVoiceType::STANDARD" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "TTSVoiceType::NEURAL", (int64)TTSVoiceType::NEURAL },
		{ "TTSVoiceType::STANDARD", (int64)TTSVoiceType::STANDARD },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_TTSVoiceType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	"TTSVoiceType",
	"TTSVoiceType",
	Z_Construct_UEnum_FANTASIA_TTSVoiceType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_TTSVoiceType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_TTSVoiceType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_TTSVoiceType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FANTASIA_TTSVoiceType()
{
	if (!Z_Registration_Info_UEnum_TTSVoiceType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_TTSVoiceType.InnerSingleton, Z_Construct_UEnum_FANTASIA_TTSVoiceType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_TTSVoiceType.InnerSingleton;
}
// End Enum TTSVoiceType

// Begin Enum Neo4jOperation
static FEnumRegistrationInfo Z_Registration_Info_UEnum_Neo4jOperation;
static UEnum* Neo4jOperation_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_Neo4jOperation.OuterSingleton)
	{
		Z_Registration_Info_UEnum_Neo4jOperation.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_Neo4jOperation, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("Neo4jOperation"));
	}
	return Z_Registration_Info_UEnum_Neo4jOperation.OuterSingleton;
}
template<> FANTASIA_API UEnum* StaticEnum<Neo4jOperation>()
{
	return Neo4jOperation_StaticEnum();
}
struct Z_Construct_UEnum_FANTASIA_Neo4jOperation_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
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
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "Neo4jOperation::SINGLE_REQUEST", (int64)Neo4jOperation::SINGLE_REQUEST },
		{ "Neo4jOperation::BEGIN_TRANSACTION", (int64)Neo4jOperation::BEGIN_TRANSACTION },
		{ "Neo4jOperation::COMMIT_TRANSACTION", (int64)Neo4jOperation::COMMIT_TRANSACTION },
		{ "Neo4jOperation::ROLLBACK_TRANSACTION", (int64)Neo4jOperation::ROLLBACK_TRANSACTION },
		{ "Neo4jOperation::ADD_TO_TRANSACTION", (int64)Neo4jOperation::ADD_TO_TRANSACTION },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_Neo4jOperation_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	"Neo4jOperation",
	"Neo4jOperation",
	Z_Construct_UEnum_FANTASIA_Neo4jOperation_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_Neo4jOperation_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_Neo4jOperation_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_Neo4jOperation_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FANTASIA_Neo4jOperation()
{
	if (!Z_Registration_Info_UEnum_Neo4jOperation.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_Neo4jOperation.InnerSingleton, Z_Construct_UEnum_FANTASIA_Neo4jOperation_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_Neo4jOperation.InnerSingleton;
}
// End Enum Neo4jOperation

// Begin ScriptStruct FTTSTimedStruct
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TTSTimedStruct;
class UScriptStruct* FTTSTimedStruct::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TTSTimedStruct.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TTSTimedStruct.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTTSTimedStruct, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("TTSTimedStruct"));
	}
	return Z_Registration_Info_UScriptStruct_TTSTimedStruct.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FTTSTimedStruct>()
{
	return FTTSTimedStruct::StaticStruct();
}
struct Z_Construct_UScriptStruct_FTTSTimedStruct_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_time_MetaData[] = {
		{ "Category", "TTSTimedStruct" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_data_MetaData[] = {
		{ "Category", "TTSTimedStruct" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_time;
	static const UECodeGen_Private::FStrPropertyParams NewProp_data;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTTSTimedStruct>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_time = { "time", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTTSTimedStruct, time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_time_MetaData), NewProp_time_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_data = { "data", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTTSTimedStruct, data), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_data_MetaData), NewProp_data_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewProp_data,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"TTSTimedStruct",
	Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::PropPointers),
	sizeof(FTTSTimedStruct),
	alignof(FTTSTimedStruct),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTTSTimedStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TTSTimedStruct.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TTSTimedStruct.InnerSingleton, Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_TTSTimedStruct.InnerSingleton;
}
// End ScriptStruct FTTSTimedStruct

// Begin ScriptStruct FTTSData
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TTSData;
class UScriptStruct* FTTSData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TTSData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TTSData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTTSData, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("TTSData"));
	}
	return Z_Registration_Info_UScriptStruct_TTSData.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FTTSData>()
{
	return FTTSData::StaticStruct();
}
struct Z_Construct_UScriptStruct_FTTSData_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTTSData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTTSData_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"TTSData",
	nullptr,
	0,
	sizeof(FTTSData),
	alignof(FTTSData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTTSData_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTTSData_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTTSData()
{
	if (!Z_Registration_Info_UScriptStruct_TTSData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TTSData.InnerSingleton, Z_Construct_UScriptStruct_FTTSData_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_TTSData.InnerSingleton;
}
// End ScriptStruct FTTSData

// Begin Delegate FSynthesizedEvent
struct Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventSynthesizedEvent_Parms
	{
		FString id;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventSynthesizedEvent_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::NewProp_id,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "SynthesizedEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::_Script_FANTASIA_eventSynthesizedEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::_Script_FANTASIA_eventSynthesizedEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FSynthesizedEvent_DelegateWrapper(const FMulticastScriptDelegate& SynthesizedEvent, const FString& id)
{
	struct _Script_FANTASIA_eventSynthesizedEvent_Parms
	{
		FString id;
	};
	_Script_FANTASIA_eventSynthesizedEvent_Parms Parms;
	Parms.id=id;
	SynthesizedEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FSynthesizedEvent

// Begin Delegate FSynthesizedInternalEvent
struct Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventSynthesizedInternalEvent_Parms
	{
		FTTSData response;
		FString id;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_response;
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::NewProp_response = { "response", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventSynthesizedInternalEvent_Parms, response), Z_Construct_UScriptStruct_FTTSData, METADATA_PARAMS(0, nullptr) }; // 983459605
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventSynthesizedInternalEvent_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::NewProp_response,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::NewProp_id,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "SynthesizedInternalEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::_Script_FANTASIA_eventSynthesizedInternalEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::_Script_FANTASIA_eventSynthesizedInternalEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FSynthesizedInternalEvent_DelegateWrapper(const FMulticastScriptDelegate& SynthesizedInternalEvent, FTTSData response, const FString& id)
{
	struct _Script_FANTASIA_eventSynthesizedInternalEvent_Parms
	{
		FTTSData response;
		FString id;
	};
	_Script_FANTASIA_eventSynthesizedInternalEvent_Parms Parms;
	Parms.response=response;
	Parms.id=id;
	SynthesizedInternalEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FSynthesizedInternalEvent

// Begin ScriptStruct FNeo4jResponse
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_Neo4jResponse;
class UScriptStruct* FNeo4jResponse::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_Neo4jResponse.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_Neo4jResponse.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNeo4jResponse, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("Neo4jResponse"));
	}
	return Z_Registration_Info_UScriptStruct_Neo4jResponse.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FNeo4jResponse>()
{
	return FNeo4jResponse::StaticStruct();
}
struct Z_Construct_UScriptStruct_FNeo4jResponse_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_transactionID_MetaData[] = {
		{ "Category", "Neo4jResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_headers_MetaData[] = {
		{ "Category", "Neo4jResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_rows_MetaData[] = {
		{ "Category", "Neo4jResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_transactionID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_headers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_headers;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_rows_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_rows;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNeo4jResponse>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_transactionID = { "transactionID", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNeo4jResponse, transactionID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_transactionID_MetaData), NewProp_transactionID_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers_Inner = { "headers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers = { "headers", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNeo4jResponse, headers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_headers_MetaData), NewProp_headers_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows_Inner = { "rows", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UNeo4jResultRow_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows = { "rows", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNeo4jResponse, rows), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_rows_MetaData), NewProp_rows_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FNeo4jResponse_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_transactionID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_headers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewProp_rows,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FNeo4jResponse_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"Neo4jResponse",
	Z_Construct_UScriptStruct_FNeo4jResponse_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::PropPointers),
	sizeof(FNeo4jResponse),
	alignof(FNeo4jResponse),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNeo4jResponse_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FNeo4jResponse_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FNeo4jResponse()
{
	if (!Z_Registration_Info_UScriptStruct_Neo4jResponse.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_Neo4jResponse.InnerSingleton, Z_Construct_UScriptStruct_FNeo4jResponse_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_Neo4jResponse.InnerSingleton;
}
// End ScriptStruct FNeo4jResponse

// Begin ScriptStruct FNLUResponse
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_NLUResponse;
class UScriptStruct* FNLUResponse::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_NLUResponse.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_NLUResponse.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNLUResponse, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("NLUResponse"));
	}
	return Z_Registration_Info_UScriptStruct_NLUResponse.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FNLUResponse>()
{
	return FNLUResponse::StaticStruct();
}
struct Z_Construct_UScriptStruct_FNLUResponse_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_query_MetaData[] = {
		{ "Category", "NLUResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_entities_MetaData[] = {
		{ "Category", "NLUResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_intents_MetaData[] = {
		{ "Category", "NLUResponse" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_query;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_entities_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_entities;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_intents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_intents;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNLUResponse>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_query = { "query", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNLUResponse, query), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_query_MetaData), NewProp_query_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities_Inner = { "entities", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UNLUEntity_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities = { "entities", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNLUResponse, entities), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_entities_MetaData), NewProp_entities_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_intents_Inner = { "intents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UNLUIntent_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_intents = { "intents", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNLUResponse, intents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_intents_MetaData), NewProp_intents_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FNLUResponse_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_query,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_entities,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_intents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNLUResponse_Statics::NewProp_intents,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FNLUResponse_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"NLUResponse",
	Z_Construct_UScriptStruct_FNLUResponse_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::PropPointers),
	sizeof(FNLUResponse),
	alignof(FNLUResponse),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNLUResponse_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FNLUResponse_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FNLUResponse()
{
	if (!Z_Registration_Info_UScriptStruct_NLUResponse.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_NLUResponse.InnerSingleton, Z_Construct_UScriptStruct_FNLUResponse_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_NLUResponse.InnerSingleton;
}
// End ScriptStruct FNLUResponse

// Begin Class UNLUIntent
void UNLUIntent::StaticRegisterNativesUNLUIntent()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNLUIntent);
UClass* Z_Construct_UClass_UNLUIntent_NoRegister()
{
	return UNLUIntent::StaticClass();
}
struct Z_Construct_UClass_UNLUIntent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Azure" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_intent_MetaData[] = {
		{ "Category", "NLUIntent" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_confidence_MetaData[] = {
		{ "Category", "NLUIntent" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_intent;
	static const UECodeGen_Private::FStrPropertyParams NewProp_confidence;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLUIntent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNLUIntent_Statics::NewProp_intent = { "intent", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUIntent, intent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_intent_MetaData), NewProp_intent_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNLUIntent_Statics::NewProp_confidence = { "confidence", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUIntent, confidence), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_confidence_MetaData), NewProp_confidence_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNLUIntent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUIntent_Statics::NewProp_intent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUIntent_Statics::NewProp_confidence,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNLUIntent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNLUIntent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNLUIntent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNLUIntent_Statics::ClassParams = {
	&UNLUIntent::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UNLUIntent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UNLUIntent_Statics::PropPointers),
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNLUIntent_Statics::Class_MetaDataParams), Z_Construct_UClass_UNLUIntent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNLUIntent()
{
	if (!Z_Registration_Info_UClass_UNLUIntent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLUIntent.OuterSingleton, Z_Construct_UClass_UNLUIntent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLUIntent.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UNLUIntent>()
{
	return UNLUIntent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNLUIntent);
UNLUIntent::~UNLUIntent() {}
// End Class UNLUIntent

// Begin Class UNLUEntity
void UNLUEntity::StaticRegisterNativesUNLUEntity()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNLUEntity);
UClass* Z_Construct_UClass_UNLUEntity_NoRegister()
{
	return UNLUEntity::StaticClass();
}
struct Z_Construct_UClass_UNLUEntity_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Azure" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_entity_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_type_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_startIndex_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_endIndex_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_score_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_childName_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_children_MetaData[] = {
		{ "Category", "NLUEntity" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_entity;
	static const UECodeGen_Private::FStrPropertyParams NewProp_type;
	static const UECodeGen_Private::FBytePropertyParams NewProp_startIndex;
	static const UECodeGen_Private::FBytePropertyParams NewProp_endIndex;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_score;
	static const UECodeGen_Private::FStrPropertyParams NewProp_childName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_children_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_children;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNLUEntity>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_entity = { "entity", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUEntity, entity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_entity_MetaData), NewProp_entity_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_type = { "type", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUEntity, type), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_type_MetaData), NewProp_type_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_startIndex = { "startIndex", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUEntity, startIndex), nullptr, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_startIndex_MetaData), NewProp_startIndex_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_endIndex = { "endIndex", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUEntity, endIndex), nullptr, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_endIndex_MetaData), NewProp_endIndex_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_score = { "score", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUEntity, score), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_score_MetaData), NewProp_score_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_childName = { "childName", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUEntity, childName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_childName_MetaData), NewProp_childName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_children_Inner = { "children", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UNLUEntity_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UNLUEntity_Statics::NewProp_children = { "children", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNLUEntity, children), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_children_MetaData), NewProp_children_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNLUEntity_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_entity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_startIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_endIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_score,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_childName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_children_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNLUEntity_Statics::NewProp_children,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNLUEntity_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNLUEntity_Statics::ClassParams = {
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNLUEntity_Statics::Class_MetaDataParams), Z_Construct_UClass_UNLUEntity_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNLUEntity()
{
	if (!Z_Registration_Info_UClass_UNLUEntity.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNLUEntity.OuterSingleton, Z_Construct_UClass_UNLUEntity_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNLUEntity.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UNLUEntity>()
{
	return UNLUEntity::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNLUEntity);
UNLUEntity::~UNLUEntity() {}
// End Class UNLUEntity

// Begin Class UNeo4jResultRow
void UNeo4jResultRow::StaticRegisterNativesUNeo4jResultRow()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNeo4jResultRow);
UClass* Z_Construct_UClass_UNeo4jResultRow_NoRegister()
{
	return UNeo4jResultRow::StaticClass();
}
struct Z_Construct_UClass_UNeo4jResultRow_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_cells_MetaData[] = {
		{ "Category", "Neo4jResultRow" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_cells_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_cells_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_cells;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultRow>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_ValueProp = { "cells", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UClass_UNeo4jResultCell_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_Key_KeyProp = { "cells_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells = { "cells", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jResultRow, cells), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_cells_MetaData), NewProp_cells_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jResultRow_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultRow_Statics::NewProp_cells,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultRow_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNeo4jResultRow_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultRow_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultRow_Statics::ClassParams = {
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultRow_Statics::Class_MetaDataParams), Z_Construct_UClass_UNeo4jResultRow_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNeo4jResultRow()
{
	if (!Z_Registration_Info_UClass_UNeo4jResultRow.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNeo4jResultRow.OuterSingleton, Z_Construct_UClass_UNeo4jResultRow_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNeo4jResultRow.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UNeo4jResultRow>()
{
	return UNeo4jResultRow::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultRow);
UNeo4jResultRow::~UNeo4jResultRow() {}
// End Class UNeo4jResultRow

// Begin Class UNeo4jResultCell
void UNeo4jResultCell::StaticRegisterNativesUNeo4jResultCell()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNeo4jResultCell);
UClass* Z_Construct_UClass_UNeo4jResultCell_NoRegister()
{
	return UNeo4jResultCell::StaticClass();
}
struct Z_Construct_UClass_UNeo4jResultCell_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultCell>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UNeo4jResultCell_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCell_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultCell_Statics::ClassParams = {
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCell_Statics::Class_MetaDataParams), Z_Construct_UClass_UNeo4jResultCell_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNeo4jResultCell()
{
	if (!Z_Registration_Info_UClass_UNeo4jResultCell.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNeo4jResultCell.OuterSingleton, Z_Construct_UClass_UNeo4jResultCell_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNeo4jResultCell.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UNeo4jResultCell>()
{
	return UNeo4jResultCell::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultCell);
UNeo4jResultCell::~UNeo4jResultCell() {}
// End Class UNeo4jResultCell

// Begin Class UNeo4jResultCellNode
void UNeo4jResultCellNode::StaticRegisterNativesUNeo4jResultCellNode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNeo4jResultCellNode);
UClass* Z_Construct_UClass_UNeo4jResultCellNode_NoRegister()
{
	return UNeo4jResultCellNode::StaticClass();
}
struct Z_Construct_UClass_UNeo4jResultCellNode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_labels_MetaData[] = {
		{ "Category", "Neo4jResultCellNode" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_id_MetaData[] = {
		{ "Category", "Neo4jResultCellNode" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_properties_MetaData[] = {
		{ "Category", "Neo4jResultCellNode" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_labels_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_labels;
	static const UECodeGen_Private::FIntPropertyParams NewProp_id;
	static const UECodeGen_Private::FStrPropertyParams NewProp_properties_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_properties_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_properties;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultCellNode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels_Inner = { "labels", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels = { "labels", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jResultCellNode, labels), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_labels_MetaData), NewProp_labels_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jResultCellNode, id), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_id_MetaData), NewProp_id_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_ValueProp = { "properties", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_Key_KeyProp = { "properties_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties = { "properties", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jResultCellNode, properties), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_properties_MetaData), NewProp_properties_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jResultCellNode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_labels,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellNode_Statics::NewProp_properties,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellNode_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNeo4jResultCellNode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNeo4jResultCell,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellNode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultCellNode_Statics::ClassParams = {
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellNode_Statics::Class_MetaDataParams), Z_Construct_UClass_UNeo4jResultCellNode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNeo4jResultCellNode()
{
	if (!Z_Registration_Info_UClass_UNeo4jResultCellNode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNeo4jResultCellNode.OuterSingleton, Z_Construct_UClass_UNeo4jResultCellNode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNeo4jResultCellNode.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UNeo4jResultCellNode>()
{
	return UNeo4jResultCellNode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultCellNode);
UNeo4jResultCellNode::~UNeo4jResultCellNode() {}
// End Class UNeo4jResultCellNode

// Begin Class UNeo4jResultCellRelationship
void UNeo4jResultCellRelationship::StaticRegisterNativesUNeo4jResultCellRelationship()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNeo4jResultCellRelationship);
UClass* Z_Construct_UClass_UNeo4jResultCellRelationship_NoRegister()
{
	return UNeo4jResultCellRelationship::StaticClass();
}
struct Z_Construct_UClass_UNeo4jResultCellRelationship_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_label_MetaData[] = {
		{ "Category", "Neo4jResultCellRelationship" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_id_MetaData[] = {
		{ "Category", "Neo4jResultCellRelationship" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_properties_MetaData[] = {
		{ "Category", "Neo4jResultCellRelationship" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_label;
	static const UECodeGen_Private::FIntPropertyParams NewProp_id;
	static const UECodeGen_Private::FStrPropertyParams NewProp_properties_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_properties_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_properties;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultCellRelationship>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_label = { "label", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jResultCellRelationship, label), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_label_MetaData), NewProp_label_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jResultCellRelationship, id), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_id_MetaData), NewProp_id_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_ValueProp = { "properties", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_Key_KeyProp = { "properties_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties = { "properties", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jResultCellRelationship, properties), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_properties_MetaData), NewProp_properties_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_label,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::NewProp_properties,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNeo4jResultCell,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::ClassParams = {
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::Class_MetaDataParams), Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNeo4jResultCellRelationship()
{
	if (!Z_Registration_Info_UClass_UNeo4jResultCellRelationship.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNeo4jResultCellRelationship.OuterSingleton, Z_Construct_UClass_UNeo4jResultCellRelationship_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNeo4jResultCellRelationship.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UNeo4jResultCellRelationship>()
{
	return UNeo4jResultCellRelationship::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultCellRelationship);
UNeo4jResultCellRelationship::~UNeo4jResultCellRelationship() {}
// End Class UNeo4jResultCellRelationship

// Begin Class UNeo4jResultCellSimple
void UNeo4jResultCellSimple::StaticRegisterNativesUNeo4jResultCellSimple()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNeo4jResultCellSimple);
UClass* Z_Construct_UClass_UNeo4jResultCellSimple_NoRegister()
{
	return UNeo4jResultCellSimple::StaticClass();
}
struct Z_Construct_UClass_UNeo4jResultCellSimple_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "FANTASIATypes.h" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_value_MetaData[] = {
		{ "Category", "Neo4jResultCellSimple" },
		{ "ModuleRelativePath", "Public/FANTASIATypes.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jResultCellSimple>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jResultCellSimple_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jResultCellSimple, value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_value_MetaData), NewProp_value_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jResultCellSimple_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jResultCellSimple_Statics::NewProp_value,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellSimple_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UNeo4jResultCellSimple_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UNeo4jResultCell,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellSimple_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jResultCellSimple_Statics::ClassParams = {
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jResultCellSimple_Statics::Class_MetaDataParams), Z_Construct_UClass_UNeo4jResultCellSimple_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNeo4jResultCellSimple()
{
	if (!Z_Registration_Info_UClass_UNeo4jResultCellSimple.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNeo4jResultCellSimple.OuterSingleton, Z_Construct_UClass_UNeo4jResultCellSimple_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNeo4jResultCellSimple.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UNeo4jResultCellSimple>()
{
	return UNeo4jResultCellSimple::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jResultCellSimple);
UNeo4jResultCellSimple::~UNeo4jResultCellSimple() {}
// End Class UNeo4jResultCellSimple

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ ChatGPTRoleType_StaticEnum, TEXT("ChatGPTRoleType"), &Z_Registration_Info_UEnum_ChatGPTRoleType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1359525058U) },
		{ InfluenceNodeType_StaticEnum, TEXT("InfluenceNodeType"), &Z_Registration_Info_UEnum_InfluenceNodeType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3896454705U) },
		{ BayesianNodeType_StaticEnum, TEXT("BayesianNodeType"), &Z_Registration_Info_UEnum_BayesianNodeType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2887683997U) },
		{ TTSVoiceType_StaticEnum, TEXT("TTSVoiceType"), &Z_Registration_Info_UEnum_TTSVoiceType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 851191106U) },
		{ Neo4jOperation_StaticEnum, TEXT("Neo4jOperation"), &Z_Registration_Info_UEnum_Neo4jOperation, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 652439313U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FChatTurn::StaticStruct, Z_Construct_UScriptStruct_FChatTurn_Statics::NewStructOps, TEXT("ChatTurn"), &Z_Registration_Info_UScriptStruct_ChatTurn, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FChatTurn), 2042086127U) },
		{ FTTSTimedStruct::StaticStruct, Z_Construct_UScriptStruct_FTTSTimedStruct_Statics::NewStructOps, TEXT("TTSTimedStruct"), &Z_Registration_Info_UScriptStruct_TTSTimedStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTTSTimedStruct), 3581234331U) },
		{ FTTSData::StaticStruct, Z_Construct_UScriptStruct_FTTSData_Statics::NewStructOps, TEXT("TTSData"), &Z_Registration_Info_UScriptStruct_TTSData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTTSData), 983459605U) },
		{ FNeo4jResponse::StaticStruct, Z_Construct_UScriptStruct_FNeo4jResponse_Statics::NewStructOps, TEXT("Neo4jResponse"), &Z_Registration_Info_UScriptStruct_Neo4jResponse, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNeo4jResponse), 26987846U) },
		{ FNLUResponse::StaticStruct, Z_Construct_UScriptStruct_FNLUResponse_Statics::NewStructOps, TEXT("NLUResponse"), &Z_Registration_Info_UScriptStruct_NLUResponse, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNLUResponse), 667433752U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNLUIntent, UNLUIntent::StaticClass, TEXT("UNLUIntent"), &Z_Registration_Info_UClass_UNLUIntent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLUIntent), 980026208U) },
		{ Z_Construct_UClass_UNLUEntity, UNLUEntity::StaticClass, TEXT("UNLUEntity"), &Z_Registration_Info_UClass_UNLUEntity, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNLUEntity), 937203255U) },
		{ Z_Construct_UClass_UNeo4jResultRow, UNeo4jResultRow::StaticClass, TEXT("UNeo4jResultRow"), &Z_Registration_Info_UClass_UNeo4jResultRow, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNeo4jResultRow), 3460069060U) },
		{ Z_Construct_UClass_UNeo4jResultCell, UNeo4jResultCell::StaticClass, TEXT("UNeo4jResultCell"), &Z_Registration_Info_UClass_UNeo4jResultCell, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNeo4jResultCell), 3803135964U) },
		{ Z_Construct_UClass_UNeo4jResultCellNode, UNeo4jResultCellNode::StaticClass, TEXT("UNeo4jResultCellNode"), &Z_Registration_Info_UClass_UNeo4jResultCellNode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNeo4jResultCellNode), 38539807U) },
		{ Z_Construct_UClass_UNeo4jResultCellRelationship, UNeo4jResultCellRelationship::StaticClass, TEXT("UNeo4jResultCellRelationship"), &Z_Registration_Info_UClass_UNeo4jResultCellRelationship, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNeo4jResultCellRelationship), 4008198376U) },
		{ Z_Construct_UClass_UNeo4jResultCellSimple, UNeo4jResultCellSimple::StaticClass, TEXT("UNeo4jResultCellSimple"), &Z_Registration_Info_UClass_UNeo4jResultCellSimple, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNeo4jResultCellSimple), 3829507120U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_3876249590(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_FANTASIATypes_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
