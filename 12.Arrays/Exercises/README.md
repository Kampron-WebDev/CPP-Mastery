# Lesson 12 Exercises

| # | Exercise | Level | Skill |
|---|----------|-------|-------|
| 01 | [Statistics](01_Statistics/main.cpp) | ⭐ | min/max/average over an array |
| 02 | [ReverseInPlace](02_ReverseInPlace/main.cpp) | ⭐⭐ | Two-index technique |
| 03 | [DiceHistogram](03_DiceHistogram/main.cpp) | ⭐⭐ | `<random>` + counting array |
| 04 | [TicTacToeBoard](04_TicTacToeBoard/main.cpp) | ⭐⭐⭐ | 2D arrays + win detection |

<details><summary>Hint for 02</summary>

Use two indexes: `left = 0`, `right = size - 1`. Swap, then move them towards each other until they meet.
</details>
<details><summary>Hint for 03</summary>

Make `int counts[13]{}` and do `++counts[total]` for each roll. Index = the dice total.
</details>
