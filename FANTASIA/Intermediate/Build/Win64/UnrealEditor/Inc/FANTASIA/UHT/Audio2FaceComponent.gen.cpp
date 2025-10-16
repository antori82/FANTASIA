// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Audio2FaceComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAudio2FaceComponent() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
FANTASIA_API UClass* Z_Construct_UClass_UAudio2FaceComponent();
FANTASIA_API UClass* Z_Construct_UClass_UAudio2FaceComponent_NoRegister();
FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_FANTASIA();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FLoadSceneCompleteEvent ***********************************************
struct Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics
{
	struct _Script_FANTASIA_eventLoadSceneCompleteEvent_Parms
	{
		bool sceneReady;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif // WITH_METADATA
	static void NewProp_sceneReady_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_sceneReady;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
void Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::NewProp_sceneReady_SetBit(void* Obj)
{
	((_Script_FANTASIA_eventLoadSceneCompleteEvent_Parms*)Obj)->sceneReady = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::NewProp_sceneReady = { "sceneReady", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(_Script_FANTASIA_eventLoadSceneCompleteEvent_Parms), &Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::NewProp_sceneReady_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::NewProp_sceneReady,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "LoadSceneCompleteEvent__DelegateSignature", Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::_Script_FANTASIA_eventLoadSceneCompleteEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::_Script_FANTASIA_eventLoadSceneCompleteEvent_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FLoadSceneCompleteEvent_DelegateWrapper(const FMulticastScriptDelegate& LoadSceneCompleteEvent, bool sceneReady)
{
	struct _Script_FANTASIA_eventLoadSceneCompleteEvent_Parms
	{
		bool sceneReady;
	};
	_Script_FANTASIA_eventLoadSceneCompleteEvent_Parms Parms;
	Parms.sceneReady=sceneReady ? true : false;
	LoadSceneCompleteEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FLoadSceneCompleteEvent *************************************************

// ********** Begin Class UAudio2FaceComponent Function Connect ************************************
struct Z_Construct_UFunction_UAudio2FaceComponent_Connect_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio2Face" },
		{ "DisplayName", "Connect" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAudio2FaceComponent_Connect_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAudio2FaceComponent, nullptr, "Connect", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_Connect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAudio2FaceComponent_Connect_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UAudio2FaceComponent_Connect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAudio2FaceComponent_Connect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAudio2FaceComponent::execConnect)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Connect();
	P_NATIVE_END;
}
// ********** End Class UAudio2FaceComponent Function Connect **************************************

// ********** Begin Class UAudio2FaceComponent Function LoadScene **********************************
struct Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics
{
	struct Audio2FaceComponent_eventLoadScene_Parms
	{
		FString sceneName;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio2Face" },
		{ "CPP_Default_sceneName", "Audio2Face.usd" },
		{ "DisplayName", "Load Scene" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_sceneName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::NewProp_sceneName = { "sceneName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Audio2FaceComponent_eventLoadScene_Parms, sceneName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::NewProp_sceneName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAudio2FaceComponent, nullptr, "LoadScene", Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::Audio2FaceComponent_eventLoadScene_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::Audio2FaceComponent_eventLoadScene_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAudio2FaceComponent_LoadScene()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAudio2FaceComponent_LoadScene_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAudio2FaceComponent::execLoadScene)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_sceneName);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->LoadScene(Z_Param_sceneName);
	P_NATIVE_END;
}
// ********** End Class UAudio2FaceComponent Function LoadScene ************************************

// ********** Begin Class UAudio2FaceComponent Function QueueAudio *********************************
struct Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics
{
	struct Audio2FaceComponent_eventQueueAudio_Parms
	{
		TArray<float> data;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Audio2Face" },
		{ "DisplayName", "Play Audio" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_data_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_data;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::NewProp_data_Inner = { "data", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::NewProp_data = { "data", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Audio2FaceComponent_eventQueueAudio_Parms, data), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::NewProp_data_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::NewProp_data,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAudio2FaceComponent, nullptr, "QueueAudio", Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::Audio2FaceComponent_eventQueueAudio_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::Audio2FaceComponent_eventQueueAudio_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAudio2FaceComponent::execQueueAudio)
{
	P_GET_TARRAY(float,Z_Param_data);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->QueueAudio(Z_Param_data);
	P_NATIVE_END;
}
// ********** End Class UAudio2FaceComponent Function QueueAudio ***********************************

// ********** Begin Class UAudio2FaceComponent *****************************************************
void UAudio2FaceComponent::StaticRegisterNativesUAudio2FaceComponent()
{
	UClass* Class = UAudio2FaceComponent::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Connect", &UAudio2FaceComponent::execConnect },
		{ "LoadScene", &UAudio2FaceComponent::execLoadScene },
		{ "QueueAudio", &UAudio2FaceComponent::execQueueAudio },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAudio2FaceComponent;
UClass* UAudio2FaceComponent::GetPrivateStaticClass()
{
	using TClass = UAudio2FaceComponent;
	if (!Z_Registration_Info_UClass_UAudio2FaceComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("Audio2FaceComponent"),
			Z_Registration_Info_UClass_UAudio2FaceComponent.InnerSingleton,
			StaticRegisterNativesUAudio2FaceComponent,
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
	return Z_Registration_Info_UClass_UAudio2FaceComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UAudio2FaceComponent_NoRegister()
{
	return UAudio2FaceComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAudio2FaceComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Audio2FaceComponent.h" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoadSceneComplete_MetaData[] = {
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_endpoint_MetaData[] = {
		{ "Category", "Audio2Face" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_port_MetaData[] = {
		{ "Category", "Audio2Face" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_A2FPlayerName_MetaData[] = {
		{ "Category", "Audio2Face" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_LoadSceneComplete;
	static const UECodeGen_Private::FStrPropertyParams NewProp_endpoint;
	static const UECodeGen_Private::FUInt32PropertyParams NewProp_port;
	static const UECodeGen_Private::FStrPropertyParams NewProp_A2FPlayerName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAudio2FaceComponent_Connect, "Connect" }, // 3869789427
		{ &Z_Construct_UFunction_UAudio2FaceComponent_LoadScene, "LoadScene" }, // 2160569508
		{ &Z_Construct_UFunction_UAudio2FaceComponent_QueueAudio, "QueueAudio" }, // 2141229298
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAudio2FaceComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_LoadSceneComplete = { "LoadSceneComplete", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudio2FaceComponent, LoadSceneComplete), Z_Construct_UDelegateFunction_FANTASIA_LoadSceneCompleteEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoadSceneComplete_MetaData), NewProp_LoadSceneComplete_MetaData) }; // 1229858432
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_endpoint = { "endpoint", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudio2FaceComponent, endpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_endpoint_MetaData), NewProp_endpoint_MetaData) };
const UECodeGen_Private::FUInt32PropertyParams Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_port = { "port", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudio2FaceComponent, port), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_port_MetaData), NewProp_port_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_A2FPlayerName = { "A2FPlayerName", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudio2FaceComponent, A2FPlayerName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_A2FPlayerName_MetaData), NewProp_A2FPlayerName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAudio2FaceComponent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_LoadSceneComplete,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_endpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_port,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_A2FPlayerName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UAudio2FaceComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UActorComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAudio2FaceComponent_Statics::ClassParams = {
	&UAudio2FaceComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UAudio2FaceComponent_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::PropPointers),
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UAudio2FaceComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAudio2FaceComponent()
{
	if (!Z_Registration_Info_UClass_UAudio2FaceComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAudio2FaceComponent.OuterSingleton, Z_Construct_UClass_UAudio2FaceComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAudio2FaceComponent.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAudio2FaceComponent);
UAudio2FaceComponent::~UAudio2FaceComponent() {}
// ********** End Class UAudio2FaceComponent *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h__Script_FANTASIA_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAudio2FaceComponent, UAudio2FaceComponent::StaticClass, TEXT("UAudio2FaceComponent"), &Z_Registration_Info_UClass_UAudio2FaceComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAudio2FaceComponent), 3849681363U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h__Script_FANTASIA_2303555324(TEXT("/Script/FANTASIA"),
	Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h__Script_FANTASIA_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h__Script_FANTASIA_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
