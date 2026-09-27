// ⭐⭐ Exercise 02: PredictTheOutput
// For each line, WRITE YOUR PREDICTION in the comment BEFORE running.
// Then run and count how many you got right. Understand every miss!
#include <iostream>

int main()
{
    int a = 10, b = 3;
    std::cout << std::boolalpha;
    std::cout << a / b << '\n';                  // prediction:
    std::cout << a % b << '\n';                  // prediction:
    std::cout << a / b * b + a % b << '\n';      // prediction:
    std::cout << 10.0 / 4 << '\n';               // prediction:
    std::cout << 2 + 3 * 4 - 6 / 2 << '\n';      // prediction:
    int c = a++;
    std::cout << c << ' ' << a << '\n';          // prediction:
    int d = --b;
    std::cout << d << ' ' << b << '\n';          // prediction:
    std::cout << (a > 5 && b < 2) << '\n';       // prediction:
    std::cout << (a > 5 || b < 2) << '\n';       // prediction:
    std::cout << !(a == 11) << '\n';             // prediction:
}
