#include <iostream>

int main()
{
    double a{}, b{};
    char op{};
    std::cout << "Expression (e.g. 12 * 4): ";
    std::cin >> a >> op >> b;
    if (!std::cin) {
        std::cout << "Could not read that expression.\n";
        return 1;
    }

    switch (op) {
    case '+': std::cout << a + b << '\n'; break;
    case '-': std::cout << a - b << '\n'; break;
    case '*': std::cout << a * b << '\n'; break;
    case '/':
        if (b == 0) std::cout << "Error: division by zero\n";
        else        std::cout << a / b << '\n';
        break;
    case '%': {   // braces: this case declares variables
        const auto ia = static_cast<long long>(a);
        const auto ib = static_cast<long long>(b);
        if (ia != a || ib != b) std::cout << "Error: % needs whole numbers\n";
        else if (ib == 0)       std::cout << "Error: modulus by zero\n";
        else                    std::cout << ia % ib << '\n';
        break;
    }
    default:
        std::cout << "Unknown operator '" << op << "'\n";
    }
}
