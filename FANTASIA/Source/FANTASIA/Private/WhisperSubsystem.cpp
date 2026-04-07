// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#include "WhisperSubsystem.h"

DEFINE_LOG_CATEGORY(LogWhisperASR);
#include "Async/Async.h"
#include "HAL/FileManager.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"

// Suppress all warnings from third-party whisper.cpp / ggml headers.
// NOTE: #pragma warning(push, 0) is NOT enough — UE adds /weXXXX flags
// that override the warning level. Only explicit disable beats /we.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4456 4457 4458 4459) // shadow variable
#pragma warning(disable: 4244 4267)           // unsafe type cast
#pragma warning(disable: 4800)                // implicit bool conversion
#pragma warning(disable: 4756)                // constant arithmetic overflow
#pragma warning(disable: 4100)                // unreferenced parameter
#pragma warning(disable: 4127)                // conditional is constant
#pragma warning(disable: 4189)                // local var not referenced
#pragma warning(disable: 4706)                // assignment in conditional
#pragma warning(disable: 4702)                // unreachable code
#pragma warning(disable: 4310)                // cast truncates constant
#pragma warning(disable: 4305)                // truncation from double to float
#pragma warning(disable: 4242 4389)           // signed/unsigned mismatch
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#include "ggml.h"
#include "ggml-cpu.h"
#include "whisper.h"

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

// ─────────────────────────────────────────────────────────────────────────────
// Lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	bShuttingDown = false;
	SetStatus(EWhisperStatus::Uninitialized);
	UE_LOG(LogWhisperASR, Log, TEXT("WhisperSubsystem initialized."));
}

void UWhisperSubsystem::Deinitialize()
{
	UE_LOG(LogWhisperASR, Log, TEXT("WhisperSubsystem shutting down..."));

	// Signal shutdown first — all async tasks check this flag
	bShuttingDown = true;

	// Free the whisper context (waits for in-flight inference via InferenceMutex)
	UnloadModel();

	Super::Deinitialize();
	UE_LOG(LogWhisperASR, Log, TEXT("WhisperSubsystem deinitialized."));
}

// ─────────────────────────────────────────────────────────────────────────────
// Status management
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperSubsystem::SetStatus(EWhisperStatus NewStatus)
{
	if (CurrentStatus != NewStatus)
	{
		CurrentStatus = NewStatus;
		// Broadcast on game thread
		if (IsInGameThread())
		{
			OnStatusChanged.Broadcast(NewStatus);
		}
		else
		{
			AsyncTask(ENamedThreads::GameThread, [this, NewStatus]()
			{
				OnStatusChanged.Broadcast(NewStatus);
			});
		}
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Model management
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperSubsystem::LoadModel(const FString& ModelFilePath)
{
	if (CurrentStatus == EWhisperStatus::Loading || CurrentStatus == EWhisperStatus::Processing)
	{
		UE_LOG(LogWhisperASR, Warning, TEXT("Cannot load model while busy (status: %d)."),
			static_cast<int32>(CurrentStatus));
		return;
	}

	// Unload any existing model first
	UnloadModel();

	if (!FPaths::FileExists(ModelFilePath))
	{
		UE_LOG(LogWhisperASR, Error, TEXT("Model file does not exist: %s"), *ModelFilePath);
		SetStatus(EWhisperStatus::Error);
		OnModelLoaded.Broadcast(false);
		return;
	}

	SetStatus(EWhisperStatus::Loading);

	// Load on a background thread to avoid blocking the game thread.
	// Use a weak pointer so PIE shutdown doesn't crash if loading outlives us.
	FString PathCopy = ModelFilePath;
	TWeakObjectPtr<UWhisperSubsystem> WeakThis(this);
	const bool bWantGPU = bUseGPU;
	const int32 DeviceIdx = GPUDeviceIndex;

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [WeakThis, PathCopy, bWantGPU, DeviceIdx]()
	{
		UE_LOG(LogWhisperASR, Log, TEXT("Loading Whisper model from: %s (GPU=%s, device=%d)"),
			*PathCopy, bWantGPU ? TEXT("ON") : TEXT("OFF"), DeviceIdx);

		// Check before the expensive load
		UWhisperSubsystem* Self = WeakThis.Get();
		if (!Self || Self->bShuttingDown)
		{
			UE_LOG(LogWhisperASR, Warning, TEXT("Model load aborted — subsystem shutting down."));
			return;
		}

		whisper_context_params CtxParams = whisper_context_default_params();
#if FANTASIA_WITH_CUDA
		CtxParams.use_gpu = bWantGPU;
		CtxParams.gpu_device = DeviceIdx;
		if (bWantGPU)
		{
			UE_LOG(LogWhisperASR, Log, TEXT("CUDA GPU acceleration enabled (device %d)."), DeviceIdx);
		}
#else
		CtxParams.use_gpu = false;
		if (bWantGPU)
		{
			UE_LOG(LogWhisperASR, Warning, TEXT("GPU requested but plugin was built without CUDA. Using CPU."));
		}
#endif
		whisper_context* Ctx = whisper_init_from_file_with_params(
			TCHAR_TO_UTF8(*PathCopy), CtxParams);

		// Return to game thread to update state
		AsyncTask(ENamedThreads::GameThread, [WeakThis, Ctx]()
		{
			UWhisperSubsystem* GameSelf = WeakThis.Get();
			if (!GameSelf || GameSelf->bShuttingDown)
			{
				// Subsystem already gone — free the context we just loaded
				if (Ctx)
				{
					whisper_free(Ctx);
				}
				return;
			}

			if (Ctx)
			{
				GameSelf->WhisperCtx = Ctx;
				GameSelf->SetStatus(EWhisperStatus::Ready);
				UE_LOG(LogWhisperASR, Log, TEXT("Whisper model loaded successfully."));
				GameSelf->OnModelLoaded.Broadcast(true);
			}
			else
			{
				GameSelf->SetStatus(EWhisperStatus::Error);
				UE_LOG(LogWhisperASR, Error, TEXT("Failed to load Whisper model."));
				GameSelf->OnModelLoaded.Broadcast(false);
			}
		});
	});
}

/** Locate the FANTASIA plugin base directory via IPluginManager. */
static FString GetFantasiaPluginBaseDir()
{
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("FANTASIA"));
	if (Plugin.IsValid())
	{
		return Plugin->GetBaseDir();
	}
	// Fallback: assume project-level Plugins/FANTASIA
	return FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("FANTASIA"));
}

void UWhisperSubsystem::LoadModelBySize(EWhisperModelSize Size)
{
	FString ModelDir = GetDefaultModelDirectory();
	FString FileName;

	switch (Size)
	{
	case EWhisperModelSize::Tiny:   FileName = TEXT("ggml-tiny.bin");   break;
	case EWhisperModelSize::Base:   FileName = TEXT("ggml-base.bin");   break;
	case EWhisperModelSize::Small:  FileName = TEXT("ggml-small.bin");  break;
	case EWhisperModelSize::Medium: FileName = TEXT("ggml-medium.bin"); break;
	case EWhisperModelSize::Large:  FileName = TEXT("ggml-large.bin");  break;
	}

	FString FullPath = FPaths::Combine(ModelDir, FileName);
	LoadModel(FullPath);
}

void UWhisperSubsystem::LoadModelByName(const FString& ModelFileName)
{
	const FString PluginDir = GetFantasiaPluginBaseDir();

	// Search the standard model directories for the given filename
	TArray<FString> SearchDirs;
	SearchDirs.Add(FPaths::Combine(PluginDir, TEXT("Resources")));
	SearchDirs.Add(FPaths::Combine(PluginDir, TEXT("Content"), TEXT("Models")));
	SearchDirs.Add(FPaths::Combine(FPaths::ProjectContentDir(), TEXT("WhisperModels")));

	for (const FString& Dir : SearchDirs)
	{
		FString FullPath = FPaths::Combine(Dir, ModelFileName);
		if (FPaths::FileExists(FullPath))
		{
			LoadModel(FullPath);
			return;
		}
	}

	UE_LOG(LogWhisperASR, Error, TEXT("Model file '%s' not found in any search directory."), *ModelFileName);
	SetStatus(EWhisperStatus::Error);
	OnModelLoaded.Broadcast(false);
}

void UWhisperSubsystem::UnloadModel()
{
	if (WhisperCtx)
	{
		// Wait for any in-flight inference to finish before freeing
		FScopeLock InferenceLock(&InferenceMutex);

		whisper_free(WhisperCtx);
		WhisperCtx = nullptr;
		SetStatus(EWhisperStatus::Uninitialized);
		UE_LOG(LogWhisperASR, Log, TEXT("Whisper model unloaded."));
	}
}

bool UWhisperSubsystem::IsModelLoaded() const
{
	return WhisperCtx != nullptr && CurrentStatus == EWhisperStatus::Ready;
}

bool UWhisperSubsystem::IsGPUSupported()
{
#if FANTASIA_WITH_CUDA
	return true;
#else
	return false;
#endif
}

// ─────────────────────────────────────────────────────────────────────────────
// Transcription
// ─────────────────────────────────────────────────────────────────────────────

void UWhisperSubsystem::TranscribeAudioFile(const FString& WavFilePath, FWhisperConfig Config)
{
	if (!IsModelLoaded())
	{
		UE_LOG(LogWhisperASR, Error, TEXT("Cannot transcribe: model not loaded."));
		FWhisperResult ErrorResult;
		ErrorResult.bSuccess = false;
		ErrorResult.ErrorMessage = TEXT("Model not loaded.");
		OnTranscriptionComplete.Broadcast(ErrorResult);
		return;
	}

	// Load WAV on background thread, then transcribe
	FString PathCopy = WavFilePath;
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, PathCopy, Config]()
	{
		TArray<float> Samples;
		bool bLoaded = LoadWavFile(PathCopy, Samples);

		if (!bLoaded || Samples.Num() == 0)
		{
			FWhisperResult ErrorResult;
			ErrorResult.bSuccess = false;
			ErrorResult.ErrorMessage = FString::Printf(
				TEXT("Failed to load WAV file: %s"), *PathCopy);

			AsyncTask(ENamedThreads::GameThread, [this, ErrorResult]()
			{
				OnTranscriptionComplete.Broadcast(ErrorResult);
			});
			return;
		}

		FWhisperResult Result = RunInference(Samples, Config);

		AsyncTask(ENamedThreads::GameThread, [this, Result]()
		{
			OnTranscriptionComplete.Broadcast(Result);
		});
	});
}

void UWhisperSubsystem::TranscribeAudioData(const TArray<float>& PCMData, FWhisperConfig Config)
{
	if (bShuttingDown)
	{
		return;
	}

	if (!IsModelLoaded())
	{
		UE_LOG(LogWhisperASR, Error, TEXT("Cannot transcribe: model not loaded."));
		FWhisperResult ErrorResult;
		ErrorResult.bSuccess = false;
		ErrorResult.ErrorMessage = TEXT("Model not loaded.");
		OnTranscriptionComplete.Broadcast(ErrorResult);
		return;
	}

	if (PCMData.Num() == 0)
	{
		FWhisperResult ErrorResult;
		ErrorResult.bSuccess = false;
		ErrorResult.ErrorMessage = TEXT("Empty audio data.");
		OnTranscriptionComplete.Broadcast(ErrorResult);
		return;
	}

	// Deep copy data for the background thread — explicit allocation
	// on this thread + raw memcpy to avoid cross-thread allocator issues.
	TArray<float> DataCopy;
	DataCopy.SetNumUninitialized(PCMData.Num());
	FMemory::Memcpy(DataCopy.GetData(), PCMData.GetData(), PCMData.Num() * sizeof(float));

	// Use a weak pointer to safely check if subsystem is still alive in callbacks
	TWeakObjectPtr<UWhisperSubsystem> WeakThis(this);

	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask,
		[WeakThis, DataCopy = MoveTemp(DataCopy), Config]()
	{
		UWhisperSubsystem* Self = WeakThis.Get();
		if (!Self || Self->bShuttingDown)
		{
			return;
		}

		FWhisperResult Result = Self->RunInference(DataCopy, Config);

		if (Self->bShuttingDown)
		{
			return;
		}

		AsyncTask(ENamedThreads::GameThread, [WeakThis, Result]()
		{
			UWhisperSubsystem* GameSelf = WeakThis.Get();
			if (GameSelf && !GameSelf->bShuttingDown)
			{
				GameSelf->OnTranscriptionComplete.Broadcast(Result);
			}
		});
	});
}

FWhisperResult UWhisperSubsystem::TranscribeSync(const TArray<float>& PCMData,
	const FWhisperConfig& Config)
{
	if (!IsModelLoaded())
	{
		FWhisperResult R;
		R.bSuccess = false;
		R.ErrorMessage = TEXT("Model not loaded.");
		return R;
	}

	return RunInference(PCMData, Config);
}

// ─────────────────────────────────────────────────────────────────────────────
// Core inference
// ─────────────────────────────────────────────────────────────────────────────

FWhisperResult UWhisperSubsystem::RunInference(const TArray<float>& Samples,
	const FWhisperConfig& Config)
{
	// whisper_full is NOT thread-safe on the same context.
	// Serialize all inference calls.
	FScopeLock InferenceLock(&InferenceMutex);

	FWhisperResult Result;

	if (bShuttingDown)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("Subsystem is shutting down.");
		return Result;
	}

	if (!WhisperCtx)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("No whisper context.");
		return Result;
	}

	SetStatus(EWhisperStatus::Processing);

	const double StartTime = FPlatformTime::Seconds();

	// Build whisper_full_params
	whisper_full_params Params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);

	// Thread count — use physical cores only. Hyperthreads share SIMD
	// execution units and actually slow down ggml's vectorized loops.
	Params.n_threads = (Config.NumThreads > 0)
		? Config.NumThreads
		: FMath::Max(1, static_cast<int>(FPlatformMisc::NumberOfCores()));

	// Task
	Params.translate = (Config.Task == EWhisperTask::Translate);

	// Language
	FString LangStr = LanguageToString(Config.Language);
	auto LangUtf8 = StringCast<ANSICHAR>(*LangStr);
	if (Config.Language == EWhisperLanguage::Auto)
	{
		Params.language = nullptr; // auto-detect
	}
	else
	{
		Params.language = LangUtf8.Get();
	}

	// Suppress non-speech
	Params.suppress_blank = Config.bSuppressNonSpeech;
	Params.suppress_nst   = Config.bSuppressNonSpeech;

	// Token timestamps
	Params.token_timestamps = Config.bTokenTimestamps;

	// Temperature
	Params.temperature = Config.Temperature;

	// Initial prompt
	auto PromptUtf8 = StringCast<ANSICHAR>(*Config.InitialPrompt);
	if (!Config.InitialPrompt.IsEmpty())
	{
		Params.initial_prompt = PromptUtf8.Get();
	}

	// Segment callback for streaming
	Params.new_segment_callback = [](whisper_context* Ctx, whisper_state* /*State*/,
		int NewSegmentCount, void* UserData)
	{
		UWhisperSubsystem* Self = static_cast<UWhisperSubsystem*>(UserData);
		if (!Self || Self->bShuttingDown) return;

		const int TotalSegments = whisper_full_n_segments(Ctx);
		for (int i = TotalSegments - NewSegmentCount; i < TotalSegments; ++i)
		{
			FWhisperSegment Seg;
			Seg.StartTime = static_cast<float>(whisper_full_get_segment_t0(Ctx, i)) / 100.0f;
			Seg.EndTime   = static_cast<float>(whisper_full_get_segment_t1(Ctx, i)) / 100.0f;
			Seg.Text      = UTF8_TO_TCHAR(whisper_full_get_segment_text(Ctx, i));
			Seg.Text.TrimStartAndEndInline();

			const int NumTokens = whisper_full_n_tokens(Ctx, i);
			float SumProb = 0.f;
			for (int t = 0; t < NumTokens; ++t)
			{
				SumProb += whisper_full_get_token_p(Ctx, i, t);
			}
			Seg.Confidence = (NumTokens > 0) ? (SumProb / NumTokens) : 0.f;

			if (!Self->bShuttingDown)
			{
				AsyncTask(ENamedThreads::GameThread, [Self, Seg]()
				{
					if (Self && !Self->bShuttingDown)
					{
						Self->OnSegmentReady.Broadcast(Seg);
					}
				});
			}
		}
	};
	Params.new_segment_callback_user_data = this;

	// ── Run inference ────────────────────────────────────────────────────

	int RetCode = whisper_full(WhisperCtx, Params, Samples.GetData(), Samples.Num());

	const double EndTime = FPlatformTime::Seconds();
	Result.ProcessingTimeSeconds = static_cast<float>(EndTime - StartTime);

	if (RetCode != 0)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = FString::Printf(TEXT("whisper_full returned error code %d"), RetCode);
		SetStatus(EWhisperStatus::Ready);
		return Result;
	}

	// ── Collect segments ─────────────────────────────────────────────────

	const int NumSegments = whisper_full_n_segments(WhisperCtx);
	FString FullText;

	for (int i = 0; i < NumSegments; ++i)
	{
		FWhisperSegment Seg;
		Seg.StartTime = static_cast<float>(whisper_full_get_segment_t0(WhisperCtx, i)) / 100.0f;
		Seg.EndTime   = static_cast<float>(whisper_full_get_segment_t1(WhisperCtx, i)) / 100.0f;
		Seg.Text      = UTF8_TO_TCHAR(whisper_full_get_segment_text(WhisperCtx, i));
		Seg.Text.TrimStartAndEndInline();

		const int NumTokens = whisper_full_n_tokens(WhisperCtx, i);
		float SumProb = 0.f;
		for (int t = 0; t < NumTokens; ++t)
		{
			SumProb += whisper_full_get_token_p(WhisperCtx, i, t);
		}
		Seg.Confidence = (NumTokens > 0) ? (SumProb / NumTokens) : 0.f;

		Result.Segments.Add(Seg);

		if (FullText.Len() > 0) FullText += TEXT(" ");
		FullText += Seg.Text;
	}

	Result.FullText = FullText;
	Result.bSuccess = true;

	// Detected language
	int LangId = whisper_full_lang_id(WhisperCtx);
	if (LangId >= 0)
	{
		Result.Language = UTF8_TO_TCHAR(whisper_lang_str(LangId));
	}

	UE_LOG(LogWhisperASR, Log,
		TEXT("Transcription complete: %d segments, %.2fs processing, lang=%s"),
		NumSegments, Result.ProcessingTimeSeconds, *Result.Language);

	SetStatus(EWhisperStatus::Ready);
	return Result;
}

// ─────────────────────────────────────────────────────────────────────────────
// Audio utilities
// ─────────────────────────────────────────────────────────────────────────────

bool UWhisperSubsystem::LoadWavFile(const FString& WavFilePath, TArray<float>& OutSamples)
{
	OutSamples.Reset();

	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *WavFilePath))
	{
		UE_LOG(LogWhisperASR, Error, TEXT("Failed to read file: %s"), *WavFilePath);
		return false;
	}

	// Minimal WAV header parsing
	if (FileData.Num() < 44)
	{
		UE_LOG(LogWhisperASR, Error, TEXT("File too small for WAV header: %s"), *WavFilePath);
		return false;
	}

	const uint8* Data = FileData.GetData();

	// Verify RIFF header
	if (FMemory::Memcmp(Data, "RIFF", 4) != 0 || FMemory::Memcmp(Data + 8, "WAVE", 4) != 0)
	{
		UE_LOG(LogWhisperASR, Error, TEXT("Not a valid WAV file: %s"), *WavFilePath);
		return false;
	}

	// Find "fmt " and "data" chunks
	int32 FmtOffset = -1;
	int32 DataOffset = -1;
	int32 DataSize = 0;

	int32 Offset = 12;
	while (Offset + 8 <= FileData.Num())
	{
		const char* ChunkId = reinterpret_cast<const char*>(Data + Offset);
		int32 ChunkSize = *reinterpret_cast<const int32*>(Data + Offset + 4);

		if (FMemory::Memcmp(ChunkId, "fmt ", 4) == 0)
		{
			FmtOffset = Offset + 8;
		}
		else if (FMemory::Memcmp(ChunkId, "data", 4) == 0)
		{
			DataOffset = Offset + 8;
			DataSize = ChunkSize;
			break;
		}

		Offset += 8 + ChunkSize;
		if (ChunkSize % 2 != 0) Offset++; // padding byte
	}

	if (FmtOffset < 0 || DataOffset < 0)
	{
		UE_LOG(LogWhisperASR, Error, TEXT("Could not find fmt/data chunks in WAV: %s"), *WavFilePath);
		return false;
	}

	// Parse fmt chunk
	const uint16 AudioFormat = *reinterpret_cast<const uint16*>(Data + FmtOffset);
	const uint16 NumChannels = *reinterpret_cast<const uint16*>(Data + FmtOffset + 2);
	const uint32 SampleRate  = *reinterpret_cast<const uint32*>(Data + FmtOffset + 4);
	const uint16 BitsPerSample = *reinterpret_cast<const uint16*>(Data + FmtOffset + 14);

	if (AudioFormat != 1) // PCM
	{
		UE_LOG(LogWhisperASR, Error, TEXT("WAV is not PCM format (format=%d): %s"),
			AudioFormat, *WavFilePath);
		return false;
	}

	if (BitsPerSample != 16)
	{
		UE_LOG(LogWhisperASR, Error, TEXT("WAV is not 16-bit (bits=%d): %s"),
			BitsPerSample, *WavFilePath);
		return false;
	}

	// Convert to float
	const int32 NumSamplesTotal = DataSize / (BitsPerSample / 8);
	const int16* SampleData = reinterpret_cast<const int16*>(Data + DataOffset);

	// Mix to mono if needed
	const int32 NumFrames = NumSamplesTotal / NumChannels;
	TArray<float> MonoSamples;
	MonoSamples.SetNumUninitialized(NumFrames);

	for (int32 i = 0; i < NumFrames; ++i)
	{
		float Sum = 0.f;
		for (uint16 ch = 0; ch < NumChannels; ++ch)
		{
			Sum += static_cast<float>(SampleData[i * NumChannels + ch]) / 32768.f;
		}
		MonoSamples[i] = Sum / NumChannels;
	}

	// Resample to 16 kHz if necessary (simple linear interpolation)
	if (SampleRate != 16000)
	{
		const double Ratio = static_cast<double>(SampleRate) / 16000.0;
		const int32 OutCount = static_cast<int32>(NumFrames / Ratio);
		OutSamples.SetNumUninitialized(OutCount);

		for (int32 i = 0; i < OutCount; ++i)
		{
			const double SrcIdx = i * Ratio;
			const int32 Idx0 = FMath::FloorToInt(static_cast<float>(SrcIdx));
			const int32 Idx1 = FMath::Min(Idx0 + 1, NumFrames - 1);
			const float Frac = static_cast<float>(SrcIdx - Idx0);
			OutSamples[i] = FMath::Lerp(MonoSamples[Idx0], MonoSamples[Idx1], Frac);
		}
	}
	else
	{
		OutSamples = MoveTemp(MonoSamples);
	}

	UE_LOG(LogWhisperASR, Log,
		TEXT("Loaded WAV: %d Hz, %d ch, %d frames -> %d samples at 16 kHz"),
		SampleRate, NumChannels, NumFrames, OutSamples.Num());

	return true;
}

void UWhisperSubsystem::ConvertInt16ToFloat(const TArray<uint8>& Int16Data,
	TArray<float>& OutSamples)
{
	const int32 NumSamples = Int16Data.Num() / 2;
	OutSamples.SetNumUninitialized(NumSamples);
	const int16* Src = reinterpret_cast<const int16*>(Int16Data.GetData());

	for (int32 i = 0; i < NumSamples; ++i)
	{
		OutSamples[i] = static_cast<float>(Src[i]) / 32768.f;
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Utility
// ─────────────────────────────────────────────────────────────────────────────

FString UWhisperSubsystem::LanguageToString(EWhisperLanguage Language)
{
	switch (Language)
	{
	case EWhisperLanguage::Auto:       return TEXT("auto");
	case EWhisperLanguage::English:    return TEXT("en");
	case EWhisperLanguage::Spanish:    return TEXT("es");
	case EWhisperLanguage::French:     return TEXT("fr");
	case EWhisperLanguage::German:     return TEXT("de");
	case EWhisperLanguage::Italian:    return TEXT("it");
	case EWhisperLanguage::Portuguese: return TEXT("pt");
	case EWhisperLanguage::Russian:    return TEXT("ru");
	case EWhisperLanguage::Chinese:    return TEXT("zh");
	case EWhisperLanguage::Japanese:   return TEXT("ja");
	case EWhisperLanguage::Korean:     return TEXT("ko");
	case EWhisperLanguage::Arabic:     return TEXT("ar");
	case EWhisperLanguage::Hindi:      return TEXT("hi");
	case EWhisperLanguage::Dutch:      return TEXT("nl");
	case EWhisperLanguage::Turkish:    return TEXT("tr");
	case EWhisperLanguage::Polish:     return TEXT("pl");
	case EWhisperLanguage::Swedish:    return TEXT("sv");
	case EWhisperLanguage::Ukrainian:  return TEXT("uk");
	default:                           return TEXT("en");
	}
}

FString UWhisperSubsystem::GetDefaultModelDirectory()
{
	const FString PluginDir = GetFantasiaPluginBaseDir();

	// 1. Plugin Resources/ folder (ships with the plugin)
	FString ResourcesDir = FPaths::Combine(PluginDir, TEXT("Resources"));
	if (FPaths::DirectoryExists(ResourcesDir))
	{
		return ResourcesDir;
	}

	// 2. Plugin Content/Models/
	FString ContentDir = FPaths::Combine(PluginDir, TEXT("Content"), TEXT("Models"));
	if (FPaths::DirectoryExists(ContentDir))
	{
		return ContentDir;
	}

	// 3. Project Content/WhisperModels/
	return FPaths::Combine(FPaths::ProjectContentDir(), TEXT("WhisperModels"));
}
