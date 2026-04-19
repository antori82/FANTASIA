/**
 * @file FANTASIATests.h
 * @brief Module header for the FANTASIATests editor module.
 */

#pragma once

#include "Modules/ModuleManager.h"

/**
 * @brief Module interface for FANTASIATests, the automated test suite for the FANTASIA plugin.
 *
 * This module has no startup or shutdown logic; it exists solely to register
 * Unreal Automation tests defined in the Private source files.
 */
class FFANTASIATestsModule : public IModuleInterface
{
public:
	virtual void StartupModule() override {}
	virtual void ShutdownModule() override {}
};
