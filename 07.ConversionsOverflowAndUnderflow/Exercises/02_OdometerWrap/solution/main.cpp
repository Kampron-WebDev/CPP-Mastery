#include <iostream>
#include <cstdint>

int main()
{
    std::uint8_t trip{250};
    for (int i = 0; i < 10; ++i) {
        ++trip;                                    // 251 ... 255, 0, 1, 2, 3, 4
        std::cout << static_cast<int>(trip) << ' ';
    }
    std::cout << '\n';

    std::uint8_t small{3};
    std::uint8_t result = static_cast<std::uint8_t>(small - 5);   // -2 wraps to 254
    std::cout << "3 - 5 in uint8_t = " << static_cast<int>(result) << '\n';
}
