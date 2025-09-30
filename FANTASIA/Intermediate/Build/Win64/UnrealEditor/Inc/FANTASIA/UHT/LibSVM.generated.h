// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "LibSVM.h"

#ifdef FANTASIA_LibSVM_generated_h
#error "LibSVM.generated.h already included, missing '#pragma once' in LibSVM.h"
#endif
#define FANTASIA_LibSVM_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

struct FCLFResult;
struct FCLFSample;

// ********** Begin ScriptStruct FCLFSample ********************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_16_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FCLFSample_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FCLFSample;
// ********** End ScriptStruct FCLFSample **********************************************************

// ********** Begin ScriptStruct FCLFResult ********************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_31_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FCLFResult_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FCLFResult;
// ********** End ScriptStruct FCLFResult **********************************************************

// ********** Begin ScriptStruct FSVMParameters ****************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_60_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FSVMParameters_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


struct FSVMParameters;
// ********** End ScriptStruct FSVMParameters ******************************************************

// ********** Begin Class ULibSVM ******************************************************************
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_102_RPC_WRAPPERS \
	DECLARE_FUNCTION(execload); \
	DECLARE_FUNCTION(execpredict); \
	DECLARE_FUNCTION(exectrain);


FANTASIA_API UClass* Z_Construct_UClass_ULibSVM_NoRegister();

#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_102_INCLASS \
private: \
	static void StaticRegisterNativesULibSVM(); \
	friend struct Z_Construct_UClass_ULibSVM_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend FANTASIA_API UClass* Z_Construct_UClass_ULibSVM_NoRegister(); \
public: \
	DECLARE_CLASS2(ULibSVM, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/FANTASIA"), Z_Construct_UClass_ULibSVM_NoRegister) \
	DECLARE_SERIALIZER(ULibSVM)


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_102_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ULibSVM(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULibSVM) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ULibSVM); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULibSVM); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ULibSVM(ULibSVM&&) = delete; \
	ULibSVM(const ULibSVM&) = delete; \
	NO_API virtual ~ULibSVM();


#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_99_PROLOG
#define FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_102_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_102_RPC_WRAPPERS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_102_INCLASS \
	FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h_102_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ULibSVM;

// ********** End Class ULibSVM ********************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_FANTASIADevelopment_Plugins_FANTASIA_FANTASIA_Source_FANTASIA_Public_LibSVM_h

// ********** Begin Enum LibSVMTypes ***************************************************************
#define FOREACH_ENUM_LIBSVMTYPES(op) \
	op(LibSVMTypes::C_SVC) \
	op(LibSVMTypes::NU_SVC) \
	op(LibSVMTypes::ONE_CLASS_SVM) \
	op(LibSVMTypes::EPSILON_SVR) \
	op(LibSVMTypes::NU_SVR) 

enum class LibSVMTypes : uint8;
template<> struct TIsUEnumClass<LibSVMTypes> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<LibSVMTypes>();
// ********** End Enum LibSVMTypes *****************************************************************

// ********** Begin Enum LibSVMKernels *************************************************************
#define FOREACH_ENUM_LIBSVMKERNELS(op) \
	op(LibSVMKernels::LINEAR) \
	op(LibSVMKernels::POLYNOMIAL) \
	op(LibSVMKernels::RBF) \
	op(LibSVMKernels::SIGMOID) 

enum class LibSVMKernels : uint8;
template<> struct TIsUEnumClass<LibSVMKernels> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<LibSVMKernels>();
// ********** End Enum LibSVMKernels ***************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
