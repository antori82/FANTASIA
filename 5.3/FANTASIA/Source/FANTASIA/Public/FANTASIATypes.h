#pragma once
#include "CoreMinimal.h"
#include "FANTASIATypes.generated.h"

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

	UPROPERTY(BlueprintReadOnly)
	FString topIntent;

	UPROPERTY(BlueprintReadOnly)
	float score;

	UPROPERTY(BlueprintReadWrite)
	TArray<UNLUEntity*> entities;
};

UCLASS(ClassGroup = (Azure), BlueprintType)
class UNLUEntity : public UObject {

	GENERATED_BODY()

	UNLUEntity() {};

public:
	UPROPERTY(BlueprintReadOnly)
	FString entity;

	UPROPERTY(BlueprintReadOnly)
	FString type;

	UPROPERTY(BlueprintReadOnly)
	uint8 startIndex;

	UPROPERTY(BlueprintReadOnly)
	uint8 endIndex;

	UPROPERTY(BlueprintReadOnly)
	float score;

	UPROPERTY(BlueprintReadOnly)
	FString childName;

	UPROPERTY(BlueprintReadOnly)
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