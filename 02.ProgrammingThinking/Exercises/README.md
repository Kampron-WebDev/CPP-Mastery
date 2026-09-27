# Lesson 02 Exercises: Thinking First

For each exercise: **write the pseudocode as comments first**, then the code.

| # | Exercise | Level | Skill |
|---|----------|-------|-------|
| 01 | [TraceMe](01_TraceMe/main.cpp) | ⭐ | Tracing by hand |
| 02 | [BiggestOfThree](02_BiggestOfThree/main.cpp) | ⭐ | Decomposition + if |
| 03 | [SecondsConverter](03_SecondsConverter/main.cpp) | ⭐⭐ | Integer division and % |
| 04 | [CoinChange](04_CoinChange/main.cpp) | ⭐⭐⭐ | Algorithm design |

<details><summary>Hint for 03</summary>

`total / 3600` gives whole hours. `total % 3600` gives the seconds left over. Repeat the idea for minutes.
</details>

<details><summary>Hint for 04</summary>

"Greedy" algorithm: always take as many of the **biggest** coin as possible, then move to the next smaller coin.
Work in whole cents (integers) so you don't get rounding problems.
</details>
