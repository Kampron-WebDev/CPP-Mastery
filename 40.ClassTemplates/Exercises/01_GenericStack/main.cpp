// ⭐⭐ Exercise 01: GenericStack
// A stack = a pile of plates: you only add (push) and remove (pop) at the TOP. (LIFO)
// Write   template <typename T> class Stack   using a std::vector<T> member:
//   push(const T&), pop() (throws std::underflow_error when empty), top() const, empty(), size()
//   and a hidden-friend operator<< printing bottom -> top.
// Then use it to:
//   1. reverse a word ("stressed" -> "desserts") with Stack<char>
//   2. check balanced brackets: "{[()]}" ok, "([)]" not ok, "((" not ok
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // TODO
}
