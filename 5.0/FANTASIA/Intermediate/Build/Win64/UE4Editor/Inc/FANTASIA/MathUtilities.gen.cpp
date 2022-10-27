// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/MathUtilities.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMathUtilities() {}
// Cross Module References
	FANTASIA_API UClass* Z_Construct_UClass_UKernelDensityEstimator_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UKernelDensityEstimator();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
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
	DEFINE_FUNCTION(UKernelDensityEstimator::execevaluate)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_point);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(float*)Z_Param__Result=P_THIS->evaluate(Z_Param_point);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UKernelDensityEstimator::execsetData)
	{
		P_GET_TARRAY(float,Z_Param_newData);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->setData(Z_Param_newData);
		P_NATIVE_END;
	}
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
	struct Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics
	{
		struct KernelDensityEstimator_eventevaluate_Parms
		{
			float point;
			float ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_point;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::NewProp_point = { "point", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(KernelDensityEstimator_eventevaluate_Parms, point), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(KernelDensityEstimator_eventevaluate_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::NewProp_point,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::Function_MetaDataParams[] = {
		{ "Category", "Kernel_Density_Estimation" },
		{ "DisplayName", "Evaluate" },
		{ "ModuleRelativePath", "Public/MathUtilities.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UKernelDensityEstimator, nullptr, "evaluate", nullptr, nullptr, sizeof(KernelDensityEstimator_eventevaluate_Parms), Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UKernelDensityEstimator_evaluate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UKernelDensityEstimator_evaluate_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics
	{
		struct KernelDensityEstimator_eventgetPdf_Parms
		{
			float min;
			float max;
			int32 points;
			TMap<float,float> ReturnValue;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_min;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_max;
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_points;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_ValueProp;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_Key_KeyProp;
		static const UE4CodeGen_Private::FMapPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_min = { "min", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(KernelDensityEstimator_eventgetPdf_Parms, min), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_max = { "max", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(KernelDensityEstimator_eventgetPdf_Parms, max), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_points = { "points", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(KernelDensityEstimator_eventgetPdf_Parms, points), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue_ValueProp = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue_Key_KeyProp = { "ReturnValue_Key", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(KernelDensityEstimator_eventgetPdf_Parms, ReturnValue), EMapPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_min,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_max,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_points,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue_ValueProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue_Key_KeyProp,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::Function_MetaDataParams[] = {
		{ "Category", "Kernel_Density_Estimation" },
		{ "DisplayName", "GetPDF" },
		{ "ModuleRelativePath", "Public/MathUtilities.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UKernelDensityEstimator, nullptr, "getPdf", nullptr, nullptr, sizeof(KernelDensityEstimator_eventgetPdf_Parms), Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UKernelDensityEstimator_getPdf()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UKernelDensityEstimator_getPdf_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics
	{
		struct KernelDensityEstimator_eventsetData_Parms
		{
			TArray<float> newData;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_newData_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_newData;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::NewProp_newData_Inner = { "newData", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::NewProp_newData = { "newData", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(KernelDensityEstimator_eventsetData_Parms, newData), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::NewProp_newData_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::NewProp_newData,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::Function_MetaDataParams[] = {
		{ "Category", "Kernel_Density_Estimation" },
		{ "DisplayName", "SetData" },
		{ "ModuleRelativePath", "Public/MathUtilities.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UKernelDensityEstimator, nullptr, "setData", nullptr, nullptr, sizeof(KernelDensityEstimator_eventsetData_Parms), Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UKernelDensityEstimator_setData()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UKernelDensityEstimator_setData_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UKernelDensityEstimator_NoRegister()
	{
		return UKernelDensityEstimator::StaticClass();
	}
	struct Z_Construct_UClass_UKernelDensityEstimator_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UKernelDensityEstimator_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UKernelDensityEstimator_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UKernelDensityEstimator_evaluate, "evaluate" }, // 450031369
		{ &Z_Construct_UFunction_UKernelDensityEstimator_getPdf, "getPdf" }, // 269172415
		{ &Z_Construct_UFunction_UKernelDensityEstimator_setData, "setData" }, // 557634384
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UKernelDensityEstimator_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "MathUtilities.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/MathUtilities.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UKernelDensityEstimator_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UKernelDensityEstimator>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UKernelDensityEstimator_Statics::ClassParams = {
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
		METADATA_PARAMS(Z_Construct_UClass_UKernelDensityEstimator_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UKernelDensityEstimator_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UKernelDensityEstimator()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UKernelDensityEstimator_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UKernelDensityEstimator, 3173493031);
	template<> FANTASIA_API UClass* StaticClass<UKernelDensityEstimator>()
	{
		return UKernelDensityEstimator::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UKernelDensityEstimator(Z_Construct_UClass_UKernelDensityEstimator, &UKernelDensityEstimator::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UKernelDensityEstimator"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UKernelDensityEstimator);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
