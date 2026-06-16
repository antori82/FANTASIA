<#
.SYNOPSIS
  Enable FANTASIA + companion plugins in a UE project's .uproject.

  Called by bootstrap.bat --enable-plugins. Given the project's Plugins/
  directory, finds the sibling .uproject and ensures the FANTASIA stack is
  listed as Enabled. A one-time .uproject.bak backup is written first.

  Best-effort + non-fatal: any problem prints a note and exits 0 so the
  bootstrap as a whole still succeeds (the user can enable in the editor).
#>
param([Parameter(Mandatory = $true)][string]$PluginsDir)

$ErrorActionPreference = 'Stop'
try {
    $projRoot = Split-Path -Parent $PluginsDir
    $uproj = Get-ChildItem -LiteralPath $projRoot -Filter *.uproject -File -ErrorAction SilentlyContinue | Select-Object -First 1
    if (-not $uproj) {
        Write-Output "  No .uproject found in $projRoot -- enable the plugins in the editor's Plugins panel instead."
        exit 0
    }

    $path = $uproj.FullName
    $bak  = "$path.bak"
    if (-not (Test-Path -LiteralPath $bak)) { Copy-Item -LiteralPath $path -Destination $bak }

    # Use .NET ReadAllText/WriteAllText (clean open+close). Get-Content -Raw can
    # keep a memory-mapped handle that collides with writing the same file
    # immediately after ("user-mapped section is open").
    $json = [System.IO.File]::ReadAllText($path) | ConvertFrom-Json

    $want = @('FANTASIA', 'FANTASIAACE', 'NV_ACE_Reference', 'NvAudio2FaceMark', 'NvAudio2FaceJames')

    $plugins = @()
    if (($json.PSObject.Properties.Name -contains 'Plugins') -and $json.Plugins) {
        $plugins = @($json.Plugins)
    }

    foreach ($name in $want) {
        $existing = $plugins | Where-Object { $_.Name -eq $name } | Select-Object -First 1
        if ($existing) {
            $existing.Enabled = $true
        }
        else {
            $plugins += [pscustomobject]@{ Name = $name; Enabled = $true }
        }
    }

    if ($json.PSObject.Properties.Name -contains 'Plugins') {
        $json.Plugins = $plugins
    }
    else {
        $json | Add-Member -NotePropertyName Plugins -NotePropertyValue $plugins
    }

    [System.IO.File]::WriteAllText($path, ($json | ConvertTo-Json -Depth 30))
    Write-Output "  Enabled in $($uproj.Name): $($want -join ', ')   (backup: $($uproj.Name).bak)"
}
catch {
    Write-Output "  Could not auto-enable plugins ($($_.Exception.Message)). Enable them in the editor's Plugins panel; your .uproject is unchanged or restorable from .uproject.bak."
    exit 0
}
