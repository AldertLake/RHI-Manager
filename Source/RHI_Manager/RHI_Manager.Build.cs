/************************************************************************************
 *                                                                                  *
 * Copyright (c) 2025 AldertLake. All Rights Reserved.                              *
 * GitHub: https://github.com/AldertLake/Windows-Native-Toolkit                     *
 *                                                                                  *
 ************************************************************************************/

using UnrealBuildTool;

public class RHI_Manager : ModuleRules
{
    public RHI_Manager(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {

            }
        );

        // Optimize build settings
        bEnableExceptions = false;
        bUseUnity = true;
        MinFilesUsingPrecompiledHeaderOverride = 1;
    }
}