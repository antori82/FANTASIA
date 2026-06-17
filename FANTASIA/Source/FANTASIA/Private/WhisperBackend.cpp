/**
 * @file WhisperBackend.cpp
 * @brief Runtime CPU/GPU dispatch implementation.
 */

#include "WhisperBackend.h"

#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "WhisperTypes.h" // LogWhisperASR

namespace FantasiaWhisper
{
	/**
	 * Initialise GApi to the static-linked CPU symbols. These are the
	 * whisper.cpp functions compiled into the FANTASIA module via the
	 * staged source under Private/whisper_staged/ (CPU path) or via the
	 * pinned prebuilt CUDA libs (CUDA path) -- whichever LoadWhisper()
	 * in Build.cs picked at compile time.
	 *
	 * For a Blueprint-only shipped install, FANTASIA always carries the
	 * CPU build statically. The runtime GPU dispatch below targets a
	 * SEPARATE `fantasia_whisper_cuda.dll` dropped into Binaries/Win64/
	 * by the user, so even Blueprint-only users can opt into GPU
	 * without recompiling the plugin.
	 */
	FApi GApi =
	{
		&whisper_context_default_params,
		&whisper_init_from_file_with_params,
		&whisper_free,
		&whisper_full_default_params,
		&whisper_full,
		&whisper_full_n_segments,
		&whisper_full_get_segment_t0,
		&whisper_full_get_segment_t1,
		&whisper_full_get_segment_text,
		&whisper_full_n_tokens,
		&whisper_full_get_token_p,
		&whisper_full_lang_id,
		&whisper_lang_str,
	};

	/** Cached CPU defaults so UnloadGpuLibrary() can restore exactly the
	 *  same pointers GApi started with (no risk of drift if some other
	 *  code touches GApi during the GPU window). */
	static const FApi GCpuDefaults = GApi;

	/** OS-level DLL handle for the loaded CUDA whisper library. nullptr
	 *  if not loaded. We hold this for the lifetime of the module so
	 *  symbol pointers stay valid; UnloadGpuLibrary releases it. */
	static void* GLoadedCudaHandle = nullptr;

	bool IsGpuLibraryLoaded()
	{
		return GLoadedCudaHandle != nullptr;
	}

	/** Locate the FANTASIA plugin's Binaries/Win64/ directory. Falls
	 *  back to the project's Plugins/FANTASIA path if IPluginManager
	 *  can't locate the plugin (shouldn't happen during normal runtime). */
	static FString GetPluginBinariesDir()
	{
		TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("FANTASIA"));
		const FString BaseDir = Plugin.IsValid()
			? Plugin->GetBaseDir()
			: FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("FANTASIA"));
		return FPaths::Combine(BaseDir, TEXT("Binaries"), TEXT("Win64"));
	}

	/** Filename we look for. Kept here so the rest of the codebase
	 *  doesn't hard-code the name. */
	static const TCHAR* const kCudaDllName = TEXT("fantasia_whisper_cuda.dll");

	bool IsGpuLibraryAvailable()
	{
		const FString DllPath = FPaths::Combine(GetPluginBinariesDir(), kCudaDllName);
		return FPaths::FileExists(DllPath);
	}

	bool LoadGpuLibrary()
	{
		// Idempotent: already loaded -> success.
		if (GLoadedCudaHandle != nullptr)
		{
			return true;
		}

		const FString DllPath = FPaths::Combine(GetPluginBinariesDir(), kCudaDllName);
		if (!FPaths::FileExists(DllPath))
		{
			UE_LOG(LogWhisperASR, Warning,
				TEXT("GPU backend requested but %s is not present in %s. Falling back to CPU."),
				kCudaDllName, *GetPluginBinariesDir());
			return false;
		}

		// FPlatformProcess::GetDllHandle is UE's portable LoadLibrary wrapper.
		// It already sets the search path so co-located DLLs (ggml, cudart,
		// cublas) resolve from the same folder.
		void* Handle = FPlatformProcess::GetDllHandle(*DllPath);
		if (!Handle)
		{
			UE_LOG(LogWhisperASR, Warning,
				TEXT("LoadLibrary failed for %s (CUDA runtime missing? wrong CUDA version?). Falling back to CPU."),
				*DllPath);
			return false;
		}

		// Resolve every whisper_* symbol. A miss on any of them is a
		// hard failure -- we don't want to silently call into stale
		// static-linked code for some symbols and the dynamic DLL for
		// others, because the two builds may have diverged subtly.
		FApi Trial;
		auto Get = [Handle](const ANSICHAR* Name) -> void*
		{
			return FPlatformProcess::GetDllExport(Handle, ANSI_TO_TCHAR(Name));
		};

#define WHISPER_BIND(field, sym)                                          \
		do {                                                              \
			void* Sym = Get(sym);                                         \
			if (!Sym)                                                     \
			{                                                             \
				UE_LOG(LogWhisperASR, Warning,                            \
					TEXT("Symbol %s missing from %s. Falling back to CPU."), \
					ANSI_TO_TCHAR(sym), kCudaDllName);                    \
				FPlatformProcess::FreeDllHandle(Handle);                  \
				return false;                                             \
			}                                                             \
			Trial.field = reinterpret_cast<decltype(Trial.field)>(Sym);   \
		} while (0)

		WHISPER_BIND(context_default_params,       "whisper_context_default_params");
		WHISPER_BIND(init_from_file_with_params,   "whisper_init_from_file_with_params");
		WHISPER_BIND(free,                         "whisper_free");
		WHISPER_BIND(full_default_params,          "whisper_full_default_params");
		WHISPER_BIND(full,                         "whisper_full");
		WHISPER_BIND(full_n_segments,              "whisper_full_n_segments");
		WHISPER_BIND(full_get_segment_t0,          "whisper_full_get_segment_t0");
		WHISPER_BIND(full_get_segment_t1,          "whisper_full_get_segment_t1");
		WHISPER_BIND(full_get_segment_text,        "whisper_full_get_segment_text");
		WHISPER_BIND(full_n_tokens,                "whisper_full_n_tokens");
		WHISPER_BIND(full_get_token_p,             "whisper_full_get_token_p");
		WHISPER_BIND(full_lang_id,                 "whisper_full_lang_id");
		WHISPER_BIND(lang_str,                     "whisper_lang_str");
#undef WHISPER_BIND

		// All symbols resolved -- commit the new dispatch table atomically.
		GApi = Trial;
		GLoadedCudaHandle = Handle;

		UE_LOG(LogWhisperASR, Log,
			TEXT("Loaded GPU whisper backend from %s. CUDA inference enabled."),
			*DllPath);
		return true;
	}

	void UnloadGpuLibrary()
	{
		if (GLoadedCudaHandle != nullptr)
		{
			// Restore CPU defaults BEFORE unloading the DLL so any
			// pending callbacks that race the unload (shouldn't happen
			// in practice -- subsystem Deinitialize joins inference --
			// but defensive) land on the safe static-linked symbols
			// rather than freed pages.
			GApi = GCpuDefaults;
			FPlatformProcess::FreeDllHandle(GLoadedCudaHandle);
			GLoadedCudaHandle = nullptr;
			UE_LOG(LogWhisperASR, Log, TEXT("Unloaded GPU whisper backend."));
		}
	}
}
