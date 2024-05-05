// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "../../../../../../Source/FANTASIA/Public/TTSInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTTSInterface() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	ENGINE_API UClass* Z_Construct_UClass_USoundWave_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UTTSInterface();
	FANTASIA_API UClass* Z_Construct_UClass_UTTSInterface_NoRegister();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
	DEFINE_FUNCTION(ITTSInterface::execTTSGetSound)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USoundWave**)Z_Param__Result=P_THIS->TTSGetSound(Z_Param_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(ITTSInterface::execTTSSynthesize)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ssml);
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->TTSSynthesize(Z_Param_ssml,Z_Param_id);
		P_NATIVE_END;
	}
	void UTTSInterface::StaticRegisterNativesUTTSInterface()
	{
		UClass* Class = UTTSInterface::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "TTSGetSound", &ITTSInterface::execTTSGetSound },
			{ "TTSSynthesize", &ITTSInterface::execTTSSynthesize },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics
	{
		struct TTSInterface_eventTTSGetSound_Parms
		{
			FString id;
			USoundWave* ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_id;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSGetSound_Parms, id), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSGetSound_Parms, ReturnValue), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::NewProp_id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* To format the synthesis result into audio playable by Unreal\n\x09*\n\x09*\x09@parm id - buffer synthesis id\n\x09*\n\x09**/" },
#endif
		{ "ModuleRelativePath", "Public/TTSInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "To format the synthesis result into audio playable by Unreal\n\n      @parm id - buffer synthesis id" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTTSInterface, nullptr, "TTSGetSound", nullptr, nullptr, Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::TTSInterface_eventTTSGetSound_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::TTSInterface_eventTTSGetSound_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UTTSInterface_TTSGetSound()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTTSInterface_TTSGetSound_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics
	{
		struct TTSInterface_eventTTSSynthesize_Parms
		{
			FString ssml;
			FString id;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ssml;
		static const UECodeGen_Private::FStrPropertyParams NewProp_id;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::NewProp_ssml = { "ssml", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSSynthesize_Parms, ssml), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(TTSInterface_eventTTSSynthesize_Parms, id), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::NewProp_ssml,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::NewProp_id,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09* To manage speech synthesis\n\x09*\n\x09*\x09@param ssml - synthesis data\n\x09*\x09@param id - buffer synthesis id\n\x09*\n\x09**/" },
#endif
		{ "ModuleRelativePath", "Public/TTSInterface.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "To manage speech synthesis\n\n      @param ssml - synthesis data\n      @param id - buffer synthesis id" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UTTSInterface, nullptr, "TTSSynthesize", nullptr, nullptr, Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::PropPointers), sizeof(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::TTSInterface_eventTTSSynthesize_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::Function_MetaDataParams), Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::TTSInterface_eventTTSSynthesize_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UTTSInterface_TTSSynthesize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UTTSInterface_TTSSynthesize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTTSInterface);
	UClass* Z_Construct_UClass_UTTSInterface_NoRegister()
	{
		return UTTSInterface::StaticClass();
	}
	struct Z_Construct_UClass_UTTSInterface_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTTSInterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTTSInterface_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UTTSInterface_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UTTSInterface_TTSGetSound, "TTSGetSound" }, // 3160714645
		{ &Z_Construct_UFunction_UTTSInterface_TTSSynthesize, "TTSSynthesize" }, // 2355189333
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTTSInterface_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTTSInterface_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/TTSInterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTTSInterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ITTSInterface>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UTTSInterface_Statics::ClassParams = {
		&UTTSInterface::StaticClass,
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
		0x000840A1u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTTSInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UTTSInterface_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UTTSInterface()
	{
		if (!Z_Registration_Info_UClass_UTTSInterface.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTTSInterface.OuterSingleton, Z_Construct_UClass_UTTSInterface_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UTTSInterface.OuterSingleton;
	}
	template<> FANTASIA_API UClass* StaticClass<UTTSInterface>()
	{
		return UTTSInterface::StaticClass();
	}
	UTTSInterface::UTTSInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UTTSInterface);
	UTTSInterface::~UTTSInterface() {}
	struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UTTSInterface, UTTSInterface::StaticClass, TEXT("UTTSInterface"), &Z_Registration_Info_UClass_UTTSInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTTSInterface), 3444065753U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_434742790(TEXT("/Script/FANTASIA"),
		Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
