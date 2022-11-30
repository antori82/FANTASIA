// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/paramObject.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeparamObject() {}
// Cross Module References
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FparamValues();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_paramValues;
class UScriptStruct* FparamValues::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_paramValues.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_paramValues.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FparamValues, Z_Construct_UPackage__Script_FANTASIA(), TEXT("paramValues"));
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
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FStrPropertyParams NewProp_values_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_values_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_values;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FparamValues_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "//If you want this to appear in BP, make sure to use this instead\n" },
		{ "ModuleRelativePath", "Public/paramObject.h" },
		{ "ToolTip", "If you want this to appear in BP, make sure to use this instead" },
	};
#endif
	void* Z_Construct_UScriptStruct_FparamValues_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FparamValues>();
	}
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_Inner = { "values", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_MetaData[] = {
		{ "Category", "paramValues" },
		{ "Comment", "// So to simplify your life for later debugging, always use UPROPERTY()\n" },
		{ "ModuleRelativePath", "Public/paramObject.h" },
		{ "ToolTip", "So to simplify your life for later debugging, always use UPROPERTY()" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values = { "values", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(FparamValues, values), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FparamValues_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FparamValues_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"paramValues",
		sizeof(FparamValues),
		alignof(FparamValues),
		Z_Construct_UScriptStruct_FparamValues_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FparamValues_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FparamValues_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FparamValues_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FparamValues()
	{
		if (!Z_Registration_Info_UScriptStruct_paramValues.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_paramValues.InnerSingleton, Z_Construct_UScriptStruct_FparamValues_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_paramValues.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_Statics::ScriptStructInfo[] = {
		{ FparamValues::StaticStruct, Z_Construct_UScriptStruct_FparamValues_Statics::NewStructOps, TEXT("paramValues"), &Z_Registration_Info_UScriptStruct_paramValues, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FparamValues), 3797614306U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_1921866496(TEXT("/Script/FANTASIA"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_paramObject_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
