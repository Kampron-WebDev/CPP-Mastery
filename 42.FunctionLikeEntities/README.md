# Lesson 42: Function-like Entities

> **In one sentence:** In C++ lots of things can be "called like a function": function pointers,
> functors (objects with `operator()`), lambdas and `std::function`, and you can pass them around
> as values to customise behaviour (callbacks).

---

## 🎯 You will learn

- Function pointers and type aliases for them.
- Callbacks: passing behaviour into a function.
- Functors, including standard ones (`std::plus`, `std::greater`…).
- How lambdas work under the hood (they're functors!), capturing by value/reference/`this`.
- `std::function`: one type that can hold any callable.

---

## 🧸 The Big Idea: giving instructions to a helper

You hire a helper to go through your photo album. Instead of writing a separate helper for
"find blurry photos", "find photos of cats", "find photos from 2020", you write **one** helper
and hand them a **rule card** each time: *"here's how to decide."* That rule card is a **callable**.

```cpp
int countIf(const std::vector<int>& v, bool (*rule)(int))    // rule: a function pointer
{
    int n{0};
    for (int x : v) if (rule(x)) ++n;
    return n;
}
bool isEven(int x) { return x % 2 == 0; }
countIf(numbers, isEven);                       // pass the function itself
countIf(numbers, [](int x) { return x > 10; }); // or a lambda (no captures → converts to a pointer)
```

---

## 📚 Step by step

### 1. Function pointers ([42.2](42.2FunctionPointers/main.cpp)–[42.5](42.5FunctionPointerTypeAliasesWithTemplates/main.cpp))
```cpp
double (*op)(double, double) = &add;            // ugly syntax...
using BinaryOp = double (*)(double, double);    // ...so give it a name
BinaryOp op2 = multiply;
op2(3, 4);
```
Callbacks ([42.3](42.3CallbackFunctions/main.cpp)): pass them as parameters to customise behaviour.

### 2. Functors ([42.6](42.6Functors/main.cpp)–[42.9](42.9FunctorsAndLambdaFunctions/main.cpp))
A class with `operator()`. Unlike plain functions, functors can **hold state**:
```cpp
class IsGreaterThan {
public:
    explicit IsGreaterThan(int limit) : limit{limit} {}
    bool operator()(int x) const { return x > limit; }
private:
    int limit;
};
std::count_if(v.begin(), v.end(), IsGreaterThan{10});
```
Standard functors in `<functional>`: `std::plus<>`, `std::minus<>`, `std::greater<>`, `std::less<>`, …
`std::sort(v.begin(), v.end(), std::greater<>{});` sorts descending.

### 3. Lambdas under the hood ([42.10](42.10LambdaFunctionsAsCallbacks/main.cpp)–[42.14](42.14CapturingTheThisPointer/main.cpp))
The compiler turns every lambda into a **hidden functor class**:
```cpp
int limit = 10;
auto f = [limit](int x) { return x > limit; };
// becomes roughly:
class __Lambda { int limit; public: bool operator()(int x) const { return x > limit; } };
```
Captures by value = member copies. By reference = member references. `[this]` = captures the object pointer
(dangling risk if the lambda outlives the object; `[*this]` copies the whole object, C++17).

### 4. `std::function` ([42.15](42.15StdFunction/main.cpp))
```cpp
#include <functional>
std::function<int(int, int)> op = [](int a, int b) { return a + b; };
op = std::multiplies<>{};       // can hold a lambda, functor, or function pointer
std::vector<std::function<void()>> buttons;   // store different callables together
```
Flexible, but it has some overhead (possible heap allocation, indirect call). For parameters in
templates, `auto`/template callables are faster.

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [42.2FunctionPointers](42.2FunctionPointers/main.cpp) | Declaring & calling |
| [42.3CallbackFunctions](42.3CallbackFunctions/main.cpp) | Passing behaviour |
| [42.4FunctionPointerTypeAliases](42.4FunctionPointerTypeAliases/main.cpp) | `using Op = ...` |
| [42.5FunctionPointerTypeAliasesWithTemplates](42.5FunctionPointerTypeAliasesWithTemplates/main.cpp) | Template aliases |
| [42.6Functors](42.6Functors/main.cpp) | `operator()` |
| [42.7StandardFunctors](42.7StandardFunctors/main.cpp) | `std::plus`, `std::greater` |
| [42.8FunctorsWithParameters](42.8FunctorsWithParameters/main.cpp) | Stateful functors |
| [42.9FunctorsAndLambdaFunctions](42.9FunctorsAndLambdaFunctions/main.cpp) | Same thing, two syntaxes |
| [42.10LambdaFunctionsAsCallbacks](42.10LambdaFunctionsAsCallbacks/main.cpp) | Lambdas as callbacks |
| [42.11](42.11CapturingByValueUnderTheHood/main.cpp), [42.12](42.12CapturingByReferenceUnderTheHood/main.cpp) | How captures work |
| [42.13MixinCapturing](42.13MixinCapturing/main.cpp) | Mixed captures |
| [42.14CapturingTheThisPointer](42.14CapturingTheThisPointer/main.cpp) | `[this]` |
| [42.15StdFunction](42.15StdFunction/main.cpp) | `std::function` |

## ⚠️ Common mistakes

- A lambda capturing `[&]` or `[this]` stored and called after the objects died.
- Using `std::function` everywhere in hot code "because it's easy".
- A capturing lambda can't convert to a plain function pointer.

## 🧠 Senior developer notes

- Callbacks power event systems, GUIs, async code, and the **Strategy** and **Observer** patterns (Lesson 57).
- Prefer templates/`auto` parameters for callables in performance-critical functions; `std::function` at API boundaries where you need to store them.

## ✅ Check yourself

1. Write a type alias for a pointer to a function taking two ints and returning bool.
2. What's the advantage of a functor over a plain function?
3. What is a lambda, really?

<details><summary>Answers</summary>

1. `using Compare = bool (*)(int, int);`
2. It can carry state (member variables).
3. An object of a compiler-generated class with an `operator()`, and captures become members.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 43: STL Containers and Iterators](../43.StlContainersAndIterators/README.md)
