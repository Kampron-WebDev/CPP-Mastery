# Lesson 37: Polymorphism

> **In one sentence:** Polymorphism ("many shapes") lets you treat different objects through
> **one common interface**. You call `shape->draw()` and each shape draws *itself* correctly,
> decided **at run time**.

This is the heart of object-oriented design and of most frameworks, game engines and GUIs.

---

## 🎯 You will learn

- Static vs dynamic binding; `virtual` functions.
- Object **slicing** and why polymorphism needs pointers/references.
- Storing polymorphic objects in collections.
- `override` and `final`.
- Overloading vs overriding vs hiding.
- Virtual functions with default arguments, static members, access specifiers.
- **Virtual destructors** (critical!).
- `dynamic_cast` and `typeid`.
- Pure virtual functions, abstract classes, interfaces.

---

## 🧸 The Big Idea: the universal remote

You press **PLAY** on one remote. If it's pointed at the TV, a show plays. At the music box, a song plays.
At the game console, a game starts. **Same button, different behaviour**, depending on the actual device.

```cpp
class Shape {
public:
    virtual void draw() const = 0;        // "every shape can draw; ask the real shape how"
    virtual ~Shape() = default;           // ALWAYS virtual destructor in a polymorphic base
};
class Circle : public Shape { public: void draw() const override { std::cout << "○\n"; } };
class Square : public Shape { public: void draw() const override { std::cout << "□\n"; } };

std::vector<std::unique_ptr<Shape>> shapes;
shapes.push_back(std::make_unique<Circle>());
shapes.push_back(std::make_unique<Square>());
for (const auto& s : shapes) s->draw();   // ○ □ : each draws itself
```

---

## 📚 Step by step

### 1. Static binding (the problem) ([37.2](37.2StaticBindingWithInheritance/main.cpp))
Without `virtual`, `Shape* p = &circle; p->draw();` calls **Shape::draw**. The compiler decides by the *pointer type*.

### 2. Dynamic binding with `virtual` ([37.3](37.3PolymorphismWithVirtualFunctions/main.cpp))
With `virtual`, the call is decided **at run time** by the *actual object type*.
How? Each polymorphic object carries a hidden pointer (**vptr**) to a table of function pointers (**vtable**).

```
 circle object            Circle's vtable
 ┌───────────┐           ┌─────────────────────┐
 │ vptr ─────┼─────────► │ draw → Circle::draw │
 │ radius    │           │ ~dtor → Circle::~   │
 └───────────┘           └─────────────────────┘
```

### 3. Size and slicing ([37.4](37.4SizeOfPolymorphicObjectsAndSlicing/main.cpp))
Polymorphic objects are 8 bytes bigger (the vptr).
**Slicing:** `Shape s = circle;` copies only the Shape part, and the Circle-ness is **sliced off**.
Polymorphism only works through **pointers or references**.

### 4. Collections ([37.5](37.5PolymorphicObjectsStoredInCollections/main.cpp))
`std::vector<Shape>` slices. Use `std::vector<std::unique_ptr<Shape>>`.

### 5. `override` and `final` ([37.6](37.6Override/main.cpp), [37.10](37.10Final/main.cpp), [37.11](37.11FinalAndOverrideAreNotKeywords/main.cpp))
- `override`: "I intend to override a virtual function". The compiler errors if you got the signature wrong (e.g. forgot `const`). **Always use it.**
- `final`: "no one may override this further / inherit from this class".

### 6. Overloading vs overriding vs hiding ([37.7](37.7OverloadingOverridingAndHiding/main.cpp))
| | Same name? | Same signature? | Virtual? | Where |
|---|---|---|---|---|
| Overloading | ✅ | ❌ | – | same scope |
| Overriding | ✅ | ✅ | ✅ | derived redefines base virtual |
| Hiding | ✅ | either | ❌ | derived name hides base name(s) |

### 7. More rules ([37.8](37.8PolymorphismAtDifferentLevels/main.cpp), [37.9](37.9InheritanceAndPolymorphismWithStaticMembers/main.cpp), [37.12](37.12PolymorphicFunctionsAndAccessSpecifiers/main.cpp), [37.13](37.13NonPolymorphicFunctionsAndAccessSpecifiers/main.cpp), [37.14](37.14VirtualFunctionsWithDefaultArguments/main.cpp))
- Access is checked on the **static** (pointer) type; the function called follows the dynamic type.
- ⚠️ Default arguments are taken from the **static** type. Don't give overrides different defaults.
- Static members are not polymorphic.

### 8. Virtual destructors ([37.15](37.15VirtualDestructors/main.cpp)) ⭐
```cpp
Shape* s = new Circle;
delete s;   // without virtual ~Shape(): only ~Shape runs → Circle's part LEAKS (undefined behaviour)
```
**Rule:** a class with any virtual function needs a `virtual` destructor.
Also: don't call virtual functions from constructors/destructors ([37.17](37.17PolymorphicFunctionsAndDestructors/main.cpp)); during construction the object isn't the derived type yet.

### 9. `dynamic_cast` and `typeid` ([37.16](37.16DynamicCasts/main.cpp), [37.18](37.18TypeIdOperator/main.cpp))
```cpp
if (auto* c = dynamic_cast<Circle*>(shapePtr)) { c->setRadius(2); }   // nullptr if it isn't a Circle
typeid(*shapePtr).name();
```
Needing lots of `dynamic_cast` usually means the design is missing a virtual function.

### 10. Abstract classes and interfaces ([37.19](37.19PureVirtualFunctionsAndAbstractClasses/main.cpp), [37.20](37.20AbstractClassesAsInterfaces/main.cpp))
`virtual void draw() const = 0;` is a **pure virtual** function. A class with one is **abstract**: you can't create objects of it.
An **interface** = abstract class with only pure virtual functions (+ virtual destructor). It's a **contract**: "anything that is `Drawable` can `draw()`".

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [37.2](37.2StaticBindingWithInheritance/main.cpp) / [37.3](37.3PolymorphismWithVirtualFunctions/main.cpp) | Static vs dynamic binding |
| [37.4](37.4SizeOfPolymorphicObjectsAndSlicing/main.cpp) | vptr size, slicing |
| [37.5](37.5PolymorphicObjectsStoredInCollections/main.cpp) | Collections of base pointers |
| [37.6](37.6Override/main.cpp) | `override` |
| [37.7](37.7OverloadingOverridingAndHiding/main.cpp) | Overload / override / hide |
| [37.8](37.8PolymorphismAtDifferentLevels/main.cpp) | Multi-level hierarchies |
| [37.9](37.9InheritanceAndPolymorphismWithStaticMembers/main.cpp) | Static members |
| [37.10](37.10Final/main.cpp) / [37.11](37.11FinalAndOverrideAreNotKeywords/main.cpp) | `final` |
| [37.12](37.12PolymorphicFunctionsAndAccessSpecifiers/main.cpp) / [37.13](37.13NonPolymorphicFunctionsAndAccessSpecifiers/main.cpp) | Access specifiers |
| [37.14](37.14VirtualFunctionsWithDefaultArguments/main.cpp) | Default-argument trap |
| [37.15](37.15VirtualDestructors/main.cpp) | Virtual destructors |
| [37.16](37.16DynamicCasts/main.cpp) | `dynamic_cast` |
| [37.17](37.17PolymorphicFunctionsAndDestructors/main.cpp) | Virtual calls in ctors/dtors |
| [37.18](37.18TypeIdOperator/main.cpp) | `typeid` |
| [37.19](37.19PureVirtualFunctionsAndAbstractClasses/main.cpp) / [37.20](37.20AbstractClassesAsInterfaces/main.cpp) | Abstract classes, interfaces |

## ⚠️ Common mistakes

- Missing `virtual` destructor in a base class.
- Forgetting `override` → a typo'd signature silently creates a *new* function instead of overriding.
- Storing derived objects **by value** in a base container (slicing).
- Calling virtual functions in constructors.

## 🧠 Senior developer notes

- Design to **interfaces**: code depends on `ILogger`, not `FileLogger`. Then you can swap in a `TestLogger`
  in tests. This is the **Dependency Inversion Principle** (Lesson 57).
- Virtual calls cost a little (an indirect call; the compiler usually can't inline them). Irrelevant for most code,
  but it matters in hot loops, where templates/`std::variant` (static polymorphism) are alternatives.
- **Open/Closed Principle:** add a new `Triangle` class without changing any existing drawing code.

## ✅ Check yourself

1. Why does `Shape s = Circle{};` not behave polymorphically?
2. What happens when you `delete` a derived object through a base pointer without a virtual destructor?
3. What does `override` protect you from?
4. Can you create an object of an abstract class?

<details><summary>Answers</summary>

1. Slicing: only the `Shape` part is copied into `s`.
2. Undefined behaviour: typically the derived destructor doesn't run (leaks).
3. Accidentally declaring a new function because the signature doesn't match the base's virtual.
4. No, only of concrete derived classes that implement all pure virtuals.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 38: Exceptions](../38.Exceptions/README.md)
