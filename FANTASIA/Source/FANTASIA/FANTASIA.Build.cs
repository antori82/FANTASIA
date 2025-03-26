// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using EpicGames.Core;
using System;

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


    private void LoadGrpc(ReadOnlyTargetRules Target, string ThirdPartyPath)
    {
        string EngineThirdPartyPath = Path.Combine(ModuleDirectory, "../../ThirdParty/");
        // Use UE third-party library
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "OpenSSL",
            "zlib"
        });

        System.Console.WriteLine("Platform={0}, Architecture={1}", Target.Platform.ToString(), Target.Architecture);

        string[] libraryPaths = Directory.GetFiles(Path.Combine(Path.Combine(EngineThirdPartyPath, "OpenSSL", "1.1.1t", "lib"), "Win64", "VS2015", "Release"), "*.lib");
        PublicAdditionalLibraries.AddRange(libraryPaths);
        PublicIncludePaths.Add(Path.Combine(Path.Combine(EngineThirdPartyPath, "OpenSSL", "1.1.1t", "include"), "Win64", "VS2015"));

        libraryPaths = Directory.GetFiles(Path.Combine(ThirdPartyPath, "grpc", "lib", "win64", "Release"), "*.lib");
        PublicAdditionalLibraries.AddRange(libraryPaths);

        // gRPC include
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "grpc", "include"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "grpc", "protobuf", "src"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "grpc", "abseil-cpp"));

        // gRPC define
        PublicDefinitions.Add("GOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0");
        PublicDefinitions.Add("GPR_FORBID_UNREACHABLE_CODE=0");

        PublicDefinitions.Add("WITH_GRPC_BINDING=1");
    }

    public void InitialUeConfig()//Config for  UE usage
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnableExceptions = true;
    }

    public void DependeciesAndPaths()//Standard dipendencies and paths, if needed
    {

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
                "Core",
                "Projects"
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
                "HTTP",
                "UnrealEd"
				// ... add private dependencies that you statically link with here ...	
			}
            );
    }
    //TODO better include paths maybe with loops
    public void MicrosoftLibs(string ThirdParty)//Microsoft Libraries Paths
    {
        string LibraryPath = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "x64", "Release");
        string IncludePath1 = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "include", "cxx_api");
        string IncludePath2 = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "include", "c_api");
        //...include other Libraries from Microsoft

        PublicAdditionalLibraries.Add(LibraryPath + "/Microsoft.CognitiveServices.Speech.core.lib");
        PublicIncludePaths.AddRange(new string[] { IncludePath1, IncludePath2 });
    }
    //TODO better include paths maybe with loops
    public void AWSLibs(string ThirdParty)//Amazon Libraries Paths
    {
        string IncludePath3 = Path.Combine(ThirdParty, "AWS", "Core");
        string IncludePath4 = Path.Combine(ThirdParty, "AWS", "Polly");
        string IncludePath5 = Path.Combine(ThirdParty, "AWS", "TTS");
        string LibraryPath = Path.Combine(ThirdParty, "AWS", "lib");
        //...include other Libraries from Amazon

        PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-core.lib");
        PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-polly.lib");
        PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-text-to-speech.lib");
        PublicIncludePaths.AddRange(new string[] {IncludePath3, IncludePath4, IncludePath5 });
    }

    public void DllLoad(string Redist)
    {
        foreach (string dllFile in Directory.GetFiles(Redist, "*"))
        {
            string destPath = Path.Combine("$(PluginDir)", "Binaries", "Win64", Path.GetFileName(dllFile));
            RuntimeDependencies.Add(destPath, dllFile);
        }
    }

    public void PrologLibs(string ThirdParty)//Prolog libraries
    {
        string PrologDllPath = Path.Combine(ThirdParty, "SWIProlog", "PrologDlls");
        string PrologCpp = Path.Combine(ThirdParty, "SWIProlog", "libs");
        

        PublicAdditionalLibraries.Add(PrologCpp + "/libswipl.dll.a");
        PublicAdditionalLibraries.Add(PrologCpp + "/libswipl.lib");

        PublicIncludePaths.Add(Path.Combine(ThirdParty, "SWIProlog", "headers"));

        RuntimeDependencies.Add(Path.Combine(PrologCpp, "/libswipl.dll"));

        foreach (string dllFile in Directory.GetFiles(PrologDllPath, "*"))
        {
            string destPath = Path.Combine("$(PluginDir)", "Binaries", "Win64", Path.GetFileName(dllFile));
            RuntimeDependencies.Add(destPath, dllFile);
        }
    }


    public FANTASIA(ReadOnlyTargetRules Target) : base(Target)
    {
        InitialUeConfig();
        
        DependeciesAndPaths();

        string ModulePath = ModuleDirectory;
        string ThirdParty = Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/"));//directs path to Third Party folder

        MicrosoftLibs(ThirdParty);

        AWSLibs(ThirdParty);

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
        string Redist = Path.Combine(ThirdParty, "Redist");

        DllLoad(Redist);

        PrologLibs(ThirdParty);

        CppStandard = CppStandardVersion.Cpp20;

        LoadAgrum(Target, ThirdParty);
        LoadGrpc(Target, ThirdParty);

        PublicIncludePaths.Add(Path.Combine(ThirdParty, "kdepp"));//kdepp

        DynamicallyLoadedModuleNames.AddRange(
        new string[]
        {
			// ... add any modules that your module loads dynamically here ...
		}
        );
    }
}