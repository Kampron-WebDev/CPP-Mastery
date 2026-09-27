# Lesson 31: Namespaces

> **In one sentence:** A namespace is a **surname for your code**: two functions can both be
> called `print` as long as they live in different namespaces (`Geometry::print` vs `Report::print`).

---

## 🎯 You will learn

- Creating namespaces and spreading them across files.
- The global namespace and built-in `std`.
- `using` declarations vs `using namespace` directives.
- Anonymous namespaces (file-private code).
- Nested namespaces and namespace aliases.

---

## 🧸 The Big Idea: surnames

In a school there are two kids called **Sam**. The teacher says **"Sam Mensah"** and **"Sam Owusu"**
and everyone knows who is meant. Namespaces are surnames for code:

```cpp
namespace Mensah { void greet() { std::cout << "Hi from Sam Mensah\n"; } }
namespace Owusu  { void greet() { std::cout << "Hi from Sam Owusu\n"; } }

Mensah::greet();
Owusu::greet();
```
`::` is the **scope resolution operator**: "look inside this namespace".

---

## 📚 Step by step

### 1. Creating namespaces ([31.2](31.2CreatingNamespaces/main.cpp)) and across files ([31.3](31.3NamespacesAcrossMultipleFiles/main.cpp))
Namespaces are **open**: you can add to the same namespace in many files (that's how `std` is spread across hundreds of headers).

### 2. The global namespace ([31.4](31.4DefaultGlobalNamespace/main.cpp))
Anything not in a namespace is in the global one. `::name` explicitly means "the global `name`".

### 3. Built-in namespaces ([31.5](31.5BuiltInNamespaces/main.cpp))
`std` (the standard library), `std::chrono`, `std::ranges`, `std::views`, `std::numbers`…

### 4. `using` ([31.6UsingDeclarations](31.6UsingDeclarations/main.cpp))
```cpp
using std::cout;          // using-DECLARATION: bring in ONE name ✅
using namespace std;      // using-DIRECTIVE: bring in EVERYTHING ⚠️
```
**Never** put `using namespace` in a header file: every file that includes it gets polluted.
Inside a function body in a `.cpp` it's acceptable.

### 5. Anonymous namespaces ([31.7](31.7AnonymousNamespaces/main.cpp))
```cpp
namespace {
    int helperCounter{0};         // only visible in THIS .cpp file
    void helper() { }
}
```
The modern replacement for `static` global functions: "private to this file" (internal linkage, Lesson 32).

### 6. Nested namespaces & aliases ([31.8](31.8NestedNamespaces/main.cpp), [31.9](31.9NamespaceAliases/main.cpp))
```cpp
namespace Company::Graphics::Shapes { struct Circle {}; }   // C++17 nested syntax
namespace Shapes = Company::Graphics::Shapes;                // alias: a short nickname
Shapes::Circle c;
```

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [31.2CreatingNamespaces](31.2CreatingNamespaces/main.cpp) | Same name, different namespaces |
| [31.3NamespacesAcrossMultipleFiles](31.3NamespacesAcrossMultipleFiles/main.cpp) | One namespace, many files |
| [31.4DefaultGlobalNamespace](31.4DefaultGlobalNamespace/main.cpp) | `::name` |
| [31.5BuiltInNamespaces](31.5BuiltInNamespaces/main.cpp) | `std` and friends |
| [31.6UsingDeclarations](31.6UsingDeclarations/main.cpp) | `using` |
| [31.7AnonymousNamespaces](31.7AnonymousNamespaces/main.cpp) | File-private code |
| [31.8NestedNamespaces](31.8NestedNamespaces/main.cpp) | `A::B::C` |
| [31.9NamespaceAliases](31.9NamespaceAliases/main.cpp) | `namespace X = ...` |

## ⚠️ Common mistakes

- `using namespace std;` in headers.
- Naming your own function `count` or `distance` and clashing with `std::` names pulled in by a using-directive.

## 🧠 Senior developer notes

- Every real project puts its code in a project namespace (`namespace myapp { ... }`), usually one per library/module.
- Anonymous namespaces for helpers in `.cpp` files keep your public API small and speed up linking.
- **ADL** (argument-dependent lookup): `std::cout << x` finds `operator<<` in `x`'s namespace automatically.
  That's why you don't write `std::operator<<(std::cout, x)`.

## ✅ Check yourself

1. What does `::` do?
2. Why is `using namespace std;` in a header harmful?
3. What does an anonymous namespace do?

<details><summary>Answers</summary>

1. Scope resolution: picks a name from a specific namespace or class.
2. It silently dumps every std name into every file that includes the header, causing clashes.
3. Makes its contents visible only in the current `.cpp` file (internal linkage).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 32: Programs with Multiple Files](../32.ProgramsWithMultipleFiles/README.md)
