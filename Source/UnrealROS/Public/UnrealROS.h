#pragma once

#include "ModuleManager.h"

class UnrealROSImpl : public IModuleInterface
{

public:

		/** IModuleInterface implementation */
		virtual void StartupModule() override;
		virtual void ShutdownModule() override;

};
