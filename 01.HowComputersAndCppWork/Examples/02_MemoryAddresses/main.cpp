// Every variable lives at an ADDRESS in memory (a house number on a long street).
// &name means "the address of name".
#include <iostream>

int main()
{
    int apples = 5;
    int pears = 7;
    double price = 2.5;

    std::cout << "apples = " << apples << "   lives at " << &apples << '\n';
    std::cout << "pears  = " << pears << "   lives at " << &pears << '\n';
    std::cout << "price  = " << price << " lives at " << &price << '\n';

    // Addresses are printed in hexadecimal (base 16), which is a short way of writing binary.
    // Run it twice: the addresses may change. The operating system picks the street each run.
}
