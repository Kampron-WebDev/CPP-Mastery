# Lesson 19: Getting Things out of Functions

> **In one sentence:** A function can hand results back by **return value**, through
> **output parameters**, or with **`std::optional`** when "no result" is a real possibility.

---

## 🎯 You will learn

- Input and output parameters.
- Returning by value, by reference, by pointer (and the dangling danger).
- `auto` return type deduction.
- `std::optional`: returning "maybe a value".

---

## 🧸 The Big Idea: asking a friend to fetch something

1. **Return value:** your friend **brings you** the thing. (Cleanest.)
2. **Output parameter:** you give your friend **an empty box**; they put the thing in it.
3. **`std::optional`:** your friend brings back a box that **might be empty**: "sorry, the shop was out of milk". You check before using it.
4. **Returning a reference/pointer to a local:** your friend gives you **directions to a sandcastle
   that the tide already washed away**. ❌ Dangling!

---

## 📚 Step by step

### 1. Input and output parameters ([19.2](19.2InputAndOutputParameters/main.cpp))
```cpp
void divide(int a, int b, int& quotient, int& remainder);   // a, b in; quotient, remainder out
```
Works, but the call `divide(7, 2, q, r)` doesn't *show* which are outputs. Prefer returning.

### 2. Return by value ([19.3](19.3ReturningFromFunctionsByValue/main.cpp))
```cpp
std::vector<int> makeList() { std::vector<int> v(1'000'000); return v; }
```
"Isn't returning a big object slow?" **No.** Compilers apply **copy elision / RVO**
(Return Value Optimization): the object is built directly in the caller's space. Returning by value is the default.

### 3. Return by reference / pointer ([19.4](19.4ReturningByReference/main.cpp), [19.5](19.5ReturningByPointer/main.cpp), [19.6](19.6ReturningArrayElementIndexByPointer/main.cpp))
Only safe if the object **outlives the function**, e.g. an element of an array that was passed in:
```cpp
int& largest(int arr[], int size);   // ✅ refers into the caller's array
int& bad() { int x{5}; return x; }   // ❌ x dies at } → dangling reference
```

### 4. `auto` return types ([19.7](19.7BareAutoTypeDeduction/main.cpp)–[19.10](19.10FunctionDefinitionsWithReturnTypeDeduction/main.cpp))
```cpp
auto area(double w, double h) { return w * h; }   // compiler deduces double
```
⚠️ Bare `auto` **drops references and const**: `auto x = someRef;` makes a copy. Use `auto&` / `const auto&` to keep the reference.
All `return` statements must agree on one type.

### 5. `std::optional` ([19.11](19.11OptionalOutputFromFunctions/main.cpp)–[19.13](19.13OptionalOutputWithStdOptional/main.cpp))
```cpp
#include <optional>
std::optional<int> findIndex(const std::string& s, char c)
{
    for (int i = 0; i < std::ssize(s); ++i)
        if (s[i] == c) return i;       // a value
    return std::nullopt;               // "nothing"
}

if (auto idx = findIndex("hello", 'l')) std::cout << *idx;   // 2
std::cout << findIndex("hello", 'z').value_or(-1);           // -1
```
Before `optional`, people returned "magic" values like `-1` or `nullptr`, and callers forgot to check them.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [19.2InputAndOutputParameters](19.2InputAndOutputParameters/main.cpp) | Out-params via references |
| [19.3ReturningFromFunctionsByValue](19.3ReturningFromFunctionsByValue/main.cpp) | Return by value, no hidden copies |
| [19.4ReturningByReference](19.4ReturningByReference/main.cpp) | Safe and unsafe references |
| [19.5ReturningByPointer](19.5ReturningByPointer/main.cpp) | Returning addresses |
| [19.6ReturningArrayElementIndexByPointer](19.6ReturningArrayElementIndexByPointer/main.cpp) | Pointer into caller's array |
| [19.7BareAutoTypeDeduction](19.7BareAutoTypeDeduction/main.cpp) | `auto` drops `&` and `const` |
| [19.8FunctionReturnTypeDeduction](19.8FunctionReturnTypeDeduction/main.cpp) | `auto` return |
| [19.9ReturnTypeDeductionWithReferences](19.9ReturnTypeDeductionWithReferences/main.cpp) | `auto&` return |
| [19.10FunctionDefinitionsWithReturnTypeDeduction](19.10FunctionDefinitionsWithReturnTypeDeduction/main.cpp) | Definition-order rules |
| [19.11OptionalOutputFromFunctions](19.11OptionalOutputFromFunctions/main.cpp) | The problem `optional` solves |
| [19.12IntroducingStdOptional](19.12IntroducingStdOptional/main.cpp) | `optional` API |
| [19.13OptionalOutputWithStdOptional](19.13OptionalOutputWithStdOptional/main.cpp) | Using it for real |

## ⚠️ Common mistakes

- Returning a reference or pointer to a local variable.
- Calling `.value()` / `*opt` on an empty optional without checking.
- Using output parameters when a return value (or a small struct, Lesson 26) would be clearer.

## 🧠 Senior developer notes

- To return several values, return a `struct` or `std::pair`/`std::tuple` and unpack with **structured bindings**:
  `auto [quotient, remainder] = divide(7, 2);` (Lesson 27).
- For "a value **or an error message**", C++23 has `std::expected<T, E>` (Lesson 51).
- Don't write `return std::move(local);`, because it *prevents* RVO.

## ✅ Check yourself

1. Why is returning a `std::vector` by value usually fast?
2. What's wrong with `const std::string& name() { std::string s{"x"}; return s; }`?
3. How do you check whether an optional has a value?

<details><summary>Answers</summary>

1. Copy elision / RVO (or move semantics) avoid the copy.
2. It returns a reference to a local that is destroyed. The reference dangles.
3. `if (opt)`, `opt.has_value()`, or use `opt.value_or(default)`.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 20: Function Overloading](../20.FunctionOverloading/README.md)
