// std::format: readable, type-safe formatting (C++20)
#include <format>
#include <iostream>
#include <string>
#include <vector>

struct Item {
    std::string name;
    int qty;
    double price;
};

int main()
{
    std::cout << std::format("Hello, {}! You are {} years old.\n", "Ada", 36);
    std::cout << std::format("pi = {:.3f}, padded = [{:08.2f}]\n", 3.14159, 3.14159);
    std::cout << std::format("hex {:x}, HEX {:#X}, binary {:#b}, octal {:o}\n", 255, 255, 5, 8);
    std::cout << std::format("[{:<8}] [{:^8}] [{:>8}]\n", "left", "mid", "right");
    std::cout << std::format("[{:*^20}]\n", " title ");        // fill character *
    std::cout << std::format("{0} and {1}, then {0} again\n", "first", "second");

    const std::vector<Item> cart{{"Apples", 3, 1.2}, {"Bread", 1, 2.5}, {"Chocolate", 12, 0.99}};
    std::cout << std::format("\n{:<12}{:>5}{:>10}\n", "Item", "Qty", "Total");
    std::cout << std::string(27, '-') << '\n';
    double sum{0};
    for (const auto& [name, qty, price] : cart) {
        std::cout << std::format("{:<12}{:>5}{:>10.2f}\n", name, qty, qty * price);
        sum += qty * price;
    }
    std::cout << std::format("{:<17}{:>10.2f}\n", "TOTAL", sum);
}
