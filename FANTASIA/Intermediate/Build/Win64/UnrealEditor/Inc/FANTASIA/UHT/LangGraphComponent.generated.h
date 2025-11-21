// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "LangGraphComponent.h"

#ifdef FANTASIA_LangGraphComponent_generated_h
#error "LangGraphComponent.generated.h already included, missing '#pragma once' in LangGraphComponent.h"
#endif
#define FANTASIA_LangGraphComponent_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

enum class GPTRoleType : uint8;
struct FChatTurn;

// ********** Begin Delegate FIncomingLangGraphThreadCreateResponseEvent ***************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_9_DELEGATE \
FANTASIA_API void FIncomingLangGraphThreadCreateResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphThreadCreateResponseEvent, const FString& threadID);


// ********** End Delegate FIncomingLangGraphThreadCreateResponseEvent *****************************

// ********** Begin Delegate FIncomingLangGraphResponseEvent ***************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_10_DELEGATE \
FANTASIA_API void FIncomingLangGraphResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphResponseEvent, const FString& LangGraphResponse, GPTRoleType role);


// ********** End Delegate FIncomingLangGraphResponseEvent *****************************************

// ********** Begin Delegate FIncomingLangGraphStreamResponseEvent *********************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_11_DELEGATE \
FANTASIA_API void FIncomingLangGraphStreamResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphStreamResponseEvent, const FString& LangGraphResponse, GPTRoleType role, bool endStream);


// ********** End Delegate FIncomingLangGraphStreamResponseEvent ***********************************

// ********** Begin Class ULangGraphComponent ******************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execlangGraphQuery); \
	DECLARE_FUNCTION(execdeleteLangGraphThread); \
	DECLARE_FUNCTION(execcreateLangGraphThread);


FANTASIA_API UClass* Z_Construct_UClass_ULangGraphComponent_NoRegister();

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULangGraphComponent(); \
	friend struct Z_Construct_UClass_ULangGraphComponent_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_ULangGraphComponent_NoRegister(); \
public: \
	DECLARE_CLASS2(ULangGraphComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_ULangGraphComponent_NoRegister) \
	DECLARE_SERIALIZER(ULangGraphComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ULangGraphComponent(ULangGraphComponent&&) = delete; \
	ULangGraphComponent(const ULangGraphComponent&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULangGraphComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULangGraphComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULangGraphComponent) \
	NO_API virtual ~ULangGraphComponent();


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_13_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_INCLASS_NO_PURE_DECLS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ULangGraphComponent;

// ********** End Class ULangGraphComponent ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
