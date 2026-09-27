#include <iostream>
#include <ranges>
#include <string>
#include <vector>

int main()
{
    namespace views = std::views;
    std::vector<std::string> words{"a", "tree", "is", "lovely", "and", "green", "!"};

    for (int x : views::iota(51) | views::filter([](int n) { return n % 7 == 0; }) | views::take(5))
        std::cout << x << ' ';
    std::cout << '\n';

    for (int x : views::iota(1, 21) | views::filter([](int n) { return n % 2 == 1; }) |
                     views::transform([](int n) { return n * n; }) | views::reverse)
        std::cout << x << ' ';
    std::cout << '\n';

    for (auto len : words | views::filter([](const std::string& w) { return w.size() > 3; }) |
                        views::transform([](const std::string& w) { return w.size(); }))
        std::cout << len << ' ';
    std::cout << '\n';

    int sum{0};
    for (int x : views::iota(1, 101) | views::filter([](int n) { return n % 3 == 0 || n % 5 == 0; })) sum += x;
    std::cout << sum << '\n';
}
