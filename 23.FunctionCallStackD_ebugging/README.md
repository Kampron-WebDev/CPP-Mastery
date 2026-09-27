# Lesson 23: The Call Stack and Debugging

> **In one sentence:** Every function call gets a **stack frame** (a tray on a pile of trays)
> and a **debugger** lets you freeze the program and inspect that pile. It's the most important
> tool for fixing bugs.

---

## 🎯 You will learn

- What the **call stack** is, and what a **stack frame** contains.
- Stack vs heap memory.
- Using the VS Code debugger: breakpoints, stepping, watches, the call stack panel.
- A systematic method for hunting bugs.

---

## 🧸 The Big Idea: a pile of cafeteria trays

When `main` calls `a()`, and `a()` calls `b()`:

```
          ┌───────────────┐
          │  b()'s frame  │ ← top: currently running
          ├───────────────┤
          │  a()'s frame  │ ← waiting for b() to return
          ├───────────────┤
          │ main()'s frame│ ← waiting for a() to return
          └───────────────┘
              THE STACK
```

Each **tray (frame)** holds that call's parameters, local variables, and the **return address**
("where to go back to"). When `b()` returns, its tray is removed (that's why locals die!),
and `a()` continues exactly where it paused.

Recursion that never stops keeps adding trays until the pile hits the ceiling: **stack overflow**.

| | Stack | Heap |
|---|---|---|
| Who manages it | Automatic | You (`new`/`delete`) or smart pointers |
| Speed | Very fast | Slower |
| Size | Small (~1–8 MB) | Large (most of RAM) |
| Lifetime | Until the function returns | Until freed |

---

## 📚 Debugging in VS Code (practise with [23.4](23.4D_ebuggingInV_S_C0de/main.cpp) and [23.7](23.7D_ebuggingArraysLoopsAndPointers/main.cpp))

1. **Breakpoint**: click left of a line number (red dot). Conditional breakpoint: right-click → *Add Conditional Breakpoint* → `i == 42`.
2. **F5**: start debugging (this course's `launch.json` builds first).
3. Use the panels:
   - **VARIABLES**: locals and their values (expand arrays/objects).
   - **WATCH**: type any expression (`numbers[2]`, `total / count`, `*ptr`).
   - **CALL STACK**: the pile of trays. Click a frame to see *that* function's variables.
4. Controls:

| Key | Action | Use it when |
|-----|--------|-------------|
| `F10` | Step **over** | Run this line, don't go inside functions |
| `F11` | Step **into** | Go inside the function called on this line |
| `Shift+F11` | Step **out** | Finish this function, return to the caller |
| `F5` | Continue | Run to the next breakpoint |
| `Shift+F5` | Stop | End the session |

> 💡 Tip: in the **DEBUG CONSOLE** you can type `-exec p numbers[0]@5` to print 5 array elements through a pointer (a GDB command).

---

## 🔍 The scientific method for bugs

1. **Reproduce** it reliably. Find the smallest input that fails.
2. **Read** the error/crash message and the call stack.
3. **Hypothesise**: "I think `total` is wrong after the loop".
4. **Test the hypothesis** with a breakpoint or watch. Don't change code yet!
5. **Fix** the root cause, not the symptom.
6. **Verify** with the failing input *and* a normal input. Add a test (Lesson 55).

**Binary search for bugs:** if 200 lines are suspect, put a breakpoint in the middle. Is the state
correct there? Then the bug is later. Halve again. 8 steps finds the line among 200.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [23.4D_ebuggingInV_S_C0de](23.4D_ebuggingInV_S_C0de/main.cpp) | Practise breakpoints and stepping |
| [23.7D_ebuggingArraysLoopsAndPointers](23.7D_ebuggingArraysLoopsAndPointers/main.cpp) | Inspecting arrays in loops |

## ⚠️ Common mistakes

- Debugging an **optimized** build: variables show as "optimized out". The course's F5 builds with `-g -O0`.
- Changing five things at once, then not knowing which one fixed it.
- Only using `std::cout` debugging. It's fine sometimes, but it misses the call stack and needs rebuilding each time.

## 🧠 Senior developer notes

- When a program **crashes**, the debugger stops at the crash, so read the **CALL STACK** first. It tells you *who* called the failing line.
- Log files + assertions (Lesson 55) are "debuggers for production" where you can't attach one.
- Explaining the bug to someone (rubber-ducking) is a legitimate senior technique.

## ✅ Check yourself

1. What does a stack frame contain?
2. Why do local variables die when a function returns?
3. F10 vs F11?
4. What is a conditional breakpoint good for?

<details><summary>Answers</summary>

1. Parameters, local variables, return address (and some saved CPU state).
2. Their frame is popped off the stack.
3. F10 steps over calls; F11 steps into them.
4. Stopping only when a condition is true, e.g. on iteration 9 999 of a loop.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 24: Function Templates](../24.FunctionTemplates/README.md)
