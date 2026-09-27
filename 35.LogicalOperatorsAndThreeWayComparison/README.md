# Lesson 35: Comparison Operators and the Spaceship `<=>` (C++20)

> **In one sentence:** Instead of writing six comparison operators (`== != < <= > >=`) by hand,
> C++20 lets you write (or `= default`) just **two**: `==` and the three-way "spaceship" `<=>`.

---

## 🎯 You will learn

- Writing all six comparison operators the old way (and `std::rel_ops`, now deprecated).
- The three-way comparison operator `<=>`.
- Defaulted `==` and `<=>`.
- Custom `==` and custom `<=>`.
- Ordering categories: **strong**, **weak**, **partial**.

---

## 🧸 The Big Idea: one question instead of six

Before, to compare two things you'd ask six questions: *equal? not equal? less? less-or-equal? …*
The spaceship operator asks **one** question: *"how do a and b compare?"* and gets one of three answers:

```
  a <=> b   →   less        (a comes first)
            →   equal       (same place)
            →   greater     (a comes after)
```
From that single answer, the compiler **rewrites** `a < b` as `(a <=> b) < 0`, and so on.

```cpp
struct Version {
    int major, minor, patch;
    auto operator<=>(const Version&) const = default;   // compares major, then minor, then patch
    bool operator==(const Version&) const = default;
};
Version{1, 2, 3} < Version{1, 10, 0};   // true, and we wrote no comparison logic
```

---

## 📚 Step by step

### 1. The old way ([35.2](35.2AllLogicalOperators/main.cpp), [35.3](35.3Rel_OpsNamespace/main.cpp), [35.4](35.4LogicalOperatorsWithImplicitConversions/main.cpp))
Six functions, easy to get inconsistent. `std::rel_ops` generated some from `==` and `<`, but it's deprecated.

### 2. `<=>` basics ([35.5](35.5ThreeWayComparisonOperator/main.cpp))
Works on built-in types: `(3 <=> 5) < 0` is true. The result is an *ordering* object compared against `0`.

### 3. `==` defaulted and custom ([35.6](35.6DefaultedEqualityOperator/main.cpp), [35.7](35.7CustomEqualityOperator/main.cpp))
`bool operator==(const T&) const = default;` compares members in declaration order. From `==`, C++20
also gives you `!=`, and `a == b` works with the arguments swapped.

### 4. Defaulted and custom `<=>` ([35.8](35.8DefaultOrderingWithSpaceship/main.cpp)–[35.12](35.12SpaceshipAsNonMember/main.cpp))
Custom when you want a different order (e.g. compare by length, or case-insensitive):
```cpp
std::strong_ordering operator<=>(const Item& other) const { return price <=> other.price; }
```
Members that don't have `<=>` themselves ([35.9](35.9MembersWithoutSpaceshipOperator/main.cpp)) need you to specify the return type.

### 5. The three ordering categories ([35.13](35.13ZoomingInOnWeakOrderingExample1/main.cpp)–[35.15](35.15ZoomingInOnPartialOrderingExample/main.cpp))

| Category | Meaning | Example |
|----------|---------|---------|
| `std::strong_ordering` | Equal means truly identical, interchangeable | `int`, `std::string` |
| `std::weak_ordering` | "Equivalent" but not identical | case-insensitive text: "ABC" ~ "abc" |
| `std::partial_ordering` | Some pairs can't be compared at all | `double`: `NaN` is neither <, ==, nor > anything |

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [35.2AllLogicalOperators](35.2AllLogicalOperators/main.cpp) | Six operators by hand |
| [35.3Rel_OpsNamespace](35.3Rel_OpsNamespace/main.cpp) | `std::rel_ops` (legacy) |
| [35.4LogicalOperatorsWithImplicitConversions](35.4LogicalOperatorsWithImplicitConversions/main.cpp) | Mixed-type comparisons |
| [35.5ThreeWayComparisonOperator](35.5ThreeWayComparisonOperator/main.cpp) | `<=>` on built-ins |
| [35.6DefaultedEqualityOperator](35.6DefaultedEqualityOperator/main.cpp) | `== default` |
| [35.7CustomEqualityOperator](35.7CustomEqualityOperator/main.cpp) | Custom `==` |
| [35.8DefaultOrderingWithSpaceship](35.8DefaultOrderingWithSpaceship/main.cpp) | `<=> default` |
| [35.9MembersWithoutSpaceshipOperator](35.9MembersWithoutSpaceshipOperator/main.cpp) | Legacy members |
| [35.10CustomSpaceshipOperatorForOrdering](35.10CustomSpaceshipOperatorForOrdering/main.cpp) | Custom `<=>` |
| [35.11LogicalOperatorsSimplified](35.11LogicalOperatorsSimplified/main.cpp) | The C++20 minimum |
| [35.12SpaceshipAsNonMember](35.12SpaceshipAsNonMember/main.cpp) | Non-member `<=>` |
| [35.13](35.13ZoomingInOnWeakOrderingExample1/main.cpp), [35.14](35.14ZoomingInOnWeakOrderingExample2/main.cpp) | Weak ordering |
| [35.15ZoomingInOnPartialOrderingExample](35.15ZoomingInOnPartialOrderingExample/main.cpp) | Partial ordering |

## ⚠️ Common mistakes

- Defining a custom `<=>` but forgetting `==`: a *custom* `<=>` does **not** generate `==`. Only a *defaulted* `<=>` implicitly declares a defaulted `==`.
- Comparing `(a <=> b) == -1`. Compare with `0` instead: `< 0`, `== 0`, `> 0`.
- Claiming `strong_ordering` for something that's really weak (e.g. case-insensitive).

## 🧠 Senior developer notes

- Sorting, `std::set`, `std::map` all rely on `<` being a **strict weak ordering**. A buggy `<` causes crashes in `std::sort`!
- For most value types: `auto operator<=>(const T&) const = default;` is all you need.

## ✅ Check yourself

1. What does `a <=> b` return for ints 3 and 5?
2. Which operators does a defaulted `<=>` give you?
3. Why does `double` use `partial_ordering`?

<details><summary>Answers</summary>

1. `std::strong_ordering::less`.
2. `<`, `<=`, `>`, `>=` (and a defaulted `<=>` also implicitly declares `==`, which gives `!=`).
3. `NaN` compares unordered with everything, even itself.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 36: Inheritance](../36.Inheritance/README.md)
