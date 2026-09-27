#include <iostream>
#include <coroutine>
#include <exception>
#include <utility>

template <typename T>
class Generator {
public:
    struct promise_type {
        T current{};
        Generator get_return_object() { return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() noexcept { return {}; }   // lazy: don't start until next()
        std::suspend_always final_suspend() noexcept { return {}; }     // keep the frame so done() is valid
        std::suspend_always yield_value(T value) noexcept
        {
            current = std::move(value);
            return {};
        }
        void return_void() noexcept {}
        void unhandled_exception() { std::terminate(); }
    };

    explicit Generator(std::coroutine_handle<promise_type> h) : handle{h} {}
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& other) noexcept : handle{std::exchange(other.handle, {})} {}
    Generator& operator=(Generator&& other) noexcept
    {
        if (this != &other) {
            if (handle) handle.destroy();
            handle = std::exchange(other.handle, {});
        }
        return *this;
    }
    ~Generator()
    {
        if (handle) handle.destroy();   // RAII: free the coroutine frame
    }

    bool next()
    {
        if (!handle || handle.done()) return false;
        handle.resume();                // run until the next co_yield (or the end)
        return !handle.done();
    }
    const T& value() const { return handle.promise().current; }

private:
    std::coroutine_handle<promise_type> handle;
};

Generator<long long> fibonacci()
{
    long long a = 0, b = 1;
    while (true) {
        co_yield a;
        const long long next = a + b;
        a = b;
        b = next;
    }
}

Generator<int> range(int from, int to)
{
    for (int i = from; i < to; ++i) co_yield i;
}

int main()
{
    auto fib = fibonacci();
    for (int i = 0; i < 10 && fib.next(); ++i) std::cout << fib.value() << ' ';
    std::cout << '\n';

    auto r = range(5, 9);
    while (r.next()) std::cout << r.value() << ' ';
    std::cout << "(done)\n";
}
