#include <iostream>
#include <iomanip>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 engine{rd()};
    std::uniform_int_distribution<int> die{1, 6};

    int counts[13]{};   // index = total; we only use 2..12
    constexpr int rolls{10'000};
    for (int i = 0; i < rolls; ++i)
        ++counts[die(engine) + die(engine)];

    for (int total = 2; total <= 12; ++total) {
        std::cout << std::setw(2) << total << ": ";
        for (int s = 0; s < counts[total] / 60; ++s) std::cout << '*';
        std::cout << "  (" << counts[total] << ")\n";
    }
    // 7 is most common: 6 combinations make it (1+6, 2+5, 3+4, 4+3, 5+2, 6+1),
    // while 2 and 12 have only one combination each.
}
