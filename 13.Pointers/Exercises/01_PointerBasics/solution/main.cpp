#include <iostream>

int main()
{
    int a{10};
    int b{20};
    int* p{&a};

    std::cout << *p << '\n';                  // 10 (p points at a)
    *p = 15;
    std::cout << a << '\n';                   // 15 (changed a through p)
    p = &b;
    *p += 5;
    std::cout << a << ' ' << b << '\n';       // 15 25
    int* q{p};                                // q points where p points: at b
    *q = *q * 2;
    std::cout << b << ' ' << *p << '\n';      // 50 50
    std::cout << (p == q) << '\n';            // 1 (same address)
    std::cout << (p == &a) << '\n';           // 0
}
