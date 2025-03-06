// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "LangGraphComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class GPTRoleType : uint8;
struct FChatTurn;
#ifdef FANTASIA_LangGraphComponent_generated_h
#error "LangGraphComponent.generated.h already included, missing '#pragma once' in LangGraphComponent.h"
#endif
#define FANTASIA_LangGraphComponent_generated_h

#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_9_DELEGATE \
FANTASIA_API void FIncomingLangGraphThreadCreateResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphThreadCreateResponseEvent, const FString& threadID);


#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_10_DELEGATE \
FANTASIA_API void FIncomingLangGraphResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphResponseEvent, const FString& LangGraphResponse, GPTRoleType role);


#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_11_DELEGATE \
FANTASIA_API void FIncomingLangGraphStreamResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingLangGraphStreamResponseEvent, const FString& LangGraphResponse, GPTRoleType role, bool endStream);


#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execlangGraphQuery); \
	DECLARE_FUNCTION(execdeleteLangGraphThread); \
	DECLARE_FUNCTION(execcreateLangGraphThread);


#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesULangGraphComponent(); \
	friend struct Z_Construct_UClass_ULangGraphComponent_Statics; \
public: \
	DECLARE_CLASS(ULangGraphComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(ULangGraphComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	ULangGraphComponent(ULangGraphComponent&&); \
	ULangGraphComponent(const ULangGraphComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULangGraphComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULangGraphComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ULangGraphComponent) \
	NO_API virtual ~ULangGraphComponent();


#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_13_PROLOG
#define FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_INCLASS_NO_PURE_DECLS \
	FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class ULangGraphComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Alex_Documents_Unreal_Projects_MyProject_Plugins_FANTASIA_Source_FANTASIA_Public_LangGraphComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
