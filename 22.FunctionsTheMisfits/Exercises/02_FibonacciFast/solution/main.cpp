#include <iostream>

long long naiveCalls{0};
long long fibNaive(int n)
{
    ++naiveCalls;
    if (n < 2) return n;
    return fibNaive(n - 1) + fibNaive(n - 2);   // recomputes the same values again and again
}

long long memoCalls{0};
long long fibMemo(int n)
{
    static long long memo[93]{};   // 0 means "not computed yet" (fib(n) > 0 for n >= 1)
    ++memoCalls;
    if (n < 2) return n;
    if (memo[n] != 0) return memo[n];
    memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
    return memo[n];
}

long long fibLoop(int n)
{
    long long prev{0}, curr{1};
    if (n == 0) return 0;
    for (int i = 2; i <= n; ++i) {
        const long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main()
{
    std::cout << "naive fib(30) = " << fibNaive(30) << " using " << naiveCalls << " calls\n";
    std::cout << "memo  fib(30) = " << fibMemo(30) << " using " << memoCalls << " calls\n";
    std::cout << "loop  fib(92) = " << fibLoop(92) << '\n';
    // Loop: O(n) time, O(1) memory, no risk of stack overflow. The winner for this problem.
}
