// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/AzureNLUComponent.h"
#include "FANTASIA/Public/FANTASIATypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAzureNLUComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_UAzureNLUComponent();
FANTASIA_API UClass* Z_Construct_UClass_UAzureNLUComponent_NoRegister();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FNLUResponse();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Delegate FIncomingNLUEvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingNLUEvent_Parms
	{
		FNLUResponse NLUResponse;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_NLUResponse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::NewProp_NLUResponse = { "NLUResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingNLUEvent_Parms, NLUResponse), Z_Construct_UScriptStruct_FNLUResponse, METADATA_PARAMS(0, nullptr) }; // 667433752
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::NewProp_NLUResponse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingNLUEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingNLUEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingNLUEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingNLUEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingNLUEvent, FNLUResponse NLUResponse)
{
	struct _Script_FANTASIA_eventIncomingNLUEvent_Parms
	{
		FNLUResponse NLUResponse;
	};
	_Script_FANTASIA_eventIncomingNLUEvent_Parms Parms;
	Parms.NLUResponse=NLUResponse;
	IncomingNLUEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingNLUEvent

// Begin Class UAzureNLUComponent Function AzureNLUStart
struct Z_Construct_UFunction_UAzureNLUComponent_AzureNLUStart_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "NLU" },
		{ "DisplayName", "NLU Start" },
		{ "Keywords", "Azure Plugin NLU" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureNLUComponent_AzureNLUStart_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureNLUComponent, nullptr, "AzureNLUStart", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureNLUComponent_AzureNLUStart_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAzureNLUComponent_AzureNLUStart_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UAzureNLUComponent_AzureNLUStart()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAzureNLUComponent_AzureNLUStart_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAzureNLUComponent::execAzureNLUStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AzureNLUStart();
	P_NATIVE_END;
}
// End Class UAzureNLUComponent Function AzureNLUStart

// Begin Class UAzureNLUComponent
void UAzureNLUComponent::StaticRegisterNativesUAzureNLUComponent()
{
	UClass* Class = UAzureNLUComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AzureNLUStart", &UAzureNLUComponent::execAzureNLUStart },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAzureNLUComponent);
UClass* Z_Construct_UClass_UAzureNLUComponent_NoRegister()
{
	return UAzureNLUComponent::StaticClass();
}
struct Z_Construct_UClass_UAzureNLUComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Azure" },
		{ "IncludePath", "AzureNLUComponent.h" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpeechKey_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Region_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LanguageKey_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Endpoint_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ProjectName_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeploymentName_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingMessage_MetaData[] = {
		{ "Category", "Speech Understanding" },
		{ "ModuleRelativePath", "Public/AzureNLUComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SpeechKey;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Region;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Language;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LanguageKey;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Endpoint;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ProjectName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DeploymentName;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingMessage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAzureNLUComponent_AzureNLUStart, "AzureNLUStart" }, // 1533782229
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAzureNLUComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_SpeechKey = { "SpeechKey", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureNLUComponent, SpeechKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpeechKey_MetaData), NewProp_SpeechKey_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_Region = { "Region", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureNLUComponent, Region), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Region_MetaData), NewProp_Region_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_Language = { "Language", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureNLUComponent, Language), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Language_MetaData), NewProp_Language_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_LanguageKey = { "LanguageKey", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureNLUComponent, LanguageKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LanguageKey_MetaData), NewProp_LanguageKey_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_Endpoint = { "Endpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureNLUComponent, Endpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Endpoint_MetaData), NewProp_Endpoint_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_ProjectName = { "ProjectName", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureNLUComponent, ProjectName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ProjectName_MetaData), NewProp_ProjectName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_DeploymentName = { "DeploymentName", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureNLUComponent, DeploymentName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeploymentName_MetaData), NewProp_DeploymentName_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_IncomingMessage = { "IncomingMessage", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureNLUComponent, IncomingMessage), Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingMessage_MetaData), NewProp_IncomingMessage_MetaData) }; // 2216557217
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAzureNLUComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_SpeechKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_Region,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_Language,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_LanguageKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_Endpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_ProjectName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_DeploymentName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureNLUComponent_Statics::NewProp_IncomingMessage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureNLUComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAzureNLUComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureNLUComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAzureNLUComponent_Statics::ClassParams = {
	&UAzureNLUComponent::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UAzureNLUComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UAzureNLUComponent_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureNLUComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UAzureNLUComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAzureNLUComponent()
{
	if (!Z_Registration_Info_UClass_UAzureNLUComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAzureNLUComponent.OuterSingleton, Z_Construct_UClass_UAzureNLUComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAzureNLUComponent.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UAzureNLUComponent>()
{
	return UAzureNLUComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAzureNLUComponent);
UAzureNLUComponent::~UAzureNLUComponent() {}
// End Class UAzureNLUComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAzureNLUComponent, UAzureNLUComponent::StaticClass, TEXT("UAzureNLUComponent"), &Z_Registration_Info_UClass_UAzureNLUComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAzureNLUComponent), 1875821402U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_1995028299(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
