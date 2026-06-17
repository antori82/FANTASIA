// Copyright 1998-2026 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class FANTASIAACE : ModuleRules
{
    public FANTASIAACE(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        CppStandard = CppStandardVersion.Cpp20;
        bEnableExceptions = true;
        bUseRTTI = false;
        bUseUnity = false;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "HTTP",
            "FANTASIA",
            "ACERuntime",
            "ACECore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate",
            "SlateCore",
            "Projects",
            "Json"
        });
    }
}
