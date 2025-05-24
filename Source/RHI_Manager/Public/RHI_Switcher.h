#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RHI_Switcher.generated.h"


UCLASS()
class RHI_MANAGER_API URHI_Switcher : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static FString GetCurrentRHI();

    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void SetDesiredRHI(FString NewRHI);

    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static bool IsRelaunchRequired();

    UFUNCTION(BlueprintCallable, Category = "RHI Switcher")
    static void NotifyRelaunchRequired();
};