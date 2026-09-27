// Write a file, append to it, then read it back two different ways.
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    // 1. Write (creates the file, or erases it if it exists)
    {
        std::ofstream out{"scores.txt"};
        if (!out) {
            std::cerr << "Could not create scores.txt\n";
            return 1;
        }
        out << "Ama 90\n";
        out << "Kofi 75\n";
    }   // out is closed here automatically

    // 2. Append (keeps what's already there)
    {
        std::ofstream out{"scores.txt", std::ios::app};
        out << "Esi 82\n";
    }

    // 3. Read word by word
    std::ifstream in{"scores.txt"};
    if (!in) {
        std::cerr << "Could not open scores.txt\n";
        return 1;
    }
    std::string name;
    int score{};
    int total{0}, count{0};
    while (in >> name >> score) {   // the read itself is the loop condition
        std::cout << name << " scored " << score << '\n';
        total += score;
        ++count;
    }
    std::cout << "Average: " << static_cast<double>(total) / count << "\n\n";

    // 4. Read line by line (re-open to start from the beginning)
    std::ifstream again{"scores.txt"};
    int lineNumber{1};
    for (std::string line; std::getline(again, line); ++lineNumber)
        std::cout << lineNumber << ": " << line << '\n';
}
