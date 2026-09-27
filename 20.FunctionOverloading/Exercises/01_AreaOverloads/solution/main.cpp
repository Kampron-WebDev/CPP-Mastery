#include <iostream>
#include <cmath>
#include <numbers>
#include <string_view>

double area(double radius) { return std::numbers::pi * radius * radius; }
double area(double width, double height) { return width * height; }
double area(double a, double b, double c)
{
    const double s = (a + b + c) / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

void describe(int x) { std::cout << "int: " << x << '\n'; }
void describe(double x) { std::cout << "double: " << x << '\n'; }
void describe(std::string_view s) { std::cout << "text: " << s << '\n'; }

int main()
{
    std::cout << "circle r=1      : " << area(1.0) << '\n';
    std::cout << "rectangle 2x3   : " << area(2.0, 3.0) << '\n';
    std::cout << "triangle 3,4,5  : " << area(3.0, 4.0, 5.0) << '\n';   // 6
    describe(42);
    describe(4.2);
    describe("forty-two");
}
