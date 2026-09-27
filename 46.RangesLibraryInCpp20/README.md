# Lesson 46: The Ranges Library (C++20)

> **In one sentence:** Ranges let you pass a whole container to an algorithm (no `begin()/end()`)
> and build **lazy pipelines** like `numbers | filter(even) | transform(square) | take(3)`.

---

## 🎯 You will learn

- Range algorithms: `std::ranges::sort(v)`.
- Projections: sort people *by age* without writing a comparator.
- Views and range adaptors: `filter`, `transform`, `take`, `drop`, `reverse`, …
- Composing views with the pipe operator `|`.
- Range factories: `iota`, `single`, `empty`, `istream`.

---

## 🧸 The Big Idea: a factory conveyor belt

```
  numbers ──► [ keep evens ] ──► [ square them ] ──► [ first 3 only ] ──► results
              filter             transform            take
```
Each station is a **view**. Views are **lazy**: nothing happens until someone asks for the next item,
and then each item flows through *all* stations one at a time. No temporary vectors are created.

```cpp
#include <ranges>
std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
auto result = numbers
            | std::views::filter([](int n) { return n % 2 == 0; })
            | std::views::transform([](int n) { return n * n; })
            | std::views::take(3);
for (int x : result) std::cout << x << ' ';   // 4 16 36
```

---

## 📚 Step by step

### 1. Range algorithms ([46.2](46.2RangeAlgorithms/main.cpp), [46.3](46.3RangeLibraryIteratorPairAlgorithms/main.cpp))
`std::ranges::sort(v); std::ranges::find(v, 42); std::ranges::count_if(v, pred);`
They're constrained with concepts, so errors are clearer.

### 2. Projections ([46.4Projections](46.4Projections/main.cpp))
```cpp
std::ranges::sort(people, {}, &Person::age);          // sort by age: {} = default comparison (<)
std::ranges::sort(people, std::greater{}, &Person::age);
auto oldest = std::ranges::max_element(people, {}, &Person::age);
```
A projection says *what to look at* in each element.

### 3. Views and adaptors ([46.5](46.5ViewsAndRangeAdaptors/main.cpp))
| View | Does |
|------|------|
| `views::filter(pred)` | keep matching items |
| `views::transform(f)` | change each item |
| `views::take(n)` / `drop(n)` | first n / skip n |
| `views::take_while` / `drop_while` | while a condition holds |
| `views::reverse` | backwards |
| `views::keys` / `views::values` | from pairs/maps |
| `views::split`, `views::join` | split strings, flatten |

### 4. Composition with `|` ([46.6](46.6ViewCompositionAndPipeOperator/main.cpp))
Read left to right, just like the conveyor belt.

### 5. Factories ([46.7RangeFactories](46.7RangeFactories/main.cpp))
`std::views::iota(1, 11)` = 1..10 without a container. `std::views::iota(1)` = infinite (combine with `take`!).

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [46.2RangeAlgorithms](46.2RangeAlgorithms/main.cpp) | `std::ranges::` algorithms |
| [46.3RangeLibraryIteratorPairAlgorithms](46.3RangeLibraryIteratorPairAlgorithms/main.cpp) | Iterator-pair versions |
| [46.4Projections](46.4Projections/main.cpp) | Projections |
| [46.5ViewsAndRangeAdaptors](46.5ViewsAndRangeAdaptors/main.cpp) | Views |
| [46.6ViewCompositionAndPipeOperator](46.6ViewCompositionAndPipeOperator/main.cpp) | `\|` pipelines |
| [46.7RangeFactories](46.7RangeFactories/main.cpp) | `iota` and friends |

## ⚠️ Common mistakes

- A view **doesn't own** data. Returning a view of a local vector from a function → dangling.
- Views are lazy: a `filter` with side effects may run more times than you expect.
- Need a real container from a pipeline? Loop and `push_back`, or C++23 `std::ranges::to<std::vector>()`.

## 🧠 Senior developer notes

- Pipelines read like a description of the data flow, which is great for reviewers.
- Views are usually as fast as hand-written loops (the compiler fuses them).

## ✅ Check yourself

1. What does "lazy" mean for views?
2. Sort `std::vector<Person>` by `name` with a projection.
3. Print the squares of 1..5 without a container.

<details><summary>Answers</summary>

1. Work happens only when elements are requested, one at a time, with no intermediate containers.
2. `std::ranges::sort(people, {}, &Person::name);`
3. `for (int x : std::views::iota(1, 6) | std::views::transform([](int n){ return n*n; })) std::cout << x;`
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 47: Building Iterators for Custom Containers](../47.BuildingIteratorsForCustomContainers/README.md)
