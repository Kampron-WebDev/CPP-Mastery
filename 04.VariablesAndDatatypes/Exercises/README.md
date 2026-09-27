# Lesson 04 Exercises

| # | Exercise | Level | Skill |
|---|----------|-------|-------|
| 01 | [TypeExplorer](01_TypeExplorer/main.cpp) | ⭐ | Declaring every basic type |
| 02 | [TemperatureConverter](02_TemperatureConverter/main.cpp) | ⭐ | double arithmetic |
| 03 | [AsciiDecoder](03_AsciiDecoder/main.cpp) | ⭐⭐ | char ↔ int |
| 04 | [PrecisionTrap](04_PrecisionTrap/main.cpp) | ⭐⭐ | float vs double, comparing decimals |

<details><summary>Hint for 02</summary>

`F = C * 9 / 5 + 32`. Careful: `9 / 5` with integers is `1`! Use `9.0 / 5.0`.
</details>
<details><summary>Hint for 04</summary>

`#include <cmath>` then `std::abs(a - b) < 1e-9` means "a and b are practically equal".
</details>
