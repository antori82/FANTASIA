<# 
.SYNOPSIS
  WhisperASR Setup Script — generates wrapper files with RELATIVE paths.
  Portable: works on any machine without re-running.
.USAGE
  powershell -ExecutionPolicy Bypass -File setup_whisper.ps1
#>

$ErrorActionPreference = "Stop"
$PluginDir   = Split-Path -Parent $MyInvocation.MyCommand.Path
$WhisperRoot = Join-Path $PluginDir "Source\ThirdParty\whisper_cpp"
$StagingDir  = Join-Path $PluginDir "Source\WhisperASR\Private\whisper_staged"

# Relative path from staging dir to whisper root:
#   whisper_staged/ → Private/ → WhisperASR/ → Source/ → ThirdParty/whisper_cpp/
$RelativePrefix = "../../../ThirdParty/whisper_cpp"

Write-Host "[WhisperASR Setup]"
Write-Host "  Whisper src: $WhisperRoot"
Write-Host "  Staging dir: $StagingDir"
Write-Host "  Relative prefix: $RelativePrefix"
Write-Host ""

if (-not (Test-Path (Join-Path $WhisperRoot "include\whisper.h")) -and
    -not (Test-Path (Join-Path $WhisperRoot "whisper.h"))) {
    Write-Host "ERROR: whisper.cpp not found." -ForegroundColor Red
    exit 1
}

if (Test-Path $StagingDir) {
    Get-ChildItem $StagingDir -Include *.c,*.cpp -File | Remove-Item -Force
} else {
    New-Item -ItemType Directory -Path $StagingDir -Force | Out-Null
}

$Count = 0

$SkipPatterns = @("main","test","bench","example","cuda","metal","vulkan",
    "sycl","kompute","coreml","openvino","hip","rpc","virtgpu","zdnn","musa","amx")

function ShouldSkip($fileName) {
    $lower = $fileName.ToLower()
    foreach ($p in $SkipPatterns) {
        if ($lower -match $p) { return $true }
    }
    return $false
}

function WriteWrapper($relIncludePath, $destName) {
    $destPath = Join-Path $StagingDir $destName
    # Use forward slashes for #include portability
    $incPath = $relIncludePath.Replace('\', '/')
    $content = @"
// Auto-generated wrapper. Do not edit. Run setup_whisper.ps1 to regenerate.
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4456 4457 4458 4459 4244 4267 4800 4756 4100 4127 4189 4706 4702 4310 4305 4242 4389 4554)
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#include "$incPath"

#ifdef __clang__
#pragma clang diagnostic pop
#endif
#ifdef _MSC_VER
#pragma warning(pop)
#endif
"@
    [System.IO.File]::WriteAllText($destPath, $content, [System.Text.UTF8Encoding]::new($false))
    Write-Host "  $destName"
    $script:Count++
}

function StageDir($subDir, $prefix) {
    $srcDir = Join-Path $WhisperRoot $subDir
    if (-not (Test-Path $srcDir)) {
        Write-Host "  [SKIP] $srcDir" -ForegroundColor Yellow
        return
    }
    Get-ChildItem $srcDir -File | Where-Object { $_.Extension -in '.c','.cpp' } | ForEach-Object {
        if (-not (ShouldSkip $_.Name)) {
            $relPath = "$RelativePrefix/$subDir/$($_.Name)"
            WriteWrapper $relPath "$($prefix)_$($_.Name)"
        }
    }
}

function StageFile($subPath, $destName) {
    $srcFile = Join-Path $WhisperRoot $subPath
    if (-not (Test-Path $srcFile)) {
        Write-Host "  [SKIP] $srcFile" -ForegroundColor Yellow
        return
    }
    $relPath = "$RelativePrefix/$($subPath.Replace('\', '/'))"
    WriteWrapper $relPath $destName
}

Write-Host "--- Whisper core: src/ ---"
StageDir "src" "src"

Write-Host "--- ggml core: ggml/src/ (top-level) ---"
StageDir "ggml/src" "ggml_src"

Write-Host "--- CPU backend: ggml/src/ggml-cpu/ (all files) ---"
StageDir "ggml/src/ggml-cpu" "ggml_src_ggml-cpu"

Write-Host "--- x86 arch: ggml/src/ggml-cpu/arch/x86/ ---"
StageDir "ggml/src/ggml-cpu/arch/x86" "ggml_src_ggml-cpu_arch_x86"

Write-Host ""
Write-Host "Staged $Count wrapper files." -ForegroundColor Cyan
Write-Host ""
Write-Host "Files in staging:"
Get-ChildItem $StagingDir -Include *.c,*.cpp -File | Sort-Object Name | ForEach-Object { Write-Host "  $($_.Name)" }
Write-Host ""

# Verify a wrapper has relative path, not absolute
$testFile = Join-Path $StagingDir "src_whisper.cpp"
if (Test-Path $testFile) {
    $firstInclude = (Get-Content $testFile | Select-String '#include').Line
    if ($firstInclude -match ':[/\\]') {
        Write-Host "WARNING: Wrapper contains absolute path! Check script." -ForegroundColor Yellow
    } else {
        Write-Host "Verified: wrappers use relative paths (portable)." -ForegroundColor Green
    }
    Write-Host "Setup complete!" -ForegroundColor Green
} else {
    Write-Host "ERROR: src_whisper.cpp not found!" -ForegroundColor Red
    exit 1
}
