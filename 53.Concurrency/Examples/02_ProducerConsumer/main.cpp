// A thread-safe queue: producers add jobs, consumers wait for them (condition_variable).
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <string>
#include <thread>
#include <vector>

template <typename T>
class ThreadSafeQueue {
public:
    void push(T value)
    {
        {
            std::lock_guard lock{m};
            items.push(std::move(value));
        }
        cv.notify_one();   // wake one waiting consumer
    }

    // Waits for an item. Returns nothing once the queue is closed AND empty.
    std::optional<T> pop()
    {
        std::unique_lock lock{m};
        cv.wait(lock, [&] { return !items.empty() || closed; });
        if (items.empty()) return std::nullopt;
        T value = std::move(items.front());
        items.pop();
        return value;
    }

    void close()
    {
        {
            std::lock_guard lock{m};
            closed = true;
        }
        cv.notify_all();   // wake everyone so they can finish
    }

private:
    std::mutex m;
    std::condition_variable cv;
    std::queue<T> items;
    bool closed{false};
};

int main()
{
    ThreadSafeQueue<int> jobs;
    std::mutex printMutex;   // std::cout isn't synchronized line-by-line; protect whole lines

    std::vector<std::jthread> workers;
    for (int w = 1; w <= 3; ++w) {
        workers.emplace_back([&, w] {
            while (auto job = jobs.pop()) {
                std::lock_guard lock{printMutex};
                std::cout << "worker " << w << " processed job " << *job << '\n';
            }
        });
    }

    for (int j = 1; j <= 9; ++j) jobs.push(j);
    jobs.close();
}   // workers finish remaining jobs, then join
