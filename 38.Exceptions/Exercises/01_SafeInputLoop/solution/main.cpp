#include <iostream>
#include <string>
#include <stdexcept>

int parseAge(const std::string& text)
{
    std::size_t used{0};
    const int value = std::stoi(text, &used);   // may throw invalid_argument / out_of_range
    if (used != text.size()) throw std::invalid_argument{"extra characters after the number"};
    if (value < 0 || value > 130) throw std::out_of_range{"age must be between 0 and 130"};
    return value;
}

int main()
{
    std::string line;
    while (true) {
        std::cout << "Your age: ";
        if (!std::getline(std::cin, line)) return 1;
        try {
            const int age = parseAge(line);
            std::cout << "Thanks! You are " << age << ".\n";
            break;
        } catch (const std::invalid_argument&) {
            std::cout << "That's not a whole number. Try again.\n";
        } catch (const std::out_of_range&) {
            std::cout << "That number is out of range (0-130). Try again.\n";
        }
    }
}
