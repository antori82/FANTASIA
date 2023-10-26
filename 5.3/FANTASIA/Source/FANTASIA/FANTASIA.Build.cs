// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class FANTASIA : ModuleRules
{
	public bool LoadAgrum(ReadOnlyTargetRules Target, string ThirdPartyPath)
		{
			bool isLibrarySupported = false;

			if ((Target.Platform == UnrealTargetPlatform.Win64))
			{
				isLibrarySupported = true;

				//string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";
				string LibrariesPath = Path.Combine(ThirdPartyPath, "aGrUM", "Libraries");

				/*
				test your path with:
				using System; // Console.WriteLine("");
				Console.WriteLine("... LibrariesPath -> " + LibrariesPath);
				*/

				PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "aGrUM.x64.lib"));
			}

			if (isLibrarySupported)
			{
				// Include path
				PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "aGrUM", "Includes"));
				PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "nlohmann"));
			}

			PublicDefinitions.Add(string.Format("WITH_AGRUM_BINDING={0}", isLibrarySupported ? 1 : 0));

			return isLibrarySupported;
		}
		
	public FANTASIA(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableExceptions = true;

        PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
				// ... add other public dependencies that you statically link with here ...
			}
			);


        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Voice",
				"Json",
				"JsonUtilities",
                "HTTP"
				// ... add private dependencies that you statically link with here ...	
			}
			);

        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"UnrealEd",
					"AssetTools"
				}
			);
        }


        string ModulePath = ModuleDirectory;
		string ThirdParty = Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/"));

		string LibraryPath = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "x64", "Release");
		string IncludePath1 = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "include", "cxx_api");
		string IncludePath2 = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "include", "c_api");

		PublicAdditionalLibraries.Add(LibraryPath + "/Microsoft.CognitiveServices.Speech.core.lib");
		
		string IncludePath3 = Path.Combine(ThirdParty, "AWS", "Core");
		string IncludePath4 = Path.Combine(ThirdParty, "AWS", "Polly");
		string IncludePath5 = Path.Combine(ThirdParty, "AWS", "TTS");

		LibraryPath = Path.Combine(ThirdParty, "AWS", "lib");
		PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-core.lib");
		PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-polly.lib");
		PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-text-to-speech.lib");

		PublicIncludePaths.AddRange(new string[] { IncludePath1, IncludePath2, IncludePath3, IncludePath4, IncludePath5 });

		string Redist = Path.Combine(ThirdParty, "Redist");

        RuntimeDependencies.Add(Path.Combine(Redist, "aws-c-common.dll"));
		RuntimeDependencies.Add(Path.Combine(Redist, "aws-c-event-stream.dll"));
		RuntimeDependencies.Add(Path.Combine(Redist, "aws-checksums.dll"));
		RuntimeDependencies.Add(Path.Combine(Redist, "aws-cpp-sdk-core.dll"));
		RuntimeDependencies.Add(Path.Combine(Redist, "aws-cpp-sdk-polly.dll"));
		RuntimeDependencies.Add(Path.Combine(Redist, "aws-cpp-sdk-text-to-speech.dll"));
		RuntimeDependencies.Add(Path.Combine(Redist, "Microsoft.CognitiveServices.Speech.core.dll"));
		RuntimeDependencies.Add(Path.Combine(Redist, "Microsoft.CognitiveServices.Speech.extension.kws.dll"));

		PublicIncludePaths.Add(Path.Combine(ThirdParty, "kdepp"));

		CppStandard = CppStandardVersion.Cpp20;

		LoadAgrum(Target, ThirdParty);

		DynamicallyLoadedModuleNames.AddRange(
		new string[]
		{
			// ... add any modules that your module loads dynamically here ...
		}
		);
	}
}
