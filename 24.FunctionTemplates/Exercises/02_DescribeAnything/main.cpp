// ⭐⭐⭐ Exercise 02: DescribeAnything
// Write   template <typename T> void describe(const T& value)
// Using if constexpr + <type_traits>, print:
//   bool      -> "bool: true"          (check this BEFORE integral: bool is integral!)
//   integral  -> "integer of N bytes: value"
//   floating  -> "decimal: value"
//   pointer   -> "pointer to something at <address>" (and if it's nullptr, say so)
//   std::string -> "text of length N: value"      (std::is_same_v)
//   anything else -> "unknown type"
// Test with: true, 42, 'x', 3.14f, 2.5, &someInt, nullptr int*, std::string, and a struct.
#include <iostream>
#include <string>
#include <type_traits>

int main()
{
    // TODO
}
