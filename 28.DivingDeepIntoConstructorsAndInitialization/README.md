# Lesson 28: Constructors and Initialization in Depth

> **In one sentence:** Objects can be born in many ways (with defaults, by copying another object,
> by moving, from a list), and controlling *exactly how* is what makes a class safe and efficient.

---

## 🎯 You will learn

- Default parameters for constructors; the member initializer list.
- `explicit` constructors (stopping sneaky conversions).
- Constructor delegation.
- **Copy constructors** (shallow vs deep copy!) and a first look at move constructors.
- Deleted constructors (`= delete`).
- `std::initializer_list` constructors.
- Aggregates, designated initializers, uniform initialization.

---

## 🧸 The Big Idea: ways to make a sandwich

- **Default constructor:** "the usual, please." (`Sandwich s;`)
- **Parameterized:** "ham and cheese." (`Sandwich s{"ham", "cheese"};`)
- **Copy constructor:** "the same as hers." (`Sandwich mine{hers};`). You get **your own** sandwich.
- **Move constructor:** "she's leaving, give me hers." Faster, no new sandwich made (Lesson 41).
- **Deleted constructor:** "we don't make that." Refused at compile time.

---

## 📚 Step by step

### 1. Defaults & initializer lists ([28.2](28.2DefaultParametersForConstructors/main.cpp), [28.3](28.3InitializerListsForConstructors/main.cpp))
```cpp
Cylinder(double r = 1.0, double h = 1.0) : radius{r}, height{h} {}
```
The initializer list **initializes**; the body would **assign** (a second step). Members are initialized
in **declaration order**, not the order you list them.

### 2. `explicit` ([28.5](28.5ExplicitConstructors/main.cpp))
```cpp
class Meters { public: Meters(double v); };
void run(Meters m);
run(5.0);            // compiles! 5.0 silently becomes a Meters. Surprise!

class Meters { public: explicit Meters(double v); };
run(5.0);            // ❌ error: good
run(Meters{5.0});    // ✅ intent is clear
```
> 🧠 Mark **single-argument constructors `explicit`** unless you *want* the implicit conversion.

### 3. Delegation ([28.6](28.6ConstructorDelegation/main.cpp))
```cpp
Date() : Date(1, 1, 2000) {}          // reuse the main constructor
Date(int d, int m, int y) : day{d}, month{m}, year{y} { validate(); }
```

### 4. Copy constructor ([28.7](28.7CopyConstructors/main.cpp), [28.8](28.8ObjectsStoredInArraysAreCopies/main.cpp)) ⭐
Signature: `Dog(const Dog& other)`. The compiler writes one for you that copies each member.
**Danger:** if a member is a *raw pointer* to heap memory, the default copy copies the **address**
(shallow copy). Now two objects think they own the same memory → double delete!

```
 SHALLOW copy (default)                DEEP copy (you write it)
 a.data ──┐                            a.data ───► [1 2 3]
          ├──► [1 2 3]                 b.data ───► [1 2 3]  (its own copy)
 b.data ──┘   both delete it → 💥
```
This is the "Rule of Three/Five" story, completed in Lessons 41 and 52.
Also: putting objects into arrays or passing by value **makes copies** (28.8).

### 5. Move constructor preview ([28.10](28.10MoveConstructors/main.cpp))
`Dog(Dog&& other)` *steals* the resources of a temporary instead of copying. Lesson 41 explains it fully.

### 6. `= delete` ([28.11](28.11DeletedConstructors/main.cpp))
`Dog(const Dog&) = delete;` forbids copying (e.g. for a class that owns a file or a network socket).

### 7. `std::initializer_list` ([28.12](28.12InitializerListConstructors/main.cpp))
`Point(std::initializer_list<double> values)` lets you write `Point p{1, 2, 3};`. It's how `std::vector v{1,2,3}` works.
⚠️ `std::vector<int> a(3, 5)` = three 5s; `std::vector<int> b{3, 5}` = the two numbers 3 and 5!

### 8. Aggregates & designated initializers ([28.13](28.13AggregateInitialization/main.cpp)–[28.15](28.15UniformInitializationForAggregates/main.cpp))
An **aggregate** is a simple struct/array with no user constructors and public members:
```cpp
struct Config { int width{800}; int height{600}; bool fullscreen{false}; };
Config c{.width = 1920, .fullscreen = true};   // C++20 designated initializers: readable!
```
Designators must appear in declaration order.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [28.2DefaultParametersForConstructors](28.2DefaultParametersForConstructors/main.cpp) | One constructor, many ways |
| [28.3InitializerListsForConstructors](28.3InitializerListsForConstructors/main.cpp) | `: a{x}, b{y}` |
| [28.5ExplicitConstructors](28.5ExplicitConstructors/main.cpp) | Blocking implicit conversions |
| [28.6ConstructorDelegation](28.6ConstructorDelegation/main.cpp) | Reusing constructors |
| [28.7CopyConstructors](28.7CopyConstructors/main.cpp) | `T(const T&)` |
| [28.8ObjectsStoredInArraysAreCopies](28.8ObjectsStoredInArraysAreCopies/main.cpp) | Hidden copies |
| [28.10MoveConstructors](28.10MoveConstructors/main.cpp) | `T(T&&)` preview |
| [28.11DeletedConstructors](28.11DeletedConstructors/main.cpp) | `= delete` |
| [28.12InitializerListConstructors](28.12InitializerListConstructors/main.cpp) | `{1, 2, 3}` constructors |
| [28.13AggregateInitialization](28.13AggregateInitialization/main.cpp) | Aggregates |
| [28.14DesignatedInitializers](28.14DesignatedInitializers/main.cpp) | `.name = value` |
| [28.15UniformInitializationForAggregates](28.15UniformInitializationForAggregates/main.cpp) | `{}` everywhere |

## ⚠️ Common mistakes

- A class with a raw owning pointer and the default copy constructor → double delete.
- Copy constructor taking `Dog other` by value → infinite recursion (it must be `const Dog&`).
- Forgetting `explicit`.
- Confusing `(3, 5)` and `{3, 5}` for containers.

## 🧠 Senior developer notes

- **Rule of Zero:** if your members are all "smart" types (`std::string`, `std::vector`, `std::unique_ptr`),
  you don't need to write copy/move/destructor at all, and the defaults are correct. Aim for this!
- If you write *any* of destructor / copy ctor / copy assignment / move ctor / move assignment,
  you probably need all five (**Rule of Five**, Lesson 52).

## ✅ Check yourself

1. Why must a copy constructor take its parameter by reference?
2. What bug does a shallow copy of a raw pointer cause?
3. What does `explicit` prevent?
4. `Config c{.height = 5, .width = 3};` Is that legal if `width` is declared first?

<details><summary>Answers</summary>

1. Passing by value would itself need a copy, which would call the copy constructor again, forever.
2. Two objects own the same memory → double delete / use-after-free.
3. Implicit conversions through that constructor.
4. No, because designators must follow declaration order.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 29: Friends](../29.Friends/README.md)
