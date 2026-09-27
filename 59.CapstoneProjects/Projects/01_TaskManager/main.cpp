// Project 01: Task Manager CLI. Read README.md for the full spec and milestones.
// Start with milestone 1. Add task.h / task.cpp files in this folder when you get to milestone 5
// (Ctrl+Shift+B compiles every .cpp in the folder).
#include <iostream>
#include <string>

int main()
{
    std::cout << "Task Manager (type 'help')\n";
    for (std::string line; std::cout << "> " && std::getline(std::cin, line);) {
        if (line == "quit") break;
        std::cout << "TODO: handle '" << line << "'\n";
    }
}
