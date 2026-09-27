# Lesson 18: Arguments to the main Function

> **In one sentence:** Programs can receive words typed **after their name** on the command
> line (`rooster.exe add 3 4`), which is how real tools like `git commit -m "msg"` work.

---

## 🎯 You will learn

- `int main(int argc, char* argv[])`.
- Reading and converting arguments.
- Building a small command-line calculator.

---

## 🧸 The Big Idea: instructions on the envelope

When you run a program you can write extra words on the "envelope":

```
 > rooster.exe  add  3  4
   └─argv[0]─┘ └─1─┘└2┘└3┘       argc = 4 (how many words, including the program name)
```

- `argc` = **arg**ument **c**ount.
- `argv` = **arg**ument **v**alues: an array of C-strings.
- `argv[0]` is the program's own name.

---

## 📚 Step by step

### 1. Grab the arguments ([18.2GrabAndUseTheArguments](18.2GrabAndUseTheArguments/main.cpp))
```cpp
int main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i)
        std::cout << "argv[" << i << "] = " << argv[i] << '\n';
}
```

### 2. Convert text to numbers ([18.3CalculatorV1](18.3CalculatorV1/main.cpp), [18.4CalculatorV2](18.4CalculatorV2/main.cpp))
Every argument is **text**. `"3"` is not `3`. Convert with `std::stod(argv[2])`, `std::stoi(...)`, or `std::atof`.
**Always check `argc` first**. Reading `argv[5]` when only 3 were given is undefined behaviour.

### 3. How to pass arguments
- Terminal: `.\rooster.exe add 3 4`
- VS Code debugger: put them in `.vscode/launch.json` → `"args": ["add", "3", "4"]`.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [18.2GrabAndUseTheArguments](18.2GrabAndUseTheArguments/main.cpp) | Printing `argc`/`argv` |
| [18.3CalculatorV1](18.3CalculatorV1/main.cpp) | Calculator from arguments |
| [18.4CalculatorV2](18.4CalculatorV2/main.cpp) | Improved validation |

## ⚠️ Common mistakes

- Forgetting that `argv[0]` is the program name (so the first user argument is `argv[1]`).
- Not checking `argc` before reading `argv[i]`.
- `std::stoi("abc")` throws an exception. Validate or catch it (Lesson 38).

## 🧠 Senior developer notes

- Always print a **usage message** when arguments are wrong: `Usage: calc <add|sub> <a> <b>`.
- Return a non-zero exit code on errors so scripts can detect failure.
- Real projects use argument-parsing libraries (CLI11, cxxopts), but the idea is exactly this.

## ✅ Check yourself

1. For `app.exe -v file.txt`, what are `argc` and `argv[2]`?
2. Why must you convert `argv[1]` before doing maths?

<details><summary>Answers</summary>

1. `argc = 3`; `argv[2] = "file.txt"`.
2. Arguments are C-strings (text), not numbers.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 19: Getting Things out of Functions](../19.GettingThingsOutOfFuntions/README.md)
