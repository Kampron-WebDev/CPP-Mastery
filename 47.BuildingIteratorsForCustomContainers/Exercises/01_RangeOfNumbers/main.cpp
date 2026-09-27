// ⭐⭐⭐ Exercise 01: RangeOfNumbers
// Build a class NumberRange(start, stop, step) that produces numbers WITHOUT storing them
// (like Python's range). It needs an iterator class with:
//   the 5 type aliases, operator*, prefix/postfix ++, operator== (default ctor too!)
// Make all of these work:
//   for (int x : NumberRange{0, 10, 2}) ...                // 0 2 4 6 8
//   std::accumulate(r.begin(), r.end(), 0)
//   r | std::views::transform(square)                      // needs std::forward_iterator
//   static_assert(std::forward_iterator<NumberRange::Iterator>);
// Careful: with step 3 from 0 to 10, "end" must still be reached (0 3 6 9, not an infinite loop).
#include <iostream>

int main()
{
    // TODO
}
