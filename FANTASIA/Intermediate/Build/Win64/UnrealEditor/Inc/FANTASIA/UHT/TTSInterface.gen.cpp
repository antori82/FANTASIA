// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/TTSInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTTSInterface() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
ENGINE_API UClass* Z_Construct_UClass_USoundWave_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UTTSInterface();
FANTASIA_API UClass* Z_Construct_UClass_UTTSInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Interface UTTSInterface Function TTSGetRawSound
struct Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics
{
	struct TTSInterface_eventTTSGetRawSound_Parms
	{
		FString id;
		TArray<float> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "ModuleRelativePath", "Public/TTSInterface.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSGetRawSound_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSGetRawSound_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTTSInterface, nullptr, "TTSGetRawSound", nullptr, nullptr, Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::TTSInterface_eventTTSGetRawSound_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::TTSInterface_eventTTSGetRawSound_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTTSInterface_TTSGetRawSound()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTTSInterface_TTSGetRawSound_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ITTSInterface::execTTSGetRawSound)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<float>*)Z_Param__Result=P_THIS->TTSGetRawSound(Z_Param_id);
	P_NATIVE_END;
}
// End Interface UTTSInterface Function TTSGetRawSound

// Begin Interface UTTSInterface Function TTSGetSound
struct Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics
{
	struct TTSInterface_eventTTSGetSound_Parms
	{
		FString id;
		USoundWave* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* To format the synthesis result into audio playable by Unreal\n\x09*\n\x09*\x09@parm id - buffer synthesis id\n\x09*\n\x09**/" },
#endif
		{ "ModuleRelativePath", "Public/TTSInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "To format the synthesis result into audio playable by Unreal\n\n      @parm id - buffer synthesis id" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSGetSound_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSGetSound_Parms, ReturnValue), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTTSInterface, nullptr, "TTSGetSound", nullptr, nullptr, Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::TTSInterface_eventTTSGetSound_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::TTSInterface_eventTTSGetSound_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTTSInterface_TTSGetSound()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ITTSInterface::execTTSGetSound)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(USoundWave**)Z_Param__Result=P_THIS->TTSGetSound(Z_Param_id);
	P_NATIVE_END;
}
// End Interface UTTSInterface Function TTSGetSound

// Begin Interface UTTSInterface Function TTSSynthesize
struct Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics
{
	struct TTSInterface_eventTTSSynthesize_Parms
	{
		FString ssml;
		FString id;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* To manage speech synthesis\n\x09*\n\x09*\x09@param ssml - synthesis data\n\x09*\x09@param id - buffer synthesis id\n\x09*\n\x09**/" },
#endif
		{ "ModuleRelativePath", "Public/TTSInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "To manage speech synthesis\n\n      @param ssml - synthesis data\n      @param id - buffer synthesis id" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ssml;
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::NewProp_ssml = { "ssml", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSSynthesize_Parms, ssml), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSSynthesize_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::NewProp_ssml,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::NewProp_id,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTTSInterface, nullptr, "TTSSynthesize", nullptr, nullptr, Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::TTSInterface_eventTTSSynthesize_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::TTSInterface_eventTTSSynthesize_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UTTSInterface_TTSSynthesize()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ITTSInterface::execTTSSynthesize)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ssml);
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->TTSSynthesize(Z_Param_ssml,Z_Param_id);
	P_NATIVE_END;
}
// End Interface UTTSInterface Function TTSSynthesize

// Begin Interface UTTSInterface
void UTTSInterface::StaticRegisterNativesUTTSInterface()
{
	UClass* Class = UTTSInterface::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "TTSGetRawSound", &ITTSInterface::execTTSGetRawSound },
		{ "TTSGetSound", &ITTSInterface::execTTSGetSound },
		{ "TTSSynthesize", &ITTSInterface::execTTSSynthesize },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTTSInterface);
UClass* Z_Construct_UClass_UTTSInterface_NoRegister()
{
	return UTTSInterface::StaticClass();
}
struct Z_Construct_UClass_UTTSInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TTSInterface.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UTTSInterface_TTSGetRawSound, "TTSGetRawSound" }, // 4085028839
		{ &Z_Construct_UFunction_UTTSInterface_TTSGetSound, "TTSGetSound" }, // 86999920
		{ &Z_Construct_UFunction_UTTSInterface_TTSSynthesize, "TTSSynthesize" }, // 1129029781
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ITTSInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UTTSInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTTSInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTTSInterface_Statics::ClassParams = {
	&UTTSInterface::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTTSInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UTTSInterface_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTTSInterface()
{
	if (!Z_Registration_Info_UClass_UTTSInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTTSInterface.OuterSingleton, Z_Construct_UClass_UTTSInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTTSInterface.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UTTSInterface>()
{
	return UTTSInterface::StaticClass();
}
UTTSInterface::UTTSInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTTSInterface);
UTTSInterface::~UTTSInterface() {}
// End Interface UTTSInterface

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTTSInterface, UTTSInterface::StaticClass, TEXT("UTTSInterface"), &Z_Registration_Info_UClass_UTTSInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTTSInterface), 2614763809U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_1260764438(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
