#include <iostream>
#include <string>

int main()
{
    int age{};
    std::cout << "How old are you? ";
    std::cin >> age;

    std::string fullName;
    std::cout << "What is your full name? ";
    std::cin >> std::ws;              // skip the leftover Enter key
    std::getline(std::cin, fullName); // read the whole line, spaces included

    std::cout << "Hello, " << fullName << "!\n";
    std::cout << "Next year you will be " << age + 1 << ".\n";
}
