#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Json.h>
#include "FANTASIA.h"
#include "FANTASIATypes.h"

#include "Windows/MinWindows.h"
#include "Windows/WindowsHWrapper.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/AllowWindowsPlatformAtomics.h"
#include <SWI-cpp2.h>
#include <SWI-Prolog.h>
#include <SWI-Stream.h>
#include "Windows/HideWindowsPlatformAtomics.h"
#include "Windows/HideWindowsPlatformTypes.h"

#include "SWIPrologComponent.generated.h"

using namespace std;

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

	const char* GenericMethod(bool bWasSuccessful);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Submit query", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void submitQuery(const bool choice, FString& outString);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Start Prolog", AutoCreateRefTerm = "parameters"), Category = "SWIProlog")
	void startProlog();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};