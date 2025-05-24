#include "RHI_Switcher.h"
#include "Misc/ConfigCacheIni.h"
#include "Kismet/KismetSystemLibrary.h"

FString URHI_Switcher::GetCurrentRHI()
{
    FString CurrentRHI;

    GConfig->GetString(TEXT("SystemSettings"), TEXT("DefaultRHI"), CurrentRHI, GEngineIni);
    return CurrentRHI.IsEmpty() ? TEXT("Default") : CurrentRHI; 
}

void URHI_Switcher::SetDesiredRHI(FString NewRHI)
{
    GConfig->SetString(TEXT("SystemSettings"), TEXT("DefaultRHI"), *NewRHI, GEngineIni);

    GConfig->Flush(false, GEngineIni);
}

bool URHI_Switcher::IsRelaunchRequired()
{
    FString CurrentRHI = GetCurrentRHI();
    FString DesiredRHI;

    GConfig->GetString(TEXT("SystemSettings"), TEXT("DefaultRHI"), DesiredRHI, GEngineIni);

    return false;

}

void URHI_Switcher::NotifyRelaunchRequired()
{
    if (IsRelaunchRequired())

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