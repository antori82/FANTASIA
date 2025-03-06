// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/SWIPrologComponent.h"
#include "FANTASIA/Public/FANTASIATypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSWIPrologComponent() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_USWIPrologComponent();
FANTASIA_API UClass* Z_Construct_UClass_USWIPrologComponent_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_USWIPrologObject_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_USWIPrologTerm_NoRegister();
FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FSWIPrologResponse();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Class USWIPrologComponent Function openPrologFile
struct Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics
{
	struct SWIPrologComponent_eventopenPrologFile_Parms
	{
		FString filename;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "SWIProlog" },
		{ "DisplayName", "Open Prolog file" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_filename_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_filename;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::NewProp_filename = { "filename", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SWIPrologComponent_eventopenPrologFile_Parms, filename), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_filename_MetaData), NewProp_filename_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::NewProp_filename,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USWIPrologComponent, nullptr, "openPrologFile", nullptr, nullptr, Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::PropPointers), sizeof(Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::SWIPrologComponent_eventopenPrologFile_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::Function_MetaDataParams), Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::SWIPrologComponent_eventopenPrologFile_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USWIPrologComponent_openPrologFile()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USWIPrologComponent_openPrologFile_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USWIPrologComponent::execopenPrologFile)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_filename);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->openPrologFile(Z_Param_filename);
	P_NATIVE_END;
}
// End Class USWIPrologComponent Function openPrologFile

// Begin Class USWIPrologComponent Function SWIPLassert
struct Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics
{
	struct SWIPrologComponent_eventSWIPLassert_Parms
	{
		USWIPrologObject* prologObject;
		bool asFirstClause;
		bool bResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "SWIProlog" },
		{ "DisplayName", "Assert" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_prologObject;
	static void NewProp_asFirstClause_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_asFirstClause;
	static void NewProp_bResult_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_prologObject = { "prologObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SWIPrologComponent_eventSWIPLassert_Parms, prologObject), Z_Construct_UClass_USWIPrologObject_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_asFirstClause_SetBit(void* Obj)
{
	((SWIPrologComponent_eventSWIPLassert_Parms*)Obj)->asFirstClause = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_asFirstClause = { "asFirstClause", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SWIPrologComponent_eventSWIPLassert_Parms), &Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_asFirstClause_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_bResult_SetBit(void* Obj)
{
	((SWIPrologComponent_eventSWIPLassert_Parms*)Obj)->bResult = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_bResult = { "bResult", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SWIPrologComponent_eventSWIPLassert_Parms), &Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_bResult_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_prologObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_asFirstClause,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::NewProp_bResult,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USWIPrologComponent, nullptr, "SWIPLassert", nullptr, nullptr, Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::PropPointers), sizeof(Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::SWIPrologComponent_eventSWIPLassert_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::Function_MetaDataParams), Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::SWIPrologComponent_eventSWIPLassert_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USWIPrologComponent_SWIPLassert()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USWIPrologComponent_SWIPLassert_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USWIPrologComponent::execSWIPLassert)
{
	P_GET_OBJECT(USWIPrologObject,Z_Param_prologObject);
	P_GET_UBOOL(Z_Param_asFirstClause);
	P_GET_UBOOL_REF(Z_Param_Out_bResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SWIPLassert(Z_Param_prologObject,Z_Param_asFirstClause,Z_Param_Out_bResult);
	P_NATIVE_END;
}
// End Class USWIPrologComponent Function SWIPLassert

// Begin Class USWIPrologComponent Function SWIPLresetProlog
struct Z_Construct_UFunction_USWIPrologComponent_SWIPLresetProlog_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "SWIProlog" },
		{ "DisplayName", "Reset Prolog" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USWIPrologComponent_SWIPLresetProlog_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USWIPrologComponent, nullptr, "SWIPLresetProlog", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLresetProlog_Statics::Function_MetaDataParams), Z_Construct_UFunction_USWIPrologComponent_SWIPLresetProlog_Statics::Function_MetaDataParams) };
UFunction* Z_Construct_UFunction_USWIPrologComponent_SWIPLresetProlog()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USWIPrologComponent_SWIPLresetProlog_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USWIPrologComponent::execSWIPLresetProlog)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SWIPLresetProlog();
	P_NATIVE_END;
}
// End Class USWIPrologComponent Function SWIPLresetProlog

// Begin Class USWIPrologComponent Function SWIPLretract
struct Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics
{
	struct SWIPrologComponent_eventSWIPLretract_Parms
	{
		USWIPrologTerm* ruleOrFact;
		bool bResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "SWIProlog" },
		{ "DisplayName", "Retract" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ruleOrFact;
	static void NewProp_bResult_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::NewProp_ruleOrFact = { "ruleOrFact", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SWIPrologComponent_eventSWIPLretract_Parms, ruleOrFact), Z_Construct_UClass_USWIPrologTerm_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::NewProp_bResult_SetBit(void* Obj)
{
	((SWIPrologComponent_eventSWIPLretract_Parms*)Obj)->bResult = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::NewProp_bResult = { "bResult", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SWIPrologComponent_eventSWIPLretract_Parms), &Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::NewProp_bResult_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::NewProp_ruleOrFact,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::NewProp_bResult,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USWIPrologComponent, nullptr, "SWIPLretract", nullptr, nullptr, Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::PropPointers), sizeof(Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::SWIPrologComponent_eventSWIPLretract_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::Function_MetaDataParams), Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::SWIPrologComponent_eventSWIPLretract_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USWIPrologComponent_SWIPLretract()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USWIPrologComponent_SWIPLretract_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USWIPrologComponent::execSWIPLretract)
{
	P_GET_OBJECT(USWIPrologTerm,Z_Param_ruleOrFact);
	P_GET_UBOOL_REF(Z_Param_Out_bResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SWIPLretract(Z_Param_ruleOrFact,Z_Param_Out_bResult);
	P_NATIVE_END;
}
// End Class USWIPrologComponent Function SWIPLretract

// Begin Class USWIPrologComponent Function SWIPLsubmitQuery
struct Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics
{
	struct SWIPrologComponent_eventSWIPLsubmitQuery_Parms
	{
		USWIPrologTerm* inRuleOrFact;
		FSWIPrologResponse outResponse;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "parameters" },
		{ "Category", "SWIProlog" },
		{ "DisplayName", "Submit query" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_inRuleOrFact;
	static const UECodeGen_Private::FStructPropertyParams NewProp_outResponse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::NewProp_inRuleOrFact = { "inRuleOrFact", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SWIPrologComponent_eventSWIPLsubmitQuery_Parms, inRuleOrFact), Z_Construct_UClass_USWIPrologTerm_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::NewProp_outResponse = { "outResponse", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SWIPrologComponent_eventSWIPLsubmitQuery_Parms, outResponse), Z_Construct_UScriptStruct_FSWIPrologResponse, METADATA_PARAMS(0, nullptr) }; // 1392627495
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::NewProp_inRuleOrFact,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::NewProp_outResponse,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USWIPrologComponent, nullptr, "SWIPLsubmitQuery", nullptr, nullptr, Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::PropPointers), sizeof(Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::SWIPrologComponent_eventSWIPLsubmitQuery_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::Function_MetaDataParams), Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::SWIPrologComponent_eventSWIPLsubmitQuery_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USWIPrologComponent::execSWIPLsubmitQuery)
{
	P_GET_OBJECT(USWIPrologTerm,Z_Param_inRuleOrFact);
	P_GET_STRUCT_REF(FSWIPrologResponse,Z_Param_Out_outResponse);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->SWIPLsubmitQuery(Z_Param_inRuleOrFact,Z_Param_Out_outResponse);
	P_NATIVE_END;
}
// End Class USWIPrologComponent Function SWIPLsubmitQuery

// Begin Class USWIPrologComponent
void USWIPrologComponent::StaticRegisterNativesUSWIPrologComponent()
{
	UClass* Class = USWIPrologComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "openPrologFile", &USWIPrologComponent::execopenPrologFile },
		{ "SWIPLassert", &USWIPrologComponent::execSWIPLassert },
		{ "SWIPLresetProlog", &USWIPrologComponent::execSWIPLresetProlog },
		{ "SWIPLretract", &USWIPrologComponent::execSWIPLretract },
		{ "SWIPLsubmitQuery", &USWIPrologComponent::execSWIPLsubmitQuery },
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
		{ "IncludePath", "SWIPrologComponent.h" },
		{ "ModuleRelativePath", "Public/SWIPrologComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USWIPrologComponent_openPrologFile, "openPrologFile" }, // 1331636385
		{ &Z_Construct_UFunction_USWIPrologComponent_SWIPLassert, "SWIPLassert" }, // 901108155
		{ &Z_Construct_UFunction_USWIPrologComponent_SWIPLresetProlog, "SWIPLresetProlog" }, // 4223325723
		{ &Z_Construct_UFunction_USWIPrologComponent_SWIPLretract, "SWIPLretract" }, // 3558670054
		{ &Z_Construct_UFunction_USWIPrologComponent_SWIPLsubmitQuery, "SWIPLsubmitQuery" }, // 3827036387
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USWIPrologComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
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
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
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
struct Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USWIPrologComponent, USWIPrologComponent::StaticClass, TEXT("USWIPrologComponent"), &Z_Registration_Info_UClass_USWIPrologComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USWIPrologComponent), 3962328257U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_1037438509(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
