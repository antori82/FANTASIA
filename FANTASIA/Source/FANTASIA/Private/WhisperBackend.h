/**
 * @file WhisperBackend.h
 * @brief Runtime CPU/GPU dispatch for whisper.cpp API calls.
 *
 * FANTASIA needs to support both a CPU build of whisper.cpp (always
 * available, compiled into the FANTASIA module) and an optional CUDA
 * build (loaded at runtime from `fantasia_whisper_cuda.dll` if present).
 * Both DLLs are produced from the same whisper.cpp source revision, so
 * their ABI (whisper_context_params layout, whisper_full_params layout,
 * function calling conventions) is identical.
 *
 * The dispatch works by routing every whisper_* call FANTASIA makes
 * through a global FWhisperApi struct of function pointers. On module
 * load the pointers are initialised to the static-linked CPU symbols;
 * if the user picks GPU and the CUDA DLL loads cleanly, the pointers
 * are replaced with GetProcAddress'd ones from that DLL.
 *
 * Header is module-private (in Private/) so the whisper.h types it
 * references don't leak into the FANTASIA public surface.
 */

#pragma once

#include "CoreMinimal.h"

// We deliberately suppress whisper.cpp warnings here the same way
// WhisperSubsystem.cpp does. Any TU that pulls in whisper.h goes
// through this dance.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4456 4457 4458 4459)
#pragma warning(disable: 4244 4267 4800 4756 4100 4127 4189 4706 4702 4310 4305 4242 4389)
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif
#include "whisper.h"
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

namespace FantasiaWhisper
{
	/**
	 * Function-pointer table for the whisper.cpp API surface FANTASIA
	 * actually uses. Default-initialised at module load to the
	 * static-linked CPU symbols. LoadGpuLibrary() replaces these with
	 * pointers fetched from `fantasia_whisper_cuda.dll`.
	 *
	 * IMPORTANT: signatures must match whisper.h exactly. If you bump
	 * the pinned whisper.cpp version, regenerate both the CPU staged
	 * source AND the CUDA DLL from the same revision so this table's
	 * ABI assumptions hold.
	 */
	struct FApi
	{
		whisper_context_params   (*context_default_params)();
		whisper_context*         (*init_from_file_with_params)(const char*, whisper_context_params);
		void                     (*free)(whisper_context*);
		whisper_full_params      (*full_default_params)(whisper_sampling_strategy);
		int                      (*full)(whisper_context*, whisper_full_params, const float*, int);
		int                      (*full_n_segments)(whisper_context*);
		int64_t                  (*full_get_segment_t0)(whisper_context*, int);
		int64_t                  (*full_get_segment_t1)(whisper_context*, int);
		const char*              (*full_get_segment_text)(whisper_context*, int);
		int                      (*full_n_tokens)(whisper_context*, int);
		float                    (*full_get_token_p)(whisper_context*, int, int);
		int                      (*full_lang_id)(whisper_context*);
		const char*              (*lang_str)(int);
	};

	/** Global dispatch table. Read by every whisper call site in
	 *  FANTASIA. Initialised in the .cpp to the static-linked symbols. */
	extern FApi GApi;

	/**
	 * Attempt to load `fantasia_whisper_cuda.dll` from the FANTASIA
	 * plugin's Binaries/Win64/ folder and rebind every pointer in GApi
	 * to a symbol resolved from that DLL.
	 *
	 * @return true on full success (DLL found, every symbol resolved).
	 *         false if the DLL is missing or any symbol could not be
	 *         resolved. On false, GApi is left pointing at the
	 *         static-linked CPU symbols and the caller should fall back
	 *         to CPU with a warning.
	 *
	 * Idempotent: calling it twice with the DLL already loaded is safe
	 * and returns the cached result.
	 */
	bool LoadGpuLibrary();

	/** Release the GPU library handle (call on module shutdown) and
	 *  reset GApi to the static-linked CPU defaults. */
	void UnloadGpuLibrary();

	/** True if the GPU library has been successfully loaded and is
	 *  currently bound into GApi. */
	bool IsGpuLibraryLoaded();

	/**
	 * Check whether a CUDA whisper DLL is present in the plugin's
	 * Binaries/Win64/ folder, *without* trying to load it. Used by
	 * UWhisperSubsystem::IsGPUSupported() for the static getter.
	 */
	bool IsGpuLibraryAvailable();
}
