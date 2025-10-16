// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ElevenLabsTTSComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeElevenLabsTTSComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
ENGINE_API UClass* Z_Construct_UClass_USoundWaveProcedural_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UAudio2FaceComponent_NoRegister();
FANTASIA_API UClass* Z_Construct_UClass_UElevenLabsTTSComponent();
FANTASIA_API UClass* Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_PartialSynthesizedEvent__DelegateSignature();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UElevenLabsTTSComponent Function TTSGetPartialRawSound *******************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics
{
	struct ElevenLabsTTSComponent_eventTTSGetPartialRawSound_Parms
	{
		FString id;
		TArray<float> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Streaming Raw Sound" },
		{ "Keywords", "ElevenLabs TTS" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventTTSGetPartialRawSound_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventTTSGetPartialRawSound_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "TTSGetPartialRawSound", Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::PropPointers), sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::ElevenLabsTTSComponent_eventTTSGetPartialRawSound_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::ElevenLabsTTSComponent_eventTTSGetPartialRawSound_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execTTSGetPartialRawSound)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<float>*)Z_Param__Result=P_THIS->TTSGetPartialRawSound(Z_Param_id);
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function TTSGetPartialRawSound *********************

// ********** Begin Class UElevenLabsTTSComponent Function TTSGetRawSound **************************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics
{
	struct ElevenLabsTTSComponent_eventTTSGetRawSound_Parms
	{
		FString id;
		TArray<float> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Raw Sound" },
		{ "Keywords", "ElevenLabs TTS" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventTTSGetRawSound_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventTTSGetRawSound_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "TTSGetRawSound", Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::PropPointers), sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::ElevenLabsTTSComponent_eventTTSGetRawSound_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::ElevenLabsTTSComponent_eventTTSGetRawSound_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execTTSGetRawSound)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<float>*)Z_Param__Result=P_THIS->TTSGetRawSound(Z_Param_id);
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function TTSGetRawSound ****************************

// ********** Begin Class UElevenLabsTTSComponent Function TTSGetSound *****************************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics
{
	struct ElevenLabsTTSComponent_eventTTSGetSound_Parms
	{
		FString id;
		USoundWaveProcedural* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Sound" },
		{ "Keywords", "ElevenLabs TTS" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventTTSGetSound_Parms, id), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventTTSGetSound_Parms, ReturnValue), Z_Construct_UClass_USoundWaveProcedural_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "TTSGetSound", Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::PropPointers), sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::ElevenLabsTTSComponent_eventTTSGetSound_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::ElevenLabsTTSComponent_eventTTSGetSound_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execTTSGetSound)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(USoundWaveProcedural**)Z_Param__Result=P_THIS->TTSGetSound(Z_Param_id);
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function TTSGetSound *******************************

// ********** Begin Class UElevenLabsTTSComponent Function TTSSynthesize ***************************
struct Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics
{
	struct ElevenLabsTTSComponent_eventTTSSynthesize_Parms
	{
		FString ssml;
		FString id;
		bool stream;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "TTS Start" },
		{ "Keywords", "ElevenLabs TTS" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ssml;
	static const UECodeGen_Private::FStrPropertyParams NewProp_id;
	static void NewProp_stream_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_stream;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::NewProp_ssml = { "ssml", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventTTSSynthesize_Parms, ssml), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ElevenLabsTTSComponent_eventTTSSynthesize_Parms, id), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::NewProp_stream_SetBit(void* Obj)
{
	((ElevenLabsTTSComponent_eventTTSSynthesize_Parms*)Obj)->stream = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::NewProp_stream = { "stream", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ElevenLabsTTSComponent_eventTTSSynthesize_Parms), &Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::NewProp_stream_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::NewProp_ssml,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::NewProp_id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::NewProp_stream,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UElevenLabsTTSComponent, nullptr, "TTSSynthesize", Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::PropPointers), sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::ElevenLabsTTSComponent_eventTTSSynthesize_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::Function_MetaDataParams), Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::ElevenLabsTTSComponent_eventTTSSynthesize_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UElevenLabsTTSComponent::execTTSSynthesize)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_ssml);
	P_GET_PROPERTY(FStrProperty,Z_Param_id);
	P_GET_UBOOL(Z_Param_stream);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->TTSSynthesize(Z_Param_ssml,Z_Param_id,Z_Param_stream);
	P_NATIVE_END;
}
// ********** End Class UElevenLabsTTSComponent Function TTSSynthesize *****************************

// ********** Begin Class UElevenLabsTTSComponent **************************************************
void UElevenLabsTTSComponent::StaticRegisterNativesUElevenLabsTTSComponent()
{
	UClass* Class = UElevenLabsTTSComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "TTSGetPartialRawSound", &UElevenLabsTTSComponent::execTTSGetPartialRawSound },
		{ "TTSGetRawSound", &UElevenLabsTTSComponent::execTTSGetRawSound },
		{ "TTSGetSound", &UElevenLabsTTSComponent::execTTSGetSound },
		{ "TTSSynthesize", &UElevenLabsTTSComponent::execTTSSynthesize },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UElevenLabsTTSComponent;
UClass* UElevenLabsTTSComponent::GetPrivateStaticClass()
{
	using TClass = UElevenLabsTTSComponent;
	if (!Z_Registration_Info_UClass_UElevenLabsTTSComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("ElevenLabsTTSComponent"),
			Z_Registration_Info_UClass_UElevenLabsTTSComponent.InnerSingleton,
			StaticRegisterNativesUElevenLabsTTSComponent,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UElevenLabsTTSComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UElevenLabsTTSComponent_NoRegister()
{
	return UElevenLabsTTSComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UElevenLabsTTSComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "IncludePath", "ElevenLabsTTSComponent.h" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_A2Fpointer_MetaData[] = {
		{ "Category", "TTS" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SynthesisReady_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PartialSynthesisReady_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VoiceID_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelID_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_stability_MetaData[] = {
		{ "Category", "Voice Settings" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_similarity_boost_MetaData[] = {
		{ "Category", "Voice Settings" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_style_MetaData[] = {
		{ "Category", "Voice Settings" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_use_speaker_boost_MetaData[] = {
		{ "Category", "Voice Settings" },
		{ "ModuleRelativePath", "Public/ElevenLabsTTSComponent.h" },
		{ "UIMax", "1.0" },
		{ "UIMin", "0.0" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_A2Fpointer;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_SynthesisReady;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_PartialSynthesisReady;
	static const UECodeGen_Private::FStrPropertyParams NewProp_VoiceID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModelID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_stability;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_similarity_boost;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_style;
	static void NewProp_use_speaker_boost_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_use_speaker_boost;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetPartialRawSound, "TTSGetPartialRawSound" }, // 3666814148
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetRawSound, "TTSGetRawSound" }, // 1026918463
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_TTSGetSound, "TTSGetSound" }, // 3119934098
		{ &Z_Construct_UFunction_UElevenLabsTTSComponent_TTSSynthesize, "TTSSynthesize" }, // 2041763989
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UElevenLabsTTSComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_A2Fpointer = { "A2Fpointer", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, A2Fpointer), Z_Construct_UClass_UAudio2FaceComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_A2Fpointer_MetaData), NewProp_A2Fpointer_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_SynthesisReady = { "SynthesisReady", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, SynthesisReady), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SynthesisReady_MetaData), NewProp_SynthesisReady_MetaData) }; // 1658130564
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_PartialSynthesisReady = { "PartialSynthesisReady", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, PartialSynthesisReady), Z_Construct_UDelegateFunction_FANTASIA_PartialSynthesizedEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PartialSynthesisReady_MetaData), NewProp_PartialSynthesisReady_MetaData) }; // 965322784
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_VoiceID = { "VoiceID", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, VoiceID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VoiceID_MetaData), NewProp_VoiceID_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_ModelID = { "ModelID", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, ModelID), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelID_MetaData), NewProp_ModelID_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, Key), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Key_MetaData), NewProp_Key_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_stability = { "stability", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, stability), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_stability_MetaData), NewProp_stability_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_similarity_boost = { "similarity_boost", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, similarity_boost), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_similarity_boost_MetaData), NewProp_similarity_boost_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_style = { "style", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UElevenLabsTTSComponent, style), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_style_MetaData), NewProp_style_MetaData) };
void Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_use_speaker_boost_SetBit(void* Obj)
{
	((UElevenLabsTTSComponent*)Obj)->use_speaker_boost = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_use_speaker_boost = { "use_speaker_boost", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UElevenLabsTTSComponent), &Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_use_speaker_boost_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_use_speaker_boost_MetaData), NewProp_use_speaker_boost_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UElevenLabsTTSComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_A2Fpointer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_SynthesisReady,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_PartialSynthesisReady,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_VoiceID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_ModelID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_Key,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_stability,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_similarity_boost,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_style,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UElevenLabsTTSComponent_Statics::NewProp_use_speaker_boost,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UElevenLabsTTSComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UElevenLabsTTSComponent_Statics::ClassParams = {
	&UElevenLabsTTSComponent::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UElevenLabsTTSComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::PropPointers),
	0,
	0x00A000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UElevenLabsTTSComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UElevenLabsTTSComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UElevenLabsTTSComponent()
{
	if (!Z_Registration_Info_UClass_UElevenLabsTTSComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UElevenLabsTTSComponent.OuterSingleton, Z_Construct_UClass_UElevenLabsTTSComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UElevenLabsTTSComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UElevenLabsTTSComponent);
UElevenLabsTTSComponent::~UElevenLabsTTSComponent() {}
// ********** End Class UElevenLabsTTSComponent ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h__Script_FANTASIA_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UElevenLabsTTSComponent, UElevenLabsTTSComponent::StaticClass, TEXT("UElevenLabsTTSComponent"), &Z_Registration_Info_UClass_UElevenLabsTTSComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UElevenLabsTTSComponent), 1715922388U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h__Script_FANTASIA_432945862(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h__Script_FANTASIA_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_ElevenLabsTTSComponent_h__Script_FANTASIA_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
