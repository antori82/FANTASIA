#!/usr/bin/env bash
set -euo pipefail

# ─────────────────────────────────────────────────────────────────────────────
#  Build whisper.cpp with CUDA as static libraries for FANTASIA plugin (Linux)
#  Prerequisites: CUDA Toolkit (12.x+), CMake 3.24+, GCC/Clang
# ─────────────────────────────────────────────────────────────────────────────

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
WHISPER_DIR="${SCRIPT_DIR}/ThirdParty/whisper_cpp"
BUILD_DIR="${WHISPER_DIR}/build"

# Check CUDA
if [ -z "${CUDA_PATH:-}" ]; then
    # Try common Linux install paths
    if [ -d "/usr/local/cuda" ]; then
        export CUDA_PATH="/usr/local/cuda"
    else
        echo "ERROR: CUDA_PATH not set and /usr/local/cuda not found."
        echo "Install the NVIDIA CUDA Toolkit or set CUDA_PATH."
        exit 1
    fi
fi
echo "CUDA Toolkit: ${CUDA_PATH}"

# Check CMake
command -v cmake >/dev/null 2>&1 || { echo "ERROR: cmake not found in PATH."; exit 1; }

# Check whisper source
[ -f "${WHISPER_DIR}/CMakeLists.txt" ] || { echo "ERROR: whisper.cpp source not found at ${WHISPER_DIR}"; exit 1; }

echo
echo "Configuring whisper.cpp with CUDA..."
echo

cmake -B "${BUILD_DIR}" -S "${WHISPER_DIR}" \
    -DGGML_CUDA=ON \
    -DGGML_CUDA_FA=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DWHISPER_BUILD_EXAMPLES=OFF \
    -DWHISPER_BUILD_TESTS=OFF \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON

echo
echo "Building (Release)..."
echo

cmake --build "${BUILD_DIR}" --config Release --parallel "$(nproc)"

# ── Copy CUDA runtime shared libs so end users don't need the toolkit ──
echo
echo "Copying CUDA runtime libraries for distribution..."

DLL_DIR="${BUILD_DIR}/lib"
mkdir -p "${DLL_DIR}"

CUDA_LIB_DIRS=("${CUDA_PATH}/lib64" "${CUDA_PATH}/lib" "${CUDA_PATH}/lib/x86_64-linux-gnu")
CUDA_LIB_DIR=""
for d in "${CUDA_LIB_DIRS[@]}"; do
    if [ -d "$d" ]; then
        CUDA_LIB_DIR="$d"
        break
    fi
done

if [ -n "${CUDA_LIB_DIR}" ]; then
    for pattern in libcudart.so* libcublas.so* libcublasLt.so*; do
        for f in "${CUDA_LIB_DIR}"/${pattern}; do
            [ -f "$f" ] || continue
            cp -v "$f" "${DLL_DIR}/"
        done
    done
else
    echo "WARNING: Could not find CUDA shared libraries."
fi

echo
echo "─────────────────────────────────────────────────"
echo " Build complete. Libraries:"
echo "─────────────────────────────────────────────────"

find "${BUILD_DIR}" -name "*.a" -o -name "*.lib" | while read -r f; do
    echo "  $f"
done

echo
echo " CUDA shared libs (for distribution):"
echo "─────────────────────────────────────────────────"
ls -lh "${DLL_DIR}"/*.so* 2>/dev/null || echo "  (none)"

echo
echo "Now rebuild the UE project — Build.cs will detect and link these libs."
echo "CUDA shared libs will be shipped alongside the binary automatically."
