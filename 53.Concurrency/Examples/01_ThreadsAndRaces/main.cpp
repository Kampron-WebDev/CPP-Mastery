// A data race in action, then two correct fixes.
#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

constexpr int threadsCount{4};
constexpr int incrementsEach{250'000};

template <typename Work>
void runOnThreads(Work work)
{
    std::vector<std::jthread> threads;
    for (int t = 0; t < threadsCount; ++t) threads.emplace_back(work);
}   // every jthread joins here automatically

int main()
{
    std::cout << "hardware threads: " << std::thread::hardware_concurrency() << "\n\n";

    // 1. BROKEN: unsynchronized ++ on shared data (undefined behaviour: results vary run to run)
    //    'volatile' only stops the optimizer hiding the bug; it does NOT make the code thread-safe.
    volatile int racy{0};
    runOnThreads([&] { for (int i = 0; i < incrementsEach; ++i) racy = racy + 1; });
    std::cout << "racy counter:   " << racy << "  (expected " << threadsCount * incrementsEach << ")\n";

    // 2. FIX with a mutex: correct, but threads queue up for the lock
    int guarded{0};
    std::mutex m;
    runOnThreads([&] {
        for (int i = 0; i < incrementsEach; ++i) {
            std::lock_guard lock{m};
            ++guarded;
        }
    });
    std::cout << "mutex counter:  " << guarded << '\n';

    // 3. FIX with an atomic: correct and simpler for a single variable
    std::atomic<int> atomicCounter{0};
    runOnThreads([&] { for (int i = 0; i < incrementsEach; ++i) ++atomicCounter; });
    std::cout << "atomic counter: " << atomicCounter << '\n';
}
