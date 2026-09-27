# Lesson 06: Literals and Constants

> **In one sentence:** A *literal* is a value typed straight into your code (`42`, `3.14`, `'A'`),
> and a *constant* is a box you lock after filling it, so nobody can change it by accident.

---

## 🎯 You will learn

- Literal suffixes: `u`, `l`, `ll`, `f`, and digit separators `1'000'000`.
- `const`: "this never changes after it's created".
- `constexpr`: "work this out while **compiling**, not while running".
- `consteval` and `constinit` (C++20).

---

## 🧸 The Big Idea

Think of a birthday cake recipe:
- The **number of eggs (3)** written in the recipe is a **literal**.
- **"Oven temperature: 180°C. DO NOT CHANGE"** is a **constant**. If someone tries to change it,
  the compiler stops them.
- **`constexpr`** is like a recipe that says *"2 × 90°C"*. The chef works it out **before**
  cooking starts (at compile time), so no time is wasted while cooking (at run time).

---

## 📚 Step by step

### 1. Literals ([6.2Literals](6.2Literals/main.cpp))
```cpp
42        // int
42u       // unsigned int
42l, 42ll // long, long long
3.14      // double
3.14f     // float
'A'       // char
"Hello"   // string literal (an array of chars ending in '\0')
true      // bool
0x2A 052 0b101010   // hex, octal, binary: all equal 42
1'000'000 // digit separators: easier to read, same number
```

### 2. `const` ([6.3Constants](6.3Constants/main.cpp))
```cpp
const double pi{3.14159};
pi = 3;            // ❌ compile error: good! You're protected.
```
> 🧠 **Senior rule:** make everything `const` unless it needs to change. It documents intent and
> prevents whole families of bugs. Many pros read "not const" as "watch out, this changes later".

### 3. `constexpr` ([6.4ConstantExpressions](6.4ConstantExpressions/main.cpp))
```cpp
constexpr int secondsPerDay = 24 * 60 * 60;   // computed by the COMPILER
static_assert(secondsPerDay == 86400);        // checked at compile time. Wrong = build fails.

constexpr int square(int x) { return x * x; }
constexpr int area = square(12);              // 144, computed before the program ever runs
```
`const` means *won't change*. `constexpr` means *known at compile time* (and therefore also won't change).

### 4. `consteval` and `constinit` ([6.5constinit](6.5constinit/main.cpp))
- `consteval` function: **must** run at compile time (an "immediate function").
- `constinit` variable: **must** be initialized at compile time, but can change later. It
  prevents the "static initialization order fiasco" (Lesson 32).

| Keyword | Can change later? | Must be known at compile time? |
|---------|-------------------|--------------------------------|
| `const` | No | No |
| `constexpr` | No | Yes |
| `constinit` | **Yes** | Its *starting* value, yes |
| `consteval` (functions) | n/a | Always runs at compile time |

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [6.2Literals](6.2Literals/main.cpp) | Suffixes, prefixes, separators |
| [6.3Constants](6.3Constants/main.cpp) | `const` variables |
| [6.4ConstantExpressions](6.4ConstantExpressions/main.cpp) | `constexpr`, `static_assert` |
| [6.5constinit](6.5constinit/main.cpp) | `constinit` / `consteval` |

## ⚠️ Common mistakes

- **Magic numbers:** `if (speed > 88)`. What is 88? Write `constexpr int timeTravelSpeed{88};`.
- `3.14f` vs `3.14`: mixing float and double silently loses precision.
- Forgetting a `const` variable **must** be initialized when it is declared.

## 🧠 Senior developer notes

- Use `constexpr` for configuration values and lookup tables. It is free at run time.
- `static_assert` is a test that runs while you compile. Use it to guard assumptions:
  `static_assert(sizeof(int) == 4, "this code assumes 32-bit int");`

## ✅ Check yourself

1. What is the type of `5u`? Of `2.0f`?
2. Difference between `const` and `constexpr`?
3. Can a `constinit` variable be changed later?
4. What happens if a `static_assert` condition is false?

<details><summary>Answers</summary>

1. `unsigned int`; `float`.
2. `const` = can't change; `constexpr` = can't change **and** value is known at compile time.
3. Yes. Only its initial value must be compile-time.
4. The build fails with your message.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 07: Conversions, Overflow and Underflow](../07.ConversionsOverflowAndUnderflow/README.md)
