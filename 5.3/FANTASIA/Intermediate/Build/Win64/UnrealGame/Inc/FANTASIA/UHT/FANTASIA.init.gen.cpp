// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFANTASIA_init() {}
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_FANTASIA;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_FANTASIA()
	{
		if (!Z_Registration_Info_UPackage__Script_FANTASIA.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/FANTASIA",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x767FD6A7,
				0x2E81D895,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_FANTASIA.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_FANTASIA.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_FANTASIA(Z_Construct_UPackage__Script_FANTASIA, TEXT("/Script/FANTASIA"), Z_Registration_Info_UPackage__Script_FANTASIA, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x767FD6A7, 0x2E81D895));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
