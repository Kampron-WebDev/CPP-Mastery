#include <iostream>
#include <vector>

long long waysRecursive(int n)   // O(2^n): recomputes the same sub-problems over and over
{
    if (n <= 2) return n;
    return waysRecursive(n - 1) + waysRecursive(n - 2);
}

long long waysMemo(int n, std::vector<long long>& memo)   // O(n): each n solved once
{
    if (n <= 2) return n;
    auto& slot = memo[static_cast<std::size_t>(n)];
    if (slot == 0) slot = waysMemo(n - 1, memo) + waysMemo(n - 2, memo);
    return slot;
}

long long waysBottomUp(int n)   // O(n) time, O(1) memory
{
    if (n <= 2) return n;
    long long twoBack = 1, oneBack = 2;
    for (int step = 3; step <= n; ++step) {
        const long long current = oneBack + twoBack;
        twoBack = oneBack;
        oneBack = current;
    }
    return oneBack;
}

long long waysWithThree(int n)   // bonus: steps of 1, 2 or 3
{
    std::vector<long long> ways(static_cast<std::size_t>(std::max(n + 1, 4)), 0);
    ways[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int step = 1; step <= 3; ++step)
            if (i - step >= 0) ways[static_cast<std::size_t>(i)] += ways[static_cast<std::size_t>(i - step)];
    return ways[static_cast<std::size_t>(n)];
}

int main()
{
    std::cout << "recursive(30) = " << waysRecursive(30) << '\n';
    std::vector<long long> memo(51, 0);
    std::cout << "memo(50)      = " << waysMemo(50, memo) << '\n';
    std::cout << "bottomUp(50)  = " << waysBottomUp(50) << '\n';
    std::cout << "with 1/2/3 steps, n=10: " << waysWithThree(10) << '\n';   // 274
}
