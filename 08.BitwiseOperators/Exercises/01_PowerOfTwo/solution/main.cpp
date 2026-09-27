#include <iostream>
#include <bitset>
#include <bit>   // C++20: std::popcount, to double-check our loop

int main()
{
    unsigned int x{};
    std::cout << "Number: ";
    std::cin >> x;

    const bool isOdd = (x & 1u) == 1u;
    const bool isPowerOfTwo = x != 0 && (x & (x - 1)) == 0;   // one single 1-bit

    int ones{0};
    for (unsigned int v = x; v != 0; v >>= 1)
        ones += static_cast<int>(v & 1u);

    std::cout << std::boolalpha << std::bitset<32>(x)
              << " | odd: " << isOdd
              << " | power of two: " << isPowerOfTwo
              << " | ones: " << ones << " (std::popcount says " << std::popcount(x) << ")\n";
}
