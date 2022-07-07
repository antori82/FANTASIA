// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/AWSPollyComponent.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAWSPollyComponent() {}
// Cross Module References
	FANTASIA_API UClass* Z_Construct_UClass_UAWSPollyComponent_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UAWSPollyComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FTTSTimedStruct();
	ENGINE_API UClass* Z_Construct_UClass_USoundWaveProcedural_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_TTSVoiceType();
// End Cross Module References
	DEFINE_FUNCTION(UAWSPollyComponent::execAWSPollyGetNotifies)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FTTSTimedStruct>*)Z_Param__Result=P_THIS->AWSPollyGetNotifies(Z_Param_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAWSPollyComponent::execAWSPollyGetLipSync)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FTTSTimedStruct>*)Z_Param__Result=P_THIS->AWSPollyGetLipSync(Z_Param_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAWSPollyComponent::execAWSPollyGetSound)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USoundWaveProcedural**)Z_Param__Result=P_THIS->AWSPollyGetSound(Z_Param_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAWSPollyComponent::execAWSPollySynthesize)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ssml);
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_GET_UBOOL(Z_Param_getLipSync);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AWSPollySynthesize(Z_Param_ssml,Z_Param_id,Z_Param_getLipSync);
		P_NATIVE_END;
	}
	void UAWSPollyComponent::StaticRegisterNativesUAWSPollyComponent()
	{
		UClass* Class = UAWSPollyComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AWSPollyGetLipSync", &UAWSPollyComponent::execAWSPollyGetLipSync },
			{ "AWSPollyGetNotifies", &UAWSPollyComponent::execAWSPollyGetNotifies },
			{ "AWSPollyGetSound", &UAWSPollyComponent::execAWSPollyGetSound },
			{ "AWSPollySynthesize", &UAWSPollyComponent::execAWSPollySynthesize },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics
	{
		struct AWSPollyComponent_eventAWSPollyGetLipSync_Parms
		{
			FString id;
			TArray<FTTSTimedStruct> ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetLipSync_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FTTSTimedStruct, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetLipSync_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get LipSync" },
		{ "Keywords", "AWS Plugin TTS" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAWSPollyComponent, nullptr, "AWSPollyGetLipSync", nullptr, nullptr, sizeof(AWSPollyComponent_eventAWSPollyGetLipSync_Parms), Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics
	{
		struct AWSPollyComponent_eventAWSPollyGetNotifies_Parms
		{
			FString id;
			TArray<FTTSTimedStruct> ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetNotifies_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FTTSTimedStruct, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetNotifies_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_ReturnValue_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Notifies" },
		{ "Keywords", "AWS Plugin TTS" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAWSPollyComponent, nullptr, "AWSPollyGetNotifies", nullptr, nullptr, sizeof(AWSPollyComponent_eventAWSPollyGetNotifies_Parms), Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics
	{
		struct AWSPollyComponent_eventAWSPollyGetSound_Parms
		{
			FString id;
			USoundWaveProcedural* ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetSound_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetSound_Parms, ReturnValue), Z_Construct_UClass_USoundWaveProcedural_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::NewProp_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Sound" },
		{ "Keywords", "AWS Plugin TTS" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAWSPollyComponent, nullptr, "AWSPollyGetSound", nullptr, nullptr, sizeof(AWSPollyComponent_eventAWSPollyGetSound_Parms), Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics
	{
		struct AWSPollyComponent_eventAWSPollySynthesize_Parms
		{
			FString ssml;
			FString id;
			bool getLipSync;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ssml;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_id;
		static void NewProp_getLipSync_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_getLipSync;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_ssml = { "ssml", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollySynthesize_Parms, ssml), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollySynthesize_Parms, id), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_getLipSync_SetBit(void* Obj)
	{
		((AWSPollyComponent_eventAWSPollySynthesize_Parms*)Obj)->getLipSync = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_getLipSync = { "getLipSync", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AWSPollyComponent_eventAWSPollySynthesize_Parms), &Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_getLipSync_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_ssml,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_id,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_getLipSync,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "TTS Start" },
		{ "Keywords", "AWS Plugin TTS" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAWSPollyComponent, nullptr, "AWSPollySynthesize", nullptr, nullptr, sizeof(AWSPollyComponent_eventAWSPollySynthesize_Parms), Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAWSPollyComponent_NoRegister()
	{
		return UAWSPollyComponent::StaticClass();
	}
	struct Z_Construct_UClass_UAWSPollyComponent_Statics
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
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Voice_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Voice;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_voiceType_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_voiceType_MetaData[];
#endif
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_voiceType;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AccessKey_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_AccessKey;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SecretAccessKey_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_SecretAccessKey;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAWSPollyComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAWSPollyComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync, "AWSPollyGetLipSync" }, // 1351864615
		{ &Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies, "AWSPollyGetNotifies" }, // 1994391926
		{ &Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound, "AWSPollyGetSound" }, // 3111266339
		{ &Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize, "AWSPollySynthesize" }, // 2329783264
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "AmazonWebServices" },
		{ "Comment", "//using namespace std;\n" },
		{ "IncludePath", "AWSPollyComponent.h" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
		{ "ToolTip", "using namespace std;" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker = { "Speaker", nullptr, (EPropertyFlags)0x001000000008000c, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, Speaker), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady = { "SynthesisReady", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, SynthesisReady), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice = { "Voice", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, Voice), METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType = { "voiceType", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, voiceType), Z_Construct_UEnum_FANTASIA_TTSVoiceType, METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey = { "AccessKey", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, AccessKey), METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey = { "SecretAccessKey", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, SecretAccessKey), METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAWSPollyComponent_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAWSPollyComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAWSPollyComponent>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAWSPollyComponent_Statics::ClassParams = {
		&UAWSPollyComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAWSPollyComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::PropPointers),
		0,
		0x00A000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAWSPollyComponent()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAWSPollyComponent_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAWSPollyComponent, 429506356);
	template<> FANTASIA_API UClass* StaticClass<UAWSPollyComponent>()
	{
		return UAWSPollyComponent::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAWSPollyComponent(Z_Construct_UClass_UAWSPollyComponent, &UAWSPollyComponent::StaticClass, TEXT("/Script/FANTASIA"), TEXT("UAWSPollyComponent"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAWSPollyComponent);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
