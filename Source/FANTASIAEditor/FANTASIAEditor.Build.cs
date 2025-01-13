// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class FANTASIAEditor : ModuleRules
{
	public FANTASIAEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableExceptions = true;

        PublicIncludePaths.AddRange(
			new string[] {
				"FANTASIAEditor/Public"
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
                "FANTASIAEditor/Private"
            }
            );
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"FANTASIA"
			}
			);


        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "AssetTools"
			}
			);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        CppStandard = CppStandardVersion.Cpp20;

    }
}
