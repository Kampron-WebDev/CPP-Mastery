# Lesson 47: Building Iterators for Custom Containers

> **In one sentence:** If you give your own container an **iterator** (with the right
> operations), it instantly works with range-for loops, STL algorithms and even C++20 views.

(The sub-folders here are numbered `40.xx` from the original course recording. They belong to this lesson.)

---

## 🎯 You will learn

- The iterator categories and what each one can do.
- Building input, output, forward, bidirectional and random-access iterators.
- Making custom iterators work with ranges/views (C++20 iterator concepts).
- Constant iterators.
- Raw pointers as iterators; wrapping another container's iterators.

---

## 🧸 The Big Idea: what can your finger do?

Every iterator is a "finger" (Lesson 43), but some fingers have more powers:

```
 Input          → read once, move forward       (reading a keyboard stream)
 Output         → write once, move forward      (printing)
 Forward        → read many times, forward      (singly linked list)
 Bidirectional  → forward AND backward          (doubly linked list, map)
 Random access  → jump anywhere: it + 5, it[3]  (vector, array, deque)
 Contiguous     → random access + items sit side by side in memory (vector, array)
```
Each level can do everything the level above it can. Algorithms say which power they need:
`std::sort` needs random access, which is why you can't `std::sort` a `std::list` (it has its own `list.sort()`).

---

## 📚 What an iterator needs (forward iterator example)

```cpp
class Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = int;
    using pointer           = int*;
    using reference         = int&;

    reference operator*() const { return *ptr; }                 // *it
    pointer operator->() { return ptr; }                         // it->member
    Iterator& operator++() { ++ptr; return *this; }              // ++it
    Iterator operator++(int) { Iterator t = *this; ++ptr; return t; }   // it++
    friend bool operator==(const Iterator&, const Iterator&) = default; // it == end
private:
    int* ptr{nullptr};
};
// and the container provides: Iterator begin(); Iterator end();
```
Bidirectional adds `--`. Random access adds `+ - += -= [] <` and `it2 - it1`.

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [40.02.IteratorPowers](40.02.IteratorPowers/main.cpp) | The categories in action |
| [40.04CustomInputIterator](40.04CustomInputIterator/main.cpp) | Input iterator |
| [40.05CustomOutputIterator](40.05CustomOutputIterator/main.cpp) | Output iterator |
| [40.06CustomForwardIterator](40.06CustomForwardIterator/main.cpp) | Forward iterator |
| [40.07CustomBidirectionalIteator](40.07CustomBidirectionalIteator/main.cpp) | Bidirectional |
| [40.08CustomRandomAccessIterator](40.08CustomRandomAccessIterator/main.cpp) | Random access (works with `std::sort`) |
| [40.09CustomIteratorsWithViews](40.09CustomIteratorsWithViews/main.cpp) | Making views work |
| [40.10ConstantIterators](40.10ConstantIterators/main.cpp) | `const_iterator` |
| [40.11RawPointersAsIterators](40.11RawPointersAsIterators/main.cpp) | Pointers are iterators |
| [40.12WrappingIteratorsFromOtherContainers](40.12WrappingIteratorsFromOtherContainers/main.cpp) | Reusing `std::vector`'s iterators |

## ⚠️ Common mistakes

- Missing `const` versions (`begin() const` / `cbegin()`): the container can't be iterated when const.
- Views (C++20) require a default constructor and `==`. Check with `static_assert(std::forward_iterator<MyIt>);`.
- Forgetting that `end()` is one-past-the-last.

## 🧠 Senior developer notes

- Often the simplest correct answer is to **wrap** a standard container and forward its iterators (40.12), or use raw pointers (40.11) when storage is contiguous.
- `static_assert(std::random_access_iterator<It>)` documents and tests your iterator at compile time.

## ✅ Check yourself

1. Which iterator category does `std::sort` require?
2. What's the difference between forward and bidirectional iterators?
3. Name the 5 type aliases an iterator traditionally provides.

<details><summary>Answers</summary>

1. Random access.
2. Bidirectional iterators can also move backwards (`--`).
3. `iterator_category`, `difference_type`, `value_type`, `pointer`, `reference`.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 48: Coroutines](../48.Coroutines/README.md)
