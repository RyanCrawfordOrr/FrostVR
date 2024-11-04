/* Copyright (C) Siqi.Wu - All Rights Reserved
 * Written by Siqi.Wu <lion547016@gmail.com>, October 2020
 */

using UnrealBuildTool;
using System.IO;

public class GraphQL : ModuleRules
{
    public GraphQL(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivatePCHHeaderFile = "Private/GraphQLPrivatePCH.h";

        PublicIncludePaths.Add(
            Path.Combine(ModuleDirectory, "Public")
            );

        PrivateIncludePaths.Add(
            Path.Combine(ModuleDirectory, "Private")
            );

        AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenSSL");

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
            "Core", "CoreUObject", "Projects", "Engine", "HTTP", "SSL", "WebSockets", "Json", "JsonUtilities"
            }
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
            }
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
            }
            );

        bEnableExceptions = true;
    }
}
