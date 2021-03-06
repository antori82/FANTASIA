// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/Neo4jComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNeo4jComponent() {}
// Cross Module References
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FNeo4jResponse();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jComponent_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UNeo4jComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_Neo4jOperation();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms
		{
			FNeo4jResponse Neo4jResponse;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Neo4jResponse;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::NewProp_Neo4jResponse = { "Neo4jResponse", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms, Neo4jResponse), Z_Construct_UScriptStruct_FNeo4jResponse, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::NewProp_Neo4jResponse,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingNeo4jResponseEvent__DelegateSignature", nullptr, nullptr, sizeof(_Script_FANTASIA_eventIncomingNeo4jResponseEvent_Parms), Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UNeo4jComponent::execsubmitQuery)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_query);
		P_GET_ENUM(Neo4jOperation,Z_Param_operation);
		P_GET_PROPERTY(FStrProperty,Z_Param_transactionID);
		P_GET_TMAP(FString,FString,Z_Param_parameters);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->submitQuery(Z_Param_query,Neo4jOperation(Z_Param_operation),Z_Param_transactionID,Z_Param_parameters);
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
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_query;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_operation_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_operation;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_transactionID;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_parameters_ValueProp;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_parameters_Key_KeyProp;
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_parameters;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_query = { "query", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, query), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_operation_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_operation = { "operation", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, operation), Z_Construct_UEnum_FANTASIA_Neo4jOperation, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_transactionID = { "transactionID", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, transactionID), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters_ValueProp = { "parameters", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters_Key_KeyProp = { "parameters_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters = { "parameters", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(Neo4jComponent_eventsubmitQuery_Parms, parameters), EMapPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_query,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_operation_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_operation,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_transactionID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::NewProp_parameters,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "Neo4j" },
		{ "DisplayName", "Submit query" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UNeo4jComponent, nullptr, "submitQuery", nullptr, nullptr, sizeof(Neo4jComponent_eventsubmitQuery_Parms), Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UNeo4jComponent_submitQuery()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UNeo4jComponent_submitQuery_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UNeo4jComponent_NoRegister()
	{
		return UNeo4jComponent::StaticClass();
	}
	struct Z_Construct_UClass_UNeo4jComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_endpoint_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_endpoint;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_port_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_port;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_user_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_user;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_password_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_password;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IncomingResponse_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingResponse;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_response_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_response;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UNeo4jComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UNeo4jComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UNeo4jComponent_submitQuery, "submitQuery" }, // 1448447233
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Neo4j" },
		{ "IncludePath", "Neo4jComponent.h" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint = { "endpoint", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jComponent, endpoint), METADATA_PARAMS(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port = { "port", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jComponent, port), METADATA_PARAMS(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user = { "user", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jComponent, user), METADATA_PARAMS(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password = { "password", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jComponent, password), METADATA_PARAMS(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse = { "IncomingResponse", nullptr, (EPropertyFlags)0x0010100010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jComponent, IncomingResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response_MetaData[] = {
		{ "Category", "Neo4jComponent" },
		{ "ModuleRelativePath", "Public/Neo4jComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response = { "response", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UNeo4jComponent, response), METADATA_PARAMS(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNeo4jComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_endpoint,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_port,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_user,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_password,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_IncomingResponse,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNeo4jComponent_Statics::NewProp_response,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UNeo4jComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNeo4jComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UNeo4jComponent_Statics::ClassParams = {
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
		METADATA_PARAMS(Z_Construct_UClass_UNeo4jComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UNeo4jComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UNeo4jComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UNeo4jComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UNeo4jComponent, 4276322143);
	template<> FANTASIA_API UClass* StaticClass<UNeo4jComponent>()
	{
		return UNeo4jComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UNeo4jComponent(Z_Construct_UClass_UNeo4jComponent, &UNeo4jComponent::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UNeo4jComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UNeo4jComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
