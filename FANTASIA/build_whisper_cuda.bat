@echo off
setlocal EnableDelayedExpansion

REM ─────────────────────────────────────────────────────────────────────────────
REM  Build whisper.cpp with CUDA for FANTASIA plugin (Windows)
REM  Prerequisites: CUDA Toolkit (12.x+), CMake 3.24+, Visual Studio 2022
REM
REM  Modes:
REM    (default) / --shared  — produce fantasia_whisper_cuda.dll + dependencies
REM                            in FANTASIA/Binaries/Win64/. Plugin's runtime
REM                            dispatcher LoadLibrarys it when Backend = GPU.
REM                            Blueprint-only users can use GPU with no rebuild.
REM    --static              — produce static libs Build.cs links into the
REM                            FANTASIA module. Legacy flow that requires a
REM                            full plugin rebuild after running this script.
REM ─────────────────────────────────────────────────────────────────────────────

set MODE=shared
if /I "%~1"=="--shared" set MODE=shared
if /I "%~1"=="--static" set MODE=static

set SCRIPT_DIR=%~dp0
set WHISPER_DIR=%SCRIPT_DIR%ThirdParty\whisper_cpp
set BUILD_DIR=%WHISPER_DIR%\build

REM Check CUDA
if not defined CUDA_PATH (
    echo ERROR: CUDA_PATH not set. Install the NVIDIA CUDA Toolkit.
    exit /b 1
)
echo CUDA Toolkit: %CUDA_PATH%
echo Mode: %MODE%

REM Check CMake
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: cmake not found in PATH.
    exit /b 1
)

REM Check whisper source
if not exist "%WHISPER_DIR%\CMakeLists.txt" (
    echo ERROR: whisper.cpp source not found at %WHISPER_DIR%
    echo Run setup_whisper.bat first.
    exit /b 1
)

REM ─────────────────────────────────────────────────────────────────────
REM Workaround for whisper.cpp's standalone CMake configure: it always
REM runs configure_file on bindings/javascript/package-tmpl.json (top-level
REM CMakeLists.txt around line 29). The FANTASIA distribution strips the
REM bindings/ directory since nothing here builds JS bindings, so the
REM configure step bails out before generating any library targets.
REM Materialize an empty stub before invoking cmake — the configured output
REM is never consumed by anything we build.
REM ─────────────────────────────────────────────────────────────────────
set BINDINGS_JS_DIR=%WHISPER_DIR%\bindings\javascript
if not exist "%BINDINGS_JS_DIR%\package-tmpl.json" (
    if not exist "%BINDINGS_JS_DIR%" mkdir "%BINDINGS_JS_DIR%"
    > "%BINDINGS_JS_DIR%\package-tmpl.json" echo {}
    echo Created stub bindings\javascript\package-tmpl.json to satisfy whisper.cpp configure.
)

REM ─── CMake configure ──────────────────────────────────────────────────
echo.
if "%MODE%"=="shared" (
    echo Configuring whisper.cpp with CUDA, SHARED libraries...
    set CMAKE_SHARED_FLAG=-DBUILD_SHARED_LIBS=ON
) else (
    echo Configuring whisper.cpp with CUDA, STATIC libraries...
    set CMAKE_SHARED_FLAG=-DBUILD_SHARED_LIBS=OFF
)
echo.

REM Wipe the build tree if the mode changed since last invocation -- mixing
REM SHARED and STATIC artifacts in the same build/ directory produces
REM unpredictable linker behaviour.
set MODE_STAMP=%BUILD_DIR%\.fantasia_build_mode
set NEED_CLEAN=0
if exist "%MODE_STAMP%" (
    set /p LAST_MODE=<"%MODE_STAMP%"
    if /I not "!LAST_MODE!"=="%MODE%" set NEED_CLEAN=1
)
if "%NEED_CLEAN%"=="1" (
    echo Build mode changed from !LAST_MODE! to %MODE% -- wiping %BUILD_DIR%
    rmdir /S /Q "%BUILD_DIR%"
)

REM ─── CUDA architectures (CRITICAL for a redistributable DLL) ──────────
REM ggml defaults GGML_NATIVE=ON, which makes CMake compile ONLY the build
REM machine's GPU architecture (e.g. a 4060 build host yields 89-real cubin
REM and NO PTX). That DLL then ABORTS at the first kernel launch on any other
REM architecture (e.g. a Blackwell 50-series, sm_120) with
REM cudaErrorNoKernelImageForDevice -> GGML_ABORT -> crash.
REM
REM Build instead for a broad set of real cubins (Turing..Blackwell) plus a
REM virtual (PTX) entry so the driver can JIT for anything newer. Override
REM with the FANTASIA_CUDA_ARCHS env var if your toolkit predates an arch
REM (e.g. CUDA < 12.8 does not know 120 -- drop it).
if not defined FANTASIA_CUDA_ARCHS (
    set "FANTASIA_CUDA_ARCHS=75-real;80-real;86-real;89-real;90-real;120-real;120-virtual"
)
echo CUDA architectures: %FANTASIA_CUDA_ARCHS%

cmake -B "%BUILD_DIR%" -S "%WHISPER_DIR%" ^
    -DGGML_CUDA=ON ^
    -DGGML_CUDA_FA=ON ^
    -DGGML_NATIVE=OFF ^
    -DCMAKE_CUDA_ARCHITECTURES="%FANTASIA_CUDA_ARCHS%" ^
    %CMAKE_SHARED_FLAG% ^
    -DWHISPER_BUILD_EXAMPLES=OFF ^
    -DWHISPER_BUILD_TESTS=OFF ^
    -DCMAKE_BUILD_TYPE=Release

if %errorlevel% neq 0 (
    echo ERROR: CMake configure failed.
    echo If the error mentions an unknown CUDA architecture, your CUDA toolkit
    echo is older than one listed -- set FANTASIA_CUDA_ARCHS to a supported set,
    echo e.g.  set FANTASIA_CUDA_ARCHS=75-real;80-real;86-real;89-real;89-virtual
    exit /b 1
)

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
> "%MODE_STAMP%" echo %MODE%

echo.
echo Building (Release)...
echo.

cmake --build "%BUILD_DIR%" --config Release --parallel

if %errorlevel% neq 0 (
    echo ERROR: Build failed.
    exit /b 1
)

REM ─── Stage outputs ─────────────────────────────────────────────────────
REM Use goto labels rather than nested if/else blocks: cmd's parser handles
REM parens-inside-parens unreliably when delayed expansion and for-loops
REM are mixed in. Labels are flat and predictable.

set CUDA_BIN=%CUDA_PATH%\bin\x64
if not exist "%CUDA_BIN%" set CUDA_BIN=%CUDA_PATH%\bin

if /I "%MODE%"=="shared" goto :STAGE_SHARED
goto :STAGE_STATIC

:STAGE_SHARED
REM Land everything the plugin needs at runtime directly in Binaries/Win64/.
REM The runtime dispatcher (WhisperBackend.cpp) LoadLibrarys
REM fantasia_whisper_cuda.dll from there; ggml*.dll and CUDA runtime
REM DLLs must be co-located so Windows resolves the import chain.
set DST=%SCRIPT_DIR%Binaries\Win64
if not exist "%DST%" mkdir "%DST%"

echo.
echo Staging shared-build artifacts into %DST% ...

REM Locate the build's bin output. CMake's MSVC generator drops DLLs in
REM build\bin\Release or build\Release\bin depending on whisper.cpp's
REM CMake setup. Probe both.
set BIN_OUT=
if exist "%BUILD_DIR%\bin\Release\whisper.dll" set BIN_OUT=%BUILD_DIR%\bin\Release
if exist "%BUILD_DIR%\Release\whisper.dll"     set BIN_OUT=%BUILD_DIR%\Release
if exist "%BUILD_DIR%\bin\whisper.dll"          set BIN_OUT=%BUILD_DIR%\bin
if "%BIN_OUT%"=="" (
    echo ERROR: whisper.dll not found under %BUILD_DIR%. CMake config / build broken.
    exit /b 1
)
echo Found shared-build output at %BIN_OUT%

REM whisper.dll -> fantasia_whisper_cuda.dll  (the name our loader looks for)
copy /Y "%BIN_OUT%\whisper.dll" "%DST%\fantasia_whisper_cuda.dll" >nul
echo   whisper.dll -^> fantasia_whisper_cuda.dll

REM ggml family DLLs -- keep names. They're transitive deps of whisper.dll
REM and Windows resolves them by their actual filenames in the same folder.
for %%f in ("%BIN_OUT%\ggml*.dll") do (
    copy /Y "%%f" "%DST%\" >nul
    echo   %%~nxf
)

REM CUDA runtime DLLs from the toolkit so end users without the SDK can run.
echo.
echo Copying CUDA runtime DLLs from %CUDA_BIN% ...
for %%d in ("%CUDA_BIN%\cudart64_*.dll" "%CUDA_BIN%\cublas64_*.dll" "%CUDA_BIN%\cublasLt64_*.dll") do (
    copy /Y "%%d" "%DST%\" >nul
    echo   %%~nxd
)

REM Belt-and-suspenders cleanup. SHARED mode also produces whisper.lib +
REM ggml-cuda.lib (as DLL import libs). Since 2026-07 Build.cs only links the
REM prebuilt CUDA libs when FANTASIA_WHISPER_PREBUILT_CUDA=1, so a leftover lib
REM no longer silently flips the shipped DLL into a whisper.dll-importing hybrid.
REM We still delete them here so no stale import libs linger and Build.cs stays
REM cleanly on LoadWhisperFromStagedSource (CPU built-in) with the runtime
REM dispatcher in charge of GPU.
if exist "%BUILD_DIR%\src\Release\whisper.lib" del /F /Q "%BUILD_DIR%\src\Release\whisper.lib"
if exist "%BUILD_DIR%\ggml\src\ggml-cuda\Release\ggml-cuda.lib" del /F /Q "%BUILD_DIR%\ggml\src\ggml-cuda\Release\ggml-cuda.lib"

echo.
echo ─────────────────────────────────────────────────
echo  SHARED build complete. Files staged in:
echo    %DST%
echo ─────────────────────────────────────────────────
echo  In your project, set UWhisperSubsystem.Backend = GPU
echo  before LoadModel. The plugin's runtime dispatcher will
echo  LoadLibrary fantasia_whisper_cuda.dll automatically.
echo  No plugin rebuild needed.
goto :EOF

:STAGE_STATIC
REM Legacy static-build flow: leave the libs in build/ for Build.cs's
REM LoadWhisperPrebuiltCuda. NOTE (since 2026-07): Build.cs also requires the
REM env var FANTASIA_WHISPER_PREBUILT_CUDA=1 to actually link them, so a stray
REM lib can't silently bake CUDA into the shipped DLL -- set it before compiling.
REM Also stage CUDA runtime DLLs into build\bin so Build.cs's
REM RuntimeDependencies copy step has them.
set DLL_DIR=%BUILD_DIR%\bin
if not exist "%DLL_DIR%" mkdir "%DLL_DIR%"

echo.
echo Copying CUDA runtime DLLs for distribution into %DLL_DIR% ...
for %%d in ("%CUDA_BIN%\cudart64_*.dll" "%CUDA_BIN%\cublas64_*.dll" "%CUDA_BIN%\cublasLt64_*.dll") do (
    copy /Y "%%d" "%DLL_DIR%\" >nul
    echo   Copied %%~nxd
)

echo.
echo ─────────────────────────────────────────────────
echo  STATIC build complete. Libraries:
echo ─────────────────────────────────────────────────
for /R "%BUILD_DIR%" %%f in (*.lib) do echo   %%f
echo.
echo  CUDA DLLs (for distribution):
echo ─────────────────────────────────────────────────
for %%f in ("%DLL_DIR%\*.dll") do echo   %%f
echo.
echo  Now set FANTASIA_WHISPER_PREBUILT_CUDA=1 and rebuild the UE project --
echo  Build.cs will then link these libs statically into UnrealEditor-FANTASIA.dll.
echo  (Local/dev build only -- a CUDA-baked core DLL is NOT the redistributable one.)
goto :EOF
