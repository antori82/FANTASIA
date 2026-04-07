#pragma once

#include "CoreMinimal.h"
#include "RESTTTSComponent.h"
#include "ElevenLabsTTSComponent.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent), Config = Game)
class UElevenLabsTTSComponent : public URESTTTSComponent
{
	GENERATED_BODY()

public:
	UElevenLabsTTSComponent();

protected:
	virtual FTTSSynthesisRequest BuildSynthesisRequest(const FString& Text, const FString& ID) override;

public:
	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString VoiceID;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString ModelID;

	UPROPERTY(EditAnywhere, Category = "Configuration", Config)
	FString Key;

	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float stability;

	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float similarity_boost;

	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	float style;

	UPROPERTY(EditAnywhere, Category = "Voice Settings")
	bool use_speaker_boost;
};
