#include <iostream>

// Each value now has a name that explains itself, and there's one place to change it.
constexpr double discountRate{0.15};
constexpr double taxRate{0.20};
constexpr double freeShippingThreshold{50.0};
constexpr double shippingFee{3.0};

int main()
{
    const double price{120.0};
    const double discounted = price - price * discountRate;
    const double withTax = discounted + discounted * taxRate;
    const double shipping = (withTax > freeShippingThreshold) ? 0.0 : shippingFee;
    std::cout << "Final price: " << withTax + shipping << '\n';
}
