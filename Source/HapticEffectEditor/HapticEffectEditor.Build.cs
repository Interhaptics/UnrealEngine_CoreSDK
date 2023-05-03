/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

using UnrealBuildTool;

public class HapticEffectEditor : ModuleRules
{
	public HapticEffectEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
				"AssetTools"
			});

		PrivateIncludePaths.AddRange(
			new string[] {
				"HapticEffectEditor/Private",
				"HapticEffectEditor/Private/Factories"
			});

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"ContentBrowser",
				"Core",
				"CoreUObject",
				"Engine",
				"Projects",
				"HapticEffect",
				"UnrealEd"
			});

		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"UnrealEd"
			});
	}
}
