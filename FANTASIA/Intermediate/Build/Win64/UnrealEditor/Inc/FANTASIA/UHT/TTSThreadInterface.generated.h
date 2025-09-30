// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "TTSThreadInterface.h"

#ifdef FANTASIA_TTSThreadInterface_generated_h
#error "TTSThreadInterface.generated.h already included, missing '#pragma once' in TTSThreadInterface.h"
#endif
#define FANTASIA_TTSThreadInterface_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Interface UTTSThreadInterface **************************************************
FANTASIA_API UClass* Z_Construct_UClass_UTTSThreadInterface_NoRegister();

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	FANTASIA_API UTTSThreadInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UTTSThreadInterface(UTTSThreadInterface&&) = delete; \
	UTTSThreadInterface(const UTTSThreadInterface&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(FANTASIA_API, UTTSThreadInterface); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UTTSThreadInterface); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UTTSThreadInterface) \
	virtual ~UTTSThreadInterface() = default;


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_12_GENERATED_UINTERFACE_BODY() \
private: \
	static void StaticRegisterNativesUTTSThreadInterface(); \
	friend struct Z_Construct_UClass_UTTSThreadInterface_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_UTTSThreadInterface_NoRegister(); \
public: \
	DECLARE_CLASS2(UTTSThreadInterface, UInterface, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Interface), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_UTTSThreadInterface_NoRegister) \
	DECLARE_SERIALIZER(UTTSThreadInterface)


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_12_GENERATED_BODY \
	PRAGMA_DISABLE_DEPRECATION_WARNINGS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_12_GENERATED_UINTERFACE_BODY() \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_12_ENHANCED_CONSTRUCTORS \
private: \
	PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_12_INCLASS_IINTERFACE_NO_PURE_DECLS \
protected: \
	virtual ~ITTSThreadInterface() {} \
public: \
	typedef UTTSThreadInterface UClassType; \
	typedef ITTSThreadInterface ThisClass; \
	virtual UObject* _getUObject() const { return nullptr; }


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_9_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_20_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h_12_INCLASS_IINTERFACE_NO_PURE_DECLS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UTTSThreadInterface;

// ********** End Interface UTTSThreadInterface ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_TTSThreadInterface_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
