/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

#include "../Public/IHGameInput.h"
#include "../Public/HAR.h"
#include "../Public/HapticDeviceManager.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FIHGameInputModule"

void FIHGameInputModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

#pragma region Load Haptic Providers

#if PLATFORM_WINDOWS
	FString BaseDir = IPluginManager::Get().FindPlugin("Interhaptics")->GetBaseDir();

	FString LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ProviderGameInput/Lib/Interhaptics.GameInputProvider.dll"));
	InterhapticsEngine::HapticDeviceManager::AddProvider(FPlatformProcess::GetDllHandle(*LibraryPath));
#endif

#pragma endregion
}

void FIHGameInputModule::ShutdownModule()
{

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FIHGameInputModule, IHGameInput)
