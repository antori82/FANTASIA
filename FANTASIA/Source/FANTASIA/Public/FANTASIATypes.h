/**
 * @file FANTASIATypes.h
 * @brief Core type definitions shared across the FANTASIA plugin.
 *
 * Declares enums, structs, delegates, and lightweight UObject-based data classes
 * used by SWI-Prolog, Bayesian networks, LLM components, TTS/ASR services,
 * NLU pipelines, and Neo4j graph-database integration.
 */

#pragma once
#include "CoreMinimal.h"
#include "FANTASIATypes.generated.h"

// ── SWI-Prolog Types ────────────────────────────────────────────────────────

/**
 * Logical and arithmetic operators available when constructing Prolog queries
 * from Blueprints.
 *
 * Each value maps to the corresponding SWI-Prolog operator shown in the
 * DisplayName metadata.
 */
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

/**
 * Result of a SWI-Prolog query executed through USWIPrologComponent.
 *
 * Each response bundles the original query functor name, its arity, and an
 * array of solution bindings returned by Prolog.
 */
USTRUCT(BlueprintType)
struct FSWIPrologResponse {

	GENERATED_BODY()

	/** Functor name of the query that produced this response. */
	UPROPERTY(BlueprintReadOnly)
	FString queryName;

	/** Arity (number of arguments) of the query. */
	UPROPERTY(BlueprintReadOnly)
	uint8 arity;

	/** Ordered list of solution bindings returned by the Prolog engine. */
	UPROPERTY(BlueprintReadOnly)
	TArray<USWIPrologSolution*> results;
};

/**
 * Abstract base class for all SWI-Prolog AST nodes used in Blueprint-constructed queries.
 *
 * @see USWIPrologTerm, USWIPrologRuleBody, USWIPrologRule
 */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologObject : public UObject {
	GENERATED_BODY()
public:
	USWIPrologObject() {};
};

/**
 * Binary expression node that combines two Prolog sub-expressions with an operator.
 *
 * Represents constructs such as @c (A, B), @c (A ; B), or arithmetic
 * comparisons built visually in Blueprints.
 */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologRuleBody : public USWIPrologObject {

	GENERATED_BODY()

public:

	USWIPrologRuleBody() {};

	/** Left-hand operand (may be another rule body or a term). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "USWIPrologRuleBody, USWIPrologTerm"))
	USWIPrologObject* firstRule;

	/** Right-hand operand (may be another rule body or a term). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "USWIPrologRuleBody, USWIPrologTerm"))
	USWIPrologObject* secondRule;

	/** Operator that joins the two operands. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	SWIPrologOperation prologOperator;
};

/**
 * A Prolog rule of the form @c Head :- Body.
 *
 * @see USWIPrologRuleBody
 */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologRule : public USWIPrologObject {

	GENERATED_BODY()

public:

	USWIPrologRule() {};

	/** Head (conclusion) of the rule — must be a compound term or atom. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USWIPrologTerm* head;

	/** Body (conditions) of the rule — a term or a compound rule body. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "USWIPrologRuleBody, USWIPrologTerm"))
	USWIPrologObject* body;
};

/**
 * Base class for all Prolog term nodes (atoms, variables, compounds, lists, etc.).
 *
 * Subclasses represent the different SWI-Prolog term types that can appear in
 * queries and facts constructed from Blueprints.
 */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologTerm : public USWIPrologObject {

	GENERATED_BODY()

public:

	USWIPrologTerm() {};

};

/** A Prolog atom — an unquoted symbolic constant (e.g. @c hello, @c world). */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologAtom : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologAtom() {};

	/** Textual value of the atom. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString atomValue = "";

};

/** A Prolog variable — an unbound placeholder that the engine will attempt to unify. */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologVariable : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologVariable() {};

	/** Name of the variable (e.g. @c "X", @c "Result"). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString varName = "";

};

/** A Prolog integer literal. */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologInteger : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologInteger() {};

	/** Integer value of this term. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 intValue = 0;

};

/** A Prolog floating-point literal. */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologFloat : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologFloat() {};

	/** Floating-point value of this term. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float floatValue = 0;

};

/**
 * A Prolog compound term — a functor with zero or more arguments
 * (e.g. @c parent(tom, bob)).
 */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologCompound : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologCompound() {};

	/** Functor name of the compound (e.g. @c "parent"). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString compoundName;

	/** Ordered list of argument terms. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USWIPrologTerm*> arguments;

};

/** A Prolog list — an ordered sequence of terms (e.g. @c [a, b, c]). */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologList : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologList() {};

	/** Elements of the list, in order. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USWIPrologTerm*> elements;

};

/**
 * A Prolog head-tail list decomposition (e.g. @c [H1, H2 | T]).
 *
 * Allows pattern-matching on the first N elements while binding the
 * remainder of the list to @c tail.
 */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologHeadToTail : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologHeadToTail() {};

	/** Leading elements extracted from the front of the list. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USWIPrologTerm*> headElements;

	/** Remainder of the list after the head elements. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowedClasses = "USWIPrologTerm, USWIPrologList, USWIPrologHeatToTail"))
	USWIPrologTerm* tail;

};

/** The Prolog cut operator (@c !), which commits to the current choice point. */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologCut : public USWIPrologTerm {

	GENERATED_BODY()

public:

	USWIPrologCut() {};

};


/**
 * A single solution (set of variable bindings) returned by a Prolog query.
 *
 * Each element in @c resultSet corresponds, in order, to one of the query's
 * variables.
 */
UCLASS(ClassGroup = (SWIProlog), BlueprintType)
class USWIPrologSolution : public UObject {

	GENERATED_BODY()

public:

	USWIPrologSolution() {};

	/** String representations of the bound values, one per query variable. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> resultSet;

	/** Whether the Prolog engine verified (proved) this solution. */
	UPROPERTY(BlueprintReadOnly)
	bool verified;
};

// ── Azure ASR Types ─────────────────────────────────────────────────────────

/**
 * Recognition mode for the Azure Automatic Speech Recognition service.
 *
 * @deprecated UAzureASRComponent is deprecated; prefer UWhisperCaptureComponent.
 */
UENUM(BlueprintType)
enum EAzureASREnum : uint8
{
	/** Continuous recognition — keeps listening until explicitly stopped. */
	ASR_CONTINUOUS,
	/** One-shot recognition — returns a single utterance and stops. */
	ASR_ONESHOT
};

// ── LLM / Chat Types ────────────────────────────────────────────────────────

/** Role of a participant in an LLM chat conversation. */
UENUM(BlueprintType)
enum class GPTRoleType : uint8 {
	SYSTEM = 0 UMETA(DisplayName = "SYSTEM"),       ///< System prompt / instructions.
	ASSISTANT = 1 UMETA(DisplayName = "ASSISTANT"),  ///< Model-generated response.
	USER = 2 UMETA(DisplayName = "USER"),            ///< Human user message.
	FUNCTION = 3 UMETA(DisplayName = "FUNCTION"),    ///< Tool / function call result.
};

/** A single turn (message) in an LLM chat conversation. */
USTRUCT(Blueprintable)
struct FChatTurn
{
	GENERATED_USTRUCT_BODY()

	/** Role of the speaker for this turn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	GPTRoleType role = GPTRoleType::USER;

	/** Textual content of the message. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString content = TEXT("");
};

/** Fired when a complete (non-streaming) LLM response is received. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FIncomingGPTResponseEvent, FString, GPTResponse, GPTRoleType, role);

/** Fired for each chunk of a streaming LLM response; @p endStream is true on the final chunk. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIncomingGPTStreamResponseEvent, FString, GPTResponse, GPTRoleType, role, bool, endStream);

// ── Probabilistic Graphical Model Types ─────────────────────────────────────

/** Node type within an influence diagram (aGrUM). */
UENUM(BlueprintType)
enum class InfluenceNodeType : uint8 {
	CHANCE = 0 UMETA(DisplayName = "CHANCE"),       ///< Random variable node.
	UTILITY = 1 UMETA(DisplayName = "UTILITY"),     ///< Utility / value node.
	DECISION = 2 UMETA(DisplayName = "DECISION"),   ///< Decision variable node.
};

/** Aggregation type for a node in a Bayesian network (aGrUM). */
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

/** Exact inference algorithms available for Bayesian networks. */
UENUM(BlueprintType)
enum class InferenceAlgs : uint8
{
	Lazy_Propagation UMETA(DisplayName = "Lazy Propagation"),
	ShaferShenoy UMETA(DisplayName = "Shafer Shenoy Inference"),
	VariableElimination UMETA(DisplayName = "Variable Elimination")
};

/** Inference algorithms available for influence diagrams (LIMIDs). */
UENUM(BlueprintType)
enum class InferenceIDAlgs : uint8
{
	ShaferShenoyLIMID UMETA(DisplayName = "Shafer Shenoy LIMID Inference"),
};

// ── TTS Types ───────────────────────────────────────────────────────────────

/** Voice engine type for text-to-speech synthesis. */
UENUM(BlueprintType)
enum class TTSVoiceType : uint8 {
	NEURAL = 0 UMETA(DisplayName = "Neural"),       ///< Neural (higher quality) voice.
	STANDARD = 1 UMETA(DisplayName = "Standard")    ///< Standard (lower latency) voice.
};

// ── Neo4j Types ─────────────────────────────────────────────────────────────

/** Transaction mode for a Neo4j Cypher query submitted through UNeo4jComponent. */
UENUM(BlueprintType)
enum class Neo4jOperation : uint8 {
	SINGLE_REQUEST = 0 UMETA(DisplayName = "Single request"),               ///< Auto-commit single query.
	BEGIN_TRANSACTION = 1  UMETA(DisplayName = "Begin transaction"),         ///< Open a new explicit transaction.
	COMMIT_TRANSACTION = 2     UMETA(DisplayName = "Commit transaction"),    ///< Commit the current transaction.
	ROLLBACK_TRANSACTION = 3 UMETA(DisplayName = "Rollback transaction"),    ///< Roll back the current transaction.
	ADD_TO_TRANSACTION = 4 UMETA(DisplayName = "Add to transaction")         ///< Append a query to the open transaction.
};

/** A time-stamped data point used for lip-sync visemes or animation notifies. */
USTRUCT(Blueprintable)
struct FTTSTimedStruct
{
	GENERATED_USTRUCT_BODY()

	/** Timestamp in milliseconds relative to the start of the audio clip. */
	UPROPERTY(BlueprintReadWrite)
	int time = 0;

	/** Payload string (viseme ID, notify name, etc.). */
	UPROPERTY(BlueprintReadWrite)
	FString data;
};

/**
 * Complete TTS synthesis result containing raw audio and metadata.
 *
 * Produced internally by TTS threads and forwarded to the owning component.
 */
USTRUCT()
struct FTTSData
{
	GENERATED_USTRUCT_BODY()

	/** Raw PCM / encoded audio bytes. */
	TArray<uint8> AudioData;

	/** Original SSML markup that was synthesized. */
	FString ssml = "";

	/** Lip-sync viseme timeline. */
	TArray<FTTSTimedStruct> lipsync;

	/** Animation notify timeline. */
	TArray<FTTSTimedStruct> notifies;
};

/** Fired when a full TTS synthesis is complete; @p id identifies the request. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSynthesizedEvent, FString, id);

/** Internal delegate carrying the full FTTSData payload after synthesis. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSynthesizedInternalEvent, FTTSData, response, FString, id);

/** Fired when a partial (streaming) TTS chunk is ready. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPartialSynthesizedEvent, FString, id);

/** Internal delegate carrying partial FTTSData for streaming synthesis. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPartialSynthesizedInternalEvent, FTTSData, response, FString, id);

/** Non-dynamic delegate used by TTS threads to deliver a complete result to the game thread. */
DECLARE_DELEGATE_TwoParams(FTTSResultAvailableDelegate, FTTSData, FString);

/** Non-dynamic delegate used by TTS threads to deliver a partial audio chunk. */
DECLARE_DELEGATE_TwoParams(FTTSPartialResultAvailableDelegate, TArray<uint8>, FString);

/**
 * Response from a Neo4j Cypher query executed through UNeo4jComponent.
 *
 * Contains column headers and an ordered list of result rows, plus the
 * transaction ID when running inside an explicit transaction.
 */
USTRUCT(BlueprintType)
struct FNeo4jResponse {

	GENERATED_BODY()

	/** Transaction identifier (empty for auto-commit queries). */
	UPROPERTY(BlueprintReadOnly)
	FString transactionID;

	/** Column names returned by the query. */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> headers;

	/** Ordered result rows, each containing one cell per header. */
	UPROPERTY(BlueprintReadOnly)
	TArray<UNeo4jResultRow*> rows;
};

// ── NLU Types ───────────────────────────────────────────────────────────────

/**
 * Response from a Natural Language Understanding service (e.g. Azure CLU).
 *
 * Bundles the original query text together with extracted intents and entities.
 */
USTRUCT(BlueprintType)
struct FNLUResponse {

	GENERATED_BODY()

	/** The original user utterance that was analyzed. */
	UPROPERTY(BlueprintReadOnly)
	FString query;

	/** Entities extracted from the utterance. */
	UPROPERTY(BlueprintReadWrite)
	TArray<UNLUEntity*> entities;

	/** Intents detected in the utterance, ordered by confidence. */
	UPROPERTY(BlueprintReadWrite)
	TArray<UNLUIntent*> intents;
};

/** A single intent detected by the NLU service. */
UCLASS(ClassGroup = (Azure), BlueprintType)
class UNLUIntent : public UObject {

	GENERATED_BODY()

	UNLUIntent() {};

public:
	/** Canonical name of the detected intent. */
	UPROPERTY(BlueprintReadOnly)
	FString intent;

	/** Confidence score as a string (e.g. "0.95"). */
	UPROPERTY(BlueprintReadOnly)
	FString confidence;
};

/**
 * A single entity extracted from an utterance by the NLU service.
 *
 * Entities may form a hierarchy via the @c children array (e.g. a
 * "datetime" entity containing "date" and "time" sub-entities).
 */
UCLASS(ClassGroup = (Azure), BlueprintType)
class UNLUEntity : public UObject {

	GENERATED_BODY()

	UNLUEntity() {};

public:
	/** Recognised text span of the entity. */
	UPROPERTY(BlueprintReadWrite)
	FString entity;

	/** Entity type / category name. */
	UPROPERTY(BlueprintReadWrite)
	FString type;

	/** Character offset where the entity begins in the original utterance. */
	UPROPERTY(BlueprintReadWrite)
	uint8 startIndex;

	/** Character offset where the entity ends in the original utterance. */
	UPROPERTY(BlueprintReadWrite)
	uint8 endIndex;

	/** Confidence score in [0, 1]. */
	UPROPERTY(BlueprintReadWrite)
	float score;

	/** Name used to identify the child entity list (Azure CLU list-entity key). */
	UPROPERTY(BlueprintReadWrite)
	FString childName;

	/** Nested sub-entities, if any. */
	UPROPERTY(BlueprintReadWrite)
	TArray<UNLUEntity*> children;
};

// ── Neo4j Result Classes ────────────────────────────────────────────────────

/** A single row in a Neo4j query result, keyed by column name. */
UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultRow : public UObject {

	GENERATED_BODY()

public:
	UNeo4jResultRow() {};

	/** Map from column header to the corresponding result cell. */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, UNeo4jResultCell*> cells;
};

/**
 * Abstract base for a single value cell in a Neo4j result row.
 *
 * Concrete subclasses represent nodes, relationships, and scalar values.
 *
 * @see UNeo4jResultCellNode, UNeo4jResultCellRelationship, UNeo4jResultCellSimple
 */
UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultCell : public UObject {

	GENERATED_BODY()

public:
		UNeo4jResultCell() {};
};

/** A Neo4j node returned in a query result. */
UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultCellNode : public UNeo4jResultCell {

	GENERATED_BODY()

public:
	UNeo4jResultCellNode() {}

	/** Label(s) assigned to the node (e.g. "Person", "Actor"). */
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> labels;

	/** Internal Neo4j node identity. */
	UPROPERTY(BlueprintReadOnly)
	int id;

	/** Key-value property map of the node (all values serialized to strings). */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString,FString> properties;
};

/** A Neo4j relationship returned in a query result. */
UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultCellRelationship : public UNeo4jResultCell {

	GENERATED_BODY()

public:
	UNeo4jResultCellRelationship() {}

	/** Relationship type label (e.g. "KNOWS"). */
	UPROPERTY(BlueprintReadOnly)
	FString label;

	/** Internal Neo4j relationship identity. */
	UPROPERTY(BlueprintReadOnly)
	int id;

	/** Key-value property map of the relationship. */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> properties;
};

/** A scalar (string, number, boolean) value cell in a Neo4j result. */
UCLASS(ClassGroup = (Neo4j), BlueprintType)
class UNeo4jResultCellSimple : public UNeo4jResultCell {

	GENERATED_BODY()

public:
	UNeo4jResultCellSimple() {}

	/** String representation of the scalar value. */
	UPROPERTY(BlueprintReadOnly)
	FString value;
};

// ── Audio2Face Emotion Mirror Structs ───────────────────────────────────────
// These mirror the shape of NVIDIA ACE's FAudio2FaceEmotion /
// FAudio2FaceEmotionOverride (from ACECore in NV_ACE_Reference) so that
// the FANTASIA plugin can expose emotion-parameter UPROPERTYs on
// URESTTTSComponent without a hard build-time dependency on ACE.
// RESTTTSComponent.cpp copies field-by-field into the real ACE structs
// inside #if FANTASIA_WITH_ACE before passing to AnimateFromAudioSamples.
// Field names, default values, and metadata (clamps etc.) match ACE's
// definitions so Blueprint experience is identical.

/**
 * @brief Per-emotion override toggles and target values for Audio2Face.
 *
 * Mirrors the shape of NVIDIA ACE's @c FAudio2FaceEmotionOverride. Each
 * emotion has a `bOverride*` boolean that gates a clamped-[0,1] strength
 * value; only emotions whose override flag is set are passed through to
 * ACE. Embedded inside FFantasiaAudio2FaceEmotion via @c EmotionOverrides.
 */
USTRUCT(BlueprintType, meta = (DisplayName = "FANTASIA Audio2Face Emotion Overrides"))
struct FFantasiaAudio2FaceEmotionOverride
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideAmazement = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideAmazement"))
	float Amazement = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideAnger = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideAnger"))
	float Anger = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideCheekiness = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideCheekiness"))
	float Cheekiness = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideDisgust = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideDisgust"))
	float Disgust = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideFear = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideFear"))
	float Fear = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideGrief = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideGrief"))
	float Grief = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideJoy = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideJoy"))
	float Joy = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideOutOfBreath = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideOutOfBreath"))
	float OutOfBreath = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverridePain = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverridePain"))
	float Pain = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool bOverrideSadness = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bOverrideSadness"))
	float Sadness = 0.0f;
};

/**
 * @brief Audio2Face emotion parameter set passed to ACE during streaming.
 *
 * Mirrors the shape of NVIDIA ACE's @c FAudio2FaceEmotion so that
 * URESTTTSComponent can expose emotion controls in Blueprints without a
 * hard build-time dependency on ACE. When the plugin is built with
 * @c FANTASIA_WITH_ACE=1, RESTTTSComponent.cpp copies these fields
 * field-by-field into the real ACE struct before calling
 * @c AnimateFromAudioSamples; without ACE the values are simply ignored.
 *
 * Field names, defaults, and clamps match ACE so the Blueprint editing
 * experience is identical.
 *
 * @see FFantasiaAudio2FaceEmotionOverride
 */
USTRUCT(BlueprintType, meta = (DisplayName = "FANTASIA Audio2Face Emotion Parameters"))
struct FFantasiaAudio2FaceEmotion
{
	GENERATED_BODY()

	/** Overall strength of generated emotion (ACE default 0.6). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float OverallEmotionStrength = 0.6f;

	/** Spread between detected emotion values (ACE default 1.0). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detected Emotion", meta = (ClampMin = "0.3", ClampMax = "3.0"))
	float DetectedEmotionContrast = 1.0f;

	/** Max detected emotions to engage simultaneously (ACE default 3). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detected Emotion", meta = (ClampMin = "1", ClampMax = "6"))
	int32 MaxDetectedEmotions = 3;

	/** Temporal smoothing of detected emotion (ACE default 0.7). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detected Emotion", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DetectedEmotionSmoothing = 0.7f;

	/** Enable application emotion overrides (ACE default true). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Application Overrides", meta = (InlineEditConditionToggle))
	bool bEnableEmotionOverride = true;

	/** Strength of application overrides vs detected emotion (ACE default 0.5). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Application Overrides", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bEnableEmotionOverride"))
	float EmotionOverrideStrength = 0.5f;

	/** Per-emotion override toggles and values. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Application Overrides", meta = (EditCondition = "bEnableEmotionOverride && (EmotionOverrideStrength > 0.0)"))
	FFantasiaAudio2FaceEmotionOverride EmotionOverrides;
};