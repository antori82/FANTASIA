// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/LangGraphComponent.h"
#include "FANTASIA/Public/FANTASIATypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLangGraphComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_ULangGraphComponent();
FANTASIA_API UClass* Z_Construct_UClass_ULangGraphComponent_NoRegister();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_GPTRoleType();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FChatTurn();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Delegate FIncomingLangGraphThreadCreateResponseEvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingLangGraphThreadCreateResponseEvent_Parms
	{
		FString threadID;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_threadID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::NewProp_threadID = { "threadID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingLangGraphThreadCreateResponseEvent_Parms, threadID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::NewProp_threadID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingLangGraphThreadCreateResponseEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingLangGraphThreadCreateResponseEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingLangGraphThreadCreateResponseEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingLangGraphThreadCreateResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphThreadCreateResponseEvent, const FString& threadID)
{
	struct _Script_FANTASIA_eventIncomingLangGraphThreadCreateResponseEvent_Parms
	{
		FString threadID;
	};
	_Script_FANTASIA_eventIncomingLangGraphThreadCreateResponseEvent_Parms Parms;
	Parms.threadID=threadID;
	IncomingLangGraphThreadCreateResponseEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingLangGraphThreadCreateResponseEvent

// Begin Delegate FIncomingLangGraphResponseEvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingLangGraphResponseEvent_Parms
	{
		FString LangGraphResponse;
		GPTRoleType role;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_LangGraphResponse;
	static const UECodeGen_Private::FBytePropertyParams NewProp_role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_role;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::NewProp_LangGraphResponse = { "LangGraphResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingLangGraphResponseEvent_Parms, LangGraphResponse), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::NewProp_role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::NewProp_role = { "role", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingLangGraphResponseEvent_Parms, role), Z_Construct_UEnum_FANTASIA_GPTRoleType, METADATA_PARAMS(0, nullptr) }; // 1459499313
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::NewProp_LangGraphResponse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::NewProp_role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::NewProp_role,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingLangGraphResponseEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingLangGraphResponseEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingLangGraphResponseEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingLangGraphResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphResponseEvent, const FString& LangGraphResponse, GPTRoleType role)
{
	struct _Script_FANTASIA_eventIncomingLangGraphResponseEvent_Parms
	{
		FString LangGraphResponse;
		GPTRoleType role;
	};
	_Script_FANTASIA_eventIncomingLangGraphResponseEvent_Parms Parms;
	Parms.LangGraphResponse=LangGraphResponse;
	Parms.role=role;
	IncomingLangGraphResponseEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingLangGraphResponseEvent

// Begin Delegate FIncomingLangGraphStreamResponseEvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms
	{
		FString LangGraphResponse;
		GPTRoleType role;
		bool endStream;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_LangGraphResponse;
	static const UECodeGen_Private::FBytePropertyParams NewProp_role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_role;
	static void NewProp_endStream_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_endStream;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_LangGraphResponse = { "LangGraphResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms, LangGraphResponse), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_role = { "role", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms, role), Z_Construct_UEnum_FANTASIA_GPTRoleType, METADATA_PARAMS(0, nullptr) }; // 1459499313
void Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_endStream_SetBit(void* Obj)
{
	((_Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms*)Obj)->endStream = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_endStream = { "endStream", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms), &Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_endStream_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_LangGraphResponse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_role,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::NewProp_endStream,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingLangGraphStreamResponseEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingLangGraphStreamResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphStreamResponseEvent, const FString& LangGraphResponse, GPTRoleType role, bool endStream)
{
	struct _Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms
	{
		FString LangGraphResponse;
		GPTRoleType role;
		bool endStream;
	};
	_Script_FANTASIA_eventIncomingLangGraphStreamResponseEvent_Parms Parms;
	Parms.LangGraphResponse=LangGraphResponse;
	Parms.role=role;
	Parms.endStream=endStream ? true : false;
	IncomingLangGraphStreamResponseEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingLangGraphStreamResponseEvent

// Begin Class ULangGraphComponent Function createLangGraphThread
struct Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics
{
	struct LangGraphComponent_eventcreateLangGraphThread_Parms
	{
		FString threadID;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "LangGraph" },
		{ "DisplayName", "Create LangGraph thread" },
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_threadID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::NewProp_threadID = { "threadID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LangGraphComponent_eventcreateLangGraphThread_Parms, threadID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::NewProp_threadID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULangGraphComponent, nullptr, "createLangGraphThread", nullptr, nullptr, Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::LangGraphComponent_eventcreateLangGraphThread_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::LangGraphComponent_eventcreateLangGraphThread_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULangGraphComponent::execcreateLangGraphThread)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_threadID);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->createLangGraphThread(Z_Param_threadID);
	P_NATIVE_END;
}
// End Class ULangGraphComponent Function createLangGraphThread

// Begin Class ULangGraphComponent Function deleteLangGraphThread
struct Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics
{
	struct LangGraphComponent_eventdeleteLangGraphThread_Parms
	{
		FString threadID;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "LangGraph" },
		{ "DisplayName", "Delete LangGraph thread" },
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_threadID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::NewProp_threadID = { "threadID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LangGraphComponent_eventdeleteLangGraphThread_Parms, threadID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::NewProp_threadID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULangGraphComponent, nullptr, "deleteLangGraphThread", nullptr, nullptr, Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::LangGraphComponent_eventdeleteLangGraphThread_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::LangGraphComponent_eventdeleteLangGraphThread_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULangGraphComponent::execdeleteLangGraphThread)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_threadID);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->deleteLangGraphThread(Z_Param_threadID);
	P_NATIVE_END;
}
// End Class ULangGraphComponent Function deleteLangGraphThread

// Begin Class ULangGraphComponent Function langGraphQuery
struct Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics
{
	struct LangGraphComponent_eventlangGraphQuery_Parms
	{
		TArray<FChatTurn> messages;
		FString threadID;
		FString assistantID;
		FString model;
		int32 recursionLimit;
		bool stream;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "messages" },
		{ "Category", "LangGraph" },
		{ "CPP_Default_model", "openai/gpt-4o" },
		{ "CPP_Default_recursionLimit", "10" },
		{ "CPP_Default_stream", "false" },
		{ "DisplayName", "LangGraph query" },
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_messages_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_messages;
	static const UECodeGen_Private::FStrPropertyParams NewProp_threadID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_assistantID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_model;
	static const UECodeGen_Private::FIntPropertyParams NewProp_recursionLimit;
	static void NewProp_stream_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_stream;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_messages_Inner = { "messages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FChatTurn, METADATA_PARAMS(0, nullptr) }; // 4210891163
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_messages = { "messages", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LangGraphComponent_eventlangGraphQuery_Parms, messages), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 4210891163
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_threadID = { "threadID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LangGraphComponent_eventlangGraphQuery_Parms, threadID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_assistantID = { "assistantID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LangGraphComponent_eventlangGraphQuery_Parms, assistantID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_model = { "model", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LangGraphComponent_eventlangGraphQuery_Parms, model), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_recursionLimit = { "recursionLimit", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LangGraphComponent_eventlangGraphQuery_Parms, recursionLimit), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_stream_SetBit(void* Obj)
{
	((LangGraphComponent_eventlangGraphQuery_Parms*)Obj)->stream = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_stream = { "stream", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(LangGraphComponent_eventlangGraphQuery_Parms), &Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_stream_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_messages_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_messages,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_threadID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_assistantID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_model,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_recursionLimit,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::NewProp_stream,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULangGraphComponent, nullptr, "langGraphQuery", nullptr, nullptr, Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::LangGraphComponent_eventlangGraphQuery_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::LangGraphComponent_eventlangGraphQuery_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ULangGraphComponent_langGraphQuery()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULangGraphComponent_langGraphQuery_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULangGraphComponent::execlangGraphQuery)
{
	P_GET_TARRAY(FChatTurn,Z_Param_messages);
	P_GET_PROPERTY(FStrProperty,Z_Param_threadID);
	P_GET_PROPERTY(FStrProperty,Z_Param_assistantID);
	P_GET_PROPERTY(FStrProperty,Z_Param_model);
	P_GET_PROPERTY(FIntProperty,Z_Param_recursionLimit);
	P_GET_UBOOL(Z_Param_stream);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->langGraphQuery(Z_Param_messages,Z_Param_threadID,Z_Param_assistantID,Z_Param_model,Z_Param_recursionLimit,Z_Param_stream);
	P_NATIVE_END;
}
// End Class ULangGraphComponent Function langGraphQuery

// Begin Class ULangGraphComponent
void ULangGraphComponent::StaticRegisterNativesULangGraphComponent()
{
	UClass* Class = ULangGraphComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "createLangGraphThread", &ULangGraphComponent::execcreateLangGraphThread },
		{ "deleteLangGraphThread", &ULangGraphComponent::execdeleteLangGraphThread },
		{ "langGraphQuery", &ULangGraphComponent::execlangGraphQuery },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULangGraphComponent);
UClass* Z_Construct_UClass_ULangGraphComponent_NoRegister()
{
	return ULangGraphComponent::StaticClass();
}
struct Z_Construct_UClass_ULangGraphComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "OpenAI" },
		{ "IncludePath", "LangGraphComponent.h" },
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_endpoint_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_port_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingLangGraphResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingLangGraphStreamResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LangGraphThreadCreateResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/LangGraphComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_endpoint;
	static const UECodeGen_Private::FIntPropertyParams NewProp_port;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingLangGraphResponse;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingLangGraphStreamResponse;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_LangGraphThreadCreateResponse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ULangGraphComponent_createLangGraphThread, "createLangGraphThread" }, // 1601105639
		{ &Z_Construct_UFunction_ULangGraphComponent_deleteLangGraphThread, "deleteLangGraphThread" }, // 2417441837
		{ &Z_Construct_UFunction_ULangGraphComponent_langGraphQuery, "langGraphQuery" }, // 3609268043
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULangGraphComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_endpoint = { "endpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULangGraphComponent, endpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_endpoint_MetaData), NewProp_endpoint_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_port = { "port", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULangGraphComponent, port), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_port_MetaData), NewProp_port_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_IncomingLangGraphResponse = { "IncomingLangGraphResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULangGraphComponent, IncomingLangGraphResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingLangGraphResponse_MetaData), NewProp_IncomingLangGraphResponse_MetaData) }; // 1660468719
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_IncomingLangGraphStreamResponse = { "IncomingLangGraphStreamResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULangGraphComponent, IncomingLangGraphStreamResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphStreamResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingLangGraphStreamResponse_MetaData), NewProp_IncomingLangGraphStreamResponse_MetaData) }; // 1793225715
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_LangGraphThreadCreateResponse = { "LangGraphThreadCreateResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULangGraphComponent, LangGraphThreadCreateResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingLangGraphThreadCreateResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LangGraphThreadCreateResponse_MetaData), NewProp_LangGraphThreadCreateResponse_MetaData) }; // 2992933986
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULangGraphComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_endpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_port,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_IncomingLangGraphResponse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_IncomingLangGraphStreamResponse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULangGraphComponent_Statics::NewProp_LangGraphThreadCreateResponse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULangGraphComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ULangGraphComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULangGraphComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULangGraphComponent_Statics::ClassParams = {
	&ULangGraphComponent::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ULangGraphComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ULangGraphComponent_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULangGraphComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_ULangGraphComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULangGraphComponent()
{
	if (!Z_Registration_Info_UClass_ULangGraphComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULangGraphComponent.OuterSingleton, Z_Construct_UClass_ULangGraphComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULangGraphComponent.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<ULangGraphComponent>()
{
	return ULangGraphComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULangGraphComponent);
ULangGraphComponent::~ULangGraphComponent() {}
// End Class ULangGraphComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULangGraphComponent, ULangGraphComponent::StaticClass, TEXT("ULangGraphComponent"), &Z_Registration_Info_UClass_ULangGraphComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULangGraphComponent), 2510659933U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_3076518045(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
