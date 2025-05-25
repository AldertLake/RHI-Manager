/************************************************************************************
 *                                                                                  *
 * Copyright (c) 2025 AldertLake. All Rights Reserved.                              *
 * GitHub: https://github.com/AldertLake/Windows-Native-Toolkit                     *
 *                                                                                  *
 ************************************************************************************/


#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RHI_Switcher.h"
#include "RHI_Detector.generated.h"


UCLASS()
class RHI_MANAGER_API URHI_Detector : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure, Category = "RHI Switcher")
    static bool IsRHISupported(ERHIType RHI);

    UFUNCTION(BlueprintPure, Category = "RHI Switcher")
    static FString GetGPUName();

};