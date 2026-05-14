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

class FFANTASIAACEModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
