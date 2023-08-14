// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "../../../../../../Source/FANTASIA/Public/OpenAIComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOpenAIComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	FANTASIA_API UClass* Z_Construct_UClass_UOpenAIComponent();
	FANTASIA_API UClass* Z_Construct_UClass_UOpenAIComponent_NoRegister();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventIncomingGPTResponseEvent_Parms
		{
			FString GPTResponse;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_GPTResponse;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::NewProp_GPTResponse = { "GPTResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms, GPTResponse), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::NewProp_GPTResponse,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingGPTResponseEvent__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams)) };
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
	DEFINE_FUNCTION(UOpenAIComponent::execgetGPTCompletion)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_prompt);
		P_GET_TARRAY(FString,Z_Param_stopSequences);
		P_GET_PROPERTY(FStrProperty,Z_Param_apiMethod);
		P_GET_PROPERTY(FIntProperty,Z_Param_maxTokens);
		P_GET_PROPERTY(FFloatProperty,Z_Param_temperature);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->getGPTCompletion(Z_Param_prompt,Z_Param_stopSequences,Z_Param_apiMethod,Z_Param_maxTokens,Z_Param_temperature);
		P_NATIVE_END;
	}
	void UOpenAIComponent::StaticRegisterNativesUOpenAIComponent()
	{
		UClass* Class = UOpenAIComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "getGPTCompletion", &UOpenAIComponent::execgetGPTCompletion },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics
	{
		struct OpenAIComponent_eventgetGPTCompletion_Parms
		{
			FString prompt;
			TArray<FString> stopSequences;
			FString apiMethod;
			int32 maxTokens;
			float temperature;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_prompt;
		static const UECodeGen_Private::FStrPropertyParams NewProp_stopSequences_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_stopSequences;
		static const UECodeGen_Private::FStrPropertyParams NewProp_apiMethod;
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_maxTokens;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_temperature;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_prompt = { "prompt", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, prompt), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_stopSequences_Inner = { "stopSequences", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_stopSequences = { "stopSequences", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, stopSequences), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_apiMethod = { "apiMethod", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, apiMethod), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_maxTokens = { "maxTokens", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, maxTokens), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_temperature = { "temperature", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, temperature), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_prompt,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_stopSequences_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_stopSequences,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_apiMethod,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_maxTokens,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_temperature,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "stopSequences" },
		{ "Category", "GPT" },
		{ "CPP_Default_apiMethod", "text-davinci-003" },
		{ "CPP_Default_maxTokens", "1000" },
		{ "CPP_Default_temperature", "0.700000" },
		{ "DisplayName", "GetGPTCompletion" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOpenAIComponent, nullptr, "getGPTCompletion", nullptr, nullptr, sizeof(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::OpenAIComponent_eventgetGPTCompletion_Parms), Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UOpenAIComponent);
	UClass* Z_Construct_UClass_UOpenAIComponent_NoRegister()
	{
		return UOpenAIComponent::StaticClass();
	}
	struct Z_Construct_UClass_UOpenAIComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IncomingGPTResponse_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingGPTResponse;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UOpenAIComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UOpenAIComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion, "getGPTCompletion" }, // 3871717047
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOpenAIComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "OpenAI" },
		{ "IncludePath", "OpenAIComponent.h" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UOpenAIComponent, Key), METADATA_PARAMS(Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse = { "IncomingGPTResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UOpenAIComponent, IncomingGPTResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse_MetaData)) }; // 196047445
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UOpenAIComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UOpenAIComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UOpenAIComponent_Statics::ClassParams = {
		&UOpenAIComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers),
		0,
		0x00A000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UOpenAIComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UOpenAIComponent()
	{
		if (!Z_Registration_Info_UClass_UOpenAIComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UOpenAIComponent.OuterSingleton, Z_Construct_UClass_UOpenAIComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UOpenAIComponent.OuterSingleton;
	}
	template<> FANTASIA_API UClass* StaticClass<UOpenAIComponent>()
	{
		return UOpenAIComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UOpenAIComponent);
	UOpenAIComponent::~UOpenAIComponent() {}
	struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UOpenAIComponent, UOpenAIComponent::StaticClass, TEXT("UOpenAIComponent"), &Z_Registration_Info_UClass_UOpenAIComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UOpenAIComponent), 4108349668U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_214405884(TEXT("/Script/FANTASIA"),
		Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
