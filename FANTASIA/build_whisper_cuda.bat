@echo off
setlocal

REM ─────────────────────────────────────────────────────────────────────────────
REM  Build whisper.cpp with CUDA as static libraries for FANTASIA plugin
REM  Prerequisites: CUDA Toolkit (12.x), CMake 3.24+, Visual Studio 2022
REM ─────────────────────────────────────────────────────────────────────────────

set SCRIPT_DIR=%~dp0
set WHISPER_DIR=%SCRIPT_DIR%ThirdParty\whisper_cpp
set BUILD_DIR=%WHISPER_DIR%\build

REM Check CUDA
if not defined CUDA_PATH (
    echo ERROR: CUDA_PATH not set. Install the NVIDIA CUDA Toolkit.
    exit /b 1
)
echo CUDA Toolkit: %CUDA_PATH%

REM Check CMake
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo ERROR: cmake not found in PATH.
    exit /b 1
)

REM Check whisper source
if not exist "%WHISPER_DIR%\CMakeLists.txt" (
    echo ERROR: whisper.cpp source not found at %WHISPER_DIR%
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

echo.
echo Configuring whisper.cpp with CUDA...
echo.

cmake -B "%BUILD_DIR%" -S "%WHISPER_DIR%" ^
    -DGGML_CUDA=ON ^
    -DGGML_CUDA_FA=ON ^
    -DBUILD_SHARED_LIBS=OFF ^
    -DWHISPER_BUILD_EXAMPLES=OFF ^
    -DWHISPER_BUILD_TESTS=OFF ^
    -DCMAKE_BUILD_TYPE=Release

if %errorlevel% neq 0 (
    echo ERROR: CMake configure failed.
    exit /b 1
)

echo.
echo Building (Release)...
echo.

cmake --build "%BUILD_DIR%" --config Release --parallel

if %errorlevel% neq 0 (
    echo ERROR: Build failed.
    exit /b 1
)

REM ── Copy CUDA runtime DLLs so end users don't need the toolkit ──
echo.
echo Copying CUDA runtime DLLs for distribution...

set DLL_DIR=%BUILD_DIR%\bin
if not exist "%DLL_DIR%" mkdir "%DLL_DIR%"

set CUDA_BIN=%CUDA_PATH%\bin\x64
if not exist "%CUDA_BIN%" set CUDA_BIN=%CUDA_PATH%\bin

for %%d in (cudart64_*.dll cublas64_*.dll cublasLt64_*.dll) do (
    if exist "%CUDA_BIN%\%%d" (
        copy /Y "%CUDA_BIN%\%%d" "%DLL_DIR%\" >nul
        echo   Copied %%d
    )
)

echo.
echo ─────────────────────────────────────────────────
echo  Build complete. Libraries:
echo ─────────────────────────────────────────────────

for /R "%BUILD_DIR%" %%f in (*.lib) do (
    echo   %%f
)

echo.
echo  CUDA DLLs (for distribution):
echo ─────────────────────────────────────────────────

for %%f in ("%DLL_DIR%\*.dll") do (
    echo   %%f
)

echo.
echo Now rebuild the UE project — Build.cs will detect and link these libs.
echo CUDA DLLs will be shipped alongside the binary automatically.
