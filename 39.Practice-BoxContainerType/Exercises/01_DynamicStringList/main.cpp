// ⭐⭐⭐ Exercise 01: DynamicStringList
// Build your OWN container class StringList that stores std::string items in a heap array.
// Without looking at 39.x, write:
//   - StringList()                          capacity 2, size 0
//   - ~StringList()                          frees memory
//   - StringList(const StringList&)          DEEP copy
//   - StringList& operator=(const StringList&)   deep copy, handles self-assignment, returns *this
//   - void add(const std::string&)           doubles the capacity when full
//   - bool removeFirst(const std::string&)   keeps the ORDER of the other items (shift left)
//   - const std::string& operator[](std::size_t) const   (throws std::out_of_range if bad index)
//   - size(), capacity(), and operator<< printing [a, b, c]
// Test: add 5 items (watch capacity 2 -> 4 -> 8), copy, modify the copy, remove, print both.
#include <iostream>
#include <string>

int main()
{
    // TODO
}
