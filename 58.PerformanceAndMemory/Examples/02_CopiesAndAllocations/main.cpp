// Hidden copies and allocations, measured. Use the Optimized -O2 task.
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

template <typename F>
long long us(F f)
{
    const auto start = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
}

std::size_t totalLengthByValue(std::vector<std::string> words)   // copies EVERY string
{
    std::size_t total = 0;
    for (auto w : words) total += w.size();                        // ...and copies each one AGAIN
    return total;
}

std::size_t totalLengthByRef(const std::vector<std::string>& words)
{
    std::size_t total = 0;
    for (const auto& w : words) total += w.size();
    return total;
}

int main()
{
    const std::vector<std::string> words(200'000, std::string(40, 'x'));
    std::size_t r1 = 0, r2 = 0;
    std::cout << "by value:     " << us([&] { r1 = totalLengthByValue(words); }) << " us\n";
    std::cout << "by const ref: " << us([&] { r2 = totalLengthByRef(words); }) << " us   (" << r1 << " == " << r2 << ")\n";

    std::vector<int> noReserve, withReserve;
    std::cout << "push_back 5M, no reserve:   " << us([&] { for (int i = 0; i < 5'000'000; ++i) noReserve.push_back(i); }) << " us\n";
    std::cout << "push_back 5M, with reserve: " << us([&] {
        withReserve.reserve(5'000'000);
        for (int i = 0; i < 5'000'000; ++i) withReserve.push_back(i);
    }) << " us\n";

    std::string slow, fast;
    std::cout << "s = s + piece: " << us([&] { for (int i = 0; i < 20'000; ++i) slow = slow + "piece"; }) << " us\n";
    std::cout << "s += piece:    " << us([&] { for (int i = 0; i < 20'000; ++i) fast += "piece"; }) << " us   ("
              << (slow == fast ? "same result" : "different!") << ")\n";
}
