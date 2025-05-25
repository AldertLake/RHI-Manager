/************************************************************************************
 *                                                                                  *
 * Copyright (c) 2025 AldertLake. All Rights Reserved.                              *
 * GitHub: https://github.com/AldertLake/Windows-Native-Toolkit                     *
 *                                                                                  *
 ************************************************************************************/

#include "RHI_Detector.h"
#include "HAL/PlatformMisc.h"     
#include "RHI.h"                  
#include "Kismet/GameplayStatics.h" 

bool URHI_Detector::IsRHISupported(ERHIType RHI)
{
    FString PlatformName = UGameplayStatics::GetPlatformName();
    if (PlatformName != TEXT("Windows"))
    {
        return false; 
    }

    switch (RHI)
    {
    case ERHIType::DirectX11:
    {

        return GMaxRHIFeatureLevel >= ERHIFeatureLevel::SM5;
    }
    case ERHIType::DirectX12:
    {

        return PLATFORM_WINDOWS && GDynamicRHI != nullptr;
    }
    case ERHIType::Vulkan:
    {

        return PLATFORM_WINDOWS;
    }
    case ERHIType::Default:
    {

        return true;
    }
    default:
        return false; // Unknown RHI
    }
}


FString URHI_Detector::GetGPUName()
{
    FString GPUBrand = FPlatformMisc::GetPrimaryGPUBrand();
    if (!GPUBrand.IsEmpty())
    {
        return GPUBrand; 
    }
    return TEXT("Unknown GPU"); // Fallback if GPU brand is unavailable
}