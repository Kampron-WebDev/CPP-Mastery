#include <iostream>

class Vec2 {
public:
    Vec2() = default;
    Vec2(double x, double y) : x{x}, y{y} {}

    Vec2& operator+=(const Vec2& r) { x += r.x; y += r.y; return *this; }
    Vec2& operator-=(const Vec2& r) { x -= r.x; y -= r.y; return *this; }
    Vec2& operator*=(double k) { x *= k; y *= k; return *this; }

    Vec2 operator-() const { return Vec2{-x, -y}; }

    friend Vec2 operator+(Vec2 l, const Vec2& r) { return l += r; }   // l is a copy: reuse +=
    friend Vec2 operator-(Vec2 l, const Vec2& r) { return l -= r; }
    friend Vec2 operator*(Vec2 v, double k) { return v *= k; }
    friend Vec2 operator*(double k, Vec2 v) { return v *= k; }        // symmetric version

    friend bool operator==(const Vec2& a, const Vec2& b) { return a.x == b.x && a.y == b.y; }
    // C++20: != is generated automatically from ==

    friend std::ostream& operator<<(std::ostream& os, const Vec2& v) { return os << '(' << v.x << ", " << v.y << ')'; }
    friend std::istream& operator>>(std::istream& is, Vec2& v) { return is >> v.x >> v.y; }

private:
    double x{0};
    double y{0};
};

int main()
{
    Vec2 a, b;
    std::cout << "Vector a (x y): ";
    std::cin >> a;
    std::cout << "Vector b (x y): ";
    std::cin >> b;

    std::cout << "a + b = " << a + b << '\n';
    std::cout << "a - b = " << a - b << '\n';
    std::cout << "2 * a = " << 2 * a << '\n';
    std::cout << "-a    = " << -a << '\n';
    std::cout << std::boolalpha << "a == b ? " << (a == b) << ", a != b ? " << (a != b) << '\n';
}
