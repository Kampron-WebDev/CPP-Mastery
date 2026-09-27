# Lesson 32: Programs with Multiple Files

> **In one sentence:** Real programs are split into many files; the **compiler** turns each `.cpp`
> into an object file, and the **linker** stitches them together, following strict rules about
> *declarations*, *definitions* and *linkage*.

---

## 🎯 You will learn

- The compile → link model in detail.
- Declarations vs definitions.
- The One Definition Rule (ODR).
- Linkage: internal vs external, and how to flip it (`static`, `extern`).
- `inline` variables and functions; `inline` vs `static`.
- Forward declarations.

---

## 🧸 The Big Idea: a group school project

Each student writes **one chapter** alone (each `.cpp` is compiled alone: a **translation unit**).
Chapter 3 says *"as explained in Chapter 1's `calculateTax`…"*. That's a **declaration**: a promise
that it exists somewhere.

At the end, the **editor (linker)** staples all chapters together and checks every promise:
- Promise made but no chapter defines it → **"undefined reference"** (linker error).
- Two chapters define the same thing → **"multiple definition"** (linker error; ODR violation).

```
 main.cpp ──compile──► main.o ─┐
                               ├──link──► rooster.exe
 utils.cpp ─compile──► utils.o ─┘
     ▲
 utils.h (#included into both: shared declarations)
```

---

## 📚 Step by step

### 1. The model ([32.2](32.2CompilingAndLinking_Model/main.cpp))
Headers (`.h`) hold **declarations**; `.cpp` files hold **definitions**. `#include` is literally copy-paste.
Use `#pragma once` (or include guards) so a header isn't pasted twice into the same file.

### 2. Declarations vs definitions ([32.4](32.4DeclarationsAndDefinitions/main.cpp))
| Declaration (a promise) | Definition (the real thing) |
|---|---|
| `int add(int, int);` | `int add(int a, int b) { return a + b; }` |
| `extern int counter;` | `int counter{0};` |
| `class Dog;` (forward declaration) | `class Dog { ... };` |

### 3. One Definition Rule ([32.5](32.5OneDefinitionRule/main.cpp))
- Functions and variables: **exactly one** definition in the whole program.
- Classes, templates, inline functions: may be defined in several `.cpp` files, **identically** (that's why they live in headers).

### 4. Linkage ([32.6](32.6Linkage/main.cpp), [32.8](32.8FlippingLinkage/main.cpp))
- **External linkage:** visible to other files (default for functions and non-const globals).
- **Internal linkage:** private to one file (`static`, anonymous namespace, and `const`/`constexpr` globals by default).
- `extern int counter;` means "it's defined in another file". It flips a const variable to external too.

### 5. `inline` ([32.9](32.9InlineVariablesAndFunctions/main.cpp), [32.10](32.10InlineVersusStatic/main.cpp))
`inline` = "one shared entity, and it's OK to see its definition in many files".
`static` = "each file gets its **own private copy**".
```cpp
// config.h
inline int maxUsers{100};        // ONE variable shared by the whole program
static int perFileCounter{0};    // a SEPARATE variable in every .cpp that includes this
```

### 6. Forward declarations ([32.11](32.11ForwardDeclarations/main.cpp))
If a header only uses `Dog*` or `Dog&`, write `class Dog;` instead of `#include "dog.h"`. This
speeds up builds and breaks circular includes.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [32.2CompilingAndLinking_Model](32.2CompilingAndLinking_Model/main.cpp) | `.h` + `.cpp` → `.o` → exe |
| [32.4DeclarationsAndDefinitions](32.4DeclarationsAndDefinitions/main.cpp) | Promise vs real thing |
| [32.5OneDefinitionRule](32.5OneDefinitionRule/main.cpp) | ODR |
| [32.6Linkage](32.6Linkage/main.cpp) | Internal vs external |
| [32.8FlippingLinkage](32.8FlippingLinkage/main.cpp) | `extern`, `static` |
| [32.9InlineVariablesAndFunctions](32.9InlineVariablesAndFunctions/main.cpp) | `inline` in headers |
| [32.10InlineVersusStatic](32.10InlineVersusStatic/main.cpp) | Shared vs per-file copies |
| [32.11ForwardDeclarations](32.11ForwardDeclarations/main.cpp) | `class X;` |

## ⚠️ Common mistakes

- Defining a normal function or variable in a header that's included by two `.cpp` files → "multiple definition".
  Fix: `inline`, or move the definition into one `.cpp`.
- Forgetting to compile/link a `.cpp` (in this course's setup, all `.cpp` in the folder are compiled together automatically).
- Circular `#include`s. Fix with forward declarations.

## 🧠 Senior developer notes

- Build speed matters in big codebases: include what you use, forward-declare where you can, and keep headers small.
- **Static initialization order fiasco**: globals in different files are initialized in an unspecified order.
  Avoid globals that depend on other globals; use `constinit`, or a function returning a static local.
- C++20 **modules** (Lesson 49) are the long-term cure for many header problems.

## ✅ Check yourself

1. Which build stage reports "undefined reference"?
2. Can a function be declared many times? Defined many times?
3. `static int x;` in a header included by 3 files: how many `x` variables exist?
4. Why can class definitions appear in headers included everywhere?

<details><summary>Answers</summary>

1. The linker.
2. Declared: yes. Defined: once (unless inline).
3. Three, one per file.
4. The ODR allows identical class definitions in multiple translation units.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 33: Smart Pointers](../33.SmartPointers/README.md)
