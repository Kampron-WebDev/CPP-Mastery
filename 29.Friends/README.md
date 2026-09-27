# Lesson 29: Friends

> **In one sentence:** A `friend` is an outside function or class that a class **explicitly
> trusts** with access to its private members.

---

## 🎯 You will learn

- Friend functions.
- Friend classes.
- When friends are a good idea (and when they're a smell).

---

## 🧸 The Big Idea: the spare key

Your house (class) is locked; private rooms are private. But you give a **spare key** to one
trusted friend. They are not *part* of your family (not a member function), but they can come in.

Important rules:
- **You** decide who is your friend. Nobody can declare themselves your friend.
- Friendship is **not mutual**: if A trusts B, B doesn't automatically trust A.
- Friendship is **not inherited** and **not transitive**: a friend's friend is not your friend.

---

## 📚 Step by step

### 1. Friend functions ([29.2FriendFunctions](29.2FriendFunctions/main.cpp))
```cpp
class Dog {
    friend void debugPrint(const Dog& d);   // "debugPrint may see my privates"
private:
    std::string name{"Rex"};
};

void debugPrint(const Dog& d) { std::cout << d.name; }   // not a member, no Dog::
```

### 2. Friend classes ([29.3FriendClasses](29.3FriendClasses/main.cpp))
```cpp
class Engine {
    friend class Car;   // all of Car's member functions can access Engine's privates
private:
    int rpm{0};
};
```

### The #1 real use: `operator<<` (Lesson 34)
```cpp
class Point {
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << '(' << p.x << ", " << p.y << ')';
    }
    double x{}, y{};
};
std::cout << Point{};   // (0, 0)
```
`operator<<` can't be a member (the left side is `std::ostream`, not `Point`), so friendship gives it access.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [29.2FriendFunctions](29.2FriendFunctions/main.cpp) | A function with private access |
| [29.3FriendClasses](29.3FriendClasses/main.cpp) | A whole class with private access |

## ⚠️ Common mistakes

- Using `friend` to "fix" access errors everywhere, which destroys encapsulation.
- Thinking a friend function is a member (it isn't: no `this`, no `ClassName::`).

## 🧠 Senior developer notes

- Friends are fine for **tightly coupled pairs** designed together (a container + its iterator,
  a class + its operators). Otherwise, prefer adding a proper public function.
- "Hidden friends" (friend functions *defined* inside the class, like `operator<<` above) are only found through
  argument-dependent lookup. That speeds compilation and avoids accidental conversions, and it's the modern best practice for operators.

## ✅ Check yourself

1. If class A declares `friend class B;`, can A access B's privates?
2. Is a friend function a member function?

<details><summary>Answers</summary>

1. No. Friendship is one-way.
2. No. It's a normal function with special access.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 30: Const and Static Members](../30.ConstAndStaticMembers/README.md)
