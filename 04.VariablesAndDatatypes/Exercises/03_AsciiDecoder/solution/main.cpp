#include <iostream>

int main()
{
    // Part 1
    std::cout << static_cast<char>(72) << static_cast<char>(101) << static_cast<char>(108)
              << static_cast<char>(108) << static_cast<char>(111) << '\n';   // Hello

    // Part 2
    char letter{};
    std::cout << "Type a character: ";
    std::cin >> letter;

    int code{static_cast<int>(letter)};
    char next{static_cast<char>(letter + 1)};
    std::cout << "'" << letter << "' has code " << code << ", next is '" << next << "'\n";
}
