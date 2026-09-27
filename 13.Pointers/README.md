# Lesson 13: Pointers

> **In one sentence:** A pointer is a variable that holds an **address**, like a note that says
> *"the treasure is in locker 1004"*, instead of holding the treasure itself.

Pointers scare beginners only because they're explained badly. If you remember
**"a variable lives at an address"** from Lesson 01, you already understand 80% of this lesson.

---

## 🎯 You will learn

- Declaring pointers, `&` (address-of) and `*` (dereference).
- `nullptr` and null safety.
- Pointers to `char` and arrays of C-strings.
- `const` with pointers (4 combinations).
- Pointers and arrays, and pointer arithmetic.
- **Dynamic memory**: `new`, `delete`, `new[]`, `delete[]`.
- The three classic disasters: **dangling pointers**, **memory leaks**, **double delete**.

---

## 🧸 The Big Idea: lockers and notes

```
         a normal int                 a pointer to that int
  int score{42};               int* p{&score};

  address 1004                  address 2000
  ┌──────────────┐              ┌──────────────┐
  │      42      │ ◄─────────── │     1004     │
  └──────────────┘   "points     └──────────────┘
   name: score        to"         name: p
```

- `&score` means **"where does score live?"** → `1004`
- `p` stores that address.
- `*p` means **"go to the address in p and open the locker"** → `42`
- `*p = 50;` changes what's in locker 1004, so `score` is now 50!

| You write | Read it as | Gives |
|-----------|-----------|-------|
| `int* p` | "p is a pointer to an int" | a variable that can hold an int's address |
| `&x` | "address of x" | e.g. `1004` |
| `*p` | "the thing p points at" | the int in the locker |
| `p = nullptr` | "p points at nothing" | a safe "empty" value |

---

## 📚 Step by step

### 1. Declaring and using ([13.2](13.2DeclaringAndUsingPointers/main.cpp))
```cpp
int value{42};
int* p{&value};       // p holds value's address
std::cout << p;       // prints an address like 0x61ff08
std::cout << *p;      // 42
*p = 7;               // value is now 7
int* empty{nullptr};  // ALWAYS initialize; nullptr if nothing yet
```
All pointers are the same size (8 bytes on 64-bit), no matter what they point at. They're all just addresses.

### 2. Pointers to char ([13.3](13.3PointerToChar/main.cpp), [13.4](13.4ArrayOfPointerToChar/main.cpp))
`const char* name{"Ada"};` points at the first letter of a string literal. `cout` prints
the text (not the address) for `char*`, because it assumes a C-string.
String literals are **read-only**, so always use `const char*` for them.

### 3. `const` and pointers ([13.5](13.5ConstPointerAndPointerToConst/main.cpp), [13.6](13.6ArrayOfContPointerToConstChar/main.cpp))
**Read it right to left:**
```cpp
int* p;                   // pointer to int: can change both
const int* p;             // pointer to CONST int: can't change the value via p
int* const p = &x;        // CONST pointer to int: can't point somewhere else
const int* const p = &x;  // can change neither
```
Kid version: `const` on the **left of `*`** locks the *treasure*; on the **right of `*`** it locks the *note*.

### 4. Pointers and arrays ([13.7](13.7PointersAndArrays/main.cpp), [13.8](13.8SwappingArrayData_Demo/main.cpp))
An array's name **decays** into a pointer to its first element:
```cpp
int nums[]{10, 20, 30};
int* p = nums;          // same as &nums[0]
p[1] == *(p + 1) == nums[1] == 20
```

### 5. Pointer arithmetic ([13.10](13.10PointerArithmetic_Navigation/main.cpp)–[13.13](13.13SwappingArrayData_PointerArithmetic/main.cpp))
`p + 1` moves by **one element**, not one byte (for `int`, that's 4 bytes).
```
 nums:  [10][20][30]
         ▲   ▲   ▲
         p  p+1 p+2
```
- `p2 - p1` = number of elements between them (type `std::ptrdiff_t`).
- You can compare pointers into the **same** array with `<`, `>`.

### 6. Dynamic memory ([13.15](13.15DynamicMemoryAllocation/main.cpp))
So far every variable lived on the **stack**: automatic, fast, destroyed at `}`.
The **heap** (free store) is memory you ask for **while running**, and keep until you give it back.

```cpp
int* p = new int{5};    // ask the heap for one int
std::cout << *p;
delete p;               // give it back. YOU must do this!
p = nullptr;            // good habit

int* arr = new int[n];  // size can be decided at run time
delete[] arr;           // arrays need delete[]  (with brackets!)
```

```
 STACK (automatic)              HEAP (manual)
 ┌──────────────┐              ┌──────────────┐
 │ p: 0x7A00 ───┼────────────► │  5           │  ← lives until delete
 └──────────────┘              └──────────────┘
 destroyed at }                 NOT destroyed at }
```

### 7. The three disasters ([13.16](13.16DanglingPointers/main.cpp)–[13.19](13.19MemoryLeaks/main.cpp))
| Disaster | What happens | Kid version |
|----------|--------------|-------------|
| **Memory leak** | `new` without `delete`. Memory is lost until the program ends. | Borrowing library books and never returning them; eventually the library is empty |
| **Dangling pointer** | Using a pointer after `delete` (or to a dead local). | A note pointing to a locker that was given to someone else |
| **Double delete** | `delete` the same memory twice. Crash or corruption. | Returning the same book twice |

Also: `new` can fail ([13.17](13.17WhenNewFails/main.cpp)). It throws `std::bad_alloc`, or returns `nullptr` with `new(std::nothrow)`.
Always check for null before dereferencing ([13.18](13.18NullPointerSafety/main.cpp)).

### 8. Dynamic arrays ([13.20](13.20DynamicallyAllocatedArrays/main.cpp))
`new int[n]{}` creates n zeros. But `std::size` doesn't work on it, because a pointer doesn't know how many elements follow it.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [13.2DeclaringAndUsingPointers](13.2DeclaringAndUsingPointers/main.cpp) | `&`, `*`, `nullptr` |
| [13.3PointerToChar](13.3PointerToChar/main.cpp) | `const char*` |
| [13.4ArrayOfPointerToChar](13.4ArrayOfPointerToChar/main.cpp) | A list of strings |
| [13.5ConstPointerAndPointerToConst](13.5ConstPointerAndPointerToConst/main.cpp) | The 4 const combinations |
| [13.6ArrayOfContPointerToConstChar](13.6ArrayOfContPointerToConstChar/main.cpp) | Fully const string tables |
| [13.7PointersAndArrays](13.7PointersAndArrays/main.cpp) | Array decay |
| [13.8SwappingArrayData_Demo](13.8SwappingArrayData_Demo/main.cpp) | Swapping via pointers |
| [13.10PointerArithmetic_Navigation](13.10PointerArithmetic_Navigation/main.cpp) | `p + n`, `++p` |
| [13.11PointerArithmetic_DistanceBetweenElements](13.11PointerArithmetic_DistanceBetweenElements/main.cpp) | `p2 - p1` |
| [13.12PointerArithmetic_ComparingPointers](13.12PointerArithmetic_ComparingPointers/main.cpp) | `<`, `>` on pointers |
| [13.13SwappingArrayData_PointerArithmetic](13.13SwappingArrayData_PointerArithmetic/main.cpp) | Arithmetic-based swaps |
| [13.15DynamicMemoryAllocation](13.15DynamicMemoryAllocation/main.cpp) | `new` / `delete` |
| [13.16DanglingPointers](13.16DanglingPointers/main.cpp) | Use after delete |
| [13.17WhenNewFails](13.17WhenNewFails/main.cpp) | `std::bad_alloc`, `nothrow` |
| [13.18NullPointerSafety](13.18NullPointerSafety/main.cpp) | Checking for null |
| [13.19MemoryLeaks](13.19MemoryLeaks/main.cpp) | Losing the only pointer |
| [13.20DynamicallyAllocatedArrays](13.20DynamicallyAllocatedArrays/main.cpp) | `new[]` / `delete[]` |

## ⚠️ Common mistakes

- `int* a, b;` makes `a` a pointer but `b` a plain int! Declare one per line.
- Dereferencing `nullptr` or an uninitialized pointer, which crashes.
- `delete` for something made with `new[]` (use `delete[]`) and vice-versa.
- Returning `&localVariable` from a function (dangling).

## 🧠 Senior developer notes

- **In modern C++, you almost never write `new`/`delete` yourself.** Use `std::vector`,
  `std::string`, `std::unique_ptr`, `std::shared_ptr` (Lesson 33). They release memory
  automatically (RAII, Lesson 52). This lesson exists so you understand *what they do for you*,
  and so you can read older code.
- Raw pointers are still fine as **non-owning observers** ("I can look at it, but I don't own it").
- Tools that find pointer bugs: AddressSanitizer (`-fsanitize=address` on Linux/Clang), Valgrind, and the debugger (Lesson 55).

## ✅ Check yourself

1. `int x{3}; int* p{&x}; *p += 2;` What is x?
2. `int arr[]{5,10,15}; int* p = arr + 1;` What is `*p`? `p[1]`?
3. What's the difference between `const int* p` and `int* const p`?
4. What is a memory leak? How do you avoid one in modern C++?
5. What must you use to free `new int[10]`?

<details><summary>Answers</summary>

1. 5.
2. `10`; `15`.
3. The first can't change the *value* through p; the second can't change *where p points*.
4. Memory allocated with `new` that is never `delete`d. Use smart pointers / containers (RAII).
5. `delete[]`.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 14: References](../14.References/README.md)
