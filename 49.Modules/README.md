# Lesson 49: Modules (C++20)

> **In one sentence:** Modules replace `#include`'s copy-paste with a proper **import** system:
> faster builds, no macro leaks, and explicit control over what's public (`export`).

---

## 🎯 You will learn

- Writing a module interface (`export module math;`) and importing it (`import math;`).
- The global module fragment (`module;` + `#include`s).
- Exporting single declarations or whole blocks.
- Separating interface and implementation (same file / different files / many files).
- Exporting imports, submodules, and interface partitions (`math:addition`).
- Modules and namespaces; visibility vs reachability; the private module fragment.
- How to BUILD modules (they need a build order).

---

## 🧸 The Big Idea: a restaurant menu

`#include` is like being handed the restaurant's **entire kitchen**, with every recipe, every
ingredient and every note the chef ever scribbled, pasted into your house every time you want a meal.

A module is a **menu**: the restaurant decides what's on it (`export`); you order by name (`import`).
The kitchen stays private, and the menu is prepared **once** (compiled once) instead of on every visit.

```cpp
// math.ixx: module interface
export module math;                      // "this file IS the module named math"
export double add(double a, double b)    // on the menu
{
    return a + b;
}
double secretHelper() { return 42; }     // NOT exported: invisible to importers

// main.cpp
import math;
int main() { return static_cast<int>(add(1, 2)); }   // secretHelper() would be an error here
```

---

## ▶️ How to build these examples (important!)

Modules must be compiled **in dependency order**: a module before anything that imports it.
This folder includes [build-modules.ps1](build-modules.ps1), which works out the order automatically using **Clang**
(GCC 14 on Windows has a linker bug with `import <iostream>;`).

- **In VS Code:** open any file in a module example and press **`Ctrl + Shift + B`**.
  (The `.vscode` in this chapter uses the modules build task.)
- **Terminal:** `powershell -ExecutionPolicy Bypass -File build-modules.ps1 -Dir .\48.2YourFirstModule -Run`

Generated files go to a `build\` subfolder. All 15 examples in this chapter build and run with it.
(Debugging modules with F5 isn't set up; use output while learning this chapter.)

In real projects: **CMake 3.28+** with Ninja handles module build order for you (see Lesson 56).

---

## 📚 Step by step

| Folder | Concept |
|--------|---------|
| [48.1Introduction](48.1Introduction/main.cpp) | The motivation |
| [48.2YourFirstModule](48.2YourFirstModule/math.ixx) | `export module`, `import`, global module fragment |
| [48.3BlockExport](48.3BlockExport/math.ixx) | `export { ... }` |
| [48.4SeparateInterfaceFromImplementation-SameFile](48.4SeparateInterfaceFromImplementation-SameFile/math.ixx) | Declarations first, definitions below |
| [48.5…DifferentFiles](48.5SeparateInterfaceFromImplementation-DifferentFiles/math.ixx) | `module math;` in an implementation `.cpp` |
| [48.6MultipleImplementationFiles](48.6MultipleImplementationFiles/math.ixx) | Several implementation units |
| [48.7MultipleInterfaceFiles](48.7MultipleInterfaceFiles/math.ixx) | Several modules |
| [48.8ExportImport](48.8ExportImport/line.ixx) | `export import Point;` (re-exporting) |
| [48.9SubModules](48.9SubModules/math.ixx) | `math.add_sub` style submodules |
| [48.10ModuleInterfacePartitions](48.10ModuleInterfacePartitions/math.ixx) | `export module math:addition;` partitions |
| [48.11BoxContainerModule](48.11BoxContainerModule/boxcontainer.ixx) | Lesson 39's container as a module |
| [48.12ModulesWithNamespaces](48.12ModulesWithNamespaces/math.ixx) | Namespaces inside modules (fixed: `<cmath>` now included in the global module fragment) |
| [48.13VisibilityReachability](48.13VisibilityReachability/math.ixx) | You can use a type you can't *name* |
| [48.14PrivateModuleFragment](48.14PrivateModuleFragment/math.ixx) | `module :private;` |
| [48.15DosAndDonts](48.15DosAndDonts/math.ixx) | Best practices |

### Key syntax
```cpp
module;                       // 1. global module fragment: old-style #includes go HERE
#include <cstring>
export module math;           // 2. module declaration
import <iostream>;            // 3. imports (header units or other modules)
export namespace math { ... } // 4. exported things
module :private;              // 5. (optional) private fragment: implementation details
```

## ⚠️ Common mistakes

- `#include` after `export module X;` instead of in the global module fragment.
- Expecting macros to cross module boundaries (they don't, by design).
- Compiling in the wrong order ("module not found"). Use the script / CMake.

## 🧠 Senior developer notes

- Tooling support is still maturing (2026: MSVC best, Clang good, GCC improving). Many companies still use headers.
- `import std;` (C++23) imports the entire standard library in one fast line, where supported.
- The concepts (explicit exports, no macro leakage, faster builds) are worth knowing for interviews and future codebases.

## ✅ Check yourself

1. Where do `#include`s go in a module interface file?
2. What does `export import Point;` do?
3. How is a partition named?

<details><summary>Answers</summary>

1. In the global module fragment, between `module;` and `export module X;`.
2. Imports `Point` and re-exports it to anyone importing this module.
3. `module_name:partition_name` (e.g. `math:addition`).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 50: Files and Streams](../50.FileIOAndStreams/README.md), where the new senior-developer lessons begin!
