// ⭐⭐⭐ Exercise 02: CaseInsensitiveName
// class Name { std::string value; }  should compare IGNORING case:
//   Name{"alice"} == Name{"ALICE"}   -> true
//   Name{"Bob"}   <  Name{"alice"}   -> false  (b comes after a)
// 1. Write a custom  std::weak_ordering operator<=>(const Name&) const
//    (weak: "alice" and "ALICE" are equivalent but not identical)
// 2. Write a custom operator== (a custom <=> does NOT generate ==!)
// 3. Sort {"bob", "Alice", "carol", "ALICE", "Bob"} and print it.
#include <iostream>
#include <string>
#include <vector>
#include <compare>

int main()
{
    // TODO
}
