/**
 * @file FANTASIA.cpp
 * @brief FANTASIA plugin module implementation.
 */

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FANTASIA.h"

DEFINE_LOG_CATEGORY_STATIC(LogFANTASIA, Log, All);

#define LOCTEXT_NAMESPACE "FFANTASIAModule"

void FFANTASIAModule::StartupModule()
{
	// Surface the installation-procedure pointer once at module startup so
	// users hitting ACE / Whisper recompile issues see the wiki link in the
	// log without needing to open the plugin descriptor. This hint will be
	// removed once UE 5.7 makes the rebuild step unnecessary.
	UE_LOG(LogFANTASIA, Log,
		TEXT("FANTASIA loaded. ACE and Whisper integrations may require a one-time C++ rebuild — ")
		TEXT("see the installation guide at https://github.com/antori82/FANTASIA/wiki"));
}

void FFANTASIAModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFANTASIAModule, FANTASIA)