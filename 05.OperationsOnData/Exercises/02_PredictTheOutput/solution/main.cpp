#include <iostream>

int main()
{
    int a = 10, b = 3;
    std::cout << std::boolalpha;
    std::cout << a / b << '\n';                  // 3   (integer division)
    std::cout << a % b << '\n';                  // 1
    std::cout << a / b * b + a % b << '\n';      // 10  (3*3 + 1: always gives back a)
    std::cout << 10.0 / 4 << '\n';               // 2.5 (one double makes it decimal)
    std::cout << 2 + 3 * 4 - 6 / 2 << '\n';      // 11  (2 + 12 - 3)
    int c = a++;
    std::cout << c << ' ' << a << '\n';          // 10 11
    int d = --b;
    std::cout << d << ' ' << b << '\n';          // 2 2
    std::cout << (a > 5 && b < 2) << '\n';       // false (b is 2)
    std::cout << (a > 5 || b < 2) << '\n';       // true
    std::cout << !(a == 11) << '\n';             // false
}
