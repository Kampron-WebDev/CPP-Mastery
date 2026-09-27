# Lesson 57: Design Patterns and SOLID ⭐ NEW

> **In one sentence:** Design patterns are **proven solutions to common design problems**, and
> SOLID is a set of five principles that keep code easy to change. Both are the shared vocabulary of senior developers.

---

## 🎯 You will learn

- The **SOLID** principles, explained simply.
- Key patterns in modern C++: **Strategy, Observer, Factory, Command, Builder, Adapter, Decorator, State, Singleton (and why to be careful), PIMPL, CRTP**.
- When a pattern helps and when it's over-engineering.

---

## 🧸 The Big Idea: LEGO instructions for code

When builders keep solving the same problem ("how do I make a strong corner?") they write down the best answer and give it a name.
Then one builder can say to another "use a **Strategy** here" and both instantly picture the solution.
Patterns are **names for good ideas**, not code to copy blindly.

---

## 🧱 SOLID in plain words

| Letter | Principle | Kid version | Smell when violated |
|--------|-----------|-------------|---------------------|
| **S** | Single Responsibility | "One job per class." A toaster toasts; it doesn't also do your taxes. | Class changes for many different reasons |
| **O** | Open/Closed | Add new features by **adding** code, not **editing** old working code. Plug a new device into the socket; don't rewire the house. | Big `switch` on type that grows with every feature |
| **L** | Liskov Substitution | A child class must work **anywhere** the parent works. A toy duck that needs batteries isn't a drop-in duck. | Overrides that throw "not supported" |
| **I** | Interface Segregation | Small, focused interfaces. Don't force a printer to implement `fax()`. | Empty/dummy method implementations |
| **D** | Dependency Inversion | Depend on **abstractions** (interfaces), not concrete classes. A lamp uses "a socket", not "that specific power plant". | Can't test a class without a real database/network |

---

## 📚 The patterns

### Behavioural
- **Strategy** ([Examples/01_Strategy](Examples/01_Strategy/main.cpp)): swap an algorithm at run time. (Sorting rule, pricing rule, AI difficulty.)
  In modern C++ often just a `std::function` or a template parameter.
- **Observer** (Lesson 42's EventSystem): "notify everyone who subscribed" (GUIs, events, pub/sub).
- **Command** ([Examples/03_CommandUndo](Examples/03_CommandUndo/main.cpp)): turn an action into an object → **undo/redo**, queues, macros.
- **State**: an object behaves differently depending on its state; each state is a class (or a `std::variant`, Lesson 51).

### Creational
- **Factory** ([Examples/02_Factory](Examples/02_Factory/main.cpp)): create objects without the caller knowing the concrete class: `makeShape("circle")`.
- **Builder**: construct complicated objects step by step: `Request::builder().url(u).timeout(5s).build()`.
- **Singleton**: exactly one instance (a "Meyers singleton": `static T& instance() { static T t; return t; }`).
  ⚠️ It's a global in disguise: hidden dependencies, hard to test. Prefer passing dependencies in.

### Structural
- **Adapter**: make an existing class fit an interface it wasn't built for (a travel plug adapter).
- **Decorator**: wrap an object to add behaviour (logging, caching, retries) without changing it.
- **PIMPL** ("pointer to implementation") ([Examples/04_Pimpl](Examples/04_Pimpl/main.cpp)): hide private details in the `.cpp`
  → faster builds, stable binary interface. Very common in C++ libraries.

### C++-specific
- **RAII** (Lesson 52): the #1 C++ idiom.
- **CRTP** (Curiously Recurring Template Pattern): `class Derived : public Base<Derived>`, static polymorphism with zero virtual-call cost.

---

## 🗂️ Examples

| Folder | Pattern |
|--------|---------|
| [01_Strategy](Examples/01_Strategy/main.cpp) | Strategy with interfaces AND with `std::function` |
| [02_Factory](Examples/02_Factory/main.cpp) | Factory + registry of creators (Open/Closed) |
| [03_CommandUndo](Examples/03_CommandUndo/main.cpp) | Command objects with undo/redo |
| [04_Pimpl](Examples/04_Pimpl/main.cpp) | PIMPL across `.h`/`.cpp` files |

## ⚠️ Common mistakes

- "Pattern fever": adding a Factory-of-Factories to a 50-line program. **YAGNI**: You Aren't Gonna Need It.
- Singletons everywhere, which makes the code impossible to unit test.
- Deep inheritance hierarchies where composition + small interfaces would do.

## 🧠 Senior developer notes

- **KISS** (Keep It Simple) beats clever. Introduce a pattern when the *second or third* use case appears, not before.
- Dependency Inversion is what makes code **testable**: pass an `ILogger&`/`IClock&` in, and give it a fake in tests.
- Many classic patterns shrink in modern C++: Strategy → lambda, Visitor → `std::visit`, Iterator → ranges.

## ✅ Check yourself

1. Which SOLID principle does a growing `switch (shape.type)` violate?
2. What problem does the Command pattern solve?
3. Why is Singleton often called an anti-pattern?
4. What does PIMPL improve?

<details><summary>Answers</summary>

1. Open/Closed (and often Single Responsibility).
2. Treating actions as objects: undo/redo, queuing, logging, macros.
3. It's hidden global state: hidden dependencies, hard to test, threading issues.
4. Compile times (private details out of the header) and binary/ABI stability; it also hides implementation.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 58: Performance and Memory](../58.PerformanceAndMemory/README.md)
