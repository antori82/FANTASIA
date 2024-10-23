// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/OpenAIComponent.h"
#include "FANTASIA/Public/FANTASIATypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOpenAIComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_UOpenAIComponent();
FANTASIA_API UClass* Z_Construct_UClass_UOpenAIComponent_NoRegister();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FChatTurn();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Class UOpenAIComponent Function getChatGPTCompletion
struct Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics
{
	struct OpenAIComponent_eventgetChatGPTCompletion_Parms
	{
		TArray<FChatTurn> messages;
		FString apiMethod;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "messages" },
		{ "Category", "GPT" },
		{ "CPP_Default_apiMethod", "gpt-4-turbo-preview" },
		{ "DisplayName", "GetChatGPTCompletion" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_messages_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_messages;
	static const UECodeGen_Private::FStrPropertyParams NewProp_apiMethod;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_messages_Inner = { "messages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FChatTurn, METADATA_PARAMS(0, nullptr) }; // 2042086127
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_messages = { "messages", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetChatGPTCompletion_Parms, messages), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 2042086127
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_apiMethod = { "apiMethod", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetChatGPTCompletion_Parms, apiMethod), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_messages_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_messages,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_apiMethod,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOpenAIComponent, nullptr, "getChatGPTCompletion", nullptr, nullptr, Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::OpenAIComponent_eventgetChatGPTCompletion_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::OpenAIComponent_eventgetChatGPTCompletion_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UOpenAIComponent::execgetChatGPTCompletion)
{
	P_GET_TARRAY(FChatTurn,Z_Param_messages);
	P_GET_PROPERTY(FStrProperty,Z_Param_apiMethod);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->getChatGPTCompletion(Z_Param_messages,Z_Param_apiMethod);
	P_NATIVE_END;
}
// End Class UOpenAIComponent Function getChatGPTCompletion

// Begin Class UOpenAIComponent
void UOpenAIComponent::StaticRegisterNativesUOpenAIComponent()
{
	UClass* Class = UOpenAIComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "getChatGPTCompletion", &UOpenAIComponent::execgetChatGPTCompletion },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UOpenAIComponent);
UClass* Z_Construct_UClass_UOpenAIComponent_NoRegister()
{
	return UOpenAIComponent::StaticClass();
}
struct Z_Construct_UClass_UOpenAIComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "OpenAI" },
		{ "IncludePath", "OpenAIComponent.h" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingChatGPTResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingChatGPTResponse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion, "getChatGPTCompletion" }, // 3306270835
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UOpenAIComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOpenAIComponent, Key), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Key_MetaData), NewProp_Key_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingChatGPTResponse = { "IncomingChatGPTResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOpenAIComponent, IncomingChatGPTResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingChatGPTResponse_MetaData), NewProp_IncomingChatGPTResponse_MetaData) }; // 2190720310
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingChatGPTResponse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UOpenAIComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UOpenAIComponent_Statics::ClassParams = {
	&UOpenAIComponent::StaticClass,
	"Game",
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UOpenAIComponent_Statics::Class_MetaDataParams)
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
// End Class UOpenAIComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UOpenAIComponent, UOpenAIComponent::StaticClass, TEXT("UOpenAIComponent"), &Z_Registration_Info_UClass_UOpenAIComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UOpenAIComponent), 2514094117U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_2145644226(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
