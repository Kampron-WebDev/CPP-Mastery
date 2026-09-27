#include <iostream>

int main()
{
    double celsius{};
    std::cout << "Temperature in Celsius: ";
    std::cin >> celsius;

    double fahrenheit{celsius * 9.0 / 5.0 + 32.0};   // 9.0 forces decimal maths
    double kelvin{celsius + 273.15};

    std::cout << celsius << " C = " << fahrenheit << " F = " << kelvin << " K\n";
}
