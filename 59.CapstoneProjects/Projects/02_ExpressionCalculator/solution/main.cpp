// Expression Calculator: reference solution.
// Run with the argument "--test" (see Lesson 18) to run the automated tests instead of the prompt.
#include <cmath>
#include <iostream>
#include <string>
#include <string_view>

#include "calculator.h"

namespace {

int runTests()
{
    struct Case {
        std::string_view input;
        double expected;
    };
    const Case ok[]{{"2 + 3 * 4", 14}, {"(2 + 3) * 4", 20}, {"10 - 4 - 3", 3}, {"2 ^ 3 ^ 2", 512},
                    {"-3 + 5", 2}, {"-(2 + 3)", -5}, {"7 % 3", 1}, {"1.5 * 4", 6}, {"sqrt(16) + abs(-2)", 6},
                    {"x = 5", 5}, {"y = x ^ 2 - 1", 24}, {"-(x + y) / 2", -14.5}, {"ans * 2", -29}};
    const std::string_view errors[]{"10 / (5 - 5)", "3 + * 4", "(1 + 2", "foo + 1", "2 $ 3", "nosuch(1)", "1.2.3", ""};

    Calculator calc;
    int failures = 0;
    for (const auto& [input, expected] : ok) {
        try {
            const double got = calc.evaluate(input);
            if (std::abs(got - expected) > 1e-9) {
                ++failures;
                std::cout << "FAIL " << input << " = " << got << ", expected " << expected << '\n';
            }
        } catch (const std::exception& e) {
            ++failures;
            std::cout << "FAIL " << input << " threw: " << e.what() << '\n';
        }
    }
    for (std::string_view input : errors) {
        try {
            calc.evaluate(input);
            ++failures;
            std::cout << "FAIL '" << input << "' should have been an error\n";
        } catch (const ParseError&) {
        }
    }
    std::cout << (failures == 0 ? "all tests passed\n" : "some tests failed\n");
    return failures;
}

}  // namespace

int main(int argc, char* argv[])
{
    if (argc > 1 && std::string_view{argv[1]} == "--test") return runTests();

    Calculator calc;
    std::cout << "Calculator: + - * / % ^ ( ), variables (x = 2), sqrt abs sin cos ln, pi e ans. 'quit' to exit.\n";
    for (std::string line; std::cout << "> " && std::getline(std::cin, line);) {
        if (line == "quit" || line == "exit") break;
        if (line.find_first_not_of(' ') == std::string::npos) continue;
        try {
            std::string assigned;
            const double value = calc.evaluate(line, &assigned);
            if (!assigned.empty()) std::cout << assigned << " = ";
            std::cout << value << '\n';
        } catch (const ParseError& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }
}
