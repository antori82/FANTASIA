// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeFANTASIA_init() {}
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_FANTASIA()
	{
		static UPackage* ReturnPackage = nullptr;
		if (!ReturnPackage)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_SynthesizedInternalEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_IncomingASREvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_IncomingNLUEvent__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_GetPosteriorDelegate__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_FANTASIA_IncomingNeo4jResponseEvent__DelegateSignature,
			};
			static const UE4CodeGen_Private::FPackageParams PackageParams = {
				"/Script/FANTASIA",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x8137A12C,
				0x1005676F,
				METADATA_PARAMS(nullptr, 0)
			};
			UE4CodeGen_Private::ConstructUPackage(ReturnPackage, PackageParams);
		}
		return ReturnPackage;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
