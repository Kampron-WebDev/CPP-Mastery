# Lesson 11: Loops

> **In one sentence:** Loops let the computer **repeat** work (10 times, a million times, or
> "until the user says stop") without you writing the same line over and over.

---

## 🎯 You will learn

- `for`, range-based `for`, `while`, and `do-while` loops.
- Counting up, counting down, nested loops.
- `break` (leave the loop) and `continue` (skip to next round).
- Infinite loops (and how to use them on purpose).
- C++20 range-based `for` with an initializer.

---

## 🧸 The Big Idea: laps around a track

Imagine running laps. Before each lap you ask: *"Should I run another lap?"*

```cpp
for (int lap = 1; lap <= 5; ++lap) {      // start at lap 1; keep going while lap <= 5; after each lap add 1
    std::cout << "Running lap " << lap << '\n';
}
```

```
   ┌──────────────┐
   │ int lap = 1  │   ① start (runs once)
   └──────┬───────┘
          ▼
   ┌──────────────┐  no
   │ lap <= 5 ?   │──────► leave the loop
   └──────┬───────┘
          │ yes
          ▼
   ┌──────────────┐
   │  loop body   │   ② do the work
   └──────┬───────┘
          ▼
   ┌──────────────┐
   │   ++lap      │   ③ update, then back to the question
   └──────┬───────┘
          └────────► (back up to the check)
```

---

## 📚 Step by step

### 1. `for` loop ([11.2ForLoop](11.2ForLoop/main.cpp))
Best when you **know how many times**. The three parts: *init; condition; update*.
Multiple variables are allowed ([11.3](11.3ForLoopMultipleDeclarations/main.cpp)), and so is the comma operator ([11.4](11.4CommaOperator/main.cpp)).

### 2. Range-based `for` ([11.5RangeBasedForLoop](11.5RangeBasedForLoop/main.cpp))
"For **each** thing in this collection":
```cpp
int scores[]{90, 72, 85};
for (int s : scores) std::cout << s << ' ';
```
No index, so no off-by-one mistakes. **Your default choice** when you visit every element.

C++20 adds an initializer ([11.15](11.15ForLoopWithInitCondition/main.cpp)):
`for (int total{0}; int s : scores) { total += s; }`

### 3. `while` loop ([11.6WhileLoop](11.6WhileLoop/main.cpp))
Best when you **don't know how many times**: "keep going while…"
```cpp
while (balance < goal) {
    balance *= 1.05;
    ++years;
}
```

### 4. `do-while` ([11.8DoWhileLoop](11.8DoWhileLoop/main.cpp))
Runs the body **at least once**, then checks. Perfect for menus: *show menu, then ask "again?"*

### 5. Infinite loops ([11.9](11.9InfiniteLoops/main.cpp), [11.10](11.10InfiniteLoopPractice/main.cpp))
`while (true) { ... if (done) break; }`. This is fine **on purpose** (game loops, servers).
It's a bug when the condition can never become false by accident.

### 6. Counting down and nesting ([11.11](11.11DecrementingLoops/main.cpp), [11.12NestedLoops](11.12NestedLoops/main.cpp))
A loop inside a loop: the inner loop runs **completely** for every single step of the outer loop.
```cpp
for (int row = 1; row <= 3; ++row) {          // 3 rows
    for (int col = 1; col <= 4; ++col)        // 4 columns each → 12 stars total
        std::cout << '*';
    std::cout << '\n';
}
```

### 7. `break` and `continue` ([11.13BreakAndContinue](11.13BreakAndContinue/main.cpp))
- `break`: "stop the loop now, I'm done".
- `continue`: "skip the rest of this round, go to the next one".

### 8. Output speed ([11.7HugeLoopsWithOutput](11.7HugeLoopsWithOutput/main.cpp))
Printing is **slow**. `std::endl` in a loop of 1 000 000 flushes a million times. Use `'\n'`.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [11.2ForLoop](11.2ForLoop/main.cpp) | The classic counted loop |
| [11.3ForLoopMultipleDeclarations](11.3ForLoopMultipleDeclarations/main.cpp) | Two counters at once |
| [11.4CommaOperator](11.4CommaOperator/main.cpp) | `,` in loop updates |
| [11.5RangeBasedForLoop](11.5RangeBasedForLoop/main.cpp) | `for (x : collection)` |
| [11.6WhileLoop](11.6WhileLoop/main.cpp) | Condition-driven loop |
| [11.7HugeLoopsWithOutput](11.7HugeLoopsWithOutput/main.cpp) | Output performance |
| [11.8DoWhileLoop](11.8DoWhileLoop/main.cpp) | Body first, check after |
| [11.9InfiniteLoops](11.9InfiniteLoops/main.cpp) | Loops that never end |
| [11.10InfiniteLoopPractice](11.10InfiniteLoopPractice/main.cpp) | A menu-style loop |
| [11.11DecrementingLoops](11.11DecrementingLoops/main.cpp) | Counting down |
| [11.12NestedLoops](11.12NestedLoops/main.cpp) | Loops in loops |
| [11.13BreakAndContinue](11.13BreakAndContinue/main.cpp) | Leaving/skipping |
| [11.14FixCalculator](11.14FixCalculator/main.cpp) | Repeat-until-quit calculator |
| [11.15ForLoopWithInitCondition](11.15ForLoopWithInitCondition/main.cpp) | C++20 range-for with init |

## ⚠️ Common mistakes

- **Off-by-one**: `for (i = 0; i <= 10; ++i)` runs **11** times. For N items use `i < N`.
- Modifying the loop counter inside the body.
- `while (x != 10)` when `x` jumps by 3: it skips 10 forever. Prefer `<`.
- Counting down with `unsigned`: `for (unsigned i = 5; i >= 0; --i)` never ends (unsigned is always ≥ 0).
- Stray semicolon: `for (...);` then the body runs once, after the loop.

## 🧠 Senior developer notes

- Prefer range-based `for` and STL algorithms (Lessons 45–46) over hand-written index loops. Fewer places for bugs.
- Loop invariants: be able to say what is true at the start of every iteration. That's how you prove a loop correct.
- Big-O preview: one loop over N items ≈ N steps. A nested loop over N items ≈ N × N steps. With N = 100 000
  that's 10 billion. Lesson 54 teaches you to spot this.

## ✅ Check yourself

1. How many times does `for (int i = 3; i < 10; i += 2)` run? Values of i?
2. When would you choose `do-while` over `while`?
3. What's the difference between `break` and `continue`?
4. A 5×5 nested loop runs the inner body how many times?

<details><summary>Answers</summary>

1. 4 times: 3, 5, 7, 9.
2. When the body must run at least once (e.g. show a menu before asking).
3. `break` exits the loop; `continue` skips to the next iteration.
4. 25.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 12: Arrays](../12.Arrays/README.md)
