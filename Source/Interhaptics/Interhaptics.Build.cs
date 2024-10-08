/*
 * Copyright © 2024 Go Touch VR SAS. All rights reserved.
 */

using UnrealBuildTool;
using System.IO;

public class Interhaptics : ModuleRules
{
	public Interhaptics(ReadOnlyTargetRules Target) : base(Target)
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
				"HapticEffect",
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

		// Adjust the base path to point to the new ThirdParty folder location
		string ThirdPartyPath = Path.Combine(ModuleDirectory, "Lib", "x64", "Release");


		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicDefinitions.Add("PLATFORM_SWITCH=0");
			PublicDefinitions.Add("PLATFORM_PS5=0");
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "HAR.lib"));

			// Delay-load the DLLs, so we can load them from the right place first
			PublicDelayLoadDLLs.Add("HAR.dll");

			// Ensure that the DLLs are staged along with the executable
			RuntimeDependencies.Add(Path.Combine(ThirdPartyPath, "HAR.dll"));
		}
	}
}
