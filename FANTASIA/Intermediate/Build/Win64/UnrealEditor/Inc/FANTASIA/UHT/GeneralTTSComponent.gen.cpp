// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/GeneralTTSComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGeneralTTSComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USoundWave_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UGeneralTTSComponent();
FANTASIA_API UClass* Z_Construct_UClass_UGeneralTTSComponent_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UTTSInterface_NoRegister();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Class UGeneralTTSComponent Function TTSGetSound
struct Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics
{
	struct GeneralTTSComponent_eventTTSGetSound_Parms
	{
		FString id;
		USoundWave* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Sound General" },
		{ "Keywords", "Plugin TTS" },
		{ "ModuleRelativePath", "Public/GeneralTTSComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeneralTTSComponent_eventTTSGetSound_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeneralTTSComponent_eventTTSGetSound_Parms, ReturnValue), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneralTTSComponent, nullptr, "TTSGetSound", nullptr, nullptr, Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::GeneralTTSComponent_eventTTSGetSound_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::GeneralTTSComponent_eventTTSGetSound_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGeneralTTSComponent::execTTSGetSound)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(USoundWave**)Z_Param__Result=P_THIS->TTSGetSound(Z_Param_id);
	P_NATIVE_END;
}
// End Class UGeneralTTSComponent Function TTSGetSound

// Begin Class UGeneralTTSComponent Function TTSSynthesize
struct Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics
{
	struct GeneralTTSComponent_eventTTSSynthesize_Parms
	{
		FString ssml;
		FString id;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "TTS Start" },
		{ "Keywords", "Plugin TTS" },
		{ "ModuleRelativePath", "Public/GeneralTTSComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ssml;
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::NewProp_ssml = { "ssml", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeneralTTSComponent_eventTTSSynthesize_Parms, ssml), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GeneralTTSComponent_eventTTSSynthesize_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::NewProp_ssml,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::NewProp_id,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGeneralTTSComponent, nullptr, "TTSSynthesize", nullptr, nullptr, Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::GeneralTTSComponent_eventTTSSynthesize_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::GeneralTTSComponent_eventTTSSynthesize_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGeneralTTSComponent::execTTSSynthesize)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ssml);
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->TTSSynthesize(Z_Param_ssml,Z_Param_id);
	P_NATIVE_END;
}
// End Class UGeneralTTSComponent Function TTSSynthesize

// Begin Class UGeneralTTSComponent
void UGeneralTTSComponent::StaticRegisterNativesUGeneralTTSComponent()
{
	UClass* Class = UGeneralTTSComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "TTSGetSound", &UGeneralTTSComponent::execTTSGetSound },
		{ "TTSSynthesize", &UGeneralTTSComponent::execTTSSynthesize },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGeneralTTSComponent);
UClass* Z_Construct_UClass_UGeneralTTSComponent_NoRegister()
{
	return UGeneralTTSComponent::StaticClass();
}
struct Z_Construct_UClass_UGeneralTTSComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "IncludePath", "GeneralTTSComponent.h" },
		{ "ModuleRelativePath", "Public/GeneralTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Speaker_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/GeneralTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SynthesisReady_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "ModuleRelativePath", "Public/GeneralTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Endpoint_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/GeneralTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SamplingRate_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ClampMax", "96000" },
		{ "ClampMin", "8000" },
		{ "Default", "44100" },
		{ "DisplayName", "Sampling Rate" },
		{ "ModuleRelativePath", "Public/GeneralTTSComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Speaker;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_SynthesisReady;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Endpoint;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SamplingRate;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGeneralTTSComponent_TTSGetSound, "TTSGetSound" }, // 612152641
		{ &Z_Construct_UFunction_UGeneralTTSComponent_TTSSynthesize, "TTSSynthesize" }, // 3797961220
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGeneralTTSComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UGeneralTTSComponent_Statics::NewProp_Speaker = { "Speaker", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGeneralTTSComponent, Speaker), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Speaker_MetaData), NewProp_Speaker_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGeneralTTSComponent_Statics::NewProp_SynthesisReady = { "SynthesisReady", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGeneralTTSComponent, SynthesisReady), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SynthesisReady_MetaData), NewProp_SynthesisReady_MetaData) }; // 3364404421
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGeneralTTSComponent_Statics::NewProp_Endpoint = { "Endpoint", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGeneralTTSComponent, Endpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Endpoint_MetaData), NewProp_Endpoint_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGeneralTTSComponent_Statics::NewProp_SamplingRate = { "SamplingRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGeneralTTSComponent, SamplingRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SamplingRate_MetaData), NewProp_SamplingRate_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGeneralTTSComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGeneralTTSComponent_Statics::NewProp_Speaker,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGeneralTTSComponent_Statics::NewProp_SynthesisReady,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGeneralTTSComponent_Statics::NewProp_Endpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGeneralTTSComponent_Statics::NewProp_SamplingRate,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGeneralTTSComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGeneralTTSComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGeneralTTSComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams Z_Construct_UClass_UGeneralTTSComponent_Statics::InterfaceParams[] = {
	{ Z_Construct_UClass_UTTSInterface_NoRegister, (int32)VTABLE_OFFSET(UGeneralTTSComponent, ITTSInterface), false },  // 2146738850
};
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGeneralTTSComponent_Statics::ClassParams = {
	&UGeneralTTSComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGeneralTTSComponent_Statics::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGeneralTTSComponent_Statics::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGeneralTTSComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UGeneralTTSComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGeneralTTSComponent()
{
	if (!Z_Registration_Info_UClass_UGeneralTTSComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGeneralTTSComponent.OuterSingleton, Z_Construct_UClass_UGeneralTTSComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGeneralTTSComponent.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UGeneralTTSComponent>()
{
	return UGeneralTTSComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGeneralTTSComponent);
UGeneralTTSComponent::~UGeneralTTSComponent() {}
// End Class UGeneralTTSComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGeneralTTSComponent, UGeneralTTSComponent::StaticClass, TEXT("UGeneralTTSComponent"), &Z_Registration_Info_UClass_UGeneralTTSComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGeneralTTSComponent), 1811666879U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_1895182503(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_GeneralTTSComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
