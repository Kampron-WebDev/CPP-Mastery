// ⭐ Exercise 01: FixThePercentage
// A student got 45 out of 60. This prints "Score: 0%". Why?
// Fix it using static_cast so it prints "Score: 75%".
// Then print it with one decimal for 47 out of 60 (78.3%).
#include <iostream>

int main()
{
    int correct = 45;
    int total = 60;
    int percent = correct / total * 100;   // BUG
    std::cout << "Score: " << percent << "%\n";
}
