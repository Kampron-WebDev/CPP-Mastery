#include <iostream>

constexpr long long factorial(int n)
{
    long long result{1};
    for (int i = 2; i <= n; ++i) result *= i;
    return result;
}

constexpr bool isPrime(int n)
{
    if (n < 2) return false;
    for (int d = 2; d * d <= n; ++d)   // only need to test up to the square root
        if (n % d == 0) return false;
    return true;
}

static_assert(factorial(0) == 1);
static_assert(factorial(5) == 120);
static_assert(isPrime(2) && isPrime(13) && isPrime(97));
static_assert(!isPrime(1) && !isPrime(15));

int main()
{
    constexpr long long f10 = factorial(10);   // computed by the compiler
    std::cout << "10! = " << f10 << '\n';
}
