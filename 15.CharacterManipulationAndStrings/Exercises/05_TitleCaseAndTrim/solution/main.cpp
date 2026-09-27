#include <iostream>
#include <string>
#include <string_view>
#include <cctype>

std::string trim(std::string_view s)
{
    const auto first = s.find_first_not_of(' ');
    if (first == std::string_view::npos) return "";          // all spaces (or empty)
    const auto last = s.find_last_not_of(' ');
    return std::string{s.substr(first, last - first + 1)};
}

std::string collapseSpaces(std::string_view s)
{
    std::string out;
    for (char c : s) {
        if (c == ' ' && !out.empty() && out.back() == ' ') continue;   // skip repeated spaces
        out += c;
    }
    return out;
}

std::string titleCase(std::string_view s)
{
    std::string out;
    bool startOfWord = true;
    for (char ch : s) {
        const auto c = static_cast<unsigned char>(ch);
        out += static_cast<char>(startOfWord ? std::toupper(c) : std::tolower(c));
        startOfWord = (ch == ' ');
    }
    return out;
}

int main()
{
    std::cout << '[' << trim("   hi there  ") << "]\n";
    std::cout << '[' << collapseSpaces("a    b  c") << "]\n";
    std::cout << '[' << titleCase("the LORD of the rings") << "]\n";
    std::cout << '[' << titleCase(collapseSpaces(trim("   the   quick  BROWN fox  "))) << "]\n";
}
