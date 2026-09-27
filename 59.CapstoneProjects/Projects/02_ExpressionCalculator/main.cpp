// Project 02: Expression Calculator. Read README.md for the grammar and milestones.
// Start with milestone 1: print the tokens of each line you type.
#include <iostream>
#include <string>

int main()
{
    for (std::string line; std::cout << "> " && std::getline(std::cin, line);) {
        if (line == "quit") break;
        std::cout << "TODO: evaluate '" << line << "'\n";
    }
}
