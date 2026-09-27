// ⭐ Exercise 01: BinaryByHand
// Work these out on PAPER first, then fill in the answers and run.
//
//   a) 00000101 = ?        b) 00010000 = ?        c) 11111111 = ?
//   d) Write 9 in binary (8 bits)                 e) Write 100 in binary (8 bits)
//
// C++ lets you write binary directly with the 0b prefix, e.g. 0b0101.
// The program prints YOUR answer next to the real value so you can check yourself.
#include <iostream>

int main()
{
    int a = 5;   // TODO: your answer for 00000101
    int b = 16;   // TODO: your answer for 00010000
    int c = 255;   // TODO: your answer for 11111111

    std::cout << "a) you: " << a << "   real: " << 0b00000101 << '\n';
    std::cout << "b) you: " << b << "   real: " << 0b00010000 << '\n';
    std::cout << "c) you: " << c << "   real: " << 0b11111111 << '\n';

    // d) and e): replace 0b0 with your binary answers
    std::cout << "d) 9   -> your binary is worth " << 0b00001001 << '\n';
    std::cout << "e) 100 -> your binary is worth " << 0b01100100 << '\n';
}
