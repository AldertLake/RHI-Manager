// Copyright (c) 2025 Your Name or Company. All rights reserved.

using UnrealBuildTool;

public class RHI_Manager : ModuleRules
{
    public RHI_Manager(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // No additional include paths needed for this module
        PublicIncludePaths.AddRange(
            new string[]
            {
                // Add public include paths here if needed for external modules
            }
        );

        PrivateIncludePaths.AddRange(
            new string[]
            {
                // Add private include paths here if needed for internal headers
            }
        );

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
                // Required for UKismetSystemLibrary (PrintString)
                "UMG"
            }
        );

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // No dynamically loaded modules required
            }
        );

        // Optimize build settings
        bEnableExceptions = false;
        bUseUnity = true; // Enable Unity builds for faster compilation
        MinFilesUsingPrecompiledHeaderOverride = 1;
    }
}