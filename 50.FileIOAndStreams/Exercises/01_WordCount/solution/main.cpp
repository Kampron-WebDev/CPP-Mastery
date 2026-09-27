#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main()
{
    std::string fileName;
    std::cout << "File name: ";
    std::getline(std::cin, fileName);

    std::ifstream in{fileName};
    if (!in) {
        std::cerr << "Error: cannot open '" << fileName << "'\n";
        return 1;
    }

    std::size_t lines{0}, words{0}, chars{0};
    std::string longest;
    for (std::string line; std::getline(in, line);) {
        ++lines;
        chars += line.size() + 1;   // +1 for the newline getline removed
        std::istringstream stream{line};
        for (std::string w; stream >> w;) ++words;
        if (line.size() > longest.size()) longest = line;
    }

    std::cout << "lines: " << lines << "\nwords: " << words << "\nchars: " << chars
              << "\nlongest line: \"" << longest << "\"\n";
}
