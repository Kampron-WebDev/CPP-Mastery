# Lesson 33: Smart Pointers

> **In one sentence:** Smart pointers are pointers that **clean up after themselves**. When
> nobody needs the object any more, it's deleted automatically, so leaks and double-deletes disappear.

This is one of the most important lessons in modern C++. After it, you should almost never write `delete` again.

---

## 🎯 You will learn

- `std::unique_ptr`: one owner.
- `std::shared_ptr`: shared ownership with reference counting.
- `std::weak_ptr`: a non-owning observer that breaks cycles.
- `std::make_unique` / `std::make_shared`.
- Smart pointers with arrays, as function parameters and return values.

---

## 🧸 The Big Idea: who owns the balloon?

- **`unique_ptr`**: *one child holds the balloon string*. The child can **hand it over** (move) to
  another child, but two children can never hold it at once. When the holder goes home, the balloon is released.
- **`shared_ptr`**: *several children hold strings tied to the same balloon*. A counter tracks how many strings.
  When the **last** child lets go, the balloon is released.
- **`weak_ptr`**: *a child who can see the balloon* but holds no string. Before playing, they must ask
  "is it still here?" (`lock()`).

```
 unique_ptr:  [owner] ──► 🎈                     (count not needed: exactly 1)
 shared_ptr:  [a] ──┐
              [b] ──┼──► 🎈  use_count = 3
              [c] ──┘
 weak_ptr:    [w] ┄┄┄► 🎈  (doesn't count)
```

---

## 📚 Step by step

### 1. `unique_ptr` ([33.2](33.2UniquePointers/main.cpp))
```cpp
#include <memory>
auto dog = std::make_unique<Dog>("Rex");   // create (never use new yourself)
dog->bark();                               // use like a normal pointer
// auto copy = dog;                        // ❌ can't copy: single owner
auto newOwner = std::move(dog);            // ✅ transfer ownership; dog is now nullptr
}                                          // newOwner goes out of scope → Dog deleted automatically
```
Zero overhead compared to a raw pointer. **Your default choice.**

### 2. As parameters and return values ([33.3](33.3UniquePointersAsFunctionParametersAndReturnTypes/main.cpp))
| Signature | Meaning |
|-----------|---------|
| `void f(Dog& d)` / `void f(Dog* d)` | "I just **use** the dog" (most functions: don't mention smart pointers at all!) |
| `void f(std::unique_ptr<Dog> d)` | "Give me **ownership**" (caller must `std::move`) |
| `std::unique_ptr<Dog> make()` | "I **create** a dog and hand you ownership" (factories) |

### 3. Arrays ([33.4](33.4UniquePointersAndArrays/main.cpp), [33.7](33.7SharedPointersWithArrays/main.cpp))
`std::make_unique<int[]>(10)` works, but a `std::vector<int>` is almost always better.

### 4. `shared_ptr` ([33.5](33.5SharedPointers/main.cpp), [33.6](33.6SharedPointersFromUniquePointers/main.cpp), [33.8](33.8SharedPointersAsFunctionParametersAndReturnTypes/main.cpp))
```cpp
auto a = std::make_shared<Dog>("Rex");   // count 1
auto b = a;                              // count 2 (copying is allowed)
a.use_count();                           // 2
```
A `unique_ptr` converts to a `shared_ptr` (`std::shared_ptr<Dog> s = std::move(u);`) but not back.
Costs: an extra control block + **atomic** counter updates. Use it only when ownership is *really* shared.

### 5. `weak_ptr` ([33.9](33.9WeakPointers/main.cpp))
Problem: A holds a `shared_ptr` to B and B holds one to A. Their counts never reach 0 → **leak** (a cycle).
Fix: make one direction `weak_ptr`:
```cpp
std::weak_ptr<Person> friendRef = someShared;
if (auto locked = friendRef.lock()) {   // gets a shared_ptr if still alive
    locked->greet();
}
```

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [33.2UniquePointers](33.2UniquePointers/main.cpp) | Creating, moving, auto-delete |
| [33.3UniquePointersAsFunctionParametersAndReturnTypes](33.3UniquePointersAsFunctionParametersAndReturnTypes/main.cpp) | Ownership transfer |
| [33.4UniquePointersAndArrays](33.4UniquePointersAndArrays/main.cpp) | `unique_ptr<T[]>` |
| [33.5SharedPointers](33.5SharedPointers/main.cpp) | `use_count` |
| [33.6SharedPointersFromUniquePointers](33.6SharedPointersFromUniquePointers/main.cpp) | Converting |
| [33.7SharedPointersWithArrays](33.7SharedPointersWithArrays/main.cpp) | `shared_ptr<T[]>` |
| [33.8SharedPointersAsFunctionParametersAndReturnTypes](33.8SharedPointersAsFunctionParametersAndReturnTypes/main.cpp) | Passing shared ownership |
| [33.9WeakPointers](33.9WeakPointers/main.cpp) | `weak_ptr`, `lock()` |

## ⚠️ Common mistakes

- `std::unique_ptr<Dog> p{new Dog};` works, but prefer `make_unique` (exception-safe, no raw `new` in sight).
- Creating two smart pointers from the same raw pointer → double delete.
- Using a `unique_ptr` after `std::move`-ing from it (it's null now).
- `shared_ptr` everywhere "to be safe", which hides who really owns what and costs performance.
- Passing `const std::shared_ptr<T>&` when the function just needs `T&`.

## 🧠 Senior developer notes

- **Ownership is a design decision.** Ask for every heap object: *who owns it, and when should it die?*
  Answer with `unique_ptr` (one clear owner) in ~90% of cases.
- Raw pointers/references are still correct for **non-owning** access.
- This is RAII in action: resource lifetime tied to object lifetime (Lesson 52).
- Custom deleters: `std::unique_ptr<FILE, decltype(&fclose)> f{fopen("x", "r"), &fclose};` handles any resource, not just memory.

## ✅ Check yourself

1. Why can't a `unique_ptr` be copied?
2. When is the object behind a `shared_ptr` deleted?
3. What problem does `weak_ptr` solve?
4. What should a function that only *reads* a Dog take as parameter?

<details><summary>Answers</summary>

1. Copying would create two owners, but unique means exactly one.
2. When the last `shared_ptr` owning it is destroyed or reset (count reaches 0).
3. Reference cycles (leaks) and observing an object without keeping it alive.
4. `const Dog&` (not a smart pointer).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 34: Operator Overloading](../34.OperatorOverloading/README.md)
