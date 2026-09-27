#include <iostream>
#include "stats.h"

// Original errors: "multiple definition of `callCount'" and "multiple definition of `version()'",
// because both main.cpp and stats.cpp got their own definition from the header.
int main()
{
    std::cout << average(2, 4) << '\n';
    std::cout << average(10, 20) << '\n';
    std::cout << "calls: " << callCount << '\n';
    std::cout << version() << '\n';
}
