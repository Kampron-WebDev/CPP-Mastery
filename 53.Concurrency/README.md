# Lesson 53: Concurrency: Threads, Locks and Async ⭐ NEW

> **In one sentence:** Modern CPUs have many cores; **threads** let your program do several
> things at the same time, and **synchronization** (mutexes, atomics) stops those threads from
> trampling on each other's data.

---

## 🎯 You will learn

- Starting threads (`std::thread`, `std::jthread`) and waiting for them (`join`).
- **Data races**: what they are and why they're undefined behaviour.
- `std::mutex`, `std::lock_guard`, `std::scoped_lock`, `std::unique_lock`.
- `std::atomic` for simple shared counters.
- `std::condition_variable`: waiting for something to happen (producer/consumer).
- `std::async` and `std::future`: run a task, get its result later.
- **Deadlocks** and how to avoid them; `std::stop_token`.

---

## 🧸 The Big Idea: cooks in one kitchen

One cook (one thread) makes dinner step by step. **Four cooks** (four threads) can make it much faster:
one chops, one boils, one bakes, one makes dessert.

But there's **one salt shaker**. If two cooks grab it at the same moment, salt goes everywhere.
That's a **data race**. The fix is a rule: *"whoever holds the salt shaker's token (the **mutex**)
may use it; everyone else waits."*

And if cook A holds the salt and waits for the pepper, while cook B holds the pepper and waits for the salt,
they both wait **forever**. That's a **deadlock**.

```
  Thread 1: read counter (5) ──► add 1 ──► write 6
  Thread 2:      read counter (5) ──► add 1 ──► write 6      ← one increment LOST!
```

---

## 📚 Step by step

### 1. Starting threads ([Examples/01_ThreadsAndRaces](Examples/01_ThreadsAndRaces/main.cpp))
```cpp
#include <thread>
std::thread t{[] { std::cout << "hello from a thread\n"; }};
t.join();                        // WAIT for it to finish. Forgetting join() → std::terminate!

std::jthread jt{work};           // C++20: joins AUTOMATICALLY in its destructor (RAII!). Prefer this.
std::thread::hardware_concurrency();   // how many cores
```

### 2. Mutexes and locks
```cpp
std::mutex m;
int counter{0};
void increment() {
    std::lock_guard lock{m};     // locks now; unlocks at } automatically (RAII)
    ++counter;
}
```
| Tool | Use |
|------|-----|
| `std::lock_guard` | Simple: lock for this scope |
| `std::scoped_lock` | Lock **several** mutexes at once, deadlock-free |
| `std::unique_lock` | Flexible (unlock early; needed by condition variables) |

### 3. Atomics
```cpp
std::atomic<int> counter{0};
++counter;                       // indivisible: no mutex needed for a single variable
```

### 4. Condition variables ([Examples/02_ProducerConsumer](Examples/02_ProducerConsumer/main.cpp))
"Sleep until there's work":
```cpp
std::unique_lock lock{m};
cv.wait(lock, [&] { return !queue.empty() || done; });   // the predicate protects against "spurious wakeups"
```
Producer: push under the lock, then `cv.notify_one()`.

### 5. `std::async` and futures ([Examples/03_AsyncFutures](Examples/03_AsyncFutures/main.cpp))
```cpp
std::future<long long> f = std::async(std::launch::async, sumRange, 1, 1'000'000);
// ... do other work ...
long long result = f.get();      // waits if needed; rethrows the task's exception if it threw
```
The easiest safe way to run work in parallel: no shared state, just results.

### 6. Deadlocks
Avoid them by: locking in a **consistent order**, using `std::scoped_lock(m1, m2)`, keeping locked sections **tiny**,
and never calling unknown code (callbacks) while holding a lock.

---

## 🗂️ Examples

| Folder | Shows |
|--------|-------|
| [01_ThreadsAndRaces](Examples/01_ThreadsAndRaces/main.cpp) | A real data race losing increments, fixed with mutex and atomic |
| [02_ProducerConsumer](Examples/02_ProducerConsumer/main.cpp) | A thread-safe queue with `condition_variable` + `jthread` |
| [03_AsyncFutures](Examples/03_AsyncFutures/main.cpp) | Parallel sum with `std::async`; exceptions through futures |

## ⚠️ Common mistakes

- Forgetting to `join()` a `std::thread` → program terminates. (Use `std::jthread`.)
- Reading shared data "just to look" without a lock. Unsynchronized reads racing with writes are still a data race (UB).
- Capturing locals by reference in a thread that outlives them.
- Holding a lock while doing slow work (I/O, sleeping), which kills the parallelism.
- `cv.wait` without a predicate.

## 🧠 Senior developer notes

- **The best shared state is no shared state.** Give each thread its own data, then combine results (like 03_AsyncFutures).
- Concurrency bugs are **non-deterministic**: the program "works" 999 times. Reason about correctness; don't trust testing alone.
  Tools: ThreadSanitizer (`-fsanitize=thread` on Linux/Clang).
- More threads ≠ faster. Beyond the core count, and with contention, it's slower. Measure (Lesson 58).
- Higher-level tools exist: parallel algorithms (`std::execution::par`), thread pools, task libraries.

## ✅ Check yourself

1. What is a data race?
2. Why prefer `std::jthread` over `std::thread`?
3. When is `std::atomic<int>` enough, and when do you need a mutex?
4. Name two ways to avoid deadlock.

<details><summary>Answers</summary>

1. Two threads access the same memory at the same time, at least one writes, with no synchronization. That's undefined behaviour.
2. It joins automatically in its destructor (RAII) and supports cooperative cancellation (`stop_token`).
3. Atomic is enough for a single independent variable; a mutex is needed when several values must change together consistently.
4. Always lock in the same order; lock several mutexes at once with `std::scoped_lock`; keep critical sections small.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 54: Data Structures and Algorithms](../54.DataStructuresAndAlgorithms/README.md)
