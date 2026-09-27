// ⭐⭐⭐ Exercise 03: CancellableWorker
// A "download" worker runs in the background and reports progress 0..100%.
// 1. Start it with std::jthread; its function takes a std::stop_token as FIRST parameter.
// 2. Each step (sleep 50 ms), check  token.stop_requested()  and stop early if asked.
// 3. Progress is shared: store it in a std::atomic<int>.
// 4. main() prints the progress every 100 ms; after 600 ms it calls worker.request_stop().
// 5. Print whether the download finished or was cancelled, and at what percent.
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    // TODO
}
