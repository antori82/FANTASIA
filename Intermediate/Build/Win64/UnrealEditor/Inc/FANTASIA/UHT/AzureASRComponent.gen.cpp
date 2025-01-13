// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/AzureASRComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAzureASRComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_UAzureASRComponent();
FANTASIA_API UClass* Z_Construct_UClass_UAzureASRComponent_NoRegister();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Delegate FIncomingASREvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingASREvent_Parms
	{
		FString message;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_message;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::NewProp_message = { "message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingASREvent_Parms, message), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::NewProp_message,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingASREvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingASREvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingASREvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingASREvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingASREvent, const FString& message)
{
	struct _Script_FANTASIA_eventIncomingASREvent_Parms
	{
		FString message;
	};
	_Script_FANTASIA_eventIncomingASREvent_Parms Parms;
	Parms.message=message;
	IncomingASREvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingASREvent

// Begin Class UAzureASRComponent Function AzureASRStart
struct Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "ASR" },
		{ "DisplayName", "ASR Start" },
		{ "Keywords", "AzureASRPlugin ASR" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureASRComponent, nullptr, "AzureASRStart", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UAzureASRComponent_AzureASRStart()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAzureASRComponent::execAzureASRStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AzureASRStart();
	P_NATIVE_END;
}
// End Class UAzureASRComponent Function AzureASRStart

// Begin Class UAzureASRComponent Function AzureASRStop
struct Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "ASR" },
		{ "DisplayName", "ASR Stop" },
		{ "Keywords", "AzureASRPlugin ASR" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureASRComponent, nullptr, "AzureASRStop", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UAzureASRComponent_AzureASRStop()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAzureASRComponent_AzureASRStop_Statics::FuncParams);
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
// End Class UAzureASRComponent Function AzureASRStop

// Begin Class UAzureASRComponent
void UAzureASRComponent::StaticRegisterNativesUAzureASRComponent()
{
	UClass* Class = UAzureASRComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "AzureASRStart", &UAzureASRComponent::execAzureASRStart },
		{ "AzureASRStop", &UAzureASRComponent::execAzureASRStop },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAzureASRComponent);
UClass* Z_Construct_UClass_UAzureASRComponent_NoRegister()
{
	return UAzureASRComponent::StaticClass();
}
struct Z_Construct_UClass_UAzureASRComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Azure" },
		{ "IncludePath", "AzureASRComponent.h" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Region_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Endpoint_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingMessage_MetaData[] = {
		{ "Category", "Speech Recognition" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Region;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Language;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Endpoint;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingMessage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAzureASRComponent_AzureASRStart, "AzureASRStart" }, // 1211913257
		{ &Z_Construct_UFunction_UAzureASRComponent_AzureASRStop, "AzureASRStop" }, // 3231467058
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAzureASRComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureASRComponent, Key), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Key_MetaData), NewProp_Key_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Region = { "Region", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureASRComponent, Region), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Region_MetaData), NewProp_Region_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Language = { "Language", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureASRComponent, Language), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Language_MetaData), NewProp_Language_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Endpoint = { "Endpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureASRComponent, Endpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Endpoint_MetaData), NewProp_Endpoint_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingMessage = { "IncomingMessage", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureASRComponent, IncomingMessage), Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingMessage_MetaData), NewProp_IncomingMessage_MetaData) }; // 336214503
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAzureASRComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Key,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Region,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Language,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Endpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingMessage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAzureASRComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAzureASRComponent_Statics::ClassParams = {
	&UAzureASRComponent::StaticClass,
	"Game",
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureASRComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UAzureASRComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAzureASRComponent()
{
	if (!Z_Registration_Info_UClass_UAzureASRComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAzureASRComponent.OuterSingleton, Z_Construct_UClass_UAzureASRComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAzureASRComponent.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UAzureASRComponent>()
{
	return UAzureASRComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAzureASRComponent);
UAzureASRComponent::~UAzureASRComponent() {}
// End Class UAzureASRComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAzureASRComponent, UAzureASRComponent::StaticClass, TEXT("UAzureASRComponent"), &Z_Registration_Info_UClass_UAzureASRComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAzureASRComponent), 3331397531U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_768770342(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
