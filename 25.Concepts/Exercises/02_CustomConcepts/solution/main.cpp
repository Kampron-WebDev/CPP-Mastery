#include <iostream>
#include <string>
#include <vector>
#include <concepts>
#include <numbers>

template <typename T>
concept Printable = requires(std::ostream& os, const T& value) { os << value; };

template <typename T>
concept HasSize = requires(const T& c) {
    { c.size() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept Shape = requires(const T& s) {
    { s.area() } -> std::convertible_to<double>;
    { s.name() } -> std::convertible_to<std::string>;
};

void printAll(const Printable auto&... values)
{
    ((std::cout << values << ' '), ...);   // fold expression: repeat for every argument
    std::cout << '\n';
}

void reportSize(const HasSize auto& c) { std::cout << "size = " << c.size() << '\n'; }

void printShape(const Shape auto& s) { std::cout << s.name() << " with area " << s.area() << '\n'; }

struct Circle {
    double r;
    double area() const { return std::numbers::pi * r * r; }
    std::string name() const { return "Circle"; }
};

struct Square {
    double side;
    double area() const { return side * side; }
    std::string name() const { return "Square"; }
};

int main()
{
    printAll(1, 2.5, "three", 'x', std::string{"five"});
    reportSize(std::string{"hello"});
    reportSize(std::vector<int>{1, 2, 3});
    printShape(Circle{1.0});
    printShape(Square{3.0});
    // printShape(42);   // error: int does not satisfy Shape
}
