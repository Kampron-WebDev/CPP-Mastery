#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>

template <typename Work>
long long microseconds(Work work)
{
    const auto start = std::chrono::steady_clock::now();
    work();
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
}

int main()
{
    std::vector<std::string> a(200'000, std::string(100, 'x'));

    std::vector<std::string> b, c;
    const auto copyTime = microseconds([&] { b = a; });             // 200'000 allocations + copies
    const auto moveTime = microseconds([&] { c = std::move(a); });  // steals 3 pointers

    std::cout << "copy: " << copyTime << " us\n";
    std::cout << "move: " << moveTime << " us\n";
    std::cout << "a.size() after move: " << a.size() << '\n';   // usually 0: valid but unspecified
    std::cout << "b.size() = " << b.size() << ", c.size() = " << c.size() << '\n';
}
