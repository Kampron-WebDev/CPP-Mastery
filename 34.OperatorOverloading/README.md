# Lesson 34: Operator Overloading

> **In one sentence:** Operator overloading teaches C++ what `+`, `==`, `[]`, `<<` and friends
> should *mean* for **your own types**, so `a + b` works for vectors, money, or fractions.

---

## 🎯 You will learn

- `operator+` as a member and as a non-member.
- Subscript `operator[]` (read and write).
- Stream insertion `<<` and extraction `>>`.
- Other arithmetic and compound operators (`+=` …), and reusing one to implement another.
- Custom type conversions (`operator double()`), and implicit conversion pitfalls.
- `++`/`--` in prefix and postfix forms.
- Copy assignment `operator=`.
- Functors (`operator()`).

---

## 🧸 The Big Idea: teaching new tricks

`+` already knows how to add numbers. But if you make a `Money` type, C++ has no idea what
`wallet + price` means. Operator overloading is you **teaching** it:

```cpp
struct Money { long long cents; };

Money operator+(Money a, Money b) { return Money{a.cents + b.cents}; }

Money total = Money{250} + Money{199};   // now works: 449 cents
```
An operator is just a **function with a funny name**: `a + b` is really `operator+(a, b)`.

---

## 📚 Step by step

### 1. Member vs non-member ([34.2](34.2AdditionOperatorAsMember/main.cpp), [34.3](34.3AdditionOperatorAsNonMember/main.cpp))
```cpp
Point Point::operator+(const Point& rhs) const;          // member: left side must be a Point
Point operator+(const Point& lhs, const Point& rhs);     // non-member: symmetric
```
**Rule of thumb:** symmetric binary operators (`+ - * == <`) as **non-members** (often hidden friends);
operators that modify the object (`+= = [] ++`) as **members**.

### 2. Subscript `[]` ([34.4](34.4SubscriptOperatorReading/main.cpp)–[34.6](34.6SubscriptOperatorForCollectionTypes/main.cpp))
```cpp
double& operator[](std::size_t i) { return data[i]; }              // read & write
const double& operator[](std::size_t i) const { return data[i]; }  // read-only on const objects
```

### 3. Streams ([34.7](34.7StreamInsertionOperator/main.cpp), [34.8](34.8StreamExtractionOperator/main.cpp))
```cpp
friend std::ostream& operator<<(std::ostream& os, const Point& p) { return os << '(' << p.x << ", " << p.y << ')'; }
friend std::istream& operator>>(std::istream& is, Point& p)       { return is >> p.x >> p.y; }
```
Returning the stream enables chaining: `std::cout << a << b;`

### 4. Arithmetic & compound, reusing operators ([34.9](34.9OtherArithmeticOperators/main.cpp), [34.10](34.10CompoundOperators_ReusingOperators/main.cpp))
Write `+=` as the "real" one, then build `+` from it:
```cpp
Point& operator+=(const Point& rhs) { x += rhs.x; y += rhs.y; return *this; }
friend Point operator+(Point lhs, const Point& rhs) { lhs += rhs; return lhs; }
```

### 5. Conversions ([34.11](34.11CustomTypeConversions/main.cpp), [34.12](34.12ImplicitConversionsWithOverloadedBinaryOperators/main.cpp), [34.19](34.19TypeConversionsRecap/main.cpp))
`explicit operator double() const { return num / (double)den; }` → `static_cast<double>(fraction)`.
Make conversions `explicit` unless they're truly natural.

### 6. Increment/decrement ([34.13](34.13UnaryPrefixIncrementOperatorAsMember/main.cpp)–[34.16](34.16UnaryPrefixPostfixDecrementOperator/main.cpp))
```cpp
Counter& operator++()    { ++value; return *this; }                     // prefix ++c
Counter  operator++(int) { Counter old = *this; ++*this; return old; }  // postfix c++ (dummy int)
```
Postfix must make a copy, which is why `++i` is preferred.

### 7. Copy assignment ([34.17](34.17CopyAssignmentOperator/main.cpp), [34.18](34.18CopyAssignmentOperatorForOtherTypes/main.cpp))
Copy **constructor** = making a new object as a copy. Copy **assignment** = overwriting an *existing* object.
```cpp
Buffer& operator=(const Buffer& other)
{
    if (this == &other) return *this;   // self-assignment guard: a = a;
    // free old resources, copy new ones...
    return *this;
}
```
Lesson 52 shows the safer **copy-and-swap** idiom.

### 8. Functors ([34.20](34.20Functors/main.cpp))
A class with `operator()` can be *called like a function* and can keep state. Lesson 42 goes deeper.

### Operators you can't/shouldn't overload
Can't: `::` `.` `.*` `?:` `sizeof`. Shouldn't: `&&`, `||`, `,` (they lose short-circuit/order guarantees).

---

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [34.2](34.2AdditionOperatorAsMember/main.cpp), [34.3](34.3AdditionOperatorAsNonMember/main.cpp) | `+` member vs non-member |
| [34.4](34.4SubscriptOperatorReading/main.cpp), [34.5](34.5SubscriptOperatorReadingWritting/main.cpp), [34.6](34.6SubscriptOperatorForCollectionTypes/main.cpp) | `[]` |
| [34.7](34.7StreamInsertionOperator/main.cpp), [34.8](34.8StreamExtractionOperator/main.cpp) | `<<`, `>>` |
| [34.9](34.9OtherArithmeticOperators/main.cpp), [34.10](34.10CompoundOperators_ReusingOperators/main.cpp) | Arithmetic + compound |
| [34.11](34.11CustomTypeConversions/main.cpp), [34.12](34.12ImplicitConversionsWithOverloadedBinaryOperators/main.cpp), [34.19](34.19TypeConversionsRecap/main.cpp) | Conversions |
| [34.13](34.13UnaryPrefixIncrementOperatorAsMember/main.cpp)–[34.16](34.16UnaryPrefixPostfixDecrementOperator/main.cpp) | `++` / `--` |
| [34.17](34.17CopyAssignmentOperator/main.cpp), [34.18](34.18CopyAssignmentOperatorForOtherTypes/main.cpp) | `operator=` |
| [34.20Functors](34.20Functors/main.cpp) | `operator()` |

## ⚠️ Common mistakes

- Surprising meanings (`+` that subtracts, `<<` that deletes files). Operators must behave **as users expect**.
- Returning by value from `+=` or `=` (should return `*this` by reference).
- Missing const overload of `operator[]`.
- Forgetting the self-assignment case in `operator=`.

## 🧠 Senior developer notes

- If a type needs a user-written `operator=`, it probably needs the full **Rule of Five** (Lesson 52), or better, the **Rule of Zero**.
- Implement `==` and `<=>` with C++20 defaults where possible (Lesson 35): less code, fewer bugs.
- Keep operators consistent: if `a + b` works, `a += b` should too, and `a == b` should agree with `!(a != b)`.

## ✅ Check yourself

1. Why is `operator<<` usually a non-member?
2. How does the compiler tell prefix `++` from postfix `++`?
3. What should `operator+=` return?
4. Difference between copy constructor and copy assignment?

<details><summary>Answers</summary>

1. Its left operand is `std::ostream`, which isn't your class.
2. Postfix takes a dummy `int` parameter.
3. `*this` by reference (`T&`).
4. The constructor creates a new object; assignment overwrites an existing one (and must release old resources).
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 35: Logical Operators and Three-Way Comparison](../35.LogicalOperatorsAndThreeWayComparison/README.md)
