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
                "WebSockets",
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

        bool bHasWhisperSource = Directory.Exists(WhisperRoot) &&
            (File.Exists(Path.Combine(WhisperRoot, "include", "whisper.h")) ||
             File.Exists(Path.Combine(WhisperRoot, "whisper.h")));

        if (!bHasWhisperSource)
        {
            System.Console.WriteLine("[FANTASIA-Whisper] WARNING: whisper.cpp not found — Whisper ASR disabled.");
            return;
        }

        // ── Include paths (needed for both prebuilt and staged builds) ───
        AddInclude(WhisperRoot);
        AddInclude(Path.Combine(WhisperRoot, "include"));
        AddInclude(Path.Combine(WhisperRoot, "src"));
        AddInclude(Path.Combine(WhisperRoot, "ggml", "include"));
        AddInclude(Path.Combine(WhisperRoot, "ggml", "src"));
        AddInclude(Path.Combine(WhisperRoot, "ggml", "src", "ggml-cpu"));
        string ArchDir = GetArchDir(Target);
        if (ArchDir != null)
            AddInclude(Path.Combine(WhisperRoot, "ggml", "src", "ggml-cpu", "arch", ArchDir));

        // ── Check for prebuilt CUDA libraries (from build_whisper_cuda.bat) ──
        string BuildLibDir = Path.Combine(WhisperRoot, "build");
        string WhisperLib = Path.Combine(BuildLibDir, "src", "Release", "whisper.lib");
        string GgmlLib = Path.Combine(BuildLibDir, "ggml", "src", "Release", "ggml.lib");
        string GgmlBaseLib = Path.Combine(BuildLibDir, "ggml", "src", "Release", "ggml-base.lib");
        string GgmlCpuLib = Path.Combine(BuildLibDir, "ggml", "src", "Release", "ggml-cpu.lib");
        string GgmlCudaLib = Path.Combine(BuildLibDir, "ggml", "src", "ggml-cuda", "Release", "ggml-cuda.lib");

        bool bHasPrebuiltCuda = File.Exists(WhisperLib) && File.Exists(GgmlCudaLib);

        if (bHasPrebuiltCuda && Target.Platform == UnrealTargetPlatform.Win64)
        {
            LoadWhisperPrebuiltCuda(BuildLibDir, WhisperLib, GgmlLib, GgmlBaseLib, GgmlCpuLib, GgmlCudaLib);
        }
        else
        {
            LoadWhisperFromStagedSource(Target, WhisperRoot);
        }

        // ── Common platform defines ─────────────────────────────────────
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

        // ── Stage model files for packaging ─────────────────────────────
        string ResourcesDir = Path.GetFullPath(
            Path.Combine(ModuleDirectory, "..", "..", "Resources"));
        if (Directory.Exists(ResourcesDir))
        {
            string[] ModelFiles = Directory.GetFiles(ResourcesDir, "ggml-*.bin");
            foreach (string BinFile in ModelFiles)
            {
                RuntimeDependencies.Add(BinFile, StagedFileType.NonUFS);
            }
            System.Console.WriteLine("[FANTASIA-Whisper] Registered " +
                ModelFiles.Length + " model file(s) from Resources/ for packaging.");
        }
    }

    /// <summary>
    /// Link prebuilt whisper.cpp static libraries with CUDA support.
    /// Produced by build_whisper_cuda.bat.
    /// </summary>
    private void LoadWhisperPrebuiltCuda(
        string BuildLibDir, string WhisperLib, string GgmlLib,
        string GgmlBaseLib, string GgmlCpuLib, string GgmlCudaLib)
    {
        System.Console.WriteLine("[FANTASIA-Whisper] Using PREBUILT libraries with CUDA.");

        // Link whisper + ggml static libs
        PublicAdditionalLibraries.Add(WhisperLib);
        if (File.Exists(GgmlLib))       PublicAdditionalLibraries.Add(GgmlLib);
        if (File.Exists(GgmlBaseLib))   PublicAdditionalLibraries.Add(GgmlBaseLib);
        if (File.Exists(GgmlCpuLib))    PublicAdditionalLibraries.Add(GgmlCpuLib);
        PublicAdditionalLibraries.Add(GgmlCudaLib);

        // Link CUDA toolkit libraries
        string CudaPath = Environment.GetEnvironmentVariable("CUDA_PATH");
        if (string.IsNullOrEmpty(CudaPath))
        {
            System.Console.WriteLine("[FANTASIA-Whisper] WARNING: CUDA_PATH not set! CUDA link may fail.");
        }
        else
        {
            string CudaLibDir = Path.Combine(CudaPath, "lib", "x64");
            System.Console.WriteLine("[FANTASIA-Whisper] CUDA libs: " + CudaLibDir);

            PublicAdditionalLibraries.Add(Path.Combine(CudaLibDir, "cudart_static.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(CudaLibDir, "cublas.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(CudaLibDir, "cublasLt.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(CudaLibDir, "cuda.lib"));
        }

        PublicDefinitions.Add("FANTASIA_WITH_CUDA=1");

        // Ship CUDA runtime DLLs so end users don't need the CUDA Toolkit.
        // build_whisper_cuda.bat copies them into ThirdParty/whisper_cpp/build/bin/.
        string CudaDllDir = Path.Combine(BuildLibDir, "bin");
        if (Directory.Exists(CudaDllDir))
        {
            string[] CudaDlls = Directory.GetFiles(CudaDllDir, "*.dll");
            foreach (string Dll in CudaDlls)
            {
                string DestPath = Path.Combine("$(BinaryOutputDir)", Path.GetFileName(Dll));
                RuntimeDependencies.Add(DestPath, Dll);
            }
            System.Console.WriteLine("[FANTASIA-Whisper] Registered " +
                CudaDlls.Length + " CUDA runtime DLL(s) for shipping.");
        }
        else
        {
            System.Console.WriteLine("[FANTASIA-Whisper] WARNING: No CUDA DLLs found at " +
                CudaDllDir + " — end users will need CUDA Toolkit installed.");
        }

        // When using prebuilt libs, staged source files must not be compiled
        // or we get duplicate symbols. Verify they've been cleared.
        string StagingDir = Path.Combine(ModuleDirectory, "Private", "whisper_staged");
        if (Directory.Exists(StagingDir))
        {
            int StagedCount = Directory.GetFiles(StagingDir, "*.c").Length +
                Directory.GetFiles(StagingDir, "*.cpp").Length;
            if (StagedCount > 0)
            {
                System.Console.WriteLine("[FANTASIA-Whisper] WARNING: whisper_staged/ has " +
                    StagedCount + " files that will conflict with prebuilt libs!");
                System.Console.WriteLine("[FANTASIA-Whisper] Cleaning staged files...");
                foreach (string f in Directory.GetFiles(StagingDir, "*.c")) File.Delete(f);
                foreach (string f in Directory.GetFiles(StagingDir, "*.cpp")) File.Delete(f);
            }
        }
    }

    /// <summary>
    /// Compile whisper.cpp from staged source wrappers (CPU only, no CUDA).
    /// This is the fallback when prebuilt libs are not available.
    /// </summary>
    private void LoadWhisperFromStagedSource(ReadOnlyTargetRules Target, string WhisperRoot)
    {
        string StagingDir = Path.Combine(ModuleDirectory, "Private", "whisper_staged");
        int StagedFileCount = 0;
        if (Directory.Exists(StagingDir))
        {
            StagedFileCount = Directory.GetFiles(StagingDir, "*.c").Length +
                Directory.GetFiles(StagingDir, "*.cpp").Length;
        }

        if (StagedFileCount == 0)
        {
            System.Console.WriteLine("[FANTASIA-Whisper] WARNING: No staged files and no prebuilt libs! Run setup_whisper.bat or build_whisper_cuda.bat.");
            return;
        }

        System.Console.WriteLine("[FANTASIA-Whisper] Using STAGED SOURCE (CPU only, " +
            StagedFileCount + " files).");

        AddInclude(StagingDir);

        // Version defines normally set by CMake
        PrivateDefinitions.Add("GGML_VERSION=\"0.0.0\"");
        PrivateDefinitions.Add("GGML_BUILD_NUMBER=0");
        PrivateDefinitions.Add("GGML_BUILD_COMMIT=\"unknown\"");
        PrivateDefinitions.Add("GGML_COMMIT=\"unknown\"");
        PrivateDefinitions.Add("WHISPER_VERSION=\"0.0.0\"");
        PrivateDefinitions.Add("WHISPER_BUILD_NUMBER=0");
        PrivateDefinitions.Add("WHISPER_BUILD_COMMIT=\"unknown\"");
        PrivateDefinitions.Add("WHISPER_COMMIT=\"unknown\"");

        // CPU backend + SIMD
        PrivateDefinitions.Add("GGML_USE_CPU");
        if (Target.Platform == UnrealTargetPlatform.Win64 ||
            Target.Platform == UnrealTargetPlatform.Linux)
        {
            PrivateDefinitions.Add("GGML_USE_AVX");
            PrivateDefinitions.Add("GGML_USE_AVX2");
            PrivateDefinitions.Add("GGML_USE_FMA");
            PrivateDefinitions.Add("GGML_USE_F16C");
        }
        if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PrivateDefinitions.Add("GGML_USE_ACCELERATE");
        }

        PublicDefinitions.Add("FANTASIA_WITH_CUDA=0");
    }


    private void AddInclude(string Dir)
    {
        if (Directory.Exists(Dir))
        {
            PublicIncludePaths.Add(Dir);
            PrivateIncludePaths.Add(Dir);
        }
    }

    /// <summary>
    /// Returns the ggml SIMD architecture subdirectory name for include paths
    /// (e.g. "x86" for AVX/SSE intrinsics, "arm" for NEON).
    /// </summary>
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
			// AVX2 required for ggml SIMD acceleration (any Intel/AMD CPU from ~2015+)
			MinCpuArchX64 = MinimumCpuArchitectureX64.AVX2;
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