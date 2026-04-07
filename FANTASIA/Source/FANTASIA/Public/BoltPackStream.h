#pragma once

#include "CoreMinimal.h"

enum class EBoltValueType : uint8
{
	Null, Bool, Int, Float, String, Bytes, List, Map, Structure
};

struct FBoltValue;
using FBoltValuePtr = TSharedPtr<FBoltValue>;
using FBoltValueArray = TArray<FBoltValuePtr>;
using FBoltValueMap = TMap<FString, FBoltValuePtr>;

struct FBoltStructure
{
	uint8 Tag = 0;
	FBoltValueArray Fields;
};

struct FBoltValue
{
	EBoltValueType Type = EBoltValueType::Null;
	bool BoolVal = false;
	int64 IntVal = 0;
	double FloatVal = 0.0;
	FString StringVal;
	TArray<uint8> BytesVal;
	FBoltValueArray ListVal;
	FBoltValueMap MapVal;
	FBoltStructure StructVal;

	static FBoltValuePtr MakeNull() { auto V = MakeShared<FBoltValue>(); return V; }
	static FBoltValuePtr MakeBool(bool B) { auto V = MakeShared<FBoltValue>(); V->Type = EBoltValueType::Bool; V->BoolVal = B; return V; }
	static FBoltValuePtr MakeInt(int64 I) { auto V = MakeShared<FBoltValue>(); V->Type = EBoltValueType::Int; V->IntVal = I; return V; }
	static FBoltValuePtr MakeFloat(double F) { auto V = MakeShared<FBoltValue>(); V->Type = EBoltValueType::Float; V->FloatVal = F; return V; }
	static FBoltValuePtr MakeString(const FString& S) { auto V = MakeShared<FBoltValue>(); V->Type = EBoltValueType::String; V->StringVal = S; return V; }

	static FBoltValuePtr MakeList(FBoltValueArray&& L)
	{
		auto V = MakeShared<FBoltValue>(); V->Type = EBoltValueType::List; V->ListVal = MoveTemp(L); return V;
	}

	static FBoltValuePtr MakeMap(FBoltValueMap&& M)
	{
		auto V = MakeShared<FBoltValue>(); V->Type = EBoltValueType::Map; V->MapVal = MoveTemp(M); return V;
	}

	static FBoltValuePtr MakeStructure(uint8 Tag, FBoltValueArray&& Fields)
	{
		auto V = MakeShared<FBoltValue>(); V->Type = EBoltValueType::Structure; V->StructVal.Tag = Tag; V->StructVal.Fields = MoveTemp(Fields); return V;
	}

	FString AsString() const;
};

class FBoltPackStreamWriter
{
public:
	void WriteNull();
	void WriteBool(bool Value);
	void WriteInt(int64 Value);
	void WriteFloat(double Value);
	void WriteString(const FString& Value);
	void WriteBytes(const TArray<uint8>& Value);
	void WriteListHeader(int32 Size);
	void WriteMapHeader(int32 Size);
	void WriteStructureHeader(uint8 Tag, int32 NumFields);
	void WriteValue(const FBoltValuePtr& Value);

	const TArray<uint8>& GetBuffer() const { return Buffer; }
	void Reset() { Buffer.Empty(); }

private:
	void WriteByte(uint8 B);
	void WriteUInt16BE(uint16 Value);
	void WriteInt16BE(int16 Value);
	void WriteInt32BE(int32 Value);
	void WriteInt64BE(int64 Value);
	void WriteFloat64BE(double Value);
	TArray<uint8> Buffer;
};

class FBoltPackStreamReader
{
public:
	FBoltPackStreamReader(const TArray<uint8>& InData);
	FBoltValuePtr ReadValue();
	bool HasMore() const;
	uint8 PeekMarker() const;

private:
	uint8 ReadByte();
	uint16 ReadUInt16BE();
	int16 ReadInt16BE();
	int32 ReadInt32BE();
	int64 ReadInt64BE();
	double ReadFloat64BE();
	FString ReadStringOfLength(int32 Length);
	const TArray<uint8>& Data;
	int32 Cursor = 0;
};
