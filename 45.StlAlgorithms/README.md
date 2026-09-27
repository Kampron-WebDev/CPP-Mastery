# Lesson 45: STL Algorithms

> **In one sentence:** `<algorithm>` has over 100 ready-made, optimized, bug-free loops (find,
> sort, count, copy, transform…), and using them makes code shorter, faster and clearer.

---

## 🎯 You will learn

- `std::all_of`, `any_of`, `none_of`.
- `std::for_each`.
- `std::max_element`, `min_element`.
- `std::find`, `find_if`.
- `std::copy`, `copy_if`.
- `std::sort` (with custom comparators).
- `std::transform`.
- And a tour of more algorithms worth knowing.

---

## 🧸 The Big Idea: power tools

You *could* cut wood with a knife. But a saw is faster, safer and already sharpened.
Hand-written loops are the knife; algorithms are the power tools.

```cpp
// Hand-written: what does this do? You have to read every line.
bool found = false;
for (std::size_t i = 0; i < v.size(); ++i) { if (v[i] < 0) { found = true; break; } }

// Algorithm: says what it does, by name.
bool found = std::any_of(v.begin(), v.end(), [](int x) { return x < 0; });
```
Algorithms work on **iterator ranges** `[first, last)`, so they work with every container.

---

## 📚 Step by step

| Algorithm | Question it answers | Folder |
|-----------|--------------------|--------|
| `all_of / any_of / none_of` | "Are all / any / none of them …?" | [45.2AllOf](45.2AllOf/main.cpp) |
| `for_each` | "Do this to each one" | [45.3ForEach](45.3ForEach/main.cpp) |
| `max_element / min_element` | "Where is the biggest / smallest?" (returns an iterator) | [45.4](45.4.MaxEltMinElt/main.cpp) |
| `find / find_if` | "Where is the first one that …?" (`end()` if none) | [45.5](45.5FindAndFindIf/main.cpp) |
| `copy / copy_if` | "Copy (only these) over there" | [45.6Copy](45.6Copy/main.cpp) |
| `sort` | "Put them in order" (O(n log n)) | [45.7Sort](45.7Sort/main.cpp) |
| `transform` | "Make a new value from each one" | [45.8Transform](45.8Transform/main.cpp) |

```cpp
auto it = std::find_if(people.begin(), people.end(), [](const Person& p) { return p.age > 60; });
if (it != people.end()) std::cout << it->name;

std::vector<int> evens;
std::copy_if(v.begin(), v.end(), std::back_inserter(evens), [](int x) { return x % 2 == 0; });

std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * x; });   // square in place

std::sort(v.begin(), v.end(), std::greater<>{});   // descending
```

### More algorithms worth knowing
| From `<algorithm>` | From `<numeric>` |
|--------------------|------------------|
| `count`, `count_if` | `accumulate` (sum / fold) |
| `reverse`, `rotate`, `shuffle` | `reduce` (parallel-friendly sum) |
| `unique` (after sort) | `iota` (fill 0, 1, 2, …) |
| `binary_search`, `lower_bound` (sorted data!) | `partial_sum` |
| `stable_sort`, `partial_sort`, `nth_element` | `inner_product`, `gcd`, `lcm` |
| `remove_if` + `erase`, `replace_if`, `fill` | |
| `equal`, `mismatch`, `includes`, `set_intersection` | |

---

## ⚠️ Common mistakes

- `std::copy` into an **empty** vector with `v.begin()` → writes past the end. Use `std::back_inserter(v)`.
- `std::remove_if` doesn't shrink the container; you must `erase` (or use `std::erase_if`).
- `binary_search`/`lower_bound` on **unsorted** data gives nonsense.
- A comparator that isn't a *strict weak ordering* (e.g. using `<=`) can crash `std::sort`.

## 🧠 Senior developer notes

- "No raw loops" (Sean Parent): if a loop has a name, use the algorithm. Code reviewers will ask.
- Many algorithms accept an **execution policy** for parallelism: `std::sort(std::execution::par, ...)` (support varies by compiler).
- C++20 **ranges** (Lesson 46) let you write `std::ranges::sort(v)`, with no begin/end noise.

## ✅ Check yourself

1. What does `std::find` return if nothing is found?
2. How do you copy only positive numbers into a new vector?
3. Why is `std::sort(v.begin(), v.end(), [](int a, int b){ return a <= b; })` wrong?

<details><summary>Answers</summary>

1. The `last` iterator (usually `end()`).
2. `std::copy_if(v.begin(), v.end(), std::back_inserter(out), [](int x){ return x > 0; });`
3. `<=` isn't a strict weak ordering (`a <= a` is true); it can cause crashes or wrong results.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 46: Ranges (C++20)](../46.RangesLibraryInCpp20/README.md)
