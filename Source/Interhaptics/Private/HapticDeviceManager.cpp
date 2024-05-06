/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticDeviceManager.h"
#include "../Public/enums.h"

void InterhapticsEngine::HapticDeviceManager::InitializeAll()
{
	for (auto it : IH_DEVICE_PROVIDERS)
	{
		if (!it)  // Check if the device pointer is null
		{
			UE_LOG(LogTemp, Warning, TEXT("Device handle is null during initialization."));
			continue;
		}
		uintptr_t DllExport;
		DllExport = IH_GETDLLEXPORT("ProviderInit", DllExport, it);
		if (DllExport)
		{
			typedef bool(*GetInit)();
			GetInit InitFunc = (GetInit)(DllExport);
			if (!((bool)InitFunc()))
			{
				printf("Provider failed to initialize. \n");
			}
		}
	}
}

std::vector<void*>& InterhapticsEngine::HapticDeviceManager::GetDeviceProviders()
{
	return IH_DEVICE_PROVIDERS;
}

void InterhapticsEngine::HapticDeviceManager::RenderAll()
{
	// Check if a controller is connected
	bool controllerConnected = false;
	for (auto& provider : IH_DEVICE_PROVIDERS)
	{
		if (provider)
		{
			// Call the ProviderIsPresent function for this provider to check if a controller is connected
			uintptr_t DllExport = IH_GETDLLEXPORT("ProviderIsPresent", DllExport, provider);
			if (DllExport)
			{
				typedef bool(*GetIsPresent)();
				GetIsPresent IsPresentFunc = (GetIsPresent)(DllExport);
				if (IsPresentFunc())
				{
					controllerConnected = true;
					break;
				}
			}
		}
	}

	if (!controllerConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("No controller connected during rendering."));
		return;
	}

	// Render haptics for the first provider
	if (!IH_DEVICE_PROVIDERS.empty())
	{
		void* provider = IH_DEVICE_PROVIDERS[0];
		if (provider)
		{
			// Call the ProviderRenderHaptics function for this provider
			uintptr_t DllExport = IH_GETDLLEXPORT("ProviderRenderHaptics", DllExport, provider);
			if (DllExport)
			{
				typedef void(*GetRenderHaptics)();
				GetRenderHaptics RenderHapticsFunc = (GetRenderHaptics)(DllExport);
				if (RenderHapticsFunc)
				{
					RenderHapticsFunc();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("RenderHapticsFunc is null."));
				}
			}
		}
	}
}
void InterhapticsEngine::HapticDeviceManager::CleanAll()
{
	for (auto it : IH_DEVICE_PROVIDERS)
	{
		if (!it)  // Check if the device pointer is null
		{
			UE_LOG(LogTemp, Warning, TEXT("Device handle is null during cleanup."));
			continue;
		}
		uintptr_t DllExport;
		DllExport = IH_GETDLLEXPORT("ProviderClean", DllExport, it);
		if (DllExport)
		{
			typedef bool(*GetClean)();
			GetClean CleanFunc = (GetClean)(DllExport);
			if (!((bool)CleanFunc()))
			{
				printf("Provider failed to clean. \n");
			}
		}
	}
}

void InterhapticsEngine::HapticDeviceManager::AddProvider(void* device)
{
#if PLATFORM_SWITCH
	IH_DEVICE_PROVIDERS.push_back(device);
	return;
#endif
	if (device)
	{
		IH_DEVICE_PROVIDERS.push_back(device);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add a null device provider."));
	}
}
