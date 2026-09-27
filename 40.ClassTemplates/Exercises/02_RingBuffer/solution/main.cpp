#include <iostream>
#include <array>
#include <concepts>
#include <string>

template <typename T, std::size_t N>
class RingBuffer {
    static_assert(N > 0, "RingBuffer needs a capacity of at least 1");

public:
    void push(const T& value)
    {
        data[next] = value;
        next = (next + 1) % N;   // wrap around: the "ring"
        if (count < N) ++count;
    }

    std::size_t size() const { return count; }

    T operator[](std::size_t i) const
    {
        const std::size_t oldest = (count < N) ? 0 : next;   // when full, the oldest sits at `next`
        return data[(oldest + i) % N];
    }

    double average() const requires std::integral<T> || std::floating_point<T>
    {
        if (count == 0) return 0.0;
        double sum{0};
        for (std::size_t i = 0; i < count; ++i) sum += (*this)[i];
        return sum / static_cast<double>(count);
    }

private:
    std::array<T, N> data{};
    std::size_t next{0};
    std::size_t count{0};
};

int main()
{
    RingBuffer<int, 3> recent;
    for (int i = 1; i <= 5; ++i) recent.push(i);
    for (std::size_t i = 0; i < recent.size(); ++i) std::cout << recent[i] << ' ';   // 3 4 5
    std::cout << "| average " << recent.average() << '\n';

    RingBuffer<std::string, 2> files;
    files.push("a.txt");
    files.push("b.txt");
    files.push("c.txt");
    std::cout << files[0] << ' ' << files[1] << '\n';   // b.txt c.txt
    // files.average();   // error: constraints not satisfied
}
