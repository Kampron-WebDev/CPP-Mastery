#include <iostream>
#include <utility>
#include <vector>

class LoudBuffer {
public:
    explicit LoudBuffer(std::size_t n) : data{new int[n]{}}, size{n} { std::cout << "ctor(" << n << ")\n"; }

    LoudBuffer(const LoudBuffer& o) : data{new int[o.size]}, size{o.size}
    {
        for (std::size_t i = 0; i < size; ++i) data[i] = o.data[i];
        std::cout << "copy ctor\n";
    }

    LoudBuffer& operator=(const LoudBuffer& o)
    {
        std::cout << "copy assign\n";
        if (this != &o) {
            LoudBuffer tmp{o};          // copy-and-swap: strong exception guarantee
            swap(tmp);
        }
        return *this;
    }

    LoudBuffer(LoudBuffer&& o) noexcept
        : data{std::exchange(o.data, nullptr)}, size{std::exchange(o.size, 0)}
    {
        std::cout << "move ctor\n";
    }

    LoudBuffer& operator=(LoudBuffer&& o) noexcept
    {
        std::cout << "move assign\n";
        if (this != &o) {
            delete[] data;
            data = std::exchange(o.data, nullptr);
            size = std::exchange(o.size, 0);
        }
        return *this;
    }

    ~LoudBuffer()
    {
        std::cout << "dtor (owns " << size << " ints)\n";
        delete[] data;
    }

    void swap(LoudBuffer& o) noexcept
    {
        std::swap(data, o.data);
        std::swap(size, o.size);
    }

private:
    int* data;
    std::size_t size;
};

int main()
{
    std::cout << "-- a\n";            LoudBuffer a{5};                 // ctor(5)
    std::cout << "-- b{a}\n";         LoudBuffer b{a};                 // copy ctor
    std::cout << "-- c{move(a)}\n";   LoudBuffer c{std::move(a)};      // move ctor (a now owns 0)
    std::cout << "-- b = c\n";        b = c;                           // copy assign (+ copy ctor/dtor of tmp)
    std::cout << "-- b = temp\n";     b = LoudBuffer{3};               // ctor(3), move assign, dtor of empty temp
    std::cout << "-- vector\n";
    std::vector<LoudBuffer> v;
    v.push_back(LoudBuffer{2});       // ctor(2), move ctor into the vector, dtor of empty temp
    v.push_back(std::move(c));        // move ctor for c; vector grows: MOVES the old element (noexcept!)
    std::cout << "-- end of main\n";
}
// Without noexcept on the move ctor, the vector's growth COPIES the old element instead
// (it can't risk a throwing move halfway through), so you'd see an extra "copy ctor".
