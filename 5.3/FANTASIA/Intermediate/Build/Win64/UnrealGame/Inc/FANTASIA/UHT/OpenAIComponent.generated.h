// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "OpenAIComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FChatTurn;
#ifdef FANTASIA_OpenAIComponent_generated_h
#error "OpenAIComponent.generated.h already included, missing '#pragma once' in OpenAIComponent.h"
#endif
#define FANTASIA_OpenAIComponent_generated_h

#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_8_DELEGATE \
FANTASIA_API void FIncomingGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingGPTResponseEvent, const FString& GPTResponse);


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_9_DELEGATE \
FANTASIA_API void FIncomingChatGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingChatGPTResponseEvent, const FString& chatGPTResponse, const FString& role);


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_22_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FChatTurn_Statics; \
	FANTASIA_API static class UScriptStruct* StaticStruct();


template<> FANTASIA_API UScriptStruct* StaticStruct<struct FChatTurn>();

#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_SPARSE_DATA
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execgetChatGPTCompletion); \
	DECLARE_FUNCTION(execgetGPTCompletion);


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_ACCESSORS
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUOpenAIComponent(); \
	friend struct Z_Construct_UClass_UOpenAIComponent_Statics; \
public: \
	DECLARE_CLASS(UOpenAIComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UOpenAIComponent)


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UOpenAIComponent(UOpenAIComponent&&); \
	NO_API UOpenAIComponent(const UOpenAIComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UOpenAIComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UOpenAIComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UOpenAIComponent) \
	NO_API virtual ~UOpenAIComponent();


#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_31_PROLOG
#define FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_SPARSE_DATA \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_ACCESSORS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_INCLASS_NO_PURE_DECLS \
	FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_34_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UOpenAIComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h


#define FOREACH_ENUM_CHATGPTROLETYPE(op) \
	op(ChatGPTRoleType::SYSTEM) \
	op(ChatGPTRoleType::ASSISTANT) \
	op(ChatGPTRoleType::USER) \
	op(ChatGPTRoleType::FUNCTION) 

enum class ChatGPTRoleType : uint8;
template<> struct TIsUEnumClass<ChatGPTRoleType> { enum { Value = true }; };
template<> FANTASIA_API UEnum* StaticEnum<ChatGPTRoleType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
