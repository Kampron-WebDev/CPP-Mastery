// Input -> Process -> Output : the shape of almost every program.
#include <iostream>

int main()
{
    // INPUT
    double m1{}, m2{}, m3{};
    std::cout << "Enter three marks separated by spaces: ";
    std::cin >> m1 >> m2 >> m3;

    // PROCESS
    double total = m1 + m2 + m3;
    double average = total / 3;

    // OUTPUT
    std::cout << "Total   : " << total << '\n';
    std::cout << "Average : " << average << '\n';
}
