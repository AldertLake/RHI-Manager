#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RHI_Switcher.generated.h"

// Enum for RHI types, exposed to Blueprints as a dropdown
UENUM(BlueprintType)
enum class ERHIType : uint8
{
    Default,
    DirectX11,
    DirectX12,
    Vulkan
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

    /** Gets the current RHI the engine is using, returned as an enum for dropdown use. */
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

private:
    static ERHIType CurrentRHIAtStartup; // RHI the engine started with
    static ERHIType DesiredRHI;          // RHI set for next launch

    // Helper functions for enum-to-string conversion
    static FString RHITypeToString(ERHIType RHI);
    static ERHIType StringToRHIType(const FString& RHIString);
};