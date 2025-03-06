// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIAEditor/Public/BayesianNetworkFactory.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBayesianNetworkFactory() {}

// Begin Cross Module References
FANTASIAEDITOR_API UClass* Z_Construct_UClass_UBayesianNetworkFactory();
FANTASIAEDITOR_API UClass* Z_Construct_UClass_UBayesianNetworkFactory_NoRegister();
UNREALED_API UClass* Z_Construct_UClass_UFactory();
UPackage* Z_Construct_UPackage__Script_FANTASIAEditor();
// End Cross Module References

// Begin Class UBayesianNetworkFactory
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
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "BayesianNetworkFactory.h" },
		{ "ModuleRelativePath", "Public/BayesianNetworkFactory.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBayesianNetworkFactory>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBayesianNetworkFactory_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UFactory,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIAEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBayesianNetworkFactory_Statics::DependentSingletons) < 16);
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
// End Class UBayesianNetworkFactory

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBayesianNetworkFactory, UBayesianNetworkFactory::StaticClass, TEXT("UBayesianNetworkFactory"), &Z_Registration_Info_UClass_UBayesianNetworkFactory, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBayesianNetworkFactory), 555479487U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_3601613316(TEXT("/Script/FANTASIAEditor"),
	Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIAEditor_Public_BayesianNetworkFactory_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
