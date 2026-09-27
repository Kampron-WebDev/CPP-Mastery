<#
.SYNOPSIS
  Builds a C++20 modules example folder with Clang, then (optionally) runs it.

.DESCRIPTION
  Modules need a build ORDER: a module must be compiled before anything that imports it.
  Real projects let CMake (3.28+) work that out. This script does it for you:
    1. Precompiles standard "header units" used via  import <iostream>;
    2. Precompiles every module interface (.ixx) into a .pcm, retrying until
       dependencies are satisfied (so file order doesn't matter).
    3. Compiles .pcm files and .cpp files to object files.
    4. Links everything into rooster.exe.
  All generated files go into a  build\  subfolder.

  Why Clang and not GCC? GCC 14 on Windows (MinGW) has a linker bug with header units.

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File build-modules.ps1 -Dir .\48.2YourFirstModule -Run
#>
param(
    [Parameter(Mandatory)] [string]$Dir,
    [switch]$Run
)
# 'Continue': a failed attempt (module not built YET) is normal here. We check $LASTEXITCODE ourselves.
$ErrorActionPreference = 'Continue'
$clang = 'C:\mingw64\bin\clang++.exe'
$std   = '-std=c++20'

$src   = (Resolve-Path $Dir).Path
$build = Join-Path $src 'build'
New-Item -ItemType Directory -Force $build | Out-Null
Push-Location $build
try {
    $sources = Get-ChildItem $src -File | Where-Object { $_.Extension -in '.ixx', '.cppm', '.cpp' }

    # 1. Header units: every  import <name>;  found in any source file
    $headers = $sources | Select-String -Pattern '^\s*(?:export\s+)?import\s+<([^>]+)>\s*;' |
        ForEach-Object { $_.Matches[0].Groups[1].Value } | Sort-Object -Unique
    $huFlags = @()
    foreach ($h in $headers) {
        $pcm = "hu_$h.pcm"
        if (-not (Test-Path $pcm)) {
            Write-Host "  header unit <$h>"
            & $clang $std -Wno-experimental-header-units -x c++-system-header $h --precompile -o $pcm
            if ($LASTEXITCODE) { throw "Could not precompile <$h>" }
        }
        $huFlags += "-fmodule-file=$pcm"
    }
    $common = @($std, '-Wno-experimental-header-units', '-fprebuilt-module-path=.') + $huFlags

    # 2. Module interfaces, in dependency order (retry until nothing is left)
    $pending = @($sources | Where-Object { $_.Extension -in '.ixx', '.cppm' })
    $objects = @()
    $lastError = ''
    while ($pending.Count -gt 0) {
        $progress = $false
        foreach ($f in @($pending)) {
            $m = Select-String -Path $f.FullName -Pattern '^\s*export\s+module\s+([\w.:]+)\s*;' | Select-Object -First 1
            if (-not $m) { throw "$($f.Name): no 'export module X;' line found" }
            $name = $m.Matches[0].Groups[1].Value
            $pcm  = ($name -replace ':', '-') + '.pcm'      # partitions A:B are looked up as A-B.pcm
            $out  = & $clang @common -x c++-module $f.FullName --precompile -o $pcm 2>&1
            if ($LASTEXITCODE -eq 0) {
                Write-Host "  module $name"
                & $clang @common $pcm -c -o ($pcm -replace '\.pcm$', '.o')
                if ($LASTEXITCODE) { throw "Could not compile $pcm" }
                $objects += ($pcm -replace '\.pcm$', '.o')
                $pending = @($pending | Where-Object { $_ -ne $f })
                $progress = $true
            } else { $lastError = $out -join "`n" }
        }
        if (-not $progress) { Write-Host $lastError -ForegroundColor Red; throw 'Module build failed (see error above).' }
    }

    # 3. Ordinary .cpp files (module implementation units and main.cpp)
    foreach ($f in $sources | Where-Object { $_.Extension -eq '.cpp' }) {
        $obj = [IO.Path]::GetFileNameWithoutExtension($f.Name) + '.cpp.o'
        & $clang @common -c $f.FullName -o $obj
        if ($LASTEXITCODE) { throw "Could not compile $($f.Name)" }
        $objects += $obj
    }

    # 4. Link
    $exe = Join-Path $src 'rooster.exe'
    & $clang @objects -o $exe
    if ($LASTEXITCODE) { throw 'Link failed' }
    Write-Host "Built $exe" -ForegroundColor Green
}
finally { Pop-Location }

if ($Run) {
    Write-Host '---------------- program output ----------------'
    & (Join-Path $src 'rooster.exe')
}
