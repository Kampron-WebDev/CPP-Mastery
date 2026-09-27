# Project 08: Thread Pool ⭐⭐⭐⭐

Creating a thread for every little task is expensive. A **thread pool** keeps N worker threads alive and feeds them tasks
from a queue. Every serious server, game engine and build tool has one.

## Spec
```cpp
ThreadPool pool{4};
auto f1 = pool.submit([] { return 6 * 7; });            // returns std::future<int>
auto f2 = pool.submit(expensiveFunction, arg1, arg2);
std::cout << f1.get();                                   // 42
// pool's destructor finishes queued work and joins all threads (RAII)
```
- Workers wait on a `std::condition_variable` for tasks (Lesson 53's producer/consumer).
- `submit` works with any callable + arguments and returns the right `std::future<R>` (use `std::packaged_task`).
- Exceptions thrown by tasks come out of `future.get()`.
- Clean shutdown: no lost tasks, no deadlocks, no data races.

## Milestones
1. Fixed pool running `std::function<void()>` tasks. 2. Futures + return values via `std::packaged_task`. 3. Shutdown semantics + tests.
4. Benchmark: pool vs. `std::async` vs. one thread per task, for 10 000 tiny tasks (Lesson 58).
5. Use it to parallelise MiniGrep (Project 06).

## Stretch
- Work stealing (one queue per worker). Task priorities. `wait_all()`.

Starter: [main.cpp](main.cpp)
