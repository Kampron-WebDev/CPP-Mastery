# Lesson 52: RAII and the Rule of Zero / Three / Five ⭐ NEW

> **In one sentence:** **RAII** means "a resource is owned by an object, and released in that
> object's destructor". It is *the* most important idea in C++, and the reason good C++ code has
> no leaks, no forgotten unlocks, and no `finally` blocks.

---

## 🎯 You will learn

- RAII: Resource Acquisition Is Initialization.
- Wrapping any resource (memory, files, locks, handles) in a class.
- The **Rule of Zero**, **Rule of Three**, **Rule of Five**.
- The **copy-and-swap** idiom (strong exception safety).
- Scope guards, and `std::unique_ptr` with a custom deleter.

---

## 🧸 The Big Idea: the library book with a timer

Imagine library books that **return themselves** the moment you leave the library, however you leave:
through the door, through the window, or because the fire alarm went off. You can never forget to return a book.

That's RAII:
- **Acquire** the resource in the **constructor** (borrow the book).
- **Release** it in the **destructor** (return the book).
- C++ **guarantees** destructors run when an object goes out of scope: normal exit, early `return`,
  `break`, or an exception flying past (stack unwinding, Lesson 38).

```cpp
void risky()
{
    std::ifstream file{"data.txt"};      // opened (acquired)
    std::lock_guard lock{mutex};         // locked (acquired)
    auto buffer = std::make_unique<char[]>(1024);   // allocated (acquired)
    if (somethingWrong) throw std::runtime_error{"oops"};
    // ...
}   // ← ALL released here automatically, in reverse order, even if we threw
```
You already use RAII: `std::string`, `std::vector`, `std::unique_ptr`, `std::fstream`, `std::lock_guard`, `std::jthread`.

---

## 📚 Step by step

### 1. Writing your own RAII wrapper ([Examples/01_FileHandleRAII](Examples/01_FileHandleRAII/main.cpp))
```cpp
class File {
public:
    explicit File(const char* path) : f{std::fopen(path, "w")} {
        if (!f) throw std::runtime_error{"cannot open"};
    }
    ~File() { if (f) std::fclose(f); }
    File(const File&) = delete;                 // a file handle shouldn't be copied
    File& operator=(const File&) = delete;
    File(File&& o) noexcept : f{std::exchange(o.f, nullptr)} {}   // but it can be moved
    File& operator=(File&& o) noexcept { if (this != &o) { if (f) std::fclose(f); f = std::exchange(o.f, nullptr); } return *this; }
    void write(const char* text) { std::fputs(text, f); }
private:
    std::FILE* f;
};
```

### 2. The Rules
| Rule | Says | When |
|------|------|------|
| **Rule of Zero** | Write **none** of the special members. | Your members already manage themselves (`std::string`, `std::vector`, `std::unique_ptr`). **This is the goal for 95% of classes.** |
| **Rule of Three** (C++98) | If you write a destructor, copy constructor, or copy assignment, write all three. | A class that directly owns a resource |
| **Rule of Five** (C++11) | …plus move constructor and move assignment. | Same, and you want efficient moves |

The five special members:
```cpp
~T();                          // destructor
T(const T&);                   // copy constructor
T& operator=(const T&);        // copy assignment
T(T&&) noexcept;               // move constructor
T& operator=(T&&) noexcept;    // move assignment
```
See the full Rule-of-Five `MyString` in [Examples/02_RuleOfFiveString](Examples/02_RuleOfFiveString/main.cpp).

### 3. Copy-and-swap
```cpp
T& operator=(T other) noexcept   // take BY VALUE: the copy (or move) happens here
{
    swap(*this, other);          // swap our guts with the copy
    return *this;                // other's destructor frees our OLD data
}
```
One function handles copy **and** move assignment, is self-assignment safe, and gives the **strong exception
guarantee** (if the copy throws, `*this` is untouched).

### 4. Scope guards and custom deleters ([Examples/03_ScopeGuard](Examples/03_ScopeGuard/main.cpp))
```cpp
auto closer = [](std::FILE* f) { if (f) std::fclose(f); };
std::unique_ptr<std::FILE, decltype(closer)> file{std::fopen("x.txt", "w"), closer};   // RAII for a C API in one line
```
A **scope guard** runs any lambda at scope exit: perfect for "undo if we didn't finish" logic.

---

## 🗂️ Examples

| Folder | Shows |
|--------|-------|
| [01_FileHandleRAII](Examples/01_FileHandleRAII/main.cpp) | A move-only RAII wrapper around a C `FILE*` |
| [02_RuleOfFiveString](Examples/02_RuleOfFiveString/main.cpp) | All five special members + copy-and-swap, with logging |
| [03_ScopeGuard](Examples/03_ScopeGuard/main.cpp) | A generic scope guard; `unique_ptr` custom deleter |

## ⚠️ Common mistakes

- A destructor that frees memory, but the class is still copyable → double free (Rule of Three violated).
- Move operations that don't null out the source.
- Resources acquired *outside* a constructor ("call `init()` after constructing"), so objects can exist in a half-built state.
- Throwing from destructors.

## 🧠 Senior developer notes

- In code review, **any `new`, `delete`, `malloc`, `fopen`, `lock()` outside an RAII class is a red flag.**
- Design classes so that **if an object exists, it's valid** (constructors establish invariants or throw).
- RAII is why C++ doesn't need garbage collection *or* `finally`: cleanup is deterministic and immediate.

## ✅ Check yourself

1. What does RAII stand for, and what does it mean in plain words?
2. Your class has a `std::string` and a `std::vector` member. Which special members should you write?
3. Why does copy-and-swap give the strong exception guarantee?
4. Name three RAII types in the standard library.

<details><summary>Answers</summary>

1. Resource Acquisition Is Initialization: an object owns a resource and releases it in its destructor.
2. None: Rule of Zero. The members already copy, move and clean up correctly.
3. The risky part (making the copy) happens before `*this` is modified; the swap itself can't throw.
4. `std::unique_ptr`, `std::vector`, `std::fstream`, `std::lock_guard`, `std::jthread`, `std::string`…
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 53: Concurrency](../53.Concurrency/README.md)
