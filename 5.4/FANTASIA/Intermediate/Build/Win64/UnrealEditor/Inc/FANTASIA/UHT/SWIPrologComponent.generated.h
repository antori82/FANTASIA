// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SWIPrologComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FANTASIA_SWIPrologComponent_generated_h
#error "SWIPrologComponent.generated.h already included, missing '#pragma once' in SWIPrologComponent.h"
#endif
#define FANTASIA_SWIPrologComponent_generated_h

#define FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execstartProlog); \
	DECLARE_FUNCTION(execsubmitQuery);


#define FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_25_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSWIPrologComponent(); \
	friend struct Z_Construct_UClass_USWIPrologComponent_Statics; \
public: \
	DECLARE_CLASS(USWIPrologComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(USWIPrologComponent) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_25_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	USWIPrologComponent(USWIPrologComponent&&); \
	USWIPrologComponent(const USWIPrologComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USWIPrologComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USWIPrologComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USWIPrologComponent) \
	NO_API virtual ~USWIPrologComponent();


#define FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_22_PROLOG
#define FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_25_INCLASS_NO_PURE_DECLS \
	FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h_25_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class USWIPrologComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_Lorenzo_Documents_Unreal_Projects_DeclarativeEngine_Plugins_FANTASIA_Source_FANTASIA_Public_SWIPrologComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS