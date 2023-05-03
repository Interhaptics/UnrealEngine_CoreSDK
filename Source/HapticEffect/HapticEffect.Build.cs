/* ​
* Copyright © 2023 Go Touch VR SAS. All rights reserved.
* ​
*/

namespace UnrealBuildTool.Rules
{
	public class HapticEffect : ModuleRules
	{
		public HapticEffect(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PublicDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
				});

			PrivateIncludePaths.AddRange(
				new string[] {
					
				});
		}
	}
}
