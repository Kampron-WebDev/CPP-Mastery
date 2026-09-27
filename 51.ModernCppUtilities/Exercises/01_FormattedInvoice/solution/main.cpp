#include <cmath>
#include <format>
#include <iostream>
#include <string>
#include <vector>

struct Line {
    std::string description;
    int qty;
    double unit;
};

int main()
{
    const std::vector<Line> lines{{"Keyboard", 2, 45.00}, {"Mouse", 1, 19.99}, {"USB-C cable", 3, 7.50}};
    const std::string rule(46, '='), thin(46, '-');

    std::cout << rule << '\n' << std::format("{:^46}", std::format("INVOICE #{:04}", 42)) << '\n' << rule << '\n';
    std::cout << std::format("{:<25}{:>5}{:>8}{:>8}\n", "Description", "Qty", "Unit", "Total") << thin << '\n';

    double subtotal{0};
    for (const auto& l : lines) {
        const double total = l.qty * l.unit;
        subtotal += total;
        std::cout << std::format("{:<25}{:>5}{:>8.2f}{:>8.2f}\n", l.description, l.qty, l.unit, total);
    }
    const double vat = std::round(subtotal * 0.15 * 100) / 100;   // round to cents
    std::cout << thin << '\n';
    std::cout << std::format("{:>38}{:>8.2f}\n", "Subtotal", subtotal);
    std::cout << std::format("{:>38}{:>8.2f}\n", "VAT 15%", vat);
    std::cout << std::format("{:>38}{:>8.2f}\n", "TOTAL", subtotal + vat);
}
