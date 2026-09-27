#include <iostream>
#include <vector>

bool isPrime(int n)
{
    if (n < 2) return false;
    for (int d = 2; d * d <= n; ++d)
        if (n % d == 0) return false;
    return true;
}

int main()
{
    // Part A: trial division, fine for small ranges
    for (int n = 2; n < 100; ++n)
        if (isPrime(n)) std::cout << n << ' ';
    std::cout << '\n';

    // Part B: Sieve of Eratosthenes. Cross out multiples instead of testing divisors.
    constexpr int limit{1'000'000};
    std::vector<bool> prime(limit, true);
    prime[0] = prime[1] = false;
    for (int p = 2; p * p < limit; ++p) {
        if (!prime[p]) continue;
        for (int multiple = p * p; multiple < limit; multiple += p)
            prime[multiple] = false;
    }
    int count{0};
    for (bool isP : prime) count += isP;
    std::cout << "Primes below " << limit << ": " << count << '\n';   // 78498
}
