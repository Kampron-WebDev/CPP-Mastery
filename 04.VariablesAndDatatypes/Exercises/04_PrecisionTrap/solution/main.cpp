#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    double sum{0.1 + 0.2};
    std::cout << std::setprecision(20) << "0.1 + 0.2 = " << sum << '\n';
    std::cout << std::boolalpha;
    std::cout << "sum == 0.3 ?        " << (sum == 0.3) << '\n';                    // false!
    std::cout << "|sum - 0.3| < 1e-9 ? " << (std::abs(sum - 0.3) < 1e-9) << '\n';   // true

    float f{1234567.891f};
    double d{1234567.891};
    std::cout << std::setprecision(12);
    std::cout << "float : " << f << '\n';   // float keeps only ~7 significant digits
    std::cout << "double: " << d << '\n';   // double keeps ~15
}
