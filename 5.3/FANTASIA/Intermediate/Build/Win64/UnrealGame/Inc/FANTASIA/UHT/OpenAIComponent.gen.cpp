// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "../../../../../../Source/FANTASIA/Public/OpenAIComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOpenAIComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	FANTASIA_API UClass* Z_Construct_UClass_UOpenAIComponent();
	FANTASIA_API UClass* Z_Construct_UClass_UOpenAIComponent_NoRegister();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_ChatGPTRoleType();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FChatTurn();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventIncomingGPTResponseEvent_Parms
		{
			FString GPTResponse;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_GPTResponse;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::NewProp_GPTResponse = { "GPTResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms, GPTResponse), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::NewProp_GPTResponse,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingGPTResponseEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms) < MAX_uint16);
	UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FIncomingGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingGPTResponseEvent, const FString& GPTResponse)
{
	struct _Script_FANTASIA_eventIncomingGPTResponseEvent_Parms
	{
		FString GPTResponse;
	};
	_Script_FANTASIA_eventIncomingGPTResponseEvent_Parms Parms;
	Parms.GPTResponse=GPTResponse;
	IncomingGPTResponseEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
	struct Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics
	{
		struct _Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms
		{
			FString chatGPTResponse;
			FString role;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_chatGPTResponse;
		static const UECodeGen_Private::FStrPropertyParams NewProp_role;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::NewProp_chatGPTResponse = { "chatGPTResponse", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms, chatGPTResponse), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::NewProp_role = { "role", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms, role), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::NewProp_chatGPTResponse,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::NewProp_role,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_FANTASIA, nullptr, "IncomingChatGPTResponseEvent__DelegateSignature", nullptr, nullptr, Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms) < MAX_uint16);
	UFunction* Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FIncomingChatGPTResponseEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingChatGPTResponseEvent, const FString& chatGPTResponse, const FString& role)
{
	struct _Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms
	{
		FString chatGPTResponse;
		FString role;
	};
	_Script_FANTASIA_eventIncomingChatGPTResponseEvent_Parms Parms;
	Parms.chatGPTResponse=chatGPTResponse;
	Parms.role=role;
	IncomingChatGPTResponseEvent.ProcessMulticastDelegate<UObject>(&Parms);
}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ChatGPTRoleType;
	static UEnum* ChatGPTRoleType_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ChatGPTRoleType.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ChatGPTRoleType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_FANTASIA_ChatGPTRoleType, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("ChatGPTRoleType"));
		}
		return Z_Registration_Info_UEnum_ChatGPTRoleType.OuterSingleton;
	}
	template<> FANTASIA_API UEnum* StaticEnum<ChatGPTRoleType>()
	{
		return ChatGPTRoleType_StaticEnum();
	}
	struct Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enumerators[] = {
		{ "ChatGPTRoleType::SYSTEM", (int64)ChatGPTRoleType::SYSTEM },
		{ "ChatGPTRoleType::ASSISTANT", (int64)ChatGPTRoleType::ASSISTANT },
		{ "ChatGPTRoleType::USER", (int64)ChatGPTRoleType::USER },
		{ "ChatGPTRoleType::FUNCTION", (int64)ChatGPTRoleType::FUNCTION },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enum_MetaDataParams[] = {
		{ "ASSISTANT.DisplayName", "ASSISTANT" },
		{ "ASSISTANT.Name", "ChatGPTRoleType::ASSISTANT" },
		{ "BlueprintType", "true" },
		{ "FUNCTION.DisplayName", "FUNCTION" },
		{ "FUNCTION.Name", "ChatGPTRoleType::FUNCTION" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
		{ "SYSTEM.DisplayName", "SYSTEM" },
		{ "SYSTEM.Name", "ChatGPTRoleType::SYSTEM" },
		{ "USER.DisplayName", "USER" },
		{ "USER.Name", "ChatGPTRoleType::USER" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		"ChatGPTRoleType",
		"ChatGPTRoleType",
		Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enumerators,
		RF_Public|RF_Transient|RF_MarkAsNative,
		UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enumerators),
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::Enum_MetaDataParams)
	};
	UEnum* Z_Construct_UEnum_FANTASIA_ChatGPTRoleType()
	{
		if (!Z_Registration_Info_UEnum_ChatGPTRoleType.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ChatGPTRoleType.InnerSingleton, Z_Construct_UEnum_FANTASIA_ChatGPTRoleType_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ChatGPTRoleType.InnerSingleton;
	}
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ChatTurn;
class UScriptStruct* FChatTurn::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ChatTurn.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ChatTurn.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FChatTurn, (UObject*)Z_Construct_UPackage__Script_FANTASIA(), TEXT("ChatTurn"));
	}
	return Z_Registration_Info_UScriptStruct_ChatTurn.OuterSingleton;
}
template<> FANTASIA_API UScriptStruct* StaticStruct<FChatTurn>()
{
	return FChatTurn::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FChatTurn_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
		static const UECodeGen_Private::FBytePropertyParams NewProp_role_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_role_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_role;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_content_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_content;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FChatTurn_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FChatTurn_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FChatTurn>();
	}
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role_MetaData[] = {
		{ "Category", "ChatTurn" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role = { "role", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChatTurn, role), Z_Construct_UEnum_FANTASIA_ChatGPTRoleType, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role_MetaData), Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role_MetaData) }; // 3762617820
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_content_MetaData[] = {
		{ "Category", "ChatTurn" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_content = { "content", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FChatTurn, content), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_content_MetaData), Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_content_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FChatTurn_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_role,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FChatTurn_Statics::NewProp_content,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FChatTurn_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
		nullptr,
		&NewStructOps,
		"ChatTurn",
		Z_Construct_UScriptStruct_FChatTurn_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChatTurn_Statics::PropPointers),
		sizeof(FChatTurn),
		alignof(FChatTurn),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChatTurn_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FChatTurn_Statics::Struct_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FChatTurn_Statics::PropPointers) < 2048);
	UScriptStruct* Z_Construct_UScriptStruct_FChatTurn()
	{
		if (!Z_Registration_Info_UScriptStruct_ChatTurn.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ChatTurn.InnerSingleton, Z_Construct_UScriptStruct_FChatTurn_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_ChatTurn.InnerSingleton;
	}
	DEFINE_FUNCTION(UOpenAIComponent::execgetChatGPTCompletion)
	{
		P_GET_TARRAY(FChatTurn,Z_Param_messages);
		P_GET_PROPERTY(FStrProperty,Z_Param_apiMethod);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->getChatGPTCompletion(Z_Param_messages,Z_Param_apiMethod);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UOpenAIComponent::execgetGPTCompletion)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_prompt);
		P_GET_TARRAY(FString,Z_Param_stopSequences);
		P_GET_PROPERTY(FStrProperty,Z_Param_apiMethod);
		P_GET_PROPERTY(FIntProperty,Z_Param_maxTokens);
		P_GET_PROPERTY(FFloatProperty,Z_Param_temperature);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->getGPTCompletion(Z_Param_prompt,Z_Param_stopSequences,Z_Param_apiMethod,Z_Param_maxTokens,Z_Param_temperature);
		P_NATIVE_END;
	}
	void UOpenAIComponent::StaticRegisterNativesUOpenAIComponent()
	{
		UClass* Class = UOpenAIComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "getChatGPTCompletion", &UOpenAIComponent::execgetChatGPTCompletion },
			{ "getGPTCompletion", &UOpenAIComponent::execgetGPTCompletion },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics
	{
		struct OpenAIComponent_eventgetChatGPTCompletion_Parms
		{
			TArray<FChatTurn> messages;
			FString apiMethod;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_messages_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_messages;
		static const UECodeGen_Private::FStrPropertyParams NewProp_apiMethod;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_messages_Inner = { "messages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FChatTurn, METADATA_PARAMS(0, nullptr) }; // 1023649587
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_messages = { "messages", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetChatGPTCompletion_Parms, messages), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 1023649587
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_apiMethod = { "apiMethod", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetChatGPTCompletion_Parms, apiMethod), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_messages_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_messages,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::NewProp_apiMethod,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "messages" },
		{ "Category", "GPT" },
		{ "CPP_Default_apiMethod", "gpt-4" },
		{ "DisplayName", "GetChatGPTCompletion" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOpenAIComponent, nullptr, "getChatGPTCompletion", nullptr, nullptr, Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::OpenAIComponent_eventgetChatGPTCompletion_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::OpenAIComponent_eventgetChatGPTCompletion_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics
	{
		struct OpenAIComponent_eventgetGPTCompletion_Parms
		{
			FString prompt;
			TArray<FString> stopSequences;
			FString apiMethod;
			int32 maxTokens;
			float temperature;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_prompt;
		static const UECodeGen_Private::FStrPropertyParams NewProp_stopSequences_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_stopSequences;
		static const UECodeGen_Private::FStrPropertyParams NewProp_apiMethod;
		static const UECodeGen_Private::FIntPropertyParams NewProp_maxTokens;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_temperature;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_prompt = { "prompt", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, prompt), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_stopSequences_Inner = { "stopSequences", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_stopSequences = { "stopSequences", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, stopSequences), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_apiMethod = { "apiMethod", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, apiMethod), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_maxTokens = { "maxTokens", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, maxTokens), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_temperature = { "temperature", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(OpenAIComponent_eventgetGPTCompletion_Parms, temperature), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_prompt,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_stopSequences_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_stopSequences,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_apiMethod,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_maxTokens,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::NewProp_temperature,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::Function_MetaDataParams[] = {
		{ "AutoCreateRefTerm", "stopSequences" },
		{ "Category", "GPT" },
		{ "CPP_Default_apiMethod", "text-davinci-003" },
		{ "CPP_Default_maxTokens", "1000" },
		{ "CPP_Default_temperature", "0.700000" },
		{ "DisplayName", "GetGPTCompletion" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UOpenAIComponent, nullptr, "getGPTCompletion", nullptr, nullptr, Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::PropPointers), sizeof(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::OpenAIComponent_eventgetGPTCompletion_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::Function_MetaDataParams), Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::OpenAIComponent_eventgetGPTCompletion_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UOpenAIComponent);
	UClass* Z_Construct_UClass_UOpenAIComponent_NoRegister()
	{
		return UOpenAIComponent::StaticClass();
	}
	struct Z_Construct_UClass_UOpenAIComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IncomingGPTResponse_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingGPTResponse;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IncomingChatGPTResponse_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_IncomingChatGPTResponse;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UOpenAIComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UOpenAIComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UOpenAIComponent_getChatGPTCompletion, "getChatGPTCompletion" }, // 1617183598
		{ &Z_Construct_UFunction_UOpenAIComponent_getGPTCompletion, "getGPTCompletion" }, // 1664619988
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOpenAIComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "OpenAI" },
		{ "IncludePath", "OpenAIComponent.h" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOpenAIComponent, Key), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key_MetaData), Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse = { "IncomingGPTResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOpenAIComponent, IncomingGPTResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingGPTResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse_MetaData), Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse_MetaData) }; // 1239696054
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingChatGPTResponse_MetaData[] = {
		{ "ModuleRelativePath", "Public/OpenAIComponent.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingChatGPTResponse = { "IncomingChatGPTResponse", nullptr, (EPropertyFlags)0x0010100010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UOpenAIComponent, IncomingChatGPTResponse), Z_Construct_UDelegateFunction_FANTASIA_IncomingChatGPTResponseEvent__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingChatGPTResponse_MetaData), Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingChatGPTResponse_MetaData) }; // 1475273912
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_Key,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingGPTResponse,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UOpenAIComponent_Statics::NewProp_IncomingChatGPTResponse,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UOpenAIComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UOpenAIComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UOpenAIComponent_Statics::ClassParams = {
		&UOpenAIComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers),
		0,
		0x00A000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UOpenAIComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UOpenAIComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UOpenAIComponent()
	{
		if (!Z_Registration_Info_UClass_UOpenAIComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UOpenAIComponent.OuterSingleton, Z_Construct_UClass_UOpenAIComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UOpenAIComponent.OuterSingleton;
	}
	template<> FANTASIA_API UClass* StaticClass<UOpenAIComponent>()
	{
		return UOpenAIComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UOpenAIComponent);
	UOpenAIComponent::~UOpenAIComponent() {}
	struct Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::EnumInfo[] = {
		{ ChatGPTRoleType_StaticEnum, TEXT("ChatGPTRoleType"), &Z_Registration_Info_UEnum_ChatGPTRoleType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3762617820U) },
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ScriptStructInfo[] = {
		{ FChatTurn::StaticStruct, Z_Construct_UScriptStruct_FChatTurn_Statics::NewStructOps, TEXT("ChatTurn"), &Z_Registration_Info_UScriptStruct_ChatTurn, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FChatTurn), 1023649587U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UOpenAIComponent, UOpenAIComponent::StaticClass, TEXT("UOpenAIComponent"), &Z_Registration_Info_UClass_UOpenAIComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UOpenAIComponent), 3707004073U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_823258215(TEXT("/Script/FANTASIA"),
		Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ClassInfo),
		Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::ScriptStructInfo),
		Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Perforce_MetaFamily_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_OpenAIComponent_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
