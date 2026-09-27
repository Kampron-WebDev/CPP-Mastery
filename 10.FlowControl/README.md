# Lesson 10: Flow Control

> **In one sentence:** Flow control lets your program **make decisions**, so it can take a
> different path depending on the situation, like a "choose your own adventure" book.

---

## 🎯 You will learn

- `if`, `else if`, `else`.
- `switch` with `case`, `break`, `default`, and fall-through.
- Short-circuit evaluation.
- The ternary operator `? :`.
- `if constexpr`, `if` with initializer, `switch` with initializer.
- How scope works inside decisions.

---

## 🧸 The Big Idea: a fork in the road

```
                 ┌──────────────┐
                 │ Is it raining?│
                 └──────┬───────┘
                 yes ◄──┴──► no
                  │           │
          take umbrella   wear sunglasses
                  └─────┬─────┘
                   go outside
```

That picture **is** an `if` statement:
```cpp
if (isRaining) {
    std::cout << "Take an umbrella\n";
} else {
    std::cout << "Wear sunglasses\n";
}
std::cout << "Go outside\n";
```

---

## 📚 Step by step

### 1. `if` / `else` ([10.2IfStatements](10.2IfStatements/main.cpp))
The condition in `( )` must be (or convert to) `bool`. The block runs only if it's `true`.

### 2. `else if` chains ([10.3ElseIf](10.3ElseIf/main.cpp))
```cpp
if (score >= 90)      grade = 'A';
else if (score >= 80) grade = 'B';   // only checked if the first was false
else if (score >= 70) grade = 'C';
else                  grade = 'F';
```
The **first** true branch wins; the rest are skipped. Order matters!

### 3. `switch` ([10.4Switch](10.4Switch/main.cpp))
For choosing between many **exact integer/char/enum values**:
```cpp
switch (command) {
    case 'a': moveLeft();  break;
    case 'd': moveRight(); break;
    case 'q': quit();      break;
    default:  std::cout << "Unknown key\n";
}
```
⚠️ Forget `break` and execution **falls through** into the next case. Sometimes on purpose
(mark it with `[[fallthrough]];`), usually a bug.

### 4. Short-circuit evaluation ([10.5ShortCircuitEvaluation](10.5ShortCircuitEvaluation/main.cpp))
- `A && B`: if A is false, B is **never evaluated** (the answer is already false).
- `A || B`: if A is true, B is **never evaluated**.

That lets you write safe checks: `if (count != 0 && total / count > 10)` never divides by 0.

### 5. Integers as conditions ([10.6IntegralLogicConditions](10.6IntegralLogicConditions/main.cpp))
`0` means false, **any other number** means true. `if (items)` = "if items is not zero".

### 6. Ternary operator ([10.7TernaryOperators](10.7TernaryOperators/main.cpp))
`condition ? valueIfTrue : valueIfFalse` is a tiny `if` that **produces a value**:
```cpp
std::string label = (age >= 18) ? "adult" : "child";
```
Great for short choices; don't nest them into puzzles.

### 7. `if constexpr` ([10.8IfConstexpr](10.8IfConstexpr/main.cpp))
Decided **at compile time**: the discarded branch isn't even compiled. Shines with templates (Lesson 24).

### 8. `if` / `switch` with initializer ([10.9](10.9IfWithInitializer/main.cpp), [10.10](10.10SwitchWithInitializer/main.cpp))
```cpp
if (int speed = readSensor(); speed > 120) {
    std::cout << "Too fast: " << speed << '\n';
}   // speed doesn't exist out here: smallest scope ✅
```

### 9. Scope in decisions ([10.11](10.11VariableScopeRevisited/main.cpp), [10.12SwitchScope](10.12SwitchScope/main.cpp))
Variables declared inside a `case` need their own `{ }` braces, or the compiler complains that a jump "crosses initialization".

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [10.2IfStatements](10.2IfStatements/main.cpp) | Basic `if`/`else`, nesting |
| [10.3ElseIf](10.3ElseIf/main.cpp) | Chains of conditions |
| [10.4Switch](10.4Switch/main.cpp) | `case`, `break`, `default` |
| [10.5ShortCircuitEvaluation](10.5ShortCircuitEvaluation/main.cpp) | Functions that never get called |
| [10.6IntegralLogicConditions](10.6IntegralLogicConditions/main.cpp) | Numbers as true/false |
| [10.7TernaryOperators](10.7TernaryOperators/main.cpp) | `? :` |
| [10.8IfConstexpr](10.8IfConstexpr/main.cpp) | Compile-time branches |
| [10.9IfWithInitializer](10.9IfWithInitializer/main.cpp) | `if (init; cond)` |
| [10.10SwitchWithInitializer](10.10SwitchWithInitializer/main.cpp) | `switch (init; value)` |
| [10.11VariableScopeRevisited](10.11VariableScopeRevisited/main.cpp) | Scope of variables in branches |
| [10.12SwitchScope](10.12SwitchScope/main.cpp) | Braces inside `case` |

## ⚠️ Common mistakes

- `if (x = 5)` instead of `if (x == 5)`.
- A stray semicolon: `if (ok); { ... }`. The block always runs!
- Missing `break` in `switch`.
- Checking ranges in the wrong order (`>= 70` before `>= 90` means nobody gets an A).

## 🧠 Senior developer notes

- **Guard clauses** beat deep nesting. Handle the bad cases first and `return` early; then the main logic stays flat and readable.
  ```cpp
  if (!file) return error;
  if (size == 0) return empty;
  // happy path here, not buried 4 levels deep
  ```
- Always put braces `{}` around `if` bodies, even one line. Apple's famous "goto fail" SSL bug came from a missing brace.
- `switch` on an `enum class` + `-Wall` warns you when you forget a case. That's a free safety net.

## ✅ Check yourself

1. In `if (a != 0 && b / a > 2)`, why is it safe when `a` is 0?
2. What happens in a `switch` without `break`?
3. Rewrite with a ternary: `if (n % 2 == 0) s = "even"; else s = "odd";`
4. What is the advantage of `if (auto x = f(); x > 0)`?

<details><summary>Answers</summary>

1. Short-circuit: `a != 0` is false, so the division is never evaluated.
2. Execution falls through into the next case(s).
3. `s = (n % 2 == 0) ? "even" : "odd";`
4. `x` only exists inside the `if`/`else`: smallest scope, no leftover variable.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 11: Loops](../11.Loops/README.md)
