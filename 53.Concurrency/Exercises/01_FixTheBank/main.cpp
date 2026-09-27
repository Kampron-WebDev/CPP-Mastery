// ⭐⭐ Exercise 01: FixTheBank
// 4 threads move money between two accounts at random. Money is never created or destroyed,
// so the TOTAL must always be 2000. Run it a few times: the total is often wrong!
// 1. Explain the race in a comment.
// 2. Fix it with a std::mutex in each Account.
// 3. transfer() must lock BOTH accounts. Locking them one after the other in argument
//    order can DEADLOCK (thread 1: a then b; thread 2: b then a). Use std::scoped_lock.
#include <iostream>
#include <random>
#include <thread>
#include <vector>

struct Account {
    int balance{1000};
};

void transfer(Account& from, Account& to, int amount)
{
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
    std::cout << "a=" << a.balance << " b=" << b.balance << " total=" << a.balance + b.balance << '\n';
}
