# Lesson 25: Concepts (C++20)

> **In one sentence:** A concept is a **rule on a template's type**, like "T must be a number",
> so wrong types are rejected with a short, clear message instead of 200 lines of errors.

---

## 🎯 You will learn

- Using standard concepts (`std::integral`, `std::floating_point`, …).
- Four ways to apply a concept.
- Writing your own concepts with `requires` expressions.
- Combining concepts with `&&` and `||`.
- Concepts with `auto`.

---

## 🧸 The Big Idea: a sign on the door

A theme-park ride has a sign: **"You must be at least 140 cm tall."** The attendant checks at
the door, not halfway through the ride.

Templates without concepts let *anyone* on, then crash halfway ("error deep inside
`std::sort`…"). Concepts put **the sign on the door**:

```cpp
#include <concepts>
template <std::integral T>          // sign: "integers only"
T half(T value) { return value / 2; }

half(10);      // ✅
half(2.5);     // ❌ clear error: "2.5 does not satisfy std::integral"
```

---

## 📚 Step by step

### 1. Using concepts: 4 syntaxes ([25.02](25.02UsingConcepts/main.cpp))
```cpp
template <typename T> requires std::integral<T>      // 1. requires clause
T add(T a, T b);

template <std::integral T>                            // 2. constrained parameter
T add(T a, T b);

template <typename T>                                 // 3. trailing requires
T add(T a, T b) requires std::integral<T>;

std::integral auto add(std::integral auto a,          // 4. constrained auto
                       std::integral auto b);
```
Useful standard concepts: `std::integral`, `std::floating_point`, `std::same_as<T,U>`,
`std::convertible_to<T,U>`, `std::totally_ordered`, `std::copyable`, `std::invocable<F, Args...>`.

### 2. Your own concepts ([25.03](25.03BuildingYourOwnConcepts/main.cpp))
```cpp
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
concept Printable = requires(std::ostream& os, T value) {
    os << value;               // "this expression must compile"
};
```

### 3. The `requires` expression in depth ([25.04](25.04ZoomingInOnRequiresClause/main.cpp))
Four kinds of requirements:
```cpp
template <typename T>
concept Container = requires(T c) {
    c.size();                                    // simple: must compile
    typename T::value_type;                      // type: must have this nested type
    { c.size() } -> std::convertible_to<std::size_t>;   // compound: result type check
    requires sizeof(T) > 0;                      // nested: a compile-time bool
};
```

### 4. Combining ([25.05](25.05CombiningConcepts/main.cpp)) and with `auto` ([25.06](25.06ConceptsAndAuto/main.cpp))
`requires Number<T> && Printable<T>`. And variables too: `std::integral auto count = getCount();`

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [25.02UsingConcepts](25.02UsingConcepts/main.cpp) | Standard concepts, 4 syntaxes |
| [25.03BuildingYourOwnConcepts](25.03BuildingYourOwnConcepts/main.cpp) | `concept` + `requires` |
| [25.04ZoomingInOnRequiresClause](25.04ZoomingInOnRequiresClause/main.cpp) | Simple/type/compound/nested requirements |
| [25.05CombiningConcepts](25.05CombiningConcepts/main.cpp) | `&&`, `\|\|` |
| [25.06ConceptsAndAuto](25.06ConceptsAndAuto/main.cpp) | `Concept auto` |

## ⚠️ Common mistakes

- Confusing `requires` **clause** (after the template line: a bool condition) with `requires`
  **expression** (`requires(T x) { ... }`: a list of things that must compile). `requires requires ...` is legal, but ugly.
- Over-constraining: requiring more than the function actually needs.

## 🧠 Senior developer notes

- Concepts are **documentation the compiler checks**. Name them after *what the type can do* (`Sortable`, `Hashable`).
- Concepts also select overloads: a more constrained overload wins over a less constrained one.
- The ranges library (Lesson 46) is built on concepts like `std::ranges::range`.

## ✅ Check yourself

1. What problem do concepts solve?
2. Write a concept `Addable` meaning `a + b` compiles for two T's.
3. Is `std::integral<bool>` true?

<details><summary>Answers</summary>

1. Unclear, late template errors and unconstrained templates; they state requirements up front.
2. `template <typename T> concept Addable = requires(T a, T b) { a + b; };`
3. Yes: `bool` is an integral type (surprise!).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 26: Classes](../26.Classes/README.md)
