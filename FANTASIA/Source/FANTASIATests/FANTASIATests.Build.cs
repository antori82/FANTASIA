using UnrealBuildTool;
using System.IO;

public class FANTASIATests : ModuleRules
{
    public FANTASIATests(ReadOnlyTargetRules Target) : base(Target)
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
            "WebSockets",
            "FANTASIA"
        });

        // kdepp header-only library (needed for MathUtilities tests)
        string ThirdParty = Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));
        PublicIncludePaths.Add(Path.Combine(ThirdParty, "kdepp"));
    }
}
