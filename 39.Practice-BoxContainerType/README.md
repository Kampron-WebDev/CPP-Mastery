# Lesson 39: Practice Project: Building a BoxContainer

> **In one sentence:** You build your own growable container class, a mini `std::vector`,
> which ties together classes, dynamic memory, copy semantics, operators and interfaces.

This is a **project lesson**. Instead of new syntax, you combine everything from Lessons 13–38.
Building a container yourself is the best way to *truly* understand what `std::vector` does for you.

---

## 🎯 You will practise

- Owning heap memory in a class (constructor allocates, destructor frees).
- Deep-copy constructor and copy assignment.
- Growing capacity (`expand`) when full.
- Adding and removing items while keeping the data packed.
- `operator+=`, `operator+`, `operator=`.
- An interface class (`StreamInsertable`) to make any class printable with `<<`.
- Why templates are needed (39.7 duplicates the class for int/double/char!).

---

## 🧸 The Big Idea: a magic toy box

The box has a number of **slots** (capacity) and a number of **toys** actually in it (size).

```
 capacity = 8, size = 5
 ┌────┬────┬────┬────┬────┬────┬────┬────┐
 │ 7  │ 3  │ 9  │ 3  │ 1  │ ?  │ ?  │ ?  │
 └────┴────┴────┴────┴────┴────┴────┴────┘
   0    1    2    3    4    ▲ next toy goes here (index = size)
```

When the box is **full** and you add another toy, the box: (1) gets a **bigger** box, (2) moves all
toys across, (3) throws the old box away. Real `std::vector` usually doubles the size, so this rarely happens.

**Removing** a toy: fill the hole so there are no gaps. The fastest way is to move the **last** toy into the hole
(order changes, but no shifting needed).

---

## 🗂️ The project, step by step

| Step | Folder | What's added | Key ideas |
|------|--------|--------------|-----------|
| 1 | [39.2ConstructingDestroying](39.2ConstructingDestroying/boxcontainer.h) | Constructor, copy constructor, destructor, printing | Owning memory; `StreamInsertable` interface |
| 2 | [39.3AddingItems](39.3AddingItems/boxcontainer.cpp) | `add()` and `expand()` | Grow-and-copy |
| 3 | [39.4RemovingItems](39.4RemovingItems/boxcontainer.cpp) | `remove_item()`, `remove_all()` | Keeping data packed |
| 4 | [39.5OtherOperators](39.5OtherOperators/boxcontainer.h) | `+=`, `+`, `=` | Operators reusing each other |
| 5 | [39.7StoringInDifferentTypes](39.7StoringInDifferentTypes/main.cpp) | Int/Double/Char containers | Copy-paste per type, **the problem templates solve** (Lesson 40) |

Each folder has several files; the build task compiles them all. Open `main.cpp` and press `Ctrl+Shift+B`.

### The `StreamInsertable` interface
```cpp
class StreamInsertable {
    friend std::ostream& operator<<(std::ostream& out, const StreamInsertable& operand);
public:
    virtual void stream_insert(std::ostream& out) const = 0;
};
```
Any class that inherits it and implements `stream_insert` works with `std::cout << obj`.
That's Lesson 37's polymorphism + Lesson 29's friends working together.

---

## 🧠 Senior review of the original design

A code review is a great learning tool. Things a senior would point out in this container, and fix in the exercises:

1. **`operator=` returns `void`**, so `a = b = c;` doesn't work. It should return `BoxContainer&`.
2. **Growing by a fixed step (5)** makes adding N items cost about N²/5 copies. **Doubling** makes it amortized O(1) per add.
3. **No move constructor/assignment**, so returning a BoxContainer from `operator+` copies twice (Lesson 41).
4. **Manual memory** means Rule of Three/Five bugs are easy. A `std::vector` or `std::unique_ptr<T[]>` member would make it Rule of Zero.
5. Only works for `int` → use a **class template** (Lesson 40).

## ✅ Check yourself

1. What's the difference between size and capacity?
2. Why must the copy constructor allocate new memory?
3. Why is "grow by doubling" better than "grow by 5"?

<details><summary>Answers</summary>

1. Size = items stored; capacity = slots available before growing.
2. Otherwise both objects share one array → double delete (shallow copy).
3. With doubling, the total copying work stays proportional to N (amortized constant per add); with +5 it grows like N².
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 40: Class Templates](../40.ClassTemplates/README.md)
