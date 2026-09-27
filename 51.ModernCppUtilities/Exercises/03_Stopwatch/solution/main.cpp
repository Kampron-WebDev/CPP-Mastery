#include <chrono>
#include <format>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>

class Stopwatch {
public:
    using Clock = std::chrono::steady_clock;

    void start()
    {
        if (!running) {
            began = Clock::now();
            running = true;
        }
    }
    void stop()
    {
        if (running) {
            stored += Clock::now() - began;
            running = false;
        }
    }
    void reset()
    {
        stored = Clock::duration::zero();
        running = false;
    }
    std::chrono::milliseconds elapsed() const
    {
        auto total = stored;
        if (running) total += Clock::now() - began;
        return std::chrono::duration_cast<std::chrono::milliseconds>(total);
    }

private:
    Clock::time_point began{};
    Clock::duration stored{Clock::duration::zero()};
    bool running{false};
};

long long sumOf(std::span<const int> values) { return std::accumulate(values.begin(), values.end(), 0LL); }

int main()
{
    std::vector<int> data(10'000'000);
    std::iota(data.begin(), data.end(), 1);   // 1, 2, 3, ...

    Stopwatch sw;
    sw.start();
    const long long all = sumOf(data);
    sw.stop();
    std::cout << std::format("sum of all  = {} in {} ms\n", all, sw.elapsed().count());

    sw.reset();
    sw.start();
    const long long half = sumOf(std::span{data}.first(data.size() / 2));
    sw.stop();
    std::cout << std::format("sum of half = {} in {} ms\n", half, sw.elapsed().count());
}
