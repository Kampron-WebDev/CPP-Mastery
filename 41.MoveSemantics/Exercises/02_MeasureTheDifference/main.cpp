// ⭐⭐ Exercise 02: MeasureTheDifference
// Make a std::vector<std::string> with 200'000 strings of 100 chars each.
// Time (with <chrono>) how long it takes to:
//   1. COPY it into another vector:         auto b = a;
//   2. MOVE it into another vector:         auto c = std::move(a);
// Print both times in microseconds. Build with the "Optimized -O2" task for fair numbers.
// Then print a.size() after the move. What do you see, and why is that allowed?
//   Timing recipe:
//     auto start = std::chrono::steady_clock::now();
//     ... work ...
//     auto us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
#include <iostream>
#include <chrono>
#include <string>
#include <vector>

int main()
{
    // TODO
}
