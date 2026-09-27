#include <iostream>

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main()
{
    for (int year : {2000, 1900, 2024, 2023, 2100}) {
        std::cout << year << " -> " << (isLeapYear(year) ? "leap" : "not leap") << '\n';
    }
}
