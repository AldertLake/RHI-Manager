/************************************************************************************
 *                                                                                  *
 * Copyright (c) 2025 AldertLake. All Rights Reserved.                              *
 * GitHub: https://github.com/AldertLake/Windows-Native-Toolkit                     *
 *                                                                                  *
 ************************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RHI_Switcher.generated.h"


UENUM(BlueprintType)
enum class ERHIType : uint8
{
    Default UMETA(DisplayName = "Default"),
    DirectX11 UMETA(DisplayName = "DirectX 11"),
    DirectX12 UMETA(DisplayName = "DirectX 12"),
    Vulkan UMETA(DisplayName = "Vulkan")
};


UCLASS()
class RHI_MANAGER_API URHI_Switcher : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void InitializeRHI();

    UFUNCTION(BlueprintPure, Category = "RHI Switcher")
    static ERHIType GetCurrentRHI();

    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void SetDesiredRHI(ERHIType NewRHI);

    UFUNCTION(BlueprintPure, Category = "RHI Switcher")
    static bool IsRelaunchRequired();

private:
    static ERHIType CurrentRHIAtStartup;
    static ERHIType DesiredRHI;         
    static FString RHITypeToString(ERHIType RHI);
    static ERHIType StringToRHIType(const FString& RHIString);
};