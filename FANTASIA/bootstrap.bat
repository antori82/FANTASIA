@echo off
setlocal EnableDelayedExpansion

REM ─────────────────────────────────────────────────────────────────────────────
REM  FANTASIA artifact fetcher (Windows) — main branch
REM
REM  Downloads the heavy artifacts that don't live in git LFS anymore:
REM    - Whisper ASR model            -> Resources/ggml-large-v3-turbo-q5_0.bin
REM    - Win64 build-time static libs -> ThirdParty/{aGrUM,grpc,OpenSSL}/...
REM    - Microsoft Cognitive Services Speech SDK -> ThirdParty/Microsoft.CognitiveServices.Speech.1.32.1/
REM
REM  Source is the GitHub Release pinned via RELEASE_TAG below. Idempotent:
REM  files already present at the expected paths are skipped (size-checked).
REM
REM  Default with no args: fetch everything. C++ users need build deps + the
REM  Azure SDK to recompile FANTASIA cleanly. Blueprint-only users get an
REM  extra ~500 MB on disk but no extra bandwidth (Release assets aren't
REM  on the LFS quota).
REM
REM  Usage:
REM    bootstrap.bat                  fetch everything (recommended)
REM    bootstrap.bat --runtime-only   skip build deps + Azure SDK
REM    bootstrap.bat --model-only     just the Whisper model
REM    bootstrap.bat --deps-only      just the build-time static libs
REM    bootstrap.bat --azure-only     just the Azure Speech SDK
REM    bootstrap.bat --force          re-download even if present
REM ─────────────────────────────────────────────────────────────────────────────

set RELEASE_TAG=runtime-v2.0
set RELEASE_BASE=https://github.com/antori82/FANTASIA/releases/download/%RELEASE_TAG%
set MODEL_ASSET=whisper-large-v3-turbo-q5_0.bin
set DEPS_ASSET=fantasia-build-deps-win64.tar.gz
set AZURE_ASSET=fantasia-azure-sdk-win64.tar.gz

set FETCH_MODEL=1
set FETCH_DEPS=1
set FETCH_AZURE=1
set FORCE=0
:parse_args
if "%~1"=="" goto :args_done
if /I "%~1"=="--runtime-only" ( set FETCH_DEPS=0 & set FETCH_AZURE=0 & shift & goto :parse_args )
if /I "%~1"=="--model-only"   ( set FETCH_DEPS=0 & set FETCH_AZURE=0 & shift & goto :parse_args )
if /I "%~1"=="--deps-only"    ( set FETCH_MODEL=0 & set FETCH_AZURE=0 & shift & goto :parse_args )
if /I "%~1"=="--azure-only"   ( set FETCH_MODEL=0 & set FETCH_DEPS=0 & shift & goto :parse_args )
if /I "%~1"=="--force"        ( set FORCE=1 & shift & goto :parse_args )
echo Unknown argument: %~1
echo Usage: bootstrap.bat [--runtime-only ^| --model-only ^| --deps-only ^| --azure-only] [--force]
exit /b 1
:args_done

set SCRIPT_DIR=%~dp0
set RES_DIR=%SCRIPT_DIR%Resources
set TP_DIR=%SCRIPT_DIR%ThirdParty

if not exist "%RES_DIR%" mkdir "%RES_DIR%"
if not exist "%TP_DIR%"  mkdir "%TP_DIR%"

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
    for %%A in ("%MODEL_PATH%") do set MODEL_SIZE=%%~zA
    if !MODEL_SIZE! GTR 104857600 (
        echo Whisper model already present at %MODEL_PATH% ^(skipping^).
        goto :after_model
    )
    echo Existing model at %MODEL_PATH% looks incomplete ^(!MODEL_SIZE! bytes^); re-downloading.
)

echo.
echo Downloading whisper model %MODEL_ASSET% from %RELEASE_TAG% ...
echo   ^(~574 MB^)
curl -L --fail --progress-bar -o "%MODEL_PATH%" "%RELEASE_BASE%/%MODEL_ASSET%"
if %errorlevel% neq 0 (
    echo ERROR: failed to download %MODEL_ASSET%.
    del /F /Q "%MODEL_PATH%" 2>nul
    exit /b 1
)
echo Model downloaded to %MODEL_PATH%

:after_model

REM ── Fetch build-time static libs ─────────────────────────────────────────
if "%FETCH_DEPS%"=="1" goto :do_deps
goto :after_deps

:do_deps
set DEPS_MARKER=%TP_DIR%\aGrUM\Libraries\agrum.x64.lib
if "%FORCE%"=="0" if exist "%DEPS_MARKER%" (
    echo Build-time static libs already present under %TP_DIR% ^(skipping^).
    goto :after_deps
)

set DEPS_TGZ=%TEMP%\%DEPS_ASSET%
echo.
echo Downloading Win64 build deps %DEPS_ASSET% from %RELEASE_TAG% ...
echo   ^(~60 MB compressed, expands to ~330 MB^)
curl -L --fail --progress-bar -o "%DEPS_TGZ%" "%RELEASE_BASE%/%DEPS_ASSET%"
if %errorlevel% neq 0 (
    echo ERROR: failed to download %DEPS_ASSET%.
    del /F /Q "%DEPS_TGZ%" 2>nul
    exit /b 1
)

echo Extracting into %SCRIPT_DIR% ...
REM Trailing backslash on %SCRIPT_DIR% escapes the closing quote when passed
REM directly to tar; tack on `.` to break the escape without changing the dest.
tar -xf "%DEPS_TGZ%" -C "%SCRIPT_DIR%."
if %errorlevel% neq 0 (
    echo ERROR: failed to extract %DEPS_ASSET%.
    exit /b 1
)
del /F /Q "%DEPS_TGZ%" 2>nul
echo Build deps staged under %TP_DIR%

:after_deps

REM ── Fetch Azure Speech SDK ───────────────────────────────────────────────
if "%FETCH_AZURE%"=="1" goto :do_azure
goto :done

:do_azure
set AZURE_MARKER=%TP_DIR%\Microsoft.CognitiveServices.Speech.1.32.1\build\native\x64\Release\Microsoft.CognitiveServices.Speech.core.lib
if "%FORCE%"=="0" if exist "%AZURE_MARKER%" (
    echo Azure Speech SDK already present under %TP_DIR% ^(skipping^).
    goto :done
)

set AZURE_TGZ=%TEMP%\%AZURE_ASSET%
echo.
echo Downloading Azure Speech SDK %AZURE_ASSET% from %RELEASE_TAG% ...
echo   ^(~160 MB compressed, expands to ~170 MB^)
curl -L --fail --progress-bar -o "%AZURE_TGZ%" "%RELEASE_BASE%/%AZURE_ASSET%"
if %errorlevel% neq 0 (
    echo ERROR: failed to download %AZURE_ASSET%.
    del /F /Q "%AZURE_TGZ%" 2>nul
    exit /b 1
)

echo Extracting into %SCRIPT_DIR% ...
tar -xf "%AZURE_TGZ%" -C "%SCRIPT_DIR%."
if %errorlevel% neq 0 (
    echo ERROR: failed to extract %AZURE_ASSET%.
    exit /b 1
)
del /F /Q "%AZURE_TGZ%" 2>nul
echo Azure Speech SDK staged under %TP_DIR%

:done
echo.
echo ─────────────────────────────────────────────────
echo  Bootstrap complete.
echo ─────────────────────────────────────────────────
echo  Plugin is ready to load. Whisper, Azure ASR/TTS,
echo  and AWS Polly components all work out of the box.
