// ⭐⭐ Exercise 02: ParallelPrimes
// Count the primes below 5'000'000 using trial division (bool isPrime(int)).
// 1. Do it on one thread and time it.
// 2. Split the range into N parts (N = std::thread::hardware_concurrency()), run each part with
//    std::async(std::launch::async, ...), add up the futures, and time it.
// 3. Print both times and the speed-up. Both counts must be 348513.
// Build with the "Optimized -O2" task for meaningful numbers.
// Think: are all parts equally hard? (Bigger numbers take longer to test.)
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int main()
{
    // TODO
}
