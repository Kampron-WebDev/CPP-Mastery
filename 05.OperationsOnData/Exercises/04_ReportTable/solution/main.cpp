#include <iostream>
#include <iomanip>
#include <string>

// A small helper keeps each row identical: write the formatting rules once.
void printRow(const std::string& name, int qty, double price)
{
    std::cout << std::left << std::setw(12) << name
              << std::right << std::setw(5) << qty
              << std::setw(10) << price << '\n';
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(12) << "Item"
              << std::right << std::setw(5) << "Qty" << std::setw(10) << "Price" << '\n';
    std::cout << std::string(30, '-') << '\n';

    printRow("Apples", 3, 1.20);
    printRow("Bread", 1, 2.50);
    printRow("Chocolate", 12, 0.99);

    const double total = 3 * 1.20 + 1 * 2.50 + 12 * 0.99;
    std::cout << std::string(30, '-') << '\n';
    std::cout << std::left << std::setw(17) << "Total" << std::right << std::setw(10) << total << '\n';
}
