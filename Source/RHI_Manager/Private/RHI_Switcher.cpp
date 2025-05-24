#include "RHI_Switcher.h"
#include "Misc/ConfigCacheIni.h"        // For GConfig
#include "Kismet/KismetSystemLibrary.h" // For PrintString

// Initialize static variables
ERHIType URHI_Switcher::CurrentRHIAtStartup = ERHIType::Default;
ERHIType URHI_Switcher::DesiredRHI = ERHIType::Default;

void URHI_Switcher::InitializeRHI()
{
    FString ConfigRHI;
    // Read the RHI setting from the config file
    GConfig->GetString(TEXT("SystemSettings"), TEXT("DefaultRHI"), ConfigRHI, GEngineIni);
    // Convert the config string to our enum and set initial values
    CurrentRHIAtStartup = StringToRHIType(ConfigRHI);
    DesiredRHI = CurrentRHIAtStartup;
}

ERHIType URHI_Switcher::GetCurrentRHI()
{
    // Return the RHI the engine is currently using
    return CurrentRHIAtStartup;
}

void URHI_Switcher::SetDesiredRHI(ERHIType NewRHI)
{
    // Set the desired RHI and write it to the config for the next launch
    DesiredRHI = NewRHI;
    FString RHIString = RHITypeToString(NewRHI);
    GConfig->SetString(TEXT("SystemSettings"), TEXT("DefaultRHI"), *RHIString, GEngineIni);
    GConfig->Flush(false, GEngineIni); // Save changes to the config file
}

bool URHI_Switcher::IsRelaunchRequired()
{
    // Check if the desired RHI differs from the current one
    return CurrentRHIAtStartup != DesiredRHI;
}

void URHI_Switcher::NotifyRelaunchRequired()
{
    if (IsRelaunchRequired())
    {
        // Show a message if a relaunch is needed
        UKismetSystemLibrary::PrintString(
            nullptr,
            TEXT("Relaunch required to apply RHI changes."),
            true,
            true,
            FLinearColor::Red,
            5.0f
        );
    }
}

FString URHI_Switcher::RHITypeToString(ERHIType RHI)
{
    // Convert enum to string for config file
    switch (RHI)
    {
    case ERHIType::DirectX11: return TEXT("D3D11");
    case ERHIType::DirectX12: return TEXT("D3D12");
    case ERHIType::Vulkan: return TEXT("Vulkan");
    case ERHIType::Default: return TEXT("Default");
    default: return TEXT("Default");
    }
}

ERHIType URHI_Switcher::StringToRHIType(const FString& RHIString)
{
    // Convert config string to enum, defaulting to Default if unrecognized
    FString LowerCaseString = RHIString.ToLower();
    if (LowerCaseString == TEXT("d3d11")) return ERHIType::DirectX11;
    else if (LowerCaseString == TEXT("d3d12")) return ERHIType::DirectX12;
    else if (LowerCaseString == TEXT("vulkan")) return ERHIType::Vulkan;
    else return ERHIType::Default;
}