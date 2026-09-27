#include <iostream>

int main()
{
    std::cout << "I can read errors!\n";          // 1) missing ;
    std::cout << "2 + 3 = " << 2 + 3 << "\n";     // 2) cuot -> cout
    std::cout << "Done!\n";                        // 3) missing closing "
    return 0;
}
