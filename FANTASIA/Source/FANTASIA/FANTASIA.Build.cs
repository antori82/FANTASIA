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

            string LibrariesPath = Path.Combine(ThirdPartyPath, "aGrUM", "Libraries");

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
        CStandard = CStandardVersion.C11;

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
                
			}
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Projects",
                "AudioCapture",
                "AudioCaptureCore",
                "AudioMixer",
                "AudioMixerCore",
                "SignalProcessing"
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
                "ACERuntime",
                "ACECore"
            }
            );
    }

    public void MicrosoftLibs(string ThirdParty)
    {
        string LibraryPath = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "x64", "Release");
        string IncludePath1 = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "include", "cxx_api");
        string IncludePath2 = Path.Combine(ThirdParty, "Microsoft.CognitiveServices.Speech.1.32.1", "build", "native", "include", "c_api");

        PublicAdditionalLibraries.Add(LibraryPath + "/Microsoft.CognitiveServices.Speech.core.lib");
        PublicIncludePaths.AddRange(new string[] { IncludePath1, IncludePath2 });
    }

    public void AWSLibs(string ThirdParty)
    {
        string IncludePath3 = Path.Combine(ThirdParty, "AWS", "Core");
        string IncludePath4 = Path.Combine(ThirdParty, "AWS", "Polly");
        string IncludePath5 = Path.Combine(ThirdParty, "AWS", "TTS");
        string LibraryPath = Path.Combine(ThirdParty, "AWS", "lib");

        PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-core.lib");
        PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-polly.lib");
        PublicAdditionalLibraries.Add(LibraryPath + "/aws-cpp-sdk-text-to-speech.lib");
        PublicIncludePaths.AddRange(new string[] { IncludePath3, IncludePath4, IncludePath5 });
    }

    public void DllLoad(string Redist)
    {
        foreach (string dllFile in Directory.GetFiles(Redist, "*"))
        {
            string destPath = Path.Combine("$(PluginDir)", "Binaries", "Win64", Path.GetFileName(dllFile));
            RuntimeDependencies.Add(destPath, dllFile);
        }
    }

    private void LoadWhisper(ReadOnlyTargetRules Target, string ThirdPartyPath)
    {
        string WhisperRoot = Path.GetFullPath(
            Path.Combine(ThirdPartyPath, "whisper_cpp"));

        string StagingDir = Path.Combine(ModuleDirectory, "Private", "whisper_staged");

        // Verify setup
        bool bHasWhisperSource = Directory.Exists(WhisperRoot) &&
            (File.Exists(Path.Combine(WhisperRoot, "include", "whisper.h")) ||
             File.Exists(Path.Combine(WhisperRoot, "whisper.h")));

        int StagedFileCount = 0;
        if (Directory.Exists(StagingDir))
        {
            StagedFileCount = Directory.GetFiles(StagingDir, "*.c").Length +
                Directory.GetFiles(StagingDir, "*.cpp").Length;
        }

        System.Console.WriteLine("[FANTASIA-Whisper] Whisper source: " +
            (bHasWhisperSource ? WhisperRoot : "NOT FOUND"));
        System.Console.WriteLine("[FANTASIA-Whisper] Staged files:   " +
            StagedFileCount + " in " + StagingDir);

        if (!bHasWhisperSource)
        {
            System.Console.WriteLine("[FANTASIA-Whisper] WARNING: whisper.cpp not found in " + WhisperRoot + " — Whisper ASR disabled.");
            return;
        }
        if (StagedFileCount == 0)
        {
            System.Console.WriteLine("[FANTASIA-Whisper] WARNING: No staged files! Run setup_whisper.bat (or .sh) first.");
            return;
        }

        // Include paths
        AddInclude(WhisperRoot);
        AddInclude(Path.Combine(WhisperRoot, "include"));
        AddInclude(Path.Combine(WhisperRoot, "src"));
        AddInclude(Path.Combine(WhisperRoot, "ggml", "include"));
        AddInclude(Path.Combine(WhisperRoot, "ggml", "src"));
        AddInclude(Path.Combine(WhisperRoot, "ggml", "src", "ggml-cpu"));

        string ArchDir = GetArchDir(Target);
        if (ArchDir != null)
            AddInclude(Path.Combine(WhisperRoot, "ggml", "src", "ggml-cpu", "arch", ArchDir));

        AddInclude(StagingDir);

        // Definitions normally set by CMake
        PrivateDefinitions.Add("GGML_VERSION=\"0.0.0\"");
        PrivateDefinitions.Add("GGML_BUILD_NUMBER=0");
        PrivateDefinitions.Add("GGML_BUILD_COMMIT=\"unknown\"");
        PrivateDefinitions.Add("GGML_COMMIT=\"unknown\"");
        PrivateDefinitions.Add("WHISPER_VERSION=\"0.0.0\"");
        PrivateDefinitions.Add("WHISPER_BUILD_NUMBER=0");
        PrivateDefinitions.Add("WHISPER_BUILD_COMMIT=\"unknown\"");
        PrivateDefinitions.Add("WHISPER_COMMIT=\"unknown\"");

        // Enable the CPU backend
        PrivateDefinitions.Add("GGML_USE_CPU");

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PrivateDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
            PrivateDefinitions.Add("NOMINMAX");
            PublicDefinitions.Add("_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS");
        }

        if (Target.Platform == UnrealTargetPlatform.Linux ||
            Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDefinitions.Add("_GNU_SOURCE");
        }
    }

    private void AddInclude(string Dir)
    {
        if (Directory.Exists(Dir))
        {
            PublicIncludePaths.Add(Dir);
            PrivateIncludePaths.Add(Dir);
        }
    }

    private static string GetArchDir(ReadOnlyTargetRules Target)
    {
        if (Target.Platform == UnrealTargetPlatform.Win64 ||
            Target.Platform == UnrealTargetPlatform.Linux)
            return "x86";
        if (Target.Platform == UnrealTargetPlatform.Mac)
            return "arm";
        return null;
    }

    public void PrologLibs(string ThirdParty)
    {
        string PrologDllPath = Path.Combine(ThirdParty, "SWIProlog", "PrologDlls");
        string PrologCpp = Path.Combine(ThirdParty, "SWIProlog", "libs");


        PublicAdditionalLibraries.Add(PrologCpp + "/libswipl.dll.a");
        PublicAdditionalLibraries.Add(PrologCpp + "/libswipl.lib");

        PublicIncludePaths.Add(Path.Combine(ThirdParty, "SWIProlog", "headers"));

        RuntimeDependencies.Add(Path.Combine(PrologCpp, "libswipl.dll"));

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

        #if UE_5_3_OR_LATER
			// Increase to AVX2 OR AVX512 for better performance (if your CPU supports it)
			MinCpuArchX64 = MinimumCpuArchitectureX64.AVX;
        #else
            bUseAVX = true;
        #endif

        PublicDefinitions.Add("_UCRT_LEGACY_INFINITY");

        string ModulePath = ModuleDirectory;
        string ThirdParty = Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/"));

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
        bUseRTTI = false;
        bUseUnity = false;

        LoadAgrum(Target, ThirdParty);
        LoadGrpc(Target, ThirdParty);
        LoadWhisper(Target, ThirdParty);

        PublicIncludePaths.Add(Path.Combine(ThirdParty, "kdepp"));

        DynamicallyLoadedModuleNames.AddRange(
        new string[]
        {
			// ... add any modules that your module loads dynamically here ...
		}
        );
    }
}