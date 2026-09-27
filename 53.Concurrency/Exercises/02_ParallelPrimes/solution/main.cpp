#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

bool isPrime(int n)
{
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (int d = 3; d * d <= n; d += 2)
        if (n % d == 0) return false;
    return true;
}

int countPrimes(int from, int to)
{
    int count{0};
    for (int n = from; n < to; ++n) count += isPrime(n);
    return count;
}

template <typename F>
auto timed(F f)
{
    const auto start = std::chrono::steady_clock::now();
    const auto result = f();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    return std::pair{result, ms.count()};
}

int main()
{
    constexpr int limit{5'000'000};
    const int parts = static_cast<int>(std::max(1u, std::thread::hardware_concurrency()));

    const auto [single, singleMs] = timed([] { return countPrimes(0, limit); });

    const auto [parallel, parallelMs] = timed([parts] {
        std::vector<std::future<int>> futures;
        const int chunk = limit / parts;
        for (int p = 0; p < parts; ++p) {
            const int from = p * chunk;
            const int to = (p == parts - 1) ? limit : from + chunk;
            futures.push_back(std::async(std::launch::async, countPrimes, from, to));
        }
        int total{0};
        for (auto& f : futures) total += f.get();
        return total;
    });

    std::cout << "single:   " << single << " primes in " << singleMs << " ms\n";
    std::cout << "parallel: " << parallel << " primes in " << parallelMs << " ms on " << parts << " threads\n";
    if (parallelMs > 0) std::cout << "speed-up: " << static_cast<double>(singleMs) / parallelMs << "x\n";
    // The last chunk (biggest numbers) is the slowest, so the others wait for it.
    // Better balancing: many small chunks, or interleaving (thread t checks t, t+N, t+2N, ...).
}
