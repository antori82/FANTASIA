// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MathUtilities.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeMathUtilities() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
FANTASIA_API UClass* Z_Construct_UClass_UKernelDensityEstimator();
FANTASIA_API UClass* Z_Construct_UClass_UKernelDensityEstimator_NoRegister();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UKernelDensityEstimator Function evaluate ********************************
struct Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics
{
	struct KernelDensityEstimator_eventevaluate_Parms
	{
		float point;
		float ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Kernel_Density_Estimation" },
		{ "DisplayName", "Evaluate" },
		{ "ModuleRelativePath", "Public/MathUtilities.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_point;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::NewProp_point = { "point", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KernelDensityEstimator_eventevaluate_Parms, point), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KernelDensityEstimator_eventevaluate_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::NewProp_point,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UKernelDensityEstimator, nullptr, "evaluate", Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::PropPointers), sizeof(Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::KernelDensityEstimator_eventevaluate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::Function_MetaDataParams), Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::KernelDensityEstimator_eventevaluate_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UKernelDensityEstimator_evaluate()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UKernelDensityEstimator::execevaluate)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_point);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(float*)Z_Param__Result=P_THIS->evaluate(Z_Param_point);
	P_NATIVE_END;
}
// ********** End Class UKernelDensityEstimator Function evaluate **********************************

// ********** Begin Class UKernelDensityEstimator Function getPdf **********************************
struct Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics
{
	struct KernelDensityEstimator_eventgetPdf_Parms
	{
		float min;
		float max;
		int32 points;
		TMap<float,float> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Kernel_Density_Estimation" },
		{ "DisplayName", "GetPDF" },
		{ "ModuleRelativePath", "Public/MathUtilities.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_min;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_max;
	static const UECodeGen_Private::FIntPropertyParams NewProp_points;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_ValueProp;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_min = { "min", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KernelDensityEstimator_eventgetPdf_Parms, min), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_max = { "max", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KernelDensityEstimator_eventgetPdf_Parms, max), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_points = { "points", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KernelDensityEstimator_eventgetPdf_Parms, points), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue_ValueProp = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue_Key_KeyProp = { "ReturnValue_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KernelDensityEstimator_eventgetPdf_Parms, ReturnValue), EMapPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_min,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_max,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_points,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UKernelDensityEstimator, nullptr, "getPdf", Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::PropPointers), sizeof(Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::KernelDensityEstimator_eventgetPdf_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::Function_MetaDataParams), Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::KernelDensityEstimator_eventgetPdf_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UKernelDensityEstimator_getPdf()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UKernelDensityEstimator::execgetPdf)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_min);
	P_GET_PROPERTY(FFloatProperty,Z_Param_max);
	P_GET_PROPERTY(FIntProperty,Z_Param_points);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TMap<float,float>*)Z_Param__Result=P_THIS->getPdf(Z_Param_min,Z_Param_max,Z_Param_points);
	P_NATIVE_END;
}
// ********** End Class UKernelDensityEstimator Function getPdf ************************************

// ********** Begin Class UKernelDensityEstimator Function setData *********************************
struct Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics
{
	struct KernelDensityEstimator_eventsetData_Parms
	{
		TArray<float> newData;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Kernel_Density_Estimation" },
		{ "DisplayName", "SetData" },
		{ "ModuleRelativePath", "Public/MathUtilities.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_newData_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_newData;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::NewProp_newData_Inner = { "newData", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::NewProp_newData = { "newData", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(KernelDensityEstimator_eventsetData_Parms, newData), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::NewProp_newData_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::NewProp_newData,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UKernelDensityEstimator, nullptr, "setData", Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::PropPointers), sizeof(Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::KernelDensityEstimator_eventsetData_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::Function_MetaDataParams), Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::KernelDensityEstimator_eventsetData_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UKernelDensityEstimator_setData()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UKernelDensityEstimator::execsetData)
{
	P_GET_TARRAY(float,Z_Param_newData);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->setData(Z_Param_newData);
	P_NATIVE_END;
}
// ********** End Class UKernelDensityEstimator Function setData ***********************************

// ********** Begin Class UKernelDensityEstimator **************************************************
void UKernelDensityEstimator::StaticRegisterNativesUKernelDensityEstimator()
{
	UClass* Class = UKernelDensityEstimator::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "evaluate", &UKernelDensityEstimator::execevaluate },
		{ "getPdf", &UKernelDensityEstimator::execgetPdf },
		{ "setData", &UKernelDensityEstimator::execsetData },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UKernelDensityEstimator;
UClass* UKernelDensityEstimator::GetPrivateStaticClass()
{
	using TClass = UKernelDensityEstimator;
	if (!Z_Registration_Info_UClass_UKernelDensityEstimator.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("KernelDensityEstimator"),
			Z_Registration_Info_UClass_UKernelDensityEstimator.InnerSingleton,
			StaticRegisterNativesUKernelDensityEstimator,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UKernelDensityEstimator.InnerSingleton;
}
UClass* Z_Construct_UClass_UKernelDensityEstimator_NoRegister()
{
	return UKernelDensityEstimator::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UKernelDensityEstimator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "MathUtilities.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/MathUtilities.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UKernelDensityEstimator_evaluate, "evaluate" }, // 478565951
		{ &Z_Construct_UFunction_UKernelDensityEstimator_getPdf, "getPdf" }, // 3451106171
		{ &Z_Construct_UFunction_UKernelDensityEstimator_setData, "setData" }, // 1838832657
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UKernelDensityEstimator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UKernelDensityEstimator_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UKernelDensityEstimator_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UKernelDensityEstimator_Statics::ClassParams = {
	&UKernelDensityEstimator::StaticClass,
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
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UKernelDensityEstimator_Statics::Class_MetaDataParams), Z_Construct_UClass_UKernelDensityEstimator_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UKernelDensityEstimator()
{
	if (!Z_Registration_Info_UClass_UKernelDensityEstimator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UKernelDensityEstimator.OuterSingleton, Z_Construct_UClass_UKernelDensityEstimator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UKernelDensityEstimator.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UKernelDensityEstimator);
UKernelDensityEstimator::~UKernelDensityEstimator() {}
// ********** End Class UKernelDensityEstimator ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h__Script_FANTASIA_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UKernelDensityEstimator, UKernelDensityEstimator::StaticClass, TEXT("UKernelDensityEstimator"), &Z_Registration_Info_UClass_UKernelDensityEstimator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UKernelDensityEstimator), 3570552767U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h__Script_FANTASIA_2681884641(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h__Script_FANTASIA_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_MathUtilities_h__Script_FANTASIA_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
