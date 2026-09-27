# Lesson 56: Build Systems and CMake ⭐ NEW

> **In one sentence:** Real projects have hundreds of files, libraries and tests; **CMake** is
> the industry-standard tool that describes *what* to build, so any compiler on any OS can build it.

---

## 🎯 You will learn

- Why typing `g++ *.cpp` stops scaling.
- A professional project layout (`include/`, `src/`, `app/`, `tests/`).
- `CMakeLists.txt` essentials: `project`, `add_library`, `add_executable`, `target_link_libraries`, `target_include_directories`.
- Build types (Debug / Release), warnings per target, tests with CTest.
- Out-of-source builds, generators (Ninja, Makefiles, Visual Studio).
- Getting third-party libraries (`FetchContent`, vcpkg, Conan).

---

## 🧸 The Big Idea: a recipe book for building

`g++ main.cpp stats.cpp ...` is like cooking by memory: fine for a sandwich, hopeless for a 10-course banquet.
**CMake is the recipe book**: it says what dishes (targets) exist, which ingredients (source files) each needs, and
which dish depends on which. Then a **generator** (Ninja/Make/Visual Studio) is the kitchen staff doing the actual cooking,
and it only re-cooks what changed.

```
 CMakeLists.txt ──cmake (configure)──► build files (Ninja/Make/VS) ──build──► .exe / .lib / tests
      you write this                     generated, never edit              results
```

---

## 📚 Step by step: [Examples/01_CMakeProject](Examples/01_CMakeProject/README.md)

### Layout
```
01_CMakeProject/
├── CMakeLists.txt          ← the recipe
├── include/stats/stats.h   ← PUBLIC headers of the library
├── src/stats.cpp           ← library implementation
├── app/main.cpp            ← the program that uses the library
└── tests/test_stats.cpp    ← tests, run with CTest
```

### The recipe (annotated)
```cmake
cmake_minimum_required(VERSION 3.20)
project(StatsDemo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(stats src/stats.cpp)                        # a reusable library target
target_include_directories(stats PUBLIC include)        # users of 'stats' can #include <stats/stats.h>
target_compile_options(stats PRIVATE -Wall -Wextra)     # warnings for OUR code only

add_executable(stats_app app/main.cpp)
target_link_libraries(stats_app PRIVATE stats)          # app depends on the library

enable_testing()
add_executable(stats_tests tests/test_stats.cpp)
target_link_libraries(stats_tests PRIVATE stats)
add_test(NAME stats_tests COMMAND stats_tests)          # ctest runs it; exit code 0 = pass
```

### Build it (terminal in the example folder)
```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug   # 1. configure (once)
cmake --build build                                      # 2. build (again after every change)
.\build\stats_app.exe                                    # 3. run
ctest --test-dir build --output-on-failure              # 4. test
```
Use `-DCMAKE_BUILD_TYPE=Release` for an optimized build. Delete the `build` folder to start fresh.
> In VS Code, the **CMake Tools** extension adds buttons for configure/build/run/debug.

### Key ideas
- **Targets** are the heart of modern CMake. Attach settings to targets (`target_*`), not globally.
- **PUBLIC / PRIVATE / INTERFACE**: PRIVATE = only for building this target; PUBLIC = also passed on to anyone who links it.
- **Out-of-source builds**: generated files live in `build/`, so your source tree stays clean (and `build/` is git-ignored).
- The original lessons of this course each have a small `CMakeLists.txt`. Open one: you can now read it!

### Third-party libraries
```cmake
include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt GIT_TAG 11.0.2)
FetchContent_MakeAvailable(fmt)
target_link_libraries(stats_app PRIVATE fmt::fmt)
```
Package managers: **vcpkg** and **Conan** handle many libraries across platforms.

### Bonus: C++20 modules with CMake
CMake 3.28+ with Ninja can build modules (Lesson 49) directly: `target_sources(lib PUBLIC FILE_SET CXX_MODULES FILES math.ixx)`.

---

## ⚠️ Common mistakes

- Editing generated files in `build/`.
- Global `include_directories()` / `add_definitions()` instead of per-target commands (old style).
- Forgetting to re-run the build after changing `CMakeLists.txt` (usually automatic), or reusing a build folder configured with another compiler: delete it.
- `file(GLOB ...)` to collect sources: new files aren't noticed until you re-configure. List files explicitly.

## 🧠 Senior developer notes

- **CI (Continuous Integration)**: a server runs `configure → build → ctest` on every push (GitHub Actions, GitLab CI). Red build = don't merge.
- Warnings as errors in CI (`-Werror`) keep the codebase clean.
- Knowing CMake well is one of the most practical, under-rated skills for C++ jobs.

## ✅ Check yourself

1. What is the difference between configuring and building?
2. What does `PUBLIC` mean in `target_include_directories(stats PUBLIC include)`?
3. Why build "out of source"?

<details><summary>Answers</summary>

1. Configuring reads `CMakeLists.txt` and generates build files; building compiles and links using them.
2. The include path is used to build `stats` AND is passed to every target that links `stats`.
3. Generated files don't mix with your sources; deleting `build/` is a clean reset; several build configs can coexist.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 57: Design Patterns and SOLID](../57.DesignPatternsAndSOLID/README.md)
