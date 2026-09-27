#include <iostream>

void f(int)            { std::cout << "A f(int)\n"; }
void f(double)         { std::cout << "B f(double)\n"; }
void f(int&)           { std::cout << "C f(int&)\n"; }
void g(const int&)     { std::cout << "D g(const int&)\n"; }
void g(int&)           { std::cout << "E g(int&)\n"; }

int main()
{
    int x{5};
    // f(x);   // ERROR: ambiguous. f(int) and f(int&) are equally good matches for an int variable.
    f(5);      // A: a temporary (rvalue) can't bind to int&, so f(int) wins
    f(5.0);    // B: exact match
    f('a');    // A: char -> int is a promotion (better than char -> double conversion)
    g(x);      // E: non-const variable prefers the non-const reference
    g(5);      // D: a temporary can only bind to const int&
    const int c{1};
    g(c);      // D: a const variable can't bind to int&
    (void)x;
}
