// ⭐⭐⭐ Exercise 02: RingBuffer
// A ring buffer keeps the LAST N values: when full, a new value overwrites the oldest.
// (Used for audio, logs, sensor readings, "recent files" lists.)
//   template <typename T, std::size_t N> class RingBuffer   with a std::array<T, N> inside
//     void push(const T&)       // overwrite the oldest when full
//     std::size_t size() const  // how many stored (max N)
//     T operator[](std::size_t i) const   // 0 = oldest stored value
// Add a member function   average()   that only exists for numbers: constrain it with
//     requires std::integral<T> || std::floating_point<T>
// Test: RingBuffer<int, 3>, push 1..5 -> contents 3 4 5, average 4.
//       RingBuffer<std::string, 2> works, but calling average() on it must NOT compile.
#include <iostream>
#include <array>
#include <string>

int main()
{
    // TODO
}
