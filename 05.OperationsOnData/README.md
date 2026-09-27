# Lesson 05: Operations on Data

> **In one sentence:** Operators are the verbs of C++ (add, compare, combine), and knowing
> their **order** and **quirks** is the difference between correct and "almost correct" code.

---

## 🎯 You will learn

- Arithmetic: `+ - * / %`.
- Precedence and associativity (who goes first).
- `++` / `--` in prefix and postfix form.
- Compound assignment: `+=`, `-=`, `*=`, `/=`, `%=`.
- Relational (`< <= > >= == !=`) and logical (`&& || !`) operators.
- Output formatting with `<iomanip>`, numeric limits, and `<cmath>` functions.

---

## 🧸 The Big Idea

Operators are like buttons on a calculator. But unlike a cheap calculator, C++ follows
**strict rules about which button is pressed first**, just like maths class (BODMAS/PEMDAS).

```
  2 + 3 * 4      →   2 + 12   →   14      (* before +)
  (2 + 3) * 4    →   5 * 4    →   20      (brackets first)
```

---

## 📚 Step by step

### 1. Basic arithmetic ([5.2.BasicOperations](5.2.BasicOperations/main.cpp))
| Op | Meaning | Example | Result |
|----|---------|---------|--------|
| `+` | add | `7 + 2` | 9 |
| `-` | subtract | `7 - 2` | 5 |
| `*` | multiply | `7 * 2` | 14 |
| `/` | divide | `7 / 2` | **3** (integers!) |
| `%` | remainder (modulus) | `7 % 2` | 1 |

`%` is a superpower: `n % 2 == 0` means *n is even*; `n % 10` gives the last digit.

### 2. Precedence and associativity ([5.3](5.3.PrecedenceAndAssociativity/main.cpp))
- **Precedence**: which operator goes first (`*` beats `+`).
- **Associativity**: for equal precedence, which side first. `10 - 4 - 3` is `(10 - 4) - 3 = 3` (left to right).

> 🧠 If you have to think about precedence, **add brackets**. Code is for humans too.

### 3. Increment and decrement ([5.4](5.4.PrefixPostfixIncrementDecrement/main.cpp))
```cpp
int a = 5;
int b = ++a;  // PREFIX:  first add 1 (a=6), then use it   → b = 6
int c = a++;  // POSTFIX: first use it (c=6), then add 1   → a = 7
```
Kid version: prefix = "eat the cookie, then show the plate"; postfix = "show the plate, then eat the cookie".

⚠️ Never use `x++` twice in one expression (`x++ + x++`): the result is undefined/unspecified.

### 4. Compound assignment ([5.5](5.5.CompoundAssignmentOperators/main.cpp))
`score += 10;` is short for `score = score + 10;`. Same for `-= *= /= %=`.

### 5. Comparisons ([5.6](5.6.RelationalOperators/main.cpp)) and logic ([5.7](5.7.LogicalOperators/main.cpp))
Comparisons give a `bool`. Combine them with logic:

| `a` | `b` | `a && b` (AND) | `a \|\| b` (OR) | `!a` (NOT) |
|-----|-----|----------------|-----------------|------------|
| F | F | F | F | T |
| F | T | F | T | T |
| T | F | F | T | F |
| T | T | T | T | F |

```cpp
bool canRide = (age >= 12) && (height >= 140);
```
⚠️ `=` assigns, `==` compares. `if (x = 5)` is a classic bug. Keep `-Wall` on and the compiler will warn you.

### 6. Output formatting ([5.8.OutputFormatting](5.8.OutputFormatting/main.cpp))
`#include <iomanip>` gives you: `std::setw(n)` (column width), `std::left`/`std::right`,
`std::setfill('*')`, `std::fixed` + `std::setprecision(2)` (2 decimals), `std::boolalpha`,
`std::hex`/`std::oct`/`std::dec`, `std::showpos`.

```cpp
std::cout << std::fixed << std::setprecision(2) << 3.14159;   // 3.14
std::cout << std::setw(10) << std::left << "Name" << '|';      // "Name      |"
```

> 🔭 C++20 also has `std::format` (Lesson 51): `std::format("{:>10.2f}", price)`.

### 7. Limits and maths ([5.9.NumericLimits](5.9.NumericLimits/main.cpp), [5.10.MathFunctions](5.10.MathFunctions/main.cpp))
```cpp
#include <limits>
std::numeric_limits<int>::max();     // 2147483647
std::numeric_limits<int>::min();     // -2147483648
#include <cmath>
std::sqrt(16.0); std::pow(2, 10); std::abs(-3); std::floor(2.7); std::ceil(2.1); std::round(2.5);
```

### 8. Weird integral types ([5.11.WeirdIntegralTypes](5.11.WeirdIntegralTypes/main.cpp))
`short` and `char` are **promoted to `int`** before arithmetic. So `short + short` is an `int`.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [5.2.BasicOperations](5.2.BasicOperations/main.cpp) | `+ - * / %` |
| [5.3.PrecedenceAndAssociativity](5.3.PrecedenceAndAssociativity/main.cpp) | Order of evaluation |
| [5.4.PrefixPostfixIncrementDecrement](5.4.PrefixPostfixIncrementDecrement/main.cpp) | `++a` vs `a++` |
| [5.5.CompoundAssignmentOperators](5.5.CompoundAssignmentOperators/main.cpp) | `+=` and friends |
| [5.6.RelationalOperators](5.6.RelationalOperators/main.cpp) | Comparisons produce bool |
| [5.7.LogicalOperators](5.7.LogicalOperators/main.cpp) | `&&`, `\|\|`, `!` |
| [5.8.OutputFormatting](5.8.OutputFormatting/main.cpp) | `<iomanip>` manipulators |
| [5.9.NumericLimits](5.9.NumericLimits/main.cpp) | `std::numeric_limits` |
| [5.10.MathFunctions](5.10.MathFunctions/main.cpp) | `<cmath>` |
| [5.11.WeirdIntegralTypes](5.11.WeirdIntegralTypes/main.cpp) | Integral promotion |

---

## ⚠️ Common mistakes

- `average = (a + b) / 2;` with ints → truncated. Use `2.0`.
- `%` with doubles: not allowed. Use `std::fmod`.
- Forgetting that `std::fixed`/`setprecision` are **sticky** (they stay on for later output).

## 🧠 Senior developer notes

- Prefer `++i` over `i++` when you don't need the old value. It's never slower, and for iterators it can be faster.
- `(a + b) / 2` can overflow for huge ints; `a + (b - a) / 2` doesn't (a classic binary-search bug), or use C++20 `std::midpoint`.

---

## ✅ Check yourself

1. `17 % 5` = ?  `17 / 5` = ?
2. `int a = 3; int b = a++ + 1;` What are a and b?
3. `2 + 3 * 4 - 1` = ?
4. How do you print 3.14159 as `3.14`?

<details><summary>Answers</summary>

1. `2` and `3`.
2. `b = 3 + 1 = 4`, then `a = 4`.
3. 2 + 12 - 1 = **13**.
4. `std::cout << std::fixed << std::setprecision(2) << 3.14159;`
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 06: Literals and Constants](../06.LiteralsAndConstants/README.md)
