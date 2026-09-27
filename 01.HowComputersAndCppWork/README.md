# Lesson 01: How Computers and C++ Work

> **In one sentence:** A computer is a very fast, very obedient worker with a giant wall of
> numbered boxes. C++ lets you talk to it almost directly, which is why C++ is fast and why you
> must be careful.

---

## 🎯 By the end of this lesson you can

- Describe the **CPU**, **memory (RAM)** and **storage**, and what each one does.
- Explain **bits** and **bytes**, and count in **binary**.
- Describe the 4 stages that turn `main.cpp` into `rooster.exe`.
- Explain what a **memory address** is (the key to pointers in Lesson 13).
- Name the C++ versions (C++11 … C++23) and why "Modern C++" matters.

---

## 🧸 The Big Idea: the kitchen

Imagine a kitchen:

| Kitchen | Computer | What it does |
|---------|----------|--------------|
| 👩‍🍳 The chef | **CPU** (processor) | Does the work: adds, compares, moves things. Billions of times per second. |
| 🍽️ The counter | **RAM** (memory) | Where things are kept *while cooking*. Fast, but cleared when the power goes off. |
| 🗄️ The pantry | **Storage** (SSD/disk) | Keeps things for a long time (files, your `.exe`). Big but slow. |
| 📜 The recipe | **Your program** | The list of steps the chef follows, one at a time, in order. |

When you run `rooster.exe`, the recipe is copied from the pantry (disk) to the counter (RAM),
and the chef (CPU) starts following it from the top of `main()`.

---

## 🔢 Bits and bytes: how computers store everything

A **bit** is one tiny switch: **off (0)** or **on (1)**. That's all a computer really has.

A **byte** is 8 bits in a row. With 8 switches you can make 2⁸ = **256** different patterns,
enough for the numbers 0 to 255.

### Counting in binary (base 2)

We normally count in **decimal** (base 10): each place is worth 10× the one to its right.
Binary works the same way, but each place is worth **2×**:

```
 Place value:   128   64   32   16    8    4    2    1
 Bits:            0    0    0    0    1    1    0    1
                                     8 +  4 +      1   = 13
```

So `00001101` in binary is **13** in decimal. Try: what is `00000110`? (Answer: 4 + 2 = 6.)

Everything becomes numbers: the letter `'A'` is stored as 65, a colour is three numbers
(red, green, blue), and a picture is millions of colours. Lessons 04 and 08 go deeper.

| Unit | Size | Everyday example |
|------|------|------------------|
| 1 byte | 8 bits | one letter |
| 1 KB | ~1 000 bytes | a short text message |
| 1 MB | ~1 000 000 bytes | a photo |
| 1 GB | ~1 000 000 000 bytes | a movie |

---

## 🏠 Memory is a street of numbered houses

RAM is like a **very long street**. Every house holds **one byte**, and every house has an
**address** (a number) so the CPU can find it.

```
 Address:   1000   1001   1002   1003   1004   1005 ...
          ┌──────┬──────┬──────┬──────┬──────┬──────┐
 Value:   │  72  │ 105  │  0   │  0   │  0   │  42  │
          └──────┴──────┴──────┴──────┴──────┴──────┘
```

When you write `int age = 42;` the compiler picks some houses (4 of them, because an `int` is
usually 4 bytes), names them `age`, and puts 42 inside. You can even ask for the address with
`&age`. Run [Examples/02_MemoryAddresses](Examples/02_MemoryAddresses/main.cpp) to see real addresses.

> 🔑 This single idea, *"a variable lives at an address"*, is what makes **pointers** (Lesson 13)
> easy instead of scary. Remember it.

---

## 🏭 From main.cpp to rooster.exe: the 4-stage factory

```
 main.cpp ──► 1. PREPROCESSOR ──► 2. COMPILER ──► 3. ASSEMBLER ──► 4. LINKER ──► rooster.exe
              copies #include      C++ → assembly  assembly →       joins all .o
              files in, handles    (CPU words)     machine code     files + the
              #define                              (main.o)         library
```

1. **Preprocessor:** follows lines starting with `#`. `#include <iostream>` literally copy-pastes
   thousands of lines of the iostream library into your file.
2. **Compiler:** checks your grammar (errors!) and translates C++ into *assembly language*.
3. **Assembler:** turns assembly into machine code, stored in an **object file** (`main.o`).
4. **Linker:** glues all object files together plus the standard library, producing the `.exe`.
   *"undefined reference to …"* errors come from this stage (Lesson 32).

See each stage yourself: [Examples/03_ThePipeline](Examples/03_ThePipeline/README.md).

---

## ⚡ Why C++?

C++ compiles directly to machine code and lets you control memory yourself. That makes it:

- **Fast:** used in game engines (Unreal), browsers (Chrome), databases, trading systems,
  operating systems, robots, cars, and AI frameworks (PyTorch, TensorFlow cores).
- **Powerful but sharp:** like a chef's knife. Great in skilled hands, but it will cut you if
  you are careless. This course teaches both the power *and* the safety habits.

### C++ versions (like phone updates)

| Version | Year | Big additions |
|---------|------|---------------|
| C++98/03 | 1998 | The original standard: classes, templates, STL |
| **C++11** | 2011 | **"Modern C++" begins**: `auto`, lambdas, smart pointers, move semantics |
| C++14 / 17 | 2014 / 2017 | `std::optional`, `std::string_view`, structured bindings, `if constexpr` |
| **C++20** | 2020 | **This course**: concepts, ranges, coroutines, modules, `<=>` |
| C++23 | 2023 | `std::expected`, `std::print` (shown in later lessons) |

> 🧠 **Senior note:** Companies still maintain old C++ code. You will read `new`/`delete` and raw
> pointers in legacy code, so this course teaches them, but you should *write* modern C++.

---

## ⚠️ Common misunderstandings

- "More RAM makes my program faster." Only if you were running out of it. Speed comes mostly from
  the CPU and **how well your code uses memory** (Lesson 58).
- "The compiler fixes my logic." No. It checks grammar, not meaning. `int total = a - b;` when you
  meant `+` compiles perfectly and is still wrong.
- "Bigger number = more bits needed." Yes. That is why types have limits (Lesson 05, 07).

---

## ✅ Check yourself

1. Which part of the computer does the actual calculating?
2. What is `00001010` in decimal?
3. How many different values fit in one byte?
4. What does `&age` give you?
5. Which build stage produces "undefined reference" errors?

<details><summary>Answers</summary>

1. The CPU.
2. 8 + 2 = **10**.
3. 256 (0–255).
4. The memory address where `age` lives.
5. The linker.
</details>

---

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 02: Programming Thinking](../02.ProgrammingThinking/README.md)
