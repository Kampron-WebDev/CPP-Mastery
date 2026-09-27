<#
.SYNOPSIS
  Compiles every exercise starter and every solution in the course.
  A green run proves all the practice code is healthy.

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File tools\check-exercises.ps1
  powershell -ExecutionPolicy Bypass -File tools\check-exercises.ps1 -Filter 16.
#>
param([string]$Filter = '')
$root = Split-Path -Parent $PSScriptRoot
$gxx  = 'C:\mingw64\bin\g++.exe'
$tmp  = Join-Path ([IO.Path]::GetTempPath()) 'cpp-course-check'
New-Item -ItemType Directory -Force $tmp | Out-Null

$dirs = Get-ChildItem $root -Recurse -Filter *.cpp -File |
    Where-Object { $_.FullName -like '*\Exercises\*' -and $_.FullName -like "*$Filter*" } |
    Select-Object -ExpandProperty DirectoryName -Unique | Sort-Object

$pass = 0; $fail = @()
foreach ($d in $dirs) {
    if (Test-Path (Join-Path $d '.skip-check')) { continue }   # e.g. parts of a CMake project
    $std = if (Test-Path (Join-Path $d '.cpp23')) { '-std=c++23' } else { '-std=c++20' }
    $out = Join-Path $tmp 'check.exe'
    $extra = if (Test-Path (Join-Path $d '.threads')) { @('-pthread') } else { @() }
    if (Test-Path (Join-Path $d '.modules')) {
        # C++20 modules need an ordered, multi-step build (see 49.Modules/README.md)
        $log = & powershell -NoProfile -ExecutionPolicy Bypass -File (Join-Path $root '49.Modules\build-modules.ps1') -Dir $d 2>&1
    } else {
        $log = & $gxx $std -Wall -Wextra "$d\*.cpp" @extra -o $out 2>&1
    }
    $rel = $d.Substring($root.Length + 1)
    # A starter marked .expect-fail is broken ON PURPOSE (e.g. "fix the linker errors").
    $expectFail = Test-Path (Join-Path $d '.expect-fail')
    if ($expectFail) {
        if ($LASTEXITCODE -ne 0) { $pass++; Write-Host "  ok   $rel (fails on purpose)" -ForegroundColor DarkGreen }
        else { $fail += $rel; Write-Host "  FAIL $rel (was expected NOT to build)" -ForegroundColor Red }
    }
    elseif ($LASTEXITCODE -eq 0) { $pass++; Write-Host "  ok   $rel" -ForegroundColor DarkGreen }
    else { $fail += $rel; Write-Host "  FAIL $rel" -ForegroundColor Red; $log | Select-Object -First 8 | Write-Host }
}
Write-Host ""
Write-Host "Passed: $pass   Failed: $($fail.Count)" -ForegroundColor ($(if ($fail.Count) { 'Red' } else { 'Green' }))
exit $fail.Count
