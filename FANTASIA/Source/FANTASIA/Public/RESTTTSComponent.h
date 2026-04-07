#pragma once

#include "FANTASIA.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "Http.h"
#include <atomic>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"
#include "ACERuntimeModule.h"
#include "ACEAudioCurveSourceComponent.h"
#include "RESTTTSComponent.generated.h"

struct FTTSSynthesisRequest
{
	FString URL;
	TMap<FString, FString> Headers;
	FString Body;           // empty = GET request, non-empty = POST with this body
	FString ID;
	FString OriginalText;
	bool bStreaming = false;
};

static constexpr int32 A2F_STREAMING_BATCH_SIZE = 100;

UCLASS(meta = (BlueprintSpawnableComponent), Config = Game)
class FANTASIA_API URESTTTSComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Build the HTTP request for a synthesis call.
	 *  Base implementation uses URL, Headers, and BodyTemplate properties.
	 *  Subclasses override to build provider-specific requests. */
	virtual FTTSSynthesisRequest BuildSynthesisRequest(const FString& Text, const FString& ID);

	/** Extract additional data (word timing, lipsync, notifies) from the raw HTTP response.
	 *  Called in getResult after WAV detection and resampling.
	 *  Base implementation is a no-op. */
	virtual void ProcessResponse(const TArray<uint8>& RawResponse, FTTSData& OutResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	int32 SampleRate = 16000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	bool bStreaming = false;

private:
	TMap<FString, FTTSData> Buffer;
	FCriticalSection BufferMutex;

	int64 StreamingNum = 0;
	int64 PreviousBytes = 0;

	void IssueHttpRequest(FTTSSynthesisRequest Request);

	FString idSynthesisReady;
	std::atomic<bool> bSynthesisResultReady{false};

	FString idPartialSynthesisReady;
	std::atomic<bool> bPartialResultReady{false};

	void getResult(FTTSData response, FString id);
	void getPartialResult(TArray<uint8> response, FString id);

	/** Parse a WAV header. Returns true if data starts with RIFF/WAVE magic.
	 *  On success, sets OutSampleRate and OutDataOffset (byte offset where PCM data begins). */
	static bool TryParseWavHeader(const TArray<uint8>& Data, int32& OutSampleRate, int32& OutNumChannels, int32& OutBitsPerSample, int32& OutDataOffset);

	/** Resample 16-bit PCM audio from SourceRate to 16000 Hz using linear interpolation.
	 *  Takes raw pointer + byte count to avoid intermediate TArray copies. */
	static TArray<uint8> ResampleTo16kHz(const uint8* PCMData, int32 NumBytes, int32 SourceRate, int32 NumChannels);

	std::atomic<bool> usingStreamingBuffer{false};
	std::atomic<bool> bufferOpen{false};
	std::atomic<bool> isPlaying{false};
	std::atomic<bool> needsFlush{false};
	TQueue<float, EQueueMode::Spsc> sendData;
	FEventRef ConsumerWakeEvent{EEventMode::ManualReset};

public:
	URESTTTSComponent();

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	UACEAudioCurveSourceComponent* A2Fpointer;

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	FAudio2FaceEmotion EmotionParameters;

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	UAudio2FaceParameters* A2FParameters;

	UPROPERTY(BlueprintReadWrite, Category = "TTS")
	FName A2FProvider;

	UPROPERTY(BlueprintAssignable, Category = "TTS")
	FSynthesizedEvent SynthesisReady;

	UPROPERTY(BlueprintAssignable, Category = "TTS")
	FPartialSynthesizedEvent PartialSynthesisReady;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", Config)
	FString URL;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration")
	TMap<FString, FString> Headers;

	/** JSON body template. Use {text} as placeholder for the synthesis text.
	 *  If empty, a GET request is made (with {text} URL-encoded in the URL). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration", Config, meta = (MultiLine = true))
	FString BodyTemplate;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "TTS"), Category = "TTS")
	void TTSSynthesize(FString text, FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "TTS"), Category = "TTS")
	USoundWaveProcedural* TTSGetSound(FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Raw Sound", Keywords = "TTS"), Category = "TTS")
	TArray<uint8> TTSGetRawSound(FString id);
};
