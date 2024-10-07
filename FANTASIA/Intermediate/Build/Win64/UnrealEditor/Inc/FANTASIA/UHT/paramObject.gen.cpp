// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/paramObject.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeparamObject() {}

// Begin Cross Module References
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FparamValues();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin ScriptStruct FparamValues
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_paramValues;
class UScriptStruct* FparamValues::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_paramValues.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_paramValues.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FparamValues, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("paramValues"));
	}
	return Z_Registration_Info_UScriptStruct_paramValues.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FparamValues>()
{
	return FparamValues::StaticStruct();
}
struct Z_Construct_UScriptStruct_FparamValues_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//If you want this to appear in BP, make sure to use this instead\n" },
#endif
		{ "ModuleRelativePath", "Public/paramObject.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If you want this to appear in BP, make sure to use this instead" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_values_MetaData[] = {
		{ "Category", "paramValues" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// So to simplify your life for later debugging, always use UPROPERTY()\n" },
#endif
		{ "ModuleRelativePath", "Public/paramObject.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "So to simplify your life for later debugging, always use UPROPERTY()" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_values_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_values;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FparamValues>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_Inner = { "values", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values = { "values", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FparamValues, values), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_values_MetaData), NewProp_values_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FparamValues_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FparamValues_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FparamValues_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"paramValues",
	Z_Construct_UScriptStruct_FparamValues_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FparamValues_Statics::PropPointers),
	sizeof(FparamValues),
	alignof(FparamValues),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FparamValues_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FparamValues_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FparamValues()
{
	if (!Z_Registration_Info_UScriptStruct_paramValues.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_paramValues.InnerSingleton, Z_Construct_UScriptStruct_FparamValues_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_paramValues.InnerSingleton;
}
// End ScriptStruct FparamValues

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FparamValues::StaticStruct, Z_Construct_UScriptStruct_FparamValues_Statics::NewStructOps, TEXT("paramValues"), &Z_Registration_Info_UScriptStruct_paramValues, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FparamValues), 926523990U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_2787938260(TEXT("/Script/FANTASIA"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
