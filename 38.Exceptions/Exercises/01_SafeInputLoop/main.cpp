// ⭐⭐ Exercise 01: SafeInputLoop
// Read lines with std::getline and convert them with std::stoi.
// std::stoi throws:
//   std::invalid_argument  for "abc"
//   std::out_of_range      for "99999999999999"
// Keep asking until the user enters a valid age between 0 and 130.
// Also throw YOUR OWN std::out_of_range if the number is outside 0..130, and handle it in the same way.
// Print a specific message for each kind of problem.
// Bonus: "12abc" is accepted by stoi as 12! Use the second parameter (std::size_t* pos) to reject it.
#include <iostream>
#include <string>
#include <stdexcept>

int main()
{
    // TODO
}
