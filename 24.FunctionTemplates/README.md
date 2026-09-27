# Lesson 24: Function Templates

> **In one sentence:** A template is a **cookie cutter for functions**: you write the shape once
> with a placeholder type `T`, and the compiler stamps out a real function for each type you use.

---

## 🎯 You will learn

- Writing and using function templates.
- Type deduction and explicit template arguments.
- Specialization and overloading templates.
- Multiple type parameters, `auto` return types, `decltype`, trailing return types, `decltype(auto)`.
- Default template arguments and **non-type** template parameters.
- Abbreviated templates (`auto` parameters), template lambdas.
- Type traits and `if constexpr`.

---

## 🧸 The Big Idea: one cookie cutter, many doughs

Without templates you'd write:
```cpp
int    maximum(int a, int b)       { return a > b ? a : b; }
double maximum(double a, double b) { return a > b ? a : b; }
std::string maximum(...)           // ... again and again
```
With a template:
```cpp
template <typename T>          // "T is a placeholder for some type"
T maximum(T a, T b) { return a > b ? a : b; }

maximum(3, 7);          // compiler stamps out maximum<int>
maximum(2.5, 1.5);      // stamps out maximum<double>
maximum<double>(3, 2.5);// you choose T explicitly
```
The template **itself is not code**. It's a recipe. Real functions are generated only for the types you actually use (**instantiation**).

---

## 📚 Step by step

### 1. Basics and deduction ([24.2](24.2TryingOutFunctionTemplates/main.cpp), [24.3](24.3TemplateTypeDeductionAndExplicitArguments/main.cpp))
`maximum(3, 2.5)` **fails**: T can't be both `int` and `double`. Fix with `maximum<double>(3, 2.5)`.

### 2. By reference ([24.4](24.4TemplateTypeParametersByReference/main.cpp))
`template <typename T> const T& maximum(const T& a, const T& b)` avoids copies for big types.

### 3. Specialization ([24.5](24.5TemplateSpecialization/main.cpp)) & overloading ([24.6](24.6FunctionTemplatesWithOverloading/main.cpp))
For `const char*`, `>` compares **addresses**, not text. Provide a special version:
```cpp
template <>
const char* maximum<const char*>(const char* a, const char* b) { return std::strcmp(a, b) > 0 ? a : b; }
```
(Often a plain overload is simpler and preferred over specialization.)

### 4. Multiple parameters & return types ([24.7](24.7FunctionTemplatesWithMultipleParameters/main.cpp)–[24.10](24.10DecltypeAuto/main.cpp))
```cpp
template <typename T, typename U>
auto add(T a, U b) { return a + b; }                    // auto deduces the result type

template <typename T, typename U>
auto add2(T a, U b) -> decltype(a + b) { return a + b; } // trailing return type (older style)
```
`decltype(expr)` = "the type of this expression". `decltype(auto)` keeps references exactly.

### 5. Defaults & non-type parameters ([24.11](24.11DefaultArguments/main.cpp), [24.12](24.12NonTypeTemplateParameters/main.cpp))
```cpp
template <int Threshold>
bool isBig(int x) { return x > Threshold; }   // value baked in at compile time
isBig<100>(150);
```

### 6. `auto` parameters and template lambdas ([24.13](24.13AutoFunctionTemplates/main.cpp), [24.14](24.14NamedTemplateParametersForLambdas/main.cpp))
```cpp
auto maximum(auto a, auto b) { return a > b ? a : b; }         // C++20 abbreviated template
auto sameTypeMax = []<typename T>(T a, T b) { return a > b ? a : b; };  // C++20 template lambda
```

### 7. Type traits & `if constexpr` ([24.15](24.15TypeTraits/main.cpp), [24.16](24.16ConstexprIf/main.cpp))
```cpp
#include <type_traits>
template <typename T>
void describe(T value)
{
    if constexpr (std::is_integral_v<T>)             std::cout << "whole number\n";
    else if constexpr (std::is_floating_point_v<T>)  std::cout << "decimal\n";
    else                                             std::cout << "something else\n";
}
```
`static_assert(std::is_arithmetic_v<T>, "numbers only")` gives a clear error for bad types.
Lesson 25's **concepts** do this even better.

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [24.2TryingOutFunctionTemplates](24.2TryingOutFunctionTemplates/main.cpp) | First template |
| [24.3TemplateTypeDeductionAndExplicitArguments](24.3TemplateTypeDeductionAndExplicitArguments/main.cpp) | Deduction, `<T>` |
| [24.4TemplateTypeParametersByReference](24.4TemplateTypeParametersByReference/main.cpp) | `const T&` |
| [24.5TemplateSpecialization](24.5TemplateSpecialization/main.cpp) | `template <>` |
| [24.6FunctionTemplatesWithOverloading](24.6FunctionTemplatesWithOverloading/main.cpp) | Overload vs template |
| [24.7FunctionTemplatesWithMultipleParameters](24.7FunctionTemplatesWithMultipleParameters/main.cpp) | `T, U` |
| [24.8TemplateReturnTypeDeductionWithAuto](24.8TemplateReturnTypeDeductionWithAuto/main.cpp) | `auto` return |
| [24.9DecltypeAndTrailingReturnTypes](24.9DecltypeAndTrailingReturnTypes/main.cpp) | `-> decltype(...)` |
| [24.10DecltypeAuto](24.10DecltypeAuto/main.cpp) | `decltype(auto)` |
| [24.11DefaultArguments](24.11DefaultArguments/main.cpp) | Default template args |
| [24.12NonTypeTemplateParameters](24.12NonTypeTemplateParameters/main.cpp) | Values as template params |
| [24.13AutoFunctionTemplates](24.13AutoFunctionTemplates/main.cpp) | `auto` params |
| [24.14NamedTemplateParametersForLambdas](24.14NamedTemplateParametersForLambdas/main.cpp) | `[]<typename T>` |
| [24.15TypeTraits](24.15TypeTraits/main.cpp) | `<type_traits>` |
| [24.16ConstexprIf](24.16ConstexprIf/main.cpp) | Compile-time branching |

## ⚠️ Common mistakes

- Putting template **definitions** in a `.cpp` file and only the declaration in the header → linker errors.
  Templates must be fully visible where they're used: **define them in headers**.
- Huge error messages: read the **first** line and look for "required from here" to find *your* code.
- Assuming `T` supports an operation (`>`, `+`) that it doesn't. Concepts (Lesson 25) catch this early.

## 🧠 Senior developer notes

- The whole STL (`std::vector<T>`, `std::sort`) is built from templates. This is how C++ gets
  **generic code with zero run-time cost**.
- Each instantiation is separate machine code; too many can bloat binaries and compile times.
- Prefer overloads over specializations of function templates (specializations don't participate in overload resolution the way you'd expect).

## ✅ Check yourself

1. Why does `maximum(1, 2.0)` fail for `template <typename T> T maximum(T, T)`?
2. Where must template definitions live?
3. What does `if constexpr` do that `if` doesn't?

<details><summary>Answers</summary>

1. T is deduced as `int` from one argument and `double` from the other: a conflict.
2. In headers (or anywhere visible at the point of use).
3. It discards the non-taken branch at compile time, so that branch doesn't even need to compile for this T.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 25: Concepts](../25.Concepts/README.md)
