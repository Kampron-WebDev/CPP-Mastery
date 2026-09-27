# Lesson 20: Function Overloading

> **In one sentence:** Overloading lets several functions **share one name** as long as their
> parameter lists differ, and the compiler picks the right one by looking at the arguments.

---

## 🎯 You will learn

- Overloading on number and types of parameters.
- Overloading with pointers, references, and `const`.
- Which overloads are allowed and which are ambiguous.
- Overloads combined with default parameters.

---

## 🧸 The Big Idea: one word, many meanings

"Play" means different things: *play football*, *play the piano*, *play a song*. You know which
one by looking at **what comes after** the word. The compiler does the same:

```cpp
void print(int x)               { std::cout << "int: " << x; }
void print(double x)            { std::cout << "double: " << x; }
void print(std::string_view s)  { std::cout << "text: " << s; }

print(5);        // int version
print(2.5);      // double version
print("hi");     // text version
```

The parameter list (types, count, order) is the function's **signature**. The **return type is NOT part of it**:
`int f();` and `double f();` can't coexist, because the compiler couldn't tell which one you mean when you call `f()`.

---

## 📚 Step by step

### 1. Different parameters ([20.2](20.2OverloadingWithDifferentParameters/main.cpp))
Different **number** or **types** of parameters: ✅ allowed.

### 2. Pointers and references ([20.3](20.3OverloadingWithPointerParameters/main.cpp), [20.4](20.4OverloadingWithReferenceParameters/main.cpp))
`f(int*)` and `f(double*)` are different. `f(int&)` and `f(double&)` too.

### 3. `const` rules ([20.5](20.5OverloadingWithConstParametersByValue/main.cpp)–[20.7](20.7OverloadingWithConstReferences/main.cpp))
| Pair | Allowed? | Why |
|------|----------|-----|
| `f(int)` and `f(const int)` | ❌ | By value, it's a copy either way; const doesn't matter to the caller |
| `f(int*)` and `f(const int*)` | ✅ | Pointer-to-const is a different type |
| `f(int* const)` and `f(int*)` | ❌ | The pointer itself is copied |
| `f(int&)` and `f(const int&)` | ✅ | Non-const lvalues pick `int&`; consts and temporaries pick `const int&` |

### 4. With default parameters ([20.8](20.8OverloadsWithDefaultParameters/main.cpp))
`void f(int a, int b = 5);` plus `void f(int a);` makes `f(1)` **ambiguous**: which one? The compiler refuses.

### How the compiler chooses (simplified)
1. **Exact match** wins.
2. Then **promotions** (`char` → `int`, `float` → `double`).
3. Then **standard conversions** (`int` → `double`, etc.).
4. If two candidates tie → **ambiguous** error.

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [20.2OverloadingWithDifferentParameters](20.2OverloadingWithDifferentParameters/main.cpp) | Basics |
| [20.3OverloadingWithPointerParameters](20.3OverloadingWithPointerParameters/main.cpp) | Pointer overloads |
| [20.4OverloadingWithReferenceParameters](20.4OverloadingWithReferenceParameters/main.cpp) | Reference overloads |
| [20.5OverloadingWithConstParametersByValue](20.5OverloadingWithConstParametersByValue/main.cpp) | Why top-level const doesn't count |
| [20.6OverloadingWithConstPointerAndPointerToConstParameters](20.6OverloadingWithConstPointerAndPointerToConstParameters/main.cpp) | Pointer const-ness |
| [20.7OverloadingWithConstReferences](20.7OverloadingWithConstReferences/main.cpp) | `T&` vs `const T&` |
| [20.8OverloadsWithDefaultParameters](20.8OverloadsWithDefaultParameters/main.cpp) | Ambiguity traps |

## ⚠️ Common mistakes

- Trying to overload only on return type.
- `print(0)` when you have `print(int*)` and `print(long)`: surprising choices. Use `nullptr` for pointers.
- Too many overloads that do *different* things. Overloads should do **the same job** for different types.

## 🧠 Senior developer notes

- If many overloads have identical bodies, you want a **template** (Lesson 24).
- Overloading `T&` + `const T&` is the ancestor of move semantics' `T&&` overloads (Lesson 41).

## ✅ Check yourself

1. Can `int area(int)` and `double area(int)` both exist?
2. Is `f(int)` + `f(const int)` legal?
3. With `f(double)` and `f(long)`, what does `f(5)` do?

<details><summary>Answers</summary>

1. No, because the return type isn't part of the signature.
2. No: both take a copy, so they're the same signature.
3. Ambiguous: `int → double` and `int → long` are both standard conversions of the same rank.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 21: Lambda Functions](../21.LambdaFunctions/README.md)
