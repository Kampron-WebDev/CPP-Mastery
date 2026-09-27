# Lesson 17: Enums and Type Aliases

> **In one sentence:** An **enum** gives names to a fixed set of choices (like `Red`, `Amber`,
> `Green`), and a **type alias** gives a shorter or clearer name to an existing type.

---

## 🎯 You will learn

- `enum class` (scoped enums): the modern, safe kind.
- `using enum` (C++20).
- Old-style `enum` and why it's riskier.
- Type aliases with `using` (and old `typedef`).

---

## 🧸 The Big Idea: a menu with fixed choices

A traffic light can only be **red, amber or green**. If you store it as an `int` (0, 1, 2),
someone could write `light = 57`. What does 57 mean? Nothing, and that's a bug waiting to happen.

```cpp
enum class Light { Red, Amber, Green };
Light now = Light::Red;     // readable, and only valid values allowed
// now = 57;                // ❌ compile error. Protected!
```

---

## 📚 Step by step

### 1. `enum class` ([17.2EnumClasses](17.2EnumClasses/main.cpp))
```cpp
enum class Month : unsigned char { Jan = 1, Feb, Mar /* ... */ };   // Feb = 2, Mar = 3 ...
Month m = Month::Feb;
int n = static_cast<int>(m);   // 2 (you must convert explicitly)
```
- Names are **scoped**: you write `Month::Feb`, so no clashes with other enums.
- No silent conversion to `int`.
- `: unsigned char` picks the underlying type (saves memory).

Great with `switch`: with `-Wall` the compiler warns if you forget a case.

### 2. `using enum` ([17.3UsingEnum](17.3UsingEnum/main.cpp))
Inside a `switch`, writing `Month::` everywhere is noisy. C++20:
```cpp
switch (m) {
    using enum Month;
    case Jan: ...; break;
    case Feb: ...; break;
}
```

### 3. Old enums ([17.4OldEnums](17.4OldEnums/main.cpp))
`enum Color { Red, Green };`: the names leak into the surrounding scope, and they silently convert to `int`,
so `Color::Red == Fruit::Apple` might compile. Use `enum class` in new code.

### 4. Type aliases ([17.5TypeAliases](17.5TypeAliases/main.cpp))
```cpp
using Score = unsigned long long;                 // modern
typedef unsigned long long Score;                 // old style, same effect
using StudentMap = std::map<std::string, std::vector<int>>;   // tame long names
```
An alias is **not** a new type, just a new name. `Score` and `unsigned long long` are interchangeable.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [17.2EnumClasses](17.2EnumClasses/main.cpp) | Scoped enums, underlying type, `switch` |
| [17.3UsingEnum](17.3UsingEnum/main.cpp) | `using enum` inside `switch` |
| [17.4OldEnums](17.4OldEnums/main.cpp) | Unscoped enums and their problems |
| [17.5TypeAliases](17.5TypeAliases/main.cpp) | `using` / `typedef` |

## ⚠️ Common mistakes

- Trying to `std::cout << Month::Feb` directly: there's no automatic printing. Write a `toString` function.
- Adding a new enum value but forgetting to update the `switch` statements (keep `-Wall` on to be warned).

## 🧠 Senior developer notes

- Replace "stringly-typed" and "magic-int" code (`status == "ok"`, `mode == 3`) with enums.
- Enums are perfect for **state machines** (game states, order status: `Pending → Paid → Shipped`).
- Bit-flag enums: `enum class Perm : unsigned { Read = 1, Write = 2, Exec = 4 };` plus overloaded `|` (Lesson 34).

## ✅ Check yourself

1. Two advantages of `enum class` over plain `enum`?
2. How do you get the number behind an `enum class` value?
3. Is `using Meters = double;` a new type?

<details><summary>Answers</summary>

1. Scoped names (no clashes) and no implicit conversion to int.
2. `static_cast<int>(value)` (or `std::to_underlying` in C++23).
3. No, it's just another name for `double`.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 18: Arguments to main](../18.ArgumentsToTheMainFunction/README.md)
