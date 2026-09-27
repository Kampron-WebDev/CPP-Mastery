# Lesson 30: Const and Static Members

> **In one sentence:** `static` members belong to the **class itself** (shared by all objects),
> not to any single object, and this lesson also covers nested classes and in-class initialization.

---

## 🎯 You will learn

- Static member variables (and `inline static` since C++17).
- Static constants (`static constexpr`) and the pre-C++17 way.
- Member variables of the class's own type (pointers only!) and of other types.
- Static member functions.
- Nested classes.
- In-class member initialization.

---

## 🧸 The Big Idea: the classroom

Each **student** (object) has their own `name` and `grade` (normal members).
But the **class clock on the wall** is shared: there's only one, and every student sees the same time.
That clock is a **static member**.

```cpp
class Student {
public:
    Student() { ++count; }              // every new student adds to the shared counter
    ~Student() { --count; }
    static int getCount() { return count; }   // static function: no object needed
private:
    std::string name;                   // one per object
    inline static int count{0};         // ONE for the whole class
};

Student a, b, c;
Student::getCount();   // 3: called on the CLASS, not an object
```

---

## 📚 Step by step

### 1. Static member variables ([30.3](30.3StaticMemberVariables/main.cpp), [30.4](30.4InlineStaticMemberVariables/main.cpp))
Before C++17 you declared inside the class and **defined in exactly one .cpp**: `int Student::count{0};`.
Since C++17, `inline static int count{0};` does both in the class.

### 2. Static constants ([30.5](30.5StaticConstants/main.cpp), [30.6](30.6StaticConstantsPreCpp17/main.cpp))
`static constexpr double pi{3.14159};`: one per class, known at compile time.

### 3. Members of type self / other types ([30.7](30.7MemberVariablesOfTypeSelf/main.cpp), [30.8](30.8MemberVariablesOfOtherTypes/main.cpp))
A class **can't** contain an object of its own type (it would be infinitely big!), but it can hold a **pointer** to one:
```cpp
struct Node { int value; Node* next; };   // linked lists, trees: Lesson 54
```
It can also hold a `static` member of its own type.

### 4. Static member functions ([30.9](30.9StaticMemberFunctions/main.cpp))
No `this` pointer, so they can only touch **static** members directly. Perfect for factory functions and counters.

### 5. Nested classes ([30.10](30.10NestedClasses/main.cpp))
A class defined inside another: `Outer::Inner`. Good for helper types that only make sense in context
(`LinkedList::Node`, `Car::Engine`). The inner class can access the outer class's privates (since C++11).

### 6. In-class initialization ([30.11](30.11InClassMemberVariableInitialization/main.cpp))
`int width{800};` right in the class: every constructor that doesn't set it gets 800. Use this everywhere.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [30.3StaticMemberVariables](30.3StaticMemberVariables/main.cpp) | Shared counter |
| [30.4InlineStaticMemberVariables](30.4InlineStaticMemberVariables/main.cpp) | C++17 `inline static` |
| [30.5StaticConstants](30.5StaticConstants/main.cpp) | `static constexpr` |
| [30.6StaticConstantsPreCpp17](30.6StaticConstantsPreCpp17/main.cpp) | The old way |
| [30.7MemberVariablesOfTypeSelf](30.7MemberVariablesOfTypeSelf/main.cpp) | Self-pointers |
| [30.8MemberVariablesOfOtherTypes](30.8MemberVariablesOfOtherTypes/main.cpp) | Composition |
| [30.9StaticMemberFunctions](30.9StaticMemberFunctions/main.cpp) | Class-level functions |
| [30.10NestedClasses](30.10NestedClasses/main.cpp) | `Outer::Inner` |
| [30.11InClassMemberVariableInitialization](30.11InClassMemberVariableInitialization/main.cpp) | Default member values |

## ⚠️ Common mistakes

- Old-style static member declared but never defined → linker error "undefined reference". Use `inline static`.
- Trying to use `this` or non-static members in a static function.
- Using static members as disguised globals (shared mutable state, the same problems as globals).

## 🧠 Senior developer notes

- **Composition** ("has-a": a `Car` *has an* `Engine` member) is usually better than inheritance ("is-a", Lesson 36).
- Static counters in multithreaded code need `std::atomic<int>` (Lesson 53).
- "Named constructors" via static functions read well: `Color::fromHex("#ff8800")`, `Duration::seconds(5)`.

## ✅ Check yourself

1. How many copies of a static member exist if you create 100 objects?
2. Why can't a static member function use `this`?
3. Why can a class hold `Node*` but not `Node`?

<details><summary>Answers</summary>

1. One.
2. It isn't called on an object, so there is no `this`.
3. A `Node` inside a `Node` would need infinite size; a pointer has a fixed size.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 31: Namespaces](../31.Namespaces/README.md)
