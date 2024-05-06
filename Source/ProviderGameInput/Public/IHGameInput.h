/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "Modules/ModuleManager.h"

class FIHGameInputModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
