// ⭐⭐⭐ Exercise 02: CustomConcepts
// Write these concepts:
//   Printable<T>   : std::cout << value compiles
//   HasSize<T>     : value.size() compiles and returns something convertible to std::size_t
//   Shape<T>       : value.area() returns something convertible to double
//                    AND value.name() returns something convertible to std::string
// Then write:
//   void printAll(const Printable auto&... values)   (a "fold expression": (std::cout << ... << values))
//   void reportSize(const HasSize auto& c)
//   void printShape(const Shape auto& s)
// Create structs Circle and Square with area() and name() and test everything.
#include <iostream>
#include <string>
#include <vector>
#include <concepts>

int main()
{
    // TODO
}
