# Lesson 22: Functions, the Misfits (static variables, inline, recursion)

> **In one sentence:** Three special function tools: variables that **remember** between calls
> (`static`), functions the compiler may **paste in place** (`inline`), and functions that **call themselves** (recursion).

---

## 🎯 You will learn

- `static` local variables.
- `inline` functions (and what `inline` *really* means today).
- Recursion: base case, recursive case, and the call stack.

---

## 🧸 The Big Idea

- **`static` variable** = a **tally counter** clipped to the function. Normal local variables are
  wiped every time you leave; the static one keeps its count.
- **`inline`** = instead of phoning a friend to ask the answer (a function call), you **copy their
  answer sheet into your notes** (the body is pasted at the call site).
- **Recursion** = **Russian nesting dolls**. To open the big doll, you open a smaller doll inside,
  and so on until the **tiniest doll** that doesn't open (the **base case**). Then you work your way back out.

---

## 📚 Step by step

### 1. Static variables ([22.2StaticVariables](22.2StaticVariables/main.cpp))
```cpp
int nextId()
{
    static int id{0};   // created ONCE, the first time the line runs
    return ++id;        // 1, 2, 3 ... on each call
}
```

### 2. Inline functions ([22.3InlineFunctions](22.3InlineFunctions/main.cpp))
`inline int max(int a, int b) { return a > b ? a : b; }`
- Historically: a *hint* to paste the body at each call (avoids call overhead).
- Today: compilers decide inlining themselves (at `-O2`). The **real** modern meaning of `inline` is
  **"this definition may appear in several .cpp files"**: needed for functions defined in headers (Lesson 32).

### 3. Recursion ([22.4RecursiveFunctions](22.4RecursiveFunctions/main.cpp))
```cpp
long long factorial(int n)
{
    if (n <= 1) return 1;            // BASE CASE: stop here
    return n * factorial(n - 1);     // RECURSIVE CASE: a smaller version of the same problem
}
```
```
 factorial(4)
 = 4 * factorial(3)
       = 3 * factorial(2)
             = 2 * factorial(1)
                   = 1            ← base case, now unwind
             = 2 * 1 = 2
       = 3 * 2 = 6
 = 4 * 6 = 24
```
Each call gets its **own frame** on the **call stack** (Lesson 23). No base case means infinite calls,
which ends in a **stack overflow** crash.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [22.2StaticVariables](22.2StaticVariables/main.cpp) | Remembering between calls |
| [22.3InlineFunctions](22.3InlineFunctions/main.cpp) | `inline` |
| [22.4RecursiveFunctions](22.4RecursiveFunctions/main.cpp) | Recursive sum/factorial |

## ⚠️ Common mistakes

- Missing or wrong base case → stack overflow.
- The recursive call doesn't get **closer** to the base case (`f(n)` calling `f(n)`).
- Naive recursive Fibonacci: `fib(n-1) + fib(n-2)` recomputes the same values exponentially many times.

## 🧠 Senior developer notes

- Recursion is natural for **trees**, **divide and conquer** (merge sort, quicksort), and **backtracking**
  (mazes, sudoku). Lesson 54 uses it heavily.
- Anything recursive can be written with a loop + your own stack; do that when depth could be huge.
- **Memoization** (caching results) turns exponential recursion into linear time.
- `static` locals in multithreaded code: initialization is thread-safe since C++11, but *modifying* them is not.

## ✅ Check yourself

1. What happens to a normal local variable when the function returns? A `static` one?
2. What are the two parts every recursive function needs?
3. What does `sum(3)` return if `sum(n) = n + sum(n-1)` and `sum(0) = 0`?

<details><summary>Answers</summary>

1. The normal one is destroyed; the static one keeps its value until the program ends.
2. A base case and a recursive case that moves towards it.
3. 3 + 2 + 1 + 0 = 6.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 23: The Call Stack and Debugging](../23.FunctionCallStackD_ebugging/README.md)
