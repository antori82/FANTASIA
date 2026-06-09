#!/usr/bin/env bash
set -euo pipefail

# ─────────────────────────────────────────────────────────────────────────────
#  FANTASIA artifact fetcher (Linux/macOS)
#
#  Downloads the heavy artifacts that don't live in git LFS anymore:
#    - Whisper ASR model            -> Resources/ggml-large-v3-turbo-q5_0.bin
#    - Prebuilt GPU whisper stack   -> Binaries/Linux/ (libfantasia_whisper_cuda.so + deps)
#    - Win64 build-time static libs -> ThirdParty/{aGrUM,grpc,OpenSSL}/...
#       (Win64 only at the moment; Linux build deps build from source via UE)
#
#  Default with no args: fetch everything. C++ users need the build deps;
#  Blueprint-only users get an extra ~330 MB on disk but no extra bandwidth
#  (it's a Release asset, not LFS).
#
#  Usage:
#    bootstrap.sh                  fetch everything (recommended)
#    bootstrap.sh --runtime-only   skip build deps
#    bootstrap.sh --model-only     just the Whisper model
#    bootstrap.sh --gpu-only       just the GPU stack
#    bootstrap.sh --deps-only      just the build-time static libs
#    bootstrap.sh --force          re-download even if present
# ─────────────────────────────────────────────────────────────────────────────

RELEASE_TAG="runtime-v2.0"
RELEASE_BASE="https://github.com/antori82/FANTASIA/releases/download/${RELEASE_TAG}"
MODEL_ASSET="whisper-large-v3-turbo-q5_0.bin"
GPU_ASSET="fantasia-gpu-cuda13-linux.tar.gz"
DEPS_ASSET="fantasia-build-deps-win64.tar.gz"

FETCH_MODEL=1
FETCH_GPU=1
FETCH_DEPS=1
FORCE=0
while [ $# -gt 0 ]; do
    case "$1" in
        --runtime-only) FETCH_DEPS=0 ;;
        --model-only)   FETCH_GPU=0; FETCH_DEPS=0 ;;
        --gpu-only)     FETCH_MODEL=0; FETCH_DEPS=0 ;;
        --deps-only)    FETCH_MODEL=0; FETCH_GPU=0 ;;
        --force)        FORCE=1 ;;
        *) echo "Unknown argument: $1"; echo "Usage: bootstrap.sh [--runtime-only|--model-only|--gpu-only|--deps-only] [--force]"; exit 1 ;;
    esac
    shift
done

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
RES_DIR="${SCRIPT_DIR}/Resources"
BIN_DIR="${SCRIPT_DIR}/Binaries/Linux"
TP_DIR="${SCRIPT_DIR}/ThirdParty"

mkdir -p "${RES_DIR}" "${BIN_DIR}" "${TP_DIR}"

command -v curl >/dev/null 2>&1 || { echo "ERROR: curl not found on PATH."; exit 1; }
command -v tar  >/dev/null 2>&1 || { echo "ERROR: tar not found on PATH.";  exit 1; }

# ── Fetch whisper model ──────────────────────────────────────────────────
if [ "${FETCH_MODEL}" = "1" ]; then
    MODEL_PATH="${RES_DIR}/ggml-large-v3-turbo-q5_0.bin"
    SKIP_MODEL=0
    if [ "${FORCE}" = "0" ] && [ -f "${MODEL_PATH}" ]; then
        # Size sanity check: the q5_0 model is ~574 MB.
        MODEL_SIZE=$(stat -c%s "${MODEL_PATH}" 2>/dev/null || stat -f%z "${MODEL_PATH}")
        if [ "${MODEL_SIZE}" -gt 104857600 ]; then
            echo "Whisper model already present at ${MODEL_PATH} (skipping)."
            SKIP_MODEL=1
        else
            echo "Existing model at ${MODEL_PATH} looks incomplete (${MODEL_SIZE} bytes); re-downloading."
        fi
    fi
    if [ "${SKIP_MODEL}" = "0" ]; then
        echo
        echo "Downloading whisper model ${MODEL_ASSET} from ${RELEASE_TAG} ..."
        echo "  (this is ~574 MB)"
        if ! curl -L --fail --progress-bar -o "${MODEL_PATH}" "${RELEASE_BASE}/${MODEL_ASSET}"; then
            echo "ERROR: failed to download ${MODEL_ASSET}."
            rm -f "${MODEL_PATH}"
            exit 1
        fi
        echo "Model downloaded to ${MODEL_PATH}"
    fi
fi

# ── Fetch GPU stack ──────────────────────────────────────────────────────
if [ "${FETCH_GPU}" = "1" ]; then
    GPU_MARKER="${BIN_DIR}/libfantasia_whisper_cuda.so"
    SKIP_GPU=0
    if [ "${FORCE}" = "0" ] && [ -f "${GPU_MARKER}" ]; then
        echo "GPU stack already present at ${BIN_DIR} (skipping)."
        SKIP_GPU=1
    fi
    if [ "${SKIP_GPU}" = "0" ]; then
        GPU_TGZ="$(mktemp -t fantasia-gpu.XXXXXX.tar.gz)"
        echo
        echo "Downloading GPU whisper stack ${GPU_ASSET} from ${RELEASE_TAG} ..."
        echo "  (this is ~540 MB)"
        if ! curl -L --fail --progress-bar -o "${GPU_TGZ}" "${RELEASE_BASE}/${GPU_ASSET}"; then
            echo "ERROR: failed to download ${GPU_ASSET}."
            rm -f "${GPU_TGZ}"
            exit 1
        fi
        echo "Extracting into ${BIN_DIR} ..."
        tar -xf "${GPU_TGZ}" -C "${BIN_DIR}"
        rm -f "${GPU_TGZ}"
        echo "GPU stack staged in ${BIN_DIR}"
    fi
fi

# ── Fetch build-time static libs ─────────────────────────────────────────
if [ "${FETCH_DEPS}" = "1" ]; then
    DEPS_MARKER="${TP_DIR}/aGrUM/Libraries/agrum.x64.lib"
    SKIP_DEPS=0
    if [ "${FORCE}" = "0" ] && [ -f "${DEPS_MARKER}" ]; then
        echo "Build-time static libs already present under ${TP_DIR} (skipping)."
        SKIP_DEPS=1
    fi
    if [ "${SKIP_DEPS}" = "0" ]; then
        DEPS_TGZ="$(mktemp -t fantasia-deps.XXXXXX.tar.gz)"
        echo
        echo "Downloading Win64 build deps ${DEPS_ASSET} from ${RELEASE_TAG} ..."
        echo "  (~60 MB compressed, expands to ~330 MB)"
        if ! curl -L --fail --progress-bar -o "${DEPS_TGZ}" "${RELEASE_BASE}/${DEPS_ASSET}"; then
            echo "ERROR: failed to download ${DEPS_ASSET}."
            rm -f "${DEPS_TGZ}"
            exit 1
        fi
        echo "Extracting into ${SCRIPT_DIR} ..."
        tar -xf "${DEPS_TGZ}" -C "${SCRIPT_DIR}"
        rm -f "${DEPS_TGZ}"
        echo "Build deps staged under ${TP_DIR}"
    fi
fi

echo
echo "─────────────────────────────────────────────────"
echo " Bootstrap complete."
echo "─────────────────────────────────────────────────"
echo " CPU users: nothing else needed; the plugin is ready."
echo " GPU users: set UWhisperSubsystem.Backend = GPU on the"
echo " subsystem and reopen the editor. The runtime dispatcher"
echo " will dlopen libfantasia_whisper_cuda.so automatically."
