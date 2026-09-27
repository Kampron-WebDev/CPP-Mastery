#include <iostream>

class Vec2 {
public:
    Vec2(double x, double y) : x{x}, y{y} {}

    // Hidden friend: defined inside the class, found when a Vec2 is involved.
    friend std::ostream& operator<<(std::ostream& os, const Vec2& v)
    {
        return os << '(' << v.x << ", " << v.y << ')';
    }

    friend double dot(const Vec2& a, const Vec2& b);
    friend class VecInspector;

private:
    double x;
    double y;
};

double dot(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }

class VecInspector {
public:
    static void inspect(const Vec2& v) { std::cout << "x=" << v.x << " y=" << v.y << '\n'; }
};

int main()
{
    Vec2 a{3, 4}, b{1, 2};
    std::cout << a << '\n';
    std::cout << "dot = " << dot(a, b) << '\n';   // 11
    VecInspector::inspect(a);
}
