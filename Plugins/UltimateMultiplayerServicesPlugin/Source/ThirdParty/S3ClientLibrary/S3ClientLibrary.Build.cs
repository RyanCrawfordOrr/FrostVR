/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, December 2018
 */

using System.IO;
using UnrealBuildTool;

public class S3ClientLibrary : ModuleRules
{
    public S3ClientLibrary(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.External;

        PublicIncludePaths.Add(ModuleDirectory);

        string ThirdPartyPath = System.IO.Path.Combine(ModuleDirectory, Target.Platform.ToString());

        if (Target.Type != TargetRules.TargetType.Server)
        {
            if (Target.Platform == UnrealTargetPlatform.Linux || Target.Platform == UnrealTargetPlatform.LinuxArm64)
            {
                if (Target.Platform == UnrealTargetPlatform.LinuxArm64) {
                    ThirdPartyPath = System.IO.Path.Combine(ThirdPartyPath, "aarch64-unknown-linux-gnu");
        		} else if (Target.Platform == UnrealTargetPlatform.Linux) {
                    ThirdPartyPath = System.IO.Path.Combine(ThirdPartyPath, "x86_64-unknown-linux-gnu");
        		}

                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libaws-cpp-sdk-s3.a"));
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", System.IO.Path.Combine(ModuleDirectory, "S3ClientSDK_UPL.xml"));

                {
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "arm64-v8a", "libaws-cpp-sdk-s3.a"));
                }

                {
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "x86_64", "libaws-cpp-sdk-s3.a"));
                }

            }
            else if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                if (Target.Type == TargetRules.TargetType.Editor) {
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "Editor", "aws-cpp-sdk-s3.lib"));
                    PublicDelayLoadDLLs.Add("aws-cpp-sdk-s3.dll");
                    RuntimeDependencies.Add(System.IO.Path.Combine(ThirdPartyPath, "Editor", "aws-cpp-sdk-s3.dll"));
                } else {
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "Game", "aws-cpp-sdk-s3.lib"));
                }
            }
            else if (Target.Platform == UnrealTargetPlatform.Mac)
            {
                if (Target.Type == TargetRules.TargetType.Editor) {
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "Editor", "libaws-cpp-sdk-s3.dylib"));
                    RuntimeDependencies.Add(System.IO.Path.Combine(ThirdPartyPath, "Editor", "libaws-cpp-sdk-s3.dylib"));
                } else {
                    PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "Game", "libaws-cpp-sdk-s3.a"));
                }
            }
            else if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                PublicAdditionalLibraries.Add(System.IO.Path.Combine(ThirdPartyPath, "libaws-cpp-sdk-s3.a"));
            }
        }
    }
}