# Lesson 14: References

> **In one sentence:** A reference is a **second name (a nickname)** for an existing variable.
> Whatever you do to the nickname happens to the original.

---

## 🎯 You will learn

- Declaring and using references.
- References vs pointers.
- `const` references.
- References in range-based `for` loops.

---

## 🧸 The Big Idea: nicknames

Your friend Robert is also called "Bob". If you give Bob a hat, **Robert** is wearing a hat.
There's only one person; there are two names.

```cpp
int robert{10};
int& bob{robert};    // bob is ANOTHER NAME for robert (not a copy!)
bob = 20;
std::cout << robert; // 20
```

```
        ┌──────────────┐
 robert │      20      │ ◄── bob (same box, second label)
        └──────────────┘
```

---

## 📚 Step by step

### 1. Declaring ([14.2](14.2.DeclaringAndUsingReferences/main.cpp))
- A reference **must** be initialized when created: `int& r;` is an error.
- It can **never** be re-pointed to another variable. `r = other;` copies other's **value** into the original.
- It can't be null.

### 2. References vs pointers ([14.3](14.3.ComparingPointersAndReferences/main.cpp))
| | Pointer `int*` | Reference `int&` |
|---|---|---|
| Can be null? | Yes (`nullptr`) | No |
| Can change what it refers to? | Yes | No |
| Must be initialized? | No (but should be) | Yes |
| Syntax to use | `*p` | just `r` |
| Arithmetic? | Yes | No |

Rule of thumb: **use a reference when you can, a pointer when you must** (when "nothing" is a valid option, or you need to re-point).

### 3. `const` references ([14.4](14.4.ReferencesAndConst/main.cpp))
`const int& r{x};` is a **read-only** nickname: you can look but not touch. This becomes
*hugely* important in Lesson 16: passing a big object by `const&` avoids copying it.

### 4. References in loops ([14.5](14.5.ReferencesWithRangeBasedForLoops/main.cpp))
```cpp
int scores[]{70, 80, 90};
for (int s : scores) s += 5;          // ❌ changes COPIES: array unchanged
for (int& s : scores) s += 5;         // ✅ changes the real elements
for (const auto& s : scores) print(s);// ✅ read-only, no copies: best for big objects
```

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [14.2.DeclaringAndUsingReferences](14.2.DeclaringAndUsingReferences/main.cpp) | Same address, same value |
| [14.3.ComparingPointersAndReferences](14.3.ComparingPointersAndReferences/main.cpp) | Side-by-side comparison |
| [14.4.ReferencesAndConst](14.4.ReferencesAndConst/main.cpp) | Read-only references |
| [14.5.ReferencesWithRangeBasedForLoops](14.5.ReferencesWithRangeBasedForLoops/main.cpp) | `for (auto&)` vs `for (auto)` |

## ⚠️ Common mistakes

- Forgetting the `&` in a `for` loop and wondering why nothing changed.
- Returning a reference to a local variable (dangling reference, like the dangling pointer).
- Thinking `r = other;` makes r refer to `other`. It **copies the value**.

## 🧠 Senior developer notes

- Default loop style for reading: `for (const auto& item : items)`.
- Pass "big" things (`std::string`, `std::vector`, your classes) as `const T&` to functions;
  pass small things (`int`, `double`, `char`) by value.

## ✅ Check yourself

1. `int a{1}; int& r{a}; r = 5;` What is a?
2. `int a{1}, b{2}; int& r{a}; r = b; b = 9;` What are a and r?
3. Why does `for (int x : arr) x = 0;` leave arr unchanged?

<details><summary>Answers</summary>

1. 5.
2. a = 2, r = 2 (r still refers to a; `r = b` only copied 2).
3. `x` is a copy of each element; use `int&`.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 15: Characters and Strings](../15.CharacterManipulationAndStrings/README.md)
