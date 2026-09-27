#include <iostream>

// Greedy algorithm: always give as many of the biggest coin as possible.
// (Works for these coin values. For strange coin systems it can fail. See Lesson 54.)
int main()
{
    int cents{};
    std::cout << "Change owed in cents: ";
    std::cin >> cents;
    if (cents < 0) {
        std::cout << "Change can't be negative.\n";
        return 1;
    }

    const int coins[] = {100, 50, 25, 10, 5, 1};
    for (int coin : coins) {
        int count = cents / coin;   // how many of this coin fit?
        cents = cents % coin;       // what is left to pay?
        std::cout << coin << "c x " << count << '\n';
    }
}
