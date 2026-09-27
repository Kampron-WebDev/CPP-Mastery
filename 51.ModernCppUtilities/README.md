# Lesson 51: Modern C++ Utilities ⭐ NEW

> **In one sentence:** The modern standard library gives you small, powerful tools
> (`std::format`, `std::variant`, `std::span`, `std::chrono`, `std::expected`…) that replace
> whole categories of old, bug-prone code.

---

## 🎯 You will learn

- `std::format`: safe, Python-style text formatting (C++20).
- `std::tuple` and structured bindings.
- `std::variant` + `std::visit`: a type-safe "one of these types".
- `std::any`: "anything" (rarely the right choice).
- `std::span`: a view over any contiguous array (C++20).
- `std::chrono`: durations, clocks, timing code, dates.
- `std::expected`: a value **or** an error (C++23).
- `std::numbers`, and a recap of `std::optional` / `std::string_view`.

---

## 🧸 The Big Idea: a better toolbox

| Old way | Problem | Modern tool |
|---------|---------|-------------|
| `printf("%d", x)` / long `<<` chains | type bugs / hard to read | `std::format("{}", x)` |
| a `union` + a type flag | forget to check the flag → garbage | `std::variant` |
| `(int* data, int size)` parameters | size and pointer can disagree | `std::span<int>` |
| `time(NULL)`, mystery units | "is this seconds or ms?" | `std::chrono` with units in the type |
| return `-1` / throw for expected failures | ignored codes / heavy exceptions | `std::optional`, `std::expected` |

---

## 📚 Step by step

### 1. `std::format` ([Examples/01_Format](Examples/01_Format/main.cpp))
```cpp
#include <format>
std::string s = std::format("{} is {} years old", name, age);
std::format("{:>10}", "right");     // right-align in 10 chars
std::format("{:<10}|", "left");
std::format("{:^10}", "center");
std::format("{:.2f}", 3.14159);      // 3.14
std::format("{:08.3f}", 3.14159);    // 0003.142
std::format("{:x} {:#b}", 255, 5);   // ff 0b101
std::format("{0} {1} {0}", "a", "b");// a b a (positional)
```
Type-safe: a mismatch is a **compile error**, not a crash.
(C++23 adds `std::print`/`std::println`. On this MinGW toolchain they link but don't run, so we use `std::cout << std::format(...)`.)

### 2. Tuples and structured bindings
```cpp
std::tuple<std::string, int, double> t{"Ama", 19, 88.5};
auto [name, age, score] = t;
std::get<1>(t);   // 19
```
Prefer a named `struct` when the fields mean something. Tuples are for generic code and quick returns.

### 3. `std::variant` + `std::visit` ([Examples/02_VariantVisit](Examples/02_VariantVisit/main.cpp))
A variable that holds **exactly one of** several types, and always knows which:
```cpp
std::variant<int, double, std::string> v = 3.14;
v = "hello";                                 // now it's a string
std::holds_alternative<std::string>(v);      // true
std::visit([](const auto& x) { std::cout << x; }, v);   // runs the right code for the current type
```
Great for messages, tokens, JSON-like values, state machines, and **polymorphism without inheritance** (no heap, no vtable).

### 4. `std::any`
Holds *any* type; you must know the type to get it out (`std::any_cast<int>(a)`, which throws if wrong). Rarely the right choice; prefer `variant`.

### 5. `std::span` ([Examples/03_SpanAndChrono](Examples/03_SpanAndChrono/main.cpp))
```cpp
double average(std::span<const int> values);   // accepts vector, array, C-array, part of any of them
average(myVector);  average(myArray);  average(std::span{cArray});  average(std::span{v}.subspan(2, 3));
```
The modern answer to Lesson 16's "arrays forget their size". A span is (pointer + size) and never owns.

### 6. `std::chrono`
```cpp
using namespace std::chrono_literals;
auto timeout = 1500ms;                                  // the unit is part of the type!
std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(timeout);   // 1s
auto start = std::chrono::steady_clock::now();          // for measuring
/* work */
auto elapsed = std::chrono::steady_clock::now() - start;
std::format("{:%Y-%m-%d %H:%M}", std::chrono::system_clock::now());   // dates (C++20)
```
`steady_clock` for measuring durations (never jumps); `system_clock` for wall-clock dates.

### 7. `std::expected` (C++23) ([Examples/04_Expected](Examples/04_Expected/main.cpp))
```cpp
std::expected<int, std::string> parseAge(std::string_view s);   // an int OR an error message
if (auto r = parseAge("abc")) use(*r);
else std::cout << "Error: " << r.error();
```
Better than `optional` when the caller needs to know **why** it failed; lighter than exceptions for *expected* failures.
⚠️ Needs C++23: use the task **"C++: Build & Run this folder (C++23)"** (`Ctrl+Shift+P` → Run Task).

---

## 🗂️ Examples

| Folder | Shows |
|--------|-------|
| [01_Format](Examples/01_Format/main.cpp) | Formatting tables, numbers, alignment |
| [02_VariantVisit](Examples/02_VariantVisit/main.cpp) | Shapes as a variant; `std::visit` with overloaded lambdas |
| [03_SpanAndChrono](Examples/03_SpanAndChrono/main.cpp) | `std::span` parameters; timing code; durations |
| [04_Expected](Examples/04_Expected/main.cpp) | Error handling with `std::expected` (**C++23 task**) |

## ⚠️ Common mistakes

- A `std::span` or `std::string_view` outliving the data it looks at.
- `std::get<T>(variant)` when it holds a different type → throws `std::bad_variant_access`.
- Mixing up `steady_clock` (timing) and `system_clock` (calendar time).

## 🧠 Senior developer notes

- **Vocabulary types** (`optional`, `variant`, `expected`, `span`, `string_view`) make function signatures *self-documenting*.
  A reviewer can see "may fail", "one of these", "borrowed view" without reading the body.
- `std::variant` + `std::visit` is a strong alternative to inheritance when the set of types is **closed** (known in advance).

## ✅ Check yourself

1. Format `3.14159` right-aligned in 8 characters with 2 decimals.
2. When is `variant` better than a base class with virtual functions?
3. Why is `std::span<const int>` better than `(const int* p, int n)`?
4. Which clock should you use to time code?

<details><summary>Answers</summary>

1. `std::format("{:>8.2f}", 3.14159)` → `"    3.14"`.
2. When the set of types is fixed and known, and you want value semantics without heap allocation.
3. The size travels with the pointer; it can't disagree, and it accepts any contiguous container.
4. `std::chrono::steady_clock`.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 52: RAII and the Rule of Zero/Three/Five](../52.RAIIAndRuleOfFive/README.md)
