// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/OllamaComponent.h"
#include "FANTASIA/Public/FANTASIATypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOllamaComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_UOllamaComponent();
FANTASIA_API UClass* Z_Construct_UClass_UOllamaComponent_NoRegister();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FChatTurn();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Class UOllamaComponent Function getOllamaChatGPTCompletion
struct Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics
{
	struct OllamaComponent_eventgetOllamaChatGPTCompletion_Parms
	{
		TArray<FChatTurn> messages;
		FString model;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "messages" },
		{ "Category", "GPT" },
		{ "CPP_Default_model", "llama3" },
		{ "DisplayName", "GetOllamaChatGPTCompletion" },
		{ "ModuleRelativePath", "Public/OllamaComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_messages_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_messages;
	static const UECodeGen_Private::FStrPropertyParams NewProp_model;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::NewProp_messages_Inner = { "messages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FChatTurn, METADATA_PARAMS(0, nullptr) }; // 2042086127
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::NewProp_messages = { "messages", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OllamaComponent_eventgetOllamaChatGPTCompletion_Parms, messages), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 2042086127
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::NewProp_model = { "model", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OllamaComponent_eventgetOllamaChatGPTCompletion_Parms, model), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::NewProp_messages_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::NewProp_messages,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::NewProp_model,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOllamaComponent, nullptr, "getOllamaChatGPTCompletion", nullptr, nullptr, Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::OllamaComponent_eventgetOllamaChatGPTCompletion_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::OllamaComponent_eventgetOllamaChatGPTCompletion_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOllamaComponent::execgetOllamaChatGPTCompletion)
{
	P_GET_TARRAY(FChatTurn,Z_Param_messages);
	P_GET_PROPERTY(FStrProperty,Z_Param_model);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->getOllamaChatGPTCompletion(Z_Param_messages,Z_Param_model);
	P_NATIVE_END;
}
// End Class UOllamaComponent Function getOllamaChatGPTCompletion

// Begin Class UOllamaComponent Function getOllamaGPTCompletion
struct Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics
{
	struct OllamaComponent_eventgetOllamaGPTCompletion_Parms
	{
		FString prompt;
		FString model;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "GPT" },
		{ "CPP_Default_model", "llama3" },
		{ "DisplayName", "GetOllamaGPTCompletion" },
		{ "ModuleRelativePath", "Public/OllamaComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_prompt;
	static const UECodeGen_Private::FStrPropertyParams NewProp_model;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::NewProp_prompt = { "prompt", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OllamaComponent_eventgetOllamaGPTCompletion_Parms, prompt), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::NewProp_model = { "model", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OllamaComponent_eventgetOllamaGPTCompletion_Parms, model), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::NewProp_prompt,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::NewProp_model,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOllamaComponent, nullptr, "getOllamaGPTCompletion", nullptr, nullptr, Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::OllamaComponent_eventgetOllamaGPTCompletion_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::OllamaComponent_eventgetOllamaGPTCompletion_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOllamaComponent::execgetOllamaGPTCompletion)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_prompt);
	P_GET_PROPERTY(FStrProperty,Z_Param_model);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->getOllamaGPTCompletion(Z_Param_prompt,Z_Param_model);
	P_NATIVE_END;
}
// End Class UOllamaComponent Function getOllamaGPTCompletion

// Begin Class UOllamaComponent
void UOllamaComponent::StaticRegisterNativesUOllamaComponent()
{
	UClass* Class = UOllamaComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "getOllamaChatGPTCompletion", &UOllamaComponent::execgetOllamaChatGPTCompletion },
		{ "getOllamaGPTCompletion", &UOllamaComponent::execgetOllamaGPTCompletion },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UOllamaComponent);
UClass* Z_Construct_UClass_UOllamaComponent_NoRegister()
{
	return UOllamaComponent::StaticClass();
}
struct Z_Construct_UClass_UOllamaComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "OpenAI" },
		{ "IncludePath", "OllamaComponent.h" },
		{ "ModuleRelativePath", "Public/OllamaComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_endpoint_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/OllamaComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_port_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/OllamaComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingGPTResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/OllamaComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingChatGPTResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/OllamaComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_endpoint;
	static const UECodeGen_Private::FIntPropertyParams NewProp_port;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingGPTResponse;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingChatGPTResponse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UOllamaComponent_getOllamaChatGPTCompletion, "getOllamaChatGPTCompletion" }, // 4009279346
		{ &Z_Construct_UFunction_UOllamaComponent_getOllamaGPTCompletion, "getOllamaGPTCompletion" }, // 2055276888
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UOllamaComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UOllamaComponent_Statics::NewProp_endpoint = { "endpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOllamaComponent, endpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_endpoint_MetaData), NewProp_endpoint_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UOllamaComponent_Statics::NewProp_port = { "port", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOllamaComponent, port), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_port_MetaData), NewProp_port_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UOllamaComponent_Statics::NewProp_IncomingGPTResponse = { "IncomingGPTResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOllamaComponent, IncomingGPTResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingGPTResponse_MetaData), NewProp_IncomingGPTResponse_MetaData) }; // 4026830914
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UOllamaComponent_Statics::NewProp_IncomingChatGPTResponse = { "IncomingChatGPTResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOllamaComponent, IncomingChatGPTResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingChatGPTResponse_MetaData), NewProp_IncomingChatGPTResponse_MetaData) }; // 2190720310
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UOllamaComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOllamaComponent_Statics::NewProp_endpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOllamaComponent_Statics::NewProp_port,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOllamaComponent_Statics::NewProp_IncomingGPTResponse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOllamaComponent_Statics::NewProp_IncomingChatGPTResponse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOllamaComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UOllamaComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOllamaComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UOllamaComponent_Statics::ClassParams = {
	&UOllamaComponent::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UOllamaComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UOllamaComponent_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UOllamaComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UOllamaComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UOllamaComponent()
{
	if (!Z_Registration_Info_UClass_UOllamaComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UOllamaComponent.OuterSingleton, Z_Construct_UClass_UOllamaComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UOllamaComponent.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UOllamaComponent>()
{
	return UOllamaComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UOllamaComponent);
UOllamaComponent::~UOllamaComponent() {}
// End Class UOllamaComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UOllamaComponent, UOllamaComponent::StaticClass, TEXT("UOllamaComponent"), &Z_Registration_Info_UClass_UOllamaComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UOllamaComponent), 1182386150U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_3676338646(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OllamaComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
