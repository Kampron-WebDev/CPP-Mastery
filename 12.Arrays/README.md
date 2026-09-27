# Lesson 12: Arrays

> **In one sentence:** An array is a **row of identical boxes side by side** in memory, all
> sharing one name, and you pick a box by its number (index), starting from **0**.

---

## 🎯 You will learn

- Declaring, initializing and looping over arrays.
- `std::size()` and why arrays don't know their own size once passed around.
- Character arrays (C-strings).
- Array bounds, and why going past the end is dangerous.
- Random numbers.
- 2D (multi-dimensional) arrays.

---

## 🧸 The Big Idea: an egg carton

```
 int eggs[6]{10, 20, 30, 40, 50, 60};

 index:    [0]   [1]   [2]   [3]   [4]   [5]
         ┌─────┬─────┬─────┬─────┬─────┬─────┐
 value:  │ 10  │ 20  │ 30  │ 40  │ 50  │ 60  │
         └─────┴─────┴─────┴─────┴─────┴─────┘
 address: 1000  1004  1008  1012  1016  1020   ← each int is 4 bytes, packed tightly
```

- Counting starts at **0** because the index means *"how many boxes to skip from the start"*.
- The **last** index is `size - 1`. There is **no** `eggs[6]`.
- The boxes sit **next to each other** in memory, which makes arrays very fast.

---

## 📚 Step by step

### 1. Declaring and using ([12.2DeclaringAndUsingArrays](12.2DeclaringAndUsingArrays/main.cpp))
```cpp
int a[5];                 // 5 ints, GARBAGE values
int b[5]{};               // 5 zeros
int c[5]{1, 2};           // 1, 2, 0, 0, 0
int d[]{4, 5, 6};         // size worked out: 3
c[0] = 99;                // write
std::cout << c[1];        // read
```
The size must be a **compile-time constant**.

### 2. Size ([12.3SizeOfAnArray](12.3SizeOfAnArray/main.cpp))
```cpp
std::size(d);                    // 3 (C++17). Use this
sizeof(d) / sizeof(d[0]);        // old trick: 12 bytes / 4 bytes = 3
```

### 3. Arrays of characters ([12.4ArraysOfCharacters](12.4ArraysOfCharacters/main.cpp))
`char name[]{"Ada"};` is 4 chars: `'A' 'd' 'a' '\0'`. The invisible **null terminator `'\0'`**
marks the end. Forget it and printing runs off into garbage.

### 4. Bounds ([12.5ArrayBounds](12.5ArrayBounds/main.cpp))
`eggs[10] = 5;` compiles! C++ does **no bounds checking** on raw arrays. You scribble over
someone else's memory: **undefined behaviour**. This is the #1 source of security holes in C/C++ history.

### 5. Random numbers ([12.6GeneratingRandomNumbers](12.6GeneratingRandomNumbers/main.cpp))
Old way: `std::rand()`. **Modern way** (use this):
```cpp
#include <random>
std::random_device rd;                           // a seed from the hardware
std::mt19937 engine{rd()};                       // a good random engine
std::uniform_int_distribution<int> dice{1, 6};   // numbers 1..6, all equally likely
int roll = dice(engine);
```

### 6. Practice: Fortune Teller ([12.7 V1](12.7Practice_FortuneTellerV1/main.cpp), [12.10 V2](12.10Practice_FortuneTellerV2/main.cpp))
Pick a random index into an array of fortunes.

### 7. 2D arrays ([12.8](12.8MultiDimensionalArrays/main.cpp), [12.9](12.9MultiDimensionalArraysOfCharacters/main.cpp))
```cpp
int grid[3][4]{};          // 3 rows, 4 columns, like a spreadsheet
grid[1][2] = 7;            // row 1, column 2
for (auto& row : grid)
    for (int cell : row) std::cout << cell;
```
In memory it's still one long row: row 0, then row 1, then row 2.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [12.2DeclaringAndUsingArrays](12.2DeclaringAndUsingArrays/main.cpp) | Init styles, reading/writing |
| [12.3SizeOfAnArray](12.3SizeOfAnArray/main.cpp) | `std::size`, `sizeof` |
| [12.4ArraysOfCharacters](12.4ArraysOfCharacters/main.cpp) | `'\0'` terminator |
| [12.5ArrayBounds](12.5ArrayBounds/main.cpp) | Out-of-bounds danger |
| [12.6GeneratingRandomNumbers](12.6GeneratingRandomNumbers/main.cpp) | `rand` / `<random>` |
| [12.7Practice_FortuneTellerV1](12.7Practice_FortuneTellerV1/main.cpp) | Mini project |
| [12.8MultiDimensionalArrays](12.8MultiDimensionalArrays/main.cpp) | 2D/3D arrays |
| [12.9MultiDimensionalArraysOfCharacters](12.9MultiDimensionalArraysOfCharacters/main.cpp) | List of words |
| [12.10Practice_FortuneTellerV2](12.10Practice_FortuneTellerV2/main.cpp) | Improved mini project |

## ⚠️ Common mistakes

- Looping `i <= size` instead of `i < size`.
- Uninitialized arrays (`int a[5];`) printing garbage.
- Trying to copy with `a = b;` (not allowed for raw arrays) or compare with `a == b` (compares addresses!).

## 🧠 Senior developer notes

- In modern C++ prefer **`std::array<int, 5>`** (fixed size, knows its size, can be copied) or
  **`std::vector<int>`** (growable). See Lesson 43. Raw arrays are for understanding and legacy code.
- `.at(i)` on `std::array`/`std::vector` **checks bounds** and throws an exception instead of corrupting memory.
- Arrays are fast because their memory is **contiguous**. The CPU cache loves that (Lesson 58).

## ✅ Check yourself

1. Valid indexes of `int x[8]`?
2. What does `int x[4]{7};` contain?
3. How many bytes does `char s[]{"cat"};` use?
4. Why is `x[100] = 1;` on a size-8 array so dangerous?

<details><summary>Answers</summary>

1. 0 to 7.
2. `7, 0, 0, 0`.
3. 4 (3 letters + `'\0'`).
4. No bounds check: it overwrites unknown memory (UB): crashes, corrupted data, security holes.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 13: Pointers](../13.Pointers/README.md)
