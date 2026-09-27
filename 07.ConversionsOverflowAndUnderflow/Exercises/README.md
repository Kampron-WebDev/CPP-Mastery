# Lesson 07 Exercises

| # | Exercise | Level | Skill |
|---|----------|-------|-------|
| 01 | [FixThePercentage](01_FixThePercentage/main.cpp) | ⭐ | `static_cast` |
| 02 | [OdometerWrap](02_OdometerWrap/main.cpp) | ⭐⭐ | Unsigned wrap-around |
| 03 | [SafeAdd](03_SafeAdd/main.cpp) | ⭐⭐⭐ | Detecting overflow **before** it happens |

<details><summary>Hint for 03</summary>

For positive `b`, `a + b` overflows exactly when `a > max - b`. For negative `b`, it underflows when `a < min - b`.
</details>
