#pragma once
#pragma warning (disable : 4800)
#pragma warning (disable : 4673)
#pragma warning (disable : 4670)
#pragma warning (disable : 4668)
#pragma warning (disable : 4834)

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "FANTASIA.h"
#include "FANTASIATypes.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#pragma push_macro("verify")
#undef verify
#include <SWI-cpp2.h>
#pragma pop_macro("verify")
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"
//#include "Windows/WindowsHWrapper.h"
#include "SWIPrologComponent.generated.h"

#pragma warning (default : 4800)
#pragma warning (default : 4673)
#pragma warning (default : 4670)
#pragma warning (default : 4668)
#pragma warning (default : 4834)

//using namespace std;



//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSWITestStruct,SWIPrologResponse);

UCLASS(ClassGroup = (SWIProlog), meta = (BlueprintSpawnableComponent), config = Game)
class USWIPrologComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	void startProlog();

	FString translateTerm(UObject*);

	FString translateRule(UObject*);

	FString translateRuleBody(UObject*);

public:
	// Sets default values for this component's properties
	USWIPrologComponent();


	UPROPERTY(BlueprintReadOnly, Category = "Configuration", Config)
	FString resFolderPath;

	/* 
		inRuleOrFact: Rule or fact the query asks for
		inElements: Elements within the term requested 
			(capital letter means prolog variable
			non capital letter means prolog term
			elements in brackets means a prolog list [i,am,an,example])
		outResponse: table of results
	*/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLsubmitQuery(USWIPrologTerm* inRuleOrFact, FSWIPrologResponse& outResponse);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Assert fact", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLassertFact(USWIPrologTerm* fact, bool& bResult);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Assert rule", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLassertRule(USWIPrologRule* rule, bool& bResult);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "retract rule/fact", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLretract(USWIPrologTerm* ruleOrFact, bool& bResult);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "reset Prolog", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void SWIPLresetProlog();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Prolog file", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void openPrologFile(const FString filename);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};