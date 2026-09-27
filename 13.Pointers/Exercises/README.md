# Lesson 13 Exercises

| # | Exercise | Level | Skill |
|---|----------|-------|-------|
| 01 | [PointerBasics](01_PointerBasics/main.cpp) | ⭐ | `&`, `*`, predicting values |
| 02 | [SwapWithPointers](02_SwapWithPointers/main.cpp) | ⭐⭐ | Changing caller's variables |
| 03 | [WalkTheArray](03_WalkTheArray/main.cpp) | ⭐⭐ | Pointer arithmetic, no `[]` allowed |
| 04 | [DynamicScores](04_DynamicScores/main.cpp) | ⭐⭐⭐ | `new[]`/`delete[]` + growing an array |

<details><summary>Hint for 04</summary>

To "grow" a heap array: allocate a bigger one, copy the old elements, `delete[]` the old one,
and point at the new one. This is exactly what `std::vector` does for you internally.
</details>
