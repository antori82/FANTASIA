// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIAEditor/Public/BayesianNetworkFactory.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBayesianNetworkFactory() {}
// Cross Module References
	FANTASIAEDITOR_API UClass* Z_Construct_UClass_UBayesianNetworkFactory();
	FANTASIAEDITOR_API UClass* Z_Construct_UClass_UBayesianNetworkFactory_NoRegister();
	UNREALED_API UClass* Z_Construct_UClass_UFactory();
	UPackage* Z_Construct_UPackage__Script_FANTASIAEditor();
// End Cross Module References
	void UBayesianNetworkFactory::StaticRegisterNativesUBayesianNetworkFactory()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBayesianNetworkFactory);
	UClass* Z_Construct_UClass_UBayesianNetworkFactory_NoRegister()
	{
		return UBayesianNetworkFactory::StaticClass();
	}
	struct Z_Construct_UClass_UBayesianNetworkFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UBayesianNetworkFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIAEditor,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetworkFactory_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UBayesianNetworkFactory_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "BayesianNetworkFactory.h" },
		{ "ModuleRelativePath", "Public/BayesianNetworkFactory.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UBayesianNetworkFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBayesianNetworkFactory>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UBayesianNetworkFactory_Statics::ClassParams = {
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetworkFactory_Statics::Class_MetaDataParams), Z_Construct_UClass_UBayesianNetworkFactory_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_UBayesianNetworkFactory()
	{
		if (!Z_Registration_Info_UClass_UBayesianNetworkFactory.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBayesianNetworkFactory.OuterSingleton, Z_Construct_UClass_UBayesianNetworkFactory_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UBayesianNetworkFactory.OuterSingleton;
	}
	template<> FANTASIAEDITOR_API UClass* StaticClass<UBayesianNetworkFactory>()
	{
		return UBayesianNetworkFactory::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UBayesianNetworkFactory);
	UBayesianNetworkFactory::~UBayesianNetworkFactory() {}
	struct Z_CompiledInDeferFile_FID_Bastian_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Bastian_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UBayesianNetworkFactory, UBayesianNetworkFactory::StaticClass, TEXT("UBayesianNetworkFactory"), &Z_Registration_Info_UClass_UBayesianNetworkFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBayesianNetworkFactory), 3691850281U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Bastian_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_1657460211(TEXT("/Script/FANTASIAEditor"),
		Z_CompiledInDeferFile_FID_Bastian_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Bastian_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
