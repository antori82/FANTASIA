@echo off
setlocal EnableDelayedExpansion

REM ─────────────────────────────────────────────────────────────────────────────
REM  FANTASIA runtime artifact fetcher (Windows)
REM
REM  Downloads the heavy artifacts that don't live in git LFS anymore:
REM    - Whisper ASR model -> Resources/ggml-large-v3-turbo-q5_0.bin
REM    - Prebuilt GPU whisper stack -> Binaries/Win64/ (8 DLLs)
REM
REM  Source is the GitHub Release pinned via RELEASE_TAG below. Idempotent:
REM  files already present at the expected paths are skipped (size-checked).
REM
REM  Defaults to fetching both. Pass --model-only or --gpu-only to limit scope.
REM
REM  Usage:
REM    bootstrap.bat                  fetch model + GPU stack
REM    bootstrap.bat --model-only     fetch only the whisper model
REM    bootstrap.bat --gpu-only       fetch only the GPU stack
REM    bootstrap.bat --force          re-download even if present
REM ─────────────────────────────────────────────────────────────────────────────

set RELEASE_TAG=runtime-v2.0
set RELEASE_BASE=https://github.com/antori82/FANTASIA/releases/download/%RELEASE_TAG%
set MODEL_ASSET=whisper-large-v3-turbo-q5_0.bin
set GPU_ASSET=fantasia-gpu-cuda13-win64.tar.gz

set FETCH_MODEL=1
set FETCH_GPU=1
set FORCE=0
:parse_args
if "%~1"=="" goto :args_done
if /I "%~1"=="--model-only" ( set FETCH_GPU=0 & shift & goto :parse_args )
if /I "%~1"=="--gpu-only"   ( set FETCH_MODEL=0 & shift & goto :parse_args )
if /I "%~1"=="--force"      ( set FORCE=1 & shift & goto :parse_args )
echo Unknown argument: %~1
echo Usage: bootstrap.bat [--model-only ^| --gpu-only] [--force]
exit /b 1
:args_done

set SCRIPT_DIR=%~dp0
set RES_DIR=%SCRIPT_DIR%Resources
set BIN_DIR=%SCRIPT_DIR%Binaries\Win64

if not exist "%RES_DIR%" mkdir "%RES_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

REM Confirm curl + tar are available (built into Windows 10+ since 2018).
where curl >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: curl.exe not found on PATH. Install curl or upgrade to Windows 10 1803+.
    exit /b 1
)
where tar >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: tar.exe not found on PATH. Install bsdtar/libarchive or upgrade to Windows 10 17063+.
    exit /b 1
)

REM ── Fetch whisper model ──────────────────────────────────────────────────
if "%FETCH_MODEL%"=="1" goto :do_model
goto :after_model

:do_model
set MODEL_PATH=%RES_DIR%\ggml-large-v3-turbo-q5_0.bin
if "%FORCE%"=="0" if exist "%MODEL_PATH%" (
    REM Sanity-check the size: the q5_0 model is ~574 MB. Anything below
    REM 100 MB is almost certainly a partial / interrupted prior fetch.
    for %%A in ("%MODEL_PATH%") do set MODEL_SIZE=%%~zA
    if !MODEL_SIZE! GTR 104857600 (
        echo Whisper model already present at %MODEL_PATH% ^(skipping^).
        goto :after_model
    )
    echo Existing model at %MODEL_PATH% looks incomplete ^(!MODEL_SIZE! bytes^); re-downloading.
)

echo.
echo Downloading whisper model %MODEL_ASSET% from %RELEASE_TAG% ...
echo   ^(this is ~574 MB; first run takes a few minutes on a decent link^)
curl -L --fail --progress-bar -o "%MODEL_PATH%" "%RELEASE_BASE%/%MODEL_ASSET%"
if %errorlevel% neq 0 (
    echo ERROR: failed to download %MODEL_ASSET%.
    del /F /Q "%MODEL_PATH%" 2>nul
    exit /b 1
)
echo Model downloaded to %MODEL_PATH%

:after_model

REM ── Fetch GPU stack ──────────────────────────────────────────────────────
if "%FETCH_GPU%"=="1" goto :do_gpu
goto :done

:do_gpu
set GPU_MARKER=%BIN_DIR%\fantasia_whisper_cuda.dll
if "%FORCE%"=="0" if exist "%GPU_MARKER%" (
    echo GPU stack already present at %BIN_DIR% ^(skipping^).
    goto :done
)

set GPU_TGZ=%TEMP%\%GPU_ASSET%
echo.
echo Downloading GPU whisper stack %GPU_ASSET% from %RELEASE_TAG% ...
echo   ^(this is ~540 MB^)
curl -L --fail --progress-bar -o "%GPU_TGZ%" "%RELEASE_BASE%/%GPU_ASSET%"
if %errorlevel% neq 0 (
    echo ERROR: failed to download %GPU_ASSET%.
    del /F /Q "%GPU_TGZ%" 2>nul
    exit /b 1
)

echo Extracting into %BIN_DIR% ...
tar -xf "%GPU_TGZ%" -C "%BIN_DIR%"
if %errorlevel% neq 0 (
    echo ERROR: failed to extract %GPU_ASSET%.
    exit /b 1
)
del /F /Q "%GPU_TGZ%" 2>nul
echo GPU stack staged in %BIN_DIR%

:done
echo.
echo ─────────────────────────────────────────────────
echo  Runtime bootstrap complete.
echo ─────────────────────────────────────────────────
echo  CPU users: nothing else needed; the plugin is ready.
echo  GPU users: set UWhisperSubsystem.Backend = GPU on the
echo  subsystem and reopen the editor. The runtime dispatcher
echo  will load fantasia_whisper_cuda.dll automatically.
