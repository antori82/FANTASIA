// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/BayesianNetwork.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBayesianNetwork() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetwork();
FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetwork_NoRegister();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_BayesianNodeType();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_InferenceAlgs();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FBayesianArcStruct();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FBayesianNodeStruct();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FMapContainer();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin ScriptStruct FMapContainer
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MapContainer;
class UScriptStruct* FMapContainer::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MapContainer.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MapContainer.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMapContainer, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("MapContainer"));
	}
	return Z_Registration_Info_UScriptStruct_MapContainer.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FMapContainer>()
{
	return FMapContainer::StaticStruct();
}
struct Z_Construct_UScriptStruct_FMapContainer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Map_MetaData[] = {
		{ "Category", "MapContainer" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Map_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Map_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_Map;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMapContainer>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_ValueProp = { "Map", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_Key_KeyProp = { "Map_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map = { "Map", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMapContainer, Map), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Map_MetaData), NewProp_Map_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMapContainer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapContainer_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMapContainer_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"MapContainer",
	Z_Construct_UScriptStruct_FMapContainer_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapContainer_Statics::PropPointers),
	sizeof(FMapContainer),
	alignof(FMapContainer),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapContainer_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMapContainer_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMapContainer()
{
	if (!Z_Registration_Info_UScriptStruct_MapContainer.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_MapContainer.InnerSingleton, Z_Construct_UScriptStruct_FMapContainer_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_MapContainer.InnerSingleton;
}
// End ScriptStruct FMapContainer

// Begin Delegate FGetPosteriorDelegate
struct Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventGetPosteriorDelegate_Parms
	{
		FMapContainer outMap;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_outMap;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::NewProp_outMap = { "outMap", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventGetPosteriorDelegate_Parms, outMap), Z_Construct_UScriptStruct_FMapContainer, METADATA_PARAMS(0, nullptr) }; // 1111572595
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::NewProp_outMap,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "GetPosteriorDelegate__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::_Script_FANTASIA_eventGetPosteriorDelegate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::_Script_FANTASIA_eventGetPosteriorDelegate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FGetPosteriorDelegate_DelegateWrapper(const FScriptDelegate& GetPosteriorDelegate, FMapContainer outMap)
{
	struct _Script_FANTASIA_eventGetPosteriorDelegate_Parms
	{
		FMapContainer outMap;
	};
	_Script_FANTASIA_eventGetPosteriorDelegate_Parms Parms;
	Parms.outMap=outMap;
	GetPosteriorDelegate.ProcessDelegate<UObject>(&Parms);
}
// End Delegate FGetPosteriorDelegate

// Begin Enum InferenceAlgs
static FEnumRegistrationInfo Z_Registration_Info_UEnum_InferenceAlgs;
static UEnum* InferenceAlgs_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_InferenceAlgs.OuterSingleton)
	{
		Z_Registration_Info_UEnum_InferenceAlgs.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_InferenceAlgs, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("InferenceAlgs"));
	}
	return Z_Registration_Info_UEnum_InferenceAlgs.OuterSingleton;
}
template<> FANTASIA_API UEnum* StaticEnum<InferenceAlgs>()
{
	return InferenceAlgs_StaticEnum();
}
struct Z_Construct_UEnum_FANTASIA_InferenceAlgs_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//\"BlueprintType\" is essential to include\n" },
#endif
		{ "Lazy_Propagation.DisplayName", "Lazy Propagation" },
		{ "Lazy_Propagation.Name", "InferenceAlgs::Lazy_Propagation" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
		{ "ShaferShenoy.DisplayName", "Shafer Shenoy Inference" },
		{ "ShaferShenoy.Name", "InferenceAlgs::ShaferShenoy" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\"BlueprintType\" is essential to include" },
#endif
		{ "VariableElimination.DisplayName", "Variable Elimination" },
		{ "VariableElimination.Name", "InferenceAlgs::VariableElimination" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "InferenceAlgs::Lazy_Propagation", (int64)InferenceAlgs::Lazy_Propagation },
		{ "InferenceAlgs::ShaferShenoy", (int64)InferenceAlgs::ShaferShenoy },
		{ "InferenceAlgs::VariableElimination", (int64)InferenceAlgs::VariableElimination },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_InferenceAlgs_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	"InferenceAlgs",
	"InferenceAlgs",
	Z_Construct_UEnum_FANTASIA_InferenceAlgs_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_InferenceAlgs_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_InferenceAlgs_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_InferenceAlgs_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FANTASIA_InferenceAlgs()
{
	if (!Z_Registration_Info_UEnum_InferenceAlgs.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_InferenceAlgs.InnerSingleton, Z_Construct_UEnum_FANTASIA_InferenceAlgs_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_InferenceAlgs.InnerSingleton;
}
// End Enum InferenceAlgs

// Begin ScriptStruct FBayesianArcStruct
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_BayesianArcStruct;
class UScriptStruct* FBayesianArcStruct::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_BayesianArcStruct.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_BayesianArcStruct.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBayesianArcStruct, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("BayesianArcStruct"));
	}
	return Z_Registration_Info_UScriptStruct_BayesianArcStruct.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FBayesianArcStruct>()
{
	return FBayesianArcStruct::StaticStruct();
}
struct Z_Construct_UScriptStruct_FBayesianArcStruct_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Tail_MetaData[] = {
		{ "Category", "BayesianArcStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Head_MetaData[] = {
		{ "Category", "BayesianArcStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Tail;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Head;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBayesianArcStruct>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Tail = { "Tail", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBayesianArcStruct, Tail), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Tail_MetaData), NewProp_Tail_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Head = { "Head", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBayesianArcStruct, Head), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Head_MetaData), NewProp_Head_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Tail,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Head,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"BayesianArcStruct",
	Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::PropPointers),
	sizeof(FBayesianArcStruct),
	alignof(FBayesianArcStruct),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBayesianArcStruct()
{
	if (!Z_Registration_Info_UScriptStruct_BayesianArcStruct.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_BayesianArcStruct.InnerSingleton, Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_BayesianArcStruct.InnerSingleton;
}
// End ScriptStruct FBayesianArcStruct

// Begin ScriptStruct FBayesianNodeStruct
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_BayesianNodeStruct;
class UScriptStruct* FBayesianNodeStruct::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_BayesianNodeStruct.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_BayesianNodeStruct.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBayesianNodeStruct, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("BayesianNodeStruct"));
	}
	return Z_Registration_Info_UScriptStruct_BayesianNodeStruct.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FBayesianNodeStruct>()
{
	return FBayesianNodeStruct::StaticStruct();
}
struct Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[] = {
		{ "Category", "BayesianNodeStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_variables_MetaData[] = {
		{ "Category", "BayesianNodeStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_values_MetaData[] = {
		{ "Category", "BayesianNodeStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_parents_MetaData[] = {
		{ "Category", "BayesianNodeStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_variables_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_variables;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_values_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_values;
	static const UECodeGen_Private::FStrPropertyParams NewProp_parents_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_parents;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBayesianNodeStruct>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBayesianNodeStruct, name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_name_MetaData), NewProp_name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables_Inner = { "variables", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables = { "variables", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBayesianNodeStruct, variables), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_variables_MetaData), NewProp_variables_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values_Inner = { "values", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values = { "values", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBayesianNodeStruct, values), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_values_MetaData), NewProp_values_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents_Inner = { "parents", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents = { "parents", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBayesianNodeStruct, parents), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_parents_MetaData), NewProp_parents_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"BayesianNodeStruct",
	Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::PropPointers),
	sizeof(FBayesianNodeStruct),
	alignof(FBayesianNodeStruct),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBayesianNodeStruct()
{
	if (!Z_Registration_Info_UScriptStruct_BayesianNodeStruct.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_BayesianNodeStruct.InnerSingleton, Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_BayesianNodeStruct.InnerSingleton;
}
// End ScriptStruct FBayesianNodeStruct

// Begin Class UBayesianNetwork Function addArc
struct Z_Construct_UFunction_UBayesianNetwork_addArc_Statics
{
	struct BayesianNetwork_eventaddArc_Parms
	{
		FString parent;
		FString child;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "addArc" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_parent;
	static const UECodeGen_Private::FStrPropertyParams NewProp_child;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::NewProp_parent = { "parent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddArc_Parms, parent), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::NewProp_child = { "child", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddArc_Parms, child), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::NewProp_parent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::NewProp_child,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "addArc", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::BayesianNetwork_eventaddArc_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::BayesianNetwork_eventaddArc_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_addArc()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execaddArc)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_parent);
	P_GET_PROPERTY(FStrProperty,Z_Param_child);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->addArc(Z_Param_parent,Z_Param_child);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function addArc

// Begin Class UBayesianNetwork Function addDiscretizedVariable
struct Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics
{
	struct BayesianNetwork_eventaddDiscretizedVariable_Parms
	{
		FString variable;
		FString description;
		float minTick;
		float maxTick;
		float nPoints;
		BayesianNodeType nodeType;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "addDiscretizedVariable" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FStrPropertyParams NewProp_description;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_minTick;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_maxTick;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_nPoints;
	static const UECodeGen_Private::FBytePropertyParams NewProp_nodeType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_nodeType;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_description = { "description", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, description), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_minTick = { "minTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, minTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_maxTick = { "maxTick", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, maxTick), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nPoints = { "nPoints", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, nPoints), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nodeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nodeType = { "nodeType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, nodeType), Z_Construct_UEnum_FANTASIA_BayesianNodeType, METADATA_PARAMS(0, nullptr) }; // 2887683997
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_variable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_minTick,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_maxTick,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nPoints,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nodeType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nodeType,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "addDiscretizedVariable", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::BayesianNetwork_eventaddDiscretizedVariable_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::BayesianNetwork_eventaddDiscretizedVariable_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execaddDiscretizedVariable)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_GET_PROPERTY(FStrProperty,Z_Param_description);
	P_GET_PROPERTY(FFloatProperty,Z_Param_minTick);
	P_GET_PROPERTY(FFloatProperty,Z_Param_maxTick);
	P_GET_PROPERTY(FFloatProperty,Z_Param_nPoints);
	P_GET_ENUM(BayesianNodeType,Z_Param_nodeType);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->addDiscretizedVariable(Z_Param_variable,Z_Param_description,Z_Param_minTick,Z_Param_maxTick,Z_Param_nPoints,BayesianNodeType(Z_Param_nodeType));
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function addDiscretizedVariable

// Begin Class UBayesianNetwork Function addEvidence
struct Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics
{
	struct BayesianNetwork_eventaddEvidence_Parms
	{
		FString variable;
		TArray<float> data;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//UFUNCTION(BlueprintCallable, meta = (DisplayName = \"getPosterior\", Keywords = \"Inference\", AutoCreateRefTerm = \"evidences\"), Category = \"Bayesian_Network\")\n//void getPosterior(FGetPosteriorDelegate outMap, FString variable);\n" },
#endif
		{ "DisplayName", "addEvidence" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UFUNCTION(BlueprintCallable, meta = (DisplayName = \"getPosterior\", Keywords = \"Inference\", AutoCreateRefTerm = \"evidences\"), Category = \"Bayesian_Network\")\nvoid getPosterior(FGetPosteriorDelegate outMap, FString variable);" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_data_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_data;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddEvidence_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_data_Inner = { "data", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_data = { "data", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddEvidence_Parms, data), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_variable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_data_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_data,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "addEvidence", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::BayesianNetwork_eventaddEvidence_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::BayesianNetwork_eventaddEvidence_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_addEvidence()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execaddEvidence)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_GET_TARRAY(float,Z_Param_data);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->addEvidence(Z_Param_variable,Z_Param_data);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function addEvidence

// Begin Class UBayesianNetwork Function addLabelizedVariable
struct Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics
{
	struct BayesianNetwork_eventaddLabelizedVariable_Parms
	{
		FString variable;
		FString description;
		TArray<FString> labels;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "addLabelizedVariable" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FStrPropertyParams NewProp_description;
	static const UECodeGen_Private::FStrPropertyParams NewProp_labels_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_labels;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddLabelizedVariable_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_description = { "description", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddLabelizedVariable_Parms, description), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_labels_Inner = { "labels", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_labels = { "labels", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventaddLabelizedVariable_Parms, labels), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_variable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_labels_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_labels,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "addLabelizedVariable", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::BayesianNetwork_eventaddLabelizedVariable_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::BayesianNetwork_eventaddLabelizedVariable_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execaddLabelizedVariable)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_GET_PROPERTY(FStrProperty,Z_Param_description);
	P_GET_TARRAY(FString,Z_Param_labels);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->addLabelizedVariable(Z_Param_variable,Z_Param_description,Z_Param_labels);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function addLabelizedVariable

// Begin Class UBayesianNetwork Function erase
struct Z_Construct_UFunction_UBayesianNetwork_erase_Statics
{
	struct BayesianNetwork_eventerase_Parms
	{
		FString variable;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "clear" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_erase_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventerase_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_erase_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_erase_Statics::NewProp_variable,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_erase_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_erase_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "erase", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_erase_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_erase_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_erase_Statics::BayesianNetwork_eventerase_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_erase_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_erase_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_erase_Statics::BayesianNetwork_eventerase_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_erase()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_erase_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execerase)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->erase(Z_Param_variable);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function erase

// Begin Class UBayesianNetwork Function eraseAllEvidence
struct Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "eraseAllEvidence" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "eraseAllEvidence", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execeraseAllEvidence)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->eraseAllEvidence();
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function eraseAllEvidence

// Begin Class UBayesianNetwork Function eraseEvidence
struct Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics
{
	struct BayesianNetwork_eventeraseEvidence_Parms
	{
		FString variable;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "eraseEvidence" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventeraseEvidence_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::NewProp_variable,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "eraseEvidence", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::BayesianNetwork_eventeraseEvidence_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::BayesianNetwork_eventeraseEvidence_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_eraseEvidence()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execeraseEvidence)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->eraseEvidence(Z_Param_variable);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function eraseEvidence

// Begin Class UBayesianNetwork Function fillWith
struct Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics
{
	struct BayesianNetwork_eventfillWith_Parms
	{
		FString variable;
		float value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "fillWith" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventfillWith_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventfillWith_Parms, value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::NewProp_variable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::NewProp_value,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "fillWith", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::BayesianNetwork_eventfillWith_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::BayesianNetwork_eventfillWith_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_fillWith()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execfillWith)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_GET_PROPERTY(FFloatProperty,Z_Param_value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->fillWith(Z_Param_variable,Z_Param_value);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function fillWith

// Begin Class UBayesianNetwork Function getEntropy
struct Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics
{
	struct BayesianNetwork_eventgetEntropy_Parms
	{
		FString variable;
		double ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "getEntropy" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventgetEntropy_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventgetEntropy_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::NewProp_variable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "getEntropy", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::BayesianNetwork_eventgetEntropy_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::BayesianNetwork_eventgetEntropy_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_getEntropy()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execgetEntropy)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(double*)Z_Param__Result=P_THIS->getEntropy(Z_Param_variable);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function getEntropy

// Begin Class UBayesianNetwork Function getMarkovBlanketNodes
struct Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics
{
	struct BayesianNetwork_eventgetMarkovBlanketNodes_Parms
	{
		FString variable;
		TArray<FString> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "getMarkovBlanketNodes" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventgetMarkovBlanketNodes_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventgetMarkovBlanketNodes_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::NewProp_variable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "getMarkovBlanketNodes", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::BayesianNetwork_eventgetMarkovBlanketNodes_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::BayesianNetwork_eventgetMarkovBlanketNodes_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execgetMarkovBlanketNodes)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FString>*)Z_Param__Result=P_THIS->getMarkovBlanketNodes(Z_Param_variable);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function getMarkovBlanketNodes

// Begin Class UBayesianNetwork Function getPosterior
struct Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics
{
	struct BayesianNetwork_eventgetPosterior_Parms
	{
		FString variable;
		TMap<FString,float> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "evidences" },
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "getPosterior" },
		{ "Keywords", "Inference" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventgetPosterior_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue_ValueProp = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue_Key_KeyProp = { "ReturnValue_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventgetPosterior_Parms, ReturnValue), EMapPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_variable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "getPosterior", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::BayesianNetwork_eventgetPosterior_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::BayesianNetwork_eventgetPosterior_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_getPosterior()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execgetPosterior)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TMap<FString,float>*)Z_Param__Result=P_THIS->getPosterior(Z_Param_variable);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function getPosterior

// Begin Class UBayesianNetwork Function idFromName
struct Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics
{
	struct BayesianNetwork_eventidFromName_Parms
	{
		FString variable;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "idFromName" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_variable;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventidFromName_Parms, variable), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventidFromName_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::NewProp_variable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "idFromName", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::BayesianNetwork_eventidFromName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::BayesianNetwork_eventidFromName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_idFromName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execidFromName)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_variable);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=P_THIS->idFromName(Z_Param_variable);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function idFromName

// Begin Class UBayesianNetwork Function Init
struct Z_Construct_UFunction_UBayesianNetwork_Init_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "Init" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_Init_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "Init", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_Init_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_Init_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UBayesianNetwork_Init()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_Init_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execInit)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Init();
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function Init

// Begin Class UBayesianNetwork Function makeInference
struct Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "evidences" },
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "makeInference" },
		{ "Keywords", "Inference" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "makeInference", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_UBayesianNetwork_makeInference()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execmakeInference)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->makeInference();
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function makeInference

// Begin Class UBayesianNetwork Function writeBIF
struct Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics
{
	struct BayesianNetwork_eventwriteBIF_Parms
	{
		FString file;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "writeBIF" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_file;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::NewProp_file = { "file", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(BayesianNetwork_eventwriteBIF_Parms, file), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::NewProp_file,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "writeBIF", nullptr, nullptr, Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::PropPointers), sizeof(Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::BayesianNetwork_eventwriteBIF_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::Function_MetaDataParams), Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::BayesianNetwork_eventwriteBIF_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UBayesianNetwork_writeBIF()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UBayesianNetwork::execwriteBIF)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_file);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->writeBIF(Z_Param_file);
	P_NATIVE_END;
}
// End Class UBayesianNetwork Function writeBIF

// Begin Class UBayesianNetwork
void UBayesianNetwork::StaticRegisterNativesUBayesianNetwork()
{
	UClass* Class = UBayesianNetwork::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "addArc", &UBayesianNetwork::execaddArc },
		{ "addDiscretizedVariable", &UBayesianNetwork::execaddDiscretizedVariable },
		{ "addEvidence", &UBayesianNetwork::execaddEvidence },
		{ "addLabelizedVariable", &UBayesianNetwork::execaddLabelizedVariable },
		{ "erase", &UBayesianNetwork::execerase },
		{ "eraseAllEvidence", &UBayesianNetwork::execeraseAllEvidence },
		{ "eraseEvidence", &UBayesianNetwork::execeraseEvidence },
		{ "fillWith", &UBayesianNetwork::execfillWith },
		{ "getEntropy", &UBayesianNetwork::execgetEntropy },
		{ "getMarkovBlanketNodes", &UBayesianNetwork::execgetMarkovBlanketNodes },
		{ "getPosterior", &UBayesianNetwork::execgetPosterior },
		{ "idFromName", &UBayesianNetwork::execidFromName },
		{ "Init", &UBayesianNetwork::execInit },
		{ "makeInference", &UBayesianNetwork::execmakeInference },
		{ "writeBIF", &UBayesianNetwork::execwriteBIF },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBayesianNetwork);
UClass* Z_Construct_UClass_UBayesianNetwork_NoRegister()
{
	return UBayesianNetwork::StaticClass();
}
struct Z_Construct_UClass_UBayesianNetwork_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "BayesianNetwork.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_serializedNodes_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_nodeNames_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_nodeDescriptions_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_arcs_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InferenceAlgorithm_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_serializedNodes_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_serializedNodes;
	static const UECodeGen_Private::FStrPropertyParams NewProp_nodeNames_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_nodeNames;
	static const UECodeGen_Private::FStrPropertyParams NewProp_nodeDescriptions_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_nodeDescriptions_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_nodeDescriptions;
	static const UECodeGen_Private::FStrPropertyParams NewProp_arcs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_arcs;
	static const UECodeGen_Private::FBytePropertyParams NewProp_InferenceAlgorithm_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_InferenceAlgorithm;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UBayesianNetwork_addArc, "addArc" }, // 3735489808
		{ &Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable, "addDiscretizedVariable" }, // 1956013269
		{ &Z_Construct_UFunction_UBayesianNetwork_addEvidence, "addEvidence" }, // 2590928149
		{ &Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable, "addLabelizedVariable" }, // 4197049394
		{ &Z_Construct_UFunction_UBayesianNetwork_erase, "erase" }, // 1256025515
		{ &Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence, "eraseAllEvidence" }, // 3503794271
		{ &Z_Construct_UFunction_UBayesianNetwork_eraseEvidence, "eraseEvidence" }, // 66857581
		{ &Z_Construct_UFunction_UBayesianNetwork_fillWith, "fillWith" }, // 1831234820
		{ &Z_Construct_UFunction_UBayesianNetwork_getEntropy, "getEntropy" }, // 26947658
		{ &Z_Construct_UFunction_UBayesianNetwork_getMarkovBlanketNodes, "getMarkovBlanketNodes" }, // 3031062408
		{ &Z_Construct_UFunction_UBayesianNetwork_getPosterior, "getPosterior" }, // 4008955903
		{ &Z_Construct_UFunction_UBayesianNetwork_idFromName, "idFromName" }, // 1292974926
		{ &Z_Construct_UFunction_UBayesianNetwork_Init, "Init" }, // 2178159713
		{ &Z_Construct_UFunction_UBayesianNetwork_makeInference, "makeInference" }, // 566863579
		{ &Z_Construct_UFunction_UBayesianNetwork_writeBIF, "writeBIF" }, // 1789635343
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBayesianNetwork>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes_Inner = { "serializedNodes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBayesianNodeStruct, METADATA_PARAMS(0, nullptr) }; // 2808211742
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes = { "serializedNodes", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBayesianNetwork, serializedNodes), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_serializedNodes_MetaData), NewProp_serializedNodes_MetaData) }; // 2808211742
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames_Inner = { "nodeNames", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames = { "nodeNames", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBayesianNetwork, nodeNames), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_nodeNames_MetaData), NewProp_nodeNames_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_ValueProp = { "nodeDescriptions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_Key_KeyProp = { "nodeDescriptions_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions = { "nodeDescriptions", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBayesianNetwork, nodeDescriptions), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_nodeDescriptions_MetaData), NewProp_nodeDescriptions_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs_Inner = { "arcs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs = { "arcs", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBayesianNetwork, arcs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_arcs_MetaData), NewProp_arcs_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm = { "InferenceAlgorithm", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBayesianNetwork, InferenceAlgorithm), Z_Construct_UEnum_FANTASIA_InferenceAlgs, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InferenceAlgorithm_MetaData), NewProp_InferenceAlgorithm_MetaData) }; // 1973515391
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBayesianNetwork_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UBayesianNetwork_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBayesianNetwork_Statics::ClassParams = {
	&UBayesianNetwork::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UBayesianNetwork_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::Class_MetaDataParams), Z_Construct_UClass_UBayesianNetwork_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBayesianNetwork()
{
	if (!Z_Registration_Info_UClass_UBayesianNetwork.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBayesianNetwork.OuterSingleton, Z_Construct_UClass_UBayesianNetwork_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBayesianNetwork.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UBayesianNetwork>()
{
	return UBayesianNetwork::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBayesianNetwork);
UBayesianNetwork::~UBayesianNetwork() {}
// End Class UBayesianNetwork

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ InferenceAlgs_StaticEnum, TEXT("InferenceAlgs"), &Z_Registration_Info_UEnum_InferenceAlgs, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1973515391U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FMapContainer::StaticStruct, Z_Construct_UScriptStruct_FMapContainer_Statics::NewStructOps, TEXT("MapContainer"), &Z_Registration_Info_UScriptStruct_MapContainer, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMapContainer), 1111572595U) },
		{ FBayesianArcStruct::StaticStruct, Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewStructOps, TEXT("BayesianArcStruct"), &Z_Registration_Info_UScriptStruct_BayesianArcStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBayesianArcStruct), 434484602U) },
		{ FBayesianNodeStruct::StaticStruct, Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewStructOps, TEXT("BayesianNodeStruct"), &Z_Registration_Info_UScriptStruct_BayesianNodeStruct, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBayesianNodeStruct), 2808211742U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBayesianNetwork, UBayesianNetwork::StaticClass, TEXT("UBayesianNetwork"), &Z_Registration_Info_UClass_UBayesianNetwork, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBayesianNetwork), 1895330121U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_3761884675(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Bastian_Plugins_FANTASIA_Source_FANTASIA_Public_BayesianNetwork_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
