// How many bytes does each kind of value use on THIS computer?
// sizeof(x) answers "how many bytes (houses on the street) does x need?"
#include <iostream>

int main()
{
    std::cout << "char        : " << sizeof(char) << " byte\n";
    std::cout << "bool        : " << sizeof(bool) << " byte\n";
    std::cout << "short       : " << sizeof(short) << " bytes\n";
    std::cout << "int         : " << sizeof(int) << " bytes\n";
    std::cout << "long long   : " << sizeof(long long) << " bytes\n";
    std::cout << "float       : " << sizeof(float) << " bytes\n";
    std::cout << "double      : " << sizeof(double) << " bytes\n";
    std::cout << "a pointer   : " << sizeof(int*) << " bytes (an address)\n";

    // 1 byte = 8 bits, so an int of 4 bytes has 32 switches.
    std::cout << "\nAn int has " << sizeof(int) * 8 << " bits.\n";
}
