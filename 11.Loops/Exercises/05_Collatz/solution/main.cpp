#include <iostream>

int collatzSteps(long long n)
{
    int steps{0};
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        ++steps;
    }
    return steps;
}

int main()
{
    long long n{};
    std::cout << "Start: ";
    std::cin >> n;
    if (n < 1) {
        std::cout << "Need a positive number.\n";
        return 1;
    }

    int steps{0};
    std::cout << n;
    while (n != 1) {
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        std::cout << ' ' << n;
        ++steps;
    }
    std::cout << "  (" << steps << " steps)\n";

    int bestStart{1}, bestSteps{0};
    for (int start = 1; start < 10'000; ++start) {
        int s = collatzSteps(start);
        if (s > bestSteps) {
            bestSteps = s;
            bestStart = start;
        }
    }
    std::cout << "Below 10000, " << bestStart << " takes the most steps: " << bestSteps << '\n';
}
