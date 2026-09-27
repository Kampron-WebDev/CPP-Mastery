// The program prints its own trace table.
// Trace it on paper FIRST, then run it and compare.
#include <iostream>

int main()
{
    int total = 0;
    std::cout << "step | i | total\n";
    std::cout << "-----|---|------\n";
    for (int i = 1; i <= 4; ++i) {
        total = total + i;
        std::cout << "  " << i << "  | " << i << " | " << total << '\n';
    }
    std::cout << "Final total: " << total << '\n';
}
