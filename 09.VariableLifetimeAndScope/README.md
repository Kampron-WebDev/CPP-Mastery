# Lesson 09: Variable Lifetime and Scope

> **In one sentence:** **Scope** is *where* in the code a name can be seen; **lifetime** is
> *when* the variable exists in memory. Getting these right avoids name clashes and ghost values.

---

## 🎯 You will learn

- Local vs global scope.
- Blocks `{ }` create new scopes.
- Shadowing (a name hiding another name).
- Automatic vs static lifetime.

---

## 🧸 The Big Idea: rooms in a house

Every pair of curly braces `{ }` is a **room**. A variable made in a room lives in that room:
- Anyone **inside the room** (or in a smaller room inside it) can see it.
- When you **leave the room**, the variable is destroyed. It's like a sandcastle washed away by the tide.
- A **global** variable is painted on the outside wall of the house: everyone can see it, and
  everyone can scribble on it. That's why globals are risky.

```cpp
int globalScore{0};          // outside every room: global scope, lives the whole program

int main()
{                            // ┌── room: main
    int lives{3};            // │   lives exists from here...
    {                        // │  ┌── inner room
        int bonus{10};       // │  │   bonus exists only in here
        lives += bonus;      // │  │   ✅ can see lives (outer room)
    }                        // │  └── bonus destroyed here
    // bonus = 5;            // │   ❌ error: bonus is out of scope
}                            // └── lives destroyed here
```

---

## 📚 Step by step

### 1. Local scope
Variables declared inside a function or block. **Automatic lifetime**: created when the line
runs, destroyed at the closing `}`. They usually live on the **stack** (Lesson 23).

### 2. Global scope
Declared outside all functions. Live from program start to end (**static lifetime**).

### 3. Shadowing
```cpp
int x{1};
{
    int x{2};                 // hides the outer x inside this block
    std::cout << x;           // 2
    std::cout << ::x;         // :: means "the global one"; only works for globals
}
```
Legal, but confusing. Avoid it and give things different names. (`-Wshadow` warns about it.)

### 4. Static local variables (preview of Lesson 22)
`static int count{0};` inside a function keeps its value **between calls**. It has local *scope* but static *lifetime*.

| | Scope (who can see it) | Lifetime (when it exists) |
|---|---|---|
| local variable | its block | until the block ends |
| global variable | the whole file (and more) | the whole program |
| `static` local | its block | the whole program |

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [9.2VariableScope](9.2VariableScope/main.cpp) | Global vs local; printing addresses to prove they are different variables |

## ⚠️ Common mistakes

- Using a variable after its block ended ("was not declared in this scope").
- Returning the address of a local variable (it's destroyed at `}`, so you hold a **dangling** pointer. Lesson 13).
- Too many globals: any function can change them, so bugs are hard to trace.

## 🧠 Senior developer notes

- **Smallest possible scope** is a professional habit: declare variables right before use, inside the tightest block.
- Global *constants* (`constexpr`) are fine. Global *mutable* state is the enemy of testing and threads.
- The rule "destroyed at the closing brace" is the foundation of **RAII** (Lesson 52), the most important idiom in C++.

## ✅ Check yourself

1. Where can a variable declared inside an `if` block be used?
2. What is the lifetime of a global variable?
3. What is shadowing, and why avoid it?

<details><summary>Answers</summary>

1. Only inside that `if` block (and blocks nested inside it).
2. The whole program run.
3. An inner name hiding an outer one with the same name; it makes readers (and you) confuse the two.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 10: Flow Control](../10.FlowControl/README.md)
