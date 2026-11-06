$ErrorActionPreference = 'Stop'
try {
    Write-Host 'This project needs the official SDL3 *development* SDK for Visual C++.'
    Write-Host 'Find the EXTRACTED SDL3-devel-...-VC folder (not just SDL3.dll).'
    $inputPath = (Read-Host 'Path to SDK folder (you can drag the folder into this window)').Trim(' ', '"', "'")
    if (-not $inputPath) { throw 'No path entered.' }
    if (-not (Test-Path -LiteralPath $inputPath -PathType Container)) { throw "Folder not found: $inputPath" }
    $candidate = Get-Item -LiteralPath $inputPath
    if (-not (Test-Path -LiteralPath (Join-Path $candidate.FullName 'include/SDL3/SDL.h'))) {
        $candidate = Get-ChildItem -LiteralPath $inputPath -Directory | Where-Object {
            Test-Path -LiteralPath (Join-Path $_.FullName 'include/SDL3/SDL.h')
        } | Select-Object -First 1
    }
    if (-not $candidate) { throw 'Could not find include/SDL3/SDL.h. Please use the extracted SDL3-devel-...-VC SDK.' }
    $src = $candidate.FullName
    foreach ($file in @('include/SDL3/SDL.h', 'lib/x64/SDL3.lib', 'lib/x64/SDL3.dll')) {
        if (-not (Test-Path -LiteralPath (Join-Path $src $file))) { throw "SDK is missing: $file" }
    }
    $destination = Join-Path (Split-Path -Parent $PSScriptRoot) 'third_party/SDL3'
    New-Item -ItemType Directory -Path $destination -Force | Out-Null
    Copy-Item -LiteralPath (Join-Path $src 'include') -Destination $destination -Recurse -Force
    New-Item -ItemType Directory -Path (Join-Path $destination 'lib/x64') -Force | Out-Null
    Copy-Item -LiteralPath (Join-Path $src 'lib/x64/SDL3.lib') -Destination (Join-Path $destination 'lib/x64/SDL3.lib') -Force
    Copy-Item -LiteralPath (Join-Path $src 'lib/x64/SDL3.dll') -Destination (Join-Path $destination 'lib/x64/SDL3.dll') -Force
    if (Test-Path -LiteralPath (Join-Path $src 'LICENSE.txt')) { Copy-Item -LiteralPath (Join-Path $src 'LICENSE.txt') -Destination (Join-Path $destination 'LICENSE.txt') -Force }
    Write-Host ''
    Write-Host 'SUCCESS: SDL3 SDK copied to third_party/SDL3' -ForegroundColor Green
    Write-Host 'Next: double-click MiracleAuthor.sln, select x64 Release/Debug, and use Build > Build Solution.'
} catch {
    Write-Host "SETUP FAILED: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host 'Extract the official SDL3-devel-...-VC.zip package and try again.'
    exit 1
}
