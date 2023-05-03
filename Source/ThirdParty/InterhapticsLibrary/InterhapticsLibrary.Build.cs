/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

using System.IO;
using UnrealBuildTool;

public class InterhapticsLibrary : ModuleRules
{
	public InterhapticsLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "HAR.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "Interhaptics.XInputProvider.lib"));

			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("HAR.dll");
			PublicDelayLoadDLLs.Add("Interhaptics.XInputProvider.dll");

			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "x64", "Release", "HAR.dll"));
			RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "x64", "Release", "Interhaptics.XInputProvider.dll"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libHAR.dylib"));
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/InterhapticsLibrary/Mac/Release/libHAR.dylib");
		}
	}
}
