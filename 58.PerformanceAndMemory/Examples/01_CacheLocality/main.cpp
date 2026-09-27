// Same work, same Big-O, very different speed, because of the CPU cache.
// Run with the "Build & Run this folder (Optimized -O2)" task.
#include <chrono>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>

template <typename F>
long long ms(F f)
{
    const auto start = std::chrono::steady_clock::now();
    f();
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
}

int main()
{
    constexpr std::size_t n = 4000;
    std::vector<int> grid(n * n, 1);   // a 4000 x 4000 grid stored row after row
    long long sumRows = 0, sumCols = 0;

    const auto rowTime = ms([&] {
        for (std::size_t r = 0; r < n; ++r)
            for (std::size_t c = 0; c < n; ++c) sumRows += grid[r * n + c];   // walks memory in order
    });
    const auto colTime = ms([&] {
        for (std::size_t c = 0; c < n; ++c)
            for (std::size_t r = 0; r < n; ++r) sumCols += grid[r * n + c];   // jumps 16 KB each step
    });
    std::cout << "row by row:       " << rowTime << " ms (sum " << sumRows << ")\n";
    std::cout << "column by column: " << colTime << " ms (sum " << sumCols << ")\n";

    std::vector<int> vec(5'000'000, 1);
    std::list<int> lst(vec.begin(), vec.end());
    long long a = 0, b = 0;
    const auto vecTime = ms([&] { a = std::accumulate(vec.begin(), vec.end(), 0LL); });
    const auto lstTime = ms([&] { b = std::accumulate(lst.begin(), lst.end(), 0LL); });
    std::cout << "sum vector: " << vecTime << " ms, sum list: " << lstTime << " ms (" << a << ' ' << b << ")\n";
}
