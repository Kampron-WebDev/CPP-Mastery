# Lesson 40: Class Templates

> **In one sentence:** A class template is a **blueprint for blueprints**: write
> `BoxContainer<T>` once, and get a container of `int`, `double`, `std::string`, anything.

---

## 🎯 You will learn

- Writing class templates and their member functions.
- Non-type template parameters (`template <typename T, std::size_t N>`).
- Default template arguments.
- Specializing a whole class or single member functions.
- Friends and `operator<<` for class templates.
- Constraining class templates with type traits, `static_assert`, and **concepts**.

---

## 🧸 The Big Idea: a jelly mould

Lesson 39.7 had **three copies** of the same container class, one each for int, double and char. Painful!
A class template is a **jelly mould** with a label that says "fill with: T".

```cpp
template <typename T>
class Box {
public:
    explicit Box(T value) : item{std::move(value)} {}
    const T& get() const { return item; }
private:
    T item;
};

Box<int> a{42};
Box<std::string> b{"hello"};
Box c{3.14};            // C++17 CTAD: Class Template Argument Deduction figures out Box<double>
```
`std::vector<T>`, `std::array<T, N>`, `std::map<K, V>`, `std::unique_ptr<T>`: all class templates.

---

## 📚 Step by step

### 1. First class template ([40.2](40.2YourFirstClassTemplate/main.cpp))
Member functions defined **outside** the class need the template header again:
```cpp
template <typename T>
const T& Box<T>::get() const { return item; }
```
And (like function templates) **everything goes in the header**.

### 2. Non-type parameters ([40.4](40.4NonTypeTemplateParameters/main.cpp))
```cpp
template <typename T, std::size_t N>
class FixedArray { T data[N]; };        // exactly how std::array works
FixedArray<int, 10> arr;
```

### 3. Default arguments ([40.5](40.5DefaultValuesForTemplateParameters/main.cpp))
`template <typename T = int, std::size_t N = 5>` → `FixedArray<> a;`

### 4. Specialization ([40.7](40.7TemplateSpecializations/main.cpp), [40.8](40.8TemplateSpecializationWithSelectMemberFunctions/main.cpp))
Full class specialization: `template <> class Box<char*> { ... };` (a completely different implementation).
You can also specialize just one member function.

### 5. Friends & streams ([40.10](40.10FriendFunctionsForClassTemplates/main.cpp), [40.11](40.11StreamInsertionOperatorForClassTemplates/main.cpp))
Easiest: define the friend inside the class (hidden friend):
```cpp
friend std::ostream& operator<<(std::ostream& os, const Box& b) { return os << b.item; }
```

### 6. Constraining ([40.12](40.12ClassTemplatesWithTypeTraitsAndStaticAsserts/main.cpp)–[40.16](40.16ConceptsExample2/main.cpp))
```cpp
template <typename T>
class Stats {
    static_assert(std::is_arithmetic_v<T>, "Stats needs numbers");   // old way
};

template <std::floating_point T>   // C++20 way
class Point { T x, y; };
```

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [40.2YourFirstClassTemplate](40.2YourFirstClassTemplate/main.cpp) | Template BoxContainer |
| [40.4NonTypeTemplateParameters](40.4NonTypeTemplateParameters/main.cpp) | `<T, N>` |
| [40.5DefaultValuesForTemplateParameters](40.5DefaultValuesForTemplateParameters/main.cpp) | Defaults |
| [40.7TemplateSpecializations](40.7TemplateSpecializations/main.cpp) | Full specialization |
| [40.8TemplateSpecializationWithSelectMemberFunctions](40.8TemplateSpecializationWithSelectMemberFunctions/main.cpp) | Member specialization |
| [40.10FriendFunctionsForClassTemplates](40.10FriendFunctionsForClassTemplates/main.cpp) | Friends |
| [40.11StreamInsertionOperatorForClassTemplates](40.11StreamInsertionOperatorForClassTemplates/main.cpp) | `<<` |
| [40.12ClassTemplatesWithTypeTraitsAndStaticAsserts](40.12ClassTemplatesWithTypeTraitsAndStaticAsserts/main.cpp) | `static_assert` |
| [40.13ClassTemplatesWithConcepts](40.13ClassTemplatesWithConcepts/main.cpp) | Concepts on classes |
| [40.14BuiltInConcepts](40.14BuiltInConcepts/main.cpp) | `<concepts>` |
| [40.15ConceptsExample1](40.15ConceptsExample1/main.cpp), [40.16ConceptsExample2](40.16ConceptsExample2/main.cpp) | Worked examples |

## ⚠️ Common mistakes

- Member definitions in a `.cpp` → linker errors. Keep them in the header.
- Forgetting `template <typename T>` + `Box<T>::` before out-of-class member definitions.
- Using a type that lacks an operation the template needs. Constrain with concepts to get a clear error.

## 🧠 Senior developer notes

- Templates are **compile-time polymorphism**: no vtable, full inlining, but longer compile times and bigger binaries.
- Prefer composition of standard templates (`std::vector<T>` member) over writing raw memory management inside your template.
- CTAD + deduction guides make templates pleasant to use: `std::pair p{1, "a"};`

## ✅ Check yourself

1. What is `N` in `template <typename T, std::size_t N>`?
2. Why must class template member functions be in headers?
3. How do you require that `T` is a floating-point type?

<details><summary>Answers</summary>

1. A non-type template parameter: a compile-time value.
2. The compiler must see the full definition to generate code for each type used.
3. `template <std::floating_point T>` (or `requires std::floating_point<T>`, or a `static_assert`).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 41: Move Semantics](../41.MoveSemantics/README.md)
