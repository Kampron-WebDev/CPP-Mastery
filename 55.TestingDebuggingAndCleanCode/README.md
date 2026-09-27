# Lesson 55: Testing, Debugging and Clean Code ⭐ NEW

> **In one sentence:** Senior developers aren't people who never write bugs. They're people who
> **catch bugs early** (tests, assertions, warnings) and write code that is **easy for others to read and change**.

---

## 🎯 You will learn

- `assert` and `static_assert`: executable assumptions.
- **Unit testing**: writing tests with a tiny homemade framework, then what real frameworks (GoogleTest, Catch2, doctest) add.
- **Test-Driven Development** (TDD): red → green → refactor.
- Compiler warnings as a bug-catching tool; static analysis (`clang-tidy`); formatting (`clang-format`).
- Sanitizers and other debugging tools.
- Clean code: naming, small functions, comments, DRY, code smells, and a **code-review checklist**.

---

## 🧸 The Big Idea: the safety net and the tidy workshop

- **Tests are a safety net.** A tightrope walker with a net walks faster and braver. With tests you can
  change code boldly, because if you break something the net catches it within seconds.
- **Clean code is a tidy workshop.** In a messy workshop you waste an hour finding the hammer. In messy
  code you waste days finding the bug. You write code once; you (and others) *read* it a hundred times.

---

## 📚 Step by step

### 1. Assertions ([Examples/01_Assertions](Examples/01_Assertions/main.cpp))
```cpp
#include <cassert>
assert(index < size && "index out of range");   // checked while running (debug builds)
static_assert(sizeof(int) == 4);                // checked while compiling
```
`assert` documents **"this can never happen, unless there's a bug"**. It's removed in release builds (`-DNDEBUG`),
so never put real work or user-input validation inside it.

### 2. Unit tests ([Examples/02_MiniTestFramework](Examples/02_MiniTestFramework/main.cpp))
A unit test calls one small piece of code with known inputs and checks the output:
```cpp
TEST(add_handles_negatives) {
    CHECK_EQ(add(-2, -3), -5);
}
```
Good tests are **F.I.R.S.T.**: Fast, Independent, Repeatable, Self-checking, Timely.
Test the **happy path**, the **edge cases** (0, empty, max, min), and the **error cases**.
Structure each test as **Arrange → Act → Assert**.

Real projects use a framework. The most common are **GoogleTest**, **Catch2**, and **doctest**, usually wired up with CMake (Lesson 56).

### 3. TDD: red → green → refactor
1. **Red:** write a test for behaviour that doesn't exist yet. Watch it fail.
2. **Green:** write the *simplest* code that passes.
3. **Refactor:** clean up while the tests stay green.
Try it in [Exercises/01_TestDrivenStringUtils](Exercises/01_TestDrivenStringUtils/main.cpp).

### 4. Let the tools find bugs for you
| Tool | Finds | How |
|------|-------|-----|
| Compiler warnings | Uninitialized vars, shadowing, sign mismatch, missing returns | `-Wall -Wextra -Wpedantic -Wshadow -Wconversion`, and `-Werror` to make them errors |
| `clang-tidy` | Modernization, bug patterns, performance issues | `clang-tidy main.cpp -- -std=c++20` (installed in `C:\mingw64\bin`) |
| `clang-format` | Inconsistent style (ends formatting debates!) | `clang-format -i main.cpp`, configured by a `.clang-format` file |
| AddressSanitizer | Out-of-bounds, use-after-free, leaks | `-fsanitize=address` (Linux/macOS, or MSVC on Windows) |
| UndefinedBehaviorSanitizer | Signed overflow, bad shifts, null deref | `-fsanitize=undefined` (Linux/macOS) |
| Debugger | Anything; inspect state | F5 (Lesson 23) |
| Valgrind | Leaks, memory errors | Linux |

### 5. Clean code ([Examples/03_CleanCodeBeforeAfter](Examples/03_CleanCodeBeforeAfter/main.cpp))
| Principle | Bad | Good |
|-----------|-----|------|
| **Names reveal intent** | `int d; // days` | `int daysSinceLastLogin;` |
| **Functions do one thing** | `processData()` 200 lines | `loadOrders()`, `applyDiscounts()`, `printInvoice()` |
| **Few parameters** | `f(a, b, c, d, e, f, true)` | pass a `struct`; avoid boolean flags |
| **DRY**: Don't Repeat Yourself | the same 10 lines in 4 places | one function |
| **Comments explain *why*** | `i++; // increment i` | `// retry: the sensor drops the first reading` |
| **No magic numbers** | `if (status == 3)` | `if (status == OrderStatus::Shipped)` |
| **Early returns** | 5 levels of nested `if` | guard clauses |
| **Const everything** | mutable by default | `const` unless it must change |

**Code smells** (hints that something is wrong): long functions, long parameter lists, duplicated code, deep nesting,
huge classes ("God objects"), comments explaining confusing code (rename it instead), primitive obsession (strings for everything).

---

## 🧾 The Senior Code Review Checklist

Use this on your own code before saying "done":
- [ ] **Correct?** Edge cases (empty, 0, 1, max, negative, invalid input) handled? Tested?
- [ ] **Clear?** Would a teammate understand it in 5 minutes? Names meaningful? Functions short?
- [ ] **Safe?** No raw `new`/`delete`, no dangling references, no UB, no unchecked input, no ignored errors?
- [ ] **Const-correct?** Parameters `const&` where appropriate; member functions `const`?
- [ ] **Warning-free?** Builds clean with `-Wall -Wextra`?
- [ ] **Efficient enough?** No accidental O(n²), no needless copies?
- [ ] **Tested?** Is there a test that would fail if this broke?
- [ ] **Small diff?** One logical change per commit, with a message that explains *why*.

## ⚠️ Common mistakes

- Tests that test nothing (no assertion) or that depend on each other's order.
- Putting side effects inside `assert(...)`, which vanish in release builds.
- "I'll add tests later". Later never comes.
- Clever one-liners that nobody can read.

## 🧠 Senior developer notes

- Aim to make the bug **impossible** (types, `enum class`, `explicit`, RAII) rather than just detectable.
- A bug found by the compiler costs seconds; by a test, minutes; by QA, days; by a customer, reputation. **Shift left.**
- The Boy Scout rule: leave the code a little cleaner than you found it.

## ✅ Check yourself

1. When should you use `assert` vs throwing an exception?
2. What are the three steps of TDD?
3. Name three tools that find bugs without you writing a test.
4. Why is `bool` as a function parameter often a smell?

<details><summary>Answers</summary>

1. `assert` for programmer errors ("impossible" states); exceptions (or `expected`) for things that can legitimately go wrong at run time (bad input, missing files).
2. Red (failing test), Green (make it pass simply), Refactor (clean up with tests green).
3. Compiler warnings, clang-tidy, sanitizers (also the debugger, Valgrind).
4. `setVisible(true, false)` is unreadable at the call site. Prefer an enum or two named functions.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 56: Build Systems and CMake](../56.BuildSystemsAndCMake/README.md)
