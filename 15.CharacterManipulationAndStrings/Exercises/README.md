# Lesson 15 Exercises

| # | Exercise | Level | Skill |
|---|----------|-------|-------|
| 01 | [TextStats](01_TextStats/main.cpp) | ⭐ | `<cctype>` counting |
| 02 | [CaesarCipher](02_CaesarCipher/main.cpp) | ⭐⭐ | char arithmetic with wrap-around |
| 03 | [WordCounter](03_WordCounter/main.cpp) | ⭐⭐ | `find`, `substr` |
| 04 | [PasswordChecker](04_PasswordChecker/main.cpp) | ⭐⭐ | Validation rules |
| 05 | [TitleCaseAndTrim](05_TitleCaseAndTrim/main.cpp) | ⭐⭐⭐ | String transformation functions |

<details><summary>Hint for 02</summary>

For an uppercase letter: `'A' + (c - 'A' + shift) % 26`. Do the same for lowercase with `'a'`.
For decoding, shift by `26 - shift`.
</details>
<details><summary>Hint for 03</summary>

Or use `std::istringstream` from `<sstream>`: `while (stream >> word)` splits on spaces for you.
</details>
