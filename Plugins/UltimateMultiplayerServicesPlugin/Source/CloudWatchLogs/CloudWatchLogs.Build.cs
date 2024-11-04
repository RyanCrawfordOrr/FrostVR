/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, December 2018
 */

using System.IO;
using UnrealBuildTool;

public class CloudWatchLogs : ModuleRules
{
    public CloudWatchLogs(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "Private/CloudWatchLogsPrivatePCH.h";

        IWYUSupport = IWYUSupport.Full;
        bEnableExceptions = true;

        PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "InputCore", "Projects", "AWSCore", "AWSCoreLibrary", "CloudWatchLogsClientLibrary" });

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));

        if (Target.Type != TargetRules.TargetType.Server)
        {
            if (Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.LinuxArm64 || Target.Platform == UnrealTargetPlatform.Android || Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.IOS)
            {
                PublicDefinitions.Add("WITH_CLOUDWATCHLOGSCLIENTSDK=1");
            }
            else
            {
                PublicDefinitions.Add("WITH_CLOUDWATCHLOGSCLIENTSDK=0");
            }
        }
        else
        {
            PublicDefinitions.Add("WITH_CLOUDWATCHLOGSCLIENTSDK=0");
        }
    }
}
