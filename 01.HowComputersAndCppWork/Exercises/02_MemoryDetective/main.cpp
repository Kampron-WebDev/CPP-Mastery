// ⭐⭐ Exercise 02: MemoryDetective
// 1. Declare three variables: a char, an int and a double.
// 2. For each one print: its value, its size in bytes (sizeof), and its address (&).
// 3. Answer in a comment at the bottom: how many BITS does your double use?
//
// Tip: to print the address of a char, write  (void*)&myChar
//      otherwise cout thinks it's text and prints garbage letters.
#include <iostream>

int main()
{
    // TODO
    char grade {'A'};
    int score {96};
    double GPA {3.96};

    std::cout << "Value of grade: " << grade << std::endl;
    std::cout << "Sizeof grade: " << sizeof(grade) << " Byte" << std::endl;
    std::cout << "Addressof grade: " << (void*)&grade << std::endl;
    std::cout << "Value of score: " << score << std::endl;
    std::cout << "Sizeof score: " << sizeof(score) << " Bytes" << std::endl;
    std::cout << "Addressof score: " << &score << std::endl;
    std::cout << "Value of GPA: " << GPA << std::endl;
    std::cout << "Sizeof GPA: " << sizeof(GPA) << " Bytes" << std::endl;
    std::cout << "Addressof GPA: " << &GPA << std::endl;

    // My double variable GPA uses 8 bytes, that is 64 bits
    return  0;
}
