#include <iostream>
#include <string_view>

int sumDigits(int n)
{
    if (n < 10) return n;                  // base: single digit
    return n % 10 + sumDigits(n / 10);     // last digit + the rest
}

int power(int base, int exp)
{
    if (exp == 0) return 1;
    return base * power(base, exp - 1);
}

bool isPalindrome(std::string_view s)
{
    if (s.size() <= 1) return true;
    if (s.front() != s.back()) return false;
    return isPalindrome(s.substr(1, s.size() - 2));   // strip both ends (string_view: no copying!)
}

void countdown(int n)
{
    if (n == 0) {
        std::cout << "Liftoff!\n";
        return;
    }
    std::cout << n << ' ';
    countdown(n - 1);
}

int gcd(int a, int b)
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main()
{
    std::cout << sumDigits(1234) << ' ' << power(2, 10) << ' ' << std::boolalpha
              << isPalindrome("level") << ' ' << isPalindrome("levels") << ' ' << gcd(48, 18) << '\n';
    countdown(3);
}
