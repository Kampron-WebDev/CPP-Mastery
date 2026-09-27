# Lesson 41: Move Semantics

> **In one sentence:** Moving lets one object **steal** the resources of another object that's
> about to be thrown away, instead of making an expensive copy. That's the secret behind modern C++ speed.

---

## 🎯 You will learn

- lvalues vs rvalues.
- Rvalue references `T&&`.
- Move constructors and move assignment operators.
- `std::move`, and what happens to a moved-from object.
- Move-only types.
- Passing by rvalue reference.

---

## 🧸 The Big Idea: moving house

You're moving to a new house. Two options:
- **Copy:** buy a *brand-new identical* copy of every piece of furniture, then leave the old ones. Slow and wasteful!
- **Move:** put the *existing* furniture in the truck. The old house is left empty, but who cares: you're leaving it.

```
 COPY:  old [sofa, bed, TV]   →   new [sofa', bed', TV']   (everything duplicated)
 MOVE:  old [sofa, bed, TV]   →   new [sofa, bed, TV]      old house: [ ] (empty but valid)
```

For a `std::vector` of a million elements, a copy copies a million elements. A move copies **three pointers**.

---

## 📚 Step by step

### 1. lvalues and rvalues ([41.2](41.2LvaluesAndRvalues/main.cpp))
- **lvalue**: has a name / an address you can take. It lives on: `x`, `arr[3]`, `*ptr`.
- **rvalue**: a temporary with no name, about to vanish: `42`, `a + b`, `makeString()`.

Simple test: *can I write `&thing`?* Yes → lvalue.

### 2. Rvalue references ([41.3](41.3RvalueReferences/main.cpp), [41.4](41.4MovingTemporariesAround/main.cpp))
`int&& r = 5 + 3;`: `T&&` binds **only to rvalues**. It's how a function says *"give me something disposable"*.

### 3. Move constructor & move assignment ([41.5](41.5MoveConstructorsMoveAssignmentOperators/main.cpp))
```cpp
class Buffer {
public:
    Buffer(Buffer&& other) noexcept            // MOVE constructor
        : data{other.data}, size{other.size}
    {
        other.data = nullptr;                   // leave the old one empty but valid
        other.size = 0;
    }
    Buffer& operator=(Buffer&& other) noexcept  // MOVE assignment
    {
        if (this != &other) {
            delete[] data;                      // free what we had
            data = std::exchange(other.data, nullptr);
            size = std::exchange(other.size, 0);
        }
        return *this;
    }
private:
    int* data{nullptr};
    std::size_t size{0};
};
```
⭐ Mark moves `noexcept`: `std::vector` only uses your move (instead of copy) when growing if it's `noexcept`.

### 4. `std::move` ([41.6](41.6MovingLvaluesWithStdMove/main.cpp))
`std::move(x)` **doesn't move anything**! It's just a cast that says *"treat x as disposable"*. The actual move happens
in the move constructor/assignment that then gets chosen.
```cpp
std::string a{"a long string..."};
std::string b = std::move(a);   // b stole a's buffer; a is now "valid but unspecified" (usually empty)
```

### 5. After a move ([41.7](41.7InvalidatePointersAfterStdMove/main.cpp))
A moved-from object may only be **destroyed or assigned a new value**. Don't read it expecting the old contents.

### 6. Move-only types ([41.08](41.08MoveOnlyTypes/main.cpp))
Delete the copy operations, keep the moves: `std::unique_ptr`, `std::thread`, file handles.

### 7. Passing by rvalue reference ([41.09](41.09PassingByRvalueReference/main.cpp))
`void store(std::string&& s)` accepts only temporaries/moved values. Often simpler: take **by value** and move inside:
```cpp
void setName(std::string n) { name = std::move(n); }   // callers pass copies OR temporaries: both efficient
```

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [41.2LvaluesAndRvalues](41.2LvaluesAndRvalues/main.cpp) | Value categories |
| [41.3RvalueReferences](41.3RvalueReferences/main.cpp) | `T&&` |
| [41.4MovingTemporariesAround](41.4MovingTemporariesAround/main.cpp) | Temporaries |
| [41.5MoveConstructorsMoveAssignmentOperators](41.5MoveConstructorsMoveAssignmentOperators/main.cpp) | Writing moves |
| [41.6MovingLvaluesWithStdMove](41.6MovingLvaluesWithStdMove/main.cpp) | `std::move` |
| [41.7InvalidatePointersAfterStdMove](41.7InvalidatePointersAfterStdMove/main.cpp) | Moved-from state |
| [41.08MoveOnlyTypes](41.08MoveOnlyTypes/main.cpp) | Copy deleted, move allowed |
| [41.09PassingByRvalueReference](41.09PassingByRvalueReference/main.cpp) | `f(T&&)` |

## ⚠️ Common mistakes

- Using an object after `std::move`-ing from it.
- `return std::move(localVar);`, which blocks RVO and makes things slower.
- `std::move` on a `const` object: it silently **copies** (you can't steal from a const).
- Forgetting `noexcept` on move operations.
- Forgetting to null out the source's pointer → double delete.

## 🧠 Senior developer notes

- **Rule of Five:** destructor, copy ctor, copy assign, move ctor, move assign. Write all or none.
  Better: **Rule of Zero**. Use members that already know how to move (`std::vector`, `std::string`, `std::unique_ptr`).
- `T&&` in a *template* (`template <typename T> void f(T&& x)`) is a **forwarding reference**, not an rvalue reference.
  Pair it with `std::forward<T>(x)`, as in `std::make_unique`.

## ✅ Check yourself

1. Is `x + 1` an lvalue or an rvalue?
2. What does `std::move` actually do?
3. Why should move constructors be `noexcept`?
4. What state is a moved-from `std::string` in?

<details><summary>Answers</summary>

1. rvalue (a temporary result).
2. Casts its argument to an rvalue reference; the move happens in whatever function receives it.
3. So containers like `std::vector` can use them safely during reallocation (strong exception guarantee).
4. Valid but unspecified (in practice usually empty). Only assign to it or destroy it.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 42: Function-like Entities](../42.FunctionLikeEntities/README.md)
