#include <iostream>
#include <cmath>
#include <functional>
#include <map>
#include <stdexcept>

double add(double a, double b) { return a + b; }

int main()
{
    const std::map<char, std::function<double(double, double)>> ops{
        {'+', add},                                            // plain function
        {'-', [](double a, double b) { return a - b; }},       // lambda
        {'*', std::multiplies<>{}},                            // standard functor
        {'^', [](double a, double b) { return std::pow(a, b); }},
        {'/', [](double a, double b) {
             if (b == 0) throw std::domain_error{"division by zero"};
             return a / b;
         }},
    };

    std::cout << "Enter 'a op b' (q to quit)\n";
    double a{}, b{};
    char op{};
    while (std::cout << "> " && std::cin >> a >> op >> b) {
        const auto it = ops.find(op);
        if (it == ops.end()) {
            std::cout << "Unknown operator " << op << '\n';
            continue;
        }
        try {
            std::cout << it->second(a, b) << '\n';   // call whatever callable is stored
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}
