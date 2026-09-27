# Lesson 08: Bitwise Operators

> **In one sentence:** Bitwise operators let you flip, test and move the individual 1s and 0s
> inside a number, which is how you pack lots of yes/no information into a tiny space.

---

## 🎯 You will learn

- Printing numbers as binary with `std::bitset`.
- Shifting bits: `<<` and `>>`.
- Bitwise logic: `&` (AND), `|` (OR), `^` (XOR), `~` (NOT).
- **Masks**: set, clear, toggle and test individual bits.
- Packing colour information into one integer.

---

## 🧸 The Big Idea: a row of light switches

An `unsigned char` is **8 light switches** in a row. Each switch is a *bit*.

```
 switch #:   7   6   5   4   3   2   1   0
 state:      0   0   1   0   1   1   0   1     = 45
```

Bitwise operators let you flip **one switch** without touching the others. Games use this for
"has key / has sword / is invisible" flags; networks use it for addresses; graphics use it for colours.

---

## 📚 Step by step

### 1. See the bits ([8.2PrintingIntegersInBinary](8.2PrintingIntegersInBinary/main.cpp))
```cpp
#include <bitset>
std::cout << std::bitset<8>(45);   // 00101101
```

### 2. Shifting ([8.3ShiftOperators](8.3ShiftOperators/main.cpp))
```
 x      = 0000 0101  (5)
 x << 1 = 0000 1010  (10)   shift left by 1  = × 2
 x << 3 = 0010 1000  (40)   shift left by 3  = × 8
 x >> 1 = 0000 0010  (2)    shift right by 1 = ÷ 2 (drops the remainder)
```

### 3. Bitwise logic ([8.4LogicalBitwiseOperators](8.4LogicalBitwiseOperators/main.cpp))
Works on **each pair of bits** separately:
```
      1100            1100           1100          ~ 1100
    & 1010          | 1010         ^ 1010          ------
    ------          ------         ------            0011
      1000            1110           0110
     (AND: both)   (OR: either)   (XOR: different) (NOT: flip all)
```
⚠️ `&` (bitwise) is not `&&` (logical). `|` is not `||`.

### 4. Compound versions ([8.5CompoundBitwiseOperators](8.5CompoundBitwiseOperators/main.cpp))
`x |= mask;  x &= mask;  x ^= mask;  x <<= 2;  x >>= 1;`

### 5. Masks: the four magic moves ([8.6Masks](8.6Masks/main.cpp), [8.7MasksExample](8.7MasksExample/main.cpp))
A **mask** is a number with 1s only where you care. `1 << n` makes a mask for bit n.

| Goal | Code | Memory trick |
|------|------|--------------|
| **Set** bit n (turn on) | `x \|= (1 << n);` | OR adds ones |
| **Clear** bit n (turn off) | `x &= ~(1 << n);` | AND with a hole |
| **Toggle** bit n (flip) | `x ^= (1 << n);` | XOR flips |
| **Test** bit n | `(x & (1 << n)) != 0` | AND keeps only that bit |

### 6. Packing colours ([8.8PackingColorInformation](8.8PackingColorInformation/main.cpp))
A colour like `0xFF8800` holds Red=FF, Green=88, Blue=00 in one integer:
```cpp
unsigned int color = 0xFF8800;
unsigned int red   = (color >> 16) & 0xFF;   // 255
unsigned int green = (color >> 8)  & 0xFF;   // 136
unsigned int blue  =  color        & 0xFF;   // 0
```

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [8.2PrintingIntegersInBinary](8.2PrintingIntegersInBinary/main.cpp) | `std::bitset` |
| [8.3ShiftOperators](8.3ShiftOperators/main.cpp) | `<<`, `>>` |
| [8.4LogicalBitwiseOperators](8.4LogicalBitwiseOperators/main.cpp) | `& \| ^ ~` |
| [8.5CompoundBitwiseOperators](8.5CompoundBitwiseOperators/main.cpp) | `&= \|= ^=` … |
| [8.6Masks](8.6Masks/main.cpp) | set / clear / toggle / test |
| [8.7MasksExample](8.7MasksExample/main.cpp) | A realistic use of flags |
| [8.8PackingColorInformation](8.8PackingColorInformation/main.cpp) | RGB in one int |

## ⚠️ Common mistakes

- Shifting **signed** negative numbers, or shifting by ≥ the number of bits (UB). Use **unsigned** types for bit work.
- Precedence: `x & 1 == 0` means `x & (1 == 0)`. Always use brackets: `(x & 1) == 0`.

## 🧠 Senior developer notes

- C++20 `<bit>` gives you `std::popcount` (count 1s), `std::has_single_bit` (power of two?),
  `std::rotl`, `std::countl_zero`, and `std::bit_cast`.
- `x & (x - 1)` removes the lowest set bit, a classic interview trick. `(x & (x-1)) == 0` means x is a power of 2.
- For readable flag sets, `std::bitset<N>` or an `enum class` with operators beats raw ints.

## ✅ Check yourself

1. `0b0110 & 0b0011` = ?  `0b0110 | 0b0011` = ?  `0b0110 ^ 0b0011` = ?
2. What is `1 << 4`?
3. How do you check whether bit 2 of `x` is on?
4. How do you check whether a number is odd using bits?

<details><summary>Answers</summary>

1. `0010` (2), `0111` (7), `0101` (5).
2. 16.
3. `(x & (1u << 2)) != 0`.
4. `(x & 1) == 1`: the lowest bit is 1 for odd numbers.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 09: Variable Lifetime and Scope](../09.VariableLifetimeAndScope/README.md)
