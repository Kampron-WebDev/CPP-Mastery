// The SAME program twice: first written badly, then cleanly. Both give identical output.
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// ======================= BEFORE: works, but... =======================
// Magic numbers, cryptic names, one function doing everything, repeated code.
void p(std::vector<std::string> n, std::vector<double> a, int t)
{
    double x = 0;
    for (int i = 0; i < (int)n.size(); i++) {
        if (t == 1) {
            if (a[i] > 100) x = x + a[i] * 0.9; else x = x + a[i];
        } else {
            if (a[i] > 100) x = x + a[i] * 0.95; else x = x + a[i];
        }
    }
    std::cout << std::fixed << std::setprecision(2) << x << "\n";
}

// ======================= AFTER: same behaviour, readable =======================
enum class Customer { Regular, Premium };

struct OrderLine {
    std::string product;
    double price;
};

constexpr double largeOrderThreshold{100.0};

double discountRate(Customer customer) { return customer == Customer::Premium ? 0.10 : 0.05; }

double priceAfterDiscount(double price, Customer customer)
{
    if (price <= largeOrderThreshold) return price;   // guard clause: small items aren't discounted
    return price * (1.0 - discountRate(customer));
}

double orderTotal(const std::vector<OrderLine>& lines, Customer customer)
{
    double total{0};
    for (const auto& line : lines) total += priceAfterDiscount(line.price, customer);
    return total;
}

int main()
{
    p({"Laptop", "Mouse"}, {1200.0, 25.0}, 1);

    const std::vector<OrderLine> order{{"Laptop", 1200.0}, {"Mouse", 25.0}};
    std::cout << std::fixed << std::setprecision(2) << orderTotal(order, Customer::Premium) << '\n';
}
