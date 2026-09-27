// ⭐⭐ Exercise 03: SecondsConverter
// Read a number of seconds and print it as hours, minutes and seconds.
//   Input : 3725
//   Output: 1 h 2 min 5 s
// Tools: integer division (/) throws away the remainder; % gives the remainder.
//        7 / 2 == 3      7 % 2 == 1
#include <iostream>

int main()
{
    // TODO
    int input;

    std::cout << "Enter the number of seconds: ";
    std::cin >> input;
    int hours = input / 3600;
    int minutes = (input % 3600) / 60;
    int seconds = input % 60;

    std::cout << hours << " h " << minutes << " min " << seconds << " s" << "\n";

    return 0;

}
