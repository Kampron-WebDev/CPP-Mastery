// std::span (a view over contiguous data) and std::chrono (time with units).
#include <array>
#include <chrono>
#include <format>
#include <iostream>
#include <numeric>
#include <span>
#include <thread>
#include <vector>

double average(std::span<const int> values)   // accepts ANY contiguous sequence of ints
{
    if (values.empty()) return 0.0;
    return std::accumulate(values.begin(), values.end(), 0.0) / static_cast<double>(values.size());
}

int main()
{
    std::vector<int> v{10, 20, 30, 40, 50};
    std::array<int, 3> a{1, 2, 3};
    int raw[]{7, 8, 9, 10};

    std::cout << average(v) << ' ' << average(a) << ' ' << average(raw) << '\n';
    std::cout << "middle three of v: " << average(std::span{v}.subspan(1, 3)) << '\n';   // 20 30 40

    using namespace std::chrono_literals;
    const auto timeout = 1500ms;
    std::cout << "timeout = " << timeout.count() << " ms = "
              << std::chrono::duration_cast<std::chrono::seconds>(timeout).count() << " s (truncated)\n";

    const auto start = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(120ms);
    const auto elapsed = std::chrono::steady_clock::now() - start;
    std::cout << "slept about " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() << " ms\n";

    std::cout << std::format("today (UTC): {:%Y-%m-%d}\n", std::chrono::system_clock::now());
}
