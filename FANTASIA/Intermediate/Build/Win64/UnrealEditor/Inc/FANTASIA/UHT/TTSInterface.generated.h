// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TTSInterface.h"

#ifdef FANTASIA_TTSInterface_generated_h
#error "TTSInterface.generated.h already included, missing '#pragma once' in TTSInterface.h"
#endif
#define FANTASIA_TTSInterface_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class USoundWave;

// ********** Begin Interface UTTSInterface ********************************************************
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execTTSGetRawSound); \
	DECLARE_FUNCTION(execTTSGetSound); \
	DECLARE_FUNCTION(execTTSSynthesize);


FANTASIA_API UClass* Z_Construct_UClass_UTTSInterface_NoRegister();

#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	FANTASIA_API UTTSInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UTTSInterface(UTTSInterface&&) = delete; \
	UTTSInterface(const UTTSInterface&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(FANTASIA_API, UTTSInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UTTSInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UTTSInterface) \
	virtual ~UTTSInterface() = default;


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUTTSInterface(); \
	friend struct Z_Construct_UClass_UTTSInterface_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UTTSInterface_NoRegister(); \
public: \
	DECLARE_CLASS2(UTTSInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UTTSInterface_NoRegister) \
	DECLARE_SERIALIZER(UTTSInterface)


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_GENERATED_UINTERFACE_BODY() \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~ITTSInterface() {} \
public: \
	typedef UTTSInterface UClassType; \
	typedef ITTSInterface ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_7_PROLOG
#define FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_18_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h_10_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UTTSInterface;

// ********** End Interface UTTSInterface **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIATemplate_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSInterface_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
