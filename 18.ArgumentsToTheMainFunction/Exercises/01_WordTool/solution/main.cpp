#include <iostream>
#include <string>
#include <string_view>
#include <cctype>
#include <cstring>

void printUsage(const char* program)
{
    std::cerr << "Usage: " << program << " <upper|count|reverse|sum> <words or numbers...>\n";
}

bool looksNumeric(std::string_view s)
{
    if (s.empty()) return false;
    int dots{0};
    for (std::size_t i = 0; i < s.size(); ++i) {
        const char c = s[i];
        if (c == '-' && i == 0) continue;
        if (c == '.' && ++dots == 1) continue;
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return s != "-" && s != ".";
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }
    const std::string_view command{argv[1]};

    if (command == "upper") {
        for (int i = 2; i < argc; ++i) {
            for (const char* p = argv[i]; *p; ++p)
                std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(*p)));
            std::cout << (i + 1 < argc ? ' ' : '\n');
        }
    } else if (command == "count") {
        std::size_t letters{0};
        for (int i = 2; i < argc; ++i) letters += std::strlen(argv[i]);
        std::cout << argc - 2 << " words, " << letters << " letters\n";
    } else if (command == "reverse") {
        for (int i = argc - 1; i >= 2; --i) {
            std::string word{argv[i]};
            for (auto it = word.rbegin(); it != word.rend(); ++it) std::cout << *it;
            std::cout << (i > 2 ? ' ' : '\n');
        }
    } else if (command == "sum") {
        double total{0};
        for (int i = 2; i < argc; ++i) {
            if (!looksNumeric(argv[i])) {
                std::cerr << "Not a number: " << argv[i] << '\n';
                return 2;
            }
            total += std::stod(argv[i]);
        }
        std::cout << total << '\n';
    } else {
        printUsage(argv[0]);
        return 1;
    }
    return 0;
}
