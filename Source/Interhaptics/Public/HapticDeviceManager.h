/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
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
		static void InitializeAll();
		static void RenderAll();
		static void CleanAll();
		INTERHAPTICS_API void AddProvider(void* deviceHandle);

		static std::vector<void*> IH_DEVICE_PROVIDERS;
	};
};
