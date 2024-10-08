/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#pragma once

#include "CoreMinimal.h"
#include <vector>

/**
 * 
 */
namespace InterhapticsEngine
{
	namespace HapticDeviceManager
	{
		void InitializeAll();
		void RenderAll();
		void CleanAll();
		INTERHAPTICS_API void AddProvider(void* deviceHandle);

		std::vector<void*> IH_DEVICE_PROVIDERS;

  };
};
