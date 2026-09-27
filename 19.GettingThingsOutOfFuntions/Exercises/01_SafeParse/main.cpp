// ⭐⭐ Exercise 01: SafeParse
// Write   std::optional<int> parseInt(std::string_view text)
//   - returns the number for "42", "-7", "0"
//   - returns std::nullopt for "", "abc", "12x", "-", "3.5"
// Do it by hand (loop over the characters, build the number: value = value * 10 + digit).
// Then test it on all the examples and print "42 -> 42" or "abc -> invalid".
// Bonus: return nullopt when the number would overflow an int.
#include <iostream>
#include <optional>
#include <string_view>

int main()
{
    // TODO
}
