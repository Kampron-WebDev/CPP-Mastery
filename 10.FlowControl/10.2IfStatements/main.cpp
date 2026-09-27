// 10.2 If statements (this example was missing from the original source, so it was added for the rebuild)
// Press Ctrl+Shift+B, then try different numbers to see each path of the program run.
#include <iostream>

int main()
{
    int number1{55};
    int number2{60};

    bool result = (number1 < number2);   // a condition is just a bool value
    std::cout << std::boolalpha << "number1 < number2 : " << result << '\n';

    // 1. A plain if: the block runs only when the condition is true
    if (result) {
        std::cout << number1 << " is less than " << number2 << '\n';
    }

    // 2. You can put the comparison straight into the if
    if (!(number1 < number2)) {
        std::cout << number1 << " is NOT less than " << number2 << '\n';   // skipped this time
    }

    // 3. if / else: exactly ONE of the two blocks runs
    if (number1 < number2) {
        std::cout << "Taking the 'if' path\n";
    } else {
        std::cout << "Taking the 'else' path\n";
    }

    // 4. Nested ifs: a decision inside a decision
    bool red{false};
    bool green{true};
    bool yellow{false};
    bool policeStop{true};

    std::cout << "\nTraffic light:\n";
    if (red) {
        std::cout << "Stop\n";
    }
    if (yellow) {
        std::cout << "Slow down\n";
    }
    if (green) {
        if (policeStop) {   // only checked when the light is green
            std::cout << "Green, but the police officer says STOP\n";
        } else {
            std::cout << "Go\n";
        }
    }

    // 5. The same logic with && (and). Often clearer than nesting.
    if (green && !policeStop) {
        std::cout << "Go (checked with &&)\n";
    }
    if (green && policeStop) {
        std::cout << "Stop (checked with &&)\n";
    }

    // 6. Reading input and deciding
    int age{};
    std::cout << "\nHow old are you? ";
    std::cin >> age;
    if (!std::cin) {
        std::cout << "That wasn't a number.\n";
        return 1;
    }
    if (age >= 18) {
        std::cout << "You can vote.\n";
    } else {
        std::cout << "You can vote in " << 18 - age << " year(s).\n";
    }
    return 0;
}
