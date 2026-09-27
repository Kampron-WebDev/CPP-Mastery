// std::async + std::future: split work, run it in parallel, collect the results. No shared state!
#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

long long sumRange(const std::vector<int>& data, std::size_t from, std::size_t to)
{
    return std::accumulate(data.begin() + static_cast<std::ptrdiff_t>(from),
                           data.begin() + static_cast<std::ptrdiff_t>(to), 0LL);
}

int mayFail(int x)
{
    if (x < 0) throw std::invalid_argument{"negative input"};
    return x * 2;
}

int main()
{
    std::vector<int> data(20'000'000, 1);
    const std::size_t parts = 4, chunk = data.size() / parts;

    const auto start = std::chrono::steady_clock::now();
    std::vector<std::future<long long>> futures;
    for (std::size_t p = 0; p < parts; ++p) {
        const std::size_t from = p * chunk;
        const std::size_t to = (p == parts - 1) ? data.size() : from + chunk;
        futures.push_back(std::async(std::launch::async, sumRange, std::cref(data), from, to));
    }
    long long total{0};
    for (auto& f : futures) total += f.get();   // get() waits for each result
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    std::cout << "parallel total: " << total << " in " << ms.count() << " ms\n";

    // Exceptions travel through the future to whoever calls get()
    auto bad = std::async(std::launch::async, mayFail, -1);
    try {
        std::cout << bad.get() << '\n';
    } catch (const std::exception& e) {
        std::cout << "task failed: " << e.what() << '\n';
    }
}
