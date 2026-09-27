# Lesson 21: Lambda Functions

> **In one sentence:** A lambda is a **small function written right where you need it**,
> without a name, and it can "capture" variables from around it.

---

## 🎯 You will learn

- Lambda syntax: `[capture](params) -> ret { body }`.
- Calling lambdas and storing them in `auto` variables.
- Capture lists: by value `[x]`, by reference `[&x]`, all `[=]`, `[&]`.
- `mutable` lambdas.

---

## 🧸 The Big Idea: a sticky note with instructions

Sometimes you need a tiny instruction for just one moment: *"sort these by height"*.
Writing a whole named function somewhere else is like writing a formal letter to say "pass the salt".
A lambda is a **sticky note** you write on the spot.

```cpp
auto square = [](int x) { return x * x; };
//            │   │        └ body
//            │   └ parameters
//            └ capture list (what to bring in from outside)
std::cout << square(5);   // 25
```

---

## 📚 Step by step

### 1. Declaring and using ([21.2](21.2DeclaringAndUsingLambdas/main.cpp))
```cpp
[]() { std::cout << "Hi\n"; }();          // define AND call immediately
auto add = [](double a, double b) -> double { return a + b; };   // explicit return type (optional)
```

### 2. Capture lists ([21.3CaptureLists](21.3CaptureLists/main.cpp))
A lambda can't see local variables unless you **capture** them:
```cpp
int bonus{10};
auto addBonus = [bonus](int score) { return score + bonus; };   // copy of bonus, taken NOW
auto addTo    = [&bonus](int s) { bonus += s; };                // reference: changes the real bonus
```
**By value** = the lambda takes a **photo** of the variable when it's created. Later changes to the original don't affect the photo.
**By reference** = the lambda holds a **live link** to the original.

### 3. Capture all ([21.4CaptureAllLists](21.4CaptureAllLists/main.cpp))
- `[=]` captures everything used, by value.
- `[&]` captures everything used, by reference.
- Mixes: `[=, &total]`, `[&, count]`.

Value captures are `const` inside the lambda. Add `mutable` to modify the lambda's own copy:
```cpp
auto counter = [n = 0]() mutable { return ++n; };   // init-capture + mutable
counter(); counter();   // 1, 2
```

### Where lambdas shine: algorithms (Lessons 42, 45)
```cpp
std::sort(people.begin(), people.end(),
          [](const Person& a, const Person& b) { return a.age < b.age; });
```

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [21.2DeclaringAndUsingLambdas](21.2DeclaringAndUsingLambdas/main.cpp) | Syntax, calling, return types |
| [21.3CaptureLists](21.3CaptureLists/main.cpp) | `[x]` vs `[&x]` |
| [21.4CaptureAllLists](21.4CaptureAllLists/main.cpp) | `[=]`, `[&]` |

## ⚠️ Common mistakes

- Capturing by reference and using the lambda **after** the variable died (dangling, just like pointers).
- Expecting a by-value capture to see later changes.
- `[=]` in a class member function also captures `this`, a surprise (Lesson 42).

## 🧠 Senior developer notes

- Prefer **explicit** captures (`[&total, limit]`) over `[&]`/`[=]` in long-lived lambdas. They document dependencies.
- Each lambda is actually an object of a unique, compiler-generated class with `operator()` (Lesson 42).
- Generic lambdas: `[](auto x) { ... }` work with any type (a template in disguise).

## ✅ Check yourself

1. `int a{1}; auto f = [a]() { return a; }; a = 5;` What does `f()` return?
2. Same but `[&a]`?
3. Why is `mutable` needed to change a by-value capture?

<details><summary>Answers</summary>

1. 1 (copy taken at creation).
2. 5 (live reference).
3. The lambda's call operator is `const` by default; `mutable` removes that.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 22: Functions, the Misfits](../22.FunctionsTheMisfits/README.md)
