#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string line;
    std::cout << "Text: ";
    std::getline(std::cin, line);

    int letters{}, digits{}, spaces{}, punct{}, upper{}, vowels{};
    std::string caps;
    for (char ch : line) {
        const auto c = static_cast<unsigned char>(ch);   // cctype needs non-negative values
        if (std::isalpha(c)) ++letters;
        if (std::isdigit(c)) ++digits;
        if (std::isspace(c)) ++spaces;
        if (std::ispunct(c)) ++punct;
        if (std::isupper(c)) ++upper;
        const char lower = static_cast<char>(std::tolower(c));
        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') ++vowels;
        caps += static_cast<char>(std::toupper(c));
    }

    std::cout << "Letters: " << letters << "\nDigits: " << digits << "\nSpaces: " << spaces
              << "\nPunctuation: " << punct << "\nUppercase: " << upper << "\nVowels: " << vowels
              << "\nCAPS: " << caps << '\n';
}
