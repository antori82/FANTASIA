// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/AzureASRComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAzureASRComponent() {}
// Cross Module References
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
	FANTASIA_API UClass* Z_Construct_UClass_UAzureASRComponent_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UAzureASRComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventIncomingASREvent_Parms
		{
			FString message;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_message;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::NewProp_message = { "message", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingASREvent_Parms, message), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::NewProp_message,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingASREvent__DelegateSignature", nullptr, nullptr, sizeof(_Script_FANTASIA_eventIncomingASREvent_Parms), Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	DEFINE_FUNCTION(UAzureASRComponent::execAzureASRStop)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AzureASRStop();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAzureASRComponent::execAzureASRStart)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AzureASRStart();
		P_NATIVE_END;
	}
	void UAzureASRComponent::StaticRegisterNativesUAzureASRComponent()
	{
		UClass* Class = UAzureASRComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AzureASRStart", &UAzureASRComponent::execAzureASRStart },
			{ "AzureASRStop", &UAzureASRComponent::execAzureASRStop },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::Function_MetaDataParams[] = {
		{ "Category", "ASR" },
		{ "DisplayName", "ASR Start" },
		{ "Keywords", "AzureASRPlugin ASR" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureASRComponent, nullptr, "AzureASRStart", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAzureASRComponent_AzureASRStart()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::Function_MetaDataParams[] = {
		{ "Category", "ASR" },
		{ "DisplayName", "ASR Stop" },
		{ "Keywords", "AzureASRPlugin ASR" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureASRComponent, nullptr, "AzureASRStop", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAzureASRComponent_AzureASRStop()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAzureASRComponent_NoRegister()
	{
		return UAzureASRComponent::StaticClass();
	}
	struct Z_Construct_UClass_UAzureASRComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Key;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Region_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Region;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Language;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_IncomingMessage_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingMessage;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAzureASRComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAzureASRComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAzureASRComponent_AzureASRStart, "AzureASRStart" }, // 321796864
		{ &Z_Construct_UFunction_UAzureASRComponent_AzureASRStop, "AzureASRStop" }, // 2542484576
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureASRComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Azure" },
		{ "IncludePath", "AzureASRComponent.h" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Key_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureASRComponent, Key), METADATA_PARAMS(Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Key_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Key_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Region_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Region = { "Region", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureASRComponent, Region), METADATA_PARAMS(Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Region_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Region_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Language_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Language = { "Language", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureASRComponent, Language), METADATA_PARAMS(Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Language_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Language_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingMessage_MetaData[] = {
		{ "Category", "Speech Recognition" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingMessage = { "IncomingMessage", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureASRComponent, IncomingMessage), Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingMessage_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingMessage_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAzureASRComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Key,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Region,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Language,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingMessage,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAzureASRComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAzureASRComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAzureASRComponent_Statics::ClassParams = {
		&UAzureASRComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAzureASRComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::PropPointers),
		0,
		0x00A000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UAzureASRComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAzureASRComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAzureASRComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAzureASRComponent, 4011925783);
	template<> FANTASIA_API UClass* StaticClass<UAzureASRComponent>()
	{
		return UAzureASRComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAzureASRComponent(Z_Construct_UClass_UAzureASRComponent, &UAzureASRComponent::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UAzureASRComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAzureASRComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
