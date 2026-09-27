# Lesson 58: Performance and Memory ⭐ NEW

> **In one sentence:** C++ is chosen for speed, but speed comes from **measuring first**, then
> fixing the few things that matter: algorithms, memory access patterns, and unnecessary copies/allocations.

---

## 🎯 You will learn

- The golden rule: **measure, don't guess** (benchmarks and profilers).
- How the CPU cache works and why **memory layout** often matters more than Big-O.
- Avoiding needless copies and allocations (`const&`, move, `reserve`, `string_view`, `emplace_back`).
- Compiler optimization levels and what they do.
- Stack vs heap; object size and padding.

---

## 🧸 The Big Idea: the desk, the shelf and the warehouse

The CPU is a worker at a desk. Data can be:

| Where | Like | Time to get it (roughly) |
|-------|------|--------------------------|
| CPU registers | in your hand | ~0.3 ns |
| L1 cache | on your desk | ~1 ns |
| L2/L3 cache | on the shelf behind you | ~4–40 ns |
| RAM | in the warehouse down the road | ~100 ns |
| SSD | in another city | ~100 000 ns |

When the CPU fetches something from RAM it brings a whole **cache line** (64 bytes) at once, like grabbing the whole box, not one pencil.
So if your data sits **side by side** (`std::vector`, arrays), the next items are already on your desk. If it's scattered
(`std::list`, trees of pointers), every item is a trip to the warehouse.

> Reading data in order (sequential access) can be **10–50× faster** than jumping around, with the *same* Big-O.

---

## 📚 Step by step

### 1. Measure first
- Build optimized: `-O2` (the **"Build & Run (Optimized -O2)"** task). Never time `-O0` debug builds.
- Micro-benchmark with `std::chrono::steady_clock`, repeat several times, and use the result so the optimizer can't delete the work.
- Profilers show *where* time goes: **perf** (Linux), **Visual Studio Profiler**, **Intel VTune**, **Tracy**, `gprof`.
- 90% of the time is spent in 10% of the code. Find that 10%.

### 2. Cache-friendly code ([Examples/01_CacheLocality](Examples/01_CacheLocality/main.cpp))
- Traverse 2D data **row by row** (how C++ stores it), not column by column.
- Prefer `std::vector` of values over `std::list` / vectors of pointers.
- "Structure of arrays" vs "array of structures": if a hot loop only needs `x`, storing all `x` values together wins.

### 3. Copies and allocations ([Examples/02_CopiesAndAllocations](Examples/02_CopiesAndAllocations/main.cpp))
| Instead of | Write | Why |
|------------|-------|-----|
| `void f(std::string s)` (read-only) | `void f(std::string_view s)` / `const std::string&` | no copy |
| `for (auto x : bigObjects)` | `for (const auto& x : bigObjects)` | no copy per item |
| `push_back` in a loop of known size | `reserve(n)` first | no repeated reallocation |
| `v.push_back(Thing(a, b))` | `v.emplace_back(a, b)` | construct in place |
| `return std::move(local);` | `return local;` | allows RVO |
| `s = s + piece;` in a loop | `s += piece;` (+ `reserve`) | avoids a new string each time |

### 4. Compiler optimization
| Flag | Meaning |
|------|---------|
| `-O0` | No optimization, easiest to debug (default in this course's F5) |
| `-O2` | The usual release level: inlining, loop optimizations, vectorization |
| `-O3` | More aggressive (sometimes faster, sometimes bigger/slower: measure) |
| `-march=native` | Use every instruction your CPU has (not portable to older CPUs) |

### 5. Memory layout ([Examples/03_ObjectLayout](Examples/03_ObjectLayout/main.cpp))
Members are aligned; the compiler adds **padding**. Ordering members from largest to smallest can shrink objects.
Smaller objects → more fit in cache → faster loops.

---

## 🗂️ Examples (use the **Optimized -O2** task!)

| Folder | Shows |
|--------|-------|
| [01_CacheLocality](Examples/01_CacheLocality/main.cpp) | Row vs column traversal; vector vs list |
| [02_CopiesAndAllocations](Examples/02_CopiesAndAllocations/main.cpp) | By value vs `const&`; `reserve`; string building |
| [03_ObjectLayout](Examples/03_ObjectLayout/main.cpp) | Padding, `sizeof`, member order |

## ⚠️ Common mistakes

- **Premature optimization**: making code unreadable for a speed-up nobody measured.
- Timing a debug build, or a loop the optimizer removed because its result was unused.
- Optimizing the wrong thing: a 10× faster function that takes 1% of the runtime saves under 1% overall.

## 🧠 Senior developer notes

- Order of impact, usually: **algorithm (Big-O)** → **data layout / cache** → **allocations & copies** → **micro-tweaks**.
- Performance is a feature with a budget: know your targets (60 FPS = 16.6 ms per frame; a trading system counts microseconds).
- Keep a benchmark in the repo so regressions are caught (Google Benchmark is the standard tool).
- "Make it work, make it right, make it fast", in that order (Lesson 02).

## ✅ Check yourself

1. Why is iterating a `std::vector` usually faster than a `std::list`, even though both are O(n)?
2. Which build should you time?
3. Name three ways to avoid unnecessary copies.
4. What is padding?

<details><summary>Answers</summary>

1. Vector elements are contiguous, so cache lines and prefetching bring the next elements for free. List nodes are scattered, so almost every step is a cache miss.
2. An optimized one (`-O2` or higher), with the result used.
3. `const&` / `string_view` parameters, `const auto&` in loops, move semantics, `reserve`, `emplace_back`, returning by value (RVO).
4. Unused bytes the compiler inserts between/after members so each member is correctly aligned.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 59: Capstone Projects](../59.CapstoneProjects/README.md)
