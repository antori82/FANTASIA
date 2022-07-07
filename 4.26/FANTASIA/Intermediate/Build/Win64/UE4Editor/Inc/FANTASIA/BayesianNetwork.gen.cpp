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
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_InferenceAlgs();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FBayesianNodeStruct();
	FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetworkFactory_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetworkFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetwork_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UBayesianNetwork();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
// End Cross Module References
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
	uint32 Get_Z_Construct_UEnum_FANTASIA_InferenceAlgs_Hash() { return 2633522605U; }
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
				{ "Comment", "/* \n*\x09""Function library class.\n*\x09""Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.\n*\n*\x09When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.\n*\x09""BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.\n*\x09""BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.\n*\x09""DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.\n*\x09\x09\x09\x09Its lets you name the node using characters not allowed in C++ function names.\n*\x09""CompactNodeTitle - the word(s) that appear on the node.\n*\x09Keywords -\x09the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. \n*\x09\x09\x09\x09Good example is \"Print String\" node which you can find also by using keyword \"log\".\n*\x09""Category -\x09the category your node will be under in the Blueprint drop-down menu.\n*\n*\x09""For more info on custom blueprint nodes visit documentation:\n*\x09https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation\n*///\"BlueprintType\" is essential to include\n" },
				{ "Lazy_Propagation.DisplayName", "Lazy Propagation" },
				{ "Lazy_Propagation.Name", "InferenceAlgs::Lazy_Propagation" },
				{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
				{ "ShaferShenoy.DisplayName", "Shafer Shenoy Inference" },
				{ "ShaferShenoy.Name", "InferenceAlgs::ShaferShenoy" },
				{ "ToolTip", "*      Function library class.\n*      Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.\n*\n*      When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.\n*      BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.\n*      BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.\n*      DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.\n*                              Its lets you name the node using characters not allowed in C++ function names.\n*      CompactNodeTitle - the word(s) that appear on the node.\n*      Keywords -      the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu.\n*                              Good example is \"Print String\" node which you can find also by using keyword \"log\".\n*      Category -      the category your node will be under in the Blueprint drop-down menu.\n*\n*      For more info on custom blueprint nodes visit documentation:\n*      https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation\n//\"BlueprintType\" is essential to include" },
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
		UScriptStruct::DeferCppStructOps(FName(TEXT("BayesianNodeStruct")),new UScriptStruct::TCppStructOps<FBayesianNodeStruct>);
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
			{ "addEvidence", &UBayesianNetwork::execaddEvidence },
			{ "eraseAllEvidence", &UBayesianNetwork::execeraseAllEvidence },
			{ "eraseEvidence", &UBayesianNetwork::execeraseEvidence },
			{ "getEntropy", &UBayesianNetwork::execgetEntropy },
			{ "getPosterior", &UBayesianNetwork::execgetPosterior },
			{ "Init", &UBayesianNetwork::execInit },
			{ "makeInference", &UBayesianNetwork::execmakeInference },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
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
		{ "DisplayName", "addEvidence" },
		{ "ModuleRelativePath", "Public/BayesianNetwork.h" },
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
		{ &Z_Construct_UFunction_UBayesianNetwork_addEvidence, "addEvidence" }, // 3564293755
		{ &Z_Construct_UFunction_UBayesianNetwork_eraseAllEvidence, "eraseAllEvidence" }, // 2093652136
		{ &Z_Construct_UFunction_UBayesianNetwork_eraseEvidence, "eraseEvidence" }, // 4194899472
		{ &Z_Construct_UFunction_UBayesianNetwork_getEntropy, "getEntropy" }, // 1200467684
		{ &Z_Construct_UFunction_UBayesianNetwork_getPosterior, "getPosterior" }, // 3055596965
		{ &Z_Construct_UFunction_UBayesianNetwork_Init, "Init" }, // 1820514527
		{ &Z_Construct_UFunction_UBayesianNetwork_makeInference, "makeInference" }, // 3600683198
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
	IMPLEMENT_CLASS(UBayesianNetwork, 188889509);
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
