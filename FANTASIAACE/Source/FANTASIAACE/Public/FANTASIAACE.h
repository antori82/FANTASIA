/**
 * @file FANTASIAACE.h
 * @brief Module header for the FANTASIAACE optional plugin.
 *
 * Provides UACERESTTTSComponent, a URESTTTSComponent subclass that
 * animates a UACEAudioCurveSourceComponent via NVIDIA Audio2Face.
 */

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Primary module class for the optional FANTASIAACE plugin.
 *
 * FANTASIAACE is the NVIDIA Audio2Face companion to the core FANTASIA
 * plugin. It is intentionally thin: the module itself has no startup
 * work beyond a log line; its purpose is to register UACERESTTTSComponent,
 * which subclasses URESTTTSComponent to add A2F lip-sync.
 *
 * @see UACERESTTTSComponent
 */
class FFANTASIAACEModule : public IModuleInterface
{
public:

    /** Called after the module DLL is loaded; logs availability of UACERESTTTSComponent. */
    virtual void StartupModule() override;

    /** Called before the module DLL is unloaded; no resources to release. */
    virtual void ShutdownModule() override;
};
