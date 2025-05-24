// Copyright (c) 2025 Your Name or Company. All rights reserved.

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
                "Engine" // Covers GConfig, UGameplayStatics
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UMG" // Covers UKismetSystemLibrary
            }
        );

        // Optimize build settings
        bEnableExceptions = false;
        bUseUnity = true;
        MinFilesUsingPrecompiledHeaderOverride = 1;
    }
}