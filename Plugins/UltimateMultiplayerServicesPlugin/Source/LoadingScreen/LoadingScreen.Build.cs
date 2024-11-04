/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, Nov 2019
 */

namespace UnrealBuildTool.Rules
{
	public class LoadingScreen : ModuleRules
	{
		public LoadingScreen(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
			
			PrivateDependencyModuleNames.AddRange(
                new string[] { 
                    "Core", 
                    "CoreUObject",
                    "Engine",
                    "InputCore",
			        "MoviePlayer",
			        "UMG"
                }
            );
		}
	}
}
