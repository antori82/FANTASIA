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

public:
	// Sets default values for this component's properties
	USWIPrologComponent();


	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString aStringProperty;

	//UPROPERTY(BlueprintAssignable, BlueprintCallable)
	//FSWITestStruct assignableCallableProperty;

	UPROPERTY(BlueprintReadOnly)
	FString readOnlyProperty;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	bool aBoolProperty;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void submitQuery(const bool choice, FString& outString);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Start Prolog", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void startProlog();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Open Prolog file", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void openPrologFile(const FString filename);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};