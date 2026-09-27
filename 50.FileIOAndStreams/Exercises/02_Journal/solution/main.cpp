#include <fstream>
#include <iostream>
#include <string>

const std::string journalFile{"journal.txt"};

int countEntries()
{
    std::ifstream in{journalFile};   // may not exist yet: that's fine, count is 0
    int n{0};
    for (std::string line; std::getline(in, line);) ++n;
    return n;
}

void printMatching(const std::string& word)
{
    std::ifstream in{journalFile};
    if (!in) {
        std::cout << "(journal is empty)\n";
        return;
    }
    for (std::string line; std::getline(in, line);)
        if (word.empty() || line.find(word) != std::string::npos) std::cout << line << '\n';
}

int main()
{
    int entries = countEntries();
    std::cout << "Journal has " << entries << " entries.\n";

    while (true) {
        std::cout << "\n1) write  2) read all  3) search  4) quit\n> ";
        std::string choice;
        if (!std::getline(std::cin, choice) || choice == "4") break;

        if (choice == "1") {
            std::cout << "Entry: ";
            std::string text;
            std::getline(std::cin, text);
            std::ofstream out{journalFile, std::ios::app};
            if (!out) {
                std::cerr << "Cannot write the journal\n";
                continue;
            }
            out << "[entry " << ++entries << "] " << text << '\n';
        } else if (choice == "2") {
            printMatching("");
        } else if (choice == "3") {
            std::cout << "Word: ";
            std::string word;
            std::getline(std::cin, word);
            printMatching(word);
        }
    }
}
