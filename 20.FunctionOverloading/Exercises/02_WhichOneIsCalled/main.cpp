// ⭐⭐ Exercise 02: WhichOneIsCalled
// Predict which overload each call uses (write A, B, C, D or "error" in the comment).
// Then run it. For any "error" line, keep it commented and explain why.
#include <iostream>

void f(int)            { std::cout << "A f(int)\n"; }
void f(double)         { std::cout << "B f(double)\n"; }
void f(int&)           { std::cout << "C f(int&)\n"; }   // careful with this one!
void g(const int&)     { std::cout << "D g(const int&)\n"; }
void g(int&)           { std::cout << "E g(int&)\n"; }

int main()
{
    // int x{5};
    // f(x);          // prediction:
    // f(5);          // prediction:
    // f(5.0);        // prediction:
    // f('a');        // prediction:
    // g(x);          // prediction:
    // g(5);          // prediction:
    // const int c{1};
    // g(c);          // prediction:
    std::cout << "Uncomment lines one by one.\n";
}
