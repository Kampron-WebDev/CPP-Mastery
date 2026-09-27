#include <iostream>
#include <string>

void printReceipt(std::string item, double price, int qty)
{
    std::cout << "==== RECEIPT ====\n";
    std::cout << "Item    : " << item << '\n';
    std::cout << "Price   : " << price << '\n';
    std::cout << "Qty     : " << qty << '\n';
    std::cout << "Total   : " << price * qty << '\n';
    std::cout << "=================\n";
}

int main()
{
    std::string item;
    double price{};
    int qty{};

    std::cout << "Item name: ";
    std::getline(std::cin, item);
    std::cout << "Price: ";
    std::cin >> price;
    std::cout << "Quantity: ";
    std::cin >> qty;

    printReceipt(item, price, qty);
}
