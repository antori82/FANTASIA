// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "../../../../../../Source/FANTASIA/Public/TTSThreadInterface.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeTTSThreadInterface() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UInterface();
	FANTASIA_API UClass* Z_Construct_UClass_UTTSThreadInterface();
	FANTASIA_API UClass* Z_Construct_UClass_UTTSThreadInterface_NoRegister();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
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
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UTTSThreadInterface_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UInterface,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UTTSThreadInterface_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UTTSThreadInterface_Statics::Class_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/TTSThreadInterface.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UTTSThreadInterface_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ITTSThreadInterface>::IsAbstract,
	};
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
	struct Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UTTSThreadInterface, UTTSThreadInterface::StaticClass, TEXT("UTTSThreadInterface"), &Z_Registration_Info_UClass_UTTSThreadInterface, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UTTSThreadInterface), 3204879705U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_1819871832(TEXT("/Script/FANTASIA"),
		Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
