# Lesson 26: Classes

> **In one sentence:** A class is a **blueprint** that bundles **data** (what something *is*)
> with **functions** (what it can *do*), and each object built from it is one real "thing".

This is where C++ turns from "a list of instructions" into "a world of objects". It's the
foundation of almost all professional C++ code.

---

## 🎯 You will learn

- Declaring a class: member variables and member functions.
- `private` vs `public` (encapsulation).
- Constructors (including defaulted ones) and destructors.
- Setters and getters.
- Splitting a class across `.h` and `.cpp` files.
- Managing objects through pointers; the `this` pointer.
- `struct` vs `class`; the size of objects.

---

## 🧸 The Big Idea: blueprint and houses

```
     BLUEPRINT (class Dog)                 OBJECTS (actual dogs)
   ┌─────────────────────────┐        ┌──────────────┐  ┌──────────────┐
   │ data:                   │        │ name: "Rex"  │  │ name: "Bella"│
   │   name, age             │ ─────► │ age: 3       │  │ age: 5       │
   │ can do:                 │        └──────────────┘  └──────────────┘
   │   bark(), birthday()    │          Dog rex{...};     Dog bella{...};
   └─────────────────────────┘
```

One blueprint, many houses. Each object has **its own copy** of the data, but they share the functions.

**Encapsulation** = a TV remote. You press **public** buttons (volume up); you can't reach the
**private** circuit board inside. That protects the TV from being broken by curious fingers.

---

## 📚 Step by step

### 1. Your first class ([26.2](26.2YourFirstClass/main.cpp))
```cpp
class Cylinder {
public:                                  // anyone can use these
    double volume() const { return 3.14159 * radius * radius * height; }
private:                                 // only Cylinder's own functions can touch these
    double radius{1.0};
    double height{1.0};
};                                       // ← don't forget this semicolon!

Cylinder c;
c.volume();      // ✅
// c.radius = 5; // ❌ private
```

### 2. Constructors ([26.3](26.3Constructors/main.cpp), [26.4](26.4DefaultedConstructors/main.cpp))
A constructor is a special function that runs **automatically when an object is born**. Same name as the class, no return type.
```cpp
class Cylinder {
public:
    Cylinder() = default;                               // default constructor
    Cylinder(double r, double h) : radius{r}, height{h} {}   // ← member initializer list
private:
    double radius{1.0};
    double height{1.0};
};
Cylinder a;             // uses default
Cylinder b{2.0, 5.0};   // uses (r, h)
```
Its job is to put the object into a **valid state** from the very first moment.

### 3. Setters and getters ([26.5](26.5SettersAndGetters/main.cpp))
```cpp
double getRadius() const { return radius; }
void setRadius(double r) { if (r > 0) radius = r; }   // setters can VALIDATE
```
> 🧠 Don't write getters/setters for every field by reflex. Expose **behaviour** (`deposit(amount)`)
> rather than raw data (`setBalance(x)`). That's what encapsulation is for.

### 4. Multiple files ([26.6](26.6ClassAcrossMultipleFiles/main.cpp))
- `cylinder.h`: the class declaration (what it has).
- `cylinder.cpp`: member function bodies: `double Cylinder::volume() const { ... }`
  The `Cylinder::` says "this `volume` belongs to Cylinder".

### 5. Objects through pointers ([26.8](26.8ManagingClassObjectsThroughPointers/main.cpp))
```cpp
Cylinder* p = new Cylinder{2, 3};
p->volume();         // -> is short for (*p).volume()
delete p;
```

### 6. Destructors ([26.9](26.9Destructors/main.cpp), [26.10](26.10OrderOfConstructorDestructorCalls/main.cpp))
`~Dog()` runs **automatically when an object dies** (goes out of scope, or is `delete`d). Use it to clean up
(free memory, close files). Objects are destroyed in **reverse order** of construction: last in, first out, like plates.

### 7. The `this` pointer ([26.11](26.11ThisPointer/main.cpp))
Inside a member function, `this` points at **the object the function was called on**. It helps with name clashes
(`this->name = name;`) and lets you **chain** calls by returning `*this`:
```cpp
dog.setName("Rex").setAge(3);
```

### 8. `struct` ([26.12](26.12Struct/main.cpp)) and size ([26.13](26.13.SizeOfClassObjects/main.cpp))
`struct` = `class` whose members are **public by default**. Convention: `struct` for simple
data bundles (`Point{x, y}`), `class` when there are rules to protect (invariants).
`sizeof(object)` counts only data members (plus **padding** for alignment); functions take no space in the object.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [26.2YourFirstClass](26.2YourFirstClass/main.cpp) | Members, access specifiers |
| [26.3Constructors](26.3Constructors/main.cpp) | Default and parameterized constructors |
| [26.4DefaultedConstructors](26.4DefaultedConstructors/main.cpp) | `= default` |
| [26.5SettersAndGetters](26.5SettersAndGetters/main.cpp) | Controlled access |
| [26.6ClassAcrossMultipleFiles](26.6ClassAcrossMultipleFiles/main.cpp) | `.h` + `.cpp` |
| [26.8ManagingClassObjectsThroughPointers](26.8ManagingClassObjectsThroughPointers/main.cpp) | `->`, heap objects |
| [26.9Destructors](26.9Destructors/main.cpp) | `~ClassName()` |
| [26.10OrderOfConstructorDestructorCalls](26.10OrderOfConstructorDestructorCalls/main.cpp) | LIFO destruction |
| [26.11ThisPointer](26.11ThisPointer/main.cpp) | `this`, chaining |
| [26.12Struct](26.12Struct/main.cpp) | `struct` vs `class` |
| [26.13.SizeOfClassObjects](26.13.SizeOfClassObjects/main.cpp) | Object size, padding |

## ⚠️ Common mistakes

- Missing `;` after the closing `}` of a class.
- Public data everywhere, which means no encapsulation at all.
- Assigning members in the constructor body instead of the **initializer list** (slower, and impossible for `const`/reference members).
- Forgetting `const` on getters (then they can't be called on const objects: Lesson 27).

## 🧠 Senior developer notes

- A class should protect an **invariant**, a rule that must always be true (e.g. "balance ≥ 0", "denominator ≠ 0").
  Constructors establish it; every public function preserves it.
- Initialize members in the **same order they're declared** (the compiler uses declaration order anyway; `-Wall` warns).
- Single Responsibility: one class, one job. A `User` class shouldn't also send emails.

## ✅ Check yourself

1. Difference between a class and an object?
2. What's the only difference between `struct` and `class`?
3. When does a destructor run?
4. Why prefer the member initializer list?

<details><summary>Answers</summary>

1. The class is the blueprint; an object is one instance built from it.
2. Default access: `struct` is public, `class` is private.
3. When the object's lifetime ends (end of scope, `delete`, or end of the program for globals).
4. Members are initialized directly (not default-constructed then assigned); required for const/reference members.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 27: Zooming in on Class Objects](../27.ZoomingInOnClassObjects/README.md)
