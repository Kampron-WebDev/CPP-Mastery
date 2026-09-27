module;
#include <numbers>

export module geometry;

export import :shapes;   // anyone who imports geometry also gets Circle and Rect

double square(double x) { return x * x; }   // NOT exported: private to the module

export double area(const Circle& c) { return std::numbers::pi * square(c.r); }
export double area(const Rect& r) { return r.w * r.h; }
