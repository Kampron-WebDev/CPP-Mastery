#include <iostream>
#include "geometry.h"

// Removing a definition gives "undefined reference to `triangleArea(double, double)'".
// The COMPILER is happy (it saw the declaration); the LINKER can't find the body.
int main()
{
    std::cout << "Circle r=2      : " << circleArea(2) << '\n';
    std::cout << "Rectangle 3x4   : " << rectangleArea(3, 4) << '\n';
    std::cout << "Triangle 6 by 5 : " << triangleArea(6, 5) << '\n';
}
