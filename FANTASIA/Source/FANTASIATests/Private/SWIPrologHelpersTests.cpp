#include "Misc/AutomationTest.h"
#include "SWIPrologHelpers.h"
#include "FANTASIATypes.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPrologMakeAtom, "FANTASIA.SWIPrologHelpers.MakeAtom",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPrologMakeAtom::RunTest(const FString& Parameters)
{
	USWIPrologAtom* Atom = USWIPrologHelpers::MakeAtom(TEXT("hello"));
	TestNotNull(TEXT("Not null"), Atom);
	TestEqual(TEXT("Value"), Atom->atomValue, FString(TEXT("hello")));

	USWIPrologAtom* Empty = USWIPrologHelpers::MakeAtom(TEXT(""));
	TestNotNull(TEXT("Empty not null"), Empty);
	TestEqual(TEXT("Empty value"), Empty->atomValue, FString(TEXT("")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPrologMakeVariable, "FANTASIA.SWIPrologHelpers.MakeVariable",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPrologMakeVariable::RunTest(const FString& Parameters)
{
	USWIPrologVariable* Var = USWIPrologHelpers::MakeVariable(TEXT("X"));
	TestNotNull(TEXT("Not null"), Var);
	TestEqual(TEXT("Name"), Var->varName, FString(TEXT("X")));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPrologMakeInteger, "FANTASIA.SWIPrologHelpers.MakeInteger",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPrologMakeInteger::RunTest(const FString& Parameters)
{
	USWIPrologInteger* Int = USWIPrologHelpers::MakeInteger(42);
	TestNotNull(TEXT("Not null"), Int);
	TestEqual(TEXT("Value"), Int->intValue, 42);

	USWIPrologInteger* Zero = USWIPrologHelpers::MakeInteger(0);
	TestEqual(TEXT("Zero"), Zero->intValue, 0);

	USWIPrologInteger* Neg = USWIPrologHelpers::MakeInteger(-7);
	TestEqual(TEXT("Negative"), Neg->intValue, -7);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPrologMakeFloat, "FANTASIA.SWIPrologHelpers.MakeFloat",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPrologMakeFloat::RunTest(const FString& Parameters)
{
	USWIPrologFloat* F = USWIPrologHelpers::MakeFloat(3.14f);
	TestNotNull(TEXT("Not null"), F);
	TestTrue(TEXT("Value"), FMath::IsNearlyEqual(F->floatValue, 3.14f, 0.001f));
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPrologMakeCompound, "FANTASIA.SWIPrologHelpers.MakeCompound",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPrologMakeCompound::RunTest(const FString& Parameters)
{
	TArray<USWIPrologTerm*> Args;
	Args.Add(USWIPrologHelpers::MakeAtom(TEXT("alice")));
	Args.Add(USWIPrologHelpers::MakeInteger(30));

	USWIPrologCompound* Compound = USWIPrologHelpers::MakeCompound(TEXT("person"), Args);
	TestNotNull(TEXT("Not null"), Compound);
	TestEqual(TEXT("Name"), Compound->compoundName, FString(TEXT("person")));
	TestEqual(TEXT("Arg count"), Compound->arguments.Num(), 2);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPrologMakeList, "FANTASIA.SWIPrologHelpers.MakeList",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPrologMakeList::RunTest(const FString& Parameters)
{
	TArray<USWIPrologTerm*> Elems;
	Elems.Add(USWIPrologHelpers::MakeAtom(TEXT("a")));
	Elems.Add(USWIPrologHelpers::MakeAtom(TEXT("b")));
	Elems.Add(USWIPrologHelpers::MakeAtom(TEXT("c")));

	USWIPrologList* List = USWIPrologHelpers::MakeList(Elems);
	TestNotNull(TEXT("Not null"), List);
	TestEqual(TEXT("Size"), List->elements.Num(), 3);

	// Empty list
	TArray<USWIPrologTerm*> Empty;
	USWIPrologList* EmptyList = USWIPrologHelpers::MakeList(Empty);
	TestNotNull(TEXT("Empty not null"), EmptyList);
	TestEqual(TEXT("Empty size"), EmptyList->elements.Num(), 0);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPrologNestedCompound, "FANTASIA.SWIPrologHelpers.NestedCompound",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FPrologNestedCompound::RunTest(const FString& Parameters)
{
	// Build: likes(alice, [cats, dogs])
	TArray<USWIPrologTerm*> ListElems;
	ListElems.Add(USWIPrologHelpers::MakeAtom(TEXT("cats")));
	ListElems.Add(USWIPrologHelpers::MakeAtom(TEXT("dogs")));

	TArray<USWIPrologTerm*> CompArgs;
	CompArgs.Add(USWIPrologHelpers::MakeAtom(TEXT("alice")));
	CompArgs.Add(USWIPrologHelpers::MakeList(ListElems));

	USWIPrologCompound* Compound = USWIPrologHelpers::MakeCompound(TEXT("likes"), CompArgs);
	TestNotNull(TEXT("Not null"), Compound);
	TestEqual(TEXT("Name"), Compound->compoundName, FString(TEXT("likes")));
	TestEqual(TEXT("Args"), Compound->arguments.Num(), 2);

	// Second argument should be a list
	USWIPrologList* InnerList = Cast<USWIPrologList>(Compound->arguments[1]);
	TestNotNull(TEXT("Inner list"), InnerList);
	TestEqual(TEXT("Inner size"), InnerList->elements.Num(), 2);
	return true;
}
