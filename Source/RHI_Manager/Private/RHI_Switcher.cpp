// Copyright (c) 2025 Your Name or Company. All rights reserved.

#include "RHI_Switcher.h"
#include "Misc/ConfigCacheIni.h"        // For GConfig
#include "Kismet/KismetSystemLibrary.h" // For PrintString
#include "Kismet/GameplayStatics.h"     // For UGameplayStatics

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
    else
    {
        UKismetSystemLibrary::PrintString(
            nullptr,
            FString::Printf(TEXT("InitializeRHI: Unsupported platform '%s'. Only Windows is supported."), *PlatformName),
            true,
            true,
            FLinearColor::Red,
            5.0f
        );
        CurrentRHIAtStartup = ERHIType::Default;
        DesiredRHI = ERHIType::Default;
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
    else
    {
        UKismetSystemLibrary::PrintString(
            nullptr,
            FString::Printf(TEXT("SetDesiredRHI: Unsupported platform '%s'. Only Windows is supported."), *PlatformName),
            true,
            true,
            FLinearColor::Red,
            5.0f
        );
    }
}

bool URHI_Switcher::IsRelaunchRequired()
{
    return CurrentRHIAtStartup != DesiredRHI;
}

void URHI_Switcher::NotifyRelaunchRequired()
{
    if (IsRelaunchRequired())
    {
        UKismetSystemLibrary::PrintString(
            nullptr,
            TEXT("Engine restart required to apply RHI changes. Please restart the editor or game."),
            true,
            true,
            FLinearColor::Red,
            5.0f
        );
    }
}

void URHI_Switcher::RestartGame()
{
    if (UWorld* World = GWorld)
    {
        FString CurrentLevelName = World->GetMapName();
        CurrentLevelName.RemoveFromStart(TEXT("UEDPIE_0_")); // Handle PIE prefix
        UGameplayStatics::OpenLevel(World, FName(*CurrentLevelName), true);
        UKismetSystemLibrary::PrintString(
            nullptr,
            TEXT("Restarting game to reload level. Note: Full RHI change requires engine restart."),
            true,
            true,
            FLinearColor::Yellow,
            5.0f
        );
    }
    else
    {
        UKismetSystemLibrary::PrintString(
            nullptr,
            TEXT("RestartGame: No valid World found."),
            true,
            true,
            FLinearColor::Red,
            5.0f
        );
    }
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