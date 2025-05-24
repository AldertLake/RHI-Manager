#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RHI_Switcher.generated.h"

UENUM(BlueprintType)
enum class ERHIType : uint8
{
    DirectX11,
    DirectX12,
    Vulkan,
    Default
};

/**
 * A Blueprint function library for managing RHI settings in Unreal Engine.
 */
UCLASS()
class RHI_MANAGER_API URHI_Switcher : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Initializes the RHI settings at startup. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void InitializeRHI();

    /** Retrieves the currently set default RHI from the project settings as a string. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static FString GetCurrentRHI();

    /** Sets the desired RHI to be applied on the next engine launch using a string. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void SetDesiredRHI(FString NewRHI);

    /** Checks if a relaunch is required to apply the desired RHI. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static bool IsRelaunchRequired();

    /** Displays a notification if a relaunch is required to apply RHI changes. */
    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void NotifyRelaunchRequired();

private:
    static ERHIType CurrentRHIAtStartup;
    static ERHIType DesiredRHI;

    /** Helper function to convert a string to ERHIType. */
    static ERHIType StringToRHIType(const FString& RHIString);
};