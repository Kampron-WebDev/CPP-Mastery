#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// ---- after refactoring ----
enum class Membership { None, Silver, Gold, Platinum };
enum class Shipping { Standard, Local };   // replaces the mysterious bool "f2"

constexpr double freeShippingThreshold{50.0};
constexpr double standardShippingFee{9.99};
constexpr double localShippingFee{4.99};

double discountRate(Membership level)
{
    switch (level) {
        case Membership::None:     return 0.00;
        case Membership::Silver:   return 0.05;
        case Membership::Gold:     return 0.10;
        case Membership::Platinum: return 0.20;
    }
    return 0.0;
}

double subtotal(const std::vector<double>& prices) { return std::accumulate(prices.begin(), prices.end(), 0.0); }

double shippingFee(double amount, Shipping shipping)
{
    if (amount >= freeShippingThreshold) return 0.0;
    return shipping == Shipping::Local ? localShippingFee : standardShippingFee;
}

double orderTotal(const std::vector<double>& prices, Membership level, Shipping shipping)
{
    const double discounted = subtotal(prices) * (1.0 - discountRate(level));
    return discounted + shippingFee(discounted, shipping);
}

// ---- tests (only the call sites changed) ----
int failures{0};
void check(bool ok, const char* what)
{
    if (!ok) { ++failures; std::cout << "FAIL: " << what << '\n'; }
}
bool near(double a, double b) { return a - b < 1e-9 && b - a < 1e-9; }

int main()
{
    using enum Membership;
    check(near(orderTotal({10, 20}, None, Shipping::Standard), 39.99), "no membership, standard shipping");
    check(near(orderTotal({10, 20}, None, Shipping::Local), 34.99), "no membership, local shipping");
    check(near(orderTotal({100}, Silver, Shipping::Standard), 95.0), "silver, free shipping over 50");
    check(near(orderTotal({30, 30}, Gold, Shipping::Standard), 54.0), "gold 10%");
    check(near(orderTotal({50}, Platinum, Shipping::Local), 44.99), "platinum 20% drops below 50 -> shipping added");
    check(near(orderTotal({}, None, Shipping::Standard), 9.99), "empty cart still pays shipping");
    std::cout << (failures == 0 ? "all tests pass\n" : "tests FAILED\n");
    return failures;
}
