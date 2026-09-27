// ⭐⭐⭐ Exercise 03: SafeAdd
// Write   bool safeAdd(int a, int b, int& result)
//   - if a + b fits in an int: store it in result and return true
//   - if it would overflow/underflow: DON'T add (that's UB!), return false
// Test it with:
//   safeAdd(5, 7, r)                        -> true, 12
//   safeAdd(INT_MAX, 1, r)                  -> false
//   safeAdd(INT_MIN, -1, r)                 -> false
//   safeAdd(INT_MAX, -5, r)                 -> true
// Use std::numeric_limits<int>::max() / min() from <limits>.
// (int& result means "result is a reference": changes go back to the caller. Lesson 14.)
#include <iostream>
#include <limits>

// TODO: safeAdd

int main()
{
    // TODO: tests
}
