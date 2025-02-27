// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/LibSVM.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeLibSVM() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
FANTASIA_API UClass* Z_Construct_UClass_ULibSVM();
FANTASIA_API UClass* Z_Construct_UClass_ULibSVM_NoRegister();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_LibSVMKernels();
FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_LibSVMTypes();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FCLFResult();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FCLFSample();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FSVMParameters();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin ScriptStruct FCLFSample
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_CLFSample;
class UScriptStruct* FCLFSample::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_CLFSample.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_CLFSample.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCLFSample, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("CLFSample"));
	}
	return Z_Registration_Info_UScriptStruct_CLFSample.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FCLFSample>()
{
	return FCLFSample::StaticStruct();
}
struct Z_Construct_UScriptStruct_FCLFSample_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sampleID_MetaData[] = {
		{ "Category", "CLFSample" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CLFclass_MetaData[] = {
		{ "Category", "CLFSample" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_features_MetaData[] = {
		{ "Category", "CLFSample" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_sampleID;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_CLFclass;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_features_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_features;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCLFSample>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FCLFSample_Statics::NewProp_sampleID = { "sampleID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCLFSample, sampleID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sampleID_MetaData), NewProp_sampleID_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FCLFSample_Statics::NewProp_CLFclass = { "CLFclass", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCLFSample, CLFclass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CLFclass_MetaData), NewProp_CLFclass_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FCLFSample_Statics::NewProp_features_Inner = { "features", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FCLFSample_Statics::NewProp_features = { "features", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCLFSample, features), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_features_MetaData), NewProp_features_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCLFSample_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCLFSample_Statics::NewProp_sampleID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCLFSample_Statics::NewProp_CLFclass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCLFSample_Statics::NewProp_features_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCLFSample_Statics::NewProp_features,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCLFSample_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCLFSample_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"CLFSample",
	Z_Construct_UScriptStruct_FCLFSample_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCLFSample_Statics::PropPointers),
	sizeof(FCLFSample),
	alignof(FCLFSample),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCLFSample_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FCLFSample_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FCLFSample()
{
	if (!Z_Registration_Info_UScriptStruct_CLFSample.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_CLFSample.InnerSingleton, Z_Construct_UScriptStruct_FCLFSample_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_CLFSample.InnerSingleton;
}
// End ScriptStruct FCLFSample

// Begin ScriptStruct FCLFResult
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_CLFResult;
class UScriptStruct* FCLFResult::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_CLFResult.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_CLFResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCLFResult, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("CLFResult"));
	}
	return Z_Registration_Info_UScriptStruct_CLFResult.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FCLFResult>()
{
	return FCLFResult::StaticStruct();
}
struct Z_Construct_UScriptStruct_FCLFResult_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_sampleID_MetaData[] = {
		{ "Category", "CLFResult" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_probabilities_MetaData[] = {
		{ "Category", "CLFResult" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_sampleID;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_probabilities_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_probabilities;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCLFResult>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FCLFResult_Statics::NewProp_sampleID = { "sampleID", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCLFResult, sampleID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_sampleID_MetaData), NewProp_sampleID_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FCLFResult_Statics::NewProp_probabilities_Inner = { "probabilities", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FCLFResult_Statics::NewProp_probabilities = { "probabilities", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCLFResult, probabilities), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_probabilities_MetaData), NewProp_probabilities_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCLFResult_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCLFResult_Statics::NewProp_sampleID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCLFResult_Statics::NewProp_probabilities_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCLFResult_Statics::NewProp_probabilities,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCLFResult_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCLFResult_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"CLFResult",
	Z_Construct_UScriptStruct_FCLFResult_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCLFResult_Statics::PropPointers),
	sizeof(FCLFResult),
	alignof(FCLFResult),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCLFResult_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FCLFResult_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FCLFResult()
{
	if (!Z_Registration_Info_UScriptStruct_CLFResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_CLFResult.InnerSingleton, Z_Construct_UScriptStruct_FCLFResult_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_CLFResult.InnerSingleton;
}
// End ScriptStruct FCLFResult

// Begin Enum LibSVMTypes
static_assert(!int64(LibSVMTypes::C_SVC)||!int64(LibSVMTypes::NU_SVC)||!int64(LibSVMTypes::ONE_CLASS_SVM)||!int64(LibSVMTypes::EPSILON_SVR)||!int64(LibSVMTypes::NU_SVR), "'LibSVMTypes' does not have a 0 entry!(This is a problem when the enum is initalized by default)");
static FEnumRegistrationInfo Z_Registration_Info_UEnum_LibSVMTypes;
static UEnum* LibSVMTypes_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_LibSVMTypes.OuterSingleton)
	{
		Z_Registration_Info_UEnum_LibSVMTypes.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_LibSVMTypes, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("LibSVMTypes"));
	}
	return Z_Registration_Info_UEnum_LibSVMTypes.OuterSingleton;
}
template<> FANTASIA_API UEnum* StaticEnum<LibSVMTypes>()
{
	return LibSVMTypes_StaticEnum();
}
struct Z_Construct_UEnum_FANTASIA_LibSVMTypes_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "C_SVC.DisplayName", "C-SVC" },
		{ "C_SVC.Name", "LibSVMTypes::C_SVC" },
		{ "EPSILON_SVR.DisplayName", "epsilon-SVR" },
		{ "EPSILON_SVR.Name", "LibSVMTypes::EPSILON_SVR" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
		{ "NU_SVC.DisplayName", "nu-SVC" },
		{ "NU_SVC.Name", "LibSVMTypes::NU_SVC" },
		{ "NU_SVR.DisplayName", "nu-SVR" },
		{ "NU_SVR.Name", "LibSVMTypes::NU_SVR" },
		{ "ONE_CLASS_SVM.DisplayName", "one-class SVM" },
		{ "ONE_CLASS_SVM.Name", "LibSVMTypes::ONE_CLASS_SVM" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "LibSVMTypes::C_SVC", (int64)LibSVMTypes::C_SVC },
		{ "LibSVMTypes::NU_SVC", (int64)LibSVMTypes::NU_SVC },
		{ "LibSVMTypes::ONE_CLASS_SVM", (int64)LibSVMTypes::ONE_CLASS_SVM },
		{ "LibSVMTypes::EPSILON_SVR", (int64)LibSVMTypes::EPSILON_SVR },
		{ "LibSVMTypes::NU_SVR", (int64)LibSVMTypes::NU_SVR },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_LibSVMTypes_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	"LibSVMTypes",
	"LibSVMTypes",
	Z_Construct_UEnum_FANTASIA_LibSVMTypes_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_LibSVMTypes_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_LibSVMTypes_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_LibSVMTypes_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FANTASIA_LibSVMTypes()
{
	if (!Z_Registration_Info_UEnum_LibSVMTypes.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_LibSVMTypes.InnerSingleton, Z_Construct_UEnum_FANTASIA_LibSVMTypes_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_LibSVMTypes.InnerSingleton;
}
// End Enum LibSVMTypes

// Begin Enum LibSVMKernels
static_assert(!int64(LibSVMKernels::LINEAR)||!int64(LibSVMKernels::POLYNOMIAL)||!int64(LibSVMKernels::RBF)||!int64(LibSVMKernels::SIGMOID), "'LibSVMKernels' does not have a 0 entry!(This is a problem when the enum is initalized by default)");
static FEnumRegistrationInfo Z_Registration_Info_UEnum_LibSVMKernels;
static UEnum* LibSVMKernels_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_LibSVMKernels.OuterSingleton)
	{
		Z_Registration_Info_UEnum_LibSVMKernels.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_LibSVMKernels, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("LibSVMKernels"));
	}
	return Z_Registration_Info_UEnum_LibSVMKernels.OuterSingleton;
}
template<> FANTASIA_API UEnum* StaticEnum<LibSVMKernels>()
{
	return LibSVMKernels_StaticEnum();
}
struct Z_Construct_UEnum_FANTASIA_LibSVMKernels_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "LINEAR.DisplayName", "Linear" },
		{ "LINEAR.Name", "LibSVMKernels::LINEAR" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
		{ "POLYNOMIAL.DisplayName", "Polynomial" },
		{ "POLYNOMIAL.Name", "LibSVMKernels::POLYNOMIAL" },
		{ "RBF.DisplayName", "RBF" },
		{ "RBF.Name", "LibSVMKernels::RBF" },
		{ "SIGMOID.DisplayName", "Sigmoid" },
		{ "SIGMOID.Name", "LibSVMKernels::SIGMOID" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "LibSVMKernels::LINEAR", (int64)LibSVMKernels::LINEAR },
		{ "LibSVMKernels::POLYNOMIAL", (int64)LibSVMKernels::POLYNOMIAL },
		{ "LibSVMKernels::RBF", (int64)LibSVMKernels::RBF },
		{ "LibSVMKernels::SIGMOID", (int64)LibSVMKernels::SIGMOID },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_LibSVMKernels_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	"LibSVMKernels",
	"LibSVMKernels",
	Z_Construct_UEnum_FANTASIA_LibSVMKernels_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_LibSVMKernels_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_LibSVMKernels_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_LibSVMKernels_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_FANTASIA_LibSVMKernels()
{
	if (!Z_Registration_Info_UEnum_LibSVMKernels.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_LibSVMKernels.InnerSingleton, Z_Construct_UEnum_FANTASIA_LibSVMKernels_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_LibSVMKernels.InnerSingleton;
}
// End Enum LibSVMKernels

// Begin ScriptStruct FSVMParameters
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_SVMParameters;
class UScriptStruct* FSVMParameters::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_SVMParameters.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_SVMParameters.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FSVMParameters, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("SVMParameters"));
	}
	return Z_Registration_Info_UScriptStruct_SVMParameters.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FSVMParameters>()
{
	return FSVMParameters::StaticStruct();
}
struct Z_Construct_UScriptStruct_FSVMParameters_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SVMType_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_KernelType_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_C_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_gamma_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_degree_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_coef0_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_nu_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_svrEpsilon_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_cachesize_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_epsilon_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_shrinking_MetaData[] = {
		{ "Category", "SVMParameters" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_SVMType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_SVMType;
	static const UECodeGen_Private::FBytePropertyParams NewProp_KernelType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_KernelType;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_C;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_gamma;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_degree;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_coef0;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_nu;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_svrEpsilon;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_cachesize;
	static const UECodeGen_Private::FDoublePropertyParams NewProp_epsilon;
	static void NewProp_shrinking_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_shrinking;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSVMParameters>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_SVMType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_SVMType = { "SVMType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, SVMType), Z_Construct_UEnum_FANTASIA_LibSVMTypes, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SVMType_MetaData), NewProp_SVMType_MetaData) }; // 1580382862
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_KernelType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_KernelType = { "KernelType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, KernelType), Z_Construct_UEnum_FANTASIA_LibSVMKernels, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_KernelType_MetaData), NewProp_KernelType_MetaData) }; // 417858639
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_C = { "C", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, C), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_C_MetaData), NewProp_C_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_gamma = { "gamma", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, gamma), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_gamma_MetaData), NewProp_gamma_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_degree = { "degree", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, degree), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_degree_MetaData), NewProp_degree_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_coef0 = { "coef0", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, coef0), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_coef0_MetaData), NewProp_coef0_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_nu = { "nu", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, nu), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_nu_MetaData), NewProp_nu_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_svrEpsilon = { "svrEpsilon", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, svrEpsilon), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_svrEpsilon_MetaData), NewProp_svrEpsilon_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_cachesize = { "cachesize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, cachesize), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_cachesize_MetaData), NewProp_cachesize_MetaData) };
const UECodeGen_Private::FDoublePropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_epsilon = { "epsilon", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Double, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FSVMParameters, epsilon), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_epsilon_MetaData), NewProp_epsilon_MetaData) };
void Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_shrinking_SetBit(void* Obj)
{
	((FSVMParameters*)Obj)->shrinking = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_shrinking = { "shrinking", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FSVMParameters), &Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_shrinking_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_shrinking_MetaData), NewProp_shrinking_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSVMParameters_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_SVMType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_SVMType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_KernelType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_KernelType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_C,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_gamma,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_degree,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_coef0,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_nu,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_svrEpsilon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_cachesize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_epsilon,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSVMParameters_Statics::NewProp_shrinking,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSVMParameters_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSVMParameters_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	nullptr,
	&NewStructOps,
	"SVMParameters",
	Z_Construct_UScriptStruct_FSVMParameters_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSVMParameters_Statics::PropPointers),
	sizeof(FSVMParameters),
	alignof(FSVMParameters),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSVMParameters_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FSVMParameters_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FSVMParameters()
{
	if (!Z_Registration_Info_UScriptStruct_SVMParameters.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_SVMParameters.InnerSingleton, Z_Construct_UScriptStruct_FSVMParameters_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_SVMParameters.InnerSingleton;
}
// End ScriptStruct FSVMParameters

// Begin Class ULibSVM Function load
struct Z_Construct_UFunction_ULibSVM_load_Statics
{
	struct LibSVM_eventload_Parms
	{
		FString path;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "SVM" },
		{ "DisplayName", "Load SVM" },
		{ "Keywords", "Load SVM" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_path;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_ULibSVM_load_Statics::NewProp_path = { "path", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LibSVM_eventload_Parms, path), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULibSVM_load_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULibSVM_load_Statics::NewProp_path,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULibSVM_load_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULibSVM_load_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULibSVM, nullptr, "load", nullptr, nullptr, Z_Construct_UFunction_ULibSVM_load_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULibSVM_load_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULibSVM_load_Statics::LibSVM_eventload_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULibSVM_load_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULibSVM_load_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ULibSVM_load_Statics::LibSVM_eventload_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ULibSVM_load()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULibSVM_load_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULibSVM::execload)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_path);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->load(Z_Param_path);
	P_NATIVE_END;
}
// End Class ULibSVM Function load

// Begin Class ULibSVM Function predict
struct Z_Construct_UFunction_ULibSVM_predict_Statics
{
	struct LibSVM_eventpredict_Parms
	{
		TArray<FCLFSample> samples;
		TArray<FCLFResult> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "SVM" },
		{ "DisplayName", "SVM Predict" },
		{ "Keywords", "SVM Predict" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_samples_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_samples;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULibSVM_predict_Statics::NewProp_samples_Inner = { "samples", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FCLFSample, METADATA_PARAMS(0, nullptr) }; // 1022972749
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULibSVM_predict_Statics::NewProp_samples = { "samples", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LibSVM_eventpredict_Parms, samples), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 1022972749
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ULibSVM_predict_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FCLFResult, METADATA_PARAMS(0, nullptr) }; // 1613212741
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_ULibSVM_predict_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LibSVM_eventpredict_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 1613212741
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULibSVM_predict_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULibSVM_predict_Statics::NewProp_samples_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULibSVM_predict_Statics::NewProp_samples,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULibSVM_predict_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULibSVM_predict_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULibSVM_predict_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULibSVM_predict_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULibSVM, nullptr, "predict", nullptr, nullptr, Z_Construct_UFunction_ULibSVM_predict_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULibSVM_predict_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULibSVM_predict_Statics::LibSVM_eventpredict_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULibSVM_predict_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULibSVM_predict_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_ULibSVM_predict_Statics::LibSVM_eventpredict_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ULibSVM_predict()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULibSVM_predict_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULibSVM::execpredict)
{
	P_GET_TARRAY(FCLFSample,Z_Param_samples);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<FCLFResult>*)Z_Param__Result=P_THIS->predict(Z_Param_samples);
	P_NATIVE_END;
}
// End Class ULibSVM Function predict

// Begin Class ULibSVM Function train
struct Z_Construct_UFunction_ULibSVM_train_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "SVM" },
		{ "DisplayName", "SVM Train" },
		{ "Keywords", "SVM Train Fit" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULibSVM_train_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ULibSVM, nullptr, "train", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULibSVM_train_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULibSVM_train_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_ULibSVM_train()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULibSVM_train_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULibSVM::exectrain)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->train();
	P_NATIVE_END;
}
// End Class ULibSVM Function train

// Begin Class ULibSVM
void ULibSVM::StaticRegisterNativesULibSVM()
{
	UClass* Class = ULibSVM::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "load", &ULibSVM::execload },
		{ "predict", &ULibSVM::execpredict },
		{ "train", &ULibSVM::exectrain },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ULibSVM);
UClass* Z_Construct_UClass_ULibSVM_NoRegister()
{
	return ULibSVM::StaticClass();
}
struct Z_Construct_UClass_ULibSVM_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "DisplayName", "SVM" },
		{ "IncludePath", "LibSVM.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_trainingSet_MetaData[] = {
		{ "Category", "LibSVM" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SVMParameters_MetaData[] = {
		{ "Category", "LibSVM" },
		{ "ModuleRelativePath", "Public/LibSVM.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_trainingSet_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_trainingSet;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SVMParameters;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ULibSVM_load, "load" }, // 3365297958
		{ &Z_Construct_UFunction_ULibSVM_predict, "predict" }, // 3898248928
		{ &Z_Construct_UFunction_ULibSVM_train, "train" }, // 1696540372
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULibSVM>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULibSVM_Statics::NewProp_trainingSet_Inner = { "trainingSet", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FCLFSample, METADATA_PARAMS(0, nullptr) }; // 1022972749
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_ULibSVM_Statics::NewProp_trainingSet = { "trainingSet", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULibSVM, trainingSet), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_trainingSet_MetaData), NewProp_trainingSet_MetaData) }; // 1022972749
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_ULibSVM_Statics::NewProp_SVMParameters = { "SVMParameters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULibSVM, SVMParameters), Z_Construct_UScriptStruct_FSVMParameters, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SVMParameters_MetaData), NewProp_SVMParameters_MetaData) }; // 3464799922
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULibSVM_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULibSVM_Statics::NewProp_trainingSet_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULibSVM_Statics::NewProp_trainingSet,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULibSVM_Statics::NewProp_SVMParameters,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULibSVM_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ULibSVM_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULibSVM_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULibSVM_Statics::ClassParams = {
	&ULibSVM::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ULibSVM_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ULibSVM_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULibSVM_Statics::Class_MetaDataParams), Z_Construct_UClass_ULibSVM_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULibSVM()
{
	if (!Z_Registration_Info_UClass_ULibSVM.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULibSVM.OuterSingleton, Z_Construct_UClass_ULibSVM_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULibSVM.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<ULibSVM>()
{
	return ULibSVM::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULibSVM);
ULibSVM::~ULibSVM() {}
// End Class ULibSVM

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ LibSVMTypes_StaticEnum, TEXT("LibSVMTypes"), &Z_Registration_Info_UEnum_LibSVMTypes, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1580382862U) },
		{ LibSVMKernels_StaticEnum, TEXT("LibSVMKernels"), &Z_Registration_Info_UEnum_LibSVMKernels, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 417858639U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FCLFSample::StaticStruct, Z_Construct_UScriptStruct_FCLFSample_Statics::NewStructOps, TEXT("CLFSample"), &Z_Registration_Info_UScriptStruct_CLFSample, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCLFSample), 1022972749U) },
		{ FCLFResult::StaticStruct, Z_Construct_UScriptStruct_FCLFResult_Statics::NewStructOps, TEXT("CLFResult"), &Z_Registration_Info_UScriptStruct_CLFResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCLFResult), 1613212741U) },
		{ FSVMParameters::StaticStruct, Z_Construct_UScriptStruct_FSVMParameters_Statics::NewStructOps, TEXT("SVMParameters"), &Z_Registration_Info_UScriptStruct_SVMParameters, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FSVMParameters), 3464799922U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULibSVM, ULibSVM::StaticClass, TEXT("ULibSVM"), &Z_Registration_Info_UClass_ULibSVM, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULibSVM), 1524768110U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_380709003(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
