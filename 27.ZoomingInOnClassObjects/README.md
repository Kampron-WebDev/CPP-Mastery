# Lesson 27: Zooming in on Class Objects

> **In one sentence:** This lesson is about **const-correctness**: marking which objects and
> functions *promise not to change anything*, plus some gotchas (dangling references,
> `mutable`) and **structured bindings**.

---

## 🎯 You will learn

- `const` objects and why they can only call `const` member functions.
- Passing objects as `const&` parameters.
- Getters that double as setters (returning references).
- Dangling pointers/references to members.
- `mutable` members.
- Structured bindings: `auto [x, y] = point;`

---

## 🧸 The Big Idea: the museum rule

A `const` object is a **museum exhibit**: you may *look* but not *touch*.
A `const` member function is a **museum guide** who promises: "I'll only look, never touch."
Only guides who make that promise are allowed near the exhibit.

```cpp
class Dog {
public:
    std::string name() const { return m_name; }   // ✅ "I only look"
    void rename(std::string n) { m_name = n; }    // ✋ changes things
private:
    std::string m_name{"Rex"};
};

const Dog museumDog;
museumDog.name();          // ✅ allowed
// museumDog.rename("X");  // ❌ compile error
```

---

## 📚 Step by step

### 1. Const objects ([27.2](27.2ConstObjects/main.cpp)) and parameters ([27.3](27.3ConstObjectsAsFunctionParameters/main.cpp))
Functions taking `const Dog&` can only call `const` member functions. So if you forget `const` on
your getters, **nobody can use your class through a const reference**. That's why it's a big deal.

### 2. Const member functions ([27.4](27.4ConstMemberFunctions/main.cpp))
`const` after the parameter list means `this` is a pointer-to-const inside the function.
**Rule:** every member function that doesn't modify the object should be `const`.

### 3. Getters that double as setters ([27.5](27.5GettersThatDoubleAsSetters/main.cpp))
```cpp
std::string& name() { return m_name; }                // non-const: caller can modify
const std::string& name() const { return m_name; }    // const overload: read-only
dog.name() = "Max";                                   // works through the reference
```
Powerful but it **breaks encapsulation** (no validation). Use sparingly.

### 4. Dangling references to members ([27.6](27.6DanglingPointersAndReferences/main.cpp))
If you keep a reference/pointer returned from an object **after the object dies**, it dangles:
```cpp
const std::string& n = Dog{}.name();   // temporary Dog dies at the ; so n dangles
```

### 5. `mutable` ([27.8MutableObjects](27.8MutableObjects/main.cpp))
A `mutable` member may change even inside `const` functions. Legit uses: caches, access counters,
mutexes. The object's *observable* state doesn't change.

### 6. Structured bindings ([27.9StructuredBindings](27.9StructuredBindings/main.cpp))
```cpp
struct Point { double x; double y; };
Point p{3, 4};
auto [x, y] = p;              // copies
auto& [rx, ry] = p;           // references into p
for (const auto& [name, score] : scoresMap) { ... }   // beautiful with maps (Lesson 44)
```

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [27.2ConstObjects](27.2ConstObjects/main.cpp) | What a const object can't do |
| [27.3ConstObjectsAsFunctionParameters](27.3ConstObjectsAsFunctionParameters/main.cpp) | `const Dog&` params |
| [27.4ConstMemberFunctions](27.4ConstMemberFunctions/main.cpp) | The fix: `const` functions |
| [27.5GettersThatDoubleAsSetters](27.5GettersThatDoubleAsSetters/main.cpp) | Returning references |
| [27.6DanglingPointersAndReferences](27.6DanglingPointersAndReferences/main.cpp) | Lifetime traps |
| [27.8MutableObjects](27.8MutableObjects/main.cpp) | `mutable` |
| [27.9StructuredBindings](27.9StructuredBindings/main.cpp) | `auto [a, b]` |

## ⚠️ Common mistakes

- Non-const getters: the class becomes unusable through `const&`.
- `mutable` as a hack to silence the compiler, which breaks const's promise.
- Returning a non-const reference to internal data and then being surprised it changed.

## 🧠 Senior developer notes

- **Const-correctness is a design tool**: reading a function signature tells you what it may change.
  Code reviewers check it.
- `const` member functions should be safe to call from multiple threads at once. If you use
  `mutable` caches, protect them with a mutex (Lesson 53).

## ✅ Check yourself

1. Why can't a `const` object call a non-const member function?
2. What does `const` after a member function's parameter list mean?
3. What's a legit use of `mutable`?

<details><summary>Answers</summary>

1. The non-const function might modify the object, which would break the const promise.
2. The function promises not to modify the object's (non-mutable) members.
3. Caching an expensive result, counting accesses, a mutex.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 28: Constructors and Initialization](../28.DivingDeepIntoConstructorsAndInitialization/README.md)
