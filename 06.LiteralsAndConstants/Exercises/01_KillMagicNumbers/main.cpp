// ⭐ Exercise 01: KillMagicNumbers
// This code works, but it's full of "magic numbers": nobody knows what 0.15, 3 or 50 mean.
// Refactor: create well-named constexpr constants and use them.
// The output must stay EXACTLY the same.
#include <iostream>

int main()
{
    double price{120.0};
    double discounted = price - price * 0.15;
    double withTax = discounted + discounted * 0.2;
    double shipping = (withTax > 50) ? 0 : 3;
    std::cout << "Final price: " << withTax + shipping << '\n';
}
