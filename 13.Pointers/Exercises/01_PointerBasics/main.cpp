// ⭐ Exercise 01: PointerBasics
// Predict every output line on paper FIRST (write it in the comment), then run.
#include <iostream>

int main()
{
    int a{10};
    int b{20};
    int* p{&a};

    std::cout << *p << '\n';                  // prediction:
    *p = 15;
    std::cout << a << '\n';                   // prediction:
    p = &b;
    *p += 5;
    std::cout << a << ' ' << b << '\n';       // prediction:
    int* q{p};
    *q = *q * 2;
    std::cout << b << ' ' << *p << '\n';      // prediction:
    std::cout << (p == q) << '\n';            // prediction:
    std::cout << (p == &a) << '\n';           // prediction:
}
