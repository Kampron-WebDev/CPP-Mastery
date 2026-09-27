// Feel Big-O: count how the time grows when n doubles.
// Build with the "Optimized -O2" task for fair numbers.
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

template <typename F>
long long microseconds(F f)
{
    const auto start = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count();
}

// O(n²): compare every pair
bool hasDuplicateQuadratic(const std::vector<int>& v)
{
    for (std::size_t i = 0; i < v.size(); ++i)
        for (std::size_t j = i + 1; j < v.size(); ++j)
            if (v[i] == v[j]) return true;
    return false;
}

// O(n log n): sort a copy, then neighbours
bool hasDuplicateSorted(std::vector<int> v)
{
    std::sort(v.begin(), v.end());
    return std::adjacent_find(v.begin(), v.end()) != v.end();
}

int main()
{
    std::cout << "     n   O(n^2) us   O(n log n) us\n";
    for (int n = 2'000; n <= 32'000; n *= 2) {
        std::vector<int> v(static_cast<std::size_t>(n));
        std::iota(v.begin(), v.end(), 0);   // no duplicates: the worst case (must check everything)
        bool r1{}, r2{};
        const auto t1 = microseconds([&] { r1 = hasDuplicateQuadratic(v); });
        const auto t2 = microseconds([&] { r2 = hasDuplicateSorted(v); });
        std::cout << n << "\t" << t1 << "\t\t" << t2 << (r1 || r2 ? " (dup?!)" : "") << '\n';
    }
    std::cout << "\nNotice: when n doubles, O(n^2) takes ~4x longer; O(n log n) only ~2x.\n";
}
