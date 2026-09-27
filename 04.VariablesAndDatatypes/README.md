# Lesson 04: Variables and Data Types

> **In one sentence:** A variable is a **labelled box** in memory; its **type** decides what
> can go in the box, how big the box is, and what you are allowed to do with it.

---

## 🎯 You will learn

- Declaring and initializing variables (and why `{}` braces are safest).
- Number systems: decimal, binary, octal, hexadecimal.
- Integer types and modifiers (`short`, `long`, `unsigned`).
- Fractional numbers (`float`, `double`, `long double`) and their precision limits.
- `bool`, `char`, `auto`, and assignment.

---

## 🧸 The Big Idea: labelled boxes

```
   int age{12};            double price{2.5};        char grade{'A'};
  ┌──────────────┐        ┌──────────────┐          ┌──────┐
  │      12      │        │     2.5      │          │  'A' │
  └──────────────┘        └──────────────┘          └──────┘
   label: age              label: price              label: grade
   size: 4 bytes           size: 8 bytes             size: 1 byte
   holds: whole numbers    holds: decimals           holds: one character
```

You can't put a decimal in a whole-number box without losing a part of it, just like you can't pour soup into an egg carton.
**The type is the shape of the box.**

---

## 📚 Step by step

### 1. Three ways to initialize
```cpp
int a = 5;      // copy initialization (old style)
int b(5);       // functional initialization
int c{5};       // BRACE initialization: the modern, safest way
int d{};        // braces with nothing inside = zero (0)
int e{2.9};     // ❌ ERROR with braces: "narrowing", which protects you from losing .9
int f = 2.9;    // ⚠️ compiles, silently becomes 2
```
> 🧠 Prefer `{}`. It catches accidental data loss at compile time.

⚠️ `int x;` (no initializer) holds **garbage**: whatever was in that memory before. Always initialize.

### 2. Number systems ([4.2NumberSystems](4.2NumberSystems/main.cpp))
The same value can be written four ways:

| System | Base | Prefix | 15 written as |
|--------|------|--------|---------------|
| Decimal | 10 | none | `15` |
| Binary | 2 | `0b` | `0b1111` |
| Octal | 8 | `0` | `017` |
| Hexadecimal | 16 | `0x` | `0xF` |

Hex digits: 0-9 then A=10, B=11 … F=15. One hex digit = exactly 4 bits, which is why programmers love
hex for colours (`0xFF0000` = red) and memory addresses.

### 3. Integers ([4.3IntegerTypes](4.3IntegerTypes/main.cpp), [4.4IntegerModifiers](4.4IntegerModifiers/main.cpp))
| Type | Typical size | Typical range |
|------|--------------|---------------|
| `short` | 2 bytes | -32 768 … 32 767 |
| `int` | 4 bytes | about ±2.1 billion |
| `long long` | 8 bytes | about ±9.2 quintillion |
| `unsigned int` | 4 bytes | 0 … about 4.2 billion (no negatives) |

`unsigned` moves the whole range to 0 and up. Great for bit patterns; **dangerous** for counts that can go below zero
(`0u - 1` wraps to 4 294 967 295!).

Integer division **throws away** the fraction: `7 / 2 == 3`.

### 4. Fractional numbers ([4.5FractionalNumbers](4.5FractionalNumbers/main.cpp))
| Type | Size | Precision (digits) | Literal |
|------|------|--------------------|---------|
| `float` | 4 | ~7 | `3.14f` |
| `double` | 8 | ~15 | `3.14` |
| `long double` | 12–16 | ≥ 15 | `3.14L` |

Fractions are stored in binary, so `0.1 + 0.2` is **not exactly** `0.3`. Never compare doubles with `==`;
compare with a small tolerance instead: `std::abs(a - b) < 1e-9`.
Special values: `inf` (1.0/0.0) and `nan` (0.0/0.0, "not a number").

> 🧠 **Senior note:** Never store **money** in `double`. Store whole cents in an integer (`long long cents`).

### 5. Booleans ([4.6Booleans](4.6Booleans/main.cpp))
`bool` holds `true` or `false`. It prints as `1`/`0` unless you use `std::boolalpha`.

### 6. Characters ([4.7CharactersAndText](4.7CharactersAndText/main.cpp))
`char` holds one character in single quotes: `'A'`. It is really a small number (the **ASCII code**):
`'A'` is 65, `'a'` is 97, `'0'` is 48. That's why `'A' + 1` is 66 (`'B'`).

### 7. `auto` ([4.8Auto](4.8Auto/main.cpp))
`auto x = 3.5;` lets the compiler figure out the type (`double`). Useful for long type names;
don't use it where it hides the meaning.

### 8. Assignment ([4.9Assignments](4.9Assignments/main.cpp))
`=` in C++ means **"put the value on the right into the box on the left"**. It is not "equals" from maths.
`x = x + 1;` makes perfect sense: take x, add 1, and put the result back in x.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [4.2NumberSystems](4.2NumberSystems/main.cpp) | Same number in dec/bin/oct/hex |
| [4.3IntegerTypes](4.3IntegerTypes/main.cpp) | Brace vs functional vs assignment init; narrowing |
| [4.4IntegerModifiers](4.4IntegerModifiers/main.cpp) | `signed`, `unsigned`, `short`, `long`, `long long` |
| [4.5FractionalNumbers](4.5FractionalNumbers/main.cpp) | Precision, `inf`, `nan`, scientific notation |
| [4.6Booleans](4.6Booleans/main.cpp) | `std::boolalpha` |
| [4.7CharactersAndText](4.7CharactersAndText/main.cpp) | `char` as a number (ASCII) |
| [4.8Auto](4.8Auto/main.cpp) | Type deduction with literal suffixes |
| [4.9Assignments](4.9Assignments/main.cpp) | Changing a variable after creation |

---

## ⚠️ Common mistakes

- Uninitialized variables (`int total;` then `total += 5;` gives garbage).
- `5 / 2` expecting 2.5. Write `5.0 / 2`.
- Comparing doubles with `==`.
- Using `"A"` (a string) where you meant `'A'` (a char).

## 🧠 Senior developer notes

- Sizes of `int`/`long` vary by platform. When exact size matters (file formats, networks), use
  `<cstdint>`: `std::int32_t`, `std::uint8_t`, `std::int64_t`.
- Name variables for **what they mean**: `elapsedSeconds`, not `t`.
- Keep variables in the **smallest scope** possible and declare them where you first need them.

---

## ✅ Check yourself

1. What does `int x{};` contain?
2. Why does `int n{3.7};` fail but `int n = 3.7;` compile?
3. What is `0x1F` in decimal?
4. What does `7 / 2` give? And `7.0 / 2`?
5. Why is `double` a bad choice for money?

<details><summary>Answers</summary>

1. `0`.
2. Braces forbid *narrowing* (losing data). `=` silently truncates to 3.
3. 1×16 + 15 = **31**.
4. `3` and `3.5`.
5. Many decimal fractions (like 0.10) can't be stored exactly in binary, so rounding errors pile up. Use integer cents.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 05: Operations on Data](../05.OperationsOnData/README.md)
