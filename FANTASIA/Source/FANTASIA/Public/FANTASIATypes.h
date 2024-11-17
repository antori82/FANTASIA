#pragma once
#include "CoreMinimal.h"
#include "FANTASIATypes.generated.h"

UENUM(BlueprintType)
enum class SWIPrologOperation : uint8 {
	AND = 0 UMETA(DisplayName = "AND (,)"),
	OR = 1 UMETA(DisplayName = "OR (;)"),
	CONDITION = 2 UMETA(DisplayName = "IF-THEN-ELSE (->)"),
	EQUAL = 3 UMETA(DisplayName = "EQUAL (=)"),
	UNEQUAL = 4 UMETA(DisplayName = "UNEQUAL (\\=)"),
	IS = 5 UMETA(DisplayName = "IS (is)"),
	PLUS = 6 UMETA(DisplayName = "PLUS (+)"),
	MINUS = 7 UMETA(DisplayName = "MINUS (-)"),
	MULTIPLY = 8 UMETA(DisplayName = "MULTIPLY (*)"),
	DIVIDE = 9 UMETA(DisplayName = "DIVIDE (/)"),
	LESSTHAN = 10 UMETA(DisplayName = "LESS-THAN (<)"),
	MORETHAN = 11 UMETA(DisplayName = "MORE-THAN (>)"),
	LESSOREQUAL = 12 UMETA(DisplayName = "LESS-OR-EQUAL (<=)"),
	MOREOREQUAL = 13 UMETA(DisplayName = "MORE-OR-EQUAL (>=)"),
	TERMNOTEQUAL = 14 UMETA(DisplayName = "TERM-NOT-EQUAL (\\==)"),
	TERMEQUAL = 15 UMETA(DisplayName = "TERM-EQUAL (==)")
};

USTRUCT(BlueprintType)
struct FSWIPrologResponse {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString queryName;

	UPROPERTY(BlueprintReadOnly)
	uint8 arity;

	UPROPERTY(BlueprintReadOnly)
	TArray<USWIPrologSolution*> results;
};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologObject : public UObject {
	GENERATED_BODY()
public:
	USWIPrologObject() {};
};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologRuleBody : public USWIPrologObject {

	GENERATED_BODY()

public:

	USWIPrologRuleBody() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "USWIPrologRuleBody, USWIPrologTerm"))
	USWIPrologObject* firstRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "USWIPrologRuleBody, USWIPrologTerm"))
	USWIPrologObject* secondRule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	SWIPrologOperation prologOperator;
};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologRule : public USWIPrologObject {

	GENERATED_BODY()

public:

	USWIPrologRule() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USWIPrologTerm* head;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "USWIPrologRuleBody, USWIPrologTerm"))
	USWIPrologObject* body;
};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologTerm : public USWIPrologObject {

	GENERATED_BODY()

public:

	USWIPrologTerm() {};

};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologAtom : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologAtom() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString atomValue = "";

};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologVariable : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologVariable() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString varName = "";

};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologInteger : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologInteger() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 intValue = 0;

};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologFloat : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologFloat() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float floatValue = 0;

};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologCompound : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologCompound() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString compoundName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USWIPrologTerm*> arguments;

};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologList : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologList() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USWIPrologTerm*> elements;

};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologHeadToTail : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologHeadToTail() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USWIPrologTerm*> headElements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "USWIPrologTerm, USWIPrologList, USWIPrologHeatToTail"))
	USWIPrologTerm* tail;

};

UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologCut : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologCut() {};

};


UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologSolution : public UObject {

	GENERATED_BODY()

public:

	USWIPrologSolution() {};

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> resultSet;
};

UENUM(BlueprintType)
enum EAzureASREnum : uint8
{
	ASR_CONTINUOUS,
	ASR_ONESHOT
};

UENUM(BlueprintType)
enum class GPTRoleType : uint8 {
	SYSTEM = 0 UMETA(DisplayName = "SYSTEM"),
	ASSISTANT = 1 UMETA(DisplayName = "ASSISTANT"),
	USER = 2 UMETA(DisplayName = "USER"),
	FUNCTION = 3 UMETA(DisplayName = "FUNCTION"),
};

USTRUCT(Blueprintable)
struct FChatTurn
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	GPTRoleType role = GPTRoleType::USER;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString content = TEXT("");
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIncomingGPTResponseEvent, FString, GPTResponse, GPTRoleType, role);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIncomingGPTStreamResponseEvent, FString, GPTResponse, GPTRoleType, role, bool, endStream);

UENUM(BlueprintType)
enum class InfluenceNodeType : uint8 {
	CHANCE = 0 UMETA(DisplayName = "CHANCE"),
	UTILITY = 1 UMETA(DisplayName = "UTILITY"),
	DECISION = 2 UMETA(DisplayName = "DECISION"),
};

UENUM(BlueprintType)
enum class BayesianNodeType : uint8 {
	NORMAL = 0 UMETA(DisplayName = "NORMAL"),
	AMPLITUDE = 1 UMETA(DisplayName = "AMPLITUDE"),
	AND = 2 UMETA(DisplayName = "AND"),
	COUNT = 3 UMETA(DisplayName = "COUNT"),
	EXISTS = 4 UMETA(DisplayName = "EXISTS"),
	FORALL = 5 UMETA(DisplayName = "FORALL"),
	MAX = 6 UMETA(DisplayName = "MAX"),
	MEDIAN = 7 UMETA(DisplayName = "MEDIAN"),
	MIN = 8 UMETA(DisplayName = "MIN")
};

UENUM(BlueprintType)
enum class TTSVoiceType : uint8 {
	NEURAL = 0 UMETA(DisplayName = "Neural"),
	STANDARD = 1 UMETA(DisplayName = "Standard")
};

UENUM(BlueprintType)
enum class Neo4jOperation : uint8 {
	SINGLE_REQUEST = 0 UMETA(DisplayName = "Single request"),
	BEGIN_TRANSACTION = 1  UMETA(DisplayName = "Begin transaction"),
	COMMIT_TRANSACTION = 2     UMETA(DisplayName = "Commit transaction"),
	ROLLBACK_TRANSACTION = 3 UMETA(DisplayName = "Rollback transaction"),
	ADD_TO_TRANSACTION = 4 UMETA(DisplayName = "Add to transaction")
};

USTRUCT(Blueprintable)
struct FTTSTimedStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	int time = 0;

	UPROPERTY(BlueprintReadWrite)
	FString data;
};

USTRUCT()
struct FTTSData
{
	GENERATED_USTRUCT_BODY()

	TArray<uint8> AudioData;
	FString ssml = "";

	TArray<FTTSTimedStruct> lipsync;
	TArray<FTTSTimedStruct> notifies;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSynthesizedEvent, FString, id);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSynthesizedInternalEvent, FTTSData, response, FString, id);
DECLARE_DELEGATE_TwoParams(FTTSResultAvailableDelegate, FTTSData, FString);

USTRUCT(BlueprintType)
struct FNeo4jResponse {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString transactionID;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> headers;

	UPROPERTY(BlueprintReadOnly)
	TArray<UNeo4jResultRow*> rows;
};

USTRUCT(BlueprintType)
struct FNLUResponse {

	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString query;

	UPROPERTY(BlueprintReadWrite)
	TArray<UNLUEntity*> entities;

	UPROPERTY(BlueprintReadWrite)
	TArray<UNLUIntent*> intents;
};

UCLASS(ClassGroup = (Azure), BlueprintType)
class UNLUIntent : public UObject {

	GENERATED_BODY()

	UNLUIntent() {};

public:
	UPROPERTY(BlueprintReadOnly)
	FString intent;

	UPROPERTY(BlueprintReadOnly)
	FString confidence;
};

UCLASS(ClassGroup = (Azure), BlueprintType)
class UNLUEntity : public UObject {

	GENERATED_BODY()

	UNLUEntity() {};

public:
	UPROPERTY(BlueprintReadWrite)
	FString entity;

	UPROPERTY(BlueprintReadWrite)
	FString type;

	UPROPERTY(BlueprintReadWrite)
	uint8 startIndex;

	UPROPERTY(BlueprintReadWrite)
	uint8 endIndex;

	UPROPERTY(BlueprintReadWrite)
	float score;

	UPROPERTY(BlueprintReadWrite)
	FString childName;

	UPROPERTY(BlueprintReadWrite)
	TArray<UNLUEntity*> children;
};

UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultRow : public UObject {

	GENERATED_BODY()

public:
	UNeo4jResultRow() {};

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UNeo4jResultCell*> cells;
};

UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultCell : public UObject {

	GENERATED_BODY()

public:
		UNeo4jResultCell() {};
};

UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultCellNode : public UNeo4jResultCell {

	GENERATED_BODY()

public:
	UNeo4jResultCellNode() {}

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> labels;

	UPROPERTY(BlueprintReadOnly)
	int id;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString,FString> properties;
};

UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultCellRelationship : public UNeo4jResultCell {

	GENERATED_BODY()

public:
	UNeo4jResultCellRelationship() {}

	UPROPERTY(BlueprintReadOnly)
	FString label;

	UPROPERTY(BlueprintReadOnly)
	int id;

	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> properties;
};

UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultCellSimple : public UNeo4jResultCell {

	GENERATED_BODY()

public:
	UNeo4jResultCellSimple() {}

	UPROPERTY(BlueprintReadOnly)
	FString value;
};