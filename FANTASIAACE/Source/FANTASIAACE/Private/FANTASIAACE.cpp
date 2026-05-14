#include "FANTASIAACE.h"

#define LOCTEXT_NAMESPACE "FFANTASIAACEModule"

void FFANTASIAACEModule::StartupModule()
{
    UE_LOG(LogTemp, Log, TEXT("FANTASIA-ACE: module started (UACERESTTTSComponent available)."));
}

void FFANTASIAACEModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFANTASIAACEModule, FANTASIAACE)
