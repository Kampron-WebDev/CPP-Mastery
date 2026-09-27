// std::variant: a value that is exactly ONE of several types, and always knows which.
#include <cmath>
#include <iostream>
#include <numbers>
#include <string>
#include <variant>
#include <vector>

struct Circle { double r; };
struct Rect { double w, h; };
struct Triangle { double a, b, c; };

using Shape = std::variant<Circle, Rect, Triangle>;

// The "overloaded" trick: combine several lambdas into one visitor object.
template <typename... Fs>
struct Overloaded : Fs... {
    using Fs::operator()...;
};

double area(const Shape& s)
{
    return std::visit(Overloaded{
                          [](const Circle& c) { return std::numbers::pi * c.r * c.r; },
                          [](const Rect& r) { return r.w * r.h; },
                          [](const Triangle& t) {
                              const double p = (t.a + t.b + t.c) / 2;
                              return std::sqrt(p * (p - t.a) * (p - t.b) * (p - t.c));
                          },
                      },
                      s);
}

int main()
{
    std::vector<Shape> shapes{Circle{1}, Rect{2, 3}, Triangle{3, 4, 5}};   // no pointers, no heap
    for (const auto& s : shapes) std::cout << "area " << area(s) << '\n';

    std::variant<int, std::string> token = 42;
    std::cout << "holds int? " << std::holds_alternative<int>(token) << '\n';
    token = std::string{"plus"};
    if (const auto* text = std::get_if<std::string>(&token)) std::cout << "now a string: " << *text << '\n';
    std::cout << "index of current type: " << token.index() << '\n';   // 1
}
