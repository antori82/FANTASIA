// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#include "WhisperCaptureComponent.h"
#include "WhisperSubsystem.h"
#include "Engine/GameInstance.h"
#include "AudioCaptureCore.h"

// ─────────────────────────────────────────────────────────────────────────────
// Constants
// ─────────────────────────────────────────────────────────────────────────────

static constexpr int32 WHISPER_SAMPLE_RATE = 16000;

// ─────────────────────────────────────────────────────────────────────────────
// Construction / Destruction
// ─────────────────────────────────────────────────────────────────────────────

UWhisperCaptureComponent::UWhisperCaptureComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bTranscriptionInFlight = false;
}

UWhisperCaptureComponent::~UWhisperCaptureComponent()
{
	CloseCaptureDevice();
}

// ─────────────────────────────────────────────────────────────────────────────
// Lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperCaptureComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWhisperCaptureComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Force-stop everything — critical for PIE shutdown to not lock the editor
	bIsCalibrating = false;
	bCalibrationOwnsMic = false;
	bSpeechDetected = false;

	if (bIsCapturing)
	{
		// Stop the stream immediately without transcribing
		if (AudioCapture && AudioCapture->IsStreamOpen() && AudioCapture->IsCapturing())
		{
			AudioCapture->StopStream();
		}
		bIsCapturing = false;
		SetComponentTickEnabled(false);
		bTranscriptionInFlight = false;
	}

	// Unbind from subsystem delegates before it deinitializes
	UGameInstance* GI = GetOwner() ? GetOwner()->GetGameInstance() : nullptr;
	if (GI)
	{
		if (UWhisperSubsystem* Whisper = GI->GetSubsystem<UWhisperSubsystem>())
		{
			Whisper->OnTranscriptionComplete.RemoveDynamic(
				this, &UWhisperCaptureComponent::HandleTranscriptionResult);
			Whisper->OnSegmentReady.RemoveDynamic(
				this, &UWhisperCaptureComponent::HandleSegmentReady);
		}
	}

	CloseCaptureDevice();

	{
		FScopeLock Lock(&BufferCritSection);
		AudioBuffer.Reset();
	}

	Super::EndPlay(EndPlayReason);
}

void UWhisperCaptureComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsCapturing)
	{
		return;
	}

	// ── Noise calibration tick ───────────────────────────────────────────
	if (bIsCalibrating)
	{
		CalibrationTimer += DeltaTime;

		if (CalibrationTimer >= CalibrationDuration)
		{
			// Snapshot the buffer that accumulated during calibration
			float PeakAmplitude = 0.f;
			{
				FScopeLock Lock(&BufferCritSection);
				for (int32 i = 0; i < AudioBuffer.Num(); ++i)
				{
					float Abs = FMath::Abs(AudioBuffer[i]);
					if (Abs > PeakAmplitude) PeakAmplitude = Abs;
				}
			}

			LastMeasuredNoiseFloor = PeakAmplitude;
			const float NewThreshold = PeakAmplitude * CalibrationMultiplier;
			VadEnergyThreshold = NewThreshold;

			UE_LOG(LogWhisperASR, Log,
				TEXT("Noise calibration complete: noise=%.5f, threshold=%.5f"),
				PeakAmplitude, NewThreshold);

			bIsCalibrating = false;

			// If we opened the mic just for calibration, shut it down
			if (bCalibrationOwnsMic)
			{
				if (AudioCapture && AudioCapture->IsStreamOpen() && AudioCapture->IsCapturing())
				{
					AudioCapture->StopStream();
				}
				bIsCapturing = false;
				SetComponentTickEnabled(false);
				CloseCaptureDevice();
				{
					FScopeLock Lock(&BufferCritSection);
					AudioBuffer.Reset();
					ResamplePhase = 0.0;
				}
				bCalibrationOwnsMic = false;
			}

			OnNoiseCalibrationComplete.Broadcast(PeakAmplitude, NewThreshold);
			return;
		}
	}

	// ── VAD auto-detect: continuous listen → auto-transcribe on silence ──
	if (bAutoDetectSpeech && !bStreamingMode && !bIsCalibrating)
	{
		VadCheckTimer += DeltaTime;
		if (VadCheckTimer >= 0.2f) // Check 5 times per second
		{
			VadCheckTimer = 0.f;
			const float Peak = GetRecentPeak();
			const bool bIsSpeaking = (Peak > VadEnergyThreshold);

			UE_LOG(LogWhisperASR, Verbose,
				TEXT("VAD: peak=%.5f, threshold=%.5f, speaking=%s, detected=%s, silence=%.1fs"),
				Peak, VadEnergyThreshold,
				bIsSpeaking ? TEXT("Y") : TEXT("N"),
				bSpeechDetected ? TEXT("Y") : TEXT("N"),
				SilenceTimer);

			// While a transcription is in-flight, discard audio and skip VAD.
			// Otherwise the buffer grows with silence and the next submission
			// sends minutes of dead air to Whisper, causing huge latency spikes.
			if (bTranscriptionInFlight)
			{
				FScopeLock Lock(&BufferCritSection);
				AudioBuffer.Reset();
				ResamplePhase = 0.0;
			}
			else if (bIsSpeaking)
			{
				SilenceTimer = 0.f;
				bSpeechDetected = true;
			}
			else if (bSpeechDetected)
			{
				SilenceTimer += 0.2f;
				if (SilenceTimer >= SilenceTimeoutSeconds)
				{
					UE_LOG(LogWhisperASR, Log,
						TEXT("VAD: silence timeout (%.1fs) — transcribing utterance."),
						SilenceTimer);
					TranscribeBuffer();
					bSpeechDetected = false;
					SilenceTimer = 0.f;
				}
			}
			else
			{
				// No speech detected yet — trim silence to prevent unbounded growth
				FScopeLock Lock(&BufferCritSection);
				const int32 KeepSamples = 2 * WHISPER_SAMPLE_RATE; // Keep last 2s
				if (AudioBuffer.Num() > KeepSamples)
				{
					const int32 Excess = AudioBuffer.Num() - KeepSamples;
					AudioBuffer.RemoveAt(0, Excess, EAllowShrinking::No);
				}
			}
		}
	}

	if (bStreamingMode)
	{
		StreamingTimer += DeltaTime;

		if (StreamingTimer >= StreamingIntervalSeconds)
		{
			StreamingTimer = 0.f;

			int32 BufferSamples = 0;
			float PeakAmplitude = 0.f;
			{
				FScopeLock Lock(&BufferCritSection);
				BufferSamples = AudioBuffer.Num();
				for (int32 i = 0; i < AudioBuffer.Num(); ++i)
				{
					float Abs = FMath::Abs(AudioBuffer[i]);
					if (Abs > PeakAmplitude) PeakAmplitude = Abs;
				}
			}

			const bool bIsSpeaking = (PeakAmplitude > VadEnergyThreshold) && (BufferSamples > 0);

			UE_LOG(LogWhisperASR, Verbose,
				TEXT("Streaming tick: peak=%.4f, speaking=%s, wasSpeaking=%s, inflight=%s"),
				PeakAmplitude,
				bIsSpeaking ? TEXT("Y") : TEXT("N"),
				bWasSpeaking ? TEXT("Y") : TEXT("N"),
				bTranscriptionInFlight ? TEXT("Y") : TEXT("N"));

			if (bIsSpeaking && !bTranscriptionInFlight)
			{
				// Speech detected — transcribe this chunk.
				// Results accumulate in HandleTranscriptionResult.
				TranscribeBuffer();
				bWasSpeaking = true;
			}
			else if (!bIsSpeaking && bWasSpeaking && !bTranscriptionInFlight)
			{
				// Silence after speech — user finished talking.
				// Broadcast the accumulated result and reset.
				if (AccumulatedResult.Segments.Num() > 0)
				{
					AccumulatedResult.bSuccess = true;
					UE_LOG(LogWhisperASR, Log, TEXT("Utterance complete: '%s'"),
						*AccumulatedResult.FullText);
					OnCaptureTranscriptionComplete.Broadcast(AccumulatedResult);
				}

				// Reset for next utterance
				AccumulatedResult = FWhisperResult();
				bWasSpeaking = false;

				// Discard silent buffer
				FScopeLock Lock(&BufferCritSection);
				AudioBuffer.Reset();
				ResamplePhase = 0.0;
			}
			else if (!bIsSpeaking && !bWasSpeaking && BufferSamples > 0)
			{
				// Sustained silence — just discard
				FScopeLock Lock(&BufferCritSection);
				AudioBuffer.Reset();
				ResamplePhase = 0.0;
			}
		}
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Device management
// ─────────────────────────────────────────────────────────────────────────────

bool UWhisperCaptureComponent::OpenCaptureDevice()
{
	// Create the platform audio capture object
	AudioCapture = MakeUnique<Audio::FAudioCapture>();

	// Query available devices to log and validate the chosen index
	TArray<Audio::FCaptureDeviceInfo> Devices;
	AudioCapture->GetCaptureDevicesAvailable(Devices);

	if (Devices.Num() == 0)
	{
		UE_LOG(LogWhisperASR, Error, TEXT("No audio input devices found."));
		AudioCapture.Reset();
		return false;
	}

	UE_LOG(LogWhisperASR, Log, TEXT("Found %d audio input device(s):"), Devices.Num());
	for (int32 i = 0; i < Devices.Num(); ++i)
	{
		UE_LOG(LogWhisperASR, Log, TEXT("  [%d] %s (%d ch, %d Hz)"),
			i, *Devices[i].DeviceName,
			Devices[i].InputChannels,
			Devices[i].PreferredSampleRate);
	}

	// Resolve device index
	int32 ResolvedIndex = (AudioDeviceIndex >= 0 && AudioDeviceIndex < Devices.Num())
		? AudioDeviceIndex
		: 0; // Default device

	const Audio::FCaptureDeviceInfo& ChosenDevice = Devices[ResolvedIndex];
	DeviceSampleRate  = ChosenDevice.PreferredSampleRate;
	DeviceNumChannels = FMath::Max(1, static_cast<int32>(ChosenDevice.InputChannels));

	UE_LOG(LogWhisperASR, Log, TEXT("Opening device [%d] \"%s\" (%d ch, %d Hz)"),
		ResolvedIndex, *ChosenDevice.DeviceName, DeviceNumChannels, DeviceSampleRate);

	// Configure and open the capture stream
	Audio::FAudioCaptureDeviceParams Params;
	Params.DeviceIndex = ResolvedIndex;
	Params.NumInputChannels = DeviceNumChannels;

	// The OnCapture lambda is called from the audio thread with interleaved float data
	bool bOpened = AudioCapture->OpenAudioCaptureStream(Params,
		[this](const void* InAudioRaw, int32 NumFrames, int32 NumChannels,
			int32 SampleRate, double StreamTime, bool bOverflow)
		{
			const float* InAudio = static_cast<const float*>(InAudioRaw);
			if (bOverflow)
			{
				// First-callback overflow is normal — WASAPI buffers samples
				// between OpenStream and StartStream. Subsequent overflows
				// would indicate the callback is too slow.
				UE_LOG(LogWhisperASR, Verbose, TEXT("Audio capture overflow detected."));
			}

			if (!bIsCapturing || NumFrames <= 0)
			{
				return;
			}

			// Resample + mono-mix + buffer (thread-safe)
			FScopeLock Lock(&BufferCritSection);
			const int32 PrevCount = AudioBuffer.Num();
			ResampleAndMixToMono(InAudio, NumFrames, NumChannels, SampleRate, AudioBuffer);
			TrimBufferLocked();

			// Track peak of newly appended samples for VAD
			float CallbackPeak = 0.f;
			for (int32 i = FMath::Max(0, PrevCount); i < AudioBuffer.Num(); ++i)
			{
				float Abs = FMath::Abs(AudioBuffer[i]);
				if (Abs > CallbackPeak) CallbackPeak = Abs;
			}
			SetRecentPeak(CallbackPeak);

			// Update RMS level from the most recent 100 ms of buffered audio
			const int32 RMSWindowSamples = WHISPER_SAMPLE_RATE / 10; // 1600 samples
			const int32 Count = FMath::Min(RMSWindowSamples, AudioBuffer.Num());
			const float RMS = ComputeRMS(
				AudioBuffer.GetData() + (AudioBuffer.Num() - Count), Count);
			SetRMSLevel(RMS);
		},
		1024 // NumFramesDesired — small buffer for low-latency callbacks
	);

	if (!bOpened)
	{
		UE_LOG(LogWhisperASR, Error, TEXT("Failed to open audio capture stream."));
		AudioCapture.Reset();
		return false;
	}

	return true;
}

void UWhisperCaptureComponent::CloseCaptureDevice()
{
	if (AudioCapture)
	{
		if (AudioCapture->IsStreamOpen())
		{
			if (AudioCapture->IsCapturing())
			{
				AudioCapture->StopStream();
			}
			AudioCapture->CloseStream();
		}
		AudioCapture.Reset();
	}

	DeviceSampleRate = 0;
	DeviceNumChannels = 0;
	ResamplePhase = 0.0;
}

TArray<FString> UWhisperCaptureComponent::GetAvailableInputDevices()
{
	TArray<FString> Result;

	Audio::FAudioCapture TempCapture;
	TArray<Audio::FCaptureDeviceInfo> Devices;
	TempCapture.GetCaptureDevicesAvailable(Devices);

	for (const Audio::FCaptureDeviceInfo& Dev : Devices)
	{
		Result.Add(FString::Printf(TEXT("%s (%d ch, %d Hz)"),
			*Dev.DeviceName, Dev.InputChannels, Dev.PreferredSampleRate));
	}

	return Result;
}

// ─────────────────────────────────────────────────────────────────────────────
// Capture controls
// ─────────────────────────────────────────────────────────────────────────────

bool UWhisperCaptureComponent::StartCapture()
{
	if (bIsCapturing)
	{
		UE_LOG(LogWhisperASR, Warning, TEXT("StartCapture: already capturing."));
		return true;
	}

	// Reset state
	{
		FScopeLock Lock(&BufferCritSection);
		AudioBuffer.Reset();
	}
	StreamingTimer = 0.f;
	SetRMSLevel(0.f);
	SetRecentPeak(0.f);
	ResamplePhase = 0.0;
	bTranscriptionInFlight = false;
	bWasSpeaking = false;
	bSpeechDetected = false;
	SilenceTimer = 0.f;
	VadCheckTimer = 0.f;
	AccumulatedResult = FWhisperResult();

	// Open the microphone
	if (!OpenCaptureDevice())
	{
		return false;
	}

	// Set capturing flag BEFORE starting the stream — the audio callback
	// checks this and discards data if false. StartStream fires callbacks
	// on another thread immediately.
	bIsCapturing = true;
	SetComponentTickEnabled(true);

	// Start the capture stream — callbacks begin on the audio thread
	if (!AudioCapture->StartStream())
	{
		UE_LOG(LogWhisperASR, Error, TEXT("StartCapture: failed to start audio stream."));
		bIsCapturing = false;
		SetComponentTickEnabled(false);
		CloseCaptureDevice();
		return false;
	}

	UE_LOG(LogWhisperASR, Log,
		TEXT("Microphone capture started (streaming=%s, interval=%.1fs, device=%d Hz / %d ch)."),
		bStreamingMode ? TEXT("ON") : TEXT("OFF"),
		StreamingIntervalSeconds,
		DeviceSampleRate, DeviceNumChannels);

	// Bind subsystem delegates once for the lifetime of this capture session
	UGameInstance* GI = GetOwner() ? GetOwner()->GetGameInstance() : nullptr;
	if (GI)
	{
		if (UWhisperSubsystem* Whisper = GI->GetSubsystem<UWhisperSubsystem>())
		{
			Whisper->OnTranscriptionComplete.AddUniqueDynamic(
				this, &UWhisperCaptureComponent::HandleTranscriptionResult);
			Whisper->OnSegmentReady.AddUniqueDynamic(
				this, &UWhisperCaptureComponent::HandleSegmentReady);
		}
	}

	return true;
}

void UWhisperCaptureComponent::StopCapture()
{
	if (!bIsCapturing)
	{
		return;
	}

	// Stop the audio stream first so no more callbacks arrive
	if (AudioCapture && AudioCapture->IsStreamOpen() && AudioCapture->IsCapturing())
	{
		AudioCapture->StopStream();
	}

	bIsCapturing = false;
	SetComponentTickEnabled(false);

	int32 BufferSamples = 0;
	{
		FScopeLock Lock(&BufferCritSection);
		BufferSamples = AudioBuffer.Num();
	}

	UE_LOG(LogWhisperASR, Log, TEXT("Microphone stopped. Buffer: %.2fs (%d samples)."),
		static_cast<float>(BufferSamples) / WHISPER_SAMPLE_RATE, BufferSamples);

	// Transcribe the final buffer
	if (BufferSamples > 0)
	{
		TranscribeBuffer();
	}

	// Flush any accumulated utterance that didn't get a silence-boundary
	if (AccumulatedResult.Segments.Num() > 0)
	{
		AccumulatedResult.bSuccess = true;
		UE_LOG(LogWhisperASR, Log, TEXT("Flushing final utterance: '%s'"),
			*AccumulatedResult.FullText);
		OnCaptureTranscriptionComplete.Broadcast(AccumulatedResult);
		AccumulatedResult = FWhisperResult();
	}
	bWasSpeaking = false;

	// Unbind from subsystem delegates
	UGameInstance* GI = GetOwner() ? GetOwner()->GetGameInstance() : nullptr;
	if (GI)
	{
		if (UWhisperSubsystem* Whisper = GI->GetSubsystem<UWhisperSubsystem>())
		{
			Whisper->OnTranscriptionComplete.RemoveDynamic(
				this, &UWhisperCaptureComponent::HandleTranscriptionResult);
			Whisper->OnSegmentReady.RemoveDynamic(
				this, &UWhisperCaptureComponent::HandleSegmentReady);
		}
	}

	CloseCaptureDevice();
}

void UWhisperCaptureComponent::CancelCapture()
{
	if (AudioCapture && AudioCapture->IsStreamOpen() && AudioCapture->IsCapturing())
	{
		AudioCapture->StopStream();
	}

	bIsCapturing = false;
	SetComponentTickEnabled(false);

	// Unbind from subsystem delegates
	UGameInstance* GI = GetOwner() ? GetOwner()->GetGameInstance() : nullptr;
	if (GI)
	{
		if (UWhisperSubsystem* Whisper = GI->GetSubsystem<UWhisperSubsystem>())
		{
			Whisper->OnTranscriptionComplete.RemoveDynamic(
				this, &UWhisperCaptureComponent::HandleTranscriptionResult);
			Whisper->OnSegmentReady.RemoveDynamic(
				this, &UWhisperCaptureComponent::HandleSegmentReady);
		}
	}

	ClearBuffer();
	CloseCaptureDevice();

	UE_LOG(LogWhisperASR, Log, TEXT("Microphone capture cancelled."));
}

	void UWhisperCaptureComponent::TranscribeBuffer()
{
	if (bTranscriptionInFlight)
	{
		UE_LOG(LogWhisperASR, Warning,
			TEXT("TranscribeBuffer: transcription already in flight, skipping."));
		return;
	}

	// ── Deep copy audio from audio-thread buffer to game-thread memory ──
	// UE uses per-thread memory arenas. TArray's copy operator may still
	// reference source-thread allocator metadata. We explicitly allocate
	// a fresh TArray on this thread and memcpy the raw sample data.
	TArray<float> BufferCopy;
	{
		FScopeLock Lock(&BufferCritSection);

		if (AudioBuffer.Num() == 0)
		{
			UE_LOG(LogWhisperASR, Warning, TEXT("TranscribeBuffer: buffer is empty."));
			return;
		}

		const int32 NumSamples = AudioBuffer.Num();
		BufferCopy.SetNumUninitialized(NumSamples);
		FMemory::Memcpy(BufferCopy.GetData(), AudioBuffer.GetData(), NumSamples * sizeof(float));

		// In streaming mode, keep the last OverlapSeconds of audio
		// so the next chunk has context for words at the boundary.
		if (bStreamingMode)
		{
			const int32 OverlapSamples = static_cast<int32>(StreamingOverlapSeconds * WHISPER_SAMPLE_RATE);
			if (OverlapSamples > 0 && OverlapSamples < NumSamples)
			{
				// Keep the tail as the start of the next buffer
				const int32 KeepFrom = NumSamples - OverlapSamples;
				TArray<float> Overlap;
				Overlap.SetNumUninitialized(OverlapSamples);
				FMemory::Memcpy(Overlap.GetData(),
					AudioBuffer.GetData() + KeepFrom,
					OverlapSamples * sizeof(float));
				AudioBuffer = MoveTemp(Overlap);
			}
			else
			{
				AudioBuffer.Reset();
			}
			ResamplePhase = 0.0;
		}
	}

	// ── Validate and sanitize audio data ─────────────────────────────
	int32 NanCount = 0, InfCount = 0, DenormCount = 0;
	float MinVal = 1.f, MaxVal = -1.f;
	for (int32 i = 0; i < BufferCopy.Num(); ++i)
	{
		float& S = BufferCopy[i];
		if (FMath::IsNaN(S)) { S = 0.f; NanCount++; }
		else if (!FMath::IsFinite(S)) { S = 0.f; InfCount++; }
		else if (FMath::Abs(S) < 1.17549435e-38f && S != 0.f) { S = 0.f; DenormCount++; }
		else
		{
			S = FMath::Clamp(S, -1.0f, 1.0f);
			MinVal = FMath::Min(MinVal, S);
			MaxVal = FMath::Max(MaxVal, S);
		}
	}

	UE_LOG(LogWhisperASR, Verbose,
		TEXT("Audio validation: %d samples, range=[%.6f, %.6f], NaN=%d, Inf=%d, Denorm=%d"),
		BufferCopy.Num(), MinVal, MaxVal, NanCount, InfCount, DenormCount);

	// Resolve the subsystem
	UGameInstance* GI = GetOwner() ? GetOwner()->GetGameInstance() : nullptr;
	if (!GI)
	{
		UE_LOG(LogWhisperASR, Error, TEXT("TranscribeBuffer: no GameInstance."));
		return;
	}

	UWhisperSubsystem* Whisper = GI->GetSubsystem<UWhisperSubsystem>();
	if (!Whisper || !Whisper->IsModelLoaded())
	{
		UE_LOG(LogWhisperASR, Error, TEXT("TranscribeBuffer: Whisper model not loaded."));
		return;
	}

	bTranscriptionInFlight = true;

	UE_LOG(LogWhisperASR, Log, TEXT("Submitting %.2fs of audio for transcription."),
		static_cast<float>(BufferCopy.Num()) / WHISPER_SAMPLE_RATE);

	Whisper->TranscribeAudioData(BufferCopy, TranscriptionConfig);
}

// ─────────────────────────────────────────────────────────────────────────────
// Noise floor calibration
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperCaptureComponent::CalibrateNoiseFloor(float DurationSeconds, float Multiplier)
{
	if (bIsCalibrating)
	{
		UE_LOG(LogWhisperASR, Warning, TEXT("CalibrateNoiseFloor: calibration already in progress."));
		return;
	}

	CalibrationDuration = FMath::Max(0.1f, DurationSeconds);
	CalibrationMultiplier = FMath::Max(1.0f, Multiplier);
	CalibrationTimer = 0.f;

	// If the mic isn't already open, open it just for calibration
	bCalibrationOwnsMic = !bIsCapturing;
	if (bCalibrationOwnsMic)
	{
		if (!OpenCaptureDevice())
		{
			UE_LOG(LogWhisperASR, Error, TEXT("CalibrateNoiseFloor: failed to open mic."));
			OnNoiseCalibrationComplete.Broadcast(-1.f, VadEnergyThreshold);
			return;
		}

		// Clear the shared buffer so we only measure fresh audio
		{
			FScopeLock Lock(&BufferCritSection);
			AudioBuffer.Reset();
			ResamplePhase = 0.0;
		}

		// Temporarily set capturing so the audio callback stores samples
		bIsCapturing = true;

		if (!AudioCapture->StartStream())
		{
			UE_LOG(LogWhisperASR, Error, TEXT("CalibrateNoiseFloor: failed to start stream."));
			bIsCapturing = false;
			CloseCaptureDevice();
			OnNoiseCalibrationComplete.Broadcast(-1.f, VadEnergyThreshold);
			return;
		}
	}

	bIsCalibrating = true;
	SetComponentTickEnabled(true);

	UE_LOG(LogWhisperASR, Log,
		TEXT("Noise floor calibration started (%.1fs, multiplier=%.1f)."),
		CalibrationDuration, CalibrationMultiplier);
}

void UWhisperCaptureComponent::LogAudioDiagnostics()
{
	FScopeLock Lock(&BufferCritSection);

	float Peak = 0.f;
	for (int32 i = 0; i < AudioBuffer.Num(); ++i)
	{
		float Abs = FMath::Abs(AudioBuffer[i]);
		if (Abs > Peak) Peak = Abs;
	}

	float RMS = 0.f;
	if (AudioBuffer.Num() > 0)
	{
		RMS = ComputeRMS(AudioBuffer.GetData(), AudioBuffer.Num());
	}

	UE_LOG(LogWhisperASR, Warning,
		TEXT("=== AUDIO DIAGNOSTICS ===\n")
		TEXT("  Capturing:      %s\n")
		TEXT("  Calibrating:    %s\n")
		TEXT("  StreamingMode:  %s\n")
		TEXT("  Device:         %d Hz, %d ch\n")
		TEXT("  Buffer:         %d samples (%.2f sec)\n")
		TEXT("  Peak amplitude: %.6f\n")
		TEXT("  RMS level:      %.6f\n")
		TEXT("  VAD threshold:  %.6f\n")
		TEXT("  Peak > VAD:     %s\n")
		TEXT("  Noise floor:    %.6f\n")
		TEXT("========================="),
		bIsCapturing ? TEXT("YES") : TEXT("NO"),
		bIsCalibrating ? TEXT("YES") : TEXT("NO"),
		bStreamingMode ? TEXT("YES") : TEXT("NO"),
		DeviceSampleRate, DeviceNumChannels,
		AudioBuffer.Num(),
		static_cast<float>(AudioBuffer.Num()) / static_cast<float>(WHISPER_SAMPLE_RATE),
		Peak,
		RMS,
		VadEnergyThreshold,
		(Peak > VadEnergyThreshold) ? TEXT("YES") : TEXT("NO"),
		LastMeasuredNoiseFloor);
}

void UWhisperCaptureComponent::ClearBuffer()
{
	FScopeLock Lock(&BufferCritSection);
	AudioBuffer.Reset();
	ResamplePhase = 0.0;
	SetRMSLevel(0.f);
}

float UWhisperCaptureComponent::GetBufferDuration() const
{
	FScopeLock Lock(&BufferCritSection);
	return static_cast<float>(AudioBuffer.Num()) / static_cast<float>(WHISPER_SAMPLE_RATE);
}

float UWhisperCaptureComponent::GetCurrentAudioLevel() const
{
	return GetRMSLevel();
}

// ─────────────────────────────────────────────────────────────────────────────
// RMS level (thread-safe via fixed-point int)
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperCaptureComponent::SetRMSLevel(float Value)
{
	CurrentRMSLevelFixed.Set(FMath::RoundToInt(Value * 10000.f));
}

float UWhisperCaptureComponent::GetRMSLevel() const
{
	return static_cast<float>(CurrentRMSLevelFixed.GetValue()) / 10000.f;
}

void UWhisperCaptureComponent::SetRecentPeak(float Value)
{
	RecentPeakFixed.Set(FMath::RoundToInt(Value * 10000.f));
}

float UWhisperCaptureComponent::GetRecentPeak() const
{
	return static_cast<float>(RecentPeakFixed.GetValue()) / 10000.f;
}

// ─────────────────────────────────────────────────────────────────────────────
// Resampling (called from audio thread under lock)
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperCaptureComponent::ResampleAndMixToMono(
	const float* InAudio, int32 NumFrames, int32 NumChannels,
	int32 SrcRate, TArray<float>& OutBuffer)
{
	if (NumFrames <= 0 || !InAudio)
	{
		return;
	}

	// Fast path: source is already 16 kHz mono
	if (SrcRate == WHISPER_SAMPLE_RATE && NumChannels == 1)
	{
		OutBuffer.Append(InAudio, NumFrames);
		return;
	}

	// Resample using linear interpolation with persistent phase
	const double SrcToDst = static_cast<double>(SrcRate) / static_cast<double>(WHISPER_SAMPLE_RATE);

	// Calculate how many output samples this chunk produces
	const double SrcEnd = static_cast<double>(NumFrames);
	int32 EstimatedOut = static_cast<int32>((SrcEnd - ResamplePhase) / SrcToDst) + 1;
	if (EstimatedOut <= 0)
	{
		// Not enough input to produce even one output sample; accumulate phase
		ResamplePhase -= SrcEnd;
		return;
	}

	const int32 PrevCount = OutBuffer.Num();
	OutBuffer.AddUninitialized(EstimatedOut);
	float* OutPtr = OutBuffer.GetData() + PrevCount;

	int32 Written = 0;
	double Phase = ResamplePhase;

	while (Phase < SrcEnd && Written < EstimatedOut)
	{
		const int32 Idx0 = FMath::FloorToInt(static_cast<float>(Phase));
		const int32 Idx1 = FMath::Min(Idx0 + 1, NumFrames - 1);
		const float Frac = static_cast<float>(Phase - static_cast<double>(Idx0));

		// Pick the loudest channel for each tap point.
		// Multi-channel mic arrays may carry speech on any channel;
		// averaging dilutes the signal, and channel 0 isn't always
		// the primary. Taking the max preserves full amplitude.
		float S0 = 0.f, S1 = 0.f;
		for (int32 ch = 0; ch < NumChannels; ++ch)
		{
			float A0 = InAudio[Idx0 * NumChannels + ch];
			float A1 = InAudio[Idx1 * NumChannels + ch];
			if (FMath::Abs(A0) > FMath::Abs(S0)) S0 = A0;
			if (FMath::Abs(A1) > FMath::Abs(S1)) S1 = A1;
		}

		OutPtr[Written] = FMath::Lerp(S0, S1, Frac);
		++Written;
		Phase += SrcToDst;
	}

	// Fixup: we may have over-estimated
	if (Written < EstimatedOut)
	{
		OutBuffer.SetNum(PrevCount + Written, EAllowShrinking::No);
	}

	// Carry fractional phase into next callback (subtract consumed source frames)
	ResamplePhase = Phase - SrcEnd;
}

// ─────────────────────────────────────────────────────────────────────────────
// Buffer utilities
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperCaptureComponent::TrimBufferLocked()
{
	const int32 MaxSamples = static_cast<int32>(MaxBufferDurationSeconds * WHISPER_SAMPLE_RATE);
	if (AudioBuffer.Num() > MaxSamples)
	{
		const int32 Excess = AudioBuffer.Num() - MaxSamples;
		AudioBuffer.RemoveAt(0, Excess, EAllowShrinking::No);
	}
}

float UWhisperCaptureComponent::ComputeRMS(const float* Samples, int32 Count)
{
	if (Count <= 0 || !Samples)
	{
		return 0.f;
	}

	float SumSq = 0.f;
	for (int32 i = 0; i < Count; ++i)
	{
		SumSq += Samples[i] * Samples[i];
	}
	return FMath::Sqrt(SumSq / static_cast<float>(Count));
}

// ─────────────────────────────────────────────────────────────────────────────
// Delegate handlers
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperCaptureComponent::HandleTranscriptionResult(const FWhisperResult& Result)
{
	bTranscriptionInFlight = false;

	if (!Result.bSuccess)
	{
		return;
	}

	if (bAutoDetectSpeech && !bStreamingMode)
	{
		// In auto-detect mode, each transcription is a complete utterance.
		// Fire the event immediately.
		UE_LOG(LogWhisperASR, Log, TEXT("VAD utterance: '%s'"), *Result.FullText);
		OnCaptureTranscriptionComplete.Broadcast(Result);

		// Clear the buffer for the next utterance
		FScopeLock Lock(&BufferCritSection);
		AudioBuffer.Reset();
		ResamplePhase = 0.0;
	}
	else
	{
		// Streaming mode: accumulate segments across chunks.
		// OnCaptureTranscriptionComplete fires in TickComponent on silence.
		AccumulatedResult.Segments.Append(Result.Segments);
		if (AccumulatedResult.FullText.Len() > 0 && Result.FullText.Len() > 0)
		{
			AccumulatedResult.FullText += TEXT(" ");
		}
		AccumulatedResult.FullText += Result.FullText;
		AccumulatedResult.Language = Result.Language;
		AccumulatedResult.ProcessingTimeSeconds += Result.ProcessingTimeSeconds;
	}
}

void UWhisperCaptureComponent::HandleSegmentReady(const FWhisperSegment& Segment)
{
	// Forward streaming segments to component-level delegate
	OnStreamingSegment.Broadcast(Segment);
}
