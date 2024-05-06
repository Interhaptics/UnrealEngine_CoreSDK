/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "../Public/Interhaptics.h"
#include "../Public/HAR.h"
#include "../Public/HapticDeviceManager.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FInterhapticsModule"

void FInterhapticsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	
	FString BaseDir = IPluginManager::Get().FindPlugin("Interhaptics")->GetBaseDir();
	FString LibraryPath;

#pragma region Load Haptic Engine
	// Add on the relative location of the third party dll and load it
#if PLATFORM_WINDOWS || PLATFORM_MAC
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/Interhaptics/Lib/x64/Release/HAR.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/Interhaptics/Lib/Mac/Release/libHAR.dylib"));
#endif 

	if (LibraryPath.IsEmpty())
	{
		if (!InterhapticsEngine::v_Handle)
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("LibraryError", "DLL path is empty"));
		}
	}
	else
	{
		InterhapticsEngine::v_Handle = FPlatformProcess::GetDllHandle(*LibraryPath);
		if (!InterhapticsEngine::v_Handle)
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("LibraryError", "Failed to load InterhapticsEngine DLL"));
		}
	}
#endif
#pragma endregion
}

void FInterhapticsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(InterhapticsEngine::v_Handle);
	InterhapticsEngine::v_Handle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FInterhapticsModule, Interhaptics)
