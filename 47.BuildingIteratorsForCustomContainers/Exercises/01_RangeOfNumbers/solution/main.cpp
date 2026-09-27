#include <iostream>
#include <iterator>
#include <numeric>
#include <ranges>

class NumberRange {
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = const int*;
        using reference = int;   // we produce values on the fly, so "reference" is a plain int

        Iterator() = default;
        Iterator(int value, int step) : value{value}, step{step} {}

        int operator*() const { return value; }
        Iterator& operator++()
        {
            value += step;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator old = *this;
            ++*this;
            return old;
        }
        friend bool operator==(const Iterator& a, const Iterator& b) { return a.value == b.value; }

    private:
        int value{0};
        int step{1};
    };

    NumberRange(int start, int stop, int step = 1) : start{start}, step{step}
    {
        // Round stop UP to the next value the sequence actually hits, so == end() is reached.
        const int count = (stop > start) ? (stop - start + step - 1) / step : 0;
        last = start + count * step;
    }

    Iterator begin() const { return {start, step}; }
    Iterator end() const { return {last, step}; }

private:
    int start;
    int step;
    int last;
};

static_assert(std::forward_iterator<NumberRange::Iterator>);

int main()
{
    for (int x : NumberRange{0, 10, 2}) std::cout << x << ' ';
    std::cout << '\n';
    for (int x : NumberRange{0, 10, 3}) std::cout << x << ' ';   // 0 3 6 9
    std::cout << '\n';

    const NumberRange r{1, 101};
    std::cout << "sum 1..100 = " << std::accumulate(r.begin(), r.end(), 0) << '\n';

    for (int sq : NumberRange{1, 6} | std::views::transform([](int n) { return n * n; })) std::cout << sq << ' ';
    std::cout << '\n';
}
