#include <iostream>
#include <concepts>

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

template <typename T>
concept WholeNumber = std::integral<T> && !std::same_as<T, bool>;

double average(Number auto a, Number auto b)
{
    return (static_cast<double>(a) + static_cast<double>(b)) / 2.0;
}

bool isEven(WholeNumber auto n) { return n % 2 == 0; }

int main()
{
    std::cout << average(3, 4) << ' ' << average(2.5, 10) << ' ' << average('a', 1L) << '\n';
    std::cout << std::boolalpha << isEven(10) << ' ' << isEven(7LL) << '\n';
    // average("a", "b");   // error: const char* does not satisfy Number
    // isEven(2.5);         // error: double does not satisfy WholeNumber
    // isEven(true);        // error: bool is excluded
}
