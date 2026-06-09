#!/usr/bin/env bash
set -euo pipefail

# ─────────────────────────────────────────────────────────────────────────────
#  FANTASIA artifact fetcher (Linux/macOS) — main branch
#
#  Downloads the heavy artifacts that don't live in git LFS anymore:
#    - Whisper ASR model            -> Resources/ggml-large-v3-turbo-q5_0.bin
#    - Win64 build-time static libs -> ThirdParty/{aGrUM,grpc,OpenSSL}/...
#    - Microsoft Speech SDK         -> ThirdParty/Microsoft.CognitiveServices.Speech.1.32.1/
#
#  Default with no args: fetch everything. C++ users need the build deps +
#  the Azure SDK. Blueprint-only users get ~500 MB extra on disk but no
#  extra bandwidth (Release assets are not on the LFS quota).
#
#  Usage:
#    bootstrap.sh                  fetch everything
#    bootstrap.sh --runtime-only   skip build deps + Azure SDK
#    bootstrap.sh --model-only     just the Whisper model
#    bootstrap.sh --deps-only      just the build-time static libs
#    bootstrap.sh --azure-only     just the Azure Speech SDK
#    bootstrap.sh --force          re-download even if present
# ─────────────────────────────────────────────────────────────────────────────

RELEASE_TAG="runtime-v2.0"
RELEASE_BASE="https://github.com/antori82/FANTASIA/releases/download/${RELEASE_TAG}"
MODEL_ASSET="whisper-large-v3-turbo-q5_0.bin"
DEPS_ASSET="fantasia-build-deps-win64.tar.gz"
AZURE_ASSET="fantasia-azure-sdk-win64.tar.gz"

FETCH_MODEL=1
FETCH_DEPS=1
FETCH_AZURE=1
FORCE=0
while [ $# -gt 0 ]; do
    case "$1" in
        --runtime-only) FETCH_DEPS=0; FETCH_AZURE=0 ;;
        --model-only)   FETCH_DEPS=0; FETCH_AZURE=0 ;;
        --deps-only)    FETCH_MODEL=0; FETCH_AZURE=0 ;;
        --azure-only)   FETCH_MODEL=0; FETCH_DEPS=0 ;;
        --force)        FORCE=1 ;;
        *) echo "Unknown argument: $1"; echo "Usage: bootstrap.sh [--runtime-only|--model-only|--deps-only|--azure-only] [--force]"; exit 1 ;;
    esac
    shift
done

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
RES_DIR="${SCRIPT_DIR}/Resources"
TP_DIR="${SCRIPT_DIR}/ThirdParty"

mkdir -p "${RES_DIR}" "${TP_DIR}"

command -v curl >/dev/null 2>&1 || { echo "ERROR: curl not found on PATH."; exit 1; }
command -v tar  >/dev/null 2>&1 || { echo "ERROR: tar not found on PATH.";  exit 1; }

# ── Fetch whisper model ──────────────────────────────────────────────────
if [ "${FETCH_MODEL}" = "1" ]; then
    MODEL_PATH="${RES_DIR}/ggml-large-v3-turbo-q5_0.bin"
    SKIP_MODEL=0
    if [ "${FORCE}" = "0" ] && [ -f "${MODEL_PATH}" ]; then
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
        echo "  (~574 MB)"
        if ! curl -L --fail --progress-bar -o "${MODEL_PATH}" "${RELEASE_BASE}/${MODEL_ASSET}"; then
            echo "ERROR: failed to download ${MODEL_ASSET}."
            rm -f "${MODEL_PATH}"
            exit 1
        fi
        echo "Model downloaded to ${MODEL_PATH}"
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

# ── Fetch Azure Speech SDK ───────────────────────────────────────────────
if [ "${FETCH_AZURE}" = "1" ]; then
    AZURE_MARKER="${TP_DIR}/Microsoft.CognitiveServices.Speech.1.32.1/build/native/x64/Release/Microsoft.CognitiveServices.Speech.core.lib"
    SKIP_AZURE=0
    if [ "${FORCE}" = "0" ] && [ -f "${AZURE_MARKER}" ]; then
        echo "Azure Speech SDK already present under ${TP_DIR} (skipping)."
        SKIP_AZURE=1
    fi
    if [ "${SKIP_AZURE}" = "0" ]; then
        AZURE_TGZ="$(mktemp -t fantasia-azure.XXXXXX.tar.gz)"
        echo
        echo "Downloading Azure Speech SDK ${AZURE_ASSET} from ${RELEASE_TAG} ..."
        echo "  (~160 MB compressed, expands to ~170 MB)"
        if ! curl -L --fail --progress-bar -o "${AZURE_TGZ}" "${RELEASE_BASE}/${AZURE_ASSET}"; then
            echo "ERROR: failed to download ${AZURE_ASSET}."
            rm -f "${AZURE_TGZ}"
            exit 1
        fi
        echo "Extracting into ${SCRIPT_DIR} ..."
        tar -xf "${AZURE_TGZ}" -C "${SCRIPT_DIR}"
        rm -f "${AZURE_TGZ}"
        echo "Azure Speech SDK staged under ${TP_DIR}"
    fi
fi

echo
echo "─────────────────────────────────────────────────"
echo " Bootstrap complete."
echo "─────────────────────────────────────────────────"
echo " Plugin is ready to load. Whisper, Azure ASR/TTS,"
echo " and AWS Polly components all work out of the box."
