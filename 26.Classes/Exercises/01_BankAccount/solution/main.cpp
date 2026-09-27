#include <iostream>
#include <iomanip>
#include <string>
#include <utility>

class BankAccount {
public:
    BankAccount(std::string owner, long long initialCents)
        : ownerName{std::move(owner)}, balanceCents{initialCents > 0 ? initialCents : 0}
    {
    }

    bool deposit(long long cents)
    {
        if (cents <= 0) return false;
        balanceCents += cents;
        return true;
    }

    bool withdraw(long long cents)
    {
        if (cents <= 0 || cents > balanceCents) return false;   // protects the invariant
        balanceCents -= cents;
        return true;
    }

    long long balance() const { return balanceCents; }
    const std::string& owner() const { return ownerName; }

    void print() const
    {
        std::cout << ownerName << ": $" << balanceCents / 100 << '.' << std::setw(2)
                  << std::setfill('0') << balanceCents % 100 << std::setfill(' ') << '\n';
    }

private:
    std::string ownerName;
    long long balanceCents;   // invariant: always >= 0
};

int main()
{
    BankAccount account{"Ada", 1000};
    account.print();                                   // Ada: $10.00
    account.deposit(205);
    account.print();                                   // Ada: $12.05
    std::cout << std::boolalpha;
    std::cout << "withdraw 5000: " << account.withdraw(5000) << '\n';   // false
    std::cout << "withdraw -3:   " << account.withdraw(-3) << '\n';     // false
    std::cout << "withdraw 1200: " << account.withdraw(1200) << '\n';   // true
    account.print();                                   // Ada: $0.05
}
