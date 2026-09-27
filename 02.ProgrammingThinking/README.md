# Lesson 02: Programming Thinking

> **In one sentence:** Programming is not typing. It is **thinking clearly** about a problem,
> breaking it into tiny steps a machine can follow, and then typing those steps.

This is the lesson most courses skip, and it is the one that separates people who "know C++
syntax" from people who can **build things**. Come back to it often.

---

## 🎯 By the end of this lesson you can

- Use the **4-step problem-solving method** on any task.
- Break big problems into small ones (**decomposition**).
- Write **pseudocode** before code.
- **Trace** a program by hand with a trace table.
- Hunt for **edge cases** before they become bugs.

---

## 🧸 The Big Idea: the robot sandwich

Tell a robot to "make a sandwich". It does nothing. It doesn't know what that means.

You must say: *"Pick up the bread bag. Open it. Take out 2 slices. Put them on the plate.
Pick up the knife. Open the butter…"* Every. Single. Step.

A computer is that robot. It is **very fast** but **not smart**. Your job is to be the smart one:
turn a fuzzy wish ("make a sandwich") into exact steps. That skill is called
**algorithmic thinking**, and an **algorithm** is just *a recipe of exact steps*.

---

## 🪜 The 4-step method (use it for EVERY exercise)

This comes from mathematician George Pólya's *How to Solve It*.

### 1. Understand the problem
- Say it in your own words. What goes **in** (input)? What comes **out** (output)?
- Work **one example by hand**. If you can't do it by hand, you can't program it.

### 2. Make a plan
- Break it into small pieces (**decomposition**).
- Write the steps in **pseudocode**: plain English that looks a bit like code.

### 3. Carry out the plan
- Turn *one* pseudocode line into C++ at a time. Build and run **often** (every few lines).

### 4. Look back
- Test with normal values, **edge cases** (0, negative, huge, empty), and wrong input.
- Ask: *Can it be simpler? Are the names clear? Would a teammate understand it?*

---

## 🧩 Input → Process → Output

Almost every program has this shape:

```
 ┌─────────┐      ┌───────────┐      ┌──────────┐
 │  INPUT  │ ───► │  PROCESS  │ ───► │  OUTPUT  │
 │ 3 marks │      │ add, ÷ 3  │      │ average  │
 └─────────┘      └───────────┘      └──────────┘
```

**Example problem:** "Find the average of three test marks."

**Pseudocode:**
```
ask the user for mark1, mark2, mark3
total   ← mark1 + mark2 + mark3
average ← total / 3
show average
```

**C++** (see [Examples/01_InputProcessOutput](Examples/01_InputProcessOutput/main.cpp)):
```cpp
double m1, m2, m3;
std::cin >> m1 >> m2 >> m3;          // input
double average = (m1 + m2 + m3) / 3; // process
std::cout << average << '\n';        // output
```

Notice: the pseudocode is almost the same as the code. **That's the point.** The hard part is the
thinking; the typing is easy.

---

## 🔍 Tracing: be the computer

A **trace table** is how you run code *in your head* (and how you find bugs without a computer).
You write one column per variable and one row per step.

```cpp
int total = 0;
for (int i = 1; i <= 4; ++i) {
    total = total + i;
}
```

| Step | i | total | Note |
|------|---|-------|------|
| start | – | 0 | |
| 1 | 1 | 1 | 0 + 1 |
| 2 | 2 | 3 | 1 + 2 |
| 3 | 3 | 6 | 3 + 3 |
| 4 | 4 | 10 | 6 + 4 |
| end | 5 | 10 | 5 <= 4 is false, stop |

Run [Examples/02_TraceTable](Examples/02_TraceTable/main.cpp): it prints the same table so you can compare.

> 🧠 **Senior note:** Interviewers at top companies ask you to trace code on a whiteboard. It's also
> the fastest way to understand a bug report: trace the input that failed.

---

## 🕳️ Edge cases: where bugs hide

An **edge case** is an input at the "edge" of what is allowed. Always ask:

| Question | Example |
|----------|---------|
| What if it's **zero**? | dividing by a count of 0 students |
| What if it's **negative**? | age = -5 |
| What if it's **huge**? | 3 000 000 000 does not fit in an `int` |
| What if it's **empty**? | a name with no letters |
| What if it's **the wrong type**? | user types "abc" when you asked for a number |
| What about the **first / last** item? | off-by-one errors in loops |

See [Examples/03_EdgeCases](Examples/03_EdgeCases/main.cpp) for a divide-by-zero guard.

---

## 🛠️ Thinking tools that professionals use

- **Rubber duck debugging:** explain your code, line by line, out loud to a rubber duck (or a
  friend). You'll often find the bug halfway through the sentence.
- **Make it work → make it right → make it fast.** In that order. Never optimise broken code.
- **Small steps:** write 3–5 lines, build, run. Never write 100 lines and then compile.
- **Good names:** `average` beats `a`, `studentCount` beats `n2`. Code is read 10× more than written.
- **Divide and conquer:** if a problem feels too big, it's actually 3 smaller problems. Find them.
- **Read the error, then read your code, then search.** In that order.

---

## ⚠️ Common beginner traps

- Starting to type before understanding the problem.
- Testing only with "nice" numbers.
- Changing random things until it works ("programming by coincidence"). Instead, **predict**
  what a change will do *before* you make it.
- Being afraid of errors. Errors are information, not failure.

---

## ✅ Check yourself

1. What are the 4 steps of the problem-solving method?
2. What are the 3 parts of the Input-Process-Output model?
3. Trace: `int x = 2; x = x * 3; x = x - 1;` What is `x`?
4. Give 3 edge cases for "divide the bill between N friends".

<details><summary>Answers</summary>

1. Understand, Plan, Carry out, Look back.
2. Input, Process, Output.
3. 2 → 6 → **5**.
4. N = 0 (divide by zero!), N negative, bill of 0, a bill that doesn't divide evenly (cents).
</details>

---

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

These exercises use only `cin`, `cout`, arithmetic and `if`. Peek at Lessons 03–05 or 10 if you need them.

**Next:** [Lesson 03: First Steps](../03.FirstSteps/README.md)
