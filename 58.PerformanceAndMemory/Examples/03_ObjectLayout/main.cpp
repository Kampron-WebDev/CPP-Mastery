// Padding: the compiler aligns members, which can waste space. Member order matters.
#include <cstddef>
#include <cstdint>
#include <iostream>

struct Wasteful {
    char a;        // 1 byte + 7 padding (so d can start at a multiple of 8)
    double d;      // 8 bytes
    char b;        // 1 byte + 3 padding
    int i;         // 4 bytes
    char c;        // 1 byte + 7 padding (total must be a multiple of 8)
};

struct Compact {   // same members, largest first
    double d;
    int i;
    char a, b, c;  // 3 bytes + 1 padding
};

int main()
{
    std::cout << "Wasteful: " << sizeof(Wasteful) << " bytes\n";   // typically 32
    std::cout << "Compact:  " << sizeof(Compact) << " bytes\n";    // typically 16
    std::cout << "offsets in Wasteful: a=" << offsetof(Wasteful, a) << " d=" << offsetof(Wasteful, d)
              << " b=" << offsetof(Wasteful, b) << " i=" << offsetof(Wasteful, i) << " c=" << offsetof(Wasteful, c) << '\n';
    std::cout << "1 million objects: " << sizeof(Wasteful) * 1'000'000 / 1024 << " KB vs "
              << sizeof(Compact) * 1'000'000 / 1024 << " KB\n";
}
