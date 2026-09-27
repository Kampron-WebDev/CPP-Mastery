#include <iostream>
#include <string>

int main()
{
    auto isEven = [](int n) { return n % 2 == 0; };
    auto clamp = [](int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); };

    std::string prefix{"Hello, "};
    auto greeter = [prefix](const std::string& name) { return prefix + name; };
    prefix = "Bye, ";   // doesn't affect greeter: it captured a copy

    int total{0};
    auto addToTotal = [&total](int x) { total += x; };

    auto counter = [n = 0]() mutable { return ++n; };

    std::cout << std::boolalpha << isEven(4) << ' ' << isEven(7) << '\n';
    std::cout << clamp(15, 0, 10) << ' ' << clamp(-3, 0, 10) << ' ' << clamp(5, 0, 10) << '\n';
    std::cout << greeter("Ada") << '\n';
    addToTotal(5);
    addToTotal(7);
    std::cout << "total = " << total << '\n';
    std::cout << counter() << ' ' << counter() << ' ' << counter() << '\n';
}
