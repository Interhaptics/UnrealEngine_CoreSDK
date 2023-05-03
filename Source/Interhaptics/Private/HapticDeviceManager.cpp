/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "HapticDeviceManager.h"

void InterhapticsEngine::HapticDeviceManager::InitializeAll()
{
	for (auto it : IH_DEVICE_PROVIDERS)
	{
		if (it)
		{
			void* DllExport = FPlatformProcess::GetDllExport(it, *FString("ProviderInit"));
			if (DllExport)
			{
				typedef bool(*GetInit)();
				GetInit InitFunc = (GetInit)(DllExport);
				(bool)InitFunc();
			}
		}
	}

}

void InterhapticsEngine::HapticDeviceManager::RenderAll()
{
	for (auto it : IH_DEVICE_PROVIDERS)
	{
		if (it)
		{
			void* DllExport = FPlatformProcess::GetDllExport(it, *FString("ProviderRenderHaptics"));
			if (DllExport)
			{
				typedef void(*GetRenderHaptics)();
				GetRenderHaptics RenderHapticsFunc = (GetRenderHaptics)(DllExport);
				(void)RenderHapticsFunc();
			}
		}
	}
}

void InterhapticsEngine::HapticDeviceManager::CleanAll()
{
	for (auto it : IH_DEVICE_PROVIDERS)
	{
		if (it)
		{
			void* DllExport = FPlatformProcess::GetDllExport(it, *FString("ProviderClean"));
			if (DllExport)
			{
				typedef bool(*GetClean)();
				GetClean CleanFunc = (GetClean)(DllExport);
				(bool)CleanFunc();
			}
		}
	}
}

void InterhapticsEngine::HapticDeviceManager::AddProvider(void* device)
{
	IH_DEVICE_PROVIDERS.push_back(device);
}
