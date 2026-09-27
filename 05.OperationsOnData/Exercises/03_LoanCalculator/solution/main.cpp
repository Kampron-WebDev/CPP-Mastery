#include <iostream>
#include <iomanip>
#include <cmath>

int main()
{
    double principal{}, ratePercent{};
    int years{};
    std::cout << "Amount, yearly rate %, years: ";
    std::cin >> principal >> ratePercent >> years;

    const double r = ratePercent / 12.0 / 100.0;
    const int n = years * 12;

    double monthly{};
    if (r == 0.0) {
        monthly = principal / n;        // edge case: no interest
    } else {
        const double growth = std::pow(1.0 + r, n);
        monthly = principal * r * growth / (growth - 1.0);
    }
    const double total = monthly * n;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Monthly: " << monthly << " | Total: " << total
              << " | Interest: " << total - principal << '\n';
}
