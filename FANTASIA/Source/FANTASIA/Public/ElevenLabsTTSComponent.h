#pragma once

#include "FANTASIA.h"
#include "Engine.h"
#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "ElevenLabsTTSThread.h"
#include <atomic>
#include <string>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include "ACERuntimeModule.h"
#include "ACEAudioCurveSourceComponent.h"
#include "ElevenLabsTTSComponent.generated.h"

// [OPT] Removed: using namespace std (pollutes global namespace in headers)

/** Minimum number of float samples to batch before sending to A2F during streaming. */
static constexpr int32 A2F_STREAMING_BATCH_SIZE = 100;

UCLASS(meta = (BlueprintSpawnableComponent), Config = Game)
class UElevenLabsTTSComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	TMap<FString, FTTSData> Buffer;
	// [OPT] Removed: StreamingBuffer, PendingSSML, SyntheticVoicePCMData — all unused dead code

	ElevenLabsTTSThread* handle = nullptr;
	FDelegateHandle TTSResultAvailableHandle;
	FDelegateHandle TTSPartialResultAvailableHandle;

	FString idSynthesisReady = "";
	FString idPartialSynthesisReady = "";

	void getResult(FTTSData response, FString id);
	void getPartialResult(TArray<uint8> response, FString id);

	// [OPT] All cross-thread flags are now atomic to prevent data races.
	//       Plain bool was read/written by HTTP thread, consumer thread, and game thread simultaneously.
	std::atomic<bool> usingStreamingBuffer{false};
	std::atomic<bool> bufferOpen{false};
	std::atomic<bool> isPlaying{false};
	std::atomic<bool> needsFlush{false};     // [OPT] Signals consumer to discard stale data (the buffer bleed fix)

	TQueue<float, EQueueMode::Spsc> sendData;

	// [OPT] Event-based wake replaces CPU-burning spin loop.
	//       The consumer thread blocks on this instead of tight-polling sendData.IsEmpty().
	FEventRef ConsumerWakeEvent{EEventMode::ManualReset};

public:

	UElevenLabsTTSComponent();

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	UACEAudioCurveSourceComponent* A2Fpointer;

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	FAudio2FaceEmotion EmotionParameters;

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	UAudio2FaceParameters* A2FParameters;

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	FName A2FProvider;

	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
	FSynthesizedEvent SynthesisReady;

	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
	FPartialSynthesizedEvent PartialSynthesisReady;

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

	UPROPERTY(EditAnywhere, Category = "Voice Settings", meta = (UIMin = "0.0", UIMax = "1.0"))
	bool use_speaker_boost;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "ElevenLabs TTS"), Category = "TTS")
	void TTSSynthesize(FString text, FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "ElevenLabs TTS"), Category = "TTS")
	USoundWaveProcedural* TTSGetSound(FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Raw Sound", Keywords = "ElevenLabs TTS"), Category = "TTS")
	TArray<uint8> TTSGetRawSound(FString id);
};
