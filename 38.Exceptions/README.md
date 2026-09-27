# Lesson 38: Exceptions

> **In one sentence:** An exception is an **emergency signal**: when something goes wrong deep
> inside your program, you `throw`, and the nearest matching `catch` further up handles it,
> skipping everything in between.

---

## 🎯 You will learn

- `try`, `throw`, `catch`, and why exceptions exist.
- Handling at different levels; multiple and nested handlers.
- Throwing class objects and exception hierarchies (catch by reference!).
- Rethrowing, `catch (...)`, `std::terminate`.
- `noexcept`; exceptions in destructors.
- Standard exceptions (`std::runtime_error`, `std::out_of_range`, …) and making your own.

---

## 🧸 The Big Idea: the fire alarm

When a fire starts in a room (an error deep in a function), you don't finish your homework first.
You pull the **alarm** (`throw`). Everyone **stops what they're doing** and leaves each room
(functions exit; their local objects are properly destroyed) until they reach someone trained
to handle it: the **fire brigade** (`catch`).

```cpp
double divide(double a, double b)
{
    if (b == 0) throw std::invalid_argument{"division by zero"};   // 🚨 pull the alarm
    return a / b;
}

try {
    std::cout << divide(10, 0);        // never prints
} catch (const std::invalid_argument& e) {
    std::cout << "Error: " << e.what() << '\n';   // 🚒 handled here
}
```

---

## 📚 Step by step

### 1. Why exceptions? ([38.2](38.2TryCatchBlocks/main.cpp), [38.3](38.3TheNeedForExceptions/main.cpp))
Error codes can be ignored silently, and they clutter every call. Constructors can't return an error code at all.
Exceptions **can't be ignored**: unhandled, the program terminates.

### 2. Different levels ([38.4](38.4HandlingExceptionsAtDifferentLevels/main.cpp))
The exception travels up the call stack (**stack unwinding**) until a matching `catch`. Every local object on the way
is destroyed properly, which is why RAII (smart pointers, etc.) makes exception code leak-free.

### 3. Multiple & nested handlers ([38.5](38.5MultipleHandlersForExceptions/main.cpp), [38.6](38.6NestedTryBlocks/main.cpp))
`catch` blocks are tried **top to bottom**. Put the **most specific** first, general last.

### 4. Class objects & hierarchies ([38.7](38.7ThrowingClassObjects/main.cpp)–[38.9](38.9PolymorphicExceptions/main.cpp))
**Throw by value, catch by `const` reference.** Catching by value slices derived exceptions.

### 5. Rethrow, catch-all, terminate ([38.10](38.10RethrownExceptions/main.cpp)–[38.12](38.12EllipsisCatchAllBlock/main.cpp))
- `throw;` (empty) rethrows the *current* exception unchanged. `throw e;` would slice/copy it.
- `catch (...)` catches anything (you can't inspect it). Use it as a last resort, e.g. at the top of `main`.
- No handler at all → `std::terminate()` → the program aborts. `std::set_terminate` customizes that.

### 6. `noexcept` ([38.13](38.13NoexceptSpecifier/main.cpp)) and destructors ([38.14](38.14ExceptionsInDestructors/main.cpp))
`void f() noexcept;` promises "I never throw". If it does anyway → terminate. The STL uses it to choose
faster moves (Lesson 41). **Destructors are `noexcept` by default. Never let an exception escape a destructor.**

### 7. Standard exceptions ([38.16](38.16CatchingStandardExceptions/main.cpp)–[38.18](38.18DerivingFromStandardExceptions/main.cpp))
```
std::exception
├── std::logic_error      (bugs you could have prevented)
│   ├── std::invalid_argument
│   ├── std::out_of_range         ← vector.at(99), string.at(99)
│   └── std::length_error
├── std::runtime_error    (things that happen at run time)
│   ├── std::overflow_error
│   └── std::range_error
├── std::bad_alloc        ← new failed
└── std::bad_cast         ← dynamic_cast to a reference failed
```
Your own: `class InsufficientFunds : public std::runtime_error { using std::runtime_error::runtime_error; };`

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [38.2TryCatchBlocks](38.2TryCatchBlocks/main.cpp) | Basic try/catch |
| [38.3TheNeedForExceptions](38.3TheNeedForExceptions/main.cpp) | Why not error codes |
| [38.4HandlingExceptionsAtDifferentLevels](38.4HandlingExceptionsAtDifferentLevels/main.cpp) | Stack unwinding |
| [38.5MultipleHandlersForExceptions](38.5MultipleHandlersForExceptions/main.cpp) | Several catch blocks |
| [38.6NestedTryBlocks](38.6NestedTryBlocks/main.cpp) | try inside try |
| [38.7ThrowingClassObjects](38.7ThrowingClassObjects/main.cpp) | Custom exception objects |
| [38.8ExceptionsAsClassObjectsWithInheritanceHierarchies](38.8ExceptionsAsClassObjectsWithInheritanceHierarchies/main.cpp) | Order of handlers |
| [38.9PolymorphicExceptions](38.9PolymorphicExceptions/main.cpp) | Catch by reference |
| [38.10RethrownExceptions](38.10RethrownExceptions/main.cpp) | `throw;` |
| [38.11ProgramCustomTermimation](38.11ProgramCustomTermimation/main.cpp) | `std::set_terminate` |
| [38.12EllipsisCatchAllBlock](38.12EllipsisCatchAllBlock/main.cpp) | `catch (...)` |
| [38.13NoexceptSpecifier](38.13NoexceptSpecifier/main.cpp) | `noexcept` |
| [38.14ExceptionsInDestructors](38.14ExceptionsInDestructors/main.cpp) | Why destructors mustn't throw |
| [38.16CatchingStandardExceptions](38.16CatchingStandardExceptions/main.cpp) | Standard hierarchy |
| [38.17ThrowingStdExceptions](38.17ThrowingStdExceptions/main.cpp) | Throwing `std::` types |
| [38.18DerivingFromStandardExceptions](38.18DerivingFromStandardExceptions/main.cpp) | Your own exception classes |

## ⚠️ Common mistakes

- Catching by value (`catch (std::exception e)`), which slices.
- `catch (...)` that silently swallows errors.
- Using exceptions for normal control flow (e.g. to exit a loop).
- Throwing from destructors.
- Raw `new` + exception in between → leak. Use smart pointers.

## 🧠 Senior developer notes

- **Exception safety guarantees** (know these for interviews):
  - *No-throw*: never fails (`noexcept`).
  - *Strong*: if it fails, the state is unchanged, as if nothing happened (copy-and-swap, Lesson 52).
  - *Basic*: if it fails, no leaks and objects are still valid (but maybe changed).
- Exceptions are for **exceptional** situations. For expected failures ("user not found") prefer
  `std::optional` or `std::expected` (Lesson 51).
- Some domains (games, embedded) compile with `-fno-exceptions`. Know both styles.

## ✅ Check yourself

1. Why catch by `const&`?
2. What happens to local objects when an exception passes through a function?
3. Difference between `throw;` and `throw e;` in a catch block?
4. Which should be listed first: `catch (const std::exception&)` or `catch (const std::out_of_range&)`?

<details><summary>Answers</summary>

1. No copy, no slicing: virtual `what()` gives the real message.
2. They are destroyed (destructors run) during stack unwinding.
3. `throw;` rethrows the original object; `throw e;` throws a (possibly sliced) copy.
4. `out_of_range` first (more specific). Otherwise the general handler catches everything.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 39: Practice: Box Container](../39.Practice-BoxContainerType/README.md)
