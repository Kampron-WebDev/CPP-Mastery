#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

// The race: two threads can read the same balance, both subtract/add, and one write overwrites the
// other ("lost update"). Also the check (balance >= amount) and the update aren't one atomic step.
struct Account {
    int balance{1000};
    std::mutex m;
};

void transfer(Account& from, Account& to, int amount)
{
    // scoped_lock locks both mutexes using a deadlock-avoidance algorithm,
    // so transfer(a, b) and transfer(b, a) running at the same time can't deadlock.
    std::scoped_lock lock{from.m, to.m};
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
    }
}

int main()
{
    Account a, b;
    {
        std::vector<std::jthread> threads;
        for (int t = 0; t < 4; ++t) {
            threads.emplace_back([&, t] {
                std::mt19937 rng(static_cast<unsigned>(t));
                for (int i = 0; i < 100'000; ++i) {
                    if (rng() % 2) transfer(a, b, 1 + static_cast<int>(rng() % 10));
                    else           transfer(b, a, 1 + static_cast<int>(rng() % 10));
                }
            });
        }
    }
    std::cout << "a=" << a.balance << " b=" << b.balance << " total=" << a.balance + b.balance << '\n';   // always 2000
}
