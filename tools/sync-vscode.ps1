<#
.SYNOPSIS
  Copies the master VS Code config (tools/vscode-template) into the course root,
  every chapter folder, and every folder that contains C++ code.

.DESCRIPTION
  Why? VS Code only reads the .vscode folder of the folder you OPEN.
  So whether you open the whole course, one chapter, or one tiny example
  folder, Ctrl+Shift+B (build & run) and F5 (debug) will work.

  Changed your compiler location? Edit the files in tools/vscode-template,
  then run this script again:
      powershell -ExecutionPolicy Bypass -File tools\sync-vscode.ps1
#>
$ErrorActionPreference = 'Stop'
$root      = Split-Path -Parent $PSScriptRoot
$template  = Join-Path $PSScriptRoot 'vscode-template'
$modTasks  = Join-Path $PSScriptRoot 'vscode-template-modules\tasks.json'

$targets = [System.Collections.Generic.HashSet[string]]::new()
[void]$targets.Add($root)

Get-ChildItem $root -Directory | Where-Object { $_.Name -match '^\d\d\.' } | ForEach-Object {
    [void]$targets.Add($_.FullName)
    Get-ChildItem $_.FullName -Recurse -File -Include *.cpp, *.ixx, *.cppm |
        Where-Object { $_.FullName -notmatch '[\\/](\.vscode|build|out|gcm\.cache)[\\/]' } |
        ForEach-Object { [void]$targets.Add($_.DirectoryName) }
}

$count = 0
foreach ($dir in $targets) {
    $dest = Join-Path $dir '.vscode'
    New-Item -ItemType Directory -Force $dest | Out-Null
    Copy-Item (Join-Path $template '*') $dest -Force
    # Modules need a special multi-step build (see 49.Modules/README.md)
    if ($dir -like '*\49.Modules*' -and (Test-Path $modTasks)) {
        Copy-Item $modTasks (Join-Path $dest 'tasks.json') -Force
    }
    $count++
}
Write-Host "Synced .vscode into $count folders." -ForegroundColor Green
