/*
 * Copyright © 2024 Go Touch VR SAS. All rights reserved.
 */

using UnrealBuildTool;
using System.IO;

public class IHRazerSensa : ModuleRules
{
	public IHRazerSensa(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
                // ... add public include paths required here ...
            }
		);

		PrivateIncludePaths.AddRange(
			new string[] {
                // ... add other private include paths required here ...
            }
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Interhaptics",
				"Projects",
				"CoreUObject",
				"Engine",
				"InputCore"
                // ... other dependencies ...
            }
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                // ... add private dependencies that you statically link with here ...
            }
		);

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Lib", "Interhaptics.RazerSensaProvider.lib"));

			// Delay-load the DLLs, so we can load them from the right place first
			PublicDelayLoadDLLs.Add("Interhaptics.RazerSensaProvider.dll");

			// Ensure that the DLLs are staged along with the executable
			RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "Lib", "Interhaptics.RazerSensaProvider.dll"));
		}
	}
}
