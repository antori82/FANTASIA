// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/TTSThreadInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTTSThreadInterface() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
FANTASIA_API UClass* Z_Construct_UClass_UTTSThreadInterface();
FANTASIA_API UClass* Z_Construct_UClass_UTTSThreadInterface_NoRegister();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References

// Begin Interface UTTSThreadInterface
void UTTSThreadInterface::StaticRegisterNativesUTTSThreadInterface()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UTTSThreadInterface);
UClass* Z_Construct_UClass_UTTSThreadInterface_NoRegister()
{
	return UTTSThreadInterface::StaticClass();
}
struct Z_Construct_UClass_UTTSThreadInterface_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TTSThreadInterface.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ITTSThreadInterface>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UTTSThreadInterface_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UInterface,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTTSThreadInterface_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UTTSThreadInterface_Statics::ClassParams = {
	&UTTSThreadInterface::StaticClass,
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
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UTTSThreadInterface_Statics::Class_MetaDataParams), Z_Construct_UClass_UTTSThreadInterface_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UTTSThreadInterface()
{
	if (!Z_Registration_Info_UClass_UTTSThreadInterface.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UTTSThreadInterface.OuterSingleton, Z_Construct_UClass_UTTSThreadInterface_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UTTSThreadInterface.OuterSingleton;
}
template<> FANTASIA_API UClass* StaticClass<UTTSThreadInterface>()
{
	return UTTSThreadInterface::StaticClass();
}
UTTSThreadInterface::UTTSThreadInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UTTSThreadInterface);
UTTSThreadInterface::~UTTSThreadInterface() {}
// End Interface UTTSThreadInterface

// Begin Registration
struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UTTSThreadInterface, UTTSThreadInterface::StaticClass, TEXT("UTTSThreadInterface"), &Z_Registration_Info_UClass_UTTSThreadInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTTSThreadInterface), 1585089102U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_345810575(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Alice_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
