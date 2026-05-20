#!/usr/bin/env bash
set -euo pipefail

# ─────────────────────────────────────────────────────────────────────────────
#  FANTASIA runtime artifact fetcher (Linux/macOS)
#
#  Downloads the heavy artifacts that don't live in git LFS anymore:
#    - Whisper ASR model -> Resources/ggml-large-v3-turbo-q5_0.bin
#    - Prebuilt GPU whisper stack -> Binaries/Linux/ (libfantasia_whisper_cuda.so + deps)
#
#  Source is the GitHub Release pinned via RELEASE_TAG below. Idempotent:
#  files already present at the expected paths are skipped (size-checked).
#
#  Usage:
#    bootstrap.sh                  fetch model + GPU stack
#    bootstrap.sh --model-only     fetch only the whisper model
#    bootstrap.sh --gpu-only       fetch only the GPU stack
#    bootstrap.sh --force          re-download even if present
# ─────────────────────────────────────────────────────────────────────────────

RELEASE_TAG="runtime-v2.0"
RELEASE_BASE="https://github.com/antori82/FANTASIA/releases/download/${RELEASE_TAG}"
MODEL_ASSET="whisper-large-v3-turbo-q5_0.bin"
GPU_ASSET="fantasia-gpu-cuda13-linux.tar.gz"

FETCH_MODEL=1
FETCH_GPU=1
FORCE=0
while [ $# -gt 0 ]; do
    case "$1" in
        --model-only) FETCH_GPU=0 ;;
        --gpu-only)   FETCH_MODEL=0 ;;
        --force)      FORCE=1 ;;
        *) echo "Unknown argument: $1"; echo "Usage: bootstrap.sh [--model-only|--gpu-only] [--force]"; exit 1 ;;
    esac
    shift
done

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
RES_DIR="${SCRIPT_DIR}/Resources"
BIN_DIR="${SCRIPT_DIR}/Binaries/Linux"

mkdir -p "${RES_DIR}" "${BIN_DIR}"

command -v curl >/dev/null 2>&1 || { echo "ERROR: curl not found on PATH."; exit 1; }
command -v tar  >/dev/null 2>&1 || { echo "ERROR: tar not found on PATH.";  exit 1; }

# ── Fetch whisper model ──────────────────────────────────────────────────
if [ "${FETCH_MODEL}" = "1" ]; then
    MODEL_PATH="${RES_DIR}/ggml-large-v3-turbo-q5_0.bin"
    SKIP_MODEL=0
    if [ "${FORCE}" = "0" ] && [ -f "${MODEL_PATH}" ]; then
        # Size sanity check: the q5_0 model is ~574 MB. Anything below 100 MB
        # is almost certainly a partial/interrupted prior fetch.
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
        echo "  (this is ~574 MB; first run takes a few minutes on a decent link)"
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

echo
echo "─────────────────────────────────────────────────"
echo " Runtime bootstrap complete."
echo "─────────────────────────────────────────────────"
echo " CPU users: nothing else needed; the plugin is ready."
echo " GPU users: set UWhisperSubsystem.Backend = GPU on the"
echo " subsystem and reopen the editor. The runtime dispatcher"
echo " will dlopen libfantasia_whisper_cuda.so automatically."
