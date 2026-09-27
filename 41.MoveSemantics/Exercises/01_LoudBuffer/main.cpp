// ⭐⭐⭐ Exercise 01: LoudBuffer
// Write class LoudBuffer that owns an int array (new[]/delete[]) and implements the FULL Rule of Five.
// Each special member prints what it does:
//   "ctor", "copy ctor", "copy assign", "move ctor", "move assign", "dtor (owns N ints)"
// Then PREDICT and verify which one runs for each line:
//   LoudBuffer a{5};
//   LoudBuffer b{a};
//   LoudBuffer c{std::move(a)};
//   b = c;
//   b = LoudBuffer{3};
//   std::vector<LoudBuffer> v; v.push_back(LoudBuffer{2}); v.push_back(std::move(c));
// Bonus: remove noexcept from the move ctor. What changes when the vector grows?
#include <iostream>
#include <vector>

int main()
{
    // TODO
}
