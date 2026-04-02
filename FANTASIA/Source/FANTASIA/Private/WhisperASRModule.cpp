// Copyright (c) 2024 WhisperASR Plugin. All Rights Reserved.

#include "WhisperASRModule.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogWhisperASR);

#define LOCTEXT_NAMESPACE "FWhisperASRModule"

void FWhisperASRModule::StartupModule()
{
	UE_LOG(LogWhisperASR, Log, TEXT("WhisperASR module starting up."));
}

void FWhisperASRModule::ShutdownModule()
{
	UE_LOG(LogWhisperASR, Log, TEXT("WhisperASR module shutting down."));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FWhisperASRModule, WhisperASR)
