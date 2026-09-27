# Lesson 03: First Steps

> **In one sentence:** Every C++ program starts at `main()`, runs statements from top to bottom,
> and talks to the world through `std::cout` (output) and `std::cin` (input).

---

## 🎯 You will learn

- The anatomy of a C++ program: `#include`, `main`, statements, `return`.
- Comments: notes for humans that the compiler ignores.
- Errors vs warnings (compile-time, link-time, run-time).
- Writing your own small functions.
- Printing with `std::cout`, reading with `std::cin` and `std::getline`.

---

## 🧸 The Big Idea

A program is like a **play script** read by an actor who only ever does exactly what is written,
line by line, starting at the scene called **`main`**.

```cpp
#include <iostream>          // 1. "Bring me the toolbox for input/output"

int main()                   // 2. The play ALWAYS starts here
{                            // 3. Curly braces = the start of main's body
    std::cout << "Hi!\n";    // 4. A statement: print Hi!  (ends with ;)
    return 0;                // 5. "The play ended well" (0 = success)
}                            // 6. End of main's body
```

| Piece | Kid version | Real meaning |
|-------|-------------|--------------|
| `#include <iostream>` | Borrow the "talking" toolbox | Paste in the declarations of the input/output library |
| `int main()` | The front door | The function the operating system calls to start your program |
| `{ }` | A box that holds steps | A *block* of statements |
| `;` | A full stop | Ends one statement |
| `std::` | "from the standard toolbox" | The standard library **namespace** (Lesson 31) |
| `return 0;` | "All good!" | Exit code 0 means success to the operating system |

---

## 📚 Step by step

### 1. Statements run top to bottom
The computer runs one statement, then the next, like reading a list. See [3.2FirstCppProgram](3.2FirstCppProgram/main.cpp).

### 2. Comments ([3.3Comments](3.3Comments/main.cpp))
```cpp
// A one-line comment
/* A comment that can
   span many lines */
```
> 🧠 Good comments explain **why**, not **what**. `i++; // add 1 to i` is noise.
> `// retry once: the sensor sometimes misses the first read` is gold.

### 3. Three kinds of errors ([3.4ErrorsWarnings](3.4ErrorsWarnings/main.cpp))
| Kind | When | Example |
|------|------|---------|
| **Compile-time** | While building | Missing `;`, misspelled name |
| **Link-time** | While joining files | Function declared but never defined |
| **Run-time** | While running | Dividing by zero, wrong result (logic error) |

Warnings: "It builds, but I think you made a mistake." **Always fix warnings.**

### 4. Functions: named mini-programs ([3.5StatementsAndFunctions](3.5StatementsAndFunctions/main.cpp))
```cpp
int add(int a, int b)       // takes two ints, gives back one int
{
    return a + b;
}

int main()
{
    int sum = add(3, 4);    // "call" the function; sum becomes 7
}
```
A function is like a **vending machine**: put things in (arguments), press the button (call), get something out (return value). Lesson 16 goes deep.

### 5. Input and output ([3.6DataInputAndOutput](3.6DataInputAndOutput/main.cpp))
```cpp
std::cout << "Age: " << age << '\n';   // << pushes data OUT to the screen
std::cin >> age;                       // >> pulls data IN from the keyboard
std::getline(std::cin, fullName);      // reads a whole line, spaces included
std::cerr << "Something broke\n";      // error output
```

The arrows show the direction the data flows: `cout << x` sends x **to** the console; `cin >> x` sends keyboard input **into** x.

⚠️ `std::cin >> name` stops at the first space. "Ada Lovelace" becomes just "Ada". Use `std::getline` for full lines.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [3.2FirstCppProgram](3.2FirstCppProgram/main.cpp) | The minimum program; statements in order |
| [3.3Comments](3.3Comments/main.cpp) | `//` and `/* */` comments |
| [3.4ErrorsWarnings](3.4ErrorsWarnings/main.cpp) | Break it on purpose to see error messages |
| [3.5StatementsAndFunctions](3.5StatementsAndFunctions/main.cpp) | Defining and calling a function |
| [3.6DataInputAndOutput](3.6DataInputAndOutput/main.cpp) | `cout`, `cin`, `cerr`, `clog`, `getline` |
| `C++ 20 Template Project` | Empty starter to copy for your own experiments |

---

## ⚠️ Common mistakes

- Forgetting `;` at the end of a statement.
- Writing `cout` without `std::` (or without `#include <iostream>`).
- Using `>>` with `cout` or `<<` with `cin` (the arrows point the way data flows).
- Mixing `std::cin >> x;` then `std::getline(...)`: the leftover Enter key makes `getline` read an
  empty line. Fix: `std::cin >> std::ws;` before `getline`, or `std::cin.ignore()`.
- `using namespace std;` at the top of every file. It's fine for tiny experiments but
  causes name clashes in real projects. Professionals write `std::`.

## 🧠 Senior developer notes

- `'\n'` vs `std::endl`: `endl` also **flushes** the output buffer, which is slow in loops. Use `'\n'`.
- `main` may omit `return 0;`. The compiler adds it for `main` only.
- Exit codes matter: scripts and other programs check them. Return non-zero when your program fails.

---

## ✅ Check yourself

1. Where does every C++ program start?
2. What does `#include <iostream>` give you?
3. Why does `std::cin >> name;` only read "Ada" from "Ada Lovelace"?
4. What is the difference between a compile-time and a run-time error?

<details><summary>Answers</summary>

1. The `main()` function.
2. The input/output tools: `std::cout`, `std::cin`, `std::cerr`, `std::clog`.
3. `>>` stops reading at whitespace. Use `std::getline(std::cin, name)`.
4. Compile-time errors stop the build (grammar); run-time errors happen while the program runs (crash or wrong result).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 04: Variables and Data Types](../04.VariablesAndDatatypes/README.md)
