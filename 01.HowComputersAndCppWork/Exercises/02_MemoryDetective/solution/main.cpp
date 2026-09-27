#include <iostream>

int main()
{
    char letter = 'Q';
    int count = 12;
    double weight = 63.5;

    std::cout << "letter: " << letter << ", " << sizeof(letter) << " byte,  at "
              << static_cast<void*>(&letter) << '\n';
    std::cout << "count : " << count << ", " << sizeof(count) << " bytes, at " << &count << '\n';
    std::cout << "weight: " << weight << ", " << sizeof(weight) << " bytes, at " << &weight << '\n';

    std::cout << "A double uses " << sizeof(weight) * 8 << " bits.\n";
}
// Answer: a double is 8 bytes = 64 bits.
