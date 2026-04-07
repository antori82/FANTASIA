#include "SWIPrologHelpers.h"

USWIPrologAtom* USWIPrologHelpers::MakeAtom(const FString& Value)
{
	USWIPrologAtom* Atom = NewObject<USWIPrologAtom>();
	Atom->atomValue = Value;
	return Atom;
}

USWIPrologVariable* USWIPrologHelpers::MakeVariable(const FString& Name)
{
	USWIPrologVariable* Var = NewObject<USWIPrologVariable>();
	Var->varName = Name;
	return Var;
}

USWIPrologCompound* USWIPrologHelpers::MakeCompound(const FString& Name, const TArray<USWIPrologTerm*>& Arguments)
{
	USWIPrologCompound* Compound = NewObject<USWIPrologCompound>();
	Compound->compoundName = Name;
	Compound->arguments = Arguments;
	return Compound;
}

USWIPrologInteger* USWIPrologHelpers::MakeInteger(int32 Value)
{
	USWIPrologInteger* Int = NewObject<USWIPrologInteger>();
	Int->intValue = Value;
	return Int;
}

USWIPrologFloat* USWIPrologHelpers::MakeFloat(float Value)
{
	USWIPrologFloat* Float = NewObject<USWIPrologFloat>();
	Float->floatValue = Value;
	return Float;
}

USWIPrologList* USWIPrologHelpers::MakeList(const TArray<USWIPrologTerm*>& Elements)
{
	USWIPrologList* List = NewObject<USWIPrologList>();
	List->elements = Elements;
	return List;
}
