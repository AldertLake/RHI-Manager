// Copyright (c) 2025 Your Name or Company. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RHI_Switcher.generated.h"

// Enum for RHI types, exposed to Blueprints as a dropdown
UENUM(BlueprintType)
enum class ERHIType : uint8
{
    Default UMETA(DisplayName = "Default"),
    DirectX11 UMETA(DisplayName = "DirectX 11"),
    DirectX12 UMETA(DisplayName = "DirectX 12"),
    Vulkan UMETA(DisplayName = "Vulkan")
};

/**
 * Blueprint function library for managing RHI settings with enum dropdowns.
 */
UCLASS()
class RHI_MANAGER_API URHI_Switcher : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Initializes RHI settings at startup. Call this once before using other nodes. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void InitializeRHI();

    /** Gets the current RHI from project settings, returned as an enum for dropdown use. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static ERHIType GetCurrentRHI();

    /** Sets the desired RHI for the next engine launch, using an enum dropdown. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void SetDesiredRHI(ERHIType NewRHI);

    /** Checks if a relaunch is required to apply the new RHI setting. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static bool IsRelaunchRequired();

    /** Shows a message if a relaunch is needed to apply RHI changes. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void NotifyRelaunchRequired();

    /** Restarts the game to reload the current level. Note: Full RHI application requires an engine restart. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void RestartGame();

private:
    static ERHIType CurrentRHIAtStartup; // RHI the engine started with
    static ERHIType DesiredRHI;          // RHI set for next launch

    // Helper functions for enum-to-string conversion
    static FString RHITypeToString(ERHIType RHI);
    static ERHIType StringToRHIType(const FString& RHIString);
};