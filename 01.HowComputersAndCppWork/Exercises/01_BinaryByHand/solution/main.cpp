#include <iostream>

int main()
{
    int a = 5;     // 4 + 1
    int b = 16;    // one bit in the 16 place
    int c = 255;   // 128+64+32+16+8+4+2+1

    std::cout << "a) you: " << a << "   real: " << 0b00000101 << '\n';
    std::cout << "b) you: " << b << "   real: " << 0b00010000 << '\n';
    std::cout << "c) you: " << c << "   real: " << 0b11111111 << '\n';

    std::cout << "d) 9   -> your binary is worth " << 0b00001001 << '\n'; // 8 + 1
    std::cout << "e) 100 -> your binary is worth " << 0b01100100 << '\n'; // 64 + 32 + 4
}
