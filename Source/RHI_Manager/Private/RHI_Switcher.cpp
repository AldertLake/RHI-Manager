/************************************************************************************
 *                                                                                  *
 * Copyright (c) 2025 AldertLake. All Rights Reserved.                              *
 * GitHub: https://github.com/AldertLake/Windows-Native-Toolkit                     *
 *                                                                                  *
 ************************************************************************************/

#include "RHI_Switcher.h"
#include "Misc/ConfigCacheIni.h"        
#include "Kismet/GameplayStatics.h"    

// Initialize static variables
ERHIType URHI_Switcher::CurrentRHIAtStartup = ERHIType::Default;
ERHIType URHI_Switcher::DesiredRHI = ERHIType::Default;

void URHI_Switcher::InitializeRHI()
{
    FString ConfigRHI;
    FString PlatformName = UGameplayStatics::GetPlatformName();
    if (PlatformName == TEXT("Windows"))
    {
        if (GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), ConfigRHI, GEngineIni))
        {
            CurrentRHIAtStartup = StringToRHIType(ConfigRHI);
        }
        else
        {
            CurrentRHIAtStartup = ERHIType::Default;
        }
        DesiredRHI = CurrentRHIAtStartup; // Sync at startup
    }
}

ERHIType URHI_Switcher::GetCurrentRHI()
{
    return CurrentRHIAtStartup;
}

void URHI_Switcher::SetDesiredRHI(ERHIType NewRHI)
{
    FString PlatformName = UGameplayStatics::GetPlatformName();
    if (PlatformName == TEXT("Windows"))
    {
        FString NewRHIString = RHITypeToString(NewRHI);
        FString CurrentRHIString;
        GConfig->GetString(TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"), TEXT("DefaultGraphicsRHI"), CurrentRHIString, GEngineIni);

        // Only update if the new RHI is different
        if (CurrentRHIString != NewRHIString)
        {
            GConfig->SetString(
                TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"),
                TEXT("DefaultGraphicsRHI"),
                *NewRHIString,
                GEngineIni
            );
            GConfig->Flush(true, GEngineIni); // Force save to disk
            DesiredRHI = NewRHI; // Update desired RHI
        }
    }
}

bool URHI_Switcher::IsRelaunchRequired()
{
    return CurrentRHIAtStartup != DesiredRHI;
}

FString URHI_Switcher::RHITypeToString(ERHIType RHI)
{
    switch (RHI)
    {
    case ERHIType::DirectX11: return TEXT("DefaultGraphicsRHI_DX11");
    case ERHIType::DirectX12: return TEXT("DefaultGraphicsRHI_DX12");
    case ERHIType::Vulkan: return TEXT("DefaultGraphicsRHI_Vulkan");
    default: return TEXT("DefaultGraphicsRHI_Default");
    }
}

ERHIType URHI_Switcher::StringToRHIType(const FString& RHIString)
{
    if (RHIString == TEXT("DefaultGraphicsRHI_DX11")) return ERHIType::DirectX11;
    else if (RHIString == TEXT("DefaultGraphicsRHI_DX12")) return ERHIType::DirectX12;
    else if (RHIString == TEXT("DefaultGraphicsRHI_Vulkan")) return ERHIType::Vulkan;
    else return ERHIType::Default;
}