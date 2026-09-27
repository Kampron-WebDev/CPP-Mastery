# 🚀 The C++20 Masterclass: From Zero to Senior Developer

A complete, hands-on C++ course: **61 lessons**, hundreds of runnable examples, **200+ exercises with verified solutions**,
and **8 capstone projects**. Every lesson explains its topic in simple words, so even a beginner can follow it, and ends with the
knowledge a senior engineer is expected to have.

> Built on the source code of *The C++20 Masterclass* course (lessons 03–49, by Daniel Gakwaya), rebuilt with
> full explanations, exercises, fixes, one-key build/run/debug in every folder, and 14 new lessons covering what
> professional developers need beyond the language.

---

## ⚡ Start here (5 minutes)

1. Open this folder in **VS Code** and install the **C/C++** extension when it's suggested.
2. Open [00.SetupAndHowToStudy/README.md](00.SetupAndHowToStudy/README.md) and follow it.
3. Open any `main.cpp` and press **`Ctrl + Shift + B`**. It **builds and runs** that folder.
   Press **`F5`** to **debug** it.

This works in **every folder**, whichever folder you opened in VS Code: every folder has its own `.vscode` setup.

---

## 🔁 How every lesson works

```
NN.LessonName/
├── README.md         ← 1. READ: the lesson, explained simply, with pictures and analogies
├── x.yExample/       ← 2. RUN each example. PREDICT the output first!
├── Examples/         ←    (new lessons keep their examples here)
└── Exercises/        ← 3. PRACTISE: starter code with TODOs (⭐ easy → ⭐⭐⭐ hard)
    └── NN_Name/solution/   4. Compare with a reference solution only AFTER trying
```
Each README ends with **✅ Check yourself** questions (with hidden answers). Revisit them a few days later.

---

## 🗺️ The Roadmap

### Part 1: Foundations (think like a programmer)
| # | Lesson | You'll be able to… |
|---|--------|--------------------|
| 00 | [Setup and How to Study](00.SetupAndHowToStudy/README.md) ⭐NEW | Build, run and debug with one key; read errors; study effectively |
| 01 | [How Computers and C++ Work](01.HowComputersAndCppWork/README.md) ⭐NEW | Explain CPU, memory, binary, and the compile/link pipeline |
| 02 | [Programming Thinking](02.ProgrammingThinking/README.md) ⭐NEW | Solve problems step by step: pseudocode, tracing, edge cases |
| 03 | [First Steps](03.FirstSteps/README.md) | Write programs with input, output and functions |
| 04 | [Variables and Data Types](04.VariablesAndDatatypes/README.md) | Choose the right type; understand number systems |
| 05 | [Operations on Data](05.OperationsOnData/README.md) | Use operators, precedence, formatting, `<cmath>` |
| 06 | [Literals and Constants](06.LiteralsAndConstants/README.md) | Use `const`, `constexpr`, `consteval`, `constinit` |
| 07 | [Conversions, Overflow, Underflow](07.ConversionsOverflowAndUnderflow/README.md) | Avoid silent data loss and undefined behaviour |
| 08 | [Bitwise Operators](08.BitwiseOperators/README.md) | Manipulate bits, masks and flags |
| 09 | [Variable Lifetime and Scope](09.VariableLifetimeAndScope/README.md) | Know where names are visible and when objects die |
| 10 | [Flow Control](10.FlowControl/README.md) | Make decisions with `if`, `switch`, ternary |
| 11 | [Loops](11.Loops/README.md) | Repeat work with `for`, `while`, `do-while` |
| 12 | [Arrays](12.Arrays/README.md) | Store collections; generate random numbers |

### Part 2: Memory and Functions (the heart of C++)
| # | Lesson | You'll be able to… |
|---|--------|--------------------|
| 13 | [Pointers](13.Pointers/README.md) | Understand addresses, dynamic memory and its dangers |
| 14 | [References](14.References/README.md) | Use references safely and effectively |
| 15 | [Characters and Strings](15.CharacterManipulationAndStrings/README.md) | Process text with `std::string` and `string_view` |
| 16 | [Functions](16.Functions/README.md) | Pass data the right way; split code across files |
| 17 | [Enums and Type Aliases](17.EnumsAndTypeAliases/README.md) | Model choices safely with `enum class` |
| 18 | [Arguments to main](18.ArgumentsToTheMainFunction/README.md) | Build command-line tools |
| 19 | [Getting Things out of Functions](19.GettingThingsOutOfFuntions/README.md) | Return values safely; `std::optional` |
| 20 | [Function Overloading](20.FunctionOverloading/README.md) | Give one name to several related functions |
| 21 | [Lambda Functions](21.LambdaFunctions/README.md) | Write inline functions with captures |
| 22 | [Static, Inline, Recursion](22.FunctionsTheMisfits/README.md) | Think recursively; memoize |
| 23 | [Call Stack and Debugging](23.FunctionCallStackD_ebugging/README.md) | Hunt bugs systematically with the debugger |
| 24 | [Function Templates](24.FunctionTemplates/README.md) | Write generic code once for all types |
| 25 | [Concepts](25.Concepts/README.md) | Constrain templates with clear rules |

### Part 3: Object-Oriented Programming
| # | Lesson | You'll be able to… |
|---|--------|--------------------|
| 26 | [Classes](26.Classes/README.md) | Design classes that protect invariants |
| 27 | [Zooming in on Class Objects](27.ZoomingInOnClassObjects/README.md) | Write const-correct classes |
| 28 | [Constructors and Initialization](28.DivingDeepIntoConstructorsAndInitialization/README.md) | Control object creation; deep vs shallow copy |
| 29 | [Friends](29.Friends/README.md) | Grant access deliberately; write `operator<<` |
| 30 | [Const and Static Members](30.ConstAndStaticMembers/README.md) | Share data across objects; named constructors |
| 31 | [Namespaces](31.Namespaces/README.md) | Organize code and avoid name clashes |
| 32 | [Programs with Multiple Files](32.ProgramsWithMultipleFiles/README.md) | Fix linker errors; understand linkage and ODR |
| 33 | [Smart Pointers](33.SmartPointers/README.md) | Manage memory with `unique_ptr`/`shared_ptr`, with no leaks |
| 34 | [Operator Overloading](34.OperatorOverloading/README.md) | Build natural value types (Money, Vector…) |
| 35 | [Three-Way Comparison](35.LogicalOperatorsAndThreeWayComparison/README.md) | Use `<=>` and defaulted comparisons |
| 36 | [Inheritance](36.Inheritance/README.md) | Reuse code with base/derived classes |
| 37 | [Polymorphism](37.Polymorphism/README.md) | Design with interfaces and virtual functions |
| 38 | [Exceptions](38.Exceptions/README.md) | Handle errors with safety guarantees |
| 39 | [Practice: BoxContainer](39.Practice-BoxContainerType/README.md) | Build your own container class |

### Part 4: Generic Programming and the STL
| # | Lesson | You'll be able to… |
|---|--------|--------------------|
| 40 | [Class Templates](40.ClassTemplates/README.md) | Write generic classes like `Stack<T>` |
| 41 | [Move Semantics](41.MoveSemantics/README.md) | Avoid copies; implement the Rule of Five |
| 42 | [Function-like Entities](42.FunctionLikeEntities/README.md) | Use callbacks, functors, `std::function` |
| 43 | [STL Containers and Iterators](43.StlContainersAndIterators/README.md) | Use `vector`, `array` and iterators correctly |
| 44 | [STL Containers in Depth](44.ZoomingOnSTLContainers/README.md) | Choose the right container every time |
| 45 | [STL Algorithms](45.StlAlgorithms/README.md) | Replace raw loops with algorithms |
| 46 | [Ranges (C++20)](46.RangesLibraryInCpp20/README.md) | Build lazy data pipelines with views |
| 47 | [Custom Iterators](47.BuildingIteratorsForCustomContainers/README.md) | Make your containers STL-compatible |
| 48 | [Coroutines (C++20)](48.Coroutines/README.md) | Write generators with `co_yield` |
| 49 | [Modules (C++20)](49.Modules/README.md) | Use `import` instead of `#include` |

### Part 5: Becoming a Professional ⭐ all new
| # | Lesson | You'll be able to… |
|---|--------|--------------------|
| 50 | [Files and Streams](50.FileIOAndStreams/README.md) | Read/write files, parse CSV, use `std::filesystem` |
| 51 | [Modern C++ Utilities](51.ModernCppUtilities/README.md) | Use `format`, `variant`, `span`, `chrono`, `expected` |
| 52 | [RAII and the Rule of Zero/Three/Five](52.RAIIAndRuleOfFive/README.md) | Write leak-proof, exception-safe classes |
| 53 | [Concurrency](53.Concurrency/README.md) | Use threads, mutexes, atomics, futures safely |
| 54 | [Data Structures and Algorithms](54.DataStructuresAndAlgorithms/README.md) | Reason with Big-O; solve interview problems |
| 55 | [Testing, Debugging, Clean Code](55.TestingDebuggingAndCleanCode/README.md) | Write tests, use tools, review code like a senior |
| 56 | [Build Systems and CMake](56.BuildSystemsAndCMake/README.md) | Structure and build real projects with tests |
| 57 | [Design Patterns and SOLID](57.DesignPatternsAndSOLID/README.md) | Design flexible, testable software |
| 58 | [Performance and Memory](58.PerformanceAndMemory/README.md) | Measure and optimize; write cache-friendly code |
| 59 | [Capstone Projects](59.CapstoneProjects/README.md) | Build complete programs for your portfolio |
| 60 | [The Senior Developer Roadmap](60.SeniorDeveloperRoadmap/README.md) | Plan your career: tools, interviews, next steps |

---

## 📅 Suggested pace

| Pace | Time | Plan |
|------|------|------|
| Steady | ~1 hour/day | One lesson every 2–4 days → about 6–8 months |
| Intensive | ~3 hours/day | One lesson a day → about 3 months |

Don't rush the early lessons: **02, 13, 16, 26, 33, 37, 41, 52** are the ones everything else builds on.

## ✅ Progress tracker

Copy this into a file of your own, or tick the boxes here as you go:

- [ ] 00–02 Foundations of thinking &nbsp;&nbsp; - [ ] 03–12 Language basics &nbsp;&nbsp; - [ ] 13–25 Memory & functions
- [ ] 26–39 Object-oriented programming &nbsp;&nbsp; - [ ] 40–49 Generic programming & STL
- [ ] 50–58 Professional skills &nbsp;&nbsp; - [ ] 59 Two capstones on GitHub &nbsp;&nbsp; - [ ] 60 Roadmap plan written

---

## 🧰 Tools included in this repository

| Tool | What it does |
|------|--------------|
| `.vscode/` in every folder | `Ctrl+Shift+B` = build & run, `F5` = debug. More tasks: C++23, Clang, Optimized -O2 |
| [tools/vscode-template/](tools/vscode-template) | The master copy of those settings. Edit here if your compiler lives somewhere else |
| [tools/sync-vscode.ps1](tools/sync-vscode.ps1) | Copies the template into every folder: `powershell -ExecutionPolicy Bypass -File tools\sync-vscode.ps1` |
| [tools/check-exercises.ps1](tools/check-exercises.ps1) | Compiles every exercise and solution: `powershell -ExecutionPolicy Bypass -File tools\check-exercises.ps1` |
| [49.Modules/build-modules.ps1](49.Modules/build-modules.ps1) | Builds C++20 modules in the right order (used automatically in Lesson 49) |

**Toolchain:** MinGW-w64 **GCC 14.2** (`C:\mingw64\bin`), **Clang 19**, **GDB**, **CMake 3.31**, **Ninja**.
All code is standard C++20 (a few marked C++23 extras).

### Fixes made to the original source code
- `10.2IfStatements`: the folder had no source code at all, so a full `main.cpp` example was written for it.
- `46.2RangeAlgorithms`: added the missing `#include <iterator>` (didn't compile).
- `47.6CoYield`: added the required `return_void()` to the promise type (didn't compile).
- `48.12ModulesWithNamespaces`: moved `<cmath>` into the global module fragment (header-unit import fails on Clang + libstdc++).
- `44.3ForwardList`, `44.4List`, `44.9Set`: added the missing `#include <algorithm>` for `std::find`.
- All 15 module examples now build with one key press via `build-modules.ps1`.

### Examples that fail ON PURPOSE
16 original examples deliberately contain a compiler or linker error: the instructor uses them to *show* the error.
Each of those folders now has an **`EXPECTED_ERROR.md`** explaining the line, the reason, and how to make the rest run.
If a build fails, check for that file first. Everything else (444 original examples + all new material) builds cleanly.

---

*"The only way to learn a new programming language is by writing programs in it."* (Dennis Ritchie)
Now open [Lesson 00](00.SetupAndHowToStudy/README.md) and write your first one. 🚀
