#!/usr/bin/env bash
set -euo pipefail

# ─────────────────────────────────────────────────────────────────────────────
#  Build whisper.cpp with CUDA for FANTASIA plugin (Linux)
#  Prerequisites: CUDA Toolkit (12.x+), CMake 3.24+, GCC/Clang
#
#  Modes:
#    (default) / --shared  — produce libfantasia_whisper_cuda.so + dependencies
#                            in FANTASIA/Binaries/Win64/. Plugin's runtime
#                            dispatcher dlopens it when Backend = GPU.
#                            No plugin rebuild required.
#    --static              — produce static libs Build.cs links into the
#                            FANTASIA module. Legacy flow.
#
#  (Yes, Binaries/Win64/ on Linux too — UE uses that path on the editor
#   side regardless of OS for module-local files. RuntimeDependencies
#   relocate as needed.)
# ─────────────────────────────────────────────────────────────────────────────

MODE="shared"
if [ $# -ge 1 ]; then
    case "$1" in
        --shared) MODE="shared" ;;
        --static) MODE="static" ;;
        *)        echo "Unknown mode: $1"; echo "Usage: $0 [--shared|--static]"; exit 1 ;;
    esac
fi

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
WHISPER_DIR="${SCRIPT_DIR}/ThirdParty/whisper_cpp"
BUILD_DIR="${WHISPER_DIR}/build"

# Check CUDA
if [ -z "${CUDA_PATH:-}" ]; then
    if [ -d "/usr/local/cuda" ]; then
        export CUDA_PATH="/usr/local/cuda"
    else
        echo "ERROR: CUDA_PATH not set and /usr/local/cuda not found."
        echo "Install the NVIDIA CUDA Toolkit or set CUDA_PATH."
        exit 1
    fi
fi
echo "CUDA Toolkit: ${CUDA_PATH}"
echo "Mode: ${MODE}"

# Check CMake
command -v cmake >/dev/null 2>&1 || { echo "ERROR: cmake not found in PATH."; exit 1; }

# Check whisper source
[ -f "${WHISPER_DIR}/CMakeLists.txt" ] || { echo "ERROR: whisper.cpp source not found at ${WHISPER_DIR}"; exit 1; }

# ─────────────────────────────────────────────────────────────────────────
# Workaround for whisper.cpp's standalone CMake configure: it always runs
# configure_file on bindings/javascript/package-tmpl.json (top-level
# CMakeLists.txt around line 29). The FANTASIA distribution strips the
# bindings/ directory since nothing here builds JS bindings, so the
# configure step bails out before generating any library targets.
# Materialize an empty stub before invoking cmake — the configured output
# is never consumed by anything we build.
# ─────────────────────────────────────────────────────────────────────────
BINDINGS_JS_DIR="${WHISPER_DIR}/bindings/javascript"
if [ ! -f "${BINDINGS_JS_DIR}/package-tmpl.json" ]; then
    mkdir -p "${BINDINGS_JS_DIR}"
    echo '{}' > "${BINDINGS_JS_DIR}/package-tmpl.json"
    echo "Created stub bindings/javascript/package-tmpl.json to satisfy whisper.cpp configure."
fi

# ── CMake configure ──────────────────────────────────────────────────────
if [ "${MODE}" = "shared" ]; then
    echo
    echo "Configuring whisper.cpp with CUDA, SHARED libraries..."
    CMAKE_SHARED_FLAG="-DBUILD_SHARED_LIBS=ON"
else
    echo
    echo "Configuring whisper.cpp with CUDA, STATIC libraries..."
    CMAKE_SHARED_FLAG="-DBUILD_SHARED_LIBS=OFF"
fi

# Wipe the build tree if mode changed since last invocation.
MODE_STAMP="${BUILD_DIR}/.fantasia_build_mode"
if [ -f "${MODE_STAMP}" ]; then
    LAST_MODE="$(cat "${MODE_STAMP}")"
    if [ "${LAST_MODE}" != "${MODE}" ]; then
        echo "Build mode changed from ${LAST_MODE} to ${MODE} -- wiping ${BUILD_DIR}"
        rm -rf "${BUILD_DIR}"
    fi
fi

cmake -B "${BUILD_DIR}" -S "${WHISPER_DIR}" \
    -DGGML_CUDA=ON \
    -DGGML_CUDA_FA=ON \
    ${CMAKE_SHARED_FLAG} \
    -DWHISPER_BUILD_EXAMPLES=OFF \
    -DWHISPER_BUILD_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON

mkdir -p "${BUILD_DIR}"
echo "${MODE}" > "${MODE_STAMP}"

echo
echo "Building (Release)..."
echo

cmake --build "${BUILD_DIR}" --config Release --parallel "$(nproc)"

# ── Locate CUDA runtime libs ─────────────────────────────────────────────
CUDA_LIB_DIRS=("${CUDA_PATH}/lib64" "${CUDA_PATH}/lib" "${CUDA_PATH}/lib/x86_64-linux-gnu")
CUDA_LIB_DIR=""
for d in "${CUDA_LIB_DIRS[@]}"; do
    if [ -d "$d" ]; then CUDA_LIB_DIR="$d"; break; fi
done

# ── Stage outputs ───────────────────────────────────────────────────────
if [ "${MODE}" = "shared" ]; then
    DST="${SCRIPT_DIR}/Binaries/Linux"
    mkdir -p "${DST}"

    echo
    echo "Staging shared-build artifacts into ${DST} ..."

    # whisper SO -> libfantasia_whisper_cuda.so
    if [ -f "${BUILD_DIR}/src/libwhisper.so" ]; then
        cp -v "${BUILD_DIR}/src/libwhisper.so" "${DST}/libfantasia_whisper_cuda.so"
    elif [ -f "${BUILD_DIR}/libwhisper.so" ]; then
        cp -v "${BUILD_DIR}/libwhisper.so" "${DST}/libfantasia_whisper_cuda.so"
    else
        echo "ERROR: libwhisper.so not found under ${BUILD_DIR}."
        exit 1
    fi

    # ggml family
    find "${BUILD_DIR}" -name "libggml*.so*" -exec cp -v {} "${DST}/" \;

    # CUDA runtime shared libs
    if [ -n "${CUDA_LIB_DIR}" ]; then
        echo
        echo "Copying CUDA runtime libs from ${CUDA_LIB_DIR} ..."
        for pattern in libcudart.so* libcublas.so* libcublasLt.so*; do
            for f in "${CUDA_LIB_DIR}"/${pattern}; do
                [ -f "$f" ] && cp -v "$f" "${DST}/"
            done
        done
    else
        echo "WARNING: CUDA shared libs not found; end users will need CUDA installed."
    fi

    # Defang Build.cs's static-CUDA detection. LoadWhisperPrebuiltCuda in
    # FANTASIA.Build.cs looks for libwhisper.a + libggml-cuda.a at fixed paths
    # and -- if both exist -- links them statically into UnrealEditor-FANTASIA.so.
    # SHARED mode produces .so files instead of .a, so the check usually fails
    # here, but if any *.a stragglers exist from a prior STATIC build that
    # wasn't fully wiped, remove them defensively.
    rm -f "${BUILD_DIR}/src/libwhisper.a" "${BUILD_DIR}/ggml/src/ggml-cuda/libggml-cuda.a" || true

    echo
    echo "─────────────────────────────────────────────────"
    echo " SHARED build complete. Files staged in:"
    echo "   ${DST}"
    echo "─────────────────────────────────────────────────"
    echo " In your project, set UWhisperSubsystem.Backend = GPU"
    echo " before LoadModel. The plugin's runtime dispatcher will"
    echo " dlopen libfantasia_whisper_cuda.so automatically."
    echo " No plugin rebuild needed."
else
    DLL_DIR="${BUILD_DIR}/lib"
    mkdir -p "${DLL_DIR}"

    if [ -n "${CUDA_LIB_DIR}" ]; then
        echo
        echo "Copying CUDA runtime libs into ${DLL_DIR} ..."
        for pattern in libcudart.so* libcublas.so* libcublasLt.so*; do
            for f in "${CUDA_LIB_DIR}"/${pattern}; do
                [ -f "$f" ] && cp -v "$f" "${DLL_DIR}/"
            done
        done
    else
        echo "WARNING: CUDA shared libs not found."
    fi

    echo
    echo "─────────────────────────────────────────────────"
    echo " STATIC build complete. Libraries:"
    echo "─────────────────────────────────────────────────"
    find "${BUILD_DIR}" -name "*.a" -o -name "*.lib" | while read -r f; do
        echo "  $f"
    done
    echo
    echo " CUDA shared libs (for distribution):"
    echo "─────────────────────────────────────────────────"
    ls -lh "${DLL_DIR}"/*.so* 2>/dev/null || echo "  (none)"
    echo
    echo " Now rebuild the UE project — Build.cs will detect and link these libs"
    echo " statically into UnrealEditor-FANTASIA.dll."
fi
