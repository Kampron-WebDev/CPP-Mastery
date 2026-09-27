# Lesson 05 Exercises

| # | Exercise | Level | Skill |
|---|----------|-------|-------|
| 01 | [DigitSplitter](01_DigitSplitter/main.cpp) | ⭐ | `/` and `%` |
| 02 | [PredictTheOutput](02_PredictTheOutput/main.cpp) | ⭐⭐ | Precedence, `++`, logic |
| 03 | [LoanCalculator](03_LoanCalculator/main.cpp) | ⭐⭐ | `<cmath>` + `<iomanip>` |
| 04 | [ReportTable](04_ReportTable/main.cpp) | ⭐⭐ | Formatted columns |

<details><summary>Hint for 01</summary>

`n % 10` is the last digit. `n / 10` removes the last digit. Repeat.
</details>
<details><summary>Hint for 03</summary>

Monthly payment `M = P * r * (1+r)^n / ((1+r)^n - 1)` where `r` = yearly rate / 12 / 100 and `n` = months.
Use `std::pow(1 + r, n)`.
</details>
