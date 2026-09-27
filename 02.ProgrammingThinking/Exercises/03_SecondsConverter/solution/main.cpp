#include <iostream>

int main()
{
    int total{};
    std::cout << "Seconds: ";
    std::cin >> total;

    if (total < 0) {   // edge case
        std::cout << "Time can't be negative.\n";
        return 1;
    }

    int hours = total / 3600;           // whole hours
    int minutes = (total % 3600) / 60;  // leftover, as whole minutes
    int seconds = total % 60;           // leftover seconds

    std::cout << hours << " h " << minutes << " min " << seconds << " s\n";
}
