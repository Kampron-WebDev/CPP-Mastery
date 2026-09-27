# CMake example project

This folder is a small **real-world layout**: a library (`stats`), an app, and tests.
Unlike other lessons, don't press Ctrl+Shift+B here. Build with CMake from a terminal **in this folder**:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
.\build\stats_app.exe
ctest --test-dir build --output-on-failure
```

Then try:
1. Break a test on purpose (change an expected value) and run `ctest` again.
2. Add a new function `median` to the library + a test for it. Rebuild. Only changed files recompile!
3. Configure a Release build in another folder: `cmake -S . -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release`.
