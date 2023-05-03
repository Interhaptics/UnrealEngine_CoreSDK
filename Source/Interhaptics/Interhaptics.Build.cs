/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

using UnrealBuildTool;

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
				"InterhapticsLibrary",
				"HapticEffect",
				"Projects",
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
	}
}
