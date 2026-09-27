#include <iostream>
#include "rectangle.h"

int main()
{
    Rectangle r{2, 3};
    std::cout << "area " << r.area() << ", perimeter " << r.perimeter() << '\n';
    r.scale(2).scale(1.5);   // chaining
    std::cout << "after scaling: area " << r.area() << '\n';   // 6 * 9 = 54

    Rectangle bad{-4, 5};    // width fixed to 1
    std::cout << "bad rectangle area " << bad.area() << ", square? " << std::boolalpha
              << bad.isSquare() << '\n';
}
