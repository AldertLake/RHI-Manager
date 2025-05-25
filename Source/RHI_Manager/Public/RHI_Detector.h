
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RHI_Switcher.h" // For ERHIType
#include "RHI_Detector.generated.h"

/**
 * Blueprint function library for detecting RHI support on the target GPU.
 */
UCLASS()
class RHI_MANAGER_API URHI_Detector : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Checks if the specified RHI is supported by the current GPU. */
    UFUNCTION(BlueprintPure, Category = "RHI Switcher")
    static bool IsRHISupported(ERHIType RHI);

};