#include "RHI_Switcher.h"
#include "Misc/ConfigCacheIni.h"
#include "Kismet/KismetSystemLibrary.h"

// Initialize static variables
ERHIType URHI_Switcher::CurrentRHIAtStartup = ERHIType::Default;
ERHIType URHI_Switcher::DesiredRHI = ERHIType::Default;

void URHI_Switcher::InitializeRHI()
{
    FString CurrentRHIString = GetCurrentRHI();
    CurrentRHIAtStartup = StringToRHIType(CurrentRHIString);
    DesiredRHI = CurrentRHIAtStartup;
}

FString URHI_Switcher::GetCurrentRHI()
{
    FString CurrentRHIString;
    GConfig->GetString(TEXT("SystemSettings"), TEXT("DefaultRHI"), CurrentRHIString, GEngineIni);

    // Return the raw string from the config, defaulting to "Default" if not set
    if (CurrentRHIString.IsEmpty())
    {
        return TEXT("Default");
    }
    return CurrentRHIString;
}

void URHI_Switcher::SetDesiredRHI(FString NewRHI)
{
    // Normalize the input string for consistency
    NewRHI = NewRHI.TrimStartAndEnd().ToLower();

    // Convert the string to ERHIType to validate and store internally
    ERHIType NewRHIType = StringToRHIType(NewRHI);

    // Write the string to the config as-is (after validation via enum conversion)
    GConfig->SetString(TEXT("SystemSettings"), TEXT("DefaultRHI"), *NewRHI, GEngineIni);
    GConfig->Flush(false, GEngineIni);

    // Update the desired RHI enum
    DesiredRHI = NewRHIType;
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
            TEXT("Relaunch required to apply RHI changes."),
            true,
            true,
            FLinearColor::Red,
            5.0f
        );
    }
}

ERHIType URHI_Switcher::StringToRHIType(const FString& RHIString)
{
    FString NormalizedString = RHIString.TrimStartAndEnd().ToLower();

    if (NormalizedString == TEXT("d3d11"))
    {
        return ERHIType::DirectX11;
    }
    else if (NormalizedString == TEXT("d3d12"))
    {
        return ERHIType::DirectX12;
    }
    else if (NormalizedString == TEXT("vulkan"))
    {
        return ERHIType::Vulkan;
    }
    else
    {
        return ERHIType::Default;
    }
}