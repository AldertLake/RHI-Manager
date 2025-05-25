// Copyright (c) 2025 Your Name or Company. All rights reserved.

#include "RHI_Detector.h"
#include "HAL/PlatformMisc.h"     // For FPlatformMisc
#include "RHI.h"                  // For GDynamicRHI
#include "Kismet/GameplayStatics.h" // For GetPlatformName

bool URHI_Detector::IsRHISupported(ERHIType RHI)
{
    FString PlatformName = UGameplayStatics::GetPlatformName();
    if (PlatformName != TEXT("Windows"))
    {
        return false; // Only Windows is supported
    }

    switch (RHI)
    {
    case ERHIType::DirectX11:
    {
        // DirectX 11 is supported if the feature level is at least SM5
        return GMaxRHIFeatureLevel >= ERHIFeatureLevel::SM5;
    }
    case ERHIType::DirectX12:
    {
        // DirectX 12 requires Windows and modern GPU; assume supported on Windows
        return PLATFORM_WINDOWS && GDynamicRHI != nullptr;
    }
    case ERHIType::Vulkan:
    {
        // Vulkan requires Windows and driver support; assume supported on Windows
        return PLATFORM_WINDOWS;
    }
    case ERHIType::Default:
    {
        // Default RHI (typically DirectX 11) is assumed supported
        return true;
    }
    default:
        return false; // Unknown RHI
    }
}