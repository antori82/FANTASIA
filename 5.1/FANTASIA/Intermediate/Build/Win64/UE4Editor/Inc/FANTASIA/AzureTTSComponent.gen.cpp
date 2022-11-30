// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/AzureTTSComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAzureTTSComponent() {}
// Cross Module References
	FANTASIA_API UClass* Z_Construct_UClass_UAzureTTSComponent_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UAzureTTSComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
	ENGINE_API UClass* Z_Construct_UClass_USoundBase_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
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
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AzureTTSComponent_eventAzureTTSGetSound_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AzureTTSComponent_eventAzureTTSGetSound_Parms, ReturnValue), Z_Construct_UClass_USoundBase_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::NewProp_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Sound" },
		{ "Keywords", "Azure Plugin TTS" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureTTSComponent, nullptr, "AzureTTSGetSound", nullptr, nullptr, sizeof(AzureTTSComponent_eventAzureTTSGetSound_Parms), Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound_Statics::FuncParams);
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
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ssml;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::NewProp_ssml = { "ssml", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AzureTTSComponent_eventAzureTTSSynthesize_Parms, ssml), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AzureTTSComponent_eventAzureTTSSynthesize_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::NewProp_ssml,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::NewProp_id,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "TTS Start" },
		{ "Keywords", "Azure Plugin TTS" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAzureTTSComponent, nullptr, "AzureTTSSynthesize", nullptr, nullptr, sizeof(AzureTTSComponent_eventAzureTTSSynthesize_Parms), Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAzureTTSComponent_NoRegister()
	{
		return UAzureTTSComponent::StaticClass();
	}
	struct Z_Construct_UClass_UAzureTTSComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Speaker_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_Speaker;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SynthesisReady_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_SynthesisReady;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Language_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Language;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Voice_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Voice;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Key;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Region_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Region;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAzureTTSComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAzureTTSComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAzureTTSComponent_AzureTTSGetSound, "AzureTTSGetSound" }, // 562774800
		{ &Z_Construct_UFunction_UAzureTTSComponent_AzureTTSSynthesize, "AzureTTSSynthesize" }, // 3740994970
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Azure" },
		{ "IncludePath", "AzureTTSComponent.h" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker = { "Speaker", nullptr, (EPropertyFlags)0x001000000008000c, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureTTSComponent, Speaker), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady = { "SynthesisReady", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureTTSComponent, SynthesisReady), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language = { "Language", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureTTSComponent, Language), METADATA_PARAMS(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice = { "Voice", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureTTSComponent, Voice), METADATA_PARAMS(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureTTSComponent, Key), METADATA_PARAMS(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AzureTTSComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region = { "Region", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAzureTTSComponent, Region), METADATA_PARAMS(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAzureTTSComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Speaker,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_SynthesisReady,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Language,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Voice,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Key,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAzureTTSComponent_Statics::NewProp_Region,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAzureTTSComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAzureTTSComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAzureTTSComponent_Statics::ClassParams = {
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
		METADATA_PARAMS(Z_Construct_UClass_UAzureTTSComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAzureTTSComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAzureTTSComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAzureTTSComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAzureTTSComponent, 3540371056);
	template<> FANTASIA_API UClass* StaticClass<UAzureTTSComponent>()
	{
		return UAzureTTSComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAzureTTSComponent(Z_Construct_UClass_UAzureTTSComponent, &UAzureTTSComponent::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UAzureTTSComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAzureTTSComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
