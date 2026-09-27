# Lesson 36: Inheritance

> **In one sentence:** Inheritance lets a new class **reuse and extend** an existing one: a
> `Dog` *is an* `Animal`, so it gets everything an Animal has, plus its own extras.

---

## 🎯 You will learn

- Base and derived classes; the "is-a" relationship.
- `protected` members.
- `public`, `protected`, `private` inheritance.
- Bringing members back with `using`.
- Constructors, copy constructors, and destructors in inheritance chains.
- Inheriting constructors.
- Name hiding (reused names).

---

## 🧸 The Big Idea: family traits

```
            ┌────────────────┐
            │     Animal     │   has: name, age     can: eat(), sleep()
            └───────▲────────┘
          ┌─────────┴─────────┐
   ┌──────┴──────┐     ┌──────┴──────┐
   │     Dog     │     │    Bird     │
   │ + bark()    │     │ + fly()     │
   └─────────────┘     └─────────────┘
```
A Dog **is an** Animal, so it automatically has a name, an age, and can eat and sleep. It *adds* `bark()`.
You write the shared stuff **once** in `Animal`.

```cpp
class Animal {
public:
    explicit Animal(std::string name) : name{std::move(name)} {}
    void eat() const { std::cout << name << " eats\n"; }
protected:                 // visible to Animal AND its children, not to outsiders
    std::string name;
};

class Dog : public Animal {             // "Dog is-a Animal"
public:
    explicit Dog(std::string n) : Animal{std::move(n)} {}   // build the Animal part first
    void bark() const { std::cout << name << ": Woof!\n"; } // can use protected 'name'
};
```

---

## 📚 Step by step

### 1. First inheritance ([36.2](36.2FirstTryOnInheritance/main.cpp)) & `protected` ([36.3](36.3ProtectedMembers/main.cpp))
| Access | Class itself | Derived classes | Outside code |
|--------|:---:|:---:|:---:|
| `public` | ✅ | ✅ | ✅ |
| `protected` | ✅ | ✅ | ❌ |
| `private` | ✅ | ❌ | ❌ |

### 2. Inheritance access specifiers ([36.5](36.5BaseClassAccessSpecifiersADemo/main.cpp), [36.6](36.6ClosingInOnPrivateInheritance/main.cpp))
`class Dog : public Animal` keeps Animal's public things public. `protected`/`private` inheritance **downgrades** them.
`public` is by far the most common. `private` inheritance means "implemented-in-terms-of" (usually composition is clearer).

### 3. Resurrecting members with `using` ([36.7](36.7ResurectingMembersBackInContext/main.cpp))
`using Animal::eat;` in the derived class can restore access that private inheritance hid.

### 4. Constructors ([36.8](36.8DefaultArgConstructorsWithInheritance/main.cpp), [36.9](36.9ConstructorsWithInheritance/main.cpp), [36.10](36.10CopyConstructorsWithInheritance/main.cpp), [36.11](36.11InheritingBaseConstructors/main.cpp))
**Order of construction:** base first, then members, then the derived body. Like building a house:
foundation → walls → roof.
```cpp
Dog(const Dog& other) : Animal{other}, tricks{other.tricks} {}   // copy the base part too!
using Animal::Animal;   // inherit Animal's constructors (C++11)
```

### 5. Destructors ([36.12](36.12InheritanceAndDestructors/main.cpp))
**Reverse order**: derived destructor first, then base. Demolish the roof before the foundation.

### 6. Reused names ([36.13](36.13ReusedSymbolsInInheritance/main.cpp))
If Dog declares its own `eat()`, it **hides** Animal's `eat()` (all overloads!). Call the base one with `Animal::eat()`.

---

## 🗂️ Code in this folder

| Folder | What to look for |
|--------|------------------|
| [36.2FirstTryOnInheritance](36.2FirstTryOnInheritance/main.cpp) | Base + derived |
| [36.3ProtectedMembers](36.3ProtectedMembers/main.cpp) | `protected` |
| [36.5BaseClassAccessSpecifiersADemo](36.5BaseClassAccessSpecifiersADemo/main.cpp) | public/protected/private inheritance |
| [36.6ClosingInOnPrivateInheritance](36.6ClosingInOnPrivateInheritance/main.cpp) | Private inheritance chains |
| [36.7ResurectingMembersBackInContext](36.7ResurectingMembersBackInContext/main.cpp) | `using Base::member` |
| [36.8DefaultArgConstructorsWithInheritance](36.8DefaultArgConstructorsWithInheritance/main.cpp) | Default ctors in chains |
| [36.9ConstructorsWithInheritance](36.9ConstructorsWithInheritance/main.cpp) | Calling base constructors |
| [36.10CopyConstructorsWithInheritance](36.10CopyConstructorsWithInheritance/main.cpp) | Copying the base part |
| [36.11InheritingBaseConstructors](36.11InheritingBaseConstructors/main.cpp) | `using Base::Base` |
| [36.12InheritanceAndDestructors](36.12InheritanceAndDestructors/main.cpp) | Destruction order |
| [36.13ReusedSymbolsInInheritance](36.13ReusedSymbolsInInheritance/main.cpp) | Name hiding |

## ⚠️ Common mistakes

- Forgetting `public` (`class Dog : Animal` defaults to **private** inheritance for `class`).
- Writing a derived copy constructor that forgets to copy the base part.
- Making data `protected` "just in case" (derived classes can then break base invariants).
- Inheriting just to reuse code when there's no real "is-a" relationship.

## 🧠 Senior developer notes

- **Prefer composition over inheritance.** Ask: *is* a Car an Engine? No, a Car **has** an Engine, so use a member.
- The **Liskov Substitution Principle**: code using an `Animal` must work correctly with *any* derived class.
  The classic violation is a `Square` inheriting from a `Rectangle` (setting width breaks the square).
- Keep hierarchies **shallow** (1–2 levels). Deep trees become hard to change.

## ✅ Check yourself

1. In what order are base and derived constructors called? Destructors?
2. What can a derived class access: public, protected, private members of its base?
3. What is "name hiding"?

<details><summary>Answers</summary>

1. Construction: base → derived. Destruction: derived → base.
2. Public and protected, but not private.
3. A derived member with the same name hides *all* base members with that name.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 37: Polymorphism](../37.Polymorphism/README.md)
