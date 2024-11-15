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
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_EAzureASREnum();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Delegate FIncomingPartialASREvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingPartialASREvent_Parms
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
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::NewProp_message = { "message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingPartialASREvent_Parms, message), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::NewProp_message,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingPartialASREvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingPartialASREvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingPartialASREvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingPartialASREvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingPartialASREvent, const FString& message)
{
	struct _Script_FANTASIA_eventIncomingPartialASREvent_Parms
	{
		FString message;
	};
	_Script_FANTASIA_eventIncomingPartialASREvent_Parms Parms;
	Parms.message=message;
	IncomingPartialASREvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingPartialASREvent

// Begin Delegate FIncomingFinalASREvent
struct Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventIncomingFinalASREvent_Parms
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
const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::NewProp_message = { "message", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingFinalASREvent_Parms, message), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::NewProp_message,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingFinalASREvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingFinalASREvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingFinalASREvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FIncomingFinalASREvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingFinalASREvent, const FString& message)
{
	struct _Script_FANTASIA_eventIncomingFinalASREvent_Parms
	{
		FString message;
	};
	_Script_FANTASIA_eventIncomingFinalASREvent_Parms Parms;
	Parms.message=message;
	IncomingFinalASREvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// End Delegate FIncomingFinalASREvent

// Begin Class UAzureASRComponent Function AzureASRStart
struct Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics
{
	struct AzureASRComponent_eventAzureASRStart_Parms
	{
		TEnumAsByte<EAzureASREnum> mode;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "ASR" },
		{ "CPP_Default_mode", "ASR_ONESHOT" },
		{ "DisplayName", "ASR Start" },
		{ "Keywords", "AzureASRPlugin ASR" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_mode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::NewProp_mode = { "mode", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AzureASRComponent_eventAzureASRStart_Parms, mode), Z_Construct_UEnum_FANTASIA_EAzureASREnum, METADATA_PARAMS(0, nullptr) }; // 2771402611
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::NewProp_mode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureASRComponent, nullptr, "AzureASRStart", nullptr, nullptr, Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::AzureASRComponent_eventAzureASRStart_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UAzureASRComponent_AzureASRStart_Statics::AzureASRComponent_eventAzureASRStart_Parms) < MAX_uint16);
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
	P_GET_PROPERTY(FByteProperty,Z_Param_mode);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->AzureASRStart(EAzureASREnum(Z_Param_mode));
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingFinalMessage_MetaData[] = {
		{ "Category", "Speech Recognition" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IncomingPartialMessage_MetaData[] = {
		{ "Category", "Speech Recognition" },
		{ "ModuleRelativePath", "Public/AzureASRComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Region;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Language;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Endpoint;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingFinalMessage;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingPartialMessage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAzureASRComponent_AzureASRStart, "AzureASRStart" }, // 1781787622
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
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingFinalMessage = { "IncomingFinalMessage", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureASRComponent, IncomingFinalMessage), Z_Construct_UDelegateFunction_FANTASIA_IncomingFinalASREvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingFinalMessage_MetaData), NewProp_IncomingFinalMessage_MetaData) }; // 1323603229
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingPartialMessage = { "IncomingPartialMessage", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureASRComponent, IncomingPartialMessage), Z_Construct_UDelegateFunction_FANTASIA_IncomingPartialASREvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IncomingPartialMessage_MetaData), NewProp_IncomingPartialMessage_MetaData) }; // 2572702798
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAzureASRComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Key,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Region,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Language,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_Endpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingFinalMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureASRComponent_Statics::NewProp_IncomingPartialMessage,
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
struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAzureASRComponent, UAzureASRComponent::StaticClass, TEXT("UAzureASRComponent"), &Z_Registration_Info_UClass_UAzureASRComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAzureASRComponent), 238647578U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_2646524486(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
