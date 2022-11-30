// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/BayesianNetwork.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBayesianNetwork() {}
// Cross Module References
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FMapContainer();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_InferenceAlgs();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FBayesianNodeStruct();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FBayesianArcStruct();
	FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetworkFactory_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetworkFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetwork_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetwork();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_BayesianNodeType();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventGetPosteriorDelegate_Parms
		{
			FMapContainer outMap;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_outMap;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::NewProp_outMap = { "outMap", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_FANTASIA_eventGetPosteriorDelegate_Parms, outMap), Z_Construct_UScriptStruct_FMapContainer, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::NewProp_outMap,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "GetPosteriorDelegate__DelegateSignature", nullptr, nullptr, sizeof(_Script_FANTASIA_eventGetPosteriorDelegate_Parms), Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static UEnum* InferenceAlgs_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_InferenceAlgs, Z_Construct_UPackage__Script_FANTASIA(), TEXT("InferenceAlgs"));
		}
		return Singleton;
	}
	template<> FANTASIA_API UEnum* StaticEnum<InferenceAlgs>()
	{
		return InferenceAlgs_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_InferenceAlgs(InferenceAlgs_StaticEnum, TEXT("/Script/FANTASIA"), TEXT("InferenceAlgs"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_FANTASIA_InferenceAlgs_Hash() { return 1605103096U; }
	UEnum* Z_Construct_UEnum_FANTASIA_InferenceAlgs()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("InferenceAlgs"), 0, Get_Z_Construct_UEnum_FANTASIA_InferenceAlgs_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "InferenceAlgs::Lazy_Propagation", (int64)InferenceAlgs::Lazy_Propagation },
				{ "InferenceAlgs::ShaferShenoy", (int64)InferenceAlgs::ShaferShenoy },
				{ "InferenceAlgs::VariableElimination", (int64)InferenceAlgs::VariableElimination },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Comment", "//\"BlueprintType\" is essential to include\n" },
				{ "Lazy_Propagation.DisplayName", "Lazy Propagation" },
				{ "Lazy_Propagation.Name", "InferenceAlgs::Lazy_Propagation" },
				{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
				{ "ShaferShenoy.DisplayName", "Shafer Shenoy Inference" },
				{ "ShaferShenoy.Name", "InferenceAlgs::ShaferShenoy" },
				{ "ToolTip", "\"BlueprintType\" is essential to include" },
				{ "VariableElimination.DisplayName", "Variable Elimination" },
				{ "VariableElimination.Name", "InferenceAlgs::VariableElimination" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
				nullptr,
				"InferenceAlgs",
				"InferenceAlgs",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FBayesianNodeStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FANTASIA_API uint32 Get_Z_Construct_UScriptStruct_FBayesianNodeStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBayesianNodeStruct, Z_Construct_UPackage__Script_FANTASIA(), TEXT("BayesianNodeStruct"), sizeof(FBayesianNodeStruct), Get_Z_Construct_UScriptStruct_FBayesianNodeStruct_Hash());
	}
	return Singleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FBayesianNodeStruct>()
{
	return FBayesianNodeStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBayesianNodeStruct(FBayesianNodeStruct::StaticStruct, TEXT("/Script/FANTASIA"), TEXT("BayesianNodeStruct"), false, nullptr, nullptr);
static struct FScriptStruct_FANTASIA_StaticRegisterNativesFBayesianNodeStruct
{
	FScriptStruct_FANTASIA_StaticRegisterNativesFBayesianNodeStruct()
	{
		UScriptStruct::DeferCppStructOps<FBayesianNodeStruct>(FName(TEXT("BayesianNodeStruct")));
	}
} ScriptStruct_FANTASIA_StaticRegisterNativesFBayesianNodeStruct;
	struct Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_name_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_name;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variables_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_variables_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_variables;
		static const UE4CodeGen_Private::FDoublePropertyParams NewProp_values_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_values_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_values;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_parents_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_parents_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_parents;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBayesianNodeStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_name_MetaData[] = {
		{ "Category", "BayesianNodeStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_name = { "name", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBayesianNodeStruct, name), METADATA_PARAMS(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_name_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_name_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables_Inner = { "variables", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables_MetaData[] = {
		{ "Category", "BayesianNodeStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables = { "variables", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBayesianNodeStruct, variables), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables_MetaData)) };
	const UE4CodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values_Inner = { "values", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values_MetaData[] = {
		{ "Category", "BayesianNodeStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values = { "values", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBayesianNodeStruct, values), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents_Inner = { "parents", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents_MetaData[] = {
		{ "Category", "BayesianNodeStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents = { "parents", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBayesianNodeStruct, parents), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_name,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_variables,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_values,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::NewProp_parents,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"BayesianNodeStruct",
		sizeof(FBayesianNodeStruct),
		alignof(FBayesianNodeStruct),
		Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FBayesianNodeStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FBayesianNodeStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BayesianNodeStruct"), sizeof(FBayesianNodeStruct), Get_Z_Construct_UScriptStruct_FBayesianNodeStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FBayesianNodeStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBayesianNodeStruct_Hash() { return 1502270943U; }
class UScriptStruct* FBayesianArcStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FANTASIA_API uint32 Get_Z_Construct_UScriptStruct_FBayesianArcStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBayesianArcStruct, Z_Construct_UPackage__Script_FANTASIA(), TEXT("BayesianArcStruct"), sizeof(FBayesianArcStruct), Get_Z_Construct_UScriptStruct_FBayesianArcStruct_Hash());
	}
	return Singleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FBayesianArcStruct>()
{
	return FBayesianArcStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBayesianArcStruct(FBayesianArcStruct::StaticStruct, TEXT("/Script/FANTASIA"), TEXT("BayesianArcStruct"), false, nullptr, nullptr);
static struct FScriptStruct_FANTASIA_StaticRegisterNativesFBayesianArcStruct
{
	FScriptStruct_FANTASIA_StaticRegisterNativesFBayesianArcStruct()
	{
		UScriptStruct::DeferCppStructOps<FBayesianArcStruct>(FName(TEXT("BayesianArcStruct")));
	}
} ScriptStruct_FANTASIA_StaticRegisterNativesFBayesianArcStruct;
	struct Z_Construct_UScriptStruct_FBayesianArcStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Tail_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Tail;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Head_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Head;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBayesianArcStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Tail_MetaData[] = {
		{ "Category", "BayesianArcStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Tail = { "Tail", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBayesianArcStruct, Tail), METADATA_PARAMS(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Tail_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Tail_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Head_MetaData[] = {
		{ "Category", "BayesianArcStruct" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Head = { "Head", nullptr, (EPropertyFlags)0x0010000000000005, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBayesianArcStruct, Head), METADATA_PARAMS(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Head_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Head_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Tail,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::NewProp_Head,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"BayesianArcStruct",
		sizeof(FBayesianArcStruct),
		alignof(FBayesianArcStruct),
		Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FBayesianArcStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FBayesianArcStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BayesianArcStruct"), sizeof(FBayesianArcStruct), Get_Z_Construct_UScriptStruct_FBayesianArcStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FBayesianArcStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBayesianArcStruct_Hash() { return 2366025974U; }
class UScriptStruct* FMapContainer::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern FANTASIA_API uint32 Get_Z_Construct_UScriptStruct_FMapContainer_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FMapContainer, Z_Construct_UPackage__Script_FANTASIA(), TEXT("MapContainer"), sizeof(FMapContainer), Get_Z_Construct_UScriptStruct_FMapContainer_Hash());
	}
	return Singleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FMapContainer>()
{
	return FMapContainer::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FMapContainer(FMapContainer::StaticStruct, TEXT("/Script/FANTASIA"), TEXT("MapContainer"), false, nullptr, nullptr);
static struct FScriptStruct_FANTASIA_StaticRegisterNativesFMapContainer
{
	FScriptStruct_FANTASIA_StaticRegisterNativesFMapContainer()
	{
		UScriptStruct::DeferCppStructOps<FMapContainer>(FName(TEXT("MapContainer")));
	}
} ScriptStruct_FANTASIA_StaticRegisterNativesFMapContainer;
	struct Z_Construct_UScriptStruct_FMapContainer_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_Map_ValueProp;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Map_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Map_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_Map;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMapContainer_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FMapContainer_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMapContainer>();
	}
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_ValueProp = { "Map", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_Key_KeyProp = { "Map_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_MetaData[] = {
		{ "Category", "MapContainer" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map = { "Map", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMapContainer, Map), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMapContainer_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMapContainer_Statics::NewProp_Map,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMapContainer_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"MapContainer",
		sizeof(FMapContainer),
		alignof(FMapContainer),
		Z_Construct_UScriptStruct_FMapContainer_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapContainer_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FMapContainer_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMapContainer_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FMapContainer()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FMapContainer_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_FANTASIA();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("MapContainer"), sizeof(FMapContainer), Get_Z_Construct_UScriptStruct_FMapContainer_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FMapContainer_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FMapContainer_Hash() { return 1785446579U; }
	void UBayesianNetworkFactory::StaticRegisterNativesUBayesianNetworkFactory()
	{
	}
	UClass* Z_Construct_UClass_UBayesianNetworkFactory_NoRegister()
	{
		return UBayesianNetworkFactory::StaticClass();
	}
	struct Z_Construct_UClass_UBayesianNetworkFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBayesianNetworkFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBayesianNetworkFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BayesianNetwork.h" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBayesianNetworkFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBayesianNetworkFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBayesianNetworkFactory_Statics::ClassParams = {
		&UBayesianNetworkFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UBayesianNetworkFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetworkFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBayesianNetworkFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBayesianNetworkFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBayesianNetworkFactory, 3183469238);
	template<> FANTASIA_API UClass* StaticClass<UBayesianNetworkFactory>()
	{
		return UBayesianNetworkFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBayesianNetworkFactory(Z_Construct_UClass_UBayesianNetworkFactory, &UBayesianNetworkFactory::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UBayesianNetworkFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBayesianNetworkFactory);
	DEFINE_FUNCTION(UBayesianNetwork::execidFromName)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_variable);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->idFromName(Z_Param_variable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBayesianNetwork::execerase)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_variable);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->erase(Z_Param_variable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBayesianNetwork::execwriteBIF)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_file);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->writeBIF(Z_Param_file);
		P_NATIVE_END;
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
	DEFINE_FUNCTION(UBayesianNetwork::execaddArc)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_parent);
		P_GET_PROPERTY(FStrProperty,Z_Param_child);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->addArc(Z_Param_parent,Z_Param_child);
		P_NATIVE_END;
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
	DEFINE_FUNCTION(UBayesianNetwork::execgetEntropy)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_variable);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->getEntropy(Z_Param_variable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBayesianNetwork::execeraseEvidence)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_variable);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->eraseEvidence(Z_Param_variable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBayesianNetwork::execeraseAllEvidence)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->eraseAllEvidence();
		P_NATIVE_END;
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
	DEFINE_FUNCTION(UBayesianNetwork::execgetPosterior)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_variable);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TMap<FString,float>*)Z_Param__Result=P_THIS->getPosterior(Z_Param_variable);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBayesianNetwork::execmakeInference)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->makeInference();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UBayesianNetwork::execInit)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Init();
		P_NATIVE_END;
	}
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
			{ "getPosterior", &UBayesianNetwork::execgetPosterior },
			{ "idFromName", &UBayesianNetwork::execidFromName },
			{ "Init", &UBayesianNetwork::execInit },
			{ "makeInference", &UBayesianNetwork::execmakeInference },
			{ "writeBIF", &UBayesianNetwork::execwriteBIF },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UBayesianNetwork_addArc_Statics
	{
		struct BayesianNetwork_eventaddArc_Parms
		{
			FString parent;
			FString child;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_parent;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_child;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::NewProp_parent = { "parent", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddArc_Parms, parent), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::NewProp_child = { "child", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddArc_Parms, child), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::NewProp_parent,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::NewProp_child,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "addArc" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "addArc", nullptr, nullptr, sizeof(BayesianNetwork_eventaddArc_Parms), Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_addArc()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_addArc_Statics::FuncParams);
		}
		return ReturnFunction;
	}
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
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_description;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_minTick;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_maxTick;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_nPoints;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_nodeType_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_nodeType;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_description = { "description", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, description), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_minTick = { "minTick", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, minTick), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_maxTick = { "maxTick", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, maxTick), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nPoints = { "nPoints", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, nPoints), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nodeType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nodeType = { "nodeType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddDiscretizedVariable_Parms, nodeType), Z_Construct_UEnum_FANTASIA_BayesianNodeType, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_variable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_description,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_minTick,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_maxTick,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nPoints,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nodeType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::NewProp_nodeType,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "addDiscretizedVariable" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "addDiscretizedVariable", nullptr, nullptr, sizeof(BayesianNetwork_eventaddDiscretizedVariable_Parms), Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics
	{
		struct BayesianNetwork_eventaddEvidence_Parms
		{
			FString variable;
			TArray<float> data;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_data_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_data;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddEvidence_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_data_Inner = { "data", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_data = { "data", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddEvidence_Parms, data), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_variable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_data_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::NewProp_data,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "Comment", "//UFUNCTION(BlueprintCallable, meta = (DisplayName = \"getPosterior\", Keywords = \"Inference\", AutoCreateRefTerm = \"evidences\"), Category = \"Bayesian_Network\")\n//void getPosterior(FGetPosteriorDelegate outMap, FString variable);\n" },
		{ "DisplayName", "addEvidence" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
		{ "ToolTip", "UFUNCTION(BlueprintCallable, meta = (DisplayName = \"getPosterior\", Keywords = \"Inference\", AutoCreateRefTerm = \"evidences\"), Category = \"Bayesian_Network\")\nvoid getPosterior(FGetPosteriorDelegate outMap, FString variable);" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "addEvidence", nullptr, nullptr, sizeof(BayesianNetwork_eventaddEvidence_Parms), Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_addEvidence()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_addEvidence_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics
	{
		struct BayesianNetwork_eventaddLabelizedVariable_Parms
		{
			FString variable;
			FString description;
			TArray<FString> labels;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_description;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_labels_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_labels;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddLabelizedVariable_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_description = { "description", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddLabelizedVariable_Parms, description), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_labels_Inner = { "labels", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_labels = { "labels", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventaddLabelizedVariable_Parms, labels), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_variable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_description,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_labels_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::NewProp_labels,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "addLabelizedVariable" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "addLabelizedVariable", nullptr, nullptr, sizeof(BayesianNetwork_eventaddLabelizedVariable_Parms), Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_erase_Statics
	{
		struct BayesianNetwork_eventerase_Parms
		{
			FString variable;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_erase_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventerase_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_erase_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_erase_Statics::NewProp_variable,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_erase_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "clear" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_erase_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "erase", nullptr, nullptr, sizeof(BayesianNetwork_eventerase_Parms), Z_Construct_UFunction_UBayesianNetwork_erase_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_erase_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_erase_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_erase_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_erase()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_erase_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "eraseAllEvidence" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "eraseAllEvidence", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics
	{
		struct BayesianNetwork_eventeraseEvidence_Parms
		{
			FString variable;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventeraseEvidence_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::NewProp_variable,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "eraseEvidence" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "eraseEvidence", nullptr, nullptr, sizeof(BayesianNetwork_eventeraseEvidence_Parms), Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_eraseEvidence()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_eraseEvidence_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics
	{
		struct BayesianNetwork_eventfillWith_Parms
		{
			FString variable;
			float value;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_value;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventfillWith_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::NewProp_value = { "value", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventfillWith_Parms, value), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::NewProp_variable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::NewProp_value,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "fillWith" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "fillWith", nullptr, nullptr, sizeof(BayesianNetwork_eventfillWith_Parms), Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_fillWith()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_fillWith_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics
	{
		struct BayesianNetwork_eventgetEntropy_Parms
		{
			FString variable;
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventgetEntropy_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventgetEntropy_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::NewProp_variable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "getEntropy" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "getEntropy", nullptr, nullptr, sizeof(BayesianNetwork_eventgetEntropy_Parms), Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_getEntropy()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_getEntropy_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics
	{
		struct BayesianNetwork_eventgetPosterior_Parms
		{
			FString variable;
			TMap<FString,float> ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_ValueProp;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Key_KeyProp;
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventgetPosterior_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue_ValueProp = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue_Key_KeyProp = { "ReturnValue_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventgetPosterior_Parms, ReturnValue), EMapPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_variable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "evidences" },
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "getPosterior" },
		{ "Keywords", "Inference" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "getPosterior", nullptr, nullptr, sizeof(BayesianNetwork_eventgetPosterior_Parms), Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_getPosterior()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_getPosterior_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics
	{
		struct BayesianNetwork_eventidFromName_Parms
		{
			FString variable;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_variable;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::NewProp_variable = { "variable", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventidFromName_Parms, variable), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventidFromName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::NewProp_variable,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "idFromName" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "idFromName", nullptr, nullptr, sizeof(BayesianNetwork_eventidFromName_Parms), Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_idFromName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_idFromName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_Init_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_Init_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "Init" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_Init_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "Init", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_Init_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_Init_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_Init()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_Init_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "evidences" },
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "makeInference" },
		{ "Keywords", "Inference" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "makeInference", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_makeInference()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_makeInference_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics
	{
		struct BayesianNetwork_eventwriteBIF_Parms
		{
			FString file;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_file;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::NewProp_file = { "file", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(BayesianNetwork_eventwriteBIF_Parms, file), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::NewProp_file,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::Function_MetaDataParams[] = {
		{ "Category", "Bayesian_Network" },
		{ "DisplayName", "writeBIF" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UBayesianNetwork, nullptr, "writeBIF", nullptr, nullptr, sizeof(BayesianNetwork_eventwriteBIF_Parms), Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UBayesianNetwork_writeBIF()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UBayesianNetwork_writeBIF_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UBayesianNetwork_NoRegister()
	{
		return UBayesianNetwork::StaticClass();
	}
	struct Z_Construct_UClass_UBayesianNetwork_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_serializedNodes_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_serializedNodes_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_serializedNodes;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_nodeNames_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_nodeNames_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_nodeNames;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_nodeDescriptions_ValueProp;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_nodeDescriptions_Key_KeyProp;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_nodeDescriptions_MetaData[];
#endif
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_nodeDescriptions;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_arcs_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_arcs_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_arcs;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_InferenceAlgorithm_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_InferenceAlgorithm_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_InferenceAlgorithm;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBayesianNetwork_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UBayesianNetwork_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UBayesianNetwork_addArc, "addArc" }, // 3453882800
		{ &Z_Construct_UFunction_UBayesianNetwork_addDiscretizedVariable, "addDiscretizedVariable" }, // 2740838583
		{ &Z_Construct_UFunction_UBayesianNetwork_addEvidence, "addEvidence" }, // 8261208
		{ &Z_Construct_UFunction_UBayesianNetwork_addLabelizedVariable, "addLabelizedVariable" }, // 3736316974
		{ &Z_Construct_UFunction_UBayesianNetwork_erase, "erase" }, // 1859394010
		{ &Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence, "eraseAllEvidence" }, // 2093652136
		{ &Z_Construct_UFunction_UBayesianNetwork_eraseEvidence, "eraseEvidence" }, // 4194899472
		{ &Z_Construct_UFunction_UBayesianNetwork_fillWith, "fillWith" }, // 2756832431
		{ &Z_Construct_UFunction_UBayesianNetwork_getEntropy, "getEntropy" }, // 1200467684
		{ &Z_Construct_UFunction_UBayesianNetwork_getPosterior, "getPosterior" }, // 3055596965
		{ &Z_Construct_UFunction_UBayesianNetwork_idFromName, "idFromName" }, // 2836174964
		{ &Z_Construct_UFunction_UBayesianNetwork_Init, "Init" }, // 1820514527
		{ &Z_Construct_UFunction_UBayesianNetwork_makeInference, "makeInference" }, // 3600683198
		{ &Z_Construct_UFunction_UBayesianNetwork_writeBIF, "writeBIF" }, // 2242126481
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBayesianNetwork_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "BayesianNetwork.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes_Inner = { "serializedNodes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FBayesianNodeStruct, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes = { "serializedNodes", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBayesianNetwork, serializedNodes), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames_Inner = { "nodeNames", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames = { "nodeNames", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBayesianNetwork, nodeNames), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_ValueProp = { "nodeDescriptions", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_Key_KeyProp = { "nodeDescriptions_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions = { "nodeDescriptions", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBayesianNetwork, nodeDescriptions), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_MetaData)) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs_Inner = { "arcs", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs = { "arcs", nullptr, (EPropertyFlags)0x0010000000000014, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBayesianNetwork, arcs), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm_MetaData[] = {
		{ "Category", "BayesianNetwork" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm = { "InferenceAlgorithm", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UBayesianNetwork, InferenceAlgorithm), Z_Construct_UEnum_FANTASIA_InferenceAlgs, METADATA_PARAMS(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBayesianNetwork_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_serializedNodes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeNames,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_nodeDescriptions,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_arcs,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBayesianNetwork_Statics::NewProp_InferenceAlgorithm,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBayesianNetwork_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBayesianNetwork>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UBayesianNetwork_Statics::ClassParams = {
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
		METADATA_PARAMS(Z_Construct_UClass_UBayesianNetwork_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetwork_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UBayesianNetwork()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UBayesianNetwork_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UBayesianNetwork, 1650573633);
	template<> FANTASIA_API UClass* StaticClass<UBayesianNetwork>()
	{
		return UBayesianNetwork::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UBayesianNetwork(Z_Construct_UClass_UBayesianNetwork, &UBayesianNetwork::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UBayesianNetwork"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBayesianNetwork);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
