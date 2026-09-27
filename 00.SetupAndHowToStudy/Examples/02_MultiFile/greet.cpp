#include "greet.h"
#include <iostream>

// The DEFINITION: the actual body of greet.
void greet(const std::string& name)
{
    std::cout << "Hello, " << name << "! (printed from greet.cpp)\n";
}
