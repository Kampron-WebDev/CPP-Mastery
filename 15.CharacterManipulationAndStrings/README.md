# Lesson 15: Characters and Strings

> **In one sentence:** Text in C++ comes in two flavours: old **C-strings** (a `char` array ending
> in `'\0'`) and modern **`std::string`** (a smart, growable text box). Learn both, use `std::string`.

---

## 🎯 You will learn

- Testing and changing characters (`<cctype>`).
- C-string functions (`<cstring>`): `strlen`, `strcmp`, `strcpy`, `strcat`.
- `std::string`: creating, joining, accessing, size/capacity, modifying, comparing, searching, replacing.
- Converting between strings and numbers.
- Escape sequences and raw string literals.
- `std::string_view`: looking at text without copying it.

---

## 🧸 The Big Idea: beads on a string

A string is a row of character "beads":

```
 C-string:   char name[]{"Ada"};
             ┌───┬───┬───┬────┐
             │ A │ d │ a │ \0 │   ← '\0' is the "stop" bead. You must manage it yourself.
             └───┴───┴───┴────┘

 std::string: std::string name{"Ada"};
             ┌─────────────────────────────┐
             │ size: 3   capacity: 15      │   ← knows its own length,
             │ data: A d a                 │     grows automatically,
             └─────────────────────────────┘     frees its own memory
```

A C-string is a **necklace you have to tie off yourself**. A `std::string` is a **magic necklace
that grows and ties itself**.

---

## 📚 Step by step

### 1. Characters ([15.2CharacterManipulation](15.2CharacterManipulation/main.cpp))
```cpp
#include <cctype>
std::isalpha(c); std::isdigit(c); std::isspace(c); std::isupper(c); std::ispunct(c);
std::toupper(c); std::tolower(c);
```

### 2. C-strings ([15.3](15.3CStringManipulation/main.cpp), [15.4](15.4CStringConcatenationAndCopy/main.cpp))
```cpp
#include <cstring>
std::strlen("hello");          // 5 (doesn't count '\0')
std::strcmp(a, b);             // 0 if equal, <0 or >0 otherwise
std::strcpy(dest, src);        // ⚠️ dest must be big enough, or you overflow!
std::strcat(dest, src);        // ⚠️ same danger
```
These functions caused decades of buffer-overflow security bugs. Know them; avoid them in new code.

### 3. `std::string` basics ([15.6](15.6DeclaringAndUsingStdString/main.cpp)–[15.9](15.9StdStringSizeAndCapacity/main.cpp))
```cpp
#include <string>
std::string first{"Ada"};
std::string full = first + " " + "Lovelace";   // join with +
full += "!";                                    // append
full[0];  full.at(0);                           // 'A' (at() checks bounds)
full.front(); full.back();
full.size();     // number of chars
full.empty();    // true if size()==0
full.capacity(); // room reserved before it must grow
```

### 4. Modifying ([15.10](15.10ModifyingStdStrings/main.cpp), [15.13](15.13StdStringReplacingCopyingResizingSwapping/main.cpp))
`insert`, `erase`, `push_back`, `pop_back`, `clear`, `replace`, `resize`, `swap`, `substr`.

### 5. Comparing ([15.11](15.11ComparingStdStrings/main.cpp), [15.12](15.12StdStringCompare/main.cpp))
`==`, `!=`, `<` work (alphabetical, character by character, **case-sensitive**: `"Zebra" < "apple"` because 'Z' is 90 and 'a' is 97).

### 6. Searching ([15.14SearchingStdString](15.14SearchingStdString/main.cpp))
```cpp
auto pos = text.find("cat");
if (pos != std::string::npos) { /* found at pos */ }   // npos = "not found"
```
Also `rfind`, `find_first_of`, `find_last_not_of`, and C++20's `starts_with` / `ends_with`, and C++23's `contains`.

### 7. Numbers ↔ strings ([15.15](15.15TransformingStdStringFromToNumbers/main.cpp))
```cpp
std::string s = std::to_string(42);   // "42"
int n = std::stoi("123");             // 123 (throws if not a number)
double d = std::stod("3.14");
```

### 8. Escapes and raw strings ([15.16](15.16EscapeSequences/main.cpp), [15.17](15.17RawStringLiterals/main.cpp))
`\n` newline, `\t` tab, `\"` quote, `\\` backslash.
Raw string: `R"(C:\Users\Ada\file.txt)"`: no escaping needed. Great for paths and regex.

### 9. Copies vs views ([15.18](15.18CopiedStrings/main.cpp), [15.19StringView](15.19StringView/main.cpp))
Every `std::string` copy allocates and copies bytes. `std::string_view` is a **window** onto
existing text: a pointer + length, with no copy:
```cpp
void greet(std::string_view name) { std::cout << "Hi " << name; }   // accepts string, char*, literal, without copying
```
⚠️ A view doesn't own the text. If the original dies, the view **dangles**.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [15.2CharacterManipulation](15.2CharacterManipulation/main.cpp) | `<cctype>` |
| [15.3CStringManipulation](15.3CStringManipulation/main.cpp) | `strlen`, `strcmp`, `strchr` … |
| [15.4CStringConcatenationAndCopy](15.4CStringConcatenationAndCopy/main.cpp) | `strcat`, `strcpy` |
| [15.6DeclaringAndUsingStdString](15.6DeclaringAndUsingStdString/main.cpp) | Creating strings |
| [15.7ConcatenatingStdStrings](15.7ConcatenatingStdStrings/main.cpp) | `+`, `+=`, `append` |
| [15.8AccessingCharactersInStdString](15.8AccessingCharactersInStdString/main.cpp) | `[]`, `at`, `front`, `back` |
| [15.9StdStringSizeAndCapacity](15.9StdStringSizeAndCapacity/main.cpp) | `size`, `capacity`, `reserve` |
| [15.10ModifyingStdStrings](15.10ModifyingStdStrings/main.cpp) | `insert`, `erase`, `push_back` |
| [15.11ComparingStdStrings](15.11ComparingStdStrings/main.cpp) | `==`, `<` … |
| [15.12StdStringCompare](15.12StdStringCompare/main.cpp) | `.compare()` |
| [15.13StdStringReplacingCopyingResizingSwapping](15.13StdStringReplacingCopyingResizingSwapping/main.cpp) | `replace`, `resize`, `swap` |
| [15.14SearchingStdString](15.14SearchingStdString/main.cpp) | `find`, `npos` |
| [15.15TransformingStdStringFromToNumbers](15.15TransformingStdStringFromToNumbers/main.cpp) | `to_string`, `stoi` |
| [15.16EscapeSequences](15.16EscapeSequences/main.cpp) | `\n \t \"` |
| [15.17RawStringLiterals](15.17RawStringLiterals/main.cpp) | `R"(...)"` |
| [15.18CopiedStrings](15.18CopiedStrings/main.cpp) | The cost of copies |
| [15.19StringView](15.19StringView/main.cpp) | `std::string_view` |

## ⚠️ Common mistakes

- Comparing C-strings with `==` (compares **addresses**!). Use `strcmp` or `std::string`.
- `"Hello" + " World"`: two `const char*`, which can't be added. Make one a `std::string`.
- Using `int` for `find` results: store in `std::size_t` / `auto` and compare with `npos`.
- `std::toupper` on a `char` with negative values: cast to `unsigned char` first.

## 🧠 Senior developer notes

- Function parameters for read-only text: **`std::string_view`** (or `const std::string&`).
- Short strings (≤15 chars in GCC) live *inside* the string object with no heap allocation (Small String Optimization, SSO).
- Real-world text is often **UTF-8**: `size()` counts **bytes**, not visible letters ("é" is 2 bytes).

## ✅ Check yourself

1. How long is `"cat"` as a C-string array? What is `strlen("cat")`?
2. How do you check if `find` failed?
3. Why is `std::string_view` cheaper than `std::string` as a parameter?
4. `std::string{"Apple"} < std::string{"apple"}`: true or false?

<details><summary>Answers</summary>

1. 4 chars (with `'\0'`); `strlen` = 3.
2. `if (pos == std::string::npos)`.
3. It never copies or allocates; it's just a pointer + length.
4. True: 'A' (65) < 'a' (97).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 16: Functions](../16.Functions/README.md)
