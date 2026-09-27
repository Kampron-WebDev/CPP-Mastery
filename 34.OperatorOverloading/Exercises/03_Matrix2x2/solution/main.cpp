#include <iostream>
#include <cmath>
#include <numbers>

struct Vec {
    double x;
    double y;
};

class Matrix2 {
public:
    Matrix2(double a, double b, double c, double d) : m{{a, b}, {c, d}} {}

    static Matrix2 identity() { return {1, 0, 0, 1}; }
    static Matrix2 rotation(double r) { return {std::cos(r), -std::sin(r), std::sin(r), std::cos(r)}; }

    double& operator()(int row, int col) { return m[row][col]; }
    double operator()(int row, int col) const { return m[row][col]; }

    friend Matrix2 operator*(const Matrix2& a, const Matrix2& b)
    {
        Matrix2 r{0, 0, 0, 0};
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k) r(i, j) += a(i, k) * b(k, j);
        return r;
    }

    friend Vec operator*(const Matrix2& a, const Vec& v)
    {
        return {a(0, 0) * v.x + a(0, 1) * v.y, a(1, 0) * v.x + a(1, 1) * v.y};
    }

    friend bool operator==(const Matrix2& a, const Matrix2& b)
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                if (a(i, j) != b(i, j)) return false;
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix2& a)
    {
        return os << "[" << a(0, 0) << ' ' << a(0, 1) << "]\n[" << a(1, 0) << ' ' << a(1, 1) << "]\n";
    }

private:
    double m[2][2];
};

int main()
{
    const Matrix2 quarterTurn = Matrix2::rotation(std::numbers::pi / 2);
    Vec v{1, 0};
    v = quarterTurn * (quarterTurn * v);
    std::cout << "rotated twice: (" << std::round(v.x * 1e9) / 1e9 << ", " << std::round(v.y * 1e9) / 1e9 << ")\n";

    const Matrix2 m{1, 2, 3, 4};
    std::cout << m;
    std::cout << std::boolalpha << "identity * m == m ? " << (Matrix2::identity() * m == m) << '\n';
}
