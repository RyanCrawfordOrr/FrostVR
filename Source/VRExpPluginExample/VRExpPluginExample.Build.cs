// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class VRExpPluginExample : ModuleRules
{
	public VRExpPluginExample(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
       // PrivatePCHHeaderFile = "Private/WindowsMixedRealityPrecompiled.h";

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "VRExpansionPlugin" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		if(Target.Platform == UnrealTargetPlatform.Android)
		{
			var manifestfile = Path.Combine(ModuleDirectory, "AndroidSanitizePerms.xml");
				AdditionalPropertiesForReceipt.Add("AndroidPlugin", manifestfile);
		}

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
