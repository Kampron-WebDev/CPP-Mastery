#include <iostream>

int main()
{
    int n{};
    std::cout << "Enter a 4-digit number: ";
    std::cin >> n;

    int thousands = n / 1000;
    int hundreds = (n / 100) % 10;
    int tens = (n / 10) % 10;
    int ones = n % 10;

    std::cout << "Thousands: " << thousands << '\n';
    std::cout << "Hundreds : " << hundreds << '\n';
    std::cout << "Tens     : " << tens << '\n';
    std::cout << "Ones     : " << ones << '\n';
    std::cout << "Sum of digits: " << thousands + hundreds + tens + ones << '\n';
    std::cout << "Reversed: " << ones * 1000 + tens * 100 + hundreds * 10 + thousands << '\n';
}
