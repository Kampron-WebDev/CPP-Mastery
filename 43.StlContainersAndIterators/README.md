# Lesson 43: STL Containers and Iterators

> **In one sentence:** The Standard Template Library gives you ready-made, battle-tested
> containers (`std::vector`, `std::array`, …) and **iterators**, universal "fingers" that point
> into any container, so one algorithm can work on all of them.

---

## 🎯 You will learn

- `std::vector` (growable) and `std::array` (fixed).
- Iterators: `begin()`, `end()`, `*it`, `++it`.
- Traversing parts of a container; reverse and constant iterators.
- `std::begin` / `std::end` for any range, even raw arrays.

---

## 🧸 The Big Idea: containers and a pointing finger

- A **container** is a box that stores many things and manages its own memory (no `new`/`delete`!).
- An **iterator** is your **finger** pointing at one item. `*it` = "the item under my finger",
  `++it` = "move my finger to the next item".
- `begin()` = finger on the first item. `end()` = finger **one past the last** item (a "stop" sign, never read it).

```
  v:   [ 10 ][ 20 ][ 30 ][ 40 ]  ▢
         ▲                        ▲
      begin()                   end()   (one past the last)

  for (auto it = v.begin(); it != v.end(); ++it) std::cout << *it;
```
That's exactly the pointer walk from Lesson 13, generalised to *every* container.

---

## 📚 Step by step

### 1. `std::vector` ([43.2StdVector](43.2StdVector/main.cpp))
```cpp
#include <vector>
std::vector<int> v{1, 2, 3};
v.push_back(4);          // add at the end (grows automatically)
v.size();  v.empty();  v.front();  v.back();
v[0];      v.at(0);      // at() checks bounds and throws std::out_of_range
v.pop_back();  v.clear();
v.reserve(1000);         // pre-allocate if you know the size: avoids regrowth
```
**Your default container.** Contiguous memory, cache-friendly, fast.

### 2. `std::array` ([43.3StdArray](43.3StdArray/main.cpp))
`std::array<int, 5> a{};`: a raw array with manners. Fixed size, knows `size()`, can be copied and compared, lives on the stack.

### 3. Iterators ([43.4](43.4Iterators/main.cpp), [43.5](43.5TraversingContainerSubsetsWithIterators/main.cpp))
```cpp
auto it = v.begin() + 1;              // second element (random-access iterators allow +)
for (; it != v.end() - 1; ++it) ...   // a subset: skip first and last
```

### 4. Reverse and const iterators ([43.6](43.6ReverseIterators/main.cpp), [43.7](43.7ContantIterators/main.cpp))
- `rbegin()`/`rend()`: walk backwards.
- `cbegin()`/`cend()`: read-only fingers. You can't modify through them.

### 5. `std::begin` / `std::end` ([43.9](43.9StdBeginStdEnd/main.cpp))
Work for containers **and** raw arrays, so generic code uses them.

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [43.2StdVector](43.2StdVector/main.cpp) | `std::vector` basics |
| [43.3StdArray](43.3StdArray/main.cpp) | `std::array` |
| [43.4Iterators](43.4Iterators/main.cpp) | `begin`, `end`, `*`, `++` |
| [43.5TraversingContainerSubsetsWithIterators](43.5TraversingContainerSubsetsWithIterators/main.cpp) | Partial ranges |
| [43.6ReverseIterators](43.6ReverseIterators/main.cpp) | `rbegin`/`rend` |
| [43.7ContantIterators](43.7ContantIterators/main.cpp) | `cbegin`/`cend` |
| [43.9StdBeginStdEnd](43.9StdBeginStdEnd/main.cpp) | Free functions |

## ⚠️ Common mistakes

- **Iterator invalidation:** `push_back` may reallocate, and then *all* old iterators/pointers/references into the vector dangle.
- Dereferencing `end()`.
- Erasing inside a range-for loop. Use the erase-remove idiom or C++20 `std::erase_if(v, pred)`.
- `v[i]` with a bad index (no check) when you meant `v.at(i)`.

## 🧠 Senior developer notes

- "When in doubt, use `std::vector`": Bjarne Stroustrup. Even for searches, a sorted vector often beats fancier structures thanks to the CPU cache.
- Pass containers as `const std::vector<T>&` (or `std::span<const T>`, Lesson 51).
- `emplace_back(args...)` builds the element in place (no temporary).

## ✅ Check yourself

1. What does `end()` point to?
2. Why can `push_back` break an iterator you saved earlier?
3. Difference between `v[5]` and `v.at(5)`?

<details><summary>Answers</summary>

1. One past the last element (never dereference it).
2. If capacity runs out, the vector moves to a new memory block; old iterators point to freed memory.
3. `at` checks bounds and throws `std::out_of_range`; `[]` doesn't check (UB if out of range).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 44: Zooming in on STL Containers](../44.ZoomingOnSTLContainers/README.md)
