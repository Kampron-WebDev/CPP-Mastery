#include <iostream>
#include <limits>

bool safeAdd(int a, int b, int& result)
{
    constexpr int maxInt = std::numeric_limits<int>::max();
    constexpr int minInt = std::numeric_limits<int>::min();

    // Check using subtraction, which can't overflow in these branches.
    if (b > 0 && a > maxInt - b) return false;   // would go above max
    if (b < 0 && a < minInt - b) return false;   // would go below min
    result = a + b;
    return true;
}

void test(int a, int b)
{
    int r{};
    if (safeAdd(a, b, r))
        std::cout << a << " + " << b << " = " << r << '\n';
    else
        std::cout << a << " + " << b << " would overflow!\n";
}

int main()
{
    constexpr int maxInt = std::numeric_limits<int>::max();
    constexpr int minInt = std::numeric_limits<int>::min();
    test(5, 7);
    test(maxInt, 1);
    test(minInt, -1);
    test(maxInt, -5);
}
