// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/paramObject.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeparamObject() {}
// Cross Module References
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FparamValues();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
class UScriptStruct* FparamValues::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FANTASIA_API uint32 Get_Z_Construct_UScriptStruct_FparamValues_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FparamValues, Z_Construct_UPackage__Script_FANTASIA(), TEXT("paramValues"), sizeof(FparamValues), Get_Z_Construct_UScriptStruct_FparamValues_Hash());
	}
	return Singleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FparamValues>()
{
	return FparamValues::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FparamValues(FparamValues::StaticStruct, TEXT("/Script/FANTASIA"), TEXT("paramValues"), false, nullptr, nullptr);
static struct FScriptStruct_FANTASIA_StaticRegisterNativesFparamValues
{
	FScriptStruct_FANTASIA_StaticRegisterNativesFparamValues()
	{
		UScriptStruct::DeferCppStructOps<FparamValues>(FName(TEXT("paramValues")));
	}
} ScriptStruct_FANTASIA_StaticRegisterNativesFparamValues;
	struct Z_Construct_UScriptStruct_FparamValues_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_values_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_values_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_values;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FparamValues_Statics::Struct_MetaDataParams[] = {
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
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_Inner = { "values", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_MetaData[] = {
		{ "Category", "paramValues" },
		{ "Comment", "// So to simplify your life for later debugging, always use UPROPERTY()\n" },
		{ "ModuleRelativePath", "Public/paramObject.h" },
		{ "ToolTip", "So to simplify your life for later debugging, always use UPROPERTY()" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values = { "values", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FparamValues, values), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FparamValues_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FparamValues_Statics::NewProp_values,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FparamValues_Statics::ReturnStructParams = {
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
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FparamValues_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("paramValues"), sizeof(FparamValues), Get_Z_Construct_UScriptStruct_FparamValues_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FparamValues_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FparamValues_Hash() { return 3356302976U; }
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
