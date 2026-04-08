/**
 * @file FANTASIA.h
 * @brief FANTASIA plugin module interface.
 *
 * Declares FFANTASIAModule, the primary module class that bootstraps the
 * plugin when loaded by the Unreal Engine module system.
 */

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Primary module class for the FANTASIA plugin.
 *
 * Handles plugin-level startup and shutdown logic invoked by the engine's
 * module loader. Timing is governed by the LoadingPhase set in the
 * @c .uplugin descriptor.
 */
class FFANTASIAModule : public IModuleInterface
{
public:

	/** Called after the module DLL is loaded; performs one-time initialization. */
	virtual void StartupModule() override;

	/** Called before the module DLL is unloaded; releases plugin-level resources. */
	virtual void ShutdownModule() override;
};
