@echo off
setlocal EnableDelayedExpansion

REM ─────────────────────────────────────────────────────────────────────────────
REM  FANTASIA artifact fetcher (Windows)
REM
REM  Downloads the heavy artifacts that don't live in git LFS anymore:
REM    - Whisper ASR model            -> Resources/ggml-large-v3-turbo-q5_0.bin
REM    - Prebuilt GPU whisper stack   -> Binaries/Win64/ (8 DLLs)
REM    - Win64 build-time static libs -> ThirdParty/{aGrUM,grpc,OpenSSL}/...
REM
REM  Source is the GitHub Release pinned via RELEASE_TAG below. Idempotent:
REM  files already present at the expected paths are skipped (size-checked).
REM
REM  Default with no args: fetch ALL three groups. C++ users need the build
REM  deps; Blueprint-only users get an extra ~330 MB on disk but no extra
REM  bandwidth (it's a Release asset, not LFS).
REM
REM  Usage:
REM    bootstrap.bat                  fetch everything (recommended)
REM    bootstrap.bat --runtime-only   skip build deps (Blueprint-only users)
REM    bootstrap.bat --model-only     just the Whisper model
REM    bootstrap.bat --gpu-only       just the GPU stack
REM    bootstrap.bat --deps-only      just the build-time static libs
REM    bootstrap.bat --force          re-download even if present
REM ─────────────────────────────────────────────────────────────────────────────

set RELEASE_TAG=runtime-v2.0
set RELEASE_BASE=https://github.com/antori82/FANTASIA/releases/download/%RELEASE_TAG%
set MODEL_ASSET=whisper-large-v3-turbo-q5_0.bin
set GPU_ASSET=fantasia-gpu-cuda13-win64.tar.gz
set DEPS_ASSET=fantasia-build-deps-win64.tar.gz

set FETCH_MODEL=1
set FETCH_GPU=1
set FETCH_DEPS=1
set FORCE=0
:parse_args
if "%~1"=="" goto :args_done
if /I "%~1"=="--runtime-only" ( set FETCH_DEPS=0 & shift & goto :parse_args )
if /I "%~1"=="--model-only"   ( set FETCH_GPU=0 & set FETCH_DEPS=0 & shift & goto :parse_args )
if /I "%~1"=="--gpu-only"     ( set FETCH_MODEL=0 & set FETCH_DEPS=0 & shift & goto :parse_args )
if /I "%~1"=="--deps-only"    ( set FETCH_MODEL=0 & set FETCH_GPU=0 & shift & goto :parse_args )
if /I "%~1"=="--force"        ( set FORCE=1 & shift & goto :parse_args )
echo Unknown argument: %~1
echo Usage: bootstrap.bat [--runtime-only ^| --model-only ^| --gpu-only ^| --deps-only] [--force]
exit /b 1
:args_done

set SCRIPT_DIR=%~dp0
set RES_DIR=%SCRIPT_DIR%Resources
set BIN_DIR=%SCRIPT_DIR%Binaries\Win64
set TP_DIR=%SCRIPT_DIR%ThirdParty

if not exist "%RES_DIR%" mkdir "%RES_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"
if not exist "%TP_DIR%"  mkdir "%TP_DIR%"

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
goto :after_gpu

:do_gpu
set GPU_MARKER=%BIN_DIR%\fantasia_whisper_cuda.dll
if "%FORCE%"=="0" if exist "%GPU_MARKER%" (
    echo GPU stack already present at %BIN_DIR% ^(skipping^).
    goto :after_gpu
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

:after_gpu

REM ── Fetch build-time static libs ─────────────────────────────────────────
if "%FETCH_DEPS%"=="1" goto :do_deps
goto :done

:do_deps
set DEPS_MARKER=%TP_DIR%\aGrUM\Libraries\agrum.x64.lib
if "%FORCE%"=="0" if exist "%DEPS_MARKER%" (
    echo Build-time static libs already present under %TP_DIR% ^(skipping^).
    goto :done
)

set DEPS_TGZ=%TEMP%\%DEPS_ASSET%
echo.
echo Downloading Win64 build deps %DEPS_ASSET% from %RELEASE_TAG% ...
echo   ^(this is ~60 MB compressed, expands to ~330 MB^)
curl -L --fail --progress-bar -o "%DEPS_TGZ%" "%RELEASE_BASE%/%DEPS_ASSET%"
if %errorlevel% neq 0 (
    echo ERROR: failed to download %DEPS_ASSET%.
    del /F /Q "%DEPS_TGZ%" 2>nul
    exit /b 1
)

echo Extracting into %SCRIPT_DIR% ...
REM %SCRIPT_DIR% always ends with a backslash. Quoting it directly to tar
REM gives `"...\"` which tar parses as an unterminated quote. Tacking on
REM `.` resolves to the same directory while breaking the escape.
tar -xf "%DEPS_TGZ%" -C "%SCRIPT_DIR%."
if %errorlevel% neq 0 (
    echo ERROR: failed to extract %DEPS_ASSET%.
    exit /b 1
)
del /F /Q "%DEPS_TGZ%" 2>nul
echo Build deps staged under %TP_DIR%

:done
echo.
echo ─────────────────────────────────────────────────
echo  Bootstrap complete.
echo ─────────────────────────────────────────────────
echo  CPU users: nothing else needed; the plugin is ready.
echo  GPU users: set UWhisperSubsystem.Backend = GPU on the
echo  subsystem and reopen the editor. The runtime dispatcher
echo  will load fantasia_whisper_cuda.dll automatically.
