// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/SWIPrologComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSWIPrologComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_USWIPrologComponent();
FANTASIA_API UClass* Z_Construct_UClass_USWIPrologComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Class USWIPrologComponent Function startProlog
struct Z_Construct_UFunction_USWIPrologComponent_startProlog_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "SWIProlog" },
		{ "DisplayName", "Start Prolog" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USWIPrologComponent_startProlog_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USWIPrologComponent, nullptr, "startProlog", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_startProlog_Statics::Function_MetaDataParams), Z_Construct_UFunction_USWIPrologComponent_startProlog_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_USWIPrologComponent_startProlog()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USWIPrologComponent_startProlog_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USWIPrologComponent::execstartProlog)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->startProlog();
	P_NATIVE_END;
}
// End Class USWIPrologComponent Function startProlog

// Begin Class USWIPrologComponent Function submitQuery
struct Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics
{
	struct SWIPrologComponent_eventsubmitQuery_Parms
	{
		bool choice;
		FString outString;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "SWIProlog" },
		{ "DisplayName", "Submit query" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_choice_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static void NewProp_choice_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_choice;
	static const UECodeGen_Private::FStrPropertyParams NewProp_outString;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::NewProp_choice_SetBit(void* Obj)
{
	((SWIPrologComponent_eventsubmitQuery_Parms*)Obj)->choice = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::NewProp_choice = { "choice", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SWIPrologComponent_eventsubmitQuery_Parms), &Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::NewProp_choice_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_choice_MetaData), NewProp_choice_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::NewProp_outString = { "outString", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SWIPrologComponent_eventsubmitQuery_Parms, outString), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::NewProp_choice,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::NewProp_outString,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USWIPrologComponent, nullptr, "submitQuery", nullptr, nullptr, Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::PropPointers), sizeof(Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::SWIPrologComponent_eventsubmitQuery_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::Function_MetaDataParams), Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::SWIPrologComponent_eventsubmitQuery_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USWIPrologComponent_submitQuery()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USWIPrologComponent_submitQuery_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USWIPrologComponent::execsubmitQuery)
{
	P_GET_UBOOL(Z_Param_choice);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_outString);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->submitQuery(Z_Param_choice,Z_Param_Out_outString);
	P_NATIVE_END;
}
// End Class USWIPrologComponent Function submitQuery

// Begin Class USWIPrologComponent
void USWIPrologComponent::StaticRegisterNativesUSWIPrologComponent()
{
	UClass* Class = USWIPrologComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "startProlog", &USWIPrologComponent::execstartProlog },
		{ "submitQuery", &USWIPrologComponent::execsubmitQuery },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USWIPrologComponent);
UClass* Z_Construct_UClass_USWIPrologComponent_NoRegister()
{
	return USWIPrologComponent::StaticClass();
}
struct Z_Construct_UClass_USWIPrologComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "SWIProlog" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSWITestStruct,SWIPrologResponse);\n" },
#endif
		{ "IncludePath", "SWIPrologComponent.h" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSWITestStruct,SWIPrologResponse);" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_aStringProperty_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_readOnlyProperty_MetaData[] = {
		{ "Category", "SWIPrologComponent" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "//UPROPERTY(BlueprintAssignable, BlueprintCallable)\n//FSWITestStruct assignableCallableProperty;\n" },
#endif
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UPROPERTY(BlueprintAssignable, BlueprintCallable)\nFSWITestStruct assignableCallableProperty;" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_aBoolProperty_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_aStringProperty;
	static const UECodeGen_Private::FStrPropertyParams NewProp_readOnlyProperty;
	static void NewProp_aBoolProperty_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_aBoolProperty;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USWIPrologComponent_startProlog, "startProlog" }, // 2933650865
		{ &Z_Construct_UFunction_USWIPrologComponent_submitQuery, "submitQuery" }, // 42795029
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USWIPrologComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_USWIPrologComponent_Statics::NewProp_aStringProperty = { "aStringProperty", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USWIPrologComponent, aStringProperty), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_aStringProperty_MetaData), NewProp_aStringProperty_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_USWIPrologComponent_Statics::NewProp_readOnlyProperty = { "readOnlyProperty", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USWIPrologComponent, readOnlyProperty), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_readOnlyProperty_MetaData), NewProp_readOnlyProperty_MetaData) };
void Z_Construct_UClass_USWIPrologComponent_Statics::NewProp_aBoolProperty_SetBit(void* Obj)
{
	((USWIPrologComponent*)Obj)->aBoolProperty = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USWIPrologComponent_Statics::NewProp_aBoolProperty = { "aBoolProperty", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(USWIPrologComponent), &Z_Construct_UClass_USWIPrologComponent_Statics::NewProp_aBoolProperty_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_aBoolProperty_MetaData), NewProp_aBoolProperty_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USWIPrologComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USWIPrologComponent_Statics::NewProp_aStringProperty,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USWIPrologComponent_Statics::NewProp_readOnlyProperty,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USWIPrologComponent_Statics::NewProp_aBoolProperty,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USWIPrologComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USWIPrologComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USWIPrologComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USWIPrologComponent_Statics::ClassParams = {
	&USWIPrologComponent::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_USWIPrologComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_USWIPrologComponent_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USWIPrologComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_USWIPrologComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USWIPrologComponent()
{
	if (!Z_Registration_Info_UClass_USWIPrologComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USWIPrologComponent.OuterSingleton, Z_Construct_UClass_USWIPrologComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USWIPrologComponent.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<USWIPrologComponent>()
{
	return USWIPrologComponent::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USWIPrologComponent);
USWIPrologComponent::~USWIPrologComponent() {}
// End Class USWIPrologComponent

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USWIPrologComponent, USWIPrologComponent::StaticClass, TEXT("USWIPrologComponent"), &Z_Registration_Info_UClass_USWIPrologComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USWIPrologComponent), 2777470400U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_882934621(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
