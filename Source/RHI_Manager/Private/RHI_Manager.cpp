// Copyright Epic Games, Inc. All Rights Reserved.

#include "RHI_Manager.h"

#define LOCTEXT_NAMESPACE "FRHI_ManagerModule"

void FRHI_ManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FRHI_ManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRHI_ManagerModule, RHI_Manager)