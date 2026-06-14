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
REM  Optional NVIDIA ACE bundle (interactive MetaHumans / Audio2Face lip-sync),
REM  opt-in via --ace because it is ~520 MB and only needed for ACE lip-sync:
REM    - NV_ACE_Reference recompiled for UE 5.7 + A2F runtime + models
REM      -> ACE-UE57-Bundle/NV_ACE_Reference/  (then moved into Plugins/)
REM
REM  Usage:
REM    bootstrap.bat                  fetch model + GPU stack + build deps
REM    bootstrap.bat --ace            also fetch the NVIDIA ACE 5.7 bundle
REM                                   (= everything for interactive MetaHumans)
REM    bootstrap.bat --runtime-only   skip build deps (Blueprint-only users)
REM    bootstrap.bat --model-only     just the Whisper model
REM    bootstrap.bat --gpu-only       just the GPU stack
REM    bootstrap.bat --deps-only      just the build-time static libs
REM    bootstrap.bat --ace-only       just the NVIDIA ACE 5.7 bundle
REM    bootstrap.bat --force          re-download even if present
REM ─────────────────────────────────────────────────────────────────────────────

set RELEASE_TAG=runtime-v2.0
set RELEASE_BASE=https://github.com/antori82/FANTASIA/releases/download/%RELEASE_TAG%
set MODEL_ASSET=whisper-large-v3-turbo-q5_0.bin
set GPU_ASSET=fantasia-gpu-cuda13-win64.tar.gz
set DEPS_ASSET=fantasia-build-deps-win64.tar.gz
set ACE_ASSET=nv-ace-reference-ue57-full.tar.gz

set FETCH_MODEL=1
set FETCH_GPU=1
set FETCH_DEPS=1
set FETCH_ACE=0
set FORCE=0

REM Capture the script's own directory BEFORE the arg loop. The `shift`
REM calls below shift %0 as well, after which %~dp0 would resolve against
REM the current working directory instead of the script's location --
REM sending all fetched artifacts one level too high when any flag is used.
set SCRIPT_DIR=%~dp0

:parse_args
if "%~1"=="" goto :args_done
REM Quoted `set "VAR=val"` form is required: an unquoted `set VAR=0 & ...`
REM captures the space before `&` INTO the value (VAR becomes "0 "), which
REM then fails the `=="1"` gate checks below. Quotes delimit the value.
if /I "%~1"=="--runtime-only" ( set "FETCH_DEPS=0" & shift & goto :parse_args )
if /I "%~1"=="--model-only"   ( set "FETCH_GPU=0" & set "FETCH_DEPS=0" & shift & goto :parse_args )
if /I "%~1"=="--gpu-only"     ( set "FETCH_MODEL=0" & set "FETCH_DEPS=0" & shift & goto :parse_args )
if /I "%~1"=="--deps-only"    ( set "FETCH_MODEL=0" & set "FETCH_GPU=0" & shift & goto :parse_args )
if /I "%~1"=="--ace"          ( set "FETCH_ACE=1" & shift & goto :parse_args )
if /I "%~1"=="--ace-only"     ( set "FETCH_MODEL=0" & set "FETCH_GPU=0" & set "FETCH_DEPS=0" & set "FETCH_ACE=1" & shift & goto :parse_args )
if /I "%~1"=="--force"        ( set "FORCE=1" & shift & goto :parse_args )
echo Unknown argument: %~1
echo Usage: bootstrap.bat [--runtime-only ^| --model-only ^| --gpu-only ^| --deps-only ^| --ace ^| --ace-only] [--force]
exit /b 1
:args_done

set RES_DIR=%SCRIPT_DIR%Resources
set BIN_DIR=%SCRIPT_DIR%Binaries\Win64
set TP_DIR=%SCRIPT_DIR%ThirdParty
set ACE_DIR=%SCRIPT_DIR%ACE-UE57-Bundle

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
goto :after_deps

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

:after_deps

REM ── Fetch NVIDIA ACE 5.7 bundle (interactive MetaHumans / A2F lip-sync) ───
if "%FETCH_ACE%"=="1" goto :do_ace
goto :done

:do_ace
set ACE_MARKER=%ACE_DIR%\NV_ACE_Reference\NV_ACE_Reference.uplugin
if "%FORCE%"=="0" if exist "%ACE_MARKER%" (
    echo NVIDIA ACE 5.7 bundle already present at %ACE_DIR% ^(skipping^).
    goto :ace_instructions
)
if not exist "%ACE_DIR%" mkdir "%ACE_DIR%"

set ACE_TGZ=%TEMP%\%ACE_ASSET%
echo.
echo Downloading NVIDIA ACE 5.7 bundle %ACE_ASSET% from %RELEASE_TAG% ...
echo   ^(this is ~520 MB: NV_ACE_Reference recompiled for UE 5.7 + A2F runtime + models^)
curl -L --fail --progress-bar -o "%ACE_TGZ%" "%RELEASE_BASE%/%ACE_ASSET%"
if %errorlevel% neq 0 (
    echo ERROR: failed to download %ACE_ASSET%.
    del /F /Q "%ACE_TGZ%" 2>nul
    exit /b 1
)

REM ACE_DIR has no trailing backslash, so quote it directly (no `.` trick needed).
echo Extracting into %ACE_DIR% ...
tar -xf "%ACE_TGZ%" -C "%ACE_DIR%"
if %errorlevel% neq 0 (
    echo ERROR: failed to extract %ACE_ASSET%.
    exit /b 1
)
del /F /Q "%ACE_TGZ%" 2>nul
echo ACE 5.7 bundle staged under %ACE_DIR%

:ace_instructions
echo.
echo  [Interactive MetaHuman setup — manual steps]
echo    1. Move the "NV_ACE_Reference" folder from:
echo         %ACE_DIR%
echo       into your UE project's Plugins\ folder (alongside FANTASIA).
echo    2. Add a MetaHuman to your project (MetaHuman Creator / Fab / Quixel Bridge).
echo    3. Enable FANTASIA, FANTASIAACE and NV_ACE_Reference in the project.
echo    4. Drive the MetaHuman's face with UACERESTTTSComponent /
echo       UACEElevenLabsTTSComponent (from FANTASIAACE).
echo    Licensing + provenance: see
echo      NV_ACE_Reference\README-FANTASIA-UE5.7-bundle.txt

:done
echo.
echo ─────────────────────────────────────────────────
echo  Bootstrap complete.
echo ─────────────────────────────────────────────────
echo  CPU users: nothing else needed; the plugin is ready.
echo  GPU users: set UWhisperSubsystem.Backend = GPU on the
echo  subsystem and reopen the editor. The runtime dispatcher
echo  will load fantasia_whisper_cuda.dll automatically.
