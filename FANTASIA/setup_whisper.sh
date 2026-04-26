#!/usr/bin/env bash
set -euo pipefail
PLUGIN_DIR="$(cd "$(dirname "$0")" && pwd)"
WHISPER_ROOT="${PLUGIN_DIR}/Source/ThirdParty/whisper_cpp"
STAGING_DIR="${PLUGIN_DIR}/Source/FANTASIA/Private/whisper_staged"
REL_PREFIX="../../../ThirdParty/whisper_cpp"

[ -f "${WHISPER_ROOT}/include/whisper.h" ] || [ -f "${WHISPER_ROOT}/whisper.h" ] || { echo "ERROR: whisper.cpp not found."; exit 1; }
mkdir -p "${STAGING_DIR}"; rm -f "${STAGING_DIR}"/*.c "${STAGING_DIR}"/*.cpp 2>/dev/null || true
ARCH="x86"; [[ "$(uname -m)" == arm64 || "$(uname -m)" == aarch64 ]] && ARCH="arm"
COUNT=0
should_skip() {
    local n="$(basename "$1" | tr '[:upper:]' '[:lower:]')"
    case "$n" in main*|test*|bench*|example*|*cuda*|*metal*|*vulkan*|*sycl*|*kompute*|*coreml*|*openvino*|*hip*|*rpc*|*virtgpu*|*zdnn*|*musa*|*amx*) return 0;; esac; return 1
}
write_wrapper() {
    local rel_inc="$1" dest="$2"
    cat > "${STAGING_DIR}/${dest}" <<WRAPPER
// Auto-generated wrapper. Do not edit.
//
// FANTASIA_WITH_CUDA is defined by FANTASIA.Build.cs:
//   1 = prebuilt whisper.cpp CUDA libs are linked. This wrapper MUST compile
//       to an empty translation unit; otherwise we'd produce duplicate
//       symbols at link time alongside the prebuilt libs.
//   0 = no prebuilt libs found, fall back to compiling whisper.cpp sources
//       in-tree via the include below.
#if !FANTASIA_WITH_CUDA
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4456 4457 4458 4459 4244 4267 4800 4756 4100 4127 4189 4706 4702 4310 4305 4242 4389 4554)
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif
#include "${rel_inc}"
#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // !FANTASIA_WITH_CUDA
WRAPPER
    echo "  ${dest}"; COUNT=$((COUNT+1))
}
stage_dir() {
    local sub_dir="$1" prefix="$2" src_dir="${WHISPER_ROOT}/${sub_dir}"
    [ -d "$src_dir" ] || return
    for f in "$src_dir"/*.c "$src_dir"/*.cpp; do [ -f "$f" ] || continue
        should_skip "$f" && continue
        write_wrapper "${REL_PREFIX}/${sub_dir}/$(basename "$f")" "${prefix}_$(basename "$f")"
    done
}
stage_dir "src" "src"
stage_dir "ggml/src" "ggml_src"
stage_dir "ggml/src/ggml-cpu" "ggml_src_ggml-cpu"
stage_dir "ggml/src/ggml-cpu/arch/${ARCH}" "ggml_src_ggml-cpu_arch_${ARCH}"
echo; echo "Staged ${COUNT} files."
[ -f "${STAGING_DIR}/src_whisper.cpp" ] && echo "Setup complete!" || { echo "ERROR"; exit 1; }
