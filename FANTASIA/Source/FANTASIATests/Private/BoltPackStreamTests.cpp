#include "Misc/AutomationTest.h"
#include "BoltPackStream.h"

// ============================================================================
// FBoltValue Factory Tests
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueMakeNull, "FANTASIA.BoltPackStream.FBoltValue.MakeNull",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueMakeNull::RunTest(const FString& Parameters)
{
	auto V = FBoltValue::MakeNull();
	TestTrue(TEXT("Not null ptr"), V.IsValid());
	TestEqual(TEXT("Type is Null"), V->Type, EBoltValueType::Null);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueMakeBool, "FANTASIA.BoltPackStream.FBoltValue.MakeBool",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueMakeBool::RunTest(const FString& Parameters)
{
	auto T = FBoltValue::MakeBool(true);
	auto F = FBoltValue::MakeBool(false);
	TestEqual(TEXT("Type is Bool"), T->Type, EBoltValueType::Bool);
	TestTrue(TEXT("True value"), T->BoolVal);
	TestFalse(TEXT("False value"), F->BoolVal);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueMakeInt, "FANTASIA.BoltPackStream.FBoltValue.MakeInt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueMakeInt::RunTest(const FString& Parameters)
{
	auto V = FBoltValue::MakeInt(42);
	TestEqual(TEXT("Type is Int"), V->Type, EBoltValueType::Int);
	TestEqual(TEXT("Value is 42"), V->IntVal, (int64)42);

	auto Neg = FBoltValue::MakeInt(-100);
	TestEqual(TEXT("Negative value"), Neg->IntVal, (int64)-100);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueMakeFloat, "FANTASIA.BoltPackStream.FBoltValue.MakeFloat",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueMakeFloat::RunTest(const FString& Parameters)
{
	auto V = FBoltValue::MakeFloat(3.14);
	TestEqual(TEXT("Type is Float"), V->Type, EBoltValueType::Float);
	TestTrue(TEXT("Value is ~3.14"), FMath::IsNearlyEqual(V->FloatVal, 3.14, 0.001));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueMakeString, "FANTASIA.BoltPackStream.FBoltValue.MakeString",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueMakeString::RunTest(const FString& Parameters)
{
	auto V = FBoltValue::MakeString(TEXT("hello"));
	TestEqual(TEXT("Type is String"), V->Type, EBoltValueType::String);
	TestEqual(TEXT("Value"), V->StringVal, FString(TEXT("hello")));

	auto Empty = FBoltValue::MakeString(TEXT(""));
	TestEqual(TEXT("Empty string"), Empty->StringVal, FString(TEXT("")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueMakeList, "FANTASIA.BoltPackStream.FBoltValue.MakeList",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueMakeList::RunTest(const FString& Parameters)
{
	FBoltValueArray Items;
	Items.Add(FBoltValue::MakeInt(1));
	Items.Add(FBoltValue::MakeInt(2));
	auto V = FBoltValue::MakeList(MoveTemp(Items));
	TestEqual(TEXT("Type is List"), V->Type, EBoltValueType::List);
	TestEqual(TEXT("List size"), V->ListVal.Num(), 2);
	TestEqual(TEXT("First item"), V->ListVal[0]->IntVal, (int64)1);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueMakeMap, "FANTASIA.BoltPackStream.FBoltValue.MakeMap",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueMakeMap::RunTest(const FString& Parameters)
{
	FBoltValueMap Map;
	Map.Add(TEXT("key"), FBoltValue::MakeString(TEXT("value")));
	auto V = FBoltValue::MakeMap(MoveTemp(Map));
	TestEqual(TEXT("Type is Map"), V->Type, EBoltValueType::Map);
	TestEqual(TEXT("Map size"), V->MapVal.Num(), 1);
	TestTrue(TEXT("Has key"), V->MapVal.Contains(TEXT("key")));
	TestEqual(TEXT("Value"), V->MapVal[TEXT("key")]->StringVal, FString(TEXT("value")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueMakeStructure, "FANTASIA.BoltPackStream.FBoltValue.MakeStructure",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueMakeStructure::RunTest(const FString& Parameters)
{
	FBoltValueArray Fields;
	Fields.Add(FBoltValue::MakeInt(10));
	auto V = FBoltValue::MakeStructure(0x4E, MoveTemp(Fields));
	TestEqual(TEXT("Type is Structure"), V->Type, EBoltValueType::Structure);
	TestEqual(TEXT("Tag"), V->StructVal.Tag, (uint8)0x4E);
	TestEqual(TEXT("Fields count"), V->StructVal.Fields.Num(), 1);
	return true;
}

// ============================================================================
// AsString() Tests
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueAsStringNull, "FANTASIA.BoltPackStream.AsString.Null",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueAsStringNull::RunTest(const FString& Parameters)
{
	TestEqual(TEXT("Null -> empty"), FBoltValue::MakeNull()->AsString(), FString(TEXT("")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueAsStringBool, "FANTASIA.BoltPackStream.AsString.Bool",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueAsStringBool::RunTest(const FString& Parameters)
{
	TestEqual(TEXT("true"), FBoltValue::MakeBool(true)->AsString(), FString(TEXT("true")));
	TestEqual(TEXT("false"), FBoltValue::MakeBool(false)->AsString(), FString(TEXT("false")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueAsStringInt, "FANTASIA.BoltPackStream.AsString.Int",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueAsStringInt::RunTest(const FString& Parameters)
{
	TestEqual(TEXT("42"), FBoltValue::MakeInt(42)->AsString(), FString(TEXT("42")));
	TestEqual(TEXT("-1"), FBoltValue::MakeInt(-1)->AsString(), FString(TEXT("-1")));
	TestEqual(TEXT("0"), FBoltValue::MakeInt(0)->AsString(), FString(TEXT("0")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueAsStringList, "FANTASIA.BoltPackStream.AsString.List",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueAsStringList::RunTest(const FString& Parameters)
{
	FBoltValueArray Items;
	Items.Add(FBoltValue::MakeInt(1));
	Items.Add(FBoltValue::MakeInt(2));
	auto V = FBoltValue::MakeList(MoveTemp(Items));
	TestEqual(TEXT("List string"), V->AsString(), FString(TEXT("[1, 2]")));

	FBoltValueArray Empty;
	auto E = FBoltValue::MakeList(MoveTemp(Empty));
	TestEqual(TEXT("Empty list"), E->AsString(), FString(TEXT("[]")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueAsStringMap, "FANTASIA.BoltPackStream.AsString.Map",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueAsStringMap::RunTest(const FString& Parameters)
{
	FBoltValueMap Map;
	Map.Add(TEXT("a"), FBoltValue::MakeInt(1));
	auto V = FBoltValue::MakeMap(MoveTemp(Map));
	TestEqual(TEXT("Map string"), V->AsString(), FString(TEXT("{a: 1}")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltValueAsStringStructure, "FANTASIA.BoltPackStream.AsString.Structure",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltValueAsStringStructure::RunTest(const FString& Parameters)
{
	FBoltValueArray Fields;
	auto V = FBoltValue::MakeStructure(0x4E, MoveTemp(Fields));
	TestEqual(TEXT("Structure string"), V->AsString(), FString(TEXT("Structure(0x4E)")));
	return true;
}

// ============================================================================
// Round-Trip Tests (Write -> Read)
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripNull, "FANTASIA.BoltPackStream.RoundTrip.Null",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripNull::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteNull();
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Type"), V->Type, EBoltValueType::Null);
	TestFalse(TEXT("No more data"), Reader.HasMore());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripBool, "FANTASIA.BoltPackStream.RoundTrip.Bool",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripBool::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteBool(true);
	Writer.WriteBool(false);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestTrue(TEXT("True"), Reader.ReadValue()->BoolVal);
	TestFalse(TEXT("False"), Reader.ReadValue()->BoolVal);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripTinyPosInt, "FANTASIA.BoltPackStream.RoundTrip.TinyPositiveInt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripTinyPosInt::RunTest(const FString& Parameters)
{
	// Tiny positive: 0-127, single byte encoding
	FBoltPackStreamWriter Writer;
	Writer.WriteInt(0);
	Writer.WriteInt(42);
	Writer.WriteInt(127);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestEqual(TEXT("0"), Reader.ReadValue()->IntVal, (int64)0);
	TestEqual(TEXT("42"), Reader.ReadValue()->IntVal, (int64)42);
	TestEqual(TEXT("127"), Reader.ReadValue()->IntVal, (int64)127);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripTinyNegInt, "FANTASIA.BoltPackStream.RoundTrip.TinyNegativeInt",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripTinyNegInt::RunTest(const FString& Parameters)
{
	// Tiny negative: -16 to -1, encoded as 0xF0-0xFF
	FBoltPackStreamWriter Writer;
	Writer.WriteInt(-1);
	Writer.WriteInt(-16);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestEqual(TEXT("-1"), Reader.ReadValue()->IntVal, (int64)-1);
	TestEqual(TEXT("-16"), Reader.ReadValue()->IntVal, (int64)-16);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripInt8, "FANTASIA.BoltPackStream.RoundTrip.Int8",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripInt8::RunTest(const FString& Parameters)
{
	// Int8: -128 to -17 (boundary between tiny-neg and int8)
	FBoltPackStreamWriter Writer;
	Writer.WriteInt(-17);
	Writer.WriteInt(-128);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestEqual(TEXT("-17"), Reader.ReadValue()->IntVal, (int64)-17);
	TestEqual(TEXT("-128"), Reader.ReadValue()->IntVal, (int64)-128);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripInt16, "FANTASIA.BoltPackStream.RoundTrip.Int16",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripInt16::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteInt(1000);
	Writer.WriteInt(-1000);
	Writer.WriteInt(32767);
	Writer.WriteInt(-32768);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestEqual(TEXT("1000"), Reader.ReadValue()->IntVal, (int64)1000);
	TestEqual(TEXT("-1000"), Reader.ReadValue()->IntVal, (int64)-1000);
	TestEqual(TEXT("32767"), Reader.ReadValue()->IntVal, (int64)32767);
	TestEqual(TEXT("-32768"), Reader.ReadValue()->IntVal, (int64)-32768);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripInt32, "FANTASIA.BoltPackStream.RoundTrip.Int32",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripInt32::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteInt(100000);
	Writer.WriteInt(-100000);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestEqual(TEXT("100000"), Reader.ReadValue()->IntVal, (int64)100000);
	TestEqual(TEXT("-100000"), Reader.ReadValue()->IntVal, (int64)-100000);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripInt64, "FANTASIA.BoltPackStream.RoundTrip.Int64",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripInt64::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteInt(5000000000LL);
	Writer.WriteInt(-5000000000LL);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestEqual(TEXT("5B"), Reader.ReadValue()->IntVal, (int64)5000000000LL);
	TestEqual(TEXT("-5B"), Reader.ReadValue()->IntVal, (int64)-5000000000LL);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripFloat, "FANTASIA.BoltPackStream.RoundTrip.Float",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripFloat::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteFloat(3.14159);
	Writer.WriteFloat(0.0);
	Writer.WriteFloat(-1.5);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestTrue(TEXT("pi"), FMath::IsNearlyEqual(Reader.ReadValue()->FloatVal, 3.14159, 0.00001));
	TestTrue(TEXT("zero"), FMath::IsNearlyEqual(Reader.ReadValue()->FloatVal, 0.0, 0.00001));
	TestTrue(TEXT("-1.5"), FMath::IsNearlyEqual(Reader.ReadValue()->FloatVal, -1.5, 0.00001));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripEmptyString, "FANTASIA.BoltPackStream.RoundTrip.EmptyString",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripEmptyString::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteString(TEXT(""));
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Type"), V->Type, EBoltValueType::String);
	TestEqual(TEXT("Empty"), V->StringVal, FString(TEXT("")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripShortString, "FANTASIA.BoltPackStream.RoundTrip.ShortString",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripShortString::RunTest(const FString& Parameters)
{
	// Tiny string: <=15 bytes
	FBoltPackStreamWriter Writer;
	Writer.WriteString(TEXT("hello"));
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestEqual(TEXT("Short string"), Reader.ReadValue()->StringVal, FString(TEXT("hello")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripMediumString, "FANTASIA.BoltPackStream.RoundTrip.MediumString",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripMediumString::RunTest(const FString& Parameters)
{
	// String8: 16-255 bytes. Build a 20-char ASCII string.
	FString Str;
	for (int i = 0; i < 20; i++) Str += TEXT("A");
	FBoltPackStreamWriter Writer;
	Writer.WriteString(Str);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	TestEqual(TEXT("Medium string"), Reader.ReadValue()->StringVal, Str);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripBytes, "FANTASIA.BoltPackStream.RoundTrip.Bytes",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripBytes::RunTest(const FString& Parameters)
{
	TArray<uint8> Data = {0x01, 0x02, 0xFF, 0x00};
	FBoltPackStreamWriter Writer;
	Writer.WriteBytes(Data);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Type"), V->Type, EBoltValueType::Bytes);
	TestEqual(TEXT("Size"), V->BytesVal.Num(), 4);
	TestEqual(TEXT("Byte 0"), V->BytesVal[0], (uint8)0x01);
	TestEqual(TEXT("Byte 2"), V->BytesVal[2], (uint8)0xFF);
	TestEqual(TEXT("Byte 3"), V->BytesVal[3], (uint8)0x00);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripEmptyList, "FANTASIA.BoltPackStream.RoundTrip.EmptyList",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripEmptyList::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteListHeader(0);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Type"), V->Type, EBoltValueType::List);
	TestEqual(TEXT("Empty"), V->ListVal.Num(), 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripListOfInts, "FANTASIA.BoltPackStream.RoundTrip.ListOfInts",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripListOfInts::RunTest(const FString& Parameters)
{
	FBoltValueArray Items;
	Items.Add(FBoltValue::MakeInt(10));
	Items.Add(FBoltValue::MakeInt(20));
	Items.Add(FBoltValue::MakeInt(30));
	auto ListVal = FBoltValue::MakeList(MoveTemp(Items));

	FBoltPackStreamWriter Writer;
	Writer.WriteValue(ListVal);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Type"), V->Type, EBoltValueType::List);
	TestEqual(TEXT("Size"), V->ListVal.Num(), 3);
	TestEqual(TEXT("Item 0"), V->ListVal[0]->IntVal, (int64)10);
	TestEqual(TEXT("Item 2"), V->ListVal[2]->IntVal, (int64)30);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripMap, "FANTASIA.BoltPackStream.RoundTrip.Map",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripMap::RunTest(const FString& Parameters)
{
	FBoltValueMap Map;
	Map.Add(TEXT("name"), FBoltValue::MakeString(TEXT("Alice")));
	Map.Add(TEXT("age"), FBoltValue::MakeInt(30));
	auto MapVal = FBoltValue::MakeMap(MoveTemp(Map));

	FBoltPackStreamWriter Writer;
	Writer.WriteValue(MapVal);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Type"), V->Type, EBoltValueType::Map);
	TestEqual(TEXT("Size"), V->MapVal.Num(), 2);
	TestTrue(TEXT("Has name"), V->MapVal.Contains(TEXT("name")));
	TestEqual(TEXT("Name value"), V->MapVal[TEXT("name")]->StringVal, FString(TEXT("Alice")));
	TestEqual(TEXT("Age value"), V->MapVal[TEXT("age")]->IntVal, (int64)30);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripStructure, "FANTASIA.BoltPackStream.RoundTrip.Structure",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripStructure::RunTest(const FString& Parameters)
{
	FBoltValueArray Fields;
	Fields.Add(FBoltValue::MakeInt(1));
	Fields.Add(FBoltValue::MakeString(TEXT("node")));
	auto StructVal = FBoltValue::MakeStructure(0x4E, MoveTemp(Fields));

	FBoltPackStreamWriter Writer;
	Writer.WriteValue(StructVal);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Type"), V->Type, EBoltValueType::Structure);
	TestEqual(TEXT("Tag"), V->StructVal.Tag, (uint8)0x4E);
	TestEqual(TEXT("Fields"), V->StructVal.Fields.Num(), 2);
	TestEqual(TEXT("Field 0"), V->StructVal.Fields[0]->IntVal, (int64)1);
	TestEqual(TEXT("Field 1"), V->StructVal.Fields[1]->StringVal, FString(TEXT("node")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltRoundTripNested, "FANTASIA.BoltPackStream.RoundTrip.NestedStructures",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltRoundTripNested::RunTest(const FString& Parameters)
{
	// List containing a map containing a list
	FBoltValueMap InnerMap;
	FBoltValueArray InnerList;
	InnerList.Add(FBoltValue::MakeInt(1));
	InnerList.Add(FBoltValue::MakeInt(2));
	InnerMap.Add(TEXT("ids"), FBoltValue::MakeList(MoveTemp(InnerList)));

	FBoltValueArray OuterList;
	OuterList.Add(FBoltValue::MakeMap(MoveTemp(InnerMap)));
	OuterList.Add(FBoltValue::MakeString(TEXT("end")));
	auto Val = FBoltValue::MakeList(MoveTemp(OuterList));

	FBoltPackStreamWriter Writer;
	Writer.WriteValue(Val);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Outer type"), V->Type, EBoltValueType::List);
	TestEqual(TEXT("Outer size"), V->ListVal.Num(), 2);
	auto& MapItem = V->ListVal[0];
	TestEqual(TEXT("Map type"), MapItem->Type, EBoltValueType::Map);
	auto& IdsList = MapItem->MapVal[TEXT("ids")];
	TestEqual(TEXT("Inner list type"), IdsList->Type, EBoltValueType::List);
	TestEqual(TEXT("Inner list size"), IdsList->ListVal.Num(), 2);
	TestEqual(TEXT("Inner[0]"), IdsList->ListVal[0]->IntVal, (int64)1);
	TestEqual(TEXT("Tail string"), V->ListVal[1]->StringVal, FString(TEXT("end")));
	return true;
}

// ============================================================================
// Reader State Tests
// ============================================================================

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltReaderHasMoreEmpty, "FANTASIA.BoltPackStream.Reader.HasMoreEmpty",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltReaderHasMoreEmpty::RunTest(const FString& Parameters)
{
	TArray<uint8> Empty;
	FBoltPackStreamReader Reader(Empty);
	TestFalse(TEXT("Empty buffer has no more"), Reader.HasMore());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltReaderPeekDoesNotAdvance, "FANTASIA.BoltPackStream.Reader.PeekNoAdvance",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltReaderPeekDoesNotAdvance::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteInt(42);
	FBoltPackStreamReader Reader(Writer.GetBuffer());
	uint8 First = Reader.PeekMarker();
	uint8 Second = Reader.PeekMarker();
	TestEqual(TEXT("Peek is idempotent"), First, Second);
	auto V = Reader.ReadValue();
	TestEqual(TEXT("Value still readable"), V->IntVal, (int64)42);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltReaderMultipleValues, "FANTASIA.BoltPackStream.Reader.MultipleValues",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltReaderMultipleValues::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteNull();
	Writer.WriteBool(true);
	Writer.WriteInt(99);
	Writer.WriteString(TEXT("end"));
	FBoltPackStreamReader Reader(Writer.GetBuffer());

	TestEqual(TEXT("Null"), Reader.ReadValue()->Type, EBoltValueType::Null);
	TestTrue(TEXT("Bool"), Reader.ReadValue()->BoolVal);
	TestEqual(TEXT("Int"), Reader.ReadValue()->IntVal, (int64)99);
	TestEqual(TEXT("String"), Reader.ReadValue()->StringVal, FString(TEXT("end")));
	TestFalse(TEXT("Exhausted"), Reader.HasMore());
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBoltWriterReset, "FANTASIA.BoltPackStream.Writer.Reset",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FBoltWriterReset::RunTest(const FString& Parameters)
{
	FBoltPackStreamWriter Writer;
	Writer.WriteInt(1);
	TestTrue(TEXT("Non-empty after write"), Writer.GetBuffer().Num() > 0);
	Writer.Reset();
	TestEqual(TEXT("Empty after reset"), Writer.GetBuffer().Num(), 0);
	return true;
}
