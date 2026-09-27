#include <atomic>
#include <chrono>
#include <iostream>
#include <stop_token>
#include <thread>

int main()
{
    using namespace std::chrono_literals;
    std::atomic<int> progress{0};
    std::atomic<bool> cancelled{false};

    std::jthread worker{[&](std::stop_token token) {
        for (int p = 0; p <= 100; p += 5) {
            if (token.stop_requested()) {   // cooperative cancellation: the worker decides when it's safe to stop
                cancelled = true;
                return;
            }
            progress = p;
            std::this_thread::sleep_for(50ms);
        }
    }};

    for (int elapsed = 0; elapsed < 600 && progress < 100; elapsed += 100) {
        std::cout << "progress: " << progress << "%\n";
        std::this_thread::sleep_for(100ms);
    }
    worker.request_stop();
    worker.join();   // (jthread would also join in its destructor)

    if (cancelled) std::cout << "download CANCELLED at " << progress << "%\n";
    else           std::cout << "download finished (100%)\n";
}
