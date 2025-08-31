// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/GroqComponent.h"
#include "FANTASIA/Public/FANTASIATypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGroqComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_UGroqComponent();
FANTASIA_API UClass* Z_Construct_UClass_UGroqComponent_NoRegister();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTStreamResponseEvent__DelegateSignature();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FChatTurn();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Class UGroqComponent Function getGPTCompletion
struct Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics
{
	struct GroqComponent_eventgetGPTCompletion_Parms
	{
		TArray<FChatTurn> messages;
		FString apiMethod;
		bool stream;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "messages" },
		{ "Category", "GPT" },
		{ "CPP_Default_apiMethod", "llama3-8b-8192" },
		{ "CPP_Default_stream", "false" },
		{ "DisplayName", "GetGroqGPTCompletion" },
		{ "ModuleRelativePath", "Public/GroqComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_messages_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_messages;
	static const UECodeGen_Private::FStrPropertyParams NewProp_apiMethod;
	static void NewProp_stream_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_stream;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_messages_Inner = { "messages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FChatTurn, METADATA_PARAMS(0, nullptr) }; // 4210891163
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_messages = { "messages", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GroqComponent_eventgetGPTCompletion_Parms, messages), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 4210891163
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_apiMethod = { "apiMethod", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GroqComponent_eventgetGPTCompletion_Parms, apiMethod), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_stream_SetBit(void* Obj)
{
	((GroqComponent_eventgetGPTCompletion_Parms*)Obj)->stream = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_stream = { "stream", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(GroqComponent_eventgetGPTCompletion_Parms), &Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_stream_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_messages_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_messages,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_apiMethod,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::NewProp_stream,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGroqComponent, nullptr, "getGPTCompletion", nullptr, nullptr, Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::GroqComponent_eventgetGPTCompletion_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::GroqComponent_eventgetGPTCompletion_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGroqComponent_getGPTCompletion()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGroqComponent_getGPTCompletion_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGroqComponent::execgetGPTCompletion)
{
	P_GET_TARRAY(FChatTurn,Z_Param_messages);
	P_GET_PROPERTY(FStrProperty,Z_Param_apiMethod);
	P_GET_UBOOL(Z_Param_stream);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->getGPTCompletion(Z_Param_messages,Z_Param_apiMethod,Z_Param_stream);
	P_NATIVE_END;
}
// End Class UGroqComponent Function getGPTCompletion

// Begin Class UGroqComponent
void UGroqComponent::StaticRegisterNativesUGroqComponent()
{
	UClass* Class = UGroqComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "getGPTCompletion", &UGroqComponent::execgetGPTCompletion },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGroqComponent);
UClass* Z_Construct_UClass_UGroqComponent_NoRegister()
{
	return UGroqComponent::StaticClass();
}
struct Z_Construct_UClass_UGroqComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Groq" },
		{ "IncludePath", "GroqComponent.h" },
		{ "ModuleRelativePath", "Public/GroqComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/GroqComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingGPTResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/GroqComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingChatGPTResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/GroqComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingGPTStreamResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/GroqComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingGPTResponse;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingChatGPTResponse;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingGPTStreamResponse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGroqComponent_getGPTCompletion, "getGPTCompletion" }, // 907324479
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGroqComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGroqComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGroqComponent, Key), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Key_MetaData), NewProp_Key_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGroqComponent_Statics::NewProp_IncomingGPTResponse = { "IncomingGPTResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGroqComponent, IncomingGPTResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingGPTResponse_MetaData), NewProp_IncomingGPTResponse_MetaData) }; // 830462791
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGroqComponent_Statics::NewProp_IncomingChatGPTResponse = { "IncomingChatGPTResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGroqComponent, IncomingChatGPTResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingChatGPTResponse_MetaData), NewProp_IncomingChatGPTResponse_MetaData) }; // 830462791
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGroqComponent_Statics::NewProp_IncomingGPTStreamResponse = { "IncomingGPTStreamResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGroqComponent, IncomingGPTStreamResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTStreamResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingGPTStreamResponse_MetaData), NewProp_IncomingGPTStreamResponse_MetaData) }; // 1550049039
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGroqComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGroqComponent_Statics::NewProp_Key,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGroqComponent_Statics::NewProp_IncomingGPTResponse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGroqComponent_Statics::NewProp_IncomingChatGPTResponse,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGroqComponent_Statics::NewProp_IncomingGPTStreamResponse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGroqComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGroqComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGroqComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGroqComponent_Statics::ClassParams = {
	&UGroqComponent::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGroqComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGroqComponent_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGroqComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UGroqComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGroqComponent()
{
	if (!Z_Registration_Info_UClass_UGroqComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGroqComponent.OuterSingleton, Z_Construct_UClass_UGroqComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGroqComponent.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UGroqComponent>()
{
	return UGroqComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGroqComponent);
UGroqComponent::~UGroqComponent() {}
// End Class UGroqComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GroqComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGroqComponent, UGroqComponent::StaticClass, TEXT("UGroqComponent"), &Z_Registration_Info_UClass_UGroqComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGroqComponent), 2224448788U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GroqComponent_h_1730584604(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GroqComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_GroqComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
