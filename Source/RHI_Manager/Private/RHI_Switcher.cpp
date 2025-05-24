#include "RHI_Switcher.h"
#include "Misc/ConfigCacheIni.h"        // For GConfig
#include "Kismet/KismetSystemLibrary.h" // For PrintString

// Initialize static variables
ERHIType URHI_Switcher::CurrentRHIAtStartup = ERHIType::Default;
ERHIType URHI_Switcher::DesiredRHI = ERHIType::Default;

void URHI_Switcher::InitializeRHI()
{
    FString ConfigRHI;
    // Read the RHI setting from DefaultEngine.ini
    if (GConfig->GetString(TEXT("/Script/Engine.RendererSettings"), TEXT("r.DefaultRHI"), ConfigRHI, GEngineIni))
    {
        CurrentRHIAtStartup = StringToRHIType(ConfigRHI);
    }
    else
    {
        CurrentRHIAtStartup = ERHIType::Default;
    }
    DesiredRHI = CurrentRHIAtStartup; // Sync desired RHI with current at startup
}

ERHIType URHI_Switcher::GetCurrentRHI()
{
    return CurrentRHIAtStartup;
}

void URHI_Switcher::SetDesiredRHI(ERHIType NewRHI)
{
    DesiredRHI = NewRHI;
    FString RHIString = RHITypeToString(NewRHI);
    // Write the new RHI setting to the config file
    GConfig->SetString(TEXT("/Script/Engine.RendererSettings"), TEXT("r.DefaultRHI"), *RHIString, GEngineIni);
    GConfig->Flush(false, GEngineIni); // Save changes immediately
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
            nullptr,                   // World context (nullptr for global)
            TEXT("Relaunch required to apply RHI changes."),
            true,                      // Print to screen
            true,                      // Print to log
            FLinearColor::Red,         // Text color
            5.0f                       // Duration on screen
        );
    }
}

FString URHI_Switcher::RHITypeToString(ERHIType RHI)
{
    switch (RHI)
    {
    case ERHIType::DirectX11: return TEXT("1");
    case ERHIType::DirectX12: return TEXT("2");
    case ERHIType::Vulkan: return TEXT("3");
    default: return TEXT("0"); // Default case
    }
}

ERHIType URHI_Switcher::StringToRHIType(const FString& RHIString)
{
    if (RHIString == TEXT("1")) return ERHIType::DirectX11;
    else if (RHIString == TEXT("2")) return ERHIType::DirectX12;
    else if (RHIString == TEXT("3")) return ERHIType::Vulkan;
    else return ERHIType::Default; // Fallback for invalid or "0"
}