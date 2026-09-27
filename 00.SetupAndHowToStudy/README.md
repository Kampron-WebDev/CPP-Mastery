# Lesson 00: Setup and How to Study This Course

> **In one sentence:** Before you can bake a cake you need an oven. Here you check that your
> "oven" (the compiler) works, and you learn a study routine that turns reading into real skill.

---

## 🎯 By the end of this lesson you can

- Explain what a **compiler** is and why C++ needs one.
- Build and run any lesson in this course with **one key press**.
- Use the **debugger** to pause a program and look inside it.
- Read a compiler error without panicking.
- Follow the **study loop** that the rest of this course is built around.

---

## 🧸 The Big Idea (explained like you're 10)

Computers only understand **machine code**: long lists of 1s and 0s. Humans are bad at writing 1s and 0s.

So we write instructions in a language that looks a bit like English (C++), and a special program
called a **compiler** translates it into machine code.

```
   You write            The compiler              The computer runs
 ┌────────────┐        ┌─────────────┐          ┌──────────────────┐
 │ main.cpp   │ ─────► │  g++.exe    │ ───────► │  rooster.exe     │
 │ (C++ text) │        │ (translator)│          │  (1s and 0s)     │
 └────────────┘        └─────────────┘          └──────────────────┘
```

Think of it like a recipe written in English (your code) being translated into a language the
kitchen robot understands (machine code). If your recipe has a spelling mistake, the translator
refuses to translate and tells you where the mistake is. That message is a **compiler error**,
and it is your friend.

---

## 🔧 Step 1: Check your tools

This course is set up for the tools already installed on this PC:

| Tool | Where | What it does |
|------|-------|--------------|
| **g++ 14.2** (GCC) | `C:\mingw64\bin\g++.exe` | Main compiler |
| **clang++ 19** | `C:\mingw64\bin\clang++.exe` | Second compiler (friendlier errors, needed for Modules) |
| **gdb** | `C:\mingw64\bin\gdb.exe` | Debugger (pause and inspect programs) |
| **cmake** | `C:\mingw64\bin\cmake.exe` | Build system used by real-world projects (Lesson 56) |

Open a terminal in VS Code (menu **Terminal → New Terminal**) and type:

```powershell
g++ --version
```

If you see `g++.exe (MinGW-W64 ...) 14.2.0`, you are ready. If not, add `C:\mingw64\bin` to your
Windows `PATH` environment variable and restart VS Code.

In VS Code, install the extension **C/C++** by Microsoft. VS Code suggests it automatically
because of `.vscode/extensions.json`.

> Using a different computer or compiler location? Edit the files in
> [tools/vscode-template](../tools/vscode-template), then run
> `powershell -ExecutionPolicy Bypass -File tools\sync-vscode.ps1` from the course root.
> That copies your change into every folder.

---

## ▶️ Step 2: Run a program with ONE key

Every folder in this course has a `.vscode` folder with the same settings, so **it does not
matter which folder you open**. You can open the whole course, a single chapter, or a single example.

1. Open any `main.cpp`, for example [Examples/01_HelloWorld/main.cpp](Examples/01_HelloWorld/main.cpp).
2. Press **`Ctrl + Shift + B`**.
3. The terminal opens, the program is compiled, and then it **runs**. If it asks you to type
   something, click into the terminal and type.

What happens behind the scenes:

```
g++ -std=c++20 -g -Wall -Wextra  <this folder>\*.cpp  -o  <this folder>\rooster.exe
<this folder>\rooster.exe
```

- `-std=c++20`: use the C++20 version of the language.
- `-g`: keep debugging information so the debugger can show your code.
- `-Wall -Wextra`: turn on **warnings**. Warnings are the compiler saying "this is legal, but
  it looks like a mistake." A senior developer treats warnings like errors.
- `*.cpp`: compile **every** `.cpp` file in the folder together. That is why lessons made of several files
  (like [Examples/02_MultiFile](Examples/02_MultiFile)) just work.

**Other tasks** (`Ctrl + Shift + P` → *Tasks: Run Task*):

| Task | Use it when |
|------|-------------|
| C++: Build this folder (GCC) | You only want to compile, not run |
| C++: Build this folder (Clang) | GCC's error message confuses you; get a second opinion |
| C++: Build this folder (C++23, GCC) | A lesson uses C++23 features (marked in its README) |
| C++: Build this folder (Optimized -O2) | You are measuring speed (Lesson 58) |

---

## 🐞 Step 3: Debug with F5

A **debugger** lets you freeze time inside your program.

1. Click in the margin left of a line number. A **red dot** appears (a *breakpoint*).
2. Press **`F5`**. The program runs and **stops** on the red dot.
3. Look at the **VARIABLES** panel on the left: you can see every variable's value.
4. Press **`F10`** to run one line (*step over*), **`F11`** to go *into* a function, **`Shift+F5`** to stop.

> 💡 Beginners add `std::cout` everywhere to find bugs. Professionals use the debugger first.
> Lesson 23 goes deeper.

---

## 🩺 Step 4: Read an error message calmly

Try it: open [Examples/01_HelloWorld/main.cpp](Examples/01_HelloWorld/main.cpp), delete a `;`, and press `Ctrl+Shift+B`.

```
main.cpp:7:43: error: expected ';' before 'return'
```

Read it like an address: **file** `main.cpp`, **line** 7, **column** 43, then **what is wrong**.

Rules that save hours:
1. **Fix the FIRST error first.** One missing `;` can cause 20 fake errors after it.
2. The real mistake is often on the line **before** the one reported.
3. Copy the key part of the message (for example `expected ';' before`) into a search engine. Someone has had it before.

---

## 🔁 Step 5: The Study Loop (the most important part of this lesson)

Reading code does **not** make you a programmer, just as watching football does not make you a
footballer. Each lesson has the same shape, and you should use it the same way every time:

```
 1. READ      the lesson README.md          (understand the idea)
 2. RUN       each example folder           (see it work)
 3. PREDICT   before running, guess the output out loud. Were you right?
 4. BREAK IT  change one thing, predict again, run again
 5. EXERCISE  do Exercises/ WITHOUT looking at the solution
 6. COMPARE   only then open solution/, and note what was better
 7. QUIZ      answer "Check yourself" at the end of the README
 8. REVISIT   2–3 days later, redo one exercise from memory
```

Step 3 (predicting) and step 8 (revisiting) build long-term memory. Please don't skip them.

### Lesson folder anatomy

```
05.OperationsOnData/
├── README.md               ← the lesson (start here)
├── .vscode/                ← build/run/debug settings
├── 5.2.BasicOperations/    ← example code (one idea per folder)
├── 5.3.Precedence.../
├── ...
└── Exercises/
    ├── README.md           ← list of exercises + hints
    ├── 01_Something/
    │   ├── main.cpp        ← YOUR work goes here (starter code with TODOs)
    │   └── solution/main.cpp   ← a reference answer: open only after trying
    └── ...
```

Difficulty stars in exercises: ⭐ warm-up · ⭐⭐ practice · ⭐⭐⭐ challenge (think hard!)

Want proof all exercises compile? From the course root run:
`powershell -ExecutionPolicy Bypass -File tools\check-exercises.ps1`

---

## 🛠️ Command line (good to know, used by every professional)

```powershell
cd "03.FirstSteps\3.2FirstCppProgram"
g++ -std=c++20 -Wall -Wextra -g main.cpp -o rooster.exe
.\rooster.exe
```

Each original example folder also has a `CMakeLists.txt`. CMake is what real projects use:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\build\rooster.exe
```

---

## ✅ Check yourself

1. What does a compiler do?
2. What is the difference between an **error** and a **warning**?
3. Which key builds and runs? Which key debugs?
4. You get 15 errors. Which one do you fix first?
5. What are the 8 steps of the study loop?

<details><summary>Answers</summary>

1. It translates human-readable C++ into machine code the CPU can run.
2. An error stops the program from being built. A warning still builds, but the code looks suspicious.
3. `Ctrl+Shift+B` builds and runs; `F5` debugs.
4. The first one. Later errors are often caused by it.
5. Read, Run, Predict, Break it, Exercise, Compare, Quiz, Revisit.
</details>

---

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 01: How Computers and C++ Work](../01.HowComputersAndCppWork/README.md)
