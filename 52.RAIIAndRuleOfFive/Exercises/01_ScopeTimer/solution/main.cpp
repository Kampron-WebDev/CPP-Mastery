#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <utility>
#include <vector>

class ScopeTimer {
public:
    explicit ScopeTimer(std::string label) : label{std::move(label)}, start{std::chrono::steady_clock::now()} {}
    ~ScopeTimer()
    {
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
        std::cout << label << " took " << ms.count() << " ms\n";
    }
    ScopeTimer(const ScopeTimer&) = delete;
    ScopeTimer& operator=(const ScopeTimer&) = delete;

private:
    std::string label;
    std::chrono::steady_clock::time_point start;
};

int findFirstOver(const std::vector<int>& v, int limit)
{
    ScopeTimer t{"search with early return"};
    for (std::size_t i = 0; i < v.size(); ++i)
        if (v[i] > limit) return static_cast<int>(i);   // the timer still reports: destructor runs
    return -1;
}

int main()
{
    std::vector<int> v(1'000'000);
    std::iota(v.begin(), v.end(), 0);
    std::shuffle(v.begin(), v.end(), std::mt19937{42});

    {
        ScopeTimer t{"sorting 1M ints"};
        std::sort(v.begin(), v.end());
    }
    {
        ScopeTimer t{"summing"};
        std::cout << "sum = " << std::accumulate(v.begin(), v.end(), 0LL) << '\n';
    }
    std::cout << "index " << findFirstOver(v, 500'000) << '\n';
}
