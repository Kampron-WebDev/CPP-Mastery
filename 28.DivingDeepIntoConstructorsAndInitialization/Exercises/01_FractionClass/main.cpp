// ⭐⭐ Exercise 01: FractionClass
// class Fraction { int num; int den; }  with the INVARIANT:
//   - den is never 0 (if given 0, use 1 and print a warning)
//   - den is always positive (move the sign to num)
//   - always stored in lowest terms (6/8 -> 3/4) using std::gcd from <numeric>
// Constructors:
//   Fraction()                      -> 0/1     (delegate!)
//   explicit Fraction(int whole)    -> whole/1 (delegate!)
//   Fraction(int num, int den)      -> the main one that enforces the invariant
// Member functions: print(), toDouble(), Fraction plus(const Fraction& other) const
#include <iostream>

int main()
{
    // TODO: test 6/8, 3/-9, 5/0, Fraction{}, Fraction{7}, 1/2 plus 1/3 = 5/6
}
