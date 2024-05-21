/* ​
* Copyright © 2024 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticDeviceManager.h"
#include "enums.h"

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
        if (IsPresentFunc() && IsPresentFunc)
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

    for (auto& provider : IH_DEVICE_PROVIDERS)
    {
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
            try {
              RenderHapticsFunc();
            }
            catch (const std::exception& e) {
              UE_LOG(LogTemp, Error, TEXT("Exception during haptics rendering: %s"), *FString(e.what()));
            }
            catch (...) {
              UE_LOG(LogTemp, Error, TEXT("Unknown exception during haptics rendering"));
            }
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
