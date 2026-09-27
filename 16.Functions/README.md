# Lesson 16: Functions

> **In one sentence:** A function is a **named, reusable machine**: you feed it inputs
> (parameters), it does one job, and hands back a result. Good functions are the building blocks
> of all good software.

---

## 🎯 You will learn

- Declaring vs defining functions; splitting code over multiple files.
- The 4 ways to pass data in: **by value, by pointer, by reference, by const reference**.
- Passing arrays (and why they "forget" their size).
- Default parameters, implicit conversions at call sites.
- `std::string_view` parameters.
- `constexpr` and `consteval` functions.

---

## 🧸 The Big Idea: a juice machine

```
   inputs (arguments)         the machine (function body)        output (return value)
   🍊 🍊 🍊  ─────────────►  ┌──────────────────────────┐ ─────► 🥤
                             │ double makeJuice(int n)  │
                             └──────────────────────────┘
```

You don't need to know **how** the machine squeezes oranges to **use** it. That's the power of
functions: **hide details behind a name**. `sortStudents(list)` is readable; 40 lines of loops are not.

---

## 📚 Step by step

### 1. Anatomy ([16.2](16.2FirstHandOnCppFunctions/main.cpp))
```cpp
//  return type   name     parameters
    double        average (double a, double b)
{
    return (a + b) / 2;        // hand the result back
}
average(3, 5);                 // call: 3 and 5 are the ARGUMENTS
```
`void` means "returns nothing".

### 2. Declaration vs definition ([16.3](16.3FunctionDeclarationsAndDefinitions/main.cpp), [16.4](16.4MultipleFiles_CompilationModelRevisited/main.cpp))
- **Declaration** (prototype): "this function exists": `double average(double a, double b);`
- **Definition**: the body.

The compiler reads top to bottom, so a function must be *declared* before it's called. In real
projects declarations go in **header files (`.h`)** and definitions in **`.cpp` files** (see 16.4, which has 4 files).

### 3. The four ways to pass arguments ⭐ (the most important table in this lesson)

| Style | Syntax | Copies? | Can change caller's variable? | Use when |
|-------|--------|---------|-------------------------------|----------|
| By value | `f(int x)` | Yes | No | Small types (`int`, `double`, `char`) |
| By pointer | `f(int* x)` | No | Yes | "nothing" (`nullptr`) is a valid option; C APIs |
| By reference | `f(int& x)` | No | **Yes** | You *want* to change the caller's variable |
| By const reference | `f(const std::string& x)` | No | No | **Big** objects you only read |

Examples: [16.5 value](16.5PassByValue/main.cpp) · [16.6 const value](16.6PassByConstValue/main.cpp) ·
[16.7 pointer](16.7PassByPointer/main.cpp) · [16.8 pointer to const](16.8PassByPointerToConst/main.cpp) ·
[16.9 const pointer to const](16.9PassByConstPointerToConst/main.cpp) · [16.10 reference](16.10PassByReference/main.cpp) ·
[16.11 const reference](16.11PassByConstReference/main.cpp)

Kid version:
- **By value** = giving someone a **photocopy** of your drawing. They can scribble on it; your original is safe.
- **By reference** = handing them **your actual drawing**. Their scribbles are on your drawing.
- **By const reference** = letting them **look at your drawing through glass**. No copy needed, and it's safe.

### 4. Arrays as parameters ([16.13](16.13ArrayFunctionParameters/main.cpp)–[16.16](16.16MultiDimensionalArrayFunctionParameters/main.cpp))
`void f(int arr[])` is really `void f(int* arr)`: the array **decays** and the size is lost,
so you must pass the size too. Passing `int (&arr)[5]` keeps the size but only accepts size 5.
Modern answer: `std::span<int>` (C++20, Lesson 51) or `std::vector<int>&`.

### 5. Default parameters ([16.17](16.17DefaultFunctionParameters/main.cpp))
```cpp
void greet(std::string_view name, int times = 1);
greet("Ada");        // times = 1
greet("Ada", 3);
```
Defaults go at the **end** of the parameter list, and in the **declaration** (not repeated in the definition).

### 6. Implicit conversions at the call ([16.18](16.18ImplicitConversions/main.cpp)–[16.22](16.22ImplicitConversionsFromStringViewToString/main.cpp))
Passing `3.9` to an `int` parameter silently becomes `3`. A non-const reference `int&` will **not** bind to a `double`,
but `const int&` binds to a temporary copy. `std::string_view` → `std::string` needs an explicit conversion.

### 7. `constexpr` / `consteval` functions ([16.23](16.23constexprFunctions/main.cpp), [16.24](16.24constevalFunctions/main.cpp))
`constexpr`: *may* run at compile time. `consteval`: *must* run at compile time.

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [16.2FirstHandOnCppFunctions](16.2FirstHandOnCppFunctions/main.cpp) | Writing & calling |
| [16.3FunctionDeclarationsAndDefinitions](16.3FunctionDeclarationsAndDefinitions/main.cpp) | Prototypes |
| [16.4MultipleFiles_CompilationModelRevisited](16.4MultipleFiles_CompilationModelRevisited/main.cpp) | `.h` + `.cpp` split |
| [16.5](16.5PassByValue/main.cpp) – [16.11](16.11PassByConstReference/main.cpp) | Parameter passing styles |
| [16.13](16.13ArrayFunctionParameters/main.cpp) – [16.16](16.16MultiDimensionalArrayFunctionParameters/main.cpp) | Arrays as parameters |
| [16.17DefaultFunctionParameters](16.17DefaultFunctionParameters/main.cpp) | Defaults |
| [16.18](16.18ImplicitConversions/main.cpp) – [16.22](16.22ImplicitConversionsFromStringViewToString/main.cpp) | Conversions at call sites |
| [16.23constexprFunctions](16.23constexprFunctions/main.cpp), [16.24constevalFunctions](16.24constevalFunctions/main.cpp) | Compile-time functions |

## ⚠️ Common mistakes

- Passing `std::string`/`std::vector` **by value** by habit, which copies everything, every call.
- Expecting a by-value parameter change to affect the caller.
- Forgetting to `return` in a non-void function: UB, and `-Wall` warns you.
- Calling a function before it's declared.

## 🧠 Senior developer notes

- **A function should do ONE thing**, and its name should say what. If you need "and" in the name, split it.
- Keep functions short (roughly: fits on a screen). Long functions hide bugs.
- Prefer **returning** values over output parameters (Lesson 19).
- Pure functions (no side effects, same input → same output) are the easiest to test and reason about.
- Name booleans as questions: `isValid`, `hasPermission`.

## ✅ Check yourself

1. Which passing style for: (a) an `int` you only read, (b) a `std::vector` you only read, (c) a counter you want to increase?
2. Why must you pass an array's size separately?
3. Where do default arguments go?
4. What's the difference between a declaration and a definition?

<details><summary>Answers</summary>

1. (a) by value, (b) `const std::vector<T>&`, (c) `int&`.
2. The array decays to a pointer, and a pointer doesn't know how many elements follow it.
3. At the end of the parameter list, in the declaration.
4. A declaration announces the function's signature; a definition provides its body.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 17: Enums and Type Aliases](../17.EnumsAndTypeAliases/README.md)
