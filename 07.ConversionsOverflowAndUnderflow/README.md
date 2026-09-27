# Lesson 07: Conversions, Overflow and Underflow

> **In one sentence:** When values of different types meet, C++ quietly converts them. If a
> number gets too big for its box it **overflows**, and knowing these rules prevents very sneaky bugs.

---

## 🎯 You will learn

- **Implicit** conversions (the compiler does it for you) and **promotions**.
- **Explicit** conversions with `static_cast` (you do it on purpose).
- What happens when a value doesn't fit: overflow and underflow.

---

## 🧸 The Big Idea: pouring water between cups

- Pouring a small cup (`int`) into a big cup (`double`): **safe**, nothing spills. That's a *widening* conversion.
- Pouring a big cup (`double 3.99`) into a small cup (`int`): **spills**. You get `3`; the `.99` is lost. That's a *narrowing* conversion.
- Filling a cup past the top (overflow): the water doesn't grow the cup. It **wraps around** or makes a mess.

```
 An 8-bit unsigned "odometer":  253 → 254 → 255 → 0 → 1 ...   (wraps like a car's mileage counter)
```

---

## 📚 Step by step

### 1. Implicit conversions ([7.2ImplicitDataConversions](7.2ImplicitDataConversions/main.cpp))
When two types meet in an expression, the "smaller" is converted to the "larger":
```cpp
int i = 5;
double d = 2.5;
auto r = i + d;    // i becomes 5.0 → r is double 7.5
int x = d;         // ⚠️ narrowing: x = 2
```
Order (roughly): `bool/char/short → int → long → long long → float → double → long double`.

⚠️ **Signed/unsigned trap:**
```cpp
int a = -1;
unsigned int b = 1;
if (a < b) ...   // FALSE! -1 is converted to 4294967295
```
Compile with `-Wall -Wextra` and you get a warning. Never ignore it.

### 2. Explicit conversions ([7.3ExplicitDataConversions](7.3ExplicitDataConversions/main.cpp))
```cpp
double avg = static_cast<double>(total) / count;   // ✅ modern, searchable, checked
double avg2 = (double)total / count;                // ⚠️ old C-style cast: avoid
```
| Cast | Use for |
|------|---------|
| `static_cast` | Normal, sensible conversions (99% of the time) |
| `const_cast` | Removing `const` (rare, usually a design smell) |
| `reinterpret_cast` | Treating raw bits as another type (low-level, dangerous) |
| `dynamic_cast` | Safe down-casting in class hierarchies (Lesson 37) |

### 3. Overflow and underflow ([7.4OverflowAndUnderflow](7.4OverflowAndUnderflow/main.cpp))
```cpp
unsigned char u = 255;  u = u + 1;   // wraps to 0 (well-defined for unsigned)
int big = std::numeric_limits<int>::max();
big = big + 1;                       // ❌ UNDEFINED BEHAVIOUR for signed ints!
```
**Undefined behaviour (UB)** means the C++ rules say *anything* may happen: wrong answers, crashes,
or code that "works" today and breaks with the next compiler. Senior developers fear UB.

How to protect yourself:
- Choose a big enough type (`long long`, `std::int64_t`).
- Check **before** you add: `if (a > max - b) { /* would overflow */ }`.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [7.2ImplicitDataConversions](7.2ImplicitDataConversions/main.cpp) | Automatic conversions in expressions |
| [7.3ExplicitDataConversions](7.3ExplicitDataConversions/main.cpp) | `static_cast` |
| [7.4OverflowAndUnderflow](7.4OverflowAndUnderflow/main.cpp) | Wrapping and limits |

## ⚠️ Common mistakes

- `int percent = correct / total * 100;` gives 0 because the division happens first, in integers.
- Mixing `int` loop counters with `.size()` (which is unsigned). Use `std::size_t`, or C++20 `std::ssize()`.
- Assuming overflow "just wraps" for signed ints. It's UB.

## 🧠 Senior developer notes

- Brace initialization `int x{d};` refuses narrowing, a free safety net.
- Famous real bugs: the Ariane 5 rocket exploded (1996) because a 64-bit float was converted to a
  16-bit int that overflowed. The "Gangnam Style" video broke YouTube's 32-bit view counter.
- C++20 has `std::cmp_less(a, b)` in `<utility>` for **safe** signed/unsigned comparisons.

## ✅ Check yourself

1. `7 / 2 * 2.0` = ?
2. `unsigned char c = 250; c += 10;` What is c?
3. Why is signed overflow worse than unsigned overflow?
4. How do you divide two ints and get a decimal answer?

<details><summary>Answers</summary>

1. `7/2` is `3` (int), then `3 * 2.0 = 6.0`.
2. 260 − 256 = **4** (wraps).
3. Unsigned wrap is defined behaviour; signed overflow is **undefined behaviour**.
4. `static_cast<double>(a) / b`.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 08: Bitwise Operators](../08.BitwiseOperators/README.md)
