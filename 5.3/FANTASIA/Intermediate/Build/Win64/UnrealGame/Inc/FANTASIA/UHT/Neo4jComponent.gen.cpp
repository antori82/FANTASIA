// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "../../../../../../Source/FANTASIA/Public/Neo4jComponent.h"
#include "../../../../../../Source/FANTASIA/Public/FANTASIATypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNeo4jComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jComponent();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jComponent_NoRegister();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_Neo4jOperation();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FNeo4jResponse();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms
		{
			FNeo4jResponse Neo4jResponse;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_Neo4jResponse;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::NewProp_Neo4jResponse = { "Neo4jResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms, Neo4jResponse), Z_Construct_UScriptStruct_FNeo4jResponse, METADATA_PARAMS(0, nullptr) }; // 2632441028
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::NewProp_Neo4jResponse,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingNeo4jResponseEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms) < MAX_uint16);
	UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FIncomingNeo4jResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingNeo4jResponseEvent, FNeo4jResponse Neo4jResponse)
{
	struct _Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms
	{
		FNeo4jResponse Neo4jResponse;
	};
	_Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms Parms;
	Parms.Neo4jResponse=Neo4jResponse;
	IncomingNeo4jResponseEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
	DEFINE_FUNCTION(UNeo4jComponent::execsubmitQuery)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_query);
		P_GET_ENUM(Neo4jOperation,Z_Param_operation);
		P_GET_PROPERTY(FStrProperty,Z_Param_transactionID);
		P_GET_TMAP(FString,FString,Z_Param_parameters);
		P_GET_PROPERTY(FStrProperty,Z_Param_database);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->submitQuery(Z_Param_query,Neo4jOperation(Z_Param_operation),Z_Param_transactionID,Z_Param_parameters,Z_Param_database);
		P_NATIVE_END;
	}
	void UNeo4jComponent::StaticRegisterNativesUNeo4jComponent()
	{
		UClass* Class = UNeo4jComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "submitQuery", &UNeo4jComponent::execsubmitQuery },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics
	{
		struct Neo4jComponent_eventsubmitQuery_Parms
		{
			FString query;
			Neo4jOperation operation;
			FString transactionID;
			TMap<FString,FString> parameters;
			FString database;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_query;
		static const UECodeGen_Private::FBytePropertyParams NewProp_operation_Underlying;
		static const UECodeGen_Private::FEnumPropertyParams NewProp_operation;
		static const UECodeGen_Private::FStrPropertyParams NewProp_transactionID;
		static const UECodeGen_Private::FStrPropertyParams NewProp_parameters_ValueProp;
		static const UECodeGen_Private::FStrPropertyParams NewProp_parameters_Key_KeyProp;
		static const UECodeGen_Private::FMapPropertyParams NewProp_parameters;
		static const UECodeGen_Private::FStrPropertyParams NewProp_database;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_query = { "query", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, query), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_operation_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_operation = { "operation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, operation), Z_Construct_UEnum_FANTASIA_Neo4jOperation, METADATA_PARAMS(0, nullptr) }; // 2289837966
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_transactionID = { "transactionID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, transactionID), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters_ValueProp = { "parameters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters_Key_KeyProp = { "parameters_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters = { "parameters", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, parameters), EMapPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_database = { "database", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, database), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_query,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_operation_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_operation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_transactionID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_database,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "Neo4j" },
		{ "DisplayName", "Submit query" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNeo4jComponent, nullptr, "submitQuery", nullptr, nullptr, Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::PropPointers), sizeof(Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::Neo4jComponent_eventsubmitQuery_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::Function_MetaDataParams), Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::Neo4jComponent_eventsubmitQuery_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UNeo4jComponent_submitQuery()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNeo4jComponent);
	UClass* Z_Construct_UClass_UNeo4jComponent_NoRegister()
	{
		return UNeo4jComponent::StaticClass();
	}
	struct Z_Construct_UClass_UNeo4jComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_endpoint_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_endpoint;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_port_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_port;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_user_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_user;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_password_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_password;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IncomingResponse_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingResponse;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_response_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_response;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_useV4_MetaData[];
#endif
		static void NewProp_useV4_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_useV4;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNeo4jComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UNeo4jComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UNeo4jComponent_submitQuery, "submitQuery" }, // 190776651
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "Neo4jComponent.h" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint = { "endpoint", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jComponent, endpoint), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint_MetaData), Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port = { "port", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jComponent, port), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port_MetaData), Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user = { "user", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jComponent, user), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user_MetaData), Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password = { "password", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jComponent, password), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password_MetaData), Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse = { "IncomingResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jComponent, IncomingResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse_MetaData), Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse_MetaData) }; // 3864067283
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response_MetaData[] = {
		{ "Category", "Neo4jComponent" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response = { "response", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNeo4jComponent, response), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response_MetaData), Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_useV4_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	void Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_useV4_SetBit(void* Obj)
	{
		((UNeo4jComponent*)Obj)->useV4 = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_useV4 = { "useV4", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UNeo4jComponent), &Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_useV4_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_useV4_MetaData), Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_useV4_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_useV4,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNeo4jComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jComponent_Statics::ClassParams = {
		&UNeo4jComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UNeo4jComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::PropPointers),
		0,
		0x00A000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UNeo4jComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UNeo4jComponent()
	{
		if (!Z_Registration_Info_UClass_UNeo4jComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNeo4jComponent.OuterSingleton, Z_Construct_UClass_UNeo4jComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UNeo4jComponent.OuterSingleton;
	}
	template<> FANTASIA_API UClass* StaticClass<UNeo4jComponent>()
	{
		return UNeo4jComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jComponent);
	UNeo4jComponent::~UNeo4jComponent() {}
	struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UNeo4jComponent, UNeo4jComponent::StaticClass, TEXT("UNeo4jComponent"), &Z_Registration_Info_UClass_UNeo4jComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNeo4jComponent), 2651347883U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_4064746380(TEXT("/Script/FANTASIA"),
		Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_Neo4jComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
