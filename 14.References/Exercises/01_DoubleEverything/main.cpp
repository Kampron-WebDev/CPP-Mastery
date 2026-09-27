// ⭐ Exercise 01: DoubleEverything
// This code tries to double every price but prints the ORIGINAL prices. Why?
// 1. Fix it with ONE character.
// 2. Add a second loop that prints the prices using the best read-only loop style.
#include <iostream>

int main()
{
    double prices[]{1.5, 2.25, 10.0};
    for (double p : prices) {
        p *= 2;
    }
    for (double p : prices) std::cout << p << ' ';
    std::cout << '\n';
}
