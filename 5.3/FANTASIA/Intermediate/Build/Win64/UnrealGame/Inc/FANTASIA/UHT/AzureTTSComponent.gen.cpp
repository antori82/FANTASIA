// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "../../../../../../Source/FANTASIA/Public/AzureTTSComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAzureTTSComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_USoundBase_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UAzureTTSComponent();
	FANTASIA_API UClass* Z_Construct_UClass_UAzureTTSComponent_NoRegister();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
	DEFINE_FUNCTION(UAzureTTSComponent::execAzureTTSGetSound)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USoundBase**)Z_Param__Result=P_THIS->AzureTTSGetSound(Z_Param_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAzureTTSComponent::execAzureTTSSynthesize)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ssml);
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AzureTTSSynthesize(Z_Param_ssml,Z_Param_id);
		P_NATIVE_END;
	}
	void UAzureTTSComponent::StaticRegisterNativesUAzureTTSComponent()
	{
		UClass* Class = UAzureTTSComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AzureTTSGetSound", &UAzureTTSComponent::execAzureTTSGetSound },
			{ "AzureTTSSynthesize", &UAzureTTSComponent::execAzureTTSSynthesize },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics
	{
		struct AzureTTSComponent_eventAzureTTSGetSound_Parms
		{
			FString id;
			USoundBase* ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_id;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AzureTTSComponent_eventAzureTTSGetSound_Parms, id), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AzureTTSComponent_eventAzureTTSGetSound_Parms, ReturnValue), Z_Construct_UClass_USoundBase_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::NewProp_id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Sound" },
		{ "Keywords", "Azure Plugin TTS" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureTTSComponent, nullptr, "AzureTTSGetSound", nullptr, nullptr, Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::AzureTTSComponent_eventAzureTTSGetSound_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::AzureTTSComponent_eventAzureTTSGetSound_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics
	{
		struct AzureTTSComponent_eventAzureTTSSynthesize_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::NewProp_ssml = { "ssml", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AzureTTSComponent_eventAzureTTSSynthesize_Parms, ssml), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AzureTTSComponent_eventAzureTTSSynthesize_Parms, id), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::NewProp_ssml,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::NewProp_id,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "TTS Start" },
		{ "Keywords", "Azure Plugin TTS" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureTTSComponent, nullptr, "AzureTTSSynthesize", nullptr, nullptr, Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::AzureTTSComponent_eventAzureTTSSynthesize_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::AzureTTSComponent_eventAzureTTSSynthesize_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAzureTTSComponent);
	UClass* Z_Construct_UClass_UAzureTTSComponent_NoRegister()
	{
		return UAzureTTSComponent::StaticClass();
	}
	struct Z_Construct_UClass_UAzureTTSComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Speaker_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Speaker;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SynthesisReady_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_SynthesisReady;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Language;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Voice_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Voice;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Region_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Region;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAzureTTSComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UAzureTTSComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound, "AzureTTSGetSound" }, // 1499428135
		{ &Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize, "AzureTTSSynthesize" }, // 3197016944
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Azure" },
		{ "IncludePath", "AzureTTSComponent.h" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker = { "Speaker", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureTTSComponent, Speaker), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker_MetaData), Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady = { "SynthesisReady", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureTTSComponent, SynthesisReady), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady_MetaData), Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady_MetaData) }; // 2609128134
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language = { "Language", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureTTSComponent, Language), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language_MetaData), Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice = { "Voice", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureTTSComponent, Voice), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice_MetaData), Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureTTSComponent, Key), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key_MetaData), Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region = { "Region", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAzureTTSComponent, Region), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region_MetaData), Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAzureTTSComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAzureTTSComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAzureTTSComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UAzureTTSComponent_Statics::ClassParams = {
		&UAzureTTSComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAzureTTSComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::PropPointers),
		0,
		0x00A000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UAzureTTSComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UAzureTTSComponent()
	{
		if (!Z_Registration_Info_UClass_UAzureTTSComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAzureTTSComponent.OuterSingleton, Z_Construct_UClass_UAzureTTSComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UAzureTTSComponent.OuterSingleton;
	}
	template<> FANTASIA_API UClass* StaticClass<UAzureTTSComponent>()
	{
		return UAzureTTSComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAzureTTSComponent);
	UAzureTTSComponent::~UAzureTTSComponent() {}
	struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UAzureTTSComponent, UAzureTTSComponent::StaticClass, TEXT("UAzureTTSComponent"), &Z_Registration_Info_UClass_UAzureTTSComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAzureTTSComponent), 986613159U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_2077089147(TEXT("/Script/FANTASIA"),
		Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AzureTTSComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
